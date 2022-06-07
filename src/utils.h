#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "vehicle.h"

#define BUFFER_SIZE 256
#define NUM_BASE 10

extern bool Verbose;

void verbose(const char* format, ...);

//parse csv file passed in command line
vehicle_t* parse_file(char* path);

/**
 * @brief Extract the options given in the commande line arguments
 * @param argc number of commande line arguments
 * @param argv array of command line arguments, -f and -p are not compatible
 * @return an array of vehicle_t 
 */
vehicle_t* get_options(int argc, char* argv[]);



#endif /*UTILS_H*/