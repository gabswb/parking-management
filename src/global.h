#ifndef GLOBAL_H
#define GLOBAL_H

#include <pthread.h>

extern size_t n_private_place;//number of places for vehicle subscribed
extern size_t n_public_place;//number of places for vehicle non subscribed


extern size_t n_sub_vehicle;//number of vehicle subscribed
extern size_t n_notsub_vehicle;//number of vehicle subscribed

extern int n_gateway;//number of vehicle in the gateway
extern int n_entering;//number of vehicle who wants to enter in the parking
extern int n_leaving;//number of vehicle who wants to leave the parking

extern pthread_mutex_t mutex_gateway;//mutex for n_gateway
extern pthread_mutex_t mutex_entering;//mutex for n_entering
extern pthread_mutex_t mutex_leaving;//mutex for n_leaving
extern pthread_mutex_t mutex_private;//mutex for n_private_place
extern pthread_mutex_t mutex_public;//mutex for n_public_place

extern pthread_cond_t cond_entering;//condition for entering the parking trough the gateway
extern pthread_cond_t cond_leaving; //condition for leaving the parking though the gateway

static const char usage_msg[] = "\n" 
"Usage: %s [-f <input_file> | -p arg1 agr2 arg3 arg4] [-v] [-h]\n\n"

"    [-f] <input_file>           ,run program with the data in the specified .txt file\n"
"    [-p] arg1 arg2 arg3 arg4    ,arg1 : nb of subscribed vehicules, arg2 : nb of not subscribed vehicules\n"
"                                ,arg3 : nb of places for subscriber, arg4 : nb of places for non-subsriber\n"
"    [-v]                        ,verbose mode\n"
"    [-h]                        ,help message\n\n";

#endif /*GLOBAL_H*/