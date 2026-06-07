# prototype-uas-sda
ini prototype sblm final commit ke repo baru

# Sistem Manajemen Laundry Berbasis Queue dan Stack

## Deskripsi Sistem

Sistem Manajemen Laundry adalah aplikasi berbasis bahasa C yang digunakan untuk mengelola proses pencatatan pesanan laundry, pemantauan antrian, penyelesaian pesanan, serta penyimpanan riwayat transaksi. Sistem ini dirancang untuk membantu usaha laundry dalam mengorganisasi pesanan pelanggan secara lebih terstruktur dibandingkan pencatatan manual. Permasalahan yang diselesaikan meliputi pengelolaan antrian pelanggan, pencarian jadwal pengambilan, pencatatan riwayat laundry yang telah selesai, dan pengurutan data berdasarkan berbagai kriteria. Secara teknis, proyek ini menarik karena menggabungkan beberapa struktur data dan algoritma klasik seperti Queue, Stack, Linked List, Shell Sort, Merge Sort, dan Quick Sort dalam satu sistem yang terintegrasi.

---

## Struktur Data yang Digunakan

|  Struktur Data     |              Digunakan Untuk                   |
|--------------------|------------------------------------------------|
| Singly Linked List | Menyimpan data pesanan laundry secara dinamis  |
| Queue (FIFO)       | Mengelola antrian laundry yang sedang diproses |
| Stack (LIFO)       | Menyimpan riwayat laundry yang telah selesai   |
| Array of Pointer   | Menampung data sementara saat proses sorting   |

---

## Algoritma yang Digunakan

| Algoritma    | Kompleksitas  |                                             Digunakan Untuk                                      |
|--------------|---------------|--------------------------------------------------------------------------------------------------|
| Shell Sort   | O(n^1.25) - O(n^1.5)    | Mereorganisasi antrean aktif berdasarkantingkat urgensi layanan |
| Merge Sort   | O(n log n)    | menyajikan visualisasi daftar pesanan secara menurun berdasarkan bobot cucian yang paling berat                            |
| Quick Sort   | O(n log n)    | Mengurutkan jadwal pengambilan berdasarkan tanggal selesai tercepat                              |

---


---


---

## Cara Kompilasi

Pastikan compiler GCC telah terpasang.

### Linux / macOS

```bash
gcc *.c -o laundry
```

### Windows (MinGW)

```bash
gcc *.c -o laundry.exe
```

---

## Cara Menjalankan Program

### Linux / macOS

```bash
./laundry
```

### Windows

```bash
laundry.exe
```

Sebelum menjalankan program, pastikan file berikut tersedia:

```text
akun.txt
```

Contoh isi:

```text
admin admin123
user user123
```

---

## Tampilan Menu Program

### Login

```text
==============================
      KELOLA LAUNDRY
==============================
Username:
Password:
```

### Menu Admin

```text
+====================+
|     MENU ADMIN      |
+====================+
| 1. Tambah Laundry   |
| 2. Tandai Selesai   |
| 3. Edit Pesanan     |
| 4. Hapus Pesanan    |
| 5. Lihat Antrian    |
| 6. Lihat Riwayat    |
| 7. Daftar Harga     |
| 8. Antrian by Jenis |
| 9. Antrian by Berat |
|10. Jadwal Ambil     |
| 0. Keluar           |
+====================+
```

### Menu User

```text
+====================+
|     MENU USER       |
+====================+
| 1. Lihat Antrian    |
| 2. Lihat Harga      |
| 3. Jadwal Ambil     |
| 0. Keluar           |
+====================+
```

---

## Penyimpanan Data

Data laundry disimpan secara permanen menggunakan file:

```text
data_laundry.txt
```

Format penyimpanan:

```text
Q|ID|Nama|Jenis|Berat|Harga|TanggalMasuk|TanggalSelesai
S|ID|Nama|Jenis|Berat|Harga|TanggalMasuk|TanggalSelesai
```

Keterangan:

* `Q` = Data masih berada dalam antrian.
* `S` = Data sudah selesai dan berada dalam riwayat.

---

|       Nama     |            Peran           |
|----------------|----------------------------|
| Abrar Muda | Implementasi file I/O, login, simpan & load data, README |
| Arinal Haq  | Implementasi sorting algorithm (Shell, Merge, Quick), fitur hapus pesanan, analisis dan pemilihan struktur data, laporan |
| Kayla Adila Farija Atika | Implementasi struktur data (Array, Queue, Stack) , fitur edit pesanan, menu utama, merancang seluruh tampilan CLI program  |
| Syella Zikra Arifa | Implementasi validasi input, validasi tanggal, dokumentasi|

---

## License

MIT License

Copyright (c) 2026 Kelompok 6 - Data Structures and Algorithms Lab

Permission is hereby granted, free of charge, to any person obtaining a copy of this software to use, modify, and distribute it for educational purposes, provided that the original authors are credited.
