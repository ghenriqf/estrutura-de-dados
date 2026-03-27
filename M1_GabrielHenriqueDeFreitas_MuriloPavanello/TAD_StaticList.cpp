#include <iostream>
#include "TAD_StaticList.h"

using namespace std;

StaticList *initialize_list(int capacity)
{
    if (capacity <= 0)
        return nullptr;

    StaticList *static_list = new StaticList;

    static_list->capacity = capacity;
    static_list->elements_count = 0;
    static_list->sensors = new Sensor[static_list->capacity];

    return static_list;
}

bool insert_sensor(Sensor sensor, StaticList *static_list)
{
    if (static_list->elements_count >= static_list->capacity)
        return false;

    *(static_list->sensors + static_list->elements_count) = sensor;
    static_list->elements_count++;

    return true;
}

bool remove_sensor(int value, StaticList *static_list)
{
    for (int i = 0; i < static_list->elements_count; i++)
    {
        if (static_list->sensors[i].value == value)
        {
            for (int j = i; j < static_list->elements_count - 1; j++)
            {
                static_list->sensors[j] = static_list->sensors[j + 1];
            }

            static_list->elements_count--;
            return true;
        }
    }
    return false;
}

void print_sensor(StaticList *static_list)
{
    for (int i = 0; i < static_list->elements_count; i++)
    {
        cout << static_list->sensors[i].value << endl;
    }
}