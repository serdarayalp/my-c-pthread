#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

enum action
{
    PING,
    PONG
};

pthread_cond_t condition;
pthread_mutex_t mutex;

void *thread_ping(void *action)
{
    enum action *_action = (enum action *)action;
    while (1)
    {
        pthread_mutex_lock(&mutex);
        while (*_action != PING)
        {
            // unlock
            pthread_cond_wait(&condition, &mutex);
            // lock
        }
        pthread_mutex_unlock(&mutex);

        printf("Ping\n");

        pthread_mutex_lock(&mutex);
        *_action = PONG;
        pthread_cond_signal(&condition);
        pthread_mutex_unlock(&mutex);
    }
}

void *thread_pong(void *nAction)
{
    enum action *nextAction = (enum action *)nAction;
    while (1)
    {
        pthread_mutex_lock(&mutex);
        while (*nextAction != PONG)
        {
            // unlock
            pthread_cond_wait(&condition, &mutex);
            // lock
        }
        pthread_mutex_unlock(&mutex);

        printf("Pong\n");

        pthread_mutex_lock(&mutex);
        *nextAction = PING;
        pthread_cond_signal(&condition);
        pthread_mutex_unlock(&mutex);
    }
}

/* Starte das Program mit "-pthread"
    gcc -pthread -Wall -std=c99 -o ping-pong ping-pong-c
*/
int main(int argc, char const *argv[])
{
    pthread_t t_ping;
    pthread_t t_pong;

    pthread_cond_init(&condition, NULL);
    pthread_mutex_init(&mutex, NULL);

    enum action *action = malloc(sizeof(enum action));
    *action = PING;

    pthread_create(&t_ping, NULL, thread_ping, action);
    pthread_create(&t_pong, NULL, thread_pong, action);

    pthread_join(t_ping, NULL);
    pthread_join(t_pong, NULL);

    pthread_cond_destroy(&condition);
    pthread_mutex_destroy(&mutex);

    free(action);

    return 0;
}
