#include "stdio.h"
#include "stdlib.h"
#include "string.h"
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
typedef struct orderNode {
    OrdInfo order;
    struct orderNode *leftChild, *rightChild;
}orderNode, *orderBST;

//definition of a Heap of orders
typedef struct{
    int lastOrd; // -1 if heap of orders is empty
    orderBST orders[MAX_ORDERS];
}orderHeap, *orderPQ;

void initializeOrders(OrdInfo orders[]) {
    // Order 1
    orders[0].ordNum = 101;
    orders[0].payStatus = '1';  // paid
    orders[0].ordList = (OrdLL)malloc(sizeof(OrdLLNode));
    strcpy(orders[0].ordList->item.mealCode, "M1");
    strcpy(orders[0].ordList->item.mealName, "Chicken Burger");
    orders[0].ordList->item.price = 99.50;
    orders[0].ordList->next = NULL;

    // Order 2
    orders[1].ordNum = 103;
    orders[1].payStatus = '1';  // paid
    orders[1].ordList = (OrdLL)malloc(sizeof(OrdLLNode));
    strcpy(orders[1].ordList->item.mealCode, "M2");
    strcpy(orders[1].ordList->item.mealName, "Beef Burger");
    orders[1].ordList->item.price = 129.75;
    orders[1].ordList->next = NULL;

    // Order 3
    orders[2].ordNum = 102;
    orders[2].payStatus = '0';  // unpaid
    orders[2].ordList = (OrdLL)malloc(sizeof(OrdLLNode));
    strcpy(orders[2].ordList->item.mealCode, "M3");
    strcpy(orders[2].ordList->item.mealName, "Fish Burger");
    orders[2].ordList->item.price = 89.25;
    orders[2].ordList->next = NULL;

    // Order 4
    orders[3].ordNum = 104;
    orders[3].payStatus = '1';  // paid
    orders[3].ordList = (OrdLL)malloc(sizeof(OrdLLNode));
    strcpy(orders[3].ordList->item.mealCode, "M4");
    strcpy(orders[3].ordList->item.mealName, "Veggie Burger");
    orders[3].ordList->item.price = 79.50;
    orders[3].ordList->next = NULL;

    // Order 5
    orders[4].ordNum = 105;
    orders[4].payStatus = '1';  // paid
    orders[4].ordList = (OrdLL)malloc(sizeof(OrdLLNode));
    strcpy(orders[4].ordList->item.mealCode, "M5");
    strcpy(orders[4].ordList->item.mealName, "Double Cheeseburger");
    orders[4].ordList->item.price = 149.99;
    orders[4].ordList->next = NULL;

    // Sentinel
    orders[5].ordNum = 0;
    orders[5].payStatus = '\0';  // sentinel
    orders[5].ordList = NULL;
}

// Add this display function to verify the BST
void displayOrder(OrdInfo order) {
    printf("\nOrder #: %d", order.ordNum);
    printf("\nPayment Status: %c", order.payStatus);
    if (order.ordList != NULL) {
        printf("\nMeal: %s - %s", order.ordList->item.mealCode, order.ordList->item.mealName);
        printf("\nPrice: %.2f", order.ordList->item.price);
    }
    printf("\n-------------------");
}

void displayBST(orderBST root) {
    if (root != NULL) {
        displayBST(root->leftChild);
        displayOrder(root->order);
        displayBST(root->rightChild);
    }
}

orderBST insertPaidOrders(orderBST root, OrdInfo orders[]) {
    int i;
    // Loop until we hit the sentinel (payStatus = '\0')
    for (i = 0; orders[i].payStatus != '\0'; i++) {
        // Only insert if the order is paid (payStatus = '1')
        if (orders[i].payStatus == '1') {
            // Insert logic integrated here
            if (root == NULL) {
                orderBST newNode = (orderBST)malloc(sizeof(orderNode));
                newNode->order = orders[i];
                newNode->leftChild = NULL;
                newNode->rightChild = NULL;
                root = newNode;
            } else {
                if(orders[i].ordNum < root->order.ordNum) {
                    root->leftChild = insertPaidOrders(root->leftChild, &orders[i]);
                } else if (orders[i].ordNum > root->order.ordNum) {
                    root->rightChild = insertPaidOrders(root->rightChild, &orders[i]);
                }
            }
        }
    }
    
    return root;
}

int main() {
    orderBST B = NULL;
    OrdInfo orders[MAX_ORDERS];
    
    // Initialize orders
    initializeOrders(orders);
    
    // Insert paid orders into BST
    B = insertPaidOrders(B, orders);
    
    // Display the BST (in-order traversal)
    printf("\nOrders in BST (ascending order):\n");
    displayBST(B);
    
    return 0;
}