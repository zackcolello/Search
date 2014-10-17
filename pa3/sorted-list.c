//sorted-list.c//
#include "sorted-list.h"
#include "tokenizer.h"
#include "index.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct List* SLCreate(){
	struct List *newSL;
	newSL = (struct List*)malloc(sizeof(struct List));
	newSL->head=NULL;


}

void SLInsert(struct List *list, char* string, const char* path){

	

	if (list->head == NULL){ //Node is first, create head
		
		struct tokenNode *newHeadNode;
		newHeadNode = (struct tokenNode*)malloc(sizeof(struct tokenNode));	

		newHeadNode->token = (char*)malloc(strlen(string)+1);
		strcpy(newHeadNode->token, string);

		struct fileNode *newFileNode; //create new node for this file
		newFileNode = (struct fileNode*)malloc(sizeof(struct fileNode));
		newFileNode->path =(char*)malloc(strlen(path)+1);
		strcpy(newFileNode->path, path);

		newHeadNode->child = newFileNode;
		newFileNode->count = 1;
		
		list->head=newHeadNode;
		printf("newTokenNode is %s, newFileNode is %s\n", newHeadNode->token, newFileNode->path);

		printf("head from SLinsert is %s\n", list->head->token);

		return;
	}else{




	}
}


void printList(struct tokenNode *head){

	struct tokenNode *tempT = NULL;
	struct fileNode *tempF = NULL;
	tempT = head;
	tempF = head->child;


	while(tempT){

		printf("%s\n", tempT->token);

		while(tempF){
			printf("%s, %d\n", tempF->path, tempF->count);	
			


		}
	}



}
