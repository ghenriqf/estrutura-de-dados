#include <iostream>
#include "linkedlist.h"

using namespace std;

LinkedList *create()
{
    LinkedList *list = (LinkedList *)calloc(1, sizeof(LinkedList));
    list->first = NULL;

    return list;
}

Node *createNode(int data)
{
    Node *node = (Node *)calloc(1, sizeof(Node));

    node->data = data;
    node->next = NULL;

    return node;
}

void insert(LinkedList *list, int data)
{
    Node *node = createNode(data);

    node->next = list->first;
    list->first = node;
}

void printList(LinkedList *list)
{
    Node *node = list->first;

    while (node != NULL)
    {
        cout << node->data << " ";
        node = node->next;
    }
}

int main()
{

    LinkedList *list = create();
    insert(list, 1);
    insert(list, 2);
    insert(list, 3);
    insert(list, 4);

    printList(list);
}