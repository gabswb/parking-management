#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "global.h"

int random_int(int min, int max);

bool random_bool();

void parse_file(char* path);

void get_options(int argc, char* argv[]);

#endif /*UTIL_H*/