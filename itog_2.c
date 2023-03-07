#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

int compare(const char* n1, const char* n2){
        FILE * g;
        g = fopen(n1, "rb");
        if(g == NULL){
                printf("NOT OPENED ohg, %s\n", n1);
                return -1;
        }
        FILE * f;
        f = fopen(n2, "rb");
        if(f == NULL){
                printf("NOT OPENED jhhj\n");
                return -1;
        }
        char a, b;
        while(fscanf(f, "%c", &a) == 1 && fscanf(g, "%c", &b)==1){
                if(a!=b){
//			printf("DIFFERENT\n");
			return 0;
		}
        }

        fclose(f); fclose(g);
        return 1;
}


int jpg_or_not(const char* dirname);
int jpg_or_not(const char* dirname){
	char b[3];
	FILE * g;
	g = fopen(dirname, "rb");
	if(g == NULL){
		printf("NOT OPENED\n");
		return -1;
	}
	fread(b, sizeof(char), 2, g);
	if((unsigned char)b[0] == 255  && (unsigned char)b[1] == 216){
//		printf("%s: %hhu %hhu\n", dirname, b[0], b[1]);
		fclose(g);
		return 1;
	}

/*	printf("%s: %c, %c, %c, %c, %c, %c\n", dirname, b[0], b[1], b[2], b[3], b[4], b[5]);
*/
/*	printf("%s: %hhu %hhu \n", dirname, b[0], b[1]);
*/	fclose(g);
	return 0;
}

int listFiles(const char* dirname, int count);
int listFiles(const char* dirname, int count){
        DIR* dir = opendir(dirname);
        if(dir == NULL){	
		printf("ERROR!");
                return -1;
        }
	
	
        struct dirent* entity;
        entity = readdir(dir);
        while(entity != NULL){
		count+=1;
		char path[100];
                path[0] = 0;
                strcat(path, dirname);
                strcat(path, "/");
                strcat(path, entity->d_name);
		
		if(jpg_or_not(path) == 1 && strcmp(entity->d_name, ".")!=0 && strcmp(entity->d_name, "..")!=0){
			printf("%s\n", entity->d_name);
		}

                if(entity->d_type== DT_DIR && strcmp(entity->d_name, ".")!=0 && strcmp(entity->d_name, "..")!=0){
                	char path[100];
			path[0] = 0;
			strcat(path, dirname);
			strcat(path, "/");
			strcat(path, entity->d_name);
		        count = listFiles(path, count);
                }
                entity = readdir(dir);
        }

        closedir(dir);
	return count;
}

int comp(const char* dirname, int i, int n, int k, char* name){
//	printf("NAME: '%s'\n", name);

        DIR* dir = opendir(dirname);
        if(dir == NULL){
                printf("ERROR!");
                return -1;
        }
	
        struct dirent* entity;
        entity = readdir(dir);

        while(entity != NULL){
                char path[100];
                path[0] = 0;
                strcat(path, dirname);
                strcat(path, "/");
                strcat(path, entity->d_name);

                if(jpg_or_not(path) == 1 && strcmp(entity->d_name, ".")!=0 && strcmp(entity->d_name, "..")!=0){
                	if(k==i){
				char name2[100];
				name2[0]=0;
                		strcat(name2, dirname);
                		strcat(name2, "/");
                		strcat(name2, entity->d_name);
				strcpy(name, name2);
				//printf("THENAME: %s", name);
			}
			if(k>i && strlen(name)>0){
				if(compare(name, path)==1) printf("A PARE: %s and %s\n", name, path);
			}
                        k++;
                }

//k++;
//		printf("%d %d\n", k, i);
                if(entity->d_type== DT_DIR && strcmp(entity->d_name, ".")!=0 && strcmp(entity->d_name, "..")!=0){
                        char path[100];
                        path[0] = 0;
                        strcat(path, dirname);
                        strcat(path, "/");
                        strcat(path, entity->d_name);
                        k = comp(path, i, n, k, name);
                }


                entity = readdir(dir);
        }


        closedir(dir);

	return k;
}


int main(){
	int n;
	char name[100];
	name[0] = 0;
        n = listFiles(".", 0);

	printf("LF DONE, %d\n", n);
	int i=0;

	for(i=0;i<n;i++){
		comp(".", i, n, 0, name);
        }
	return 0;
}


//old listfiles
/* int listFiles(const char* dirname);
int listFiles(const char* dirname){
        int count = 0;
        DIR* dir = opendir(dirname);
        if(dir == NULL){
                printf("ERROR!");
                return count;
        }


        struct dirent* entity;
        entity = readdir(dir);
        while(entity != NULL){
                count+=1;
                char path[100];
                path[0] = 0;
                strcat(path, dirname);
                strcat(path, "/");
                strcat(path, entity->d_name);

                if(jpg_or_not(path) == 1 && strcmp(entity->d_name, ".")!=0 && strcmp(entity->d_name, "..")!=0){
                        printf("%s\n", entity->d_name);
                }

                if(entity->d_type== DT_DIR && strcmp(entity->d_name, ".")!=0 && strcmp(entity->d_name, "..")!=0){
                        char path[100];
                        path[0] = 0;
                        strcat(path, dirname);
                        strcat(path, "/");
                        strcat(path, entity->d_name);
                        listFiles(path);
                }
                entity = readdir(dir);
        }

        closedir(dir);
        return count;
}


*/
