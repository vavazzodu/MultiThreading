/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  This file contains demonstration of how thread is created and what are the various ways we can destroy it
 *
 *        Version:  1.0
 *        Created:  05/02/2021 01:12:27 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karan Raval (), karanraval72@yahoo.com
 *   Organization:  
 *
 * =====================================================================================
 */
/*  You need to compile program like below
 *  gcc -g -c main.c -o main.o
 *  gcc -g main.o -o main.ext -lpthread */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //to work with POSIX threads
#include <unistd.h>

void *
Thread1_fn_callback(void *arg){
    char *str = (char *)arg;
    while(1){
        printf("%s\n",str);
        sleep(1);
    }
}
void
Pthread_create(void){
    pthread_t Thread1;
    //This data will be passed to to function called while creating thread, 
    //it should be dynamically allocated or static data, it should not be local data
    static char *str = "This is thread 1..";
    /* The function which will called when thread is created is the 3rd argument
     * it has to be prototyped like : void * (*func)(void *arg).
     * The forth arg is the argument passed to the func, it has to be void pointer */
    int rc = pthread_create(&Thread1,
                            NULL,
                            &Thread1_fn_callback,
                            (void *)str);
    if(rc != 0){
        printf("thread creation failed\n");
        exit(0);
    }
    return;
}
int
main(int argc, char **argv){
    printf("In main fn paused\n");
    Pthread_create();
    pause();
    return 0;
}
