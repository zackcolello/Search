//This .c file contains the main for our code and the functions to read, write, and traverse files.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "sorted-list.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
void writefile(const char* outputFile, struct List *ls){

	FILE *fp;
	
	struct stat fileStat; //check if output file exists, warn user about overwriting
	char answer;
	
	if(stat(outputFile, &fileStat) == 0){

		if( fileStat.st_mode & S_IFDIR )
	    	{
	       	//directory
		printf("You cannot write to a dirctory. Exiting Indexer.\n");
		return;

		}else if( fileStat.st_mode & S_IFREG)  {
                    //it's a file
	
			printf("WARNING: The output file you have specified, %s, already exists in this directory.\nAre you sure you want to overwrite this file? Enter (y or n):\n", outputFile);
		
			scanf("%c", &answer);
	

			if(answer == 'y'){
				printf("Overwriting.\n");	
				//continue and overwrite file
		
			}else if(answer == 'n'){
		
				printf("The file has not been overwritten, exiting program.\n");
				return;		

			}else{
		
				printf("Not valid input, expecting character 'y' or 'n'. Exiting program.\n");
				return;
			}

		}

	}

	fp = fopen(outputFile,"w");

	struct tokenNode *tempT;
	struct fileNode *tempF;



	tempT = ls->head;
	tempF = tempT->child;


	while(tempT){

		fprintf(fp,"<list> %s\n", tempT->token);

		while(tempF){
			fprintf(fp,"%s, %d\n", tempF->path, tempF->count);    
			tempF = tempF->child;

		}

		fprintf(fp,"</list>\n");

		tempT = tempT->sibling;

		if(tempT!= NULL){
			tempF = tempT->child;
		}

	}

	fclose(fp);
}

int readFile(struct List *list, const char* filename){

	int fileSize = 0;
	char* str;
	int i = 0;
	char c;
	char* buffer;
	
	int rval;
	rval =access(filename,R_OK);

	if (rval==0){
	//you have read permission

	}
	else if(errno==EACCES){
	printf("you do not have access to %s\n",filename);
	return 0;

	}


	//read in file, put in big string 
	FILE *filePtr = fopen(filename, "r");
	
	if(filePtr == NULL){
		return -1;
	}

	fseek(filePtr, 0, SEEK_END);
	fileSize = ftell(filePtr);
	fseek(filePtr, 0, SEEK_SET);
	str = (char*)malloc(sizeof(char)*fileSize+1);
	
	while((c = fgetc(filePtr)) != EOF){

		str[i] = tolower(c);
		i++;

	}

	str[i] = '\0';
	fclose(filePtr);


	//tokenize string
	TokenizerT *tok;
	tok = TKCreate(str);	


	indexPointer = tok->input;

	while (indexPointer != '\0'){

		buffer = TKGetNextToken(tok);

		if(strlen(buffer) > 0){

			SLInsert(list, buffer, filename);
		}

		free(buffer);

	}
	TKDestroy(tok);
	free(str);
	return 0;

}

int directoryTraverse(struct List *list, const char* parentDir){
//add argument to take in char* path, and sorted-list

	DIR *dir;
	struct dirent *dent; //from dirent.h
	char* path;


	dir = opendir(parentDir);



	if (dir == NULL){ // parentDir is not a directory, parentDir is a file.

		readFile(list, parentDir);
			
	}else{
		while((dent=readdir(dir))!=NULL){
			
			if((strcmp(dent->d_name,".")==0)||(strcmp(dent->d_name,"..")==0)){
				continue;
			}
			else{
				path = (char*)malloc(strlen(parentDir)+strlen(dent->d_name)+2);
				strcpy(path, parentDir);
				strcat(path, "/\0");
				
				strcat(path, dent->d_name);
				path[strlen(path)]= '\0';
				directoryTraverse(list, path);
				free(path);	

			}
		}
	
		closedir(dir);
	}


	return 1;


}


int main(int argc, char **argv){

	if(argc != 3){
		printf("Error: invalid number of arguments\n");
		return -1;
	}
	
	if(strcmp(argv[1],argv[2])==0){
		printf("input arguments are the same file. Cannot overwrite. Exiting Indexer.\n");

		return 0;
	}

	int rval;
	char* output=argv[1];
	rval = access(output,F_OK);
	if(rval==0){
	//file exists
	}
	else if(errno==EACCES){
		printf("%s is not accessible\n", output);
		return 0;
	}

	rval = access(output, W_OK);
	if(rval==0){
		//permission to write
	}else if (errno==EACCES){
		printf("you do not have permission to write to %s\n",output);
		return 0;

	}

	struct List *list = SLCreate(); //create list to store words

	struct stat fileStat; //check if directory or file to be indexed exists
	if(stat(argv[2], &fileStat) == 0){

		directoryTraverse(list, argv[2]);


	}else{
		fprintf(stderr, "Directory or file you are trying to index does not exist.\n");	
		return -1;
	}	

	writefile(argv[1],list);
	destroyList(list);
	return 0;
}
