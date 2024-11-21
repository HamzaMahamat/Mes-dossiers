#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex1, mutex2;
int n;

void *incrementer(void *arg)
{
    while (1)
    {
        sem_wait(&mutex1);
        for (int i = 0; i <= n; i++)
            printf("%d\n", i);
        sem_post(&mutex2);
    }

    return NULL;
}

void *decrementer(void *arg)
{
    while (1)
    {
        sem_wait(&mutex2);
        for (int i = n; i >= -n; i--)
            printf("%d\n", i);
        sem_post(&mutex1);
    }

    return NULL;
}

int main()
{
    if (sem_init(&mutex1, 0, 1) != 0)
        return -1;
    if (sem_init(&mutex2, 0, 0) != 0)
        return -1;

    printf("Donner la valeur de n : ");
    scanf("%d", &n);

    pthread_t pid[2];
    void *(*fonction[])(void *) = {incrementer, decrementer};

    for (int i = 0; i < 2; i++)
    {
        if (pthread_create(&(pid[i]), NULL, fonction[i], NULL) != 0)
        {
            perror("Erreur de creation des threads");
            exit(1);
        }
    }

    for (int i = 0; i < 2; i++)
    {
        pthread_join(pid[i], NULL);
    }

    sem_destroy(&mutex1);
    sem_destroy(&mutex2);

    return 0;
}

