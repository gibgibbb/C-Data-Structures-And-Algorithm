#include "stdio.h"
#include "stdlib.h"
#define MAX_ORDERS 100

typedef struct {
    char mealCode[3];
    char mealName[24];
    float price;
}OrdItem;

typedef struct node{
    OrdItem item;
    struct node *next;
}OrdLLNode, *OrdLL;

//definition of a linked list of orderItems
typedef struct{
    int ordNum; // order number
    OrdLL ordList; // list of order
    char payStatus; // '1' for paid, '0' for sentinel
}OrdInfo;

//definition of a BST of orders
typedef struct orderNode{
    OrdInfo order;
    struct node *leftChild, *rightChild;
}orderNode, *orderBST;

//definition of a Heap of orders
typedef struct{
    int lastOrd; // -1 if heap of orders is empty
    orderBST orders[MAX_ORDERS];
}orderHeap, *orderPQ;

int main(){
    printf("Hello World");
    return 0;
}
