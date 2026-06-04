#include "laundry.h"

void initStack(Stack* s) {
    s->top = -1;
}

int isEmptyStack(Stack* s) {
    return s->top == -1;
}

void pushStack(Stack* s, Laundry* node) {
    if (s->top < 99 && node) {
        s->data[++(s->top)] = node;
    }
}

void tampilStack(Stack* s) {
    if (isEmptyStack(s)) {
        printf("\nRiwayat kosong\n");
        return;
    }
    
    printf("\n=== RIWAYAT ===\n");
    int no = 1;
    for (int i = s->top; i >= 0; i--) {
        printf("%d. ID:%d | %s | %s | %.1fkg | Rp%d\n", 
               no++, s->data[i]->id, s->data[i]->nama, 
               s->data[i]->jenis, s->data[i]->berat, s->data[i]->harga);
    }
    
    int maxIdx = 0;
    for (int i = 1; i <= s->top; i++) {
        if (s->data[i]->harga > s->data[maxIdx]->harga) {
            maxIdx = i;
        }
    }
    
    printf("\n=== TRANSAKSI TERBANYAK ===\n");
    printf("ID: %d | Nama: %s | Total: Rp%d\n", 
           s->data[maxIdx]->id, s->data[maxIdx]->nama, s->data[maxIdx]->harga);
}