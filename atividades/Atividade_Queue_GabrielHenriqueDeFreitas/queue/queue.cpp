#include <iostream>

using namespace std;

struct Node
{
    string data;
    Node *next;
};

struct Queue
{
    Node *front;
    Node *rear;
};

void init(Queue *queue)
{
    queue->front = nullptr;
    queue->rear = nullptr;
}

void enqueue(Queue *queue, string data)
{
    Node *node = new Node;
    node->data = data;
    node->next = nullptr;

    if (queue->front == nullptr)
    {
        queue->front = node;
        queue->rear = node;
    }

    queue->rear->next = node;
    queue->rear = node;
}

void dequeue(Queue *queue)
{
    Node *front = queue->front;
    queue->front = front->next;

    delete front;
}

bool is_empty(Queue *queue)
{
    if (queue->front == nullptr)
        return true;

    return false;
}

void print_queue(Queue *queue)
{
    Node *node = queue->front;

    while (node != nullptr)
    {
        cout << node->data << " ";
        node = node->next;
    }
}

int main()
{
    Queue *queue = new Queue;

    init(queue);

    enqueue(queue, "Murilo");
    enqueue(queue, "Gabriel");

    print_queue(queue);
    dequeue(queue);
    cout << endl;
    print_queue(queue);
}