# prototype-uas-sda
ini prototype sblm final commit ke repo baru

# Sistem Manajemen Laundry Berbasis Queue dan Stack

## Deskripsi Sistem

Sistem Manajemen Laundry adalah aplikasi berbasis bahasa C yang digunakan untuk mengelola proses pencatatan pesanan laundry, pemantauan antrian, penyelesaian pesanan, serta penyimpanan riwayat transaksi. Sistem ini dirancang untuk membantu usaha laundry dalam mengorganisasi pesanan pelanggan secara lebih terstruktur dibandingkan pencatatan manual. Permasalahan yang diselesaikan meliputi pengelolaan antrian pelanggan, pencarian jadwal pengambilan, pencatatan riwayat laundry yang telah selesai, dan pengurutan data berdasarkan berbagai kriteria. Secara teknis, proyek ini menarik karena menggabungkan beberapa struktur data dan algoritma klasik seperti Queue, Stack, Linked List, Shell Sort, Merge Sort, dan Quick Sort dalam satu sistem yang terintegrasi.

---

## Struktur Data yang Digunakan

| Struktur Data      | Implementasi         | Fungsi                                                |
| ------------------ | -------------------- | ----------------------------------------------------- |
| Singly Linked List | `struct Laundry`     | Menyimpan data setiap pesanan laundry                 |
| Queue              | `Queue`              | Mengelola antrian laundry yang sedang diproses (FIFO) |
| Stack              | `Stack`              | Menyimpan riwayat laundry yang telah selesai (LIFO)   |
| Array of Pointer   | `Laundry* data[100]` | Menyimpan data sementara untuk proses sorting         |

---

## Algoritma yang Digunakan

| Algoritma         | Lokasi Implementasi      | Tujuan                                                                         |
| ----------------- | ------------------------ | ------------------------------------------------------------------------------ |
| Shell Sort        | `shellSort()`            | Mengurutkan antrian berdasarkan prioritas jenis laundry (Express lebih dahulu) |
| Merge Sort        | `mergeSortByWeight()`    | Mengurutkan data berdasarkan berat laundry dari terbesar ke terkecil           |
| Quick Sort        | `quickSortByDate()`      | Mengurutkan jadwal pengambilan berdasarkan tanggal selesai tercepat            |
| Sequential Search | Edit dan Hapus Pesanan   | Mencari data laundry berdasarkan ID                                            |
| Date Validation   | `validasiTanggal()`      | Memastikan format dan nilai tanggal valid                                      |
| Date Calculation  | `hitungTanggalSelesai()` | Menghitung tanggal selesai laundry secara otomatis                             |

---

## Fitur Utama

### Admin

* Login Admin
* Menambah pesanan laundry
* Menandai laundry selesai
* Mengedit data pesanan
* Menghapus pesanan
* Melihat antrian laundry
* Melihat riwayat laundry
* Melihat daftar harga
* Mengurutkan antrian berdasarkan jenis layanan
* Mengurutkan antrian berdasarkan berat laundry
* Melihat jadwal pengambilan laundry
* Penyimpanan data otomatis ke file

### User

* Login User
* Melihat antrian laundry
* Melihat daftar harga
* Melihat jadwal pengambilan

---

## Struktur File

```text
.
├── main.c
├── laundry.h
├── queue.c
├── stack.c
├── sorting.c
├── utility.c
├── auth_file.c
├── akun.txt
├── data_laundry.txt
└── README.md
```

> Nama file implementasi dapat disesuaikan dengan struktur repository yang digunakan.

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

## Kontributor

Proyek ini dikembangkan sebagai tugas akademik mata kuliah Struktur Data dan Algoritma menggunakan bahasa pemrograman C.

---

## License

MIT License

Copyright (c) 2025

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files, to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software.
