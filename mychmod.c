#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/stat.h>

struct option longopts [] = {
    {"changes", no_argument, 0, 'c'},
    {"rename", no_argument, 0, 'r'},
    {0,0,0,0}
};

int main (int argc, char *argv[]) {

    int c,r = 0;
    int t;

    while ((t = getopt_long(argc, argv, "cr:", longopts, NULL)) != -1){

        switch (t){
            case 'c':
                c = 1;
                break;
            case 'r':
		printf("Rename !");
                r = 1;
                break;
            case ':':
		//Options manquantes
                fprintf(stderr, "%s: l'option '-%c' requiert un argument.\n", argv[0], optopt);
                break;
            case '?':
            default:
                fprintf(stderr, "%s: l'option '-%c' n'est pas valide.\n", argv[0], optopt);
            break;
        }
    }
    if (argc < 3){
      fprintf(stderr, "Erreur chmod \n");
      exit(EXIT_FAILURE);
    }

    char *mymod = argv[optind];
    char *myfile = argv[optind+1];
    int x;


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
	        fprintf(stderr, "chmod error\n");
	        exit(EXIT_FAILURE);
	    	}

		if (c == 1){
        	printf("Les permissions du fichier %s ont été remplacées par %s.\n", argv[3], argv[2]);
    		}
    	   return EXIT_SUCCESS;
	   }
    	}
	else{
	   printf("La valeur doit contenir 4 chiffre de permission, e.g: [0777] \n");
	   exit(EXIT_FAILURE);
	}
    }
}
