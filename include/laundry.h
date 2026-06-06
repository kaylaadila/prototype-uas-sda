#ifndef LAUNDRY_H
#define LAUNDRY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAMA 50
#define FILE_DATA "data_laundry.txt"

typedef struct Laundry {
    int id;
    char nama[MAX_NAMA];
    char jenis[10];
    float berat;
    int harga;
    char tanggalMasuk[11];
    char tanggalSelesai[11];
    struct Laundry* next;
} Laundry;

typedef struct {
    Laundry* front;
    Laundry* rear;
    int count;
} Queue;

typedef struct {
    Laundry* data[100];
    int top;
} Stack;

extern int nextId;

void initQueue(Queue* q);
int isEmptyQueue(Queue* q);
void enqueue(Queue* q, Laundry* node);
Laundry* dequeueByID(Queue* q, int id);
void tampilQueue(Queue* q);
int hapusPesanan(Queue* q, Stack* s, int id);

void initStack(Stack* s);
int isEmptyStack(Stack* s);
void pushStack(Stack* s, Laundry* node);
void tampilStack(Stack* s);

void shellSort(Queue* q);
void mergeSortByWeight(Queue* q);
void quickSortByDate(Laundry* arr[], int low, int high);
void tampilJadwal(Queue* q, Stack* s);

int login();
void lihatHarga();
void simpanData(Queue* q, Stack* s);
void loadData(Queue* q, Stack* s);

int hitungHarga(float berat, char* jenis);
void freeAllMemory(Queue* q, Stack* s);
void hitungTanggalSelesai(char *tglMasuk, char *tglSelesai, int tambahHari);
int validasiTanggal(char *tgl);
int compareDate(char *tgl1, char *tgl2);

void bersihkanBuffer();
int bacaInt(char *pesan);
float bacaFloat(char *pesan);
void bacaString(char *pesan, char *target, int maxLen);

#endif