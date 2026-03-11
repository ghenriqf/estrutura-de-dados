#ifndef LINKEDLIST
#define LINKEDLIST

struct Node
{
    int data;
    Node *next;
};

struct LinkedList
{
    Node *first;
};

LinkedList *create();
void insert();
void printList(LinkedList *list);

#endif