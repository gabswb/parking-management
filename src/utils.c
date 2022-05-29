#include "utils.h"


void parse_file(char* path, vehicle_t* vehicles){

    FILE* file = fopen(path, "r");
    if(file == NULL) exit(EXIT_FAILURE);
    char buffer[BUFFER_SIZE+1];

    if(fscanf(file, "%255s", buffer) == 1) puts(buffer);
    else exit(EXIT_FAILURE);
    n_sub_place = atoi(buffer);

    if(fscanf(file, "%255s", buffer) == 1) puts(buffer);
    else exit(EXIT_FAILURE);
    n_notsub_place = atoi(buffer);

    if(fscanf(file, "%255s", buffer) == 1) puts(buffer);
    else exit(EXIT_FAILURE);
    n_sub_vehicle = atoi(buffer);

    if(fscanf(file, "%255s", buffer) == 1) puts(buffer);
    else exit(EXIT_FAILURE);
    n_notsub_vehicle = atoi(buffer);

    vehicles = malloc(sizeof(*vehicles) * (n_sub_vehicle+n_notsub_vehicle));
    if(vehicles == NULL) exit(EXIT_FAILURE);//security for malloc

    int column = 1;
    while(fscanf(file, "%255s", buffer) ==1){
        puts(buffer);
        
        if(column%3 == 0) (vehicles++)->id = atoi(buffer);

        else if(column%3 == 1){//== "true\0"
            if(strcmp(buffer,"true")) (vehicles++)->is_sub = true;
            else (vehicles++)->is_sub = false;
        }
        else (vehicles++)->parking_time = atoi(buffer);
    }
}

void get_options(int argc, char* argv[], vehicle_t* vehicles){
    switch (argc){

        case 1 :vehicles = random_sample_vehicle(n_sub_vehicle, n_notsub_vehicle);
                break;

        case 2 :parse_file(argv[2], vehicles);
                break;

        case 5 :n_sub_place = atoi(argv[1]);
                n_notsub_place = atoi(argv[2]);
                n_sub_vehicle = atoi(argv[3]);
                n_notsub_vehicle = atoi(argv[4]);
                break;

        default:fprintf(stderr, "Usage: %s [-s <input_file> | -d arg1 agr2 arg3 arg4]\n"
                                "   [-s] <path-to-data>        ,run program with the data in the specified .txt file\n"
                                "   [-d] arg1 arg2 arg3 arg4   ,arg1 : nb of subscribed vehicules, arg2 : nb of not subscribed vehicules\n"
                                "                              ,arg3 : nb of places for subscriber, arg4 : nb of places for non-subsriber\n"
                                , argv[0]);
                exit(EXIT_FAILURE);
    }
}