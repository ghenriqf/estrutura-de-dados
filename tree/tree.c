#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;

    struct Node* left;
    struct Node* right;
} Node;

Node *insert(Node *root, int value) {
    Node* temp = (Node*) malloc(sizeof(Node));

    temp->data = value;
    temp->left = NULL;
    temp->right = NULL;

    if (root == NULL) {
        root = temp;
    } else {
        Node *current = root;
        Node *parent = NULL;

        while (1) {
            parent = current;

            if (value < parent->data) {
                current = current->left;


                if (current == NULL) {
                    parent->left = temp;
                    return root;
                }
            } else {
                current = current->right;

                if (current == NULL) {
                    parent->right = temp;
                    return root;
                }
            }
            
        }
        
    }

    return root;
}

Node *search(Node *root, int value) {
    Node* current = root;

    while (current) {
        if (value < current->data) {
            current = current->left;

        } else if (value > current->data) {
            current = current->right;

        } else {
            return current;
        }
    }
    
}

void inorder(Node* root) {
    if(root) {
        inorder_traversal(root->left);
        printf("%d ", root->data);
        inorder_traversal(root->right);
    }
}