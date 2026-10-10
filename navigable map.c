#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for an AVL Tree node representing a map entry
typedef struct AVLNode {
    int key;
    char value[50];
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

// Utility function to get maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Get the height of a node
int height(AVLNode* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Create a new node
AVLNode* createNode(int key, const char* value) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->key = key;
    strcpy(node->value, value);
    node->height = 1; // New node is initially added at leaf
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Right rotate subtree rooted with y
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Left rotate subtree rooted with x
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Get balance factor of node N
int getBalance(AVLNode* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Insert a key-value pair into the AVL tree
AVLNode* insert(AVLNode* node, int key, const char* value, int* updated) {
    // 1. Perform normal BST insertion
    if (node == NULL)
        return createNode(key, value);

    if (key < node->key) {
        node->left = insert(node->left, key, value, updated);
    } else if (key > node->key) {
        node->right = insert(node->right, key, value, updated);
    } else {
        // Key already exists, update value
        strcpy(node->value, value);
        *updated = 1;
        return node;
    }

    // 2. Update height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // 3. Get the balance factor to check whether this node became unbalanced
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// In-order traversal to print map sorted by key
void inorder(AVLNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("Key: %d => Value: %s\n", root->key, root->value);
        inorder(root->right);
    }
}

// Navigation Methods:
// Floor Key: Greatest key <= target
AVLNode* floorKeyNode(AVLNode* root, int target) {
    AVLNode* current = root;
    AVLNode* result = NULL;
    while (current != NULL) {
        if (current->key == target)
            return current;
        if (current->key < target) {
            result = current; // Could be our floor, search right for something closer
            current = current->right;
        } else {
            current = current->left;
        }
    }
    return result;
}

// Ceiling Key: Least key >= target
AVLNode* ceilingKeyNode(AVLNode* root, int target) {
    AVLNode* current = root;
    AVLNode* result = NULL;
    while (current != NULL) {
        if (current->key == target)
            return current;
        if (current->key > target) {
            result = current; // Could be our ceiling, search left for something closer
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return result;
}

// Lower Key: Greatest key < target
AVLNode* lowerKeyNode(AVLNode* root, int target) {
    AVLNode* current = root;
    AVLNode* result = NULL;
    while (current != NULL) {
        if (current->key < target) {
            result = current;
            current = current->right;
        } else {
            current = current->left;
        }
    }
    return result;
}

// Higher Key: Least key > target
AVLNode* higherKeyNode(AVLNode* root, int target) {
    AVLNode* current = root;
    AVLNode* result = NULL;
    while (current != NULL) {
        if (current->key > target) {
            result = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return result;
}

int main() {
    AVLNode* root = NULL;
    int choice;

    printf("=== C NavigableMap (AVL Tree) Interactive CLI ===\n");

    while (1) {
        printf("\nSelect an operation:\n");
        printf("1. Insert Key-Value Pair\n");
        printf("2. View Entire Map (Sorted by Key)\n");
        printf("3. Test Navigation Methods (Floor, Ceiling, Lower, Higher)\n");
        printf("4. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) break;

        if (choice == 1) {
            int key;
            char value[50];
            printf("Enter integer key: ");
            scanf("%d", &key);
            printf("Enter string value: ");
            scanf("%s", value);

            int updated = 0;
            root = insert(root, key, value, &updated);
            if (updated)
                printf("Updated key %d with value: %s\n", key, value);
            else
                printf("Inserted: (%d -> %s)\n", key, value);

        } else if (choice == 2) {
            printf("\nCurrent Navigable Map (Sorted):\n");
            if (root == NULL) {
                printf("Map is empty.\n");
            } else {
                inorder(root);
            }

        } else if (choice == 3) {
            if (root == NULL) {
                printf("Map is empty. Insert items first.\n");
                continue;
            }
            int target;
            printf("Enter target key for navigation lookup: ");
            scanf("%d", &target);

            printf("\n--- Navigation Results for Target: %d ---\n", target);

            AVLNode* f = floorKeyNode(root, target);
            printf("Floor Key (<= target): %s\n", f ? "" : "None");
            if (f) printf(" -> %d (%s)\n", f->key, f->value);

            AVLNode* c = ceilingKeyNode(root, target);
            printf("Ceiling Key (>= target): %s\n", c ? "" : "None");
            if (c) printf(" -> %d (%s)\n", c->key, c->value);

            AVLNode* l = lowerKeyNode(root, target);
            printf("Lower Key (< target): %s\n", l ? "" : "None");
            if (l) printf(" -> %d (%s)\n", l->key, l->value);

            AVLNode* h = higherKeyNode(root, target);
            printf("Higher Key (> target): %s\n", h ? "" : "None");
            if (h) printf(" -> %d (%s)\n", h->key, h->value);

        } else if (choice == 4) {
            printf("Exiting program.\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
