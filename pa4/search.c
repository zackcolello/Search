//search.c -- our main function is here

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parsefile.h"
#include "sorted-list.h"

int main(int argc, char **argv){

	if (argc != 2){
		fprintf(stderr, "Error: invalid number of arguments.\n");
		return -1;
	}

	FILE *fp;

	fp = fopen(argv[1], "r");

	if(fp == NULL){
		fprintf(stderr, "Invalid file name.\n");
		return -1;
	}	

	struct List* ls = buildLL(fp);	

	
	
	char* input= malloc(1000); //need to make sure input does not go out of bounds


/* do not delete this
	//keep looping until input is 'q'

	while(fgets(input, 1000, stdin)){ //need to fix input != 'q'

		//put terminating bit at end of word, so we can quit with just 'q'
		input[strlen(input) -1] = '\0';
		
		if (strcmp(input, "q") == 0){
			printf("Breaking\n");
			break;
		}

		printf("input is: %s\n", input);

	}

*/
	printf("Session ended.\n");

	return 0;
}
