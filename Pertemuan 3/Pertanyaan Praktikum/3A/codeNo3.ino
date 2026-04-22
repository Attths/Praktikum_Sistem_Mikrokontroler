int ledPin = 8;        // Menentukan pin LED
char data;             // Variabel untuk menyimpan data dari serial
bool blinkMode = false; // Status mode blink

void setup() {
  pinMode(ledPin, OUTPUT);     // Mengatur pin LED sebagai output
  Serial.begin(9600);          // Memulai komunikasi serial dengan baud rate 9600
}

void loop() {
  if (Serial.available() > 0) {   // Mengecek apakah ada data masuk
    data = Serial.read();         // Membaca data dari serial

    if (data == '1') {
      digitalWrite(ledPin, HIGH); // LED menyala
      blinkMode = false;          // Nonaktifkan mode blink
    } 
    else if (data == '0') {
      digitalWrite(ledPin, LOW);  // LED mati
      blinkMode = false;          // Nonaktifkan mode blink
    } 
    else if (data == '2') {
      blinkMode = true;           // Aktifkan mode blink
    } 
    else {
      Serial.println("Input tidak valid"); // Pesan error
    }
  }

  if (blinkMode) {
    digitalWrite(ledPin, HIGH); // LED nyala
    delay(500);                 // Delay 500 ms
    digitalWrite(ledPin, LOW);  // LED mati
    delay(500);                 // Delay 500 ms
  }
}
