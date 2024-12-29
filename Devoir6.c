Compteur.h

#ifndef COMPTEUR_H
#define COMPTEUR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct{
   int compteur;
}Message;

#endif

ClientCompteur.c

#include "Compteur.h"


int main(int argc,char *argv[])
{
    if(argc < 3){
      perror("Erreur :Manque d'argument");
      exit(1);
    }
    
    Message message;
    
    int socketClient=socket(AF_INET,SOCK_STREAM,0);
    
    if(socketClient==-1){
      perror("Erreur douverture de socket Client");
      exit(1);
    }
    
    struct sockaddr_in client;
    
    memset(&client,0,sizeof(client));
    
    client.sin_family=AF_INET;
    client.sin_port=htons(atoi(argv[2]));
    client.sin_addr.s_addr=inet_addr(argv[1]);
    
    connect(socketClient,(struct sockaddr *)&client,sizeof(client));
    
    while(1){
      recv(socketClient,&message,sizeof(message),0);
      printf("Client a recu : %d\n",message.compteur);
      sleep(1);
      message.compteur++;
      send(socketClient,&message,sizeof(message),0);
    }
    
    close(socketClient);
    
    return 0;
}

ServeurCompteur.c

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>


int main(int argc,char *argv[])
{
    if(argc < 3){
     perror("Erreur :Manque d'argument");
     return 0;
   }
   
   int socketServeur=socket(AF_INET,SOCK_STREAM,0);
   
   if(socketServeur == -1){
      perror("Erreur douverture de socket Serveur");
      exit(1);
   }
   
   struct sockaddr_in serveur,addrClient;
   
   memset(&serveur,0,sizeof(serveur));
   
   serveur.sin_family=AF_INET;
   serveur.sin_port=htons(atoi(argv[2]));
   serveur.sin_addr.s_addr=inet_addr(argv[1]);
   
   if(bind(socketServeur,(struct sockaddr *)&serveur,sizeof(serveur))==-1){
      perror("Erreur de bind");
      return 0;
   }
   
   listen(socketServeur,5);
   
   int taille=sizeof(struct sockaddr_in);
   char buffR[255];
   Message message;
   
   int socketClient=accept(socketServeur,(struct sockaddr *)&addrClient,&taille);
   
   printf("Connexion recu de client avec Adresse IP %s et PORT %d\n",inet_ntoa(addrClient.sin_addr),ntohs(addrClient.sin_port));
    while(1){
      message.compteur++;
      send(socketClient,&message,sizeof(message),0);
      sleep(1);
      recv(socketClient,&message,sizeof(message),0);
      printf("Serveur a recu : %d\n",message.compteur);
   }
   
   close(socketServeur);
   
   return 0;
}
       
    
    
