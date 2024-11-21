    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>

    int f(int n){
        int res=1;
        for(int i=0;i<n;i++)
           res=res*2;
    return res;
    }

    int g(int n){
    return 2*n;
    }


    int main(int argc,char *argv[]){


        if(argc < 3){
            perror(“Erreur : Nombre d’argument insuffisant “);
            exit(1);
        }


        int opt;
        int resultat=0;


        if(argc==3){
            while((opt=getopt(argc,argv,"f:g:"))!=-1){
                switch(opt){
                    case 'f':
                            resultat=f(atoi(argv[2]));
                            break;
                    case 'g':
                            resultat=g(atoi(argv[2]));
                            break;
                    case ':':
                            perror("Erreur : Manque dargument ");
                            exit(1);
                    case '?':
                            perror("Erreur : Option inconnue ");
                            exit(1);
                }
            }
        }
        else{
            if(!(atoi(argv[2]))){
                printf("Erreur : mauvaise syntaxe");
                exit(1);
            }


            if(strcmp(argv[1],"-f")==0){
            while((opt=getopt(argc,argv,"f:g"))!=-1){
                switch(opt){
                    case 'f':
                    case 'g':
                            resultat=f(g(atoi(argv[2])));
                            break;
                    case ':':
                            perror("Erreur : Manque dargument ");
                            exit(1);
                    case '?':
                            perror("Erreur : Option inconnue ");
                            exit(1);
                    }
                }
            }
            else{
                while((opt=getopt(argc,argv,"g:f"))!=-1){
                switch(opt){
                    case 'g':
                    case 'f':
                            resultat=g(f(atoi(argv[2])));
                            break;
                    case ':':
                            perror("Erreur : Manque dargument ");
                            exit(1);
                    case '?':
                            perror("Erreur : Option inconnue ");
                            exit(1);
                    }
                }


            }


        }


        printf("Le resultat est : %d\n",resultat);
        return 0;
    }

