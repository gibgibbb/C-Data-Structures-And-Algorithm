#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} NodeType, *BST;

void insert(BST *B, int item);
void delete(BST *B, int item);
void inOrder(BST B);
void preOrder(BST B);
void postOrder(BST B);
void display(BST B);

void insert(BST *B, int item) {
    BST *trav;
    
    for(trav = B; *trav != NULL; trav = (item < (*trav)->data) ? &(*trav)->left : &(*trav)->right) {}
    
    *trav = (BST)malloc(sizeof(NodeType));
    if(*trav != NULL) {
        (*trav)->data = item;
        (*trav)->left = (*trav)->right = NULL;
    }
}

void delete(BST *B, int item) {
    BST *trav, temp;
    
    for(trav = B; *trav != NULL && (*trav)->data != item; trav = (item < (*trav)->data) ? &(*trav)->left : &(*trav)->right) {}
    
    if(*trav != NULL) {
        if((*trav)->left == NULL) {
            temp = *trav;
            *trav = (*trav)->right;
            free(temp);
        } else if((*trav)->right == NULL) {
            temp = *trav;
            *trav = (*trav)->left;
            free(temp);
        } else {
            for(temp = (*trav)->right; temp->left != NULL; temp = temp->left) {}
            (*trav)->data = temp->data;
            delete(&(*trav)->right, temp->data);
        }
    }
}

void inOrder(BST B) {
    if(B != NULL) {
        inOrder(B->left);
        printf("%d ", B->data);
        inOrder(B->right);
    }
}

void preOrder(BST B) {
    if(B != NULL) {
        printf("%d ", B->data);
        preOrder(B->left);
        preOrder(B->right);
    }
}

void postOrder(BST B) {
    if(B != NULL) {
        postOrder(B->left);
        postOrder(B->right);
        printf("%d ", B->data);
    }
}

void display(BST B) {
    printf("\nPre-order  : ");
    preOrder(B);
    printf("\nIn-order   : ");
    inOrder(B);
    printf("\nPost-order : ");
    postOrder(B);
    printf("\n");
}

int main() {
    BST tree = NULL;
    
    int values[] = {5, 3, 7, 1, 4, 6, 8};
    int n = sizeof(values)/sizeof(values[0]);
    
    printf("Inserting values: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", values[i]);
        insert(&tree, values[i]);
    }
    
    printf("\n\nInitial tree:");
    display(tree);
    
    // Delete a value
    int deleteValue = 3;
    printf("\nDeleting value: %d", deleteValue);
    delete(&tree, deleteValue);
    
    printf("\nAfter deletion:");
    display(tree);
    
    return 0;
}