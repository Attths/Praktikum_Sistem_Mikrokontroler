[H1H024052_Hafish Athallah_Laprak-Pertemuan-4.pdf](https://github.com/user-attachments/files/27448168/H1H024052_Hafish.Athallah_Laprak-Pertemuan-4.pdf)
<br>
<h2>Pertanyaan Praktikum - Percobaan 1</h2>
<ol>
  <li>Apa fungsi perintah analogRead() pada rangkaian praktikum ini?</li>
  <li>Mengapa diperlukan fungsi map() dalam program tersebut?</li>
  <li>Modifikasi program berikut agar servo hanya bergerak dalam rentang 30° hingga 150°, meskipun potensiometer tetap memiliki rentang ADC 0–1023. Jelaskan program pada file README.md</li>
</ol>

<h2>Jawaban</h2>
<ol>
  <li>Fungsi analogRead() digunakan untuk membaca nilai tegangan analog dari potensiometer yang terhubung ke pin analog Arduino. Nilai yang dibaca kemudian dikonversi oleh ADC menjadi data digital dalam rentang 0–1023, yang merepresentasikan perubahan posisi potensiometer.</li>
  <li>Fungsi map() digunakan untuk mengubah rentang nilai ADC (0–1023) menjadi rentang lain yang sesuai dengan kebutuhan output. Pada praktikum ini, nilai tersebut diubah menjadi sudut servo (misalnya 0–180 derajat), sehingga pergerakan servo dapat mengikuti perubahan input secara proporsional.</li>
  <li>Pada program ini, nilai ADC dari potensiometer tetap dibaca dalam rentang 0–1023 menggunakan analogRead(). Namun, dengan fungsi map(), nilai tersebut diubah menjadi rentang 30° hingga 150°, sehingga servo tidak bergerak penuh dari 0° ke 180°, melainkan hanya pada batas yang telah ditentukan.

Hal ini berguna untuk membatasi pergerakan servo agar lebih sesuai dengan kebutuhan sistem atau untuk menghindari gerakan ekstrem yang tidak diperlukan.</li>
</ol>

<h3>Source Code Nomor 3 </h3>

```cpp
#include <Servo.h>

Servo myservo;

const int potensioPin = A0;
const int servoPin = 9;

int val = 0;
int pos = 0;

void setup() {
  myservo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(potensioPin);

  // Mapping dari 0–1023 menjadi 30–150 derajat
  pos = map(val, 0, 1023, 30, 150);

  myservo.write(pos);

  Serial.print("ADC: ");
  Serial.print(val);
  Serial.print(" | Sudut: ");
  Serial.println(pos);

  delay(100);
}
```
<br>
<h2>Pertanyaan Praktikum - Percobaan 2</h2>
<ol>
  <li>Jelaskan mengapa LED dapat diatur kecerahannya menggunakan fungsi analogWrite()!</li>
  <li>Apa hubungan antara nilai ADC (0–1023) dan nilai PWM (0–255)?</li>
  <li>Modifikasilah program berikut agar LED hanya menyala pada rentang kecerahan sedang, yaitu hanya ketika nilai PWM berada pada rentang 50 sampai 200. Jelaskan program pada file README.md.</li>
</ol>

<h2>Jawaban</h2>
<ol>
  <li>Fungsi analogWrite() menghasilkan sinyal PWM (Pulse Width Modulation), yaitu sinyal digital yang diatur lebar pulsa (duty cycle)-nya.
LED akan terlihat lebih terang atau redup tergantung pada rata-rata tegangan yang diterima. Ketika duty cycle besar (lebih lama ON), LED terlihat lebih terang. Sebaliknya, jika duty cycle kecil (lebih lama OFF), LED terlihat lebih redup.</li>
  <li>Nilai yang dibaca dari analogRead() berada pada rentang 0 hingga 1023 karena menggunakan resolusi 10-bit, sedangkan analogWrite() memiliki rentang 0 hingga 255 dengan resolusi 8-bit. Oleh karena itu, diperlukan fungsi map() untuk mengubah nilai ADC ke rentang PWM. Hubungan antara keduanya bersifat linier, sehingga peningkatan nilai ADC akan menghasilkan peningkatan nilai PWM secara proporsional.</li>
  <li>Pada modifikasi program, nilai ADC dibaca menggunakan analogRead() kemudian dikonversi menjadi nilai PWM dengan fungsi map(). Selanjutnya, diberikan kondisi bahwa LED hanya akan menyala jika nilai PWM berada pada rentang 50 hingga 200. Jika nilai PWM berada di luar rentang tersebut, LED akan dimatikan dengan memberikan nilai output 0. Dengan pembatasan ini, LED hanya menyala pada tingkat kecerahan sedang dan tidak berada pada kondisi terlalu redup maupun terlalu terang.</li>
</ol>

<h3>Source Code Nomor 3</h3>

```cpp
const int potPin = A0;
const int ledPin = 9;

int nilaiADC = 0;
int pwm = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  nilaiADC = analogRead(potPin);

  // Mapping ADC ke PWM
  pwm = map(nilaiADC, 0, 1023, 0, 255);

  // Batasi hanya pada rentang 50–200
  if (pwm >= 50 && pwm <= 200) {
    analogWrite(ledPin, pwm);
  } else {
    analogWrite(ledPin, 0); // LED mati di luar rentang
  }

  Serial.print("ADC: ");
  Serial.print(nilaiADC);
  Serial.print(" | PWM: ");
  Serial.println(pwm);

  delay(100);
}
```
