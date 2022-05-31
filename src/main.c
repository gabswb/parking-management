#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

size_t n_sub_place = 10;    
size_t n_notsub_place = 20;

size_t n_sub_vehicle = 12;
size_t n_notsub_vehicle = 23;

/*
Usage: [-s <input_file> | -d arg1 agr2 arg3 arg4]

    [-s] <input_file>           ,run program with the data in the specified .txt file
    [-d] arg1 arg2 arg3 arg4    ,arg1 : nb of subscribed vehicules, arg2 : nb of not subscribed vehicules
                                ,arg3 : nb of places for subscriber, arg4 : nb of places for non-subsriber
*/
int main(int argc, char* argv[])
{   
    
    vehicle_t* vehicles = get_options(argc, argv);

    print_vehicles((n_sub_vehicle+n_notsub_vehicle), vehicles);

    delete_vehicles(vehicles);

    return EXIT_SUCCESS;
}