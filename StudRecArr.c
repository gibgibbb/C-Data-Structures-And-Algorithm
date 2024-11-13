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
} studRec;

// Tree using Parent Pointer Array Implementation
typedef struct {
    studRec data;
    int parent;     // Index of parent (-1 if root)
    int childCount; // Number of children
} TreeNode;

typedef struct {
    TreeNode nodes[MAX];
    int count;      // Number of nodes in tree
} ParentTree;

// Function Prototypes
void initTree(ParentTree *T);
int insertNode(ParentTree *T, studRec newStud, int parentIndex);
int isMember(ParentTree T, unsigned int ID);
void deleteNode(ParentTree *T, unsigned int ID);
void displayTree(ParentTree T);
int findIndex(ParentTree T, unsigned int ID);
void displayNode(ParentTree T, int index, int level);

// Initialize Tree
void initTree(ParentTree *T) {
    T->count = 0;
}

// Find index of a node with given ID
int findIndex(ParentTree T, unsigned int ID) {
    int result = -1;
    for(int i = 0; i < T.count; i++) {
        if(T.nodes[i].data.ID == ID) {
            result = i;
        }
    }
    return result;
}

// Insert Node
int insertNode(ParentTree *T, studRec newStud, int parentIndex) {
    // Check if tree is full
    if(T->count >= MAX) {
        printf("\nTree is full!");
        return 0;
    }
    
    // Check if ID already exists
    if(isMember(*T, newStud.ID)) {
        printf("\nID already exists!");
        return 0;
    }
    
    // Create new node
    int newIndex = T->count;
    T->nodes[newIndex].data = newStud;
    T->nodes[newIndex].parent = parentIndex;
    T->nodes[newIndex].childCount = 0;
    
    // Update parent's child count
    if(parentIndex != -1) {
        T->nodes[parentIndex].childCount++;
    }
    T->count++;
    return 1;
}

// Check if ID exists in tree
int isMember(ParentTree T, unsigned int ID) {
    return findIndex(T, ID) != -1;
}

// Delete Node
void deleteNode(ParentTree *T, unsigned int ID) {
    int index = findIndex(*T, ID);
    if(index == -1) return;
    
    // Can't delete if node has children
    if(T->nodes[index].childCount > 0) {
        printf("\nCannot delete node with children!");
        return;
    }
    
    // Update parent's child count
    if(T->nodes[index].parent != -1) {
        T->nodes[T->nodes[index].parent].childCount--;
    }
    
    // Move last node to deleted position if not last node
    if(index != T->count - 1) {
        T->nodes[index] = T->nodes[T->count - 1];
        
        // Update parent references
        for(int i = 0; i < T->count; i++) {
            if(T->nodes[i].parent == T->count - 1) {
                T->nodes[i].parent = index;
            }
        }
    }
    T->count--;
}

// Display single node with indentation
void displayNode(ParentTree T, int index, int level) {
    // Print indentation
    for(int i = 0; i < level; i++) {
        printf("  ");
    }
    
    // Print node data
    printf("ID: %u, Name: %s %s %c\n", 
           T.nodes[index].data.ID,
           T.nodes[index].data.SName.FName,
           T.nodes[index].data.SName.LName,
           T.nodes[index].data.SName.MI);
    
    // Print children
    for(int i = 0; i < T.count; i++) {
        if(T.nodes[i].parent == index) {
            displayNode(T, i, level + 1);
        }
    }
}

// Display entire tree
void displayTree(ParentTree T) {
    printf("\nTree Structure:\n");
    // Display nodes with root (parent = -1) first
    for(int i = 0; i < T.count; i++) {
        if(T.nodes[i].parent == -1) {
            displayNode(T, i, 0);
        }
    }
}

int main() {
    ParentTree myTree;
    initTree(&myTree);
    
    // Create test students
    studRec students[] = {
        {1001, {"John", "Doe", 'A'}, "BSCS", 1},
        {1002, {"Jane", "Smith", 'B'}, "BSIT", 2},
        {1003, {"Bob", "Johnson", 'C'}, "BSCS", 1},
        {1004, {"Alice", "Brown", 'D'}, "BSIT", 3},
        {1005, {"Charlie", "Wilson", 'E'}, "BSCS", 2}
    };
    
    // Insert root
    printf("Inserting root...\n");
    insertNode(&myTree, students[0], -1);
    
    // Insert children
    printf("Inserting children...\n");
    for(int i = 1; i < 5; i++) {
        insertNode(&myTree, students[i], 0); // All children of root
    }
    
    // Display tree
    displayTree(myTree);
    
    // Test isMember
    printf("\nTesting membership:\n");
    printf("Is ID 1003 a member? %s\n", isMember(myTree, 1003) ? "Yes" : "No");
    printf("Is ID 1006 a member? %s\n", isMember(myTree, 1006) ? "Yes" : "No");
    
    // Test deletion
    printf("\nDeleting student with ID 1004...\n");
    deleteNode(&myTree, 1004);
    
    printf("\nUpdated Tree Structure:");
    displayTree(myTree);
    
    return 0;
}