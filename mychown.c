/*
"mychown" est une commande qui mime "chown" et permet de changer le propriétaire d'un fichier. 
Elle peut prendre un paramètre c qui permet d'énoncer le changement effectué 
    Exemple: mychmod -c NouveauProprio MonFichier

Auths:
    DIDOUH Mohamed
    ISHIMWE Blaise
    TOKAM George
*/

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/stat.h>
#include <pwd.h>
#include "mylib.h"
struct option longopts [] = {
    {"changes", no_argument, 0, 'c'},
    {0,0,0,0}
};

int main (int argc, char *argv[]) {

    int c = 0;
    int t;
    //Boucle getopt pour gérer les paramètres qu'on pass au programme.
    //ce: paramètre c et e, le ":" pour spécifier que le param e requiert une option (nom de l'extension) 
    while ((t = getopt_long(argc, argv, "c", longopts, NULL)) != -1){

        switch (t){
            case 'c':
                //Enoncer les changements de propriétaire
                c = 1;
                break;
            case ':':
        		//Options manquantes
                fprintf(stderr, "%s: l'option '-%c' requiert un argument.\n", argv[0], optopt);
                break;
            case '?':
        		//Options pas prise en charge par getopt
            default:
                //Autres params.
                fprintf(stderr, "%s: l'option '-%c' n'est pas valide.\n", argv[0], optopt);
            break;
        }
    }
    //Nombre d'arguments doit être min 3 ([CMD] + [Propriétaire] + [Fichier])
    if (argc < 3){
      fprintf(stderr, "Erreur chown \n");
      exit(EXIT_FAILURE);
    }

    char *myfile = argv[optind+1];
    char *myuser = argv[optind]; 
    int x;
    //getpwnam() de la librairie pwd.h nous permet de parcourir la DB des passwd sous base du login
    struct passwd *getpwnam(const char *name);

    //Si l'utilisateur existe la fonction retourne sa structure complète donc (!=NULL)
    if(getpwnam(myuser) == NULL){
        printf("Pas d'utilisateur avec le nom %s\n", myuser);
    	exit(EXIT_FAILURE);
    }
    else{
        //fonction de mylib.h pour tester si le fichier existe
        if(!is_a_file(myfile)){
            printf("Pas de fichier avec le nom %s\n", myfile);
        	exit(EXIT_FAILURE);
        }
        else{
            //chown(chemin,uid,gid), Dans ce cas on change les deux param(user,group) avec la meme commande
  		    if(chown (myfile, getpwnam(myuser)->pw_uid, getpwnam(myuser)->pw_gid) < 0){
                //Erreurs suite à l'appel system chown.
                fprintf(stderr, "Erreur chown: Vérifier que vous avez les droits nécessaire pour executer la commande\n");
                exit(EXIT_FAILURE);
        	}
            else{
                //Enoncer les changements
    	        if (c == 1){
      	             printf("Le propriétaire du fichier %s a été correctement remplacé par %s.\n", myfile, myuser);
    	        }
                return EXIT_SUCCESS;
            }

        }
    }
}
