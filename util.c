#include "laundry.h"

void bersihkanBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int bacaInt(char *pesan) {
    int nilai;
    if (strlen(pesan) > 0) printf("%s", pesan);
    while (scanf("%d", &nilai) != 1) {
        bersihkanBuffer();
        printf("Input harus angka! ");
        if (strlen(pesan) > 0) printf("%s", pesan);
    }
    bersihkanBuffer();
    return nilai;
}

float bacaFloat(char *pesan) {
    float nilai;
    printf("%s", pesan);
    while (scanf("%f", &nilai) != 1) {
        bersihkanBuffer();
        printf("Input harus angka! %s", pesan);
    }
    bersihkanBuffer();
    return nilai;
}

void bacaString(char *pesan, char *target, int maxLen) {
    printf("%s", pesan);
    fgets(target, maxLen, stdin);
    target[strcspn(target, "\n")] = 0;
}

int isKabisat(int year) {
    if (year % 400 == 0) return 1;
    if (year % 100 == 0) return 0;
    if (year % 4 == 0) return 1;
    return 0;
}

int getMaxDay(int month, int year) {
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        return 31;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    else {
        if (isKabisat(year)) return 29;
        else return 28;
    }
}

void hitungTanggalSelesai(char *tglMasuk, char *tglSelesai, int tambahHari) {
    int day, month, year;
    sscanf(tglMasuk, "%d/%d/%d", &day, &month, &year);
    
    day += tambahHari;
    
    while (day > getMaxDay(month, year)) {
        day -= getMaxDay(month, year);
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
    
    sprintf(tglSelesai, "%02d/%02d/%04d", day, month, year);
}

int validasiTanggal(char *tgl) {
    int day, month, year;
    
    if (sscanf(tgl, "%d/%d/%d", &day, &month, &year) != 3) {
        printf("Format salah! Gunakan DD/MM/YYYY\n");
        return 0;
    }
    
    if (year < 1900 || year > 2100) {
        printf("Tahun harus 1900-2100\n");
        return 0;
    }
    
    if (month < 1 || month > 12) {
        printf("Bulan harus 1-12\n");
        return 0;
    }
    
    if (day < 1) {
        printf("Hari minimal 1\n");
        return 0;
    }
    
    int maxDay = getMaxDay(month, year);
    
    if (day > maxDay) {
        if (month == 2 && day == 29) {
            printf("Tahun %d BUKAN tahun kabisat, Februari hanya 28 hari\n", year);
        } else {
            printf("Bulan %d tahun %d hanya memiliki %d hari\n", month, year, maxDay);
        }
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
    
    printf("--- BELUM SELESAI (diurutkan dari paling cepat) ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d. ID:%d | %s | %s | Selesai: %s\n", 
               i+1, belumSelesai[i]->id, belumSelesai[i]->nama, 
               belumSelesai[i]->jenis, belumSelesai[i]->tanggalSelesai);
    }
    
    if (!isEmptyStack(s)) {
        printf("\n--- SUDAH SELESAI ---\n");
        int no = 1;
        for (int i = s->top; i >= 0; i--) {
            printf("%d. ID:%d | %s | %s\n", no++, s->data[i]->id, s->data[i]->nama, s->data[i]->jenis);
        }
    }
    if (isEmptyQueue(q) && isEmptyStack(s)) {
        printf("Tidak ada data\n");
    }
}

void freeAllMemory(Queue* q, Stack* s) {
    int total = 0;
    Laundry* curr = q->front;
    while (curr) {
        Laundry* next = curr->next;
        free(curr);
        curr = next;
        total++;
    }
    for (int i = 0; i <= s->top; i++) {
        free(s->data[i]);
        total++;
    }
    q->front = NULL;
    q->rear = NULL;
    q->count = 0;
    s->top = -1;
    printf("\nMemori dibebaskan: %d node laundry\n", total);
}