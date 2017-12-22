/*
"mychmod" est une commande qui mime "chmod" et permet de changer les permissions d'un fichier avec l'option de rajouter une extension à celui-ci.
    Exemple: mychmod -ce 0777 exe MonFichier
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
#include "mylib.h"
struct option longopts [] = {
    {"changes", no_argument, 0, 'c'},
    {"extension", no_argument, 0, 'e'},
    {0,0,0,0}
};

int main (int argc, char *argv[]) {

    int c,e = 0;
    int t;
    //Boucle getopt pour gérer les paramètres qu'on pass au programme.
    //ce: paramètre c et e, le ":" pour spécifier que le param e requiert une option (nom de l'extension) 
    while ((t = getopt_long(argc, argv, "ce:", longopts, NULL)) != -1){

        switch (t){
            case 'c':
                //Enoncer les changements de permission
                c = 1;
                break;
            case 'e':
                //Ajouter une extension au fichier
                e = 1;
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
    //Nombre d'argument doit être min 3 ([CMD] + [Valeur de permission] + [Nom de fichier])
    if (argc < 3){
      fprintf(stderr, "Erreur chmod \n");
      exit(EXIT_FAILURE);
    }

    int mod_opt = optind;
    if (e == 1){
        mod_opt-=1;
    }
    char *mymod = argv[mod_opt];
    char *myfile = argv[optind+1];
    char *myextension = argv[optind]; 
    int x;

    //Erreur au cas ou le nom de fichier n'a pas été saisit/capturé
    if(myfile == NULL){
        printf("Pas de fichier entré! \n");
	exit(EXIT_FAILURE);
    }
    else{
    	if(strlen(mymod) == 4){
	   //
    	   if(((mymod[0] - '0') != 0) || ((mymod[1] - '0') > 7) || ((mymod[2] - '0') > 7) || ((mymod[3] - '0') > 7)){
    	       printf("Valeur des permissions invalide, e.g: [0777] \n");
    	       exit(EXIT_FAILURE);
    	   }
    	   else{
    	       x = strtol(mymod, 0, 8);
     		    if(chmod (myfile,x) < 0){
                    //Erreurs suite à l'appel system chmod.
    	            fprintf(stderr, "Erreur chmod\n");
    	            exit(EXIT_FAILURE);
    	    	}
                else{
                    //Enoncer les changements
    		        if (c == 1){
         	             printf("Les permissions du fichier %s ont été remplacées par %s.\n", argv[3], argv[2]);
     		        }
                    //Rajouter l'extension
                    if (e == 1)
                    {
                        //Appel à la fonction de concaténation de deux String (dans mylib.h)
                        //On concat l'extension avec un '.' puis on rajoute le nom de fichier au début
                        myextension = string_concat(".",myextension);
                        rename(myfile, string_concat(myfile,myextension));
                    }
         	        return EXIT_SUCCESS;
                }
    	   }
    	}
    //Format de la valeur "permission" non admise.
	else{
	   printf("La valeur doit contenir 4 chiffre de permission, e.g: [0777] \n");
	   exit(EXIT_FAILURE);
	}
    }
}
