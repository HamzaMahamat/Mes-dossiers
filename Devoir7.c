#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

void scannerPort(const char *adresse, int port_debut, int port_fin) {
    struct sockaddr_in serveur;
    int socket_fd;

    for (int port = port_debut; port <= port_fin; ++port) {
        socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_fd < 0) {
            perror("Erreur lors de la création du socket");
            exit(EXIT_FAILURE);
        }

        serveur.sin_family = AF_INET;
        serveur.sin_port = htons(port);
        if (inet_pton(AF_INET, adresse, &serveur.sin_addr) <= 0) {
            perror("Adresse IP invalide");
            close(socket_fd);
            exit(EXIT_FAILURE);
        }

        if (connect(socket_fd, (struct sockaddr *)&serveur, sizeof(serveur)) == 0) {
            printf("%d\n", port); 
        }

        close(socket_fd);
    }
}

int main() {
    char cible[256];

    printf("Entrez l'adresse IP ou le nom de domaine de la cible : ");
    if (scanf("%255s", cible) != 1) {
        fprintf(stderr, "Erreur lors de la lecture de l'adresse.\n");
        return EXIT_FAILURE;
    }

    scannerPort("127.0.0.1", 0, 3000);

    return EXIT_SUCCESS;
}
