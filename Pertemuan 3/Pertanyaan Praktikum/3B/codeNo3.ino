#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Inisialisasi LCD I2C

int potPin = A0;   // Pin potensiometer
int nilaiADC = 0;  // Variabel nilai ADC

void setup() {
  Serial.begin(9600);   // Memulai komunikasi serial
  lcd.init();           // Inisialisasi LCD
  lcd.backlight();      // Menyalakan backlight LCD
}

void loop() {
  nilaiADC = analogRead(potPin); // Membaca nilai ADC (0–1023)

  float volt = nilaiADC * (5.0 / 1023.0); // Konversi ke volt
  int persen = (nilaiADC * 100) / 1023;   // Konversi ke persen

  // Output ke Serial Monitor
  Serial.print("ADC: ");
  Serial.print(nilaiADC);
  Serial.print(" Volt: ");
  Serial.print(volt, 2);
  Serial.print(" V Persen: ");
  Serial.print(persen);
  Serial.println("%");

  // Output ke LCD
  lcd.setCursor(0, 0);
  lcd.print("ADC:");
  lcd.print(nilaiADC);
  lcd.print(" ");
  lcd.print(persen);
  lcd.print("%");

  // Bar level
  lcd.setCursor(0, 1);
  int panjangBar = map(nilaiADC, 0, 1023, 0, 16);
  for (int i = 0; i < panjangBar; i++) {
    lcd.print("#");
  }

  delay(500);
}
