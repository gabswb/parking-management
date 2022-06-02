#ifndef VEHICLE_H
#define VEHICLE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "global.h"

#define MIN_PARKING_TIME 5
#define MAX_PARKING_TIME 50

struct vehicle
{
    int id;
    bool is_sub;
    int parking_time;

    pthread_t thread;
};
typedef struct vehicle vehicle_t;


//return new vehicle_t with random attributes
vehicle_t new_random_vehicle(int _id);
//return new vehicle_t with attributes in parameters
vehicle_t new_vehicle(int _id, bool _is_sub, int _parking_time);

//return an array of random vehicules_t
vehicle_t* random_sample_vehicle(size_t n_sub, size_t n_not_sub);
//delete the array given in parameters
void delete_vehicles(vehicle_t* sample);

void print_vehicle(vehicle_t vehicle);
void print_vehicles(size_t size, vehicle_t* vehicles);

char* vehicle_to_string(vehicle_t vehicle);

//return random integer
int random_int(int min, int max);

//return random boolean
bool random_bool();

#endif /*VEHICLE_H*/