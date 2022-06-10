#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "clock.h"

size_t n_private_place = 10;    
size_t n_public_place = 20;

size_t n_sub_vehicle = 12;
size_t n_notsub_vehicle = 23;

int n_gateway = 0;
int n_entering = 0;
int n_leaving = 0;

pthread_mutex_t mutex_gateway = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_entering = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_leaving = PTHREAD_MUTEX_INITIALIZER;  
pthread_mutex_t mutex_private = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_public = PTHREAD_MUTEX_INITIALIZER; 

pthread_cond_t cond_entering = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_leaving = PTHREAD_COND_INITIALIZER;  

/*
Usage: [-f <input_file> | -p arg1 agr2 arg3 arg4] [-v] [-h] 

    [-f] <input_file>           ,run program with the data in the specified .txt file
    [-p] arg1 arg2 arg3 arg4    ,arg1 : nb of subscribed vehicules, arg2 : nb of not subscribed vehicules, arg3 : nb of places for subscriber, arg4 : nb of places for non-subsriber
    [-v]                        ,verbose mode
    [-h]                        ,help message
*/
int main(int argc, char* argv[])
{   
    
    vehicle_t* vehicles = get_options(argc, argv);
    pthread_t clock_thread;
    bool end_vehicle = false;
    
    pthread_create(&clock_thread, NULL, (void*) fn_clock, (void*) &end_vehicle);

    for(size_t i=0; i< (n_notsub_vehicle+n_sub_vehicle); i++){
        pthread_create(&(vehicles[i].thread), NULL, (void*) fn_vehicle, (void*) &vehicles[i]);
    }

    for(size_t i=0; i< (n_notsub_vehicle+n_sub_vehicle); i++){
        pthread_join(vehicles[i].thread, NULL);
    }

    end_vehicle = true;
    pthread_join(clock_thread, NULL);

    delete_vehicles(vehicles);

    pthread_mutex_destroy(&mutex_gateway);
    pthread_mutex_destroy(&mutex_entering);
    pthread_mutex_destroy(&mutex_leaving);
    pthread_mutex_destroy(&mutex_private);
    pthread_mutex_destroy(&mutex_public);

    pthread_cond_destroy(&cond_entering);
    pthread_cond_destroy(&cond_leaving);


    return EXIT_SUCCESS;
}