#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#include "mylib.h"

//#define COL_RED "\x1b[31m"
//#define COL_OFF "\x1b[0m"

int main(int argc, char *argv[]){
	int dirFlag = 0;
	int permissionFlag = 0;
	//int recursiveFlag = 0;
//	char *cvalue = NULL;

//	DIR *dir;
//	struct dirent *ent;


//	char path[1024];
//	int argindex;
//	char **fileNames;
	int args_num;
//	char **dirNames;
//	int dirNames_len;
//	int index = 0;

	int t;
	int opterr=0;
	struct option longopts[] = {
		{"directory", no_argument, NULL, 'd'},
		{"permission", no_argument, NULL, 'p'},
		{0, 0, 0, 0}
	};

	while((t = getopt_long(argc, argv, "dp:", longopts, NULL)) != -1){
		switch(t){
			case 'd':
				dirFlag = 1;
				printf("dirFlag\n");
			break;
			case 'p':
				permissionFlag = 1;
				printf("permissionFlag\n");
			break;
		/*	case 'R':
				recursiveFlag = 1;
			break;*/
			case '?':
			default:
			abort();
		}
	}

	args_num=argc-optind;
	if((dirFlag!=1) && (permissionFlag!=1)){
		if(args_num == 1){
			printf("argv[1] : %s\n", argv[1]);
			if(is_a_file(argv[1])){
				printf("Un fichier portant le même nom existe déjà!\n");
				return EXIT_FAILURE;
			}
			else{
				printf("Création du fichier\n");
				FILE* file_ptr = fopen(argv[1], "w");
				fclose(file_ptr);
				return EXIT_SUCCESS;
			}

		}
	}
	if(dirFlag==1){
		//printf("argc : %d",args_num);
		if(args_num == 1){
			struct stat st = {0};
			if (stat(argv[2], &st) == -1){
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
/*	if(fileNames_len == 0) {
		fileNames_len=1;
		printf("Pas de nom de fichiers!!\n");
	}
	else	fileNames = calloc(fileNames_len, sizeof(char*));
		for(argindex = optind; argindex < argc; argindex++){
			fileNames[argindex-optind] = strdup(argv[argindex]);
		}

	strcpy(path, " ");
	for(argindex = 0; argindex < fileNames_len; argindex++){
		if ((dir = opendir(fileNames[argindex])) != NULL) {
			printf(COL_RED "%s:\n" COL_OFF,fileNames[argindex]);
			while((ent = readdir(dir)) != NULL){
				if(dirFlag)	printf("%s\n", ent->d_name);
				else if(!startsWith(".", ent->d_name))	printf("%s\n", ent->d_name);
			}
			printf("Sous-répertoires trouvés: %s\n", path);
			if(strlen(path) > 3) //Recursive call to Main to be implemented.
					continue; //return main(argc, path);
			closedir(dir);
		}

		else{
			printf("Ici le fichier n'existe pas!");
			perror("");
			return EXIT_FAILURE;
		}
	}
*/

//	free(fileNames);
return EXIT_SUCCESS;
}

