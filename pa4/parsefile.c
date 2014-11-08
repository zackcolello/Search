//parsefile.c -- parses inverted index file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorted-list.h"
#include "parsefile.h"



struct List* buildLL(FILE *filep){
	
	int c, i;
	char* buffer = (char*)malloc(1000);
	char* testbuff = "<list> ";
	char testbuff2[8];
	char* trimmedbuffer;

	char* filetestbuffer;
	char* firstSeven = malloc(1000);
	char* filetestbuffer2;
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
	
		}else{ //line is not a token, it is a path

			struct fileNode *lastFileNode;


			while(1){

				strncpy(firstSeven, buffer, 7);

				if(strcmp(firstSeven, "</list>") == 0){
					break;
				}


				filetestbuffer = (char*)malloc(1000);				

		
				strcpy(filetestbuffer, buffer);
				filetestbuffer[strlen(filetestbuffer)] = '\0';

				//remove comma and count from file	
				int commaindex = strcspn(filetestbuffer, ",");
				filetestbuffer2 = (char*)malloc(1000);	

				strncpy(filetestbuffer2, filetestbuffer, commaindex);
							//make fileNode
	

	
				struct fileNode *fileTemp = (struct fileNode*)malloc(sizeof(struct fileNode));	
				fileTemp->path = (char*)malloc(strlen(filetestbuffer2)+1);
				fileTemp->child = NULL;
				fileTemp->count = 0;

				strcpy(fileTemp->path, filetestbuffer2);	


				if(lastNode->child == NULL){ //fileTemp will be first child
					lastNode->child = fileTemp;
					lastFileNode = fileTemp;
				
				}else{ //traverse fileNodes to place fileTemp at end

					lastFileNode->child = fileTemp;
					lastFileNode = fileTemp;

				}

				fgets(buffer, 1000, filep);
				//free(filetestbuffer);
			}
		}
	}

	//printlist(ls);

	return ls;

}


void printlist(struct List *ls){

	struct tokenNode *tempdude;
	tempdude = ls->head;
	struct fileNode *tempFileNode;
	tempFileNode = tempdude->child;


	while(tempdude != NULL){

		printf("node is %s\n", tempdude->token);

		while(tempFileNode != NULL){
			
			printf("\t %s \n", tempFileNode->path);
			tempFileNode = tempFileNode->child;
		}

		tempdude = tempdude->sibling;

		if(tempdude != NULL){
			tempFileNode = tempdude->child;


		}
	}
}
