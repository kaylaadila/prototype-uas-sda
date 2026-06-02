#include "laundry.h"

void shellSort(Queue* q) {
    if (q->count < 2) {
        printf("\nMinimal 2 antrian untuk sorting\n");
        return;
    }
    
    Laundry* arr[100];
    int count = 0;
    Laundry* curr = q->front;
    while (curr) {
        arr[count++] = curr;
        curr = curr->next;
    }
    
    for (int gap = count / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < count; i++) {
            Laundry* temp = arr[i];
            int prioritasTemp = (strcmp(temp->jenis, "express") == 0) ? 1 : 2;
            int j;
            for (j = i; j >= gap; j -= gap) {
                int prioritasJ = (strcmp(arr[j - gap]->jenis, "express") == 0) ? 1 : 2;
                if (prioritasJ > prioritasTemp) {
                    arr[j] = arr[j - gap];
                } else {
                    break;
                }
            }
            arr[j] = temp;
        }
    }
    
    q->front = arr[0];
    for (int i = 0; i < count - 1; i++) {
        arr[i]->next = arr[i+1];
    }
    arr[count-1]->next = NULL;
    q->rear = arr[count-1];
    
    printf("\n[SHELL SORT] Antrian: EXPRESS dulu, baru REGULER\n");
}

// ==================== MERGE SORT UNTUK QUEUE (BERAT) ====================
void mergeByWeightQueue(Laundry* arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    Laundry* L[n1];
    Laundry* R[n2];
    
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i]->berat >= R[j]->berat) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSortByWeightQueue(Laundry* arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortByWeightQueue(arr, left, mid);
        mergeSortByWeightQueue(arr, mid + 1, right);
        mergeByWeightQueue(arr, left, mid, right);
    }
}

void tampilUrutBerdasarkanBeratDariQueue(Queue *q) {
    if (isEmptyQueue(q)) {
        printf("\n[INFO] Antrian kosong, tidak ada laundry yang akan dicuci!\n");
        return;
    }
    
    int totalData = q->count;
    Laundry** arr = (Laundry**)malloc(totalData * sizeof(Laundry*));
    Laundry* curr = q->front;
    for (int i = 0; i < totalData; i++) {
        arr[i] = curr;
        curr = curr->next;
    }
    
    mergeSortByWeightQueue(arr, 0, totalData - 1);
    
    printf("\n==============================================================\n");
    printf("     REKOMENDASI MESIN CUCI BERDASARKAN BERAT (TERBERAT -> TERINGAN)\n");
    printf("==============================================================\n");
    printf("No  Nama Pelanggan     Jenis      Berat(kg)   Harga      Rekomendasi\n");
    printf("--- ------------------ ---------- ---------- ---------- -----------------\n");
    
    for (int i = 0; i < totalData; i++) {
        char mesin[20];
        if (arr[i]->berat <= 5) strcpy(mesin, "Mesin Kecil");
        else if (arr[i]->berat <= 8) strcpy(mesin, "Mesin Sedang");
        else if (arr[i]->berat <= 12) strcpy(mesin, "Mesin Besar");
        else strcpy(mesin, "Split / 2x Cuci");
        
        printf("%-3d %-18s %-10s %-10.1f %-10d %s\n",
               i+1, arr[i]->nama, arr[i]->jenis, arr[i]->berat, arr[i]->harga, mesin);
    }
    printf("==============================================================\n");
    
    free(arr);
}

// ==================== QUICK SORT ====================
int compareDate(char *tgl1, char *tgl2) {
    int d1, m1, y1, d2, m2, y2;
    sscanf(tgl1, "%d/%d/%d", &d1, &m1, &y1);
    sscanf(tgl2, "%d/%d/%d", &d2, &m2, &y2);
    
    if (y1 != y2) return y1 < y2;
    if (m1 != m2) return m1 < m2;
    return d1 < d2;
}

int partitionByDate(Laundry* arr[], int low, int high) {
    char* pivot = arr[high]->tanggalSelesai;
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (compareDate(arr[j]->tanggalSelesai, pivot)) {
            i++;
            Laundry* temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    Laundry* temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quickSortByDate(Laundry* arr[], int low, int high) {
    if (low < high) {
        int pi = partitionByDate(arr, low, high);
        quickSortByDate(arr, low, pi - 1);
        quickSortByDate(arr, pi + 1, high);
    }
}