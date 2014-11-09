//search.c -- our main function is here

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parsefile.h"
#include "bst.h"

void so(struct tokenNode* query, struct Tree* tree){

	struct fileNode *result = (struct fileNode*)malloc(sizeof(struct fileNode));
	result->child = NULL;
	result->parent = NULL;
	result->path = NULL;
	
	struct tokenNode *ptr = query;


	//traverse through query list, search BST for each ptr node
	while(ptr != NULL){

		//traverse tree
		struct bstNode *BSTptr = tree->root;

		while(BSTptr != NULL){

			//found token
			if(strcmp(BSTptr->token, ptr->token) == 0){
				//add to list of filenodes

				struct fileNode *childptr;				
				childptr = BSTptr->child;

				while(childptr != NULL){

					//first filenode
					if(result->path == NULL){
						result->path = (char*)malloc(strlen(childptr->path));
						strcpy(result->path, childptr->path);
						printf("result path is: %s\n", result->path);	
					//not first filenode
					}else{
						
					

					}
					childptr = childptr->child;
				}				


			}else if(strcmp(BSTptr->token, ptr->token) > 0){
				//go left in tree

				BSTptr = BSTptr->left;

			}else{
				//go right in tree

				BSTptr = BSTptr->right;
			}
		}

		ptr = ptr->sibling;
	}

}

void sa(struct tokenNode* query, struct Tree* tree){


}

int main(int argc, char **argv){

	struct Tree *tree = (struct Tree*)malloc(sizeof(struct Tree));
	struct bstNode;
	int flag;


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

	
	tree->root = LLtoBST(ls);	
//	printBST(tree->root);
	
	char* input= malloc(1000); //need to make sure input does not go out of bounds

	char* token;

	//keep looping until input is 'q'

	while(fgets(input, 1000, stdin)){ //need to fix input != 'q'

		//put terminating bit at end of word, so we can quit with just 'q'
		input[strlen(input) -1] = '\0';
		
		if (strcmp(input, "q") == 0){
			printf("Breaking\n");
			break;
		}

		token = strtok(input, " ");
		
		if(strcmp(token, "sa") == 0){
			flag = 0;		

		}else if(strcmp(token, "so") == 0){
			flag = 1;
		}else{
			fprintf(stderr, "incorrect input.\n");
			continue;
		}

		token = strtok(NULL, " ");

		if(token == NULL){
			fprintf(stderr, "incorrect input.\n");
			continue;
		}

		struct tokenNode *tNode;
		struct tokenNode *head;
		tNode = (struct tokenNode*)malloc(sizeof(struct tokenNode));
		tNode->token = token;
		tNode->sibling = NULL;
		tNode->child = NULL;
		head = tNode;

		token = strtok(NULL, " ");

		while(token != NULL){	
			
			struct tokenNode *newTnode = (struct tokenNode*)malloc(sizeof(struct tokenNode));
			newTnode->token = token;
			newTnode->sibling = NULL;
			newTnode->child = NULL;

			tNode->sibling = newTnode;
			tNode = newTnode;

			token = strtok(NULL, " ");
		}

		switch(flag){
		case 0:
			sa(head, tree);	
			break;

		case 1:
			so(head, tree);
			break;

		}

/* build list
		struct tokenNode *temp = head; 
		while(temp != NULL){
			printf("%s\n", temp->token);
			
			temp = temp->sibling;
		}
*/
	}

	printf("Session ended.\n");

	return 0;
}
