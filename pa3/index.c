//here we will have our actual indexing/placing into our list.
//Index.c//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"
#include "tokenizer.h"
#include "sorted-list.h"
#include <sys/types.h>
#include <dirent.h>



int readFile(struct tokenNode *head, const char* filename){

	int fileSize = 0;
	char* str;
	int i = 0;
	char c;
	char* buffer;

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
			printf("%s\n", buffer);	//insert into sorted-list here.
			SLInsert(head, buffer, filename);
		
		}

		free(buffer);

	}



	return 0;

}

int directoryTraverse(struct tokenNode *head, const char* parentDir){
//add argument to take in char* path, and sorted-list

	DIR *dir;
	struct dirent *dent; //from dirent.h
	printf("parentDir is %s\n", parentDir);
	dir = opendir(parentDir);
	
	if (dir == NULL){ // parentDir is not a directory, parentDir is a file.
		printf("dir is Null\n");

		readFile(head, parentDir);

	
			
	}else{
		while((dent=readdir(dir))!=NULL){
			
			if((strcmp(dent->d_name,".")==0)||(strcmp(dent->d_name,"..")==0)){
				continue;
			}
			else{
				directoryTraverse(head, dent->d_name);
				printf("dent name is %s\n",dent->d_name);
			}
		}
	
		closedir(dir);;
	}


	return 1;


}


int main(int argc, char **argv){

	if(argc != 3){
		printf("Error: invalid number of arguments\n");
		return -1;

	}

	struct tokenNode *head = NULL;

	//readFile(argv[2]);	
	directoryTraverse(head, argv[2]);

//	printf("head from main is %s\n", head->token);
//	printList(head);

	return 0;
}
