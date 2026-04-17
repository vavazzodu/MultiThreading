#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <malloc.h>

pthread_t child_thread1, child_thread2;

static void* ThreadFnCb ( void *CbArg )
{
    int rc = 0;
    if(CbArg == NULL)
    {
        printf("CbArg is NULL\n");
        return NULL;
    }
    int num = *(int*) CbArg;
    /* argument is not needed anymore, cleanup */
    free ( CbArg );
    CbArg = NULL;
    int *Ret = malloc ( sizeof(int) );

    while ( rc != num )
    {
        printf("Thread with argument %d in sleep\n", num);
        sleep(1);
        rc++;
    }
    *Ret = num * num;
    return (void *) Ret;
}
void ThreadCreate ( pthread_t *aChildThread, int num)
{
    /* initializing attr which will be passed in thread_create */
    pthread_attr_t attr;
    pthread_attr_init (&attr);
    pthread_attr_setdetachstate ( &attr, PTHREAD_CREATE_JOINABLE);
    //pthread_attr_setdetachstate ( &attr, PTHREAD_CREATE_DETACHED);
    
    /* argument to the CB function has to be on the heap */
    int *argp = malloc ( sizeof(int) );
    if( !argp )
    {
        printf("ThreadCreate(): malloc failed\n");
        return;
    }
    *argp = num;

    pthread_create( aChildThread, &attr, &ThreadFnCb, (void *) argp ) ;

}
int main()
{
    void *ret1, *ret2;
    ThreadCreate ( &child_thread1, 10);
    ThreadCreate ( &child_thread2, 2);
    /* main thread will be blocked here untill child thread 1 joins */
    printf("main() is waiting for thread1 to join\n");
    pthread_join( child_thread1, &ret1);
    /* when joinable thread joins, main thread has to take care of 
     * resource deallocation, clean memory here */
    if ( ret1 )
    {
        printf("Child thread 1 returned: %d\n", *(int*) ret1);
        free(ret1);
        ret1 = NULL;
    }

    printf("main() is waiting for thread2 to join\n");
    pthread_join( child_thread2, &ret2);
    if ( ret2 )
    {
        printf("Child thread 2 returned: %d\n", *(int*)ret2);
        free(ret2);
        ret2 = NULL;
    }

    return 0;
}