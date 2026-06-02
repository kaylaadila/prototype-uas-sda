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
        printf("\n[ RIWAYAT KOSONG ]\n");
        return;
    }
    
    printf("\n+-------------------------------------------------------------------+\n");
    printf("|                         DAFTAR RIWAYAT                            |\n");
    printf("+-------------------------------------------------------------------+\n");
    printf("| No | ID | Nama            | Jenis   | Berat | Harga    | Status  |\n");
    printf("+-------------------------------------------------------------------+\n");
    
    int no = 1;
    for (int i = s->top; i >= 0; i--) {
        printf("| %-2d | %-2d | %-15s | %-7s | %5.1f | Rp %-6d | SIAP    |\n", 
               no++, 
               s->data[i]->id, 
               s->data[i]->nama, 
               s->data[i]->jenis, 
               s->data[i]->berat, 
                s->data[i]->harga);
    }
    printf("+-------------------------------------------------------------------+\n");
    printf("| Total transaksi: %-42d |\n", s->top + 1);
    printf("+-------------------------------------------------------------------+\n");
}