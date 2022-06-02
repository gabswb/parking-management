#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

size_t n_sub_place = 10;    
size_t n_notsub_place = 20;

size_t n_sub_vehicle = 12;
size_t n_notsub_vehicle = 23;

int n_gateway = 0;
int n_entering = 0;
int n_leaving = 0;

pthread_mutex_t mutex_gateway = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_entering = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_leaving = PTHREAD_MUTEX_INITIALIZER;  
pthread_mutex_t mutex_sub = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_notsub = PTHREAD_MUTEX_INITIALIZER; 

pthread_cond_t cond_entering = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_leaving = PTHREAD_COND_INITIALIZER;   

/*
Usage: [-s <input_file> | -d arg1 agr2 arg3 arg4]

    [-s] <input_file>           ,run program with the data in the specified .txt file
    [-d] arg1 arg2 arg3 arg4    ,arg1 : nb of subscribed vehicules, arg2 : nb of not subscribed vehicules
                                ,arg3 : nb of places for subscriber, arg4 : nb of places for non-subsriber
*/
int main(int argc, char* argv[])
{   
    
    vehicle_t* vehicles = get_options(argc, argv);


    delete_vehicles(vehicles);

    pthread_mutex_destroy(&mutex_gateway);
    pthread_mutex_destroy(&mutex_entering);
    pthread_mutex_destroy(&mutex_leaving);
    pthread_mutex_destroy(&mutex_sub);
    pthread_mutex_destroy(&mutex_notsub);

    pthread_cond_destroy(&cond_entering);
    pthread_cond_destroy(&cond_leaving);


    return EXIT_SUCCESS;
}