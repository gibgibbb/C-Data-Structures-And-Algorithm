#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Student Record Structure (similar to the image)
typedef struct {
    char FName[24], LName[16], MI;
} nametype;

typedef struct {
    unsigned int ID;
    nametype SName;
    char course[8];
    int yr;
} studRec;

// Tree Node using List of Children
typedef struct treeNode {
    studRec data;
    struct treeNode *firstChild;   // Points to first child
    struct treeNode *nextSibling;  // Points to next sibling
} TreeNode, *Tree;

// Function Prototypes
void initTree(Tree *T);
void insertNode(Tree *T, studRec newStud);
int isMember(Tree T, unsigned int ID);
void deleteNode(Tree *T, unsigned int ID);
void displayTree(Tree T, int level);

// Initialize Tree
void initTree(Tree *T) {
    *T = NULL;
}

// Insert Node
void insertNode(Tree *T, studRec newStud) {
    Tree newNode = (Tree)malloc(sizeof(TreeNode));
    newNode->data = newStud;
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;

    if(*T != NULL) {
        if(newStud.ID < (*T)->data.ID) {
            newNode->nextSibling = (*T)->firstChild;
            (*T)->firstChild = newNode;
        } else {
            Tree *trav = &((*T)->firstChild);
            for(; *trav != NULL && (*trav)->data.ID < newStud.ID; trav = &((*trav)->nextSibling)){}
            newNode->nextSibling = *trav;
            *trav = newNode;
        }
    } else {
        *T = newNode;
    }
}

// Check if ID exists in tree
int isMember(Tree T, unsigned int ID) {
    if (T == NULL) {
        return 0;
    }
    
    if (T->data.ID == ID) {
        return 1;
    }
    
    // Check among children
    Tree child = T->firstChild;
    while (child != NULL) {
        if (isMember(child, ID)) {
            return 1;
        }
        child = child->nextSibling;
    }
    
    return 0;
}

// Delete Node
void deleteNode(Tree *T, unsigned int ID) {
    if (*T == NULL) return;

    // If root matches
    if ((*T)->data.ID == ID) {
        Tree temp = *T;
        *T = (*T)->firstChild;
        free(temp);
        return;
    }

    // Check children
    Tree *trav = &((*T)->firstChild);
    while (*trav != NULL && (*trav)->data.ID != ID) {
        trav = &((*trav)->nextSibling);
    }

    if (*trav != NULL) {
        Tree temp = *trav;
        *trav = (*trav)->nextSibling;
        free(temp);
    }
}

// Display Tree (with indentation for levels)
void displayTree(Tree T, int level) {
    if (T != NULL) {
        // Indent based on level
        for (int i = 0; i < level; i++) {
            printf("  ");
        }
        
        // Display node data
        printf("ID: %u, Name: %s %s %c\n", 
               T->data.ID, 
               T->data.SName.FName,
               T->data.SName.LName,
               T->data.SName.MI);
        
        // Display children
        displayTree(T->firstChild, level + 1);
        
        // Display siblings
        displayTree(T->nextSibling, level);
    }
}

int main() {
    Tree myTree;
    initTree(&myTree);
    // Create test students
    studRec students[] = {
        {1001, {"John", "Doe", 'A'}, "BSCS", 1},
        {1002, {"Jane", "Smith", 'B'}, "BSIT", 2},
        {1003, {"Bob", "Johnson", 'C'}, "BSCS", 1},
        {1004, {"Alice", "Brown", 'D'}, "BSIT", 3},
        {1005, {"Charlie", "Wilson", 'E'}, "BSCS", 2}
    };
    // Insert students
    printf("Inserting students...\n");
    for(int i = 0; i < 5; i++) {
        insertNode(&myTree, students[i]);
    }
    // Display tree
    printf("\nTree Structure:\n");
    displayTree(myTree, 0);
    // Test isMember
    printf("\nTesting membership:\n");
    printf("Is ID 1003 a member? %s\n", isMember(myTree, 1003) ? "Yes" : "No");
    printf("Is ID 1006 a member? %s\n", isMember(myTree, 1006) ? "Yes" : "No");
    // Test deletion
    printf("\nDeleting student with ID 1003...\n");
    deleteNode(&myTree, 1003);
    printf("\nUpdated Tree Structure:\n");
    displayTree(myTree, 0);
    return 0;
}