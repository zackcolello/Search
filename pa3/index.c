//here we will have our actual indexing/placing into our list.
//Index.c//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"
#include "tokenizer.h"
#include "sorted-list.h"



int readFile(const char* filename){

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

		str[i] = c;
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
			printf("%s\n", buffer);

		
		}

		free(buffer);

	}



	return 0;

}

int main(int argc, char **argv){

	if(argc != 3){
		printf("Error: invalid number of arguments\n");
		return -1;

	}

	readFile(argv[2]);	



	return 0;
}
