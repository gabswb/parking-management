#include "clock.h"

void fn_clock(void* _end_vehicle){
    int clock_time = 0;
    size_t n_initial_public_place = n_public_place;
    n_public_place = (size_t) n_public_place*(1-OVERFLOW_PERCENTAGE);
    printf("n_public_place %zu\n", n_public_place);
    bool* end_vehicle = (bool*) _end_vehicle;

    while(!*end_vehicle){
        sleep(3);
        clock_time = (clock_time+1)%24;
        printf("%dH\n", clock_time);
        if(clock_time > RELEASE_TIME && clock_time < RELEASE_TIME+RELEASE_PERIOD){
            pthread_mutex_lock(&mutex_public);

            size_t n_bonus_places = (size_t) (n_private_place * OVERFLOW_PERCENTAGE)/RELEASE_PERIOD;
            n_public_place += n_bonus_places;
            printf("%zu new places are now available\n", n_bonus_places);

            pthread_mutex_unlock(&mutex_public);
        }
        if(clock_time >= RELEASE_TIME+RELEASE_PERIOD){
            pthread_mutex_lock(&mutex_public);

            if(n_public_place >= n_initial_public_place*(1-OVERFLOW_PERCENTAGE)){
                n_public_place -= n_initial_public_place*OVERFLOW_PERCENTAGE;
            }
            pthread_mutex_unlock(&mutex_public);
        }
    }

}