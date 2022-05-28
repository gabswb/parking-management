#include "vehicle.h"

vehicle_t new_random_vehicle(int _id){
    return (vehicle_t) {.id = _id,
                        .is_sub = random_bool(),
                        .parking_time = random_int(MIN_PARKING_TIME, MAX_PARKING_TIME)};
}

vehicle_t new_vehicle(int _id, bool _is_sub, int _parking_time){
    return (vehicle_t) {.id = _id,
                        .is_sub = _is_sub,
                        .parking_time = _parking_time};

}

vehicle_t* random_sample_vehicle(int n_sub, int n_not_sub){

    vehicle_t* sample = malloc(sizeof(sample) * (n_sub+n_not_sub));
    if(sample == NULL) exit(EXIT_FAILURE);//security for malloc
    
    for(int i=0; i< n_sub+n_not_sub; i++){
        sample[i] = new_random_vehicle(i);
    }

    return sample;
}

void delete_sample_vehicule(vehicle_t* sample){
    free(sample);
}

