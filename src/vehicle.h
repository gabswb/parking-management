#ifndef VEHICLE_H
#define VEHICLE_H

#include <stdbool.h>
#include <stdlib.h>
#include "util.h"

#define MIN_PARKING_TIME 5
#define MAX_PARKING_TIME 50

struct vehicle
{
    int id;
    bool is_sub;
    int parking_time;
};
typedef struct vehicle vehicle_t;

//return new vehicle_t with random attributes
vehicle_t new_random_vehicle(int _id);
//return new vehicle_t with attributes in parameters
vehicle_t new_vehicle(int _id, bool _is_sub, int _parking_time);

//return an array of random vehicules_t
vehicle_t* random_sample_vehicle(int n_sub, int n_not_sub);
//delete the array given in parameters
void delete_sample_vehicule(vehicle_t* sample);

#endif /*VEHICLE_H*/