#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* thread_cb (void *aArg)
{
    int *lvVal = (int *)aArg;
    printf("Thread %d value: %d\n", *lvVal, *lvVal);
    pthread_exit(0);
}

int CreateThread( int aVal)
{
    pthread_t thread;
    int *lvVal = malloc (sizeof (int));
    *lvVal = aVal;
    if ( pthread_create ( &thread, NULL, &thread_cb, (void *)lvVal) )
    {
        printf("pthread_create() failed\n");
        return 1;
    }
    sleep(2);
    free(lvVal);
    return 0;
}


int main()
{
    int n;

    printf("Enter the value of n: ");
    scanf("%d", &n);
    for ( ; n>0; n--)
    {
        if ( CreateThread( n ) )
        {
            printf("CreateThread failed\n");
            return -1;
        }
    }
    pthread_exit(0);
    return 0;

}
