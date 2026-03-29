#include "../include/ThreadWrapper.h"
#include <unistd.h>

void * thread_create ( void *aInput )
{
    char *lvInput = (char *) aInput;
    int i=1;
    while ( i < 10 )
    {
        printf("Thread1: %s\n", lvInput);
        sleep (2);
        if ( i == 5)
        {
            printf ("thread_create() exiting thread as i=5\n");
            pthread_exit(0);
        }
        i++;
    }
    printf("Returning from thread_create()...\n");
    return NULL;
}

int ThreadCreate( void )
{
    printf("Inside ThreadCreate()...\n");
    static char *lvInput = "This is thread1...";
    pthread_t lvThread1;
    return (pthread_create( &lvThread1, NULL, &thread_create, (void *) lvInput ) );
}