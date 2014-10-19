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

		newHeadNode->sibling = NULL;
		newHeadNode->child = newFileNode;
		newFileNode->count = 1;
		newFileNode->child = NULL;	
		list->head=newHeadNode;

		return;
	}


	struct tokenNode *prevt=NULL;
	struct tokenNode *tempt = list->head;
	struct fileNode *tempf=NULL;
	struct fileNode *prevf=NULL;

	while(tempt!=NULL){
		if(strcmp(tempt->token, string)==0){ //found token, traverse fileNodes
			tempf=tempt->child;

			while(tempf!=NULL){
				if(strcmp(tempf->path, path)==0){ //found matching fileNode, count++
					tempf->count++;
					return;

				}
				else {
					prevf=tempf;
					tempf=tempf->child;	
					
				}

			}
			//reached end of file list, create a node
			struct fileNode *newFileNode; //create new node for this file
			newFileNode = (struct fileNode*)malloc(sizeof(struct fileNode));
			newFileNode->path =(char*)malloc(strlen(path)+1);
			strcpy(newFileNode->path, path);

			prevf->child = newFileNode;
			newFileNode->count = 1;
			newFileNode->child = NULL;
	
			return;

		}else if(strcmp(tempt->token, string) >0){ //Found place to put new tokenNode

			struct tokenNode *newTNode;
			newTNode = (struct tokenNode*)malloc(sizeof(struct tokenNode));	

			newTNode->token = (char*)malloc(strlen(string)+1);
			strcpy(newTNode->token, string);
	
			struct fileNode *newFileNode; //create new node for this file
			newFileNode = (struct fileNode*)malloc(sizeof(struct fileNode));
			newFileNode->path =(char*)malloc(strlen(path)+1);
			strcpy(newFileNode->path, path);
		
			newTNode->child = newFileNode;
			newFileNode->count = 1;
			newFileNode->child = NULL;
	
			if(prevt==NULL){
				list->head=newTNode;
			}else{
				prevt->sibling=newTNode;
			}

			newTNode->sibling=tempt;
		

			return;


		}else{
			prevt=tempt;
			tempt=tempt->sibling;
		}

		
	}
	struct tokenNode *newTNode;
	newTNode = (struct tokenNode*)malloc(sizeof(struct tokenNode));	

	newTNode->token = (char*)malloc(strlen(string)+1);
	strcpy(newTNode->token, string);
	
	struct fileNode *newFileNode; //create new node for this file
	newFileNode = (struct fileNode*)malloc(sizeof(struct fileNode));
	
	newFileNode->path =(char*)malloc(strlen(path)+1);
	strcpy(newFileNode->path, path);
	
	newTNode->child = newFileNode;
	newFileNode->count = 1;
		
	prevt->sibling=newTNode;
	newTNode->sibling = tempt;
	
}


void printList(struct List *list){

	struct tokenNode *tempT;
	struct fileNode *tempF;



	tempT = list->head;
	tempF = tempT->child;


	while(tempT){

		printf("%s\n", tempT->token);

		while(tempF){
			printf("\t%s, %d\n", tempF->path, tempF->count);	
			tempF = tempF->child;


		}
		
		tempT = tempT->sibling;
		
		if(tempT!= NULL){
		tempF = tempT->child;
		}
	}


}


