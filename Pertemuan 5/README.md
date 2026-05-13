<h1>Modul Percobaan 5: Real-Time Operating System Multitasking dan Komunikasi Task </h1>
<h2>Pertanyaan Praktikum Percobaan 5A</h2>
<ol>
  <li>Apakah ketiga task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!</li>
  <li>Bagaimana cara menambahkan task keempat? Jelaskan langkahnya!</li>
  <li>Modifikasilah program dengan menambah sensor (misalnya potensiometer), lalu gunakan nilainya untuk mengontrol kecepatan LED!</li>
</ol>

<p><b>Jawaban:</b></p>
<ol>
  <li>Ketiga task pada FreeRTOS tidak benar-benar berjalan secara bersamaan karena Arduino Uno hanya memiliki satu prosesor. <br>
    Task berjalan secara bergantian dengan sangat cepat melalui mekanisme scheduler pada FreeRTOS sehingga terlihat seperti berjalan bersamaan (concurrent).<br>
    Scheduler akan mengatur pembagian waktu eksekusi prosesor ke setiap task berdasarkan prioritas dan delay yang diberikan. <br>
    Ketika suatu task menjalankan fungsi vTaskDelay(), task tersebut akan berada pada kondisi blocked sehingga scheduler memindahkan eksekusi ke task lain yang siap dijalankan. <br>
    Proses perpindahan ini disebut context switching. Dengan mekanisme tersebut, beberapa task seperti kontrol LED dan penampilan data Serial Monitor dapat berjalan secara bergantian tanpa saling mengganggu.
  </li>
  <li>
    Task keempat dapat ditambahkan dengan membuat fungsi task baru kemudian mendaftarkannya menggunakan fungsi xTaskCreate() pada setup(). Langkah-langkahnya sebagai berikut: <br>
    1. Membuat fungsi task baru, misalnya: <br>
    
    ```cpp
    void task4(void *pvParameters) {
    for(;;) {
    Serial.println("Task 4 berjalan");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    }
    ```
  </li>
</ol>
