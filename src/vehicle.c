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

vehicle_t* random_sample_vehicle(size_t n_sub, size_t n_not_sub){


    vehicle_t* sample = malloc(sizeof(*sample) * (n_sub+n_not_sub));
    if(sample == NULL) exit(EXIT_FAILURE);//security for malloc
    
    for(size_t i=0; i< n_sub+n_not_sub; i++){
        sample[i] = new_random_vehicle((int) i);
    }
    
    return sample;
}

void delete_vehicles(vehicle_t* sample){
    free(sample);
}

void print_vehicle(vehicle_t v){
    printf("vehicle {id = %d, %s, %d}\n",v.id, v.is_sub ? "sub" : "not sub", v.parking_time);
}

char* vehicle_to_string(vehicle_t v){
    char* buffer = malloc(sizeof(char)*256);
    sprintf(buffer, "vehicle {id = %d, %s, %d}",v.id, v.is_sub ? "sub" : "not sub", v.parking_time);
    return buffer; 
}

void print_vehicles(size_t size, vehicle_t* vehicles){
    for(size_t i=0; i<size; i++){
        print_vehicle(vehicles[i]);
    }
}

//random int between [min, max[
int random_int(int min, int max){
  return(min + (rand() % (max - min)));
}

bool random_bool(){
    if(random_int(0,2)) return true;
    return false;
}