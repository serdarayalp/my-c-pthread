#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *threadFunction(void *arg);

/* Starte das Program mit "-pthread"
    gcc -pthread -Wall -std=c99 -o my-pthread my-pthread.c
*/
int main(int argc, char const *argv[])
{
    pthread_t tid;
    void *returnValue;

    pthread_create(&tid, NULL, threadFunction, NULL);
    pthread_join(tid, &returnValue);

    exit(0);
}

void *threadFunction(void *arg)
{
    printf("Hello World!\n");
    return NULL;
}