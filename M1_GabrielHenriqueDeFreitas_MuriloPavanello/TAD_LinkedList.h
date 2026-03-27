#ifndef TAD_LINKEDLIST_H
#define TAD_LINKEDLIST_H

struct Node
{
    int data;
    Node *next;
};

struct LinkedList
{
    Node head;
};

struct Load
{
    int value;
};

bool insert_load(Load load, LinkedList *linked_list);
bool remove_load(int value, LinkedList *linked_list);

#endif