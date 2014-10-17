//sorted-list.c//
#include "sorted-list.h"
#include "tokenizer.h"
#include "index.h"

#include <stdlib.h>
#include <stdio.h>



void SLInsert(struct tokenNode *head, char* string, const char* path){

	if (head == NULL){ //Node is first, create head
		
		struct tokenNode *newHeadNode;
		newHeadNode = (struct tokenNode*)malloc(sizeof(struct tokenNode));	

		newHeadNode->token = string;

		struct fileNode *newFileNode; //create new node for this file
		newFileNode = (struct fileNode*)malloc(sizeof(struct fileNode));
		newFileNode->path = path;

		newHeadNode->child = newFileNode;
		newFileNode->count = 1;

	//	printf("newTokenNode is %s, newFileNode is %s\n", newHeadNode->token, newFileNode->path);

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
