#include <stdio.h>
#include <stdlib.h>


typedef struct binTreeNode {
    int data;
    struct binTreeNode *left, *right;
} node;

// Construction + malloc for create node (helper method).
node* createNode(int d) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = d;
    newNode->left = NULL;
    newNode->right = NULL;
}

// Assigns root node if their is none, otherwise checks data and traverses list with recursion. Return root for pointer assignment in main.
node* insert(node* root, int d) {

    if (root == NULL) {
        return createNode(d);
    }
    if (d < root->data) {
        root->left = insert(root->left, d);
    } else if (d > root->data) {
        root->right = insert(root->right, d);
    }
    return root;
    
}

// Simple recursive search to move through either side of the tree, helper method used in called search method. 0(logN)
node* searchHelper(node* root, int d) {
    
    if (root == NULL || root->data == d) {
        return root;
    }
    if (root->data < d) {
        return searchHelper(root->right, d);
    }
    return searchHelper(root->left, d);
}

// Encapsulates if statement out of main for clean code.
void search(node* root, int d) {
    if (searchHelper(root, d) != NULL) {
        printf("Value %d found!\n",d);
    } else {
        printf("Value %d not found.\n",d);
    }
}

// Log tree data to console 'in-order' --> data in order.
void inOrderTraversal(node* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf(" %d ", root->data);
        inOrderTraversal(root->right);
    }
}

// Log tree data to console 'pre-order' --> root first, then left, then right.
void preOrderTraversal(node* root) {
    if (root != NULL) {
        printf(" %d ", root->data);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

// Log tree data to console 'post-order' --> left, right, root last.
void postOrderTraversal(node* root) {
    if (root != NULL) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        printf(" %d ", root->data);
    }
}

// Helper method to find min value in the delete function.
node* findMin(node* root)
{
    if (root == NULL) {
        return NULL;
    }
    else if (root->left != NULL) {
        return findMin(root->left);
    }
    return root;
}

// Safely removes value from tree, freeing memory, and re-arranging tree structure.
node* deleteHelper(node* root, int d) {
    
    // Tree is empty, do nothing.
    if (root == NULL) {
        return NULL;
    }

    // Recursive traversal and pointer updates.
    if (root->data < d) {
        root->right = deleteHelper(root->right, d);
    } else if (root->data > d) {
        root->left = deleteHelper(root->left, d);
    } else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left == NULL || root->right == NULL) {
            node* temp;
            if (root->left == NULL) {
                temp = root->right;
            } else {
                temp = root->left;
            }
            free(root);
            return temp;
        } else {
            node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteHelper(root->right, temp->data);
        }
    }
    return root;
}

// Delete method to handle feedback to console, using delete helper method.
void delete(node* root, int d) {
    if (root == NULL) {
        printf("Tree is empty. Cannot delete value.\n");
        return;
    }

    // Check if value exists before deletion.
    node* target = searchHelper(root, d);
    if (target == NULL) {
        printf("Value %d not found in the tree.\n", d);
        return;
    }

    root = deleteHelper(root, d);
    printf("Value %d deleted from the tree.\n", d);
}

// Recursive method to clean up memory for entire tree (root last).
void freeTree(node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {

    node* root = NULL;

    root = insert(root, 100);
    insert(root, 130);
    insert(root, 20);
    insert(root, 440);
    insert(root, 270);
    insert(root, 60);
    insert(root, 10);

    search(root, 10);
    search(root, 1000);

    inOrderTraversal(root); printf("\n");

    delete(root, 10);
    delete(root, 400);
    delete(root, 100);

    inOrderTraversal(root); printf("\n");
    // postOrderTraversal(root); printf("\n");
    // preOrderTraversal(root); printf("\n");

    freeTree(root);

    return 0;

}