#ifndef CAR_H
#define CAR_H

#include <stdbool.h>
#include <time.h>

struct car {
    int id;
    bool is_sub;
    time_t sub_date;
};
typedef struct car car_t;

#endif /*CAR_H*/