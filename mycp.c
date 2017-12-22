/*
"mycp" est une commande qui mime "cp" et permet de copier un fichier source vers un dossier de destination. 
Elle peut prendre des paramètres comme backup ou verbose pour afficher des indications supplémentaires.
    Exemple: mycp -v MonFichier CheminDeDestination

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
#include <sys/stat.h>
#include <errno.h>
#include <libgen.h>

#include "mylib.h"

#define COL_RED "\x1b[31m"
#define COL_OFF "\x1b[0m"

int main(int argc, char *argv[]){
	int verboseFlag = 0;
	int backupFlag = 0;

	FILE *pfile;

	char newSource[100];
	char newDest[100];
	int argindex;
	char **fileNames;
	int fileNames_len;
	int index = 0;  /*	Pour parcourir des tables en boucles locales; utilisée pour p.ex.
			pour stocker les noms des répertoire  */

	int t;
	int opterr=0;
	struct option longopts[] = {
		{"verbose", no_argument, NULL, 'v'},
		{"backup", no_argument, NULL, 'b'},
		{0, 0, 0, 0}
	};

	while((t = getopt_long(argc, argv, "vb", longopts, NULL)) != -1){
		switch(t){
			case 'v':
				verboseFlag = 1;
			break;
			case 'b':
				backupFlag = 1;
			break;
			case '?':
			default:
			abort();
		}
	}

	fileNames_len=argc-optind;
	if(fileNames_len != 2) {
		printf("Nombre de paramètres incorrecte.\n");
		exit(EXIT_FAILURE);
	}
	else {
		fileNames = calloc(fileNames_len, sizeof(char*));
		for(argindex = optind; argindex < argc; argindex++){
			fileNames[argindex-optind] = strdup(argv[argindex]);
		}
		//Tester les erreurs sur le fichier source
		//0-NULL , 17-EEXIST , 21-EISDIR
		strcpy(newSource, fileNames[fileNames_len-2]);
		//Si le fichier source n'existe pas
		if(access(newSource, F_OK) == -1) {
			printf("Le fichier source ["COL_RED"%s"COL_OFF"] n'existe pas.\n", newSource);
			free(fileNames);
			return EXIT_FAILURE;
		}
		else {
			strcpy(newDest, fileNames[fileNames_len-1]);
			pfile = fopen(newDest, "wb");
			//Si le fichier destination est un dossier
			if(errno == 21) {
				char *baseName;
				int indexlast = strlen(fileNames[fileNames_len-1])-1;
				baseName = basename(fileNames[fileNames_len-2]);
				//S'il y a déjà un '/' à la fin du chemin destination
				if(fileNames[fileNames_len-1][indexlast] == '/')  fileNames[fileNames_len-1][indexlast] = '\0';
				strcpy(newDest, paths_concat(fileNames[fileNames_len-1], baseName));
				errno=0;
			}
			if(errno == 0) {
				//Si le fichier de destination existe déjà
				if(access(newDest, F_OK) != -1) {
					if(backupFlag) {
						strcat(newDest, "~");
						if(verboseFlag)
							printf("Fichier copié de: "COL_RED"%s"COL_OFF"\n vers: "COL_RED"%s"COL_OFF"\n", newSource, newDest);
						copy_file(newSource, newDest);
					}
					else {
						printf("Le fichier "COL_RED"%s"COL_OFF" existe déjà.\n", newDest);
						free(fileNames);
						return EXIT_FAILURE;
					}
				}
				else {
					if(verboseFlag)
						printf("Fichier copié de: "COL_RED"%s"COL_OFF"\n vers: "COL_RED"%s"COL_OFF"\n", newSource, newDest);
					copy_file(newSource, newDest);
				}
			}
			else {
				perror("ERREUR");
				free(fileNames);
				return EXIT_FAILURE;
			}
		}
	}

	free(fileNames);
return EXIT_SUCCESS;
}
