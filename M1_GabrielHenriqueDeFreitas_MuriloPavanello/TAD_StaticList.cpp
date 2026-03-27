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

bool insert_sensor(Sensor sensor, StaticList *static_list)
{
    if (static_list->elements_count >= static_list->capacity)
        return false;

    *(static_list->sensors + static_list->elements_count) = sensor;
    static_list->elements_count++;

    return true;
}

Sensor *remove_sensor(int value, StaticList *static_list)
{
    for (int i = 0; i <= static_list->elements_count; i++)
    {
        Sensor *sensor = static_list->sensors;

        if (sensor->value == value)
            return sensor;

        sensor++;
    }

    return nullptr;
}

void print_sensor(StaticList *static_list)
{
    for (int i = 0; i <= static_list->capacity; i++)
    {
        cout << static_list->sensors->value << endl;
    }
}

int main()
{

    StaticList *static_list = initialize_list(5);

    Sensor sensor;
    sensor.value = 10;

    insert_sensor(sensor, static_list);
    insert_sensor(sensor, static_list);
    insert_sensor(sensor, static_list);
    insert_sensor(sensor, static_list);
    insert_sensor(sensor, static_list);
    insert_sensor(sensor, static_list);
    insert_sensor(sensor, static_list);

    print_sensor(static_list);

    return 0;
}