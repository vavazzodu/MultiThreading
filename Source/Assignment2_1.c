/* compile: gcc Assignment2_1.c -g -o exe -lpthread */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/* Thread call back function */
void* ThreadCb ( void *aArg )
{
    int lvNum = *(int *)aArg;
    /* Since the value we have collected we dont need the aArg, free the resource */
    free( aArg );
    aArg = NULL;
    printf( "Num: %d\n", lvNum );
    sleep(1);
    return NULL;
}

int ThreadCreate ( int aNum )
{
    void *pRet;
    /* Fill the mandatory attributes for creating joinable thread */
    pthread_t lvChildThread;
    pthread_attr_t lvAttr;
    pthread_attr_init ( &lvAttr );
    pthread_attr_setdetachstate ( &lvAttr, PTHREAD_CREATE_JOINABLE);

    for ( ; aNum > 0 ; aNum-- )
    {
        /* The data which we will pass the thread fn has to be on heap */
        int *pNum = malloc (sizeof(int));
        *pNum = aNum;
        if ( pthread_create( &lvChildThread, &lvAttr, &ThreadCb, (void*)pNum ) )
        {
            printf("Thread creation failed\n");
            return 1;
        }
        /* waiting for thread to complete the task and join back */
        pthread_join( lvChildThread, &pRet );
    }
    return 0;
}
int main()
{
    int lvNum;
    
    printf("Enter a number: ");
    scanf("%d", &lvNum);
    if ( lvNum <= 0)
    {
        printf ("Number should be greater than 0\n");
        return 0;
    }
    if ( ThreadCreate (lvNum ) )
    {
        printf ("Error in ThreadCreate()...\n");
        return 1;
    }
    return 0;
}