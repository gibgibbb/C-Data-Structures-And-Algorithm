#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
    int height;  // New field for AVL
} NodeType, *AVL;

// Helper functions
int getHeight(AVL node) {
    return (node == NULL) ? 0 : node->height;
}

int getBalance(AVL node) {
    return (node == NULL) ? 0 : getHeight(node->left) - getHeight(node->right);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Rotation functions
AVL rightRotate(AVL y) {
    AVL x = y->left;
    AVL T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

AVL leftRotate(AVL x) {
    AVL y = x->right;
    AVL T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

//Insertion
AVL insert(AVL node, int data) {
    // Create a new node if the current position is NULL
    if (node == NULL) {
        AVL newNode = (AVL)malloc(sizeof(NodeType));
        if (newNode != NULL) {
            newNode->data = data;
            newNode->left = NULL;
            newNode->right = NULL;
            newNode->height = 1;
        }
        return newNode; // Return the newly created node
    }

    // Perform normal BST insertion
    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else // Equal keys not allowed
        return node; // No changes made

    // Update height
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    // Get balance factor
    int balance = getBalance(node);

    // Balance the tree if needed
    if (balance > 1 && data < node->left->data)
        node = rightRotate(node); // Left Left Case
    else if (balance < -1 && data > node->right->data)
        node = leftRotate(node); // Right Right Case
    else if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left); // Left Right Case
        node = rightRotate(node);
    } else if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right); // Right Left Case
        node = leftRotate(node);
    }

    // Return the updated node pointer
    return node;
}

// Find minimum value node in AVL tree
AVL minValueNode(AVL node) {
    AVL current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Delete operation
AVL delete(AVL root, int data) {
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = delete(root->left, data);
    else if (data > root->data)
        root->right = delete(root->right, data);
    else {
        // Node with only one child or no child
        if (root->left == NULL || root->right == NULL) {
            AVL temp = root->left ? root->left : root->right;
            
            if (temp == NULL) { // No child case
                temp = root;
                root = NULL;
            } else // One child case
                *root = *temp; // Copy contents
            
            free(temp);
        } else {
            // Node with two children
            AVL temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = delete(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    // Update height
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    // Check balance
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Search operation
AVL search(AVL root, int data) {
    if (root == NULL || root->data == data)
        return root;
    
    if (data < root->data)
        return search(root->left, data);
    
    return search(root->right, data);
}

// Traversal functions (same as BST)
void inOrder(AVL root) {
    if(root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

void display(AVL root) {
    printf("\nIn-order traversal: ");
    inOrder(root);
    printf("\n");
}

int main() {
    AVL root = NULL;
    
    // Insert some values
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);
    
    printf("AVL Tree after insertions:");
    display(root);
    
    // Delete a node
    root = delete(root, 30);
    printf("\nAVL Tree after deleting 30:");
    display(root);
    
    // Search for a value
    int searchValue = 25;
    AVL result = search(root, searchValue);
    if(result != NULL)
        printf("\nValue %d found in the tree!", searchValue);
    else
        printf("\nValue %d not found in the tree!", searchValue);
    
    return 0;
}