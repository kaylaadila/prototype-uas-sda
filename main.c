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
            printf("| 8. Antrian by Berat |\n");
            printf("| 9. Jadwal Ambil     |\n");
            printf("| 0. Keluar           |\n");
            printf("+====================+\n");
            printf("Pilih: ");
            
            pilih = bacaInt("");
            
            if (pilih == 1) {
                char nama[50], jenis[10], tglMasuk[11], tglSelesai[11];
                float berat;
                int j;
                
                bacaString("Nama: ", nama, MAX_NAMA);
                berat = bacaFloat("Berat (kg): ");
                if (berat < 2) berat = 2;
                j = bacaInt("Jenis (1.Reguler/2.Express): ");
                if (j == 1) strcpy(jenis, "reguler");
                else strcpy(jenis, "express");
                
                int valid = 0;
                while (!valid) {
                    bacaString("Tanggal Masuk (DD/MM/YYYY): ", tglMasuk, 11);
                    if (validasiTanggal(tglMasuk)) valid = 1;
                }
                
                int tambahHari = (strcmp(jenis, "express") == 0) ? 1 : 3;
                hitungTanggalSelesai(tglMasuk, tglSelesai, tambahHari);
                
                Laundry* baru = (Laundry*)malloc(sizeof(Laundry));
                baru->id = nextId++;
                strcpy(baru->nama, nama);
                strcpy(baru->jenis, jenis);
                baru->berat = berat;
                baru->harga = hitungHarga(berat, jenis);
                strcpy(baru->tanggalMasuk, tglMasuk);
                strcpy(baru->tanggalSelesai, tglSelesai);
                baru->next = NULL;
                
                enqueue(&antrian, baru);
                simpanData(&antrian, &riwayat);
                printf("\nBERHASIL! ID:%d | Total: Rp%d\n", baru->id, baru->harga);
            }
            else if (pilih == 2) {
                if (isEmptyQueue(&antrian)) {
                    printf("\nAntrian kosong\n");
                } else {
                    int id = bacaInt("Masukkan ID Laundry: ");
                    Laundry* proses = dequeueByID(&antrian, id);
                    if (proses) {
                        pushStack(&riwayat, proses);
                        simpanData(&antrian, &riwayat);
                        printf("\nLaundry ID %d selesai\n", id);
                    } else {
                        printf("\nID %d tidak ditemukan\n", id);
                    }
                }
            }
            else if (pilih == 3) {
                if (isEmptyQueue(&antrian)) {
                    printf("\nAntrian kosong\n");
                } else {
                    printf("\n=== DAFTAR ANTRIAN ===\n");
                    Laundry* curr = antrian.front;
                    int no = 1;
                    while (curr) {
                        printf("%d. ID:%d | %s | %s | %.1fkg\n", no++, curr->id, curr->nama, curr->jenis, curr->berat);
                        curr = curr->next;
                    }
                    
                    int id = bacaInt("\nMasukkan ID yang akan diedit: ");
                    
                    Laundry* target = antrian.front;
                    while (target && target->id != id) target = target->next;
                    
                    if (!target) {
                        printf("\nID %d tidak ditemukan\n", id);
                    } else {
                        char namaBaru[50], jenisBaru[10];
                        float beratBaru;
                        int j;
                        
                        printf("\nDATA LAMA: %s | %.1f kg | %s\n", target->nama, target->berat, target->jenis);
                        bacaString("Nama baru: ", namaBaru, MAX_NAMA);
                        beratBaru = bacaFloat("Berat baru (kg): ");
                        if (beratBaru < 2) beratBaru = 2;
                        j = bacaInt("Jenis baru (1.Reguler/2.Express): ");
                        if (j == 1) strcpy(jenisBaru, "reguler");
                        else strcpy(jenisBaru, "express");
                        
                        strcpy(target->nama, namaBaru);
                        target->berat = beratBaru;
                        strcpy(target->jenis, jenisBaru);
                        target->harga = hitungHarga(beratBaru, jenisBaru);
                        
                        int tambahHari = (strcmp(jenisBaru, "express") == 0) ? 1 : 3;
                        hitungTanggalSelesai(target->tanggalMasuk, target->tanggalSelesai, tambahHari);
                        
                        simpanData(&antrian, &riwayat);
                        printf("\nDATA BERHASIL DIUPDATE!\n");
                    }
                }
            }
            else if (pilih == 4) {
                tampilQueue(&antrian);
            }
            else if (pilih == 5) {
                tampilStack(&riwayat);
            }
            else if (pilih == 6) {
                lihatHarga();
            }
            else if (pilih == 7) {
                if (isEmptyQueue(&antrian)) {
                    printf("\nAntrian kosong\n");
                } else {
                    shellSort(&antrian);
                    simpanData(&antrian, &riwayat);
                    tampilQueue(&antrian);
                }
            }
            else if (pilih == 8) {
                tampilUrutBerdasarkanBerat(&antrian);
            }
            else if (pilih == 9) {
                tampilJadwal(&antrian, &riwayat);
            }
            else if (pilih == 0) {
                simpanData(&antrian, &riwayat);
                freeAllMemory(&antrian, &riwayat);
                printf("\nTerima kasih\n");
            }
            else {
                printf("\nPilihan tidak ada!\n");
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
            
            pilih = bacaInt("");
            
            if (pilih == 1) {
                tampilQueue(&antrian);
            } else if (pilih == 2) {
                lihatHarga();
            } else if (pilih == 3) {
                tampilJadwal(&antrian, &riwayat);
            } else if (pilih == 0) {
                freeAllMemory(&antrian, &riwayat);
                printf("\nTerima kasih\n");
            } else {
                printf("\nPilihan tidak ada!\n");
            }
        }
    } while(pilih != 0);
    
    return 0;
}