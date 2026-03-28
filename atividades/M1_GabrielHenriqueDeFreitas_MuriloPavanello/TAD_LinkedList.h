#ifndef TAD_LINKEDLIST_H
#define TAD_LINKEDLIST_H

struct Node
{
    Load load;
    Node *next;
};

struct LinkedList
{
    Node *head;
};

struct Load
{
    int value;
};

void insert_load(Load load, LinkedList *linked_list);
bool remove_load(int value, LinkedList *linked_list);
LinkedList *initialize_linked_list();

#endif