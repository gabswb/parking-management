#include "vehicle.h"

void fn_vehicle(void* arg){

    vehicle_t vehicle = *(vehicle_t*) arg;
    printf("entering ");
    print_vehicle(vehicle);
    if(vehicle.is_sub) {
        fn_sub_vehicle(&vehicle);
        return;
    }

    fn_notsub_vehicle(&vehicle);
}

void fn_sub_vehicle(vehicle_t* vehicle){

    char* v_name = vehicle_to_string(*vehicle);

    pthread_mutex_lock(&mutex_sub);
    if(n_sub_place > 0)
    {
        pthread_mutex_unlock(&mutex_sub);

        pthread_mutex_lock(&mutex_entering);
        n_entering++;
        pthread_mutex_unlock(&mutex_entering);

    printf("%s want to enter in the parking\n", v_name);


        pthread_mutex_lock(&mutex_gateway);
        while(n_gateway > 0) //while() ?
        { 
            pthread_cond_wait(&cond_entering, &mutex_gateway);
        }
    printf("Green light for %s\n", v_name);
        n_gateway++;
    printf("%s is in the gateway ...\n", v_name);
        sleep(2); //time in gateway ...
        n_gateway--;

        pthread_mutex_unlock(&mutex_gateway);

        pthread_mutex_lock(&mutex_sub);
        n_sub_place--;
    printf("%s is parked\n", v_name);
        pthread_mutex_unlock(&mutex_sub);

        pthread_mutex_lock(&mutex_entering);
        n_entering--;
        pthread_mutex_unlock(&mutex_entering);

        pthread_mutex_lock(&mutex_leaving);
        pthread_mutex_lock(&mutex_entering);
        if(n_leaving > 0)//priority to leaving cars
        {
            pthread_cond_signal(&cond_leaving);
            pthread_mutex_unlock(&mutex_entering);
            pthread_mutex_unlock(&mutex_leaving);
        }
        else if(n_entering > 0)
        {
            pthread_cond_signal(&cond_entering);
            pthread_mutex_unlock(&mutex_entering);
            pthread_mutex_unlock(&mutex_leaving);      
        }


        //--------------------------------
        sleep(5); // stay park ...
        //--------------------------------

    printf("%s wants to leave in the parking\n", v_name);


        pthread_mutex_lock(&mutex_leaving);
        n_leaving++;
        pthread_mutex_unlock(&mutex_leaving);

        pthread_mutex_lock(&mutex_gateway);
        while(n_gateway > 0) //while() ?
        { 
            pthread_cond_wait(&cond_entering, &mutex_gateway);
        }

    printf("Green light for %s\n", v_name);
        n_gateway++;
    printf("%s is in the gateway ...\n", v_name);        
        sleep(2); //time in gateway ...
        n_gateway--;

        pthread_mutex_unlock(&mutex_gateway);

        pthread_mutex_lock(&mutex_leaving);
        n_leaving--;
        pthread_mutex_unlock(&mutex_leaving);

        pthread_mutex_lock(&mutex_sub);
        n_sub_place++;
        pthread_mutex_unlock(&mutex_sub);

    printf("%s is out\n", v_name);   

        pthread_mutex_lock(&mutex_leaving);
        pthread_mutex_lock(&mutex_entering);
        if(n_leaving > 0)//priority to leaving cars
        {
            pthread_cond_signal(&cond_leaving);
            pthread_mutex_unlock(&mutex_entering);
            pthread_mutex_unlock(&mutex_leaving);
        }
        else if(n_entering > 0)
        {
            pthread_cond_signal(&cond_entering);
            pthread_mutex_unlock(&mutex_entering);
            pthread_mutex_unlock(&mutex_leaving);      
        }
    }
    
    return;
}

void fn_notsub_vehicle(vehicle_t* vehicle){

    pthread_mutex_lock(&mutex_notsub);
    if(n_notsub_place > 0)
    {
        pthread_mutex_unlock(&mutex_notsub);

        pthread_mutex_lock(&mutex_entering);
        n_entering++;
        pthread_mutex_unlock(&mutex_leaving);

        pthread_mutex_lock(&mutex_gateway);
        while(n_gateway > 0)
        {
            pthread_cond_wait(&cond_entering, &mutex_gateway);
        }
        
        n_gateway++;
        sleep(2); //time in gateway ...
        n_gateway--;

        pthread_mutex_unlock(&mutex_gateway);

        pthread_mutex_lock(&mutex_notsub);
        n_notsub_place--;
        pthread_mutex_unlock(&mutex_notsub);

        pthread_mutex_lock(&mutex_entering);
        n_entering++;
        pthread_mutex_unlock(&mutex_entering);

        pthread_mutex_lock(&mutex_leaving);
        pthread_mutex_lock(&mutex_entering);
        if(n_leaving > 0)//priority to leaving cars
        {
            pthread_cond_signal(&cond_leaving);
            pthread_mutex_unlock(&mutex_entering);
            pthread_mutex_unlock(&mutex_leaving);
        }
        else if(n_entering > 0)
        {
            pthread_cond_signal(&cond_entering);
            pthread_mutex_unlock(&mutex_entering);
            pthread_mutex_unlock(&mutex_leaving);      
        }

        //--------------------------------
        sleep(5); // stay park ...
        //--------------------------------


        pthread_mutex_lock(&mutex_leaving);
        n_leaving++;
        pthread_mutex_unlock(&mutex_leaving);

        pthread_mutex_lock(&mutex_gateway);
        while(n_gateway > 0)
        {
            pthread_cond_wait(&cond_leaving, &mutex_gateway);
        }
        
        n_gateway++;
        sleep(2);
        n_gateway--;

        pthread_mutex_unlock(&mutex_gateway);

        pthread_mutex_lock(&mutex_leaving);
        n_leaving--;
        pthread_mutex_unlock(&mutex_leaving);

        pthread_mutex_lock(&mutex_notsub);
        n_notsub_place++;
        pthread_mutex_unlock(&mutex_notsub);

        pthread_mutex_lock(&mutex_leaving);
        pthread_mutex_lock(&mutex_entering);
        if(n_leaving > 0)//priority to leaving cars
        {
            pthread_cond_signal(&cond_leaving);
            pthread_mutex_unlock(&mutex_entering);
            pthread_mutex_unlock(&mutex_leaving);
        }
        else if(n_entering > 0)
        {
            pthread_cond_signal(&cond_entering);
            pthread_mutex_unlock(&mutex_entering);
            pthread_mutex_unlock(&mutex_leaving);      
        }
    }

    //pas de place dans le parking

}


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