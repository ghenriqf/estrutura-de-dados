#include <iostream>

using namespace std;

struct Sensor
{
    int value;
};

struct StaticList
{
    int capacity;
    Sensor *sensors;
    int elements_count;
};

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

int main()
{

    return 0;
}