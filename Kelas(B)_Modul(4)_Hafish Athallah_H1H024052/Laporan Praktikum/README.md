[H1H024052_Hafish Athallah_Laprak-Pertemuan-4.pdf](https://github.com/user-attachments/files/27448168/H1H024052_Hafish.Athallah_Laprak-Pertemuan-4.pdf)
<br>
<h2>Pertanyaan Praktikum - Percobaan 1</h2>
<ol>
  <li>Apa fungsi perintah analogRead() pada rangkaian praktikum ini?</li>
  <li>Mengapa diperlukan fungsi map() dalam program tersebut?</li>
  <li>Modifikasi program berikut agar servo hanya bergerak dalam rentang 30° hingga 150°, meskipun potensiometer tetap memiliki rentang ADC 0–1023. Jelaskan program pada file README.md</li>
</ol>

<h3>Jawaban</h3>
<ol>
  <li>Fungsi analogRead() digunakan untuk membaca nilai tegangan analog dari potensiometer yang terhubung ke pin analog Arduino. Nilai yang dibaca kemudian dikonversi oleh ADC menjadi data digital dalam rentang 0–1023, yang merepresentasikan perubahan posisi potensiometer.</li>
  <li>Fungsi map() digunakan untuk mengubah rentang nilai ADC (0–1023) menjadi rentang lain yang sesuai dengan kebutuhan output. Pada praktikum ini, nilai tersebut diubah menjadi sudut servo (misalnya 0–180 derajat), sehingga pergerakan servo dapat mengikuti perubahan input secara proporsional.</li>
  <li>Pada program ini, nilai ADC dari potensiometer tetap dibaca dalam rentang 0–1023 menggunakan analogRead(). Namun, dengan fungsi map(), nilai tersebut diubah menjadi rentang 30° hingga 150°, sehingga servo tidak bergerak penuh dari 0° ke 180°, melainkan hanya pada batas yang telah ditentukan.

Hal ini berguna untuk membatasi pergerakan servo agar lebih sesuai dengan kebutuhan sistem atau untuk menghindari gerakan ekstrem yang tidak diperlukan.</li>
</ol>

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
