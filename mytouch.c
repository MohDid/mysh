/*
"mytouch" est une commande qui mime "touch" et permet de créer un fichier ou un dossier grâce au paramètre -d. 
    Exemple: 	mytouch -d MonDossier
		mytouch MonFichier

Auths:
    DIDOUH Mohamed
    ISHIMWE Blaise
    TOKAM George
*/


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#include "mylib.h"


int main(int argc, char *argv[]){
	int dirFlag = 0;
	int args_num;

	int t;
	int opterr=0;
	struct option longopts[] = {
		{"directory", no_argument, NULL, 'd'},
		{0, 0, 0, 0}
	};

	while((t = getopt_long(argc, argv, "d", longopts, NULL)) != -1){
		switch(t){
			case 'd':
				//Créer un dossier
				dirFlag = 1;
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

	args_num=argc-optind;
	if(dirFlag!=1){
		if(args_num == 1){
			printf("argv[1] : %s\n", argv[1]);
			//Tester si le fichier existe déja
			if(is_a_file(argv[1])){
				printf("Un fichier portant le même nom existe déjà!\n");
				return EXIT_FAILURE;
			}
			else{
				printf("Création du fichier\n");
				//Création du fichier en l'ouvrant en mode écriture 'w'
				FILE* file_ptr = fopen(argv[1], "w");
				fclose(file_ptr);
				return EXIT_SUCCESS;
			}

		}
	}
	if(dirFlag==1){
		if(args_num == 1){
			struct stat st = {0};
			//Tester si le dossier existe déjà
			if (stat(argv[2], &st) == -1){
				//Création du dossier
				mkdir(argv[2], 0700);
				printf("Création du dossier\n");
				return EXIT_SUCCESS;
			}
			else{
				printf("Dossier existe déja!\n");
				return EXIT_FAILURE;
			}
		}
		else{
			printf("Nombre d'arguments incorrecte!\n");
			return EXIT_FAILURE;
		}
	}
return EXIT_SUCCESS;
}

