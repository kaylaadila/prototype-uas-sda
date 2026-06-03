#include "laundry.h"

// Fungsi untuk mencari laundry berdasarkan ID di antrian
Laundry* cariLaundryById(Queue* q, int id) {
    if (isEmptyQueue(q)) return NULL;
    
    Laundry* curr = q->front;
    while (curr) {
        if (curr->id == id) return curr;
        curr = curr->next;
    }
    return NULL;
}

// Fungsi utama edit pesanan
void editPesanan(Queue* q, int id, char* namaBaru, float beratBaru, char* jenisBaru) {
    // Cari data lama
    Laundry* target = cariLaundryById(q, id);
    
    if (!target) {
        printf("\nID %d tidak ditemukan dalam antrian\n", id);
        return;
    }
    
    printf("\n========================================\n");
    printf("         EDIT PESANAN ID: %d\n", id);
    printf("========================================\n");
    printf("Data Lama:\n");
    printf("   Nama : %s\n", target->nama);
    printf("   Berat: %.1f kg\n", target->berat);
    printf("   Jenis: %s\n", target->jenis);
    
    // Update data
    strcpy(target->nama, namaBaru);
    target->berat = beratBaru;
    strcpy(target->jenis, jenisBaru);
    target->harga = hitungHarga(beratBaru, jenisBaru);
    
    // Update tanggal selesai berdasarkan jenis baru
    if (strcmp(jenisBaru, "express") == 0) {
        hitungTanggalSelesai(target->tanggalMasuk, target->tanggalSelesai, 1);
    } else {
        hitungTanggalSelesai(target->tanggalMasuk, target->tanggalSelesai, 3);
    }
    
    printf("\nData Baru:\n");
    printf("   Nama : %s\n", target->nama);
    printf("   Berat: %.1f kg\n", target->berat);
    printf("   Jenis: %s\n", target->jenis);
    printf("\nPESANAN BERHASIL DIEDIT\n");
    printf("   Total biaya baru: Rp %d\n", target->harga);
    printf("   Tanggal selesai baru: %s\n", target->tanggalSelesai);
    printf("========================================\n");
}
