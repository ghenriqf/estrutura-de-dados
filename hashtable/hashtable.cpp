#include <iostream>
using namespace std;

#define TAMANHO 11

struct Aluno
{
    int matricula;
    string nome;
};

struct Node
{
    Aluno aluno;
    Node *next;
};

struct HashTable
{
    Node *dados[TAMANHO];
};

int hash_function(int key)
{
    return key % TAMANHO;
}

void insert(Aluno aluno, HashTable *hash_table)
{
    int key = hash_function(aluno.matricula);

    Node *node = new Node;
    node->next = nullptr;
    node->aluno = aluno;

    node->next = hash_table->dados[key];
    hash_table->dados[key] = node;
}

void print_alunos(HashTable *hash_table)
{
    for (int i = 0; i < TAMANHO; i++)
    {
        Node *node = hash_table->dados[i];

        if (node == nullptr)
        {
            continue;
        }

        if (node->next != nullptr)
        {
            while (node->next != nullptr)
            {
                cout << node->aluno.nome << endl;
                node = node->next;
            }
        }

        cout << node->aluno.nome << endl;
    }
}

int main()
{
    HashTable *hash_table = (HashTable *)calloc(TAMANHO, sizeof(HashTable));

    Aluno aluno1 = {123, "Gabriel"};
    Aluno aluno2 = {456, "Henrique"};
    Aluno aluno3 = {789, "Freitas"};
    Aluno aluno4 = {101112, "Murilo"};
    Aluno aluno5 = {101112, "Pedro"};

    insert(aluno1, hash_table);
    insert(aluno2, hash_table);
    insert(aluno3, hash_table);
    insert(aluno4, hash_table);
    insert(aluno5, hash_table);

    print_alunos(hash_table);

    return 0;
}