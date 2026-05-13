<h1>Modul Percobaan 5: Real-Time Operating System Multitasking dan Komunikasi Task </h1>
<h2>Pertanyaan Praktikum Percobaan 5A</h2>
<ol>
  <li>Apakah ketiga task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!</li>
  <li>Bagaimana cara menambahkan task keempat? Jelaskan langkahnya!</li>
  <li>Modifikasilah program dengan menambah sensor (misalnya potensiometer), lalu gunakan nilainya untuk mengontrol kecepatan LED!</li>
</ol>

<p><b>Jawaban:</b></p>
<p>
1. Ketiga task pada FreeRTOS tidak benar-benar berjalan secara bersamaan karena Arduino Uno hanya memiliki satu prosesor. <br>
Task berjalan secara bergantian dengan sangat cepat melalui mekanisme scheduler pada FreeRTOS sehingga terlihat seperti berjalan bersamaan (concurrent).<br>
Scheduler akan mengatur pembagian waktu eksekusi prosesor ke setiap task berdasarkan prioritas dan delay yang diberikan. <br>
Ketika suatu task menjalankan fungsi vTaskDelay(), task tersebut akan berada pada kondisi blocked sehingga scheduler memindahkan eksekusi ke task lain yang siap dijalankan. <br>
Proses perpindahan ini disebut context switching. Dengan mekanisme tersebut, beberapa task seperti kontrol LED dan penampilan data Serial Monitor dapat berjalan secara bergantian tanpa saling mengganggu.
</p> <br>

<p>
2. Task keempat dapat ditambahkan dengan membuat fungsi task baru kemudian mendaftarkannya menggunakan fungsi xTaskCreate() pada setup(). <br>
Langkah-langkahnya sebagai berikut:
1. Membuat fungsi task baru, misalnya:
</p>

```cpp
void task4(void *pvParameters) {

  for(;;) {

    Serial.println("Task 4 berjalan");

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
```

<p>
2. Menambahkan task pada setup() menggunakan xTaskCreate():
</p>

```cpp
xTaskCreate(
  task4,
  "Task 4",
  128,
  NULL,
  1,
  NULL
);
```

<p>
3. Upload program ke Arduino Uno. <br>
4. Mengamati hasil pada Serial Monitor untuk memastikan task keempat berjalan bersama task lainnya. <br>
Dengan langkah tersebut, scheduler FreeRTOS akan mengatur eksekusi task keempat bersama task-task lainnya secara concurrent.
</p>

<p>
  3. Pada percobaan ini ditambahkan potensiometer sebagai input analog untuk mengontrol kecepatan kedipan LED. Nilai analog dari potensiometer dibaca menggunakan fungsi analogRead(), kemudian digunakan sebagai nilai delay LED. <br>

Semakin besar nilai potensiometer, maka delay LED menjadi semakin besar sehingga LED berkedip lebih lambat. Sebaliknya, jika nilai potensiometer kecil maka delay menjadi lebih kecil sehingga LED berkedip lebih cepat. <br>

Contoh potongan program:
</p>

```cpp
int potValue;
int delayLED;

void taskPotensiometer(void *pvParameters) {

  for(;;) {

    potValue = analogRead(A0);

    delayLED = map(potValue, 0, 1023, 100, 1000);

    digitalWrite(LED_BUILTIN, HIGH);
    vTaskDelay(delayLED / portTICK_PERIOD_MS);

    digitalWrite(LED_BUILTIN, LOW);
    vTaskDelay(delayLED / portTICK_PERIOD_MS);
  }
}
```
<h2>Pertanyaan Praktikum 5B: Komunikasi Data</h2>
<ol>
  <li>Apakah kedua task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!</li>
  <li>Apakah program ini berpotensi mengalami race condition? Jelaskan!</li>
  <li>Modifikasilah program dengan menggunakan sensor DHT sesungguhnya sehingga informasi yang ditampilkan dinamis. Bagaimana hasilnya?</li>
</ol>

<p><b>Jawaban:</b></p>
<ol>
  <li>
  Kedua task pada FreeRTOS berjalan secara bergantian (concurrent), bukan benar-benar bersamaan, karena Arduino Uno hanya memiliki satu inti prosesor. Scheduler pada FreeRTOS mengatur  pembagian waktu eksekusi untuk setiap task sehingga task terlihat berjalan secara bersamaan.

Pada program komunikasi task, task pertama bertugas membaca data sensor DHT22 dan mengirimkannya ke queue menggunakan xQueueSend(). Setelah itu task akan menjalankan vTaskDelay() sehingga status task menjadi blocked sementara. Scheduler kemudian memindahkan eksekusi ke task kedua yang bertugas menerima data dari queue menggunakan xQueueReceive() dan menampilkannya pada Serial Monitor.

Perpindahan eksekusi antar task berlangsung sangat cepat melalui mekanisme context switching sehingga proses pembacaan sensor dan penampilan data dapat berjalan secara teratur tanpa saling mengganggu.
</li>

<li>
Program ini memiliki kemungkinan race condition yang sangat kecil karena komunikasi data antar task dilakukan menggunakan queue pada FreeRTOS. Queue berfungsi sebagai media komunikasi yang aman sehingga data dikirim dan diterima secara terstruktur.

Task pembaca sensor tidak langsung mengakses data milik task display, melainkan mengirim data terlebih dahulu ke queue menggunakan xQueueSend(). Selanjutnya task display mengambil data tersebut menggunakan xQueueReceive(). Mekanisme ini mencegah kedua task mengakses data yang sama secara bersamaan.

Race condition biasanya terjadi jika beberapa task mengakses variabel global yang sama tanpa mekanisme sinkronisasi. Namun pada program ini, penggunaan queue membuat pertukaran data menjadi lebih aman sehingga konflik akses data dapat dihindari.
</li>

<li>
  Pada percobaan ini digunakan sensor DHT22 asli yang dihubungkan ke Arduino Uno untuk membaca data suhu dan kelembapan udara secara real-time. Sistem terdiri dari dua task, yaitu task pembaca sensor dan task display dengan komunikasi data menggunakan queue.

Task pertama bertugas membaca data suhu dan kelembapan dari sensor DHT22 menggunakan library DHT.h. Setelah data berhasil dibaca, nilai suhu dan kelembapan dikirim ke queue menggunakan fungsi xQueueSend(). Selanjutnya task kedua menerima data dari queue menggunakan xQueueReceive() dan menampilkannya pada Serial Monitor.
</li>
</ol>

<p>Code programnya:</p>
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

struct SensorData {
  float temperature;
  float humidity;
};

QueueHandle_t sensorQueue;

void TaskReadSensor(void *pvParameters);
void TaskDisplay(void *pvParameters);

void setup() {

  Serial.begin(9600);

  dht.begin();

  sensorQueue = xQueueCreate(5, sizeof(SensorData));

  xTaskCreate(
    TaskReadSensor,
    "Read Sensor",
    128,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    TaskDisplay,
    "Display Data",
    128,
    NULL,
    1,
    NULL
  );
}

void loop() {
}

// =======================
// TASK MEMBACA SENSOR
// =======================
void TaskReadSensor(void *pvParameters) {

  SensorData data;

  for(;;) {

    data.temperature = dht.readTemperature();
    data.humidity = dht.readHumidity();

    if (!isnan(data.temperature) && !isnan(data.humidity)) {

      xQueueSend(sensorQueue, &data, portMAX_DELAY);
    }

    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

// =======================
// TASK DISPLAY DATA
// =======================
void TaskDisplay(void *pvParameters) {

  SensorData data;

  for(;;) {

    if (xQueueReceive(sensorQueue, &data, portMAX_DELAY) == pdPASS) {

      Serial.println("===== DHT22 SENSOR =====");

      Serial.print("Temperature : ");
      Serial.print(data.temperature);
      Serial.println(" C");

      Serial.print("Humidity    : ");
      Serial.print(data.humidity);
      Serial.println(" %");

      Serial.println("========================");
    }
  }
}
```cpp

```
