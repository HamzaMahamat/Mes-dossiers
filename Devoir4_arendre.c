#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t mutex1,mutex2;
int compteur=0;


void *incrementer(void *arg)
{
     while(1){
       sem_wait(&mutex1);
         while(compteur<=10)
           printf("compteur=%d\n",compteur++);
           sleep(1);
       sem_post(&mutex2);
     }
     pthread_exit(NULL);
}

void *decrementer(void *arg)
{
     while(1){
       sem_wait(&mutex2);
         while(compteur>=-10)
           printf("compteur=%d\n",compteur--);
         sleep(1);
       sem_post(&mutex1);
     }
     pthread_exit(NULL);
}





int main()
{
    if(sem_init(&mutex1,0,1)!=0)
         exit(1);
    if(sem_init(&mutex2,0,0)!=0)
         exit(1);
    pthread_t pid[2];
    
    void *(* function[])(void *)={incrementer,decrementer};
    
    for(int i=0;i<2;i++){
      if(pthread_create(&(pid[i]),NULL,function[i],NULL)!=0){
            perror("Erreur de creation de thread");
            exit(1);
      }
    }
    
    for(int i=0;i<2;i++){
       pthread_join(pid[i],NULL);
    }
    
    sem_destroy(&mutex1);
    sem_destroy(&mutex2);

    return 0;
}
