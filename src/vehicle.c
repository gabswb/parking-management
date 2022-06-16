#include "vehicle.h"

void fn_vehicle(void* arg)
{
    vehicle_t vehicle = *(vehicle_t*) arg;
    sleep(vehicle.arrival_time); //sleep to simulate the arrival time   
    char* v_name = vehicle_to_string(vehicle);

    if(vehicle.is_sub){
        pthread_mutex_lock(&mutex_private);
        if(n_private_place > 0){
            pthread_mutex_unlock(&mutex_private);

            enter_parking(&vehicle, true);
            sleep(vehicle.parking_time);//start parked ...
            leave_parking(&vehicle, true);
            
            free(v_name);
            return;//if the sub vehicle could find a place, no need to continue function
        }
        print_info("No place available for %s\n", v_name);
        pthread_mutex_unlock(&mutex_private);
    }

    pthread_mutex_lock(&mutex_public);
    if(n_public_place > 0){
        pthread_mutex_unlock(&mutex_public);
        enter_parking(&vehicle, true);
        sleep(vehicle.parking_time); // stay parked ...
        leave_parking(&vehicle, true);
    }
    else{
        pthread_mutex_unlock(&mutex_public);
        print_info("No place available for %s\n", v_name);
    }

    free(v_name);
}


void enter_parking(vehicle_t* vehicle, bool private_place){

    char* v_name = vehicle_to_string(*vehicle);

    pthread_mutex_lock(&mutex_entering);
    n_entering++;
    pthread_mutex_unlock(&mutex_entering);
    print_info("%s wants to enter in the parking\n", v_name);


    pthread_mutex_lock(&mutex_gateway);
    while(n_gateway > 0)
    { 
        pthread_cond_wait(&cond_entering, &mutex_gateway);
    }
    print_info("\nGreen light for %s\n\n", v_name);
    n_gateway++;
    pthread_mutex_unlock(&mutex_gateway);


    //-----------------------------------------------
    print_info("%s is in the gateway ...\n", v_name);
    sleep(2); //time in gateway ...
    //-----------------------------------------------


    if(private_place){
        pthread_mutex_lock(&mutex_private);
        n_private_place--;
        pthread_mutex_unlock(&mutex_private);
    }
    else{
        pthread_mutex_lock(&mutex_public);
        n_public_place--;
        pthread_mutex_unlock(&mutex_public);
    }
    pthread_mutex_lock(&mutex_gateway);
    pthread_mutex_lock(&mutex_entering);
    n_entering--;
    n_gateway--;
    print_info("%s out of the gateway ...\n", v_name);
    pthread_mutex_unlock(&mutex_gateway);
    pthread_mutex_unlock(&mutex_entering);

    print_info("%s is parked\n", v_name);
    pthread_mutex_lock(&mutex_leaving);
    pthread_mutex_lock(&mutex_entering);
    if(n_leaving > 0)//priority to leaving cars
    {
        verbose("%s signal to leaving\n", v_name);
        pthread_cond_signal(&cond_leaving);
    }
    else if(n_entering > 0)
    {
        verbose("%s signal to entering\n", v_name);
        pthread_cond_signal(&cond_entering);     
    }
    pthread_mutex_unlock(&mutex_entering);
    pthread_mutex_unlock(&mutex_leaving); 

    free(v_name);
}


void leave_parking(vehicle_t* vehicle, bool private_place){

    char* v_name = vehicle_to_string(*vehicle);


    print_info("%s wants to leave in the parking\n", v_name);
    pthread_mutex_lock(&mutex_leaving);
    n_leaving++;
    pthread_mutex_unlock(&mutex_leaving);

    pthread_mutex_lock(&mutex_gateway);
    while(n_gateway > 0) //while() ?
    { 
        pthread_cond_wait(&cond_leaving, &mutex_gateway);
    }
    print_info("\nGreen light for %s\n\n", v_name);
    n_gateway++;
    pthread_mutex_unlock(&mutex_gateway);//important pour que le mutex ne fasse pas office de synchronisation



    //-----------------------------------------------
    print_info("%s is in the gateway ...\n", v_name);      
    sleep(2); //time in gateway ...
    //-----------------------------------------------


    if(private_place){
        pthread_mutex_lock(&mutex_private);
        n_private_place++;
        pthread_mutex_unlock(&mutex_private);
    }
    else{
        pthread_mutex_lock(&mutex_public);
        n_public_place++;
        pthread_mutex_unlock(&mutex_public);
    }
    pthread_mutex_lock(&mutex_gateway);
    pthread_mutex_lock(&mutex_leaving);
    n_gateway--;
    n_leaving--;
    print_info("%s out of the gateway ...\n", v_name);
    pthread_mutex_unlock(&mutex_gateway);
    pthread_mutex_unlock(&mutex_leaving);


    print_info("%s is out\n", v_name);   
    pthread_mutex_lock(&mutex_leaving);
    pthread_mutex_lock(&mutex_entering);
    if(n_leaving > 0)//priority to leaving cars
    {
        verbose("%s signal to leaving\n", v_name);
        pthread_cond_signal(&cond_leaving);
    }
    else if(n_entering > 0)
    {
        verbose("%s signal to entering\n", v_name);       
        pthread_cond_signal(&cond_entering);      
    }
    pthread_mutex_unlock(&mutex_entering);
    pthread_mutex_unlock(&mutex_leaving);

    free(v_name);
}



bool Verbose = false;

void verbose(const char* format, ...){
    if(!Verbose) return;

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    fflush(stdout);
    va_end(args);
}

vehicle_t new_random_vehicle(int _id){
    return (vehicle_t) {.id = _id,
                        .is_sub = random_bool(),
                        .parking_time = random_int(MIN_PARKING_TIME, MAX_PARKING_TIME),
                        .arrival_time = random_int(MIN_ARRIVAL_TIME, MAX_ARRIVAL_TIME)};
}

vehicle_t new_vehicle(int _id, bool _is_sub, int _parking_time, int _arrival_time){
    return (vehicle_t) {.id = _id,
                        .is_sub = _is_sub,
                        .parking_time = _parking_time,
                        .arrival_time = _arrival_time};
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
    if(Verbose) print_info("vehicle [id = %d, %s, arrival=%d, park_time=%d]\n",v.id, v.is_sub ? "sub" : "not sub", v.arrival_time, v.parking_time);
    else print_info("vehicle [id = %d, %s]\n",v.id, v.is_sub ? "sub" : "not sub");
}

char* vehicle_to_string(vehicle_t v){
    char* buffer = malloc(sizeof(char)*256);

    if(Verbose) sprintf(buffer, "vehicle [id = %d, %s, arrival=%d, park_time=%d]",v.id, v.is_sub ? "sub" : "not sub", v.arrival_time, v.parking_time);
    else sprintf(buffer, "vehicle [id = %d, %s]",v.id, v.is_sub ? "sub" : "not sub");

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

void print_info(const char* format, ...){
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    fflush(stdout);
    va_end(args);
}