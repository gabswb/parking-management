#include <stdlib.h>
#include <stdio.h>
#include "vehicle.h"

int n_sub_place = 10;
int n_notsub_place = 20;

int n_sub_vehicle = 12;
int n_notsub_vehicle = 23;

/*
Usage: [-s <input_file> | -d arg1 agr2 arg3 arg4]
    [-s] <path-to-data>         ,run program with the data in the specified .txt file
    [-d] arg1 arg2 arg3 arg4    ,arg1 : nb of subscribed vehicules, arg2 : nb of not subscribed vehicules
                                ,arg3 : nb of places for subscriber, arg4 : nb of places for non-subsriber
*/
int main(int argc, char* argv[])
{
    get_options(argc, argv);

    
    return EXIT_SUCCESS;
}