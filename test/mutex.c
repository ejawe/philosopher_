#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BIG 1000000000UL;

uint32_t counter = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


void    *count_to_big(void *arg)
{
    for (uint32_t i = 0; i < 100000; i++)
    {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int     main()
{
    pthread_t t;
    pthread_create(&t, NULL, count_to_big, NULL);
    count_to_big(NULL);
    pthread_join(t, NULL);

    printf("Done. Counter = %u\n", counter);
}