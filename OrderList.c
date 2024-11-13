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

void initializeOrders(OrdInfo orders[]);
void populateHeap(orderHeap *H);
void displayHeap(orderHeap *H);
void displayOrder(OrdInfo order);
void displayBST(orderBST root);
orderBST insertPaidOrders(orderBST root, OrdInfo orders[]);
float calculateTotalPrice(OrdInfo order);
int compareOrdVal(OrdInfo order1, OrdInfo order2);
OrdInfo serveOrder(orderHeap *H);

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

    orderHeap H;
    H.lastOrd = -1;

    populateHeap(&H);
    printf("\nInitial Heap:\n");
    displayHeap(&H);

    printf("\n\nServing Orders:");
    for(int i = 0; i < 3; i++) {
        OrdInfo served = serveOrder(&H);
        printf("\n\nServed Order #%d", served.ordNum);
        printf("\nTotal Price: %.2f", calculateTotalPrice(served));
        
        printf("\nRemaining Heap:");
        displayHeap(&H);
    }
    return 0;
}

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

void populateHeap(orderHeap *H) {
    // Create sample orders
    OrdInfo orders[6];  // 5 orders + 1 sentinel

    // Order 1: Multiple items
    orders[0].ordNum = 201;
    orders[0].payStatus = '1';
    orders[0].ordList = (OrdLL)malloc(sizeof(OrdLLNode));
    strcpy(orders[0].ordList->item.mealCode, "M1");
    strcpy(orders[0].ordList->item.mealName, "Burger Combo");
    orders[0].ordList->item.price = 199.50;
    
    // Add second item to Order 1
    orders[0].ordList->next = (OrdLL)malloc(sizeof(OrdLLNode));
    strcpy(orders[0].ordList->next->item.mealCode, "M2");
    strcpy(orders[0].ordList->next->item.mealName, "Fries");
    orders[0].ordList->next->item.price = 50.00;
    orders[0].ordList->next->next = NULL;
    // Total: 249.50

    // Order 2: Single expensive item
    orders[1].ordNum = 202;
    orders[1].payStatus = '1';
    orders[1].ordList = (OrdLL)malloc(sizeof(OrdLLNode));
    strcpy(orders[1].ordList->item.mealCode, "M3");
    strcpy(orders[1].ordList->item.mealName, "Premium Steak");
    orders[1].ordList->item.price = 399.99;
    orders[1].ordList->next = NULL;
    // Total: 399.99

    // Order 3: Multiple medium-priced items
    orders[2].ordNum = 203;
    orders[2].payStatus = '1';
    orders[2].ordList = (OrdLL)malloc(sizeof(OrdLLNode));
    strcpy(orders[2].ordList->item.mealCode, "M4");
    strcpy(orders[2].ordList->item.mealName, "Pizza");
    orders[2].ordList->item.price = 150.00;
    
    orders[2].ordList->next = (OrdLL)malloc(sizeof(OrdLLNode));
    strcpy(orders[2].ordList->next->item.mealCode, "M5");
    strcpy(orders[2].ordList->next->item.mealName, "Pasta");
    orders[2].ordList->next->item.price = 120.00;
    orders[2].ordList->next->next = NULL;
    // Total: 270.00

    // Order 4: Single cheap item
    orders[3].ordNum = 204;
    orders[3].payStatus = '1';
    orders[3].ordList = (OrdLL)malloc(sizeof(OrdLLNode));
    strcpy(orders[3].ordList->item.mealCode, "M6");
    strcpy(orders[3].ordList->item.mealName, "Ice Cream");
    orders[3].ordList->item.price = 49.99;
    orders[3].ordList->next = NULL;
    // Total: 49.99

    // Order 5: Multiple items
    orders[4].ordNum = 205;
    orders[4].payStatus = '1';
    orders[4].ordList = (OrdLL)malloc(sizeof(OrdLLNode));
    strcpy(orders[4].ordList->item.mealCode, "M7");
    strcpy(orders[4].ordList->item.mealName, "Family Meal");
    orders[4].ordList->item.price = 299.99;
    
    orders[4].ordList->next = (OrdLL)malloc(sizeof(OrdLLNode));
    strcpy(orders[4].ordList->next->item.mealCode, "M8");
    strcpy(orders[4].ordList->next->item.mealName, "Dessert");
    orders[4].ordList->next->item.price = 89.99;
    orders[4].ordList->next->next = NULL;
    // Total: 389.98

    // Insert orders into heap
    for(int i = 0; i < 5; i++) {
        H->lastOrd++;
        H->orders[H->lastOrd] = (orderBST)malloc(sizeof(orderNode));
        H->orders[H->lastOrd]->order = orders[i];
        H->orders[H->lastOrd]->leftChild = NULL;
        H->orders[H->lastOrd]->rightChild = NULL;
    }

    // Heapify the entire array to maintain max heap property
for(int i = H->lastOrd/2; i >= 0; i--) {
    int index = i;
    while (1) {
        int largest = index;
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        
        if (leftChild <= H->lastOrd && 
            compareOrdVal(H->orders[leftChild]->order, H->orders[largest]->order) > 0) {
            largest = leftChild;
        }
        
        if (rightChild <= H->lastOrd && 
            compareOrdVal(H->orders[rightChild]->order, H->orders[largest]->order) > 0) {
            largest = rightChild;
        }
        
        if (largest != index) {
            orderBST temp = H->orders[index];
            H->orders[index] = H->orders[largest];
            H->orders[largest] = temp;
            index = largest;
        } else {
            break;
        }
    }
}
}

void displayHeap(orderHeap *H) {
    printf("\nHeap Contents (Total Price Order):");
    printf("\n================================");
    for(int i = 0; i <= H->lastOrd; i++) {
        printf("\nOrder #%d", H->orders[i]->order.ordNum);
        printf("\nTotal Price: %.2f", calculateTotalPrice(H->orders[i]->order));
        printf("\nItems:");
        OrdLL current = H->orders[i]->order.ordList;
        while(current != NULL) {
            printf("\n  - %s: %.2f", current->item.mealName, current->item.price);
            current = current->next;
        }
        printf("\n-----------------");
    }
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

float calculateTotalPrice(OrdInfo order) {
    float total = 0;
    OrdLL current = order.ordList;
    
    while (current != NULL) {
        total += current->item.price;
        current = current->next;
    }
    
    return total;
}

int compareOrdVal(OrdInfo order1, OrdInfo order2) {
    float total1 = calculateTotalPrice(order1);
    float total2 = calculateTotalPrice(order2);
    
    if (total1 == total2) return 0;
    if (total1 > total2) return 1;
    return -1;
}

OrdInfo serveOrder(orderHeap *H) {
    OrdInfo emptyOrder = {0, NULL, '\0'};  // Sentinel value
    
    // Check if heap is empty
    if (H->lastOrd == -1) {
        return emptyOrder;
    }
    
    // Store the root order (highest priority)
    OrdInfo highestOrder = H->orders[0]->order;
    
    // Replace root with last element
    H->orders[0] = H->orders[H->lastOrd];
    H->lastOrd--;
    
    // Heapify from root (if heap is not empty)
     if (H->lastOrd > -1) {
        for (int index = 0; ; ) {
            int largest = index;
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            
            if (leftChild <= H->lastOrd && 
                compareOrdVal(H->orders[leftChild]->order, H->orders[largest]->order) > 0) {
                largest = leftChild;
            }
            
            if (rightChild <= H->lastOrd && 
                compareOrdVal(H->orders[rightChild]->order, H->orders[largest]->order) > 0) {
                largest = rightChild;
            }
            
            if (largest != index) {
                orderBST temp = H->orders[index];
                H->orders[index] = H->orders[largest];
                H->orders[largest] = temp;
                index = largest;
            } else {
                break;  // Heap property is restored
            }
        }
    }
    return highestOrder;
}