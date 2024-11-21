#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int n;
sem_t *semaphore;

void *fonction(void *arg)
{
    int idThread=*(int *)arg;
    while(1){
        sem_wait(&(semaphore[idThread]));
        printf("Thread %d vient de sexecuter\n",idThread+1);
        sem_post(&(semaphore[(idThread+1)%n]));
    }

    return NULL;
}


int main()
{
    printf("Donner le nombre des threads : ");
    scanf("%d", &n);
    if (n <= 0)
    {
        printf("Le nombre des threads doit être supérieur à 0");
        return 0;
    }

    semaphore = (sem_t *)malloc(n * sizeof(sem_t));
    pthread_t threads[n];
    int ID[n];
    if (semaphore == NULL)
    {
        perror("Erreur d'allocation");
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        sem_init((&semaphore[i]), 0, 0);
        ID[i] = i;
    }

    sem_post(&semaphore[0]);

    for (int i = 0; i < n; i++)
    {
        if (pthread_create(&(threads[i]), NULL, fonction, &(ID[i])) == -1)
        {
            perror("Erreur de création des threads");
            exit(0);
        }
    }

    for(int i=0 ; i< n ; i++){
        pthread_join(threads[i],NULL);
    }

    for(int i=0 ; i< n ; i++){
        sem_destroy(&(semaphore[i]));
    }

    free(semaphore);

    return 0;
}
