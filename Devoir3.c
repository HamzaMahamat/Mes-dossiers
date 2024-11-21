#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void diviser_fichier(const char *nom_fichier, size_t taille_partie) {
    int source = open(nom_fichier, O_RDONLY);
    if (source == -1) {
        perror("Erreur lors de l'ouverture du fichier source");
        return;
    }

    off_t taille_fichier = lseek(source, 0, SEEK_END);
    lseek(source, 0, SEEK_SET);  

    int nombre_parties = taille_fichier / taille_partie;
    if (taille_fichier % taille_partie != 0) {
        nombre_parties++; 
    }

    char nom_partie[256];
    size_t octets_lus = 0;
    for (int i = 0; i < nombre_parties; i++) {
        snprintf(nom_partie, sizeof(nom_partie), "part%d", i + 1);
        int partie = open(nom_partie, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if (partie == -1) {
            perror("Erreur lors de la création du fichier de la partie");
            close(source);
            return;
        }

        size_t ecrits = 0;
        while (ecrits < taille_partie && octets_lus < taille_fichier) {
            char tampon[1024];
            size_t a_lire = (taille_fichier - octets_lus) < sizeof(tampon) ? (taille_fichier - octets_lus) : sizeof(tampon);
            ssize_t taille_lue = read(source, tampon, a_lire);
            write(partie, tampon, taille_lue);
            ecrits += taille_lue;
            octets_lus += taille_lue;
        }
        close(partie);
    }

    close(source);
    printf("Le fichier a été divisé avec succès.\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <nom_du_fichier> <taille_partie>\n", argv[0]);
        return 1;
    }

    const char *nom_fichier = argv[1];
    size_t taille_partie = atol(argv[2]);

    diviser_fichier(nom_fichier, taille_partie);

    return 0;
}

///Exercice 5: Deuxieme partie join 

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void fusionner_fichiers(const char *nom_fichier_sortie, int nombre_parties) {
    int sortie = open(nom_fichier_sortie, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (sortie == -1) {
        perror("Erreur lors de la création du fichier de sortie");
        return;
    }

    char nom_partie[256];
    for (int i = 1; i <= nombre_parties; i++) {
        snprintf(nom_partie, sizeof(nom_partie), "part%d", i);
        
        int partie = open(nom_partie, O_RDONLY);
        if (partie == -1) {
            perror("Erreur lors de l'ouverture de la partie");
            close(sortie);
            return;
        }

        char tampon[1024];
        ssize_t taille_lue;
        while ((taille_lue = read(partie, tampon, sizeof(tampon))) > 0) {
            write(sortie, tampon, taille_lue);
        }

        close(partie);
    }

    close(sortie);
    printf("Les parties ont été fusionnées avec succès dans %s.\n", nom_fichier_sortie);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <nom_fichier_sortie> <part1> <part2> ... <partN>\n", argv[0]);
        return 1;
    }

    const char *nom_fichier_sortie = argv[1];
    int nombre_parties = argc - 2; 
    fusionner_fichiers(nom_fichier_sortie, nombre_parties);

    return 0;
}

