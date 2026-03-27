#ifndef TAD_StaticList
#define TAD_StaticList

typedef struct Sensor
{
    int value;
};

typedef struct StaticList
{
    int capacity;
    Sensor *sensors;
    int elements_count;
};

bool insert_sensor(Sensor sensor, StaticList *static_list);
bool remove_sensor(int value, StaticList *static_list);
StaticList *initialize_list(int capacity);

#endif