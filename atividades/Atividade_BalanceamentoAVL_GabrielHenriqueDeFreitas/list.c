#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* insert(Node *head, int value) {
    Node *temp = (Node*) malloc(sizeof(Node));
    temp->data = value;

    temp->next = head;
    head = temp;

    return temp;
}

Node* search(Node *head, int value) {
    Node *current = head;

    while (current != NULL) {

        if (current->data == value) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

void print_list(Node *head) {
    Node *current = head;
    while (current) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void free_list(Node *head) {
    Node *temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}