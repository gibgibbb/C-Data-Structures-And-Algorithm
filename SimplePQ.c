#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

typedef struct {
    int data[MAX];
    int lastNdx;
} HeapList;

void insertToPot(HeapList *H, int item);
void displayHeap(HeapList H);
void heapSort(HeapList *H);
int deleteMax(HeapList *H);
void heapify(HeapList *H, int subroot);

void displayHeap(HeapList H) {
    for(int i = 0; i <= H.lastNdx; i++) {
        printf("%d ", H.data[i]);
    }
    printf("\n");
}

void heapSort(HeapList *H){
    int originalIndex = H->lastNdx;
    while(H->lastNdx > 0){
        H->data[H->lastNdx] = deleteMax(H);
    }   
    H->lastNdx = originalIndex;
}

int deleteMax(HeapList *H){
    int temp = H->data[0];
    H->data[0] = H->data[H->lastNdx--];
    if(H->lastNdx > 0){
        heapify(H, 0);
    }
    return temp;
}

void heapify(HeapList *H, int subroot){
    int trav, ndx, leftChild, rightChild;
    for(trav = subroot;; trav = ndx){
        leftChild = (2 * trav) + 1;
        rightChild = (2 * trav) + 2;
        if(leftChild > H->lastNdx){
            break;
        }
        ndx = (H->data[leftChild] > H->data[trav]) ? leftChild : trav;
        if(rightChild <= H->lastNdx && H->data[rightChild] > H->data[ndx]){
            ndx = rightChild;
        }
        if(ndx == trav){
            break;
        }
        if(ndx != trav){
            int temp = H->data[trav];
            H->data[trav] = H->data[ndx];
            H->data[ndx] = temp;
        }
    }
}

void insertToPot(HeapList *H, int item){
    if(H->lastNdx != MAX - 1){
        H->data[++H->lastNdx] = item;
        int parent, child;
        for(child = H->lastNdx, parent = (child - 1)/2; parent >= 0 && H->data[parent] < H->data[child]; child = parent, parent = (child - 1)/2){
            int temp = H->data[child];
            H->data[child] = H->data[parent];
            H->data[parent] = temp;
        }
    }
}

int main(){
    HeapList H = {{5, 6, 10, 2, 7, 3, 9, 1, 8, 4}, -1};

    int i;
    for(i = 0; i < MAX; i++){
        insertToPot(&H, H.data[i]);
    }
    printf("POT Heap: MAX HEAP\n");
    displayHeap(H);
    heapSort(&H);
    printf("Heapified Heap: MAX HEAP\n");
    displayHeap(H);

    printf("\n");

    return 0;
}