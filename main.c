#include "laundry.h"

int main() {
    Queue antrian;
    Stack riwayat;
    initQueue(&antrian);
    initStack(&riwayat);
    
    loadData(&antrian, &riwayat);
    
    int role = login();
    if (role == 0) return 1;
    
    int pilih;
    do {
        if (role == 1) {
            printf("\n+====================+\n");
            printf("|     MENU ADMIN      |\n");
            printf("+====================+\n");
            printf("| 1. Tambah Laundry   |\n");
            printf("| 2. Proses Laundry   |\n");
            printf("| 3. Lihat Antrian    |\n");
            printf("| 4. Lihat Riwayat    |\n");
            printf("| 5. Daftar Harga     |\n");
            printf("| 6. Sorting Antrian  |\n");
            printf("| 7. Jadwal Ambil     |\n");
            printf("| 8. Urut Berat       |\n");
            printf("| 0. Keluar           |\n");
            printf("+====================+\n");
            printf("Pilih: ");
            
            if (scanf("%d", &pilih) != 1) {
                printf("\nPilihan tidak valid!\n");
                while (getchar() != '\n');
                continue;
            }
            
            switch(pilih) {
               case 1: {
    char nama[50], jenis[10], tanggalMasuk[11], tanggalSelesai[11];
    int j, day, month, year;
    float berat;
    
    printf("\nNama: ");
    scanf(" %[^\n]", nama);
    printf("Berat (kg): ");
    scanf("%f", &berat);
    if (berat < 2) berat = 2;
    printf("Jenis (1.Reguler/2.Express): ");
    scanf("%d", &j);
    if (j != 1 && j != 2) {
        printf("\nPilihan tidak ada!\n");
        break;
    }
    strcpy(jenis, (j == 1) ? "reguler" : "express");
    
    int tanggalValid = 0;
    while (!tanggalValid) {
        printf("Tanggal Masuk (DD/MM/YYYY): ");
        scanf("%s", tanggalMasuk);
        
        if (validasiTanggal(tanggalMasuk)) {
            tanggalValid = 1;
        } else {
            printf("\n❌ TANGGAL TIDAK VALID! Coba lagi.\n");
            printf("   Contoh benar: 15/11/2026 atau 31/12/2026\n\n");
        }
    }
    
    sscanf(tanggalMasuk, "%d/%d/%d", &day, &month, &year);  // buat ambil nilai buat fungsi lain
    
    int tambahHari = (strcmp(jenis, "express") == 0) ? 1 : 3;
    hitungTanggalSelesai(tanggalMasuk, tanggalSelesai, tambahHari);
    
    Laundry* baru = (Laundry*)malloc(sizeof(Laundry));
    baru->id = nextId++;
    strcpy(baru->nama, nama);
    strcpy(baru->jenis, jenis);
    baru->berat = berat;
    baru->harga = hitungHarga(berat, jenis);
    strcpy(baru->tanggalMasuk, tanggalMasuk);
    strcpy(baru->tanggalSelesai, tanggalSelesai);
    baru->next = NULL;
    
    enqueue(&antrian, baru);
    simpanData(&antrian, &riwayat);
    
    printf("\n✅ BERHASIL! ID:%d | Total: Rp%d\n", baru->id, baru->harga);
    printf("   Tanggal Masuk: %s | Selesai: %s\n", tanggalMasuk, tanggalSelesai);
    break;
}
                case 2: {
                    if (isEmptyQueue(&antrian)) {
                        printf("\nAntrian kosong\n");
                        break;
                    }
                    int id;
                    printf("\nMasukkan ID Laundry: ");
                    scanf("%d", &id);
                    
                    Laundry* proses = dequeueByID(&antrian, id);
                    if (proses) {
                        pushStack(&riwayat, proses);
                        simpanData(&antrian, &riwayat);
                        printf("\n✅ Laundry ID %d (%s) selesai\n", proses->id, proses->jenis);
                    } else {
                        printf("\n❌ ID %d tidak ditemukan\n", id);
                    }
                    break;
                }
                case 3:
                    tampilQueue(&antrian);
                    break;
                case 4:
                    tampilStack(&riwayat);
                    break;
                case 5:
                    lihatHarga();
                    break;
                case 6:
                    shellSort(&antrian);
                    simpanData(&antrian, &riwayat);
                    tampilQueue(&antrian);
                    break;
                case 7:
                    tampilJadwal(&antrian, &riwayat);
                    break;
                case 8:
                    tampilUrutBerdasarkanBeratDariQueue(&antrian);
                    break;
                case 0:
                    simpanData(&antrian, &riwayat);
                    freeAllMemory(&antrian, &riwayat);
                    printf("\nTerima kasih\n");
                    break;
                default:
                    printf("\nPilihan tidak ada!\n");
                    break;
            }
        } else {
            printf("\n+====================+\n");
            printf("|     MENU USER       |\n");
            printf("+====================+\n");
            printf("| 1. Lihat Antrian    |\n");
            printf("| 2. Lihat Harga      |\n");
            printf("| 3. Jadwal Ambil     |\n");
            printf("| 0. Keluar           |\n");
            printf("+====================+\n");
            printf("Pilih: ");
            
            if (scanf("%d", &pilih) != 1) {
                printf("\nPilihan tidak valid!\n");
                while (getchar() != '\n');
                continue;
            }
            
            switch(pilih) {
                case 1:
                    tampilQueue(&antrian);
                    break;
                case 2:
                    lihatHarga();
                    break;
                case 3:
                    tampilJadwal(&antrian, &riwayat);
                    break;
                case 0:
                    freeAllMemory(&antrian, &riwayat);
                    printf("\nTerima kasih\n");
                    break;
                default:
                    printf("\nPilihan tidak ada!\n");
                    break;
            }
        }
    } while(pilih != 0);
    
    return 0;
}