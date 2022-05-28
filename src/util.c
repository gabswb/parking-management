#include "util.h"

int random_int(int min, int max){
  return(min + (rand() % (max - min)));
}

bool random_bool(){
    if(random_int(0,1)) return true;
    return false;
}

void parse_file(char* path){

}

void get_options(int argc, char* argv[]){
    switch (argc){

        case 1 : break;

        case 2 :parse_file(argv[2]);
                printf("parse\n");
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