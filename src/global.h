#ifndef GLOBAL_H
#define GLOBAL_H

extern size_t n_sub_place;
extern size_t n_notsub_place;

extern size_t n_sub_vehicle;
extern size_t n_notsub_vehicle;

extern int n_gateway;
extern int n_entering;
extern int n_leaving;

extern pthread_mutex_t mutex_gateway;
extern pthread_mutex_t mutex_entering;
extern pthread_mutex_t mutex_leaving;  
extern pthread_mutex_t mutex_sub;
extern pthread_mutex_t mutex_notsub;  

extern pthread_cond_t cond_entering;
extern pthread_cond_t cond_leaving;  

/*char usage_message[] = 
"\
Usage: program [-s <input_file> | -d arg1 agr2 arg3 arg4]\n \
   [-s] <path-to-data>        ,run program with the data in the specified .txt file\n \
   [-d] arg1 arg2 arg3 arg4   ,arg1 : nb of subscribed vehicules, arg2 : nb of not subscribed vehicules\n \
                              ,arg3 : nb of places for subscriber, arg4 : nb of places for non-subsriber\n
";*/

#endif /*GLOBAL_H*/