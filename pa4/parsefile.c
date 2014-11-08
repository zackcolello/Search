//parsefile.c -- parses inverted index file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorted-list.h"
#include "parsefile.h"



struct List buildLL(FILE *filep){
	
	int c, i;
	char* buffer = (char*)malloc(1000);
	char* testbuff = "<list> ";
	char testbuff2[8];
	char* trimmedbuffer;

	char* filetestbuffer = (char*)malloc(1000);


	struct tokenNode *lastNode;

	struct List *ls = (struct List*)malloc(sizeof(struct List));
	
	ls->head == NULL;

	while(fgets(buffer, 1000, filep)){

		strncpy(testbuff2, buffer, 7);

		if(strcmp(testbuff2, testbuff) == 0){
			
			trimmedbuffer = (char*)malloc(sizeof(buffer) - 6);

			trimmedbuffer = &buffer[7];

			struct tokenNode *temp = (struct tokenNode*)malloc(sizeof(struct tokenNode));
			temp->token = (char*)malloc(sizeof(trimmedbuffer)+1);
			strcpy(temp->token, trimmedbuffer);
			temp->sibling = NULL;
			temp->child = NULL;

			if(ls->head == NULL){ //token is first in
				
			//	printf("head node is %s\n", ls->head->token);
				ls->head = temp;
				lastNode = temp;
			}else{
				//printf("temp node is %s\n", temp->token);
				lastNode->sibling = temp;

				lastNode = temp;

			}
	
			printf("new buffer is now %s\n", trimmedbuffer);
		}else{ //line is not a token, it is a file

			while(strncmp(buffer, "</list>", 7) != 0){
			
				printf("buffer is: %s\n", buffer);		
	
				int commaindex = strcspn(buffer, ",");
				printf("comma index is: %d\n", commaindex);

				strncpy(filetestbuffer, buffer, commaindex);

				printf("should've removed comma now: %s\n", filetestbuffer);
			
				fgets(buffer, 1000, filep);

			}

		}
	}

/*	printf("token's head node is %s\n", ls->head->token);

	struct tokenNode *tempdude = (struct tokenNode*)malloc(sizeof(struct tokenNode));
	tempdude = ls->head;
	while(tempdude != NULL){

	printf("node is %s\n", tempdude->token);
	tempdude = tempdude->sibling;

	}
*/
}

