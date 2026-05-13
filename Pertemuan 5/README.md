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
