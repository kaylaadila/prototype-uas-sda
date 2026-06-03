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
            printf("| 2. Tandai Selesai   |\n");
            printf("| 3. Edit Pesanan     |\n");
            printf("| 4. Lihat Antrian    |\n");
            printf("| 5. Lihat Riwayat    |\n");
            printf("| 6. Daftar Harga     |\n");
            printf("| 7. Antrian by Jenis |\n");
            printf("| 8. Sorting by Berat |\n");
            printf("| 9. Jadwal Ambil     |\n");
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
                            printf("\nTANGGAL TIDAK VALID! Coba lagi.\n");
                            printf("   Contoh benar: 15/11/2026 atau 31/12/2026\n\n");
                        }
                    }
                    
                    sscanf(tanggalMasuk, "%d/%d/%d", &day, &month, &year);
                    
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
                    
                    printf("\nBERHASIL! ID:%d | Total: Rp%d\n", baru->id, baru->harga);
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
                        printf("\nLaundry ID %d (%s) selesai\n", proses->id, proses->jenis);
                    } else {
                        printf("\nID %d tidak ditemukan\n", id);
                    }
                    break;
                }
                case 3: {
                    if (isEmptyQueue(&antrian)) {
                        printf("\nAntrian kosong\n");
                        break;
                    }
                    
                    printf("\n=== DAFTAR ANTRIAN ===\n");
                    Laundry* curr = antrian.front;
                    int no = 1;
                    while (curr) {
                        printf("%d. ID:%d | %s | %s | %.1fkg | Rp%d\n", 
                               no++, curr->id, curr->nama, curr->jenis, curr->berat, curr->harga);
                        curr = curr->next;
                    }
                    
                    int id;
                    char namaBaru[50], jenisBaru[10];
                    int j;
                    float beratBaru;
                    
                    printf("\nMasukkan ID Laundry yang akan diedit: ");
                    scanf("%d", &id);
                    
                    Laundry* cek = cariLaundryById(&antrian, id);
                    if (!cek) {
                        printf("\nID %d tidak ditemukan dalam antrian\n", id);
                        break;
                    }
                    
                    printf("\n=== EDIT PESANAN ===\n");
                    printf("Nama baru: ");
                    scanf(" %[^\n]", namaBaru);
                    printf("Berat baru (kg): ");
                    scanf("%f", &beratBaru);
                    if (beratBaru < 2) {
                        printf("Minimal 2 kg, ditetapkan menjadi 2 kg\n");
                        beratBaru = 2;
                    }
                    printf("Jenis baru (1.Reguler/2.Express): ");
                    scanf("%d", &j);
                    if (j != 1 && j != 2) {
                        printf("Pilihan tidak ada\n");
                        break;
                    }
                    strcpy(jenisBaru, (j == 1) ? "reguler" : "express");
                    
                    editPesanan(&antrian, id, namaBaru, beratBaru, jenisBaru);
                    simpanData(&antrian, &riwayat);
                    break;
                }
                case 4: {
                    tampilQueue(&antrian);
                    break;
                }
                case 5: {
                    tampilStack(&riwayat);
                    break;
                }
                case 6: {
                    lihatHarga();
                    break;
                }
                case 7: {
                    if (isEmptyQueue(&antrian)) {
                        printf("\nAntrian kosong\n");
                        break;
                    }
                    shellSort(&antrian);
                    simpanData(&antrian, &riwayat);
                    tampilQueue(&antrian);
                    break;
                }
                case 8: {
                    tampilUrutBerdasarkanBeratDariQueue(&antrian);
                    break;
                }
                case 9: {
                    tampilJadwal(&antrian, &riwayat);
                    break;
                }
                case 0: {
                    simpanData(&antrian, &riwayat);
                    freeAllMemory(&antrian, &riwayat);
                    printf("\nTerima kasih\n");
                    break;
                }
                default: {
                    printf("\nPilihan tidak ada!\n");
                    break;
                }
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
                case 1: {
                    tampilQueue(&antrian);
                    break;
                }
                case 2: {
                    lihatHarga();
                    break;
                }
                case 3: {
                    tampilJadwal(&antrian, &riwayat);
                    break;
                }
                case 0: {
                    freeAllMemory(&antrian, &riwayat);
                    printf("\nTerima kasih\n");
                    break;
                }
                default: {
                    printf("\nPilihan tidak ada!\n");
                    break;
                }
            }
        }
    } while(pilih != 0);
    
    return 0;
}
