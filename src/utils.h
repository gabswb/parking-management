#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "vehicle.h"

#define BUFFER_SIZE


//parse txt file passed in command line
void parse_file(char* path, vehicle_t* vehicles);

//extract the command line options
void get_options(int argc, char* argv[], vehicle_t* vehicles);

#endif /*UTILS_H*/