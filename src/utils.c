#include "utils.h"


vehicle_t* parse_file(char* path){

    FILE* file = fopen(path, "r");
    if(file == NULL) exit(EXIT_FAILURE);

    char buffer[BUFFER_SIZE];
    const char* csv_token = ",";
    char* strtok_result, *end_ptr;
    vehicle_t* temp = NULL;

    
    if(fgets(buffer, BUFFER_SIZE, file) == NULL) exit(EXIT_FAILURE);
    strtok_result = strtok(buffer, csv_token);
    n_sub_place = (size_t) strtol(strtok_result, &end_ptr, NUM_BASE);
    strtok_result = strtok(NULL, csv_token);
    n_notsub_place = (size_t) strtol(strtok_result, &end_ptr, NUM_BASE);

    if(fgets(buffer, BUFFER_SIZE, file) == NULL) exit(EXIT_FAILURE);
    strtok_result = strtok(buffer, csv_token);
    n_sub_vehicle = (size_t) strtol(strtok_result, &end_ptr, NUM_BASE);
    strtok_result = strtok(NULL, csv_token);
    n_notsub_vehicle = (size_t) strtol(strtok_result, &end_ptr, NUM_BASE);


    temp = malloc(sizeof(*temp) * (n_sub_vehicle+n_notsub_vehicle));
    if(temp == NULL) exit(EXIT_FAILURE);//security for malloc


    size_t index = 0;
    while(fgets(buffer, BUFFER_SIZE, file)){

        strtok_result = strtok(buffer, csv_token);
        temp[index].id = (int) strtol(strtok_result, &end_ptr, NUM_BASE);

        strtok_result = strtok(NULL, csv_token);
        if(strcmp(strtok_result,"true")) temp[index].is_sub = true; 
        else temp[index].is_sub = false; 

        strtok_result = strtok(NULL, csv_token);
        temp[index].parking_time = (int) strtol(strtok_result, &end_ptr, NUM_BASE);
        
        index++;
    }
    return temp;
}

vehicle_t* get_options(int argc, char* argv[]){

    vehicle_t* temp = NULL;
    char* end_ptr;

    switch (argc){

        case 1 :temp = random_sample_vehicle(n_sub_vehicle, n_notsub_vehicle);
                break;

        case 2 : temp = parse_file(argv[1]);
                break;

        case 5 :n_sub_place = (size_t) strtol(argv[1], &end_ptr, NUM_BASE);
                n_notsub_place = (size_t) strtol(argv[2], &end_ptr, NUM_BASE);
                n_sub_vehicle = (size_t) strtol(argv[3], &end_ptr, NUM_BASE);
                n_notsub_vehicle = (size_t) strtol(argv[4], &end_ptr, NUM_BASE);
                temp = random_sample_vehicle(n_sub_vehicle, n_notsub_vehicle);
                break;

        default:fprintf(stderr, "\nUsage: %s [-s <input_file> | -d arg1 agr2 arg3 arg4]\n\n"
                                "   [-s] <path-to-data>        ,run program with the data in the specified .txt file\n"
                                "   [-d] arg1 arg2 arg3 arg4   ,arg1 : nb of subscribed vehicules, arg2 : nb of not subscribed vehicules\n"
                                "                              ,arg3 : nb of places for subscriber, arg4 : nb of places for non-subsriber\n\n"
                                , argv[0]);
                exit(EXIT_FAILURE);
    }

    return temp;
}