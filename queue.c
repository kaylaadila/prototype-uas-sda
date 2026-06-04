#include "laundry.h"

int nextId = 1;

int hitungHarga(float berat, char* jenis) {
    if (strcmp(jenis, "express") == 0)
        return (int)(berat * 10000);
    return (int)(berat * 5000);
}

void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
    q->count = 0;
}

int isEmptyQueue(Queue* q) {
    return q->front == NULL;
}

void enqueue(Queue* q, Laundry* node) {
    if (!node) return;
    node->next = NULL;
    if (isEmptyQueue(q)) {
        q->front = node;
        q->rear = node;
    } else {
        q->rear->next = node;
        q->rear = node;
    }
    q->count++;
}

Laundry* dequeueByID(Queue* q, int id) {
    if (isEmptyQueue(q)) return NULL;
    
    Laundry* curr = q->front;
    Laundry* prev = NULL;
    
    while (curr) {
        if (curr->id == id) {
            if (prev == NULL) {
                q->front = curr->next;
            } else {
                prev->next = curr->next;
            }
            if (curr == q->rear) {
                q->rear = prev;
            }
            q->count--;
            curr->next = NULL;
            return curr;
        }
        prev = curr;
        curr = curr->next;
    }
    return NULL;
}

void tampilQueue(Queue* q) {
    if (isEmptyQueue(q)) {
        printf("\nAntrian kosong\n");
        return;
    }
    printf("\n=== ANTRIAN ===\n");
    Laundry* curr = q->front;
    int no = 1;
    while (curr) {
        printf("%d. ID:%d | %s | %s | %.1fkg | Rp%d\n", 
               no++, curr->id, curr->nama, curr->jenis, curr->berat, curr->harga);
        curr = curr->next;
    }
}