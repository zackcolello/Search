//parsefile.c -- parses inverted index file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorted-list.h"
#include "parsefile.h"


//buildLL takes in a file pointer, and returns a List pointer of a new 2D Linked List.
//buildLL scans the file line by line, and creates tokenNodes and fileNodes.
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


	//scan file line by line, storing in buffer
	while(fgets(buffer, 1000, filep)){

		//copy first 7 characters to check if line should be put in a tokenNode
		strncpy(testbuff2, buffer, 7);

		//line is a token
		if(strcmp(testbuff2, testbuff) == 0){
			

			trimmedbuffer = &buffer[7];

			struct tokenNode *temp = (struct tokenNode*)malloc(sizeof(struct tokenNode));
			temp->token = (char*)malloc(sizeof(trimmedbuffer)+1);
			strncpy(temp->token, trimmedbuffer, strlen(trimmedbuffer)-1);
			temp->sibling = NULL;
			temp->child = NULL;

			if(ls->head == NULL){ //token is first in list to be returned
				
				ls->head = temp;
				lastNode = temp;
			}else{
				lastNode->sibling = temp;
				lastNode = temp;

			}
	
		}else{ //line is not a token, it is a path, store in a fileNode

			struct fileNode *lastFileNode;

			//iterate and only break later
			while(1){

				strncpy(firstSeven, buffer, 7);

				//if we find the end list, break out of the loop
				if(strcmp(firstSeven, "</list>") == 0){
					break;
				}


				//create a new string from line
				filetestbuffer = (char*)malloc(1000);				
		
				strcpy(filetestbuffer, buffer);
				filetestbuffer[strlen(filetestbuffer)] = '\0';

				//remove comma and count from file line	
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
			}
		}
	}
	free(firstSeven);
	free(filetestbuffer);
	free(filetestbuffer2);
	free(buffer);
	return ls;

}

//printlist takes in a list pointer and prints a 2D LL.
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
