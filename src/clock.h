#ifndef CLOCK_H
#define CLOCK_H

#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include "global.h"

#define RELEASE_TIME 18 //time in hours at which we start to realease some public place of the overflow area
#define RELEASE_PERIOD 4//this period start at RELEASE_TIME, each hour during this period some blocked place will be made available
#define OVERFLOW_PERCENTAGE 0.2 //20% of the public places will be reserved before the RELEASE_TIME

void fn_clock(void* arg);

#endif // CLOCK_H