#ifndef GLOBAL_H
#define GLOBAL_H

extern size_t n_sub_place;//number of places for vehicle subscribed
extern size_t n_notsub_place;//number of places for vehicle non subscribed


extern size_t n_sub_vehicle;//number of vehicle subscribed
extern size_t n_notsub_vehicle;//number of vehicle subscribed

extern int n_gateway;//number of vehicle in the gateway
extern int n_entering;//number of vehicle who wants to enter in the parking
extern int n_leaving;//number of vehicle who wants to leave the parking

extern pthread_mutex_t mutex_gateway;//mutex for n_gateway
extern pthread_mutex_t mutex_entering;//mutex for n_entering
extern pthread_mutex_t mutex_leaving;//mutex for n_leaving
extern pthread_mutex_t mutex_sub;//mutex for n_sub_place
extern pthread_mutex_t mutex_notsub;//mutex for n_notsub_place

extern pthread_cond_t cond_entering;//condition for entering the parking trough the gateway
extern pthread_cond_t cond_leaving; //condition for leaving the parking though the gateway

/*char usage_message[] = 
"\
Usage: program [-s <input_file> | -d arg1 agr2 arg3 arg4]\n \
   [-s] <path-to-data>        ,run program with the data in the specified .txt file\n \
   [-d] arg1 arg2 arg3 arg4   ,arg1 : nb of subscribed vehicules, arg2 : nb of not subscribed vehicules\n \
                              ,arg3 : nb of places for subscriber, arg4 : nb of places for non-subsriber\n
";*/

#endif /*GLOBAL_H*/