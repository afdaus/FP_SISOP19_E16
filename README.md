# FP_SISOP19_E16

Penjelasan : 
Dalam program ini, kami menggunakan 7 fungsi yaitu :

1. Ambil_waktu()

Fungsi ini digunakan untuk membaca file crontab.data, lalu mengambil waktu pada config an crontab per barisnya. Misal ada config seperti ini 
`10 * * * * touch /home/bastian/fp/tes.txt`, maka fungsi ini hanya akan mengambil bagian 10 * * * * nya saja. Karena per barisnya kita akan menggunakan struct, maka dalam fungsi ini juga memanggil fungsi isi_struct() untuk declare variabel awal dari suatu struct. Setelah itu memanggil fungsi konversi() untuk merubah 10 * * * * yang awalnya adalah char menjadi integer dengan * akan dianggap sebagai nilai 61. Ada juga fungsi ambil_perintah() dalam fungsi ini untuk mengambil perintah dari crontab tersebut misal “touch /home/bastian/fp/tes.txt” dalam kasus config di atas. Setelah fungsi ini mendapatkan waktu dan perintah, maka thread akan langsung dibuat. Thread ini akan menjalankan fungsi hit_waktu() yang berfungsi untuk mengecek apakah jam di linux sekarang sama dengan jam yang diminta di crontab. Jika sama, maka fungsi hit_waktu() akan memanggil fungsi proses yang akan mengeksekusi perintah dari crontab tersebut. Terakhir, ada fungsi buatwhile() juga dalam funsgi ambil_waktu() ini yang berfungsi untuk mengecek apakah file tersebut dimodify atau tidak, jika dimodify maka thread sebelumnya akan diberhentikan lalu terjadi pemanggilan fungsi ambil_waktu() kembali yang dimana akan membuat thread-thread baru sesuai config an yang telah dimodify.

2. Buatwhile()

Fungsi ini digunakan untuk memanggil fungsi ngecek() yang digunakan untuk mengecek apakah file crontab.data dimodify atau tidak. Pengecekan ini ada dalam while(1) yang dimana akan jalan terus menerus. Jika file crontab.data baru dimodify, maka akan break dari while(1) dan menjalankan fungsi ambil_waktu() kembali dari awal.

3. Konversi()

Fungsi ini hanya digunakan untuk mengubah char menjadi integer.

4. Proses()

Fungsi ini digunakan untuk mengeksekusi perintah pada crontab menggunakan command execl. Dengan menggunakan execl, kita hanya perlu memasukkan perintahnya saja. 

5. Ambil_perintah()

Fungsi ini digunakan untuk mengambil perintah pada crontab.

6. Hit_waktu()

Fungsi ini adalah fungsi yang dijalankan ketika sebuah thread dibuat, fungsi ini akan membandingkan waktu di linux sekarang dengan waktu yang ada pada crontab, jika sama maka fungsi ini akan menjalankan fungsi proses(). Pengecekan dilakukan dalam while(1) dan sleep(1) sehingga pengecekan tidak dapat berhenti dan dilakukan per detik, lalu akan di sleep(60) jika waktu di linux sekarang sudah sesuai dengan waktu pada crontab (karena jika tidak di sleep(60), maka perintah dari crontab tersebut akan jalan per detiknya).

7. Ngecek()

Fungsi ini digunakan untuk mengecek apakah file crontab.data di modify atau tidak dengan mengambil selisih waktu dari waktu sekarang dan waktu kapan terakhir file crontab.data di modify. Jika selisih waktu tersebut kurang dari 2 detik, maka flag akan menyala yang menandakan file tersebut baru saja di modify.

- Dalam menjalankan program, yang dipanggil di main hanya fungsi ambil_waktu(),
