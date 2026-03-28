#include <iostream>
#include "TAD_LinkedList.h"

using namespace std;

LinkedList *initialize_linked_list()
{
    LinkedList *linked_list = new LinkedList;
    linked_list->head = nullptr;

    return linked_list;
}

void insert_load(Load load, LinkedList *linked_list)
{
    Node *node = new Node;
    node->load = load;

    if (linked_list->head == nullptr)
    {
        linked_list->head = node;
        return;
    }

    node->next = linked_list->head;
    linked_list->head = node;
}

bool remove_load(int value, LinkedList *linked_list)
{
    Node *head = linked_list->head;

    while (true)
    {
        if (head->load.value == value)
        {
        
        }
    }
}