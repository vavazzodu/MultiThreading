#include <stdio.h>
#include <unistd.h>
#include "../include/ThreadWrapper.h"

int main()
{
    printf("Inside main()...\n");
    int lvRc = ThreadCreate();
    if ( lvRc )
    {
        perror("pthread_create() failed\n");
        printf("rc: %d\n",lvRc);
        return 0;
    }
    //printf("main() is paused...\n");
    //pause();
    printf("main() thread is terminated with pthread_exit()...\n");
    pthread_exit(0);
    return 0;
}