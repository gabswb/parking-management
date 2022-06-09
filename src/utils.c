#include "utils.h"

bool Verbose = false;

void verbose(const char* format, ...){
    if(!Verbose) return;

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    fflush(stdout);
    va_end(args);
}


vehicle_t* parse_file(char* path){

    FILE* file = fopen(path, "r");
    if(file == NULL) exit(EXIT_FAILURE);

    char buffer[BUFFER_SIZE];
    const char* csv_token = ","; //token on which we parse the file (csv --> ',')
    char* strtok_result, *end_ptr;
    vehicle_t* temp = NULL;

    /* 
    gets the first line of the file (n_sub_place and n_notsub_place)
    */
    if(fgets(buffer, BUFFER_SIZE, file) == NULL) exit(EXIT_FAILURE);
    strtok_result = strtok(buffer, csv_token);
    n_sub_place = (size_t) strtol(strtok_result, &end_ptr, NUM_BASE);
    strtok_result = strtok(NULL, csv_token);
    n_notsub_place = (size_t) strtol(strtok_result, &end_ptr, NUM_BASE);

    /* 
    gets the second line of the file (n_sub_vehicle and n_notsub_vehicle)
    */
    if(fgets(buffer, BUFFER_SIZE, file) == NULL) exit(EXIT_FAILURE);
    strtok_result = strtok(buffer, csv_token);
    n_sub_vehicle = (size_t) strtol(strtok_result, &end_ptr, NUM_BASE);
    strtok_result = strtok(NULL, csv_token);
    n_notsub_vehicle = (size_t) strtol(strtok_result, &end_ptr, NUM_BASE);


    temp = malloc(sizeof(*temp) * (n_sub_vehicle+n_notsub_vehicle));
    if(temp == NULL) exit(EXIT_FAILURE);//security for malloc


    /*
    gets all the other lines containing the data with the following format : id,is_sub,parking_time
    */
    size_t index = 0;
    while(fgets(buffer, BUFFER_SIZE, file) && index < n_sub_vehicle+n_notsub_vehicle){

        //gets id
        strtok_result = strtok(buffer, csv_token);
        temp[index].id = (int) strtol(strtok_result, &end_ptr, NUM_BASE);

        //gets if is subscribed
        strtok_result = strtok(NULL, csv_token);
        if(strcmp(strtok_result,"true")==0) temp[index].is_sub = true; 
        else temp[index].is_sub = false; 

        //gets parking time
        strtok_result = strtok(NULL, csv_token);
        temp[index].parking_time = (int) strtol(strtok_result, &end_ptr, NUM_BASE);
        
        index++;
    }
    if(index == n_sub_place+n_notsub_place){
        fprintf(stderr, "Error : the number of vehicle given is not correct\n");
        exit(EXIT_FAILURE);
    }
    return temp;
}

vehicle_t* get_options(int argc, char* argv[]){

    vehicle_t* temp = NULL;
    bool is_f_used = false;//flag to check if -f is used because -f and -p are not compatible
    bool is_p_used = false;

    if(argc > 7 ){
        fprintf(stderr, usage_msg, argv[0]);
        exit(EXIT_FAILURE);
    }

    if(argc == 1) temp = random_sample_vehicle(n_sub_vehicle, n_notsub_vehicle);


    for(int i=1; i < argc; i++){
        if(strcmp(argv[i], "-f") == 0){
            if(i+1 >= argc || is_p_used == true){
                fprintf(stderr, usage_msg, argv[0]);
                exit(EXIT_FAILURE);

            }
            temp = parse_file(argv[i+1]);
            is_f_used = true;
            i+=1;
        }
        else if(strcmp(argv[i], "-p") == 0){
            if(i+4 >= argc || is_f_used == true){
                fprintf(stderr, usage_msg, argv[0]);
                exit(EXIT_FAILURE);
            }
            n_sub_place = (size_t) strtol(argv[i+1], NULL, NUM_BASE);
            n_notsub_place = (size_t) strtol(argv[i+2], NULL, NUM_BASE);
            n_sub_vehicle = (size_t) strtol(argv[i+3], NULL, NUM_BASE);
            n_notsub_vehicle = (size_t) strtol(argv[i+4], NULL, NUM_BASE);
            temp = random_sample_vehicle(n_sub_vehicle, n_notsub_vehicle);
            is_p_used = true;
            i+=4;
        }
        else if(strcmp(argv[i], "-v") == 0){
            Verbose = true;
            if(argc == 2) temp = random_sample_vehicle(n_sub_vehicle, n_notsub_vehicle);
        }
        else{
            fprintf(stderr, usage_msg, argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    verbose("Number of place for sub : %zu\n"
            "Number of place for non sub : %zu\n"
            "Number of vechicle sub : %zu\n"
            "Number of vehicle non sub : %zu\n\n\n",
            n_sub_place, n_notsub_place, n_sub_vehicle, n_notsub_vehicle);

    return temp;
}

void print_info(const char* format, ...){
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    fflush(stdout);
    va_end(args);
}
