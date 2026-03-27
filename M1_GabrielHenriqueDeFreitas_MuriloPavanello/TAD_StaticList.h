#ifndef TAD_STATICLIST_H
#define TAD_STATICLIST_H

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

bool insert_sensor(Sensor sensor, StaticList *static_list);
bool remove_sensor(int value, StaticList *static_list);
StaticList *initialize_list(int capacity);

#endif