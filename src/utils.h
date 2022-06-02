#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "vehicle.h"

#define BUFFER_SIZE 256
#define NUM_BASE 10


//parse csv file passed in command line
vehicle_t* parse_file(char* path);

//extract the command line options
vehicle_t* get_options(int argc, char* argv[]);

#endif /*UTILS_H*/