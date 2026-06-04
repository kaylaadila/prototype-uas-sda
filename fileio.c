#include "laundry.h"

int login() {
    FILE* f = fopen("akun.txt", "r");
    if (!f) {
        printf("File akun.txt tidak ditemukan!\n");
        return 0;
    }
    
    char user[30], pass[30], fuser[30], fpass[30];
    
    printf("\n==============================\n");
    printf("      KELOLA LAUNDRY          \n");
    printf("==============================\n");
    printf("Username: ");
    scanf("%s", user);
    printf("Password: ");
    scanf("%s", pass);
    
    while (fscanf(f, "%s %s", fuser, fpass) != EOF) {
        if (strcmp(user, fuser) == 0 && strcmp(pass, fpass) == 0) {
            fclose(f);
            if (strcmp(user, "admin") == 0) {
                printf("\nLogin sebagai ADMIN\n");
                return 1;
            } else {
                printf("\nLogin sebagai USER\n");
                return 2;
            }
        }
    }
    fclose(f);
    printf("\nLogin gagal!\n");
    return 0;
}

void lihatHarga() {
    printf("\n=== DAFTAR HARGA ===\n");
    printf("Reguler : Rp5000/kg (72 jam)\n");
    printf("Express : Rp10000/kg (24 jam)\n");
}

void simpanData(Queue* q, Stack* s) {
    FILE* f = fopen(FILE_DATA, "w");
    if (!f) return;
    
    Laundry* curr = q->front;
    while (curr) {
        fprintf(f, "Q|%d|%s|%s|%.1f|%d|%s|%s\n", 
                curr->id, curr->nama, curr->jenis, 
                curr->berat, curr->harga, 
                curr->tanggalMasuk, curr->tanggalSelesai);
        curr = curr->next;
    }
    
    for (int i = 0; i <= s->top; i++) {
        fprintf(f, "S|%d|%s|%s|%.1f|%d|%s|%s\n", 
                s->data[i]->id, s->data[i]->nama, s->data[i]->jenis,
                s->data[i]->berat, s->data[i]->harga,
                s->data[i]->tanggalMasuk, s->data[i]->tanggalSelesai);
    }
    fclose(f);
    printf("Data berhasil disimpan\n");
}

void loadData(Queue* q, Stack* s) {
    FILE* f = fopen(FILE_DATA, "r");
    if (!f) {
        printf("File data_laundry.txt tidak ditemukan, memulai data baru\n");
        return;
    }
    
    char tipe;
    int id, harga, maxId = 0;
    char nama[50], jenis[10], tglMasuk[11], tglSelesai[11];
    float berat;
    
    while (fscanf(f, " %c|%d|%[^|]|%[^|]|%f|%d|%[^|]|%[^\n]\n", 
                  &tipe, &id, nama, jenis, &berat, &harga, 
                  tglMasuk, tglSelesai) == 8) {
        Laundry* baru = (Laundry*)malloc(sizeof(Laundry));
        baru->id = id;
        strcpy(baru->nama, nama);
        strcpy(baru->jenis, jenis);
        baru->berat = berat;
        baru->harga = harga;
        strcpy(baru->tanggalMasuk, tglMasuk);
        strcpy(baru->tanggalSelesai, tglSelesai);
        baru->next = NULL;
        
        if (tipe == 'Q') enqueue(q, baru);
        else if (tipe == 'S') pushStack(s, baru);
        
        if (id > maxId) maxId = id;
    }
    nextId = maxId + 1;
    fclose(f);
    printf("Data berhasil dimuat\n");
}