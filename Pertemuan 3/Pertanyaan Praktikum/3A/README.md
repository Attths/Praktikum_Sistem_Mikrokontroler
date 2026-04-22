Pertanyaan Praktikum 3A
1. Jelaskan proses dari input keyboard hingga LED menyala/mati! <br>
Input dari keyboard dikirim melalui Serial Monitor ke Arduino menggunakan komunikasi UART.
Arduino kemudian mengecek ketersediaan data dengan Serial.available(), lalu membaca data menggunakan Serial.read().
Jika input bernilai ‘1’, Arduino memberikan logika HIGH sehingga LED menyala. Jika ‘0’, LED mati. Jika input tidak sesuai, maka akan ditampilkan pesan kesalahan. <br>
   
2. Mengapa digunakan Serial.available() sebelum membaca data? Apa yang terjadi jika baris tersebut dihilangkan? <br>
Serial.available() digunakan untuk memastikan bahwa data sudah tersedia sebelum dibaca. Hal ini mencegah pembacaan data kosong.
Jika tidak digunakan, Serial.read() tetap berjalan meskipun tidak ada data, sehingga bisa menghasilkan nilai tidak valid dan
menyebabkan program tidak berjalan dengan benar. <br>
   
3. Modifikasi program agar LED berkedip (blink) ketika menerima input '2' dengan kondisi jika ‘2’ aktif maka LED akan
   terus berkedip sampai perintah selanjutnya diberikan dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md! <br>

4. Tentukan apakah menggunakan delay() atau milis()! Jelaskan pengaruhnya terhadap sistem <br>
Pada percobaan ini digunakan delay() karena mudah diterapkan untuk membuat efek berkedip. Namun, delay() bersifat blocking
sehingga Arduino tidak dapat memproses input lain selama delay berlangsung. Sebaliknya, millis() bersifat non-blocking sehingga
sistem tetap responsif dan lebih cocok untuk program yang lebih kompleks.
