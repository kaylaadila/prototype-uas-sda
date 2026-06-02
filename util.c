#include "laundry.h"

void hitungTanggalSelesai(char *tglMasuk, char *tglSelesai, int tambahHari) {
    int day, month, year;
    sscanf(tglMasuk, "%d/%d/%d", &day, &month, &year);
    
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[1] = 29;
    } else {
        daysInMonth[1] = 28;
    }
    
    day += tambahHari;
    
    while (day > daysInMonth[month - 1]) {
        day -= daysInMonth[month - 1];
        month++;
        if (month > 12) {
            month = 1;
            year++;
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                daysInMonth[1] = 29;
            } else {
                daysInMonth[1] = 28;
            }
        }
    }
    
    sprintf(tglSelesai, "%02d/%02d/%04d", day, month, year);
}

int validasiTanggal(char *tgl) {
    int day, month, year;
    int jumlah = sscanf(tgl, "%d/%d/%d", &day, &month, &year);
    
    // Harus 3 angka (DD/MM/YYYY)
    if (jumlah != 3) {
        printf("    Format salah! Gunakan DD/MM/YYYY (contoh: 15/11/2026)\n");
        return 0;
    }
    
    if (year < 1900 || year > 2100) {
        printf("    Tahun harus antara 1900-2100\n");
        return 0;
    }
    if (month < 1 || month > 12) {
        printf("    Bulan harus antara 01-12\n");
        return 0;
    }
    if (day < 1) {
        printf("    Hari minimal 1\n");
        return 0;
    }
    
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[1] = 29;
    }
    
    if (day > daysInMonth[month - 1]) {
        printf("   ❌ Bulan %d hanya memiliki %d hari\n", month, daysInMonth[month - 1]);
        return 0;
    }
    
    return 1;
}

void tampilJadwal(Queue* q, Stack* s) {
    printf("\n=== JADWAL PENGAMBILAN ===\n");
    
    Laundry* belumSelesai[100];
    int count = 0;
    Laundry* curr = q->front;
    while (curr) {
        belumSelesai[count++] = curr;
        curr = curr->next;
    }
    
    if (count > 1) {
        quickSortByDate(belumSelesai, 0, count - 1);
    }
    
    printf("--- BELUM SELESAI (diurutkan dari paling cepat selesai) ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d. ID:%d | %s | %s | Masuk: %s | Selesai: %s\n", 
               i+1, 
               belumSelesai[i]->id, 
               belumSelesai[i]->nama, 
               belumSelesai[i]->jenis,
               belumSelesai[i]->tanggalMasuk,
               belumSelesai[i]->tanggalSelesai);
    }
    
    if (!isEmptyStack(s)) {
        printf("\n--- SUDAH SELESAI ---\n");
        int no = 1;
        for (int i = s->top; i >= 0; i--) {
            printf("%d. ID:%d | %s | %s | SUDAH SIAP\n", 
                   no++, s->data[i]->id, s->data[i]->nama, s->data[i]->jenis);
        }
    }
    
    if (isEmptyQueue(q) && isEmptyStack(s)) {
        printf("Tidak ada data\n");
    }
}

void freeAllMemory(Queue* q, Stack* s) {
    int totalFreed = 0;
    
    Laundry* curr = q->front;
    while (curr) {
        Laundry* next = curr->next;
        free(curr);
        curr = next;
        totalFreed++;
    }
    
    for (int i = 0; i <= s->top; i++) {
        free(s->data[i]);
        totalFreed++;
    }
    
    q->front = q->rear = NULL;
    q->count = 0;
    s->top = -1;
    
    printf("\n[INFO] Memori dibebaskan: %d node laundry\n", totalFreed);
}