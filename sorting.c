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
            int pTemp = (strcmp(temp->jenis, "express") == 0) ? 1 : 2;
            int j;
            for (j = i; j >= gap; j -= gap) {
                int pJ = (strcmp(arr[j - gap]->jenis, "express") == 0) ? 1 : 2;
                if (pJ > pTemp) {
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
    
    printf("\n[Shell Sort] Antrian: EXPRESS dulu, baru REGULER\n");
}

void mergeByWeight(Laundry* arr[], int left, int mid, int right) {
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

void mergeSortByWeight(Laundry* arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortByWeight(arr, left, mid);
        mergeSortByWeight(arr, mid + 1, right);
        mergeByWeight(arr, left, mid, right);
    }
}

void tampilUrutBerdasarkanBerat(Queue *q) {
    if (isEmptyQueue(q)) {
        printf("\nAntrian kosong\n");
        return;
    }
    
    int total = q->count;
    Laundry** arr = (Laundry**)malloc(total * sizeof(Laundry*));
    Laundry* curr = q->front;
    for (int i = 0; i < total; i++) {
        arr[i] = curr;
        curr = curr->next;
    }
    
    mergeSortByWeight(arr, 0, total - 1);
    
    printf("\n=== SORTING BERAT (TERBERAT -> TERINGAN) ===\n");
    printf("No  Nama            Berat    Harga      Mesin\n");
    printf("--- --------------- -------- ---------- -----\n");
    
    for (int i = 0; i < total; i++) {
        char mesin[20];
        if (arr[i]->berat <= 5) strcpy(mesin, "Kecil");
        else if (arr[i]->berat <= 8) strcpy(mesin, "Sedang");
        else if (arr[i]->berat <= 12) strcpy(mesin, "Besar");
        else strcpy(mesin, "Split");
        printf("%-3d %-15s %-8.1f %-10d %s\n", i+1, arr[i]->nama, arr[i]->berat, arr[i]->harga, mesin);
    }
    free(arr);
}

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