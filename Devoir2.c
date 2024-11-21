#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc < 6) {
        perror("Erreur de syntaxe :");
        exit(1);
    }

    int i, j, fp;
    int opt;
    int taille = atoi(argv[3]);
    int Matrice[taille][taille];

    while ((opt = getopt(argc, argv, "cad:f:t")) != -1) {
        switch (opt) {
            case 'd': break;
            case 'f': break;
            case 'c':
                        for (i = 0; i < taille; i++) {
                            for (j = 0; j < taille; j++) {
                                Matrice[i][j] = rand() % 11;
                            }
                        }
                        fp = open(argv[5], O_WRONLY | O_EXCL, S_IRUSR | S_IROTH | S_IRGRP | S_IWUSR);
                        if (fp == -1) {
                             perror("Erreur ouverture :");
                            exit(1);
                        }

                        if (argc == 6) {
                          int nbW;
                         for (i = 0; i < taille; i++) {
                             for (j = 0; j < taille; j++) {
                                nbW = write(fp, &(Matrice[i][j]), sizeof(int));
                                    if (nbW <= 0) {
                                            perror("Erreur d'écriture dans le fichier");
                                            exit(1);
                                        }
                                    }
                                }
                         } 
                         else {
                            int nbWB;
                            char buff[255];
                            for (i = 0; i < taille; i++) {
                                for (j = 0; j < taille; j++) {
                                    sprintf(buff, "%d\t", Matrice[i][j]);
                                    nbWB = write(fp, buff, strlen(buff));
                                    if (nbWB <= 0) {
                                        perror("Erreur d'écriture dans le fichier");
                                        exit(1);
                                    }
                                }
                                    write(fp, "\n", strlen("\n"));
                            }
                         }
                          close(fp);
                          break;
            case 'a':
                        fp = open(argv[5], O_RDONLY);
                        if (fp == -1) {
                            perror("Erreur d'écriture");
                            exit(1);
                        }
                        char buff;
                        int nbRead = 0;

                        do {
                            nbRead = read(fp, &buff, sizeof(char));
                            if (nbRead > 0)
                                printf("%c",buff);
                        }while(nbRead > 0);

                        close(fp);
                        break;
            case ':' : perror("Erreur Manque dargument "); break;
            case '?' : perror("Erreur : Argumrnt inconnue"); break;
        }
    }

    return 0;
}
                            
                            
