<h1>Source Code Percobaan 1</h1>
<h2>Penjelasan</h2>
<p>Program ini digunakan untuk mengontrol pergerakan motor servo berdasarkan input dari potensiometer. Nilai tegangan analog yang dibaca dari 
  potensiometer melalui pin A0 akan dikonversi menjadi data digital menggunakan analogRead(). Nilai tersebut kemudian dipetakan menggunakan fungsi map() 
  dari rentang 0–1023 menjadi sudut 0–180 derajat. Hasil pemetaan ini digunakan untuk menggerakkan servo melalui fungsi write(), sehingga posisi servo 
  mengikuti perubahan putaran potensiometer. Selain itu, nilai ADC dan sudut servo ditampilkan pada Serial Monitor untuk memudahkan pengamatan, dengan 
  tambahan delay kecil agar pergerakan servo lebih stabil.
</p>

```cpp
#include <Servo.h> // library untuk servo motor

Servo myservo; // membuat objek servo

// ===================== PIN SETUP =====================
// Berdasarkan gambar: Potensio ke A0, Servo ke Pin 9
const int potensioPin = A0;   // Pin analog input A0
const int servoPin = 9;      // Pin digital PWM 9

// ===================== VARIABEL =====================
int pos = 0; // Variabel sudut (0-180)
int val = 0; // Variabel pembacaan ADC (0-1023)

void setup() {
  // Hubungkan servo ke pin 9
  myservo.attach(servoPin); 

  // Aktifkan komunikasi serial untuk monitoring
  Serial.begin(9600); 
}

void loop() {
  // ===================== PEMBACAAN ADC =====================
  // Baca nilai dari potensiometer
  val = analogRead(potensioPin); 

  // ===================== KONVERSI DATA =====================
  // Mapping nilai ADC (0-1023) ke sudut servo (0-180)
  pos = map(val, 0, 1023, 0, 180);  

  // ===================== OUTPUT SERVO =====================
  // Gerakkan servo sesuai hasil mapping
  myservo.write(pos); 

  // ===================== MONITORING DATA =====================
  Serial.print("ADC Potensio: ");
  Serial.print(val); 

  Serial.print(" | Sudut Servo: ");
  Serial.println(pos); 

  // ===================== STABILISASI =====================
  delay(10); // Delay standar untuk pergerakan servo yang halus
}
```

<h1>Source Code Percobaan 2</h1>
<h2>Penjelasan</h2>
<p>Program ini digunakan untuk mengatur kecerahan LED berdasarkan input dari potensiometer. Nilai analog dari potensiometer dibaca menggunakan 
  analogRead() dalam rentang 0–1023, kemudian dikonversi menjadi nilai PWM (0–255) menggunakan fungsi map(). Nilai PWM tersebut dikirim ke LED 
  melalui analogWrite(), sehingga tingkat kecerahan LED berubah secara bertahap sesuai dengan putaran potensiometer. Selain itu, nilai ADC dan 
  PWM ditampilkan pada Serial Monitor untuk memudahkan pengamatan, dengan tambahan delay agar pembacaan data lebih stabil dan tidak terlalu cepat.
</p>

```cpp
#include <Arduino.h> // library dasar Arduino (tidak wajib diubah)

// ===================== PIN SETUP =====================
// Berdasarkan gambar: Potensio ke A0, LED ke Pin 9
const int potPin = A0;   // Pin analog A0 untuk potensiometer
const int ledPin = 9;    // Pin digital 9 (PWM) untuk LED

// ===================== VARIABEL =====================
int nilaiADC = 0;  // Variabel penyimpan nilai bacaan analog
int pwm = 0;       // Variabel penyimpan nilai hasil konversi PWM

void setup() {

  // ===================== OUTPUT SETUP =====================
  // Atur pin LED sebagai output
  pinMode(ledPin, OUTPUT);

  // ===================== SERIAL MONITOR =====================
  // Aktifkan komunikasi serial dengan baud rate standar
  Serial.begin(9600); 
}

void loop() {

  // ===================== PEMBACAAN SENSOR =====================
  // Baca nilai analog dari potensiometer (rentang 0–1023)
  nilaiADC = analogRead(potPin); 

  // ===================== PEMROSESAN DATA (SCALING) =====================
  // Ubah nilai ADC (0–1023) menjadi nilai PWM (0–255) agar LED bisa redup/terang
  pwm = map(nilaiADC, 0, 1023, 0, 255);

  // ===================== OUTPUT PWM =====================
  // Kirim sinyal PWM ke LED
  analogWrite(ledPin, pwm); 

  // ===================== MONITORING DATA =====================
  // Tampilkan data ke Serial Monitor untuk memantau perubahan
  Serial.print("ADC: ");
  Serial.print(nilaiADC); 

  Serial.print(" | PWM: ");
  Serial.println(pwm); 

  // ===================== STABILISASI SISTEM =====================
  // Delay agar pembacaan Serial Monitor tidak terlalu cepat
  delay(50); 
}
```
