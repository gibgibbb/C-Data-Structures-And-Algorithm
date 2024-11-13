#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

// Student Record Structure
typedef struct {
    char FName[24], LName[16], MI;
} nametype;

typedef struct {
    unsigned int ID;
    nametype SName;
    char course[8];
    int yr;
    int priority;  // Added priority field
} studRec;

// Priority Queue using Array Implementation
typedef struct {
    studRec heap[MAX];
    int lastIndex;  // Index of last element (-1 if empty)
} PriorityQueue;

// Function Prototypes
void initPQ(PriorityQueue *PQ);
int isEmpty(PriorityQueue PQ);
int isFull(PriorityQueue PQ);
void enqueue(PriorityQueue *PQ, studRec newStud);
studRec dequeue(PriorityQueue *PQ);
void heapifyUp(PriorityQueue *PQ, int index);
void heapifyDown(PriorityQueue *PQ, int index);
void displayPQ(PriorityQueue PQ);
void swap(studRec *a, studRec *b);

// Initialize Priority Queue
void initPQ(PriorityQueue *PQ) {
    PQ->lastIndex = -1;
}

// Check if PQ is empty
int isEmpty(PriorityQueue PQ) {
    return PQ.lastIndex == -1;
}

// Check if PQ is full
int isFull(PriorityQueue PQ) {
    return PQ.lastIndex == MAX - 1;
}

// Swap two elements
void swap(studRec *a, studRec *b) {
    studRec temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify Up (for insertion)
void heapifyUp(PriorityQueue *PQ, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        
        // Check both priority and POT property
        if (PQ->heap[index].priority > PQ->heap[parent].priority ||
            (PQ->heap[index].priority == PQ->heap[parent].priority && 
             PQ->heap[index].ID < PQ->heap[parent].ID)) {
            swap(&PQ->heap[index], &PQ->heap[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

// Heapify Down (for deletion)
void heapifyDown(PriorityQueue *PQ, int index) {
    int maxIndex = index;
    int lastIndex = PQ->lastIndex;
    
    while (1) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        
        // Check left child
        if (leftChild <= lastIndex) {
            if (PQ->heap[leftChild].priority > PQ->heap[maxIndex].priority ||
                (PQ->heap[leftChild].priority == PQ->heap[maxIndex].priority && 
                 PQ->heap[leftChild].ID < PQ->heap[maxIndex].ID)) {
                maxIndex = leftChild;
            }
        }
        
        // Check right child
        if (rightChild <= lastIndex) {
            if (PQ->heap[rightChild].priority > PQ->heap[maxIndex].priority ||
                (PQ->heap[rightChild].priority == PQ->heap[maxIndex].priority && 
                 PQ->heap[rightChild].ID < PQ->heap[maxIndex].ID)) {
                maxIndex = rightChild;
            }
        }
        
        if (maxIndex != index) {
            swap(&PQ->heap[index], &PQ->heap[maxIndex]);
            index = maxIndex;
        } else {
            break;
        }
    }
}

// Enqueue operation
void enqueue(PriorityQueue *PQ, studRec newStud) {
    if (isFull(*PQ)) {
        printf("\nPriority Queue is full!");
        return;
    }
    
    // Add new element at the end
    PQ->lastIndex++;
    PQ->heap[PQ->lastIndex] = newStud;
    
    // Maintain heap property
    heapifyUp(PQ, PQ->lastIndex);
}

// Dequeue operation
studRec dequeue(PriorityQueue *PQ) {
    studRec emptyRec = {0, {"", "", '\0'}, "", 0, 0};  // Empty record
    
    if (isEmpty(*PQ)) {
        printf("\nPriority Queue is empty!");
        return emptyRec;
    }
    
    // Save root element
    studRec result = PQ->heap[0];
    
    // Replace root with last element
    PQ->heap[0] = PQ->heap[PQ->lastIndex];
    PQ->lastIndex--;
    
    // Maintain heap property
    if (!isEmpty(*PQ)) {
        heapifyDown(PQ, 0);
    }
    
    return result;
}

// Display Priority Queue
void displayPQ(PriorityQueue PQ) {
    printf("\nPriority Queue Contents:");
    printf("\n=======================");
    
    for (int i = 0; i <= PQ.lastIndex; i++) {
        printf("\nIndex %d:", i);
        printf("\nID: %u", PQ.heap[i].ID);
        printf("\nName: %s %s %c", 
               PQ.heap[i].SName.FName,
               PQ.heap[i].SName.LName,
               PQ.heap[i].SName.MI);
        printf("\nPriority: %d", PQ.heap[i].priority);
        printf("\n-----------------");
    }
}

int main() {
    PriorityQueue PQ;
    initPQ(&PQ);
    
    // Test data
    studRec students[] = {
        {1001, {"John", "Doe", 'A'}, "BSCS", 1, 3},
        {1002, {"Jane", "Smith", 'B'}, "BSIT", 2, 1},
        {1003, {"Bob", "Johnson", 'C'}, "BSCS", 1, 3},
        {1004, {"Alice", "Brown", 'D'}, "BSIT", 3, 2},
        {1005, {"Charlie", "Wilson", 'E'}, "BSCS", 2, 1}
    };
    
    // Enqueue students
    printf("Enqueueing students...\n");
    for(int i = 0; i < 5; i++) {
        enqueue(&PQ, students[i]);
    }
    
    // Display initial queue
    displayPQ(PQ);
    
    // Dequeue highest priority students
    printf("\n\nDequeuing 3 students...");
    for(int i = 0; i < 3; i++) {
        studRec served = dequeue(&PQ);
        printf("\nDequeued: ID %u, Priority %d", served.ID, served.priority);
    }
    
    // Display remaining queue
    printf("\n\nRemaining Queue:");
    displayPQ(PQ);
    
    return 0;
}