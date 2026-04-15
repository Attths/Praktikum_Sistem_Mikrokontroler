<h1>Pertanyaan Praktikum</h1>
1. Uraikan hasil tugas pada praktikum yang telah dilakukan pada setiap percobaan!
a. Percobaan 2A: Seven Segment
- Arduino Uno berhasil dikonfigurasi untuk mengendalikan seven segment melalui pin GPIO.
- Seven segment mampu menampilkan angka dan karakter heksadesimal dari 0 hingga F secara berurutan.
- Program berjalan secara kontinu menggunakan struktur perulangan (loop).
- Setiap segmen LED menyala sesuai dengan pola yang telah diprogram tanpa error.
- Percobaan ini membuktikan bahwa GPIO dapat digunakan sebagai output digital.

b. Percobaan 2B: Kontrol Counter dengan Push Button
- Push button berhasil digunakan sebagai input digital untuk mengontrol tampilan.
- Seven segment menampilkan nilai counter berdasarkan input dari tombol.
- Mode INPUT_PULLUP menghasilkan pembacaan sinyal yang stabil dan menghindari kondisi floating.
- Sistem counter dapat melakukan penambahan dan pengurangan nilai secara akurat.
- Percobaan ini menunjukkan integrasi antara perangkat input dan output pada mikrokontroler.

2. Bagaimana prinsip kerja dari Seven Segment Display dalam menampilkan angka dan
karakter?
Seven segment display terdiri dari tujuh LED yang diberi label a hingga g, serta satu titik desimal (dp). Setiap LED menyala dalam kombinasi tertentu untuk membentuk angka dan karakter.

Prinsip Kerja:
- Setiap segmen dikendalikan oleh sinyal digital dari mikrokontroler.
- Logika HIGH atau LOW menentukan apakah segmen menyala atau mati.
- Kombinasi penyalaan segmen membentuk angka 0–9 dan huruf A–F.

Terdapat dua jenis konfigurasi:
- Common Cathode: Menyala saat diberi logika HIGH.
- Common Anode: Menyala saat diberi logika LOW.
Dalam praktikum ini digunakan untuk menampilkan bilangan heksadesimal melalui pengendalian GPIO Arduino.

3. Jelaskan bagaimana sistem counter bekerja pada program tersebut!
Sistem counter bekerja dengan menampilkan nilai numerik yang bertambah atau berkurang berdasarkan logika program dan input pengguna.

Mekanisme Kerja:
1. Inisialisasi
- Pin seven segment diatur sebagai OUTPUT.
- Pin push button diatur sebagai INPUT_PULLUP.
2. Proses Penghitungan
- Variabel count menyimpan nilai counter.
- Pada percobaan otomatis, nilai bertambah menggunakan perulangan for.
- Pada percobaan dengan tombol:
  - Tombol ditekan → nilai bertambah (increment).
  - Tombol lain ditekan → nilai berkurang (decrement).
3. Pembatasan Nilai
- Nilai dibatasi antara 0 hingga 15 (heksadesimal).
- Jika melebihi batas, nilai kembali ke awal (overflow dan underflow).
4. Output ke Seven Segment
- Nilai counter diterjemahkan ke dalam pola biner.
- Arduino mengirimkan sinyal melalui fungsi digitalWrite() untuk menampilkan angka yang sesuai.
5. Perulangan Berkelanjutan
- Program berjalan terus menerus dalam fungsi loop().
