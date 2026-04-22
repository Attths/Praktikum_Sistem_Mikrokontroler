1. Jelaskan bagaimana cara kerja komunikasi I2C antara Arduino dan LCD pada rangkaian tersebut!
Komunikasi I2C bekerja menggunakan dua jalur, yaitu SDA (data) dan SCL (clock).
Arduino bertindak sebagai master yang mengirimkan data dan sinyal clock, sedangkan LCD sebagai slave yang menerima data.
Setiap perangkat memiliki alamat unik (misalnya 0x27), sehingga Arduino dapat mengirim data ke LCD tertentu.
Data dikirim secara serial melalui SDA dengan sinkronisasi clock dari SCL, kemudian LCD menampilkan data tersebut sesuai perintah yang diberikan.

2. Apakah pin potensiometer harus seperti itu? Jelaskan yang terjadi apabila pin kiri dan pin kanan tertukar!
Konfigurasi pin potensiometer tidak mutlak, tetapi harus mengikuti prinsip pembagi tegangan.
Kaki tengah tetap sebagai output ke pin analog Arduino, sedangkan dua kaki lainnya ke 5V dan GND.
Jika pin kiri dan kanan ditukar, hasil pembacaan tetap bekerja, tetapi arah perubahan nilai akan terbalik (misalnya diputar ke kanan malah nilai mengecil).

3. Modifikasi program dengan menggabungkan antara UART dan I2C (keduanya sebagai output) sehingga:
- Data tidak hanya ditampilkan di LCD tetapi juga di Serial Monitor
- Adapun data yang ditampilkan pada Serial Monitor sesuai dengan table berikut:
<table>
  <tr>
    <td>ADC: 0 </td>
    <td>Volt: 0.00 V</td>
    <td>Persen: 0%</td>
  </tr>
</table>
Tampilan jika potensiometer dalam kondisi diputar paling kiri
- ADC: 0 0% | setCursor(0, 0) dan Bar (level) | setCursor(0, 1)
- Berikan penjelasan disetiap baris kode nya dalam bentuk README.md!

4. Lengkapi table berikut berdasarkan pengamatan pada Serial Monitor
<table>
  <tr>
    <td>ADC</td>
    <td>Volt (V)</td>
    <td>Persen (%)</td>
  </tr>

  <tr>
    <td>1</td>
    <td>0</td>
    <td>0%</td>
  </tr>

  
  <tr>
    <td>21</td>
    <td>0.1</td>
    <td>2%</td>
  </tr>

  
  <tr>
    <td>49</td>
    <td>0.2</td>
    <td>4%</td>
  </tr>

  
  <tr>
    <td>74</td>
    <td>0.4</td>
    <td>7%</td>
  </tr>

  
  <tr>
    <td>96</td>
    <td>0.5</td>
    <td>9%</td>
  </tr>
</table>
