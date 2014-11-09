//search.c -- our main function is here

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parsefile.h"
#include "bst.h"


void printList(struct List *list){

	struct tokenNode *tempT;
	struct fileNode *tempF;

	tempT = list->head;
	tempF = tempT->child;

	while(tempT){
		printf("%s\n", tempT->token);
	
		while(tempF){

			printf("\t%s\n", tempF->path);
			tempF = tempF->child;
		}

		tempT = tempT->sibling;

		if(tempT!= NULL){
		tempF = tempT->child;
		}
	}

}

struct fileNode* so(struct tokenNode* query, struct Tree* tree){

	struct fileNode *resulthead = (struct fileNode*)malloc(sizeof(struct fileNode));
	resulthead->child = NULL;
	resulthead->parent = NULL;
	resulthead->path = NULL;
	struct fileNode *printPtr;	
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
					struct fileNode *resultPtr;
					//first filenode
					if(resulthead->path == NULL){
						resulthead->path = (char*)malloc(strlen(childptr->path));
						strcpy(resulthead->path, childptr->path);
					//not first filenode
					}else{
						resultPtr=resulthead;
						while(resultPtr != NULL){
							if(strcmp(resultPtr->path,childptr->path)==0){
								break;
							}else{
								resultPtr=resultPtr->child;
							}

						
						}
						if(resultPtr==NULL){
							struct fileNode* temp = (struct fileNode*)malloc (sizeof(struct fileNode));
							temp->path=(char*)malloc(strlen(childptr->path));
							strcpy(temp->path,childptr->path);
							temp->child=resulthead;
							resulthead=temp;
							resulthead->parent=NULL;
						}

					}
					childptr = childptr->child;
				}				
				break;

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
	//print
	
	return resulthead;
}

struct fileNode* sa(struct tokenNode* query, struct Tree* tree){
	 
	 struct List *ls= (struct List*)malloc(sizeof(struct List));
	 ls->head=query;
	 int count = countNodes(ls);
	 int printFlag=0; 

	struct fileNode *resulthead = (struct fileNode*)malloc(sizeof(struct fileNode));
	resulthead->child = NULL;
	resulthead->parent = NULL;
	resulthead->path = NULL;
	struct fileNode *printPtr;	
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
					struct fileNode *resultPtr;
					//first filenode
					if(resulthead->path == NULL){
						resulthead->path = (char*)malloc(strlen(childptr->path));
						strcpy(resulthead->path, childptr->path);
						resulthead->count=1;
					//not first filenode
					}else{
						resultPtr=resulthead;
						while(resultPtr != NULL){
							if(strcmp(resultPtr->path,childptr->path)==0){
								resultPtr->count++;
								break;
							}else{
								resultPtr=resultPtr->child;
							}

						
						}
						if(resultPtr==NULL){
							struct fileNode* temp = (struct fileNode*)malloc (sizeof(struct fileNode));
							temp->path=(char*)malloc(strlen(childptr->path));
							strcpy(temp->path,childptr->path);
							temp->child=resulthead;
							temp->count=1;
							resulthead=temp;
							resulthead->parent=NULL;
						}

					}
					childptr = childptr->child;
				}				
				break;

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
	//print
	return resulthead;


}

//Search NOR
struct fileNode* sno(struct tokenNode* query, struct Tree* tree, struct fileNode* head){

	int print=1;
	struct fileNode *temp, *stemp, *results, *new;

	temp = head;


	struct fileNode* soNode= so(query, tree);

	if(soNode == NULL){
		return NULL;
	}
	stemp=soNode;
	

	while(temp){
		print=1;
		while(stemp){
			if (strcmp(temp->path,stemp->path)==0){
				print=0;
			}
			stemp=stemp->child;
		}
		stemp=soNode;
		if (print){


			printf("%s ",temp->path);
		}
		temp=temp->child;

	}
	
}


void printResult(struct fileNode* head, int flag, int count){

	struct fileNode* printPtr;
	printPtr=head;
	int printFlag = 0;

	switch(flag){
	case 0:
		printPtr=head;
		if (printPtr->path ==NULL){
			printf("No results found.\n");
			return;
		}
		while(printPtr){
			if(printPtr->child == NULL){
				printf("%s\n", printPtr->path);
				break;
			}
	
			printf("%s, ",printPtr->path);
			printPtr= printPtr->child;
	
		}
		break;
	
	case 1:
	
		if (printPtr->path ==NULL){
			printf("No results found.\n");
			return;
		}
		while(printPtr){
			if(printPtr->child == NULL){
				if(printPtr->count==count){
					if (!printFlag){
						printf("%s", printPtr->path);
						printFlag=1;
					}else{
						printf(", %s",printPtr->path);
					}


				}
				break;
			}
			if(printPtr->count==count){
			
				if (!printFlag){
						printf("%s", printPtr->path);
						printFlag=1;
					}else{
						printf(", %s",printPtr->path);
					}

			}
			printPtr= printPtr->child;
		}
		if (!printFlag){
			printf("No results found.");
		}
		printf("\n");
			break;
	}



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





/***********************************************************************************************/
	//make list of File nodes to be used later
	struct tokenNode* Tptr = ls->head;
	struct fileNode* Fptr = Tptr->child;

	struct fileNode* temp = NULL, *tmptr=NULL;
	struct fileNode* allfilehead = NULL;
	int fileflag=0;

	while(Tptr){
		while(Fptr){
			
			tmptr=allfilehead;
			while(tmptr){
				fileflag=0;
				if (allfilehead==NULL){
					temp = (struct fileNode*)malloc(sizeof(struct fileNode));
					temp->path = (char*)malloc(strlen(Fptr->path)+1);
					strcpy(temp->path, Fptr->path);

					temp->child = allfilehead;
					allfilehead = temp;
				}
		
				if(strcmp(tmptr->path,Fptr->path)==0){
					fileflag=1;
					break; //found same
					
				}
				tmptr=tmptr->child;
			}
			if(!fileflag){
			temp = (struct fileNode*)malloc(sizeof(struct fileNode));
			temp->path = (char*)malloc(strlen(Fptr->path)+1);
			strcpy(temp->path, Fptr->path);

			temp->child = allfilehead;
			allfilehead = temp;
			}
			Fptr = Fptr->child;
		}

		Tptr = Tptr->sibling;

		if(Tptr){
			Fptr = Tptr->child;
		}

	}
/****************************************************************************************************/




	tree->root = LLtoBST(ls);	
//	printBST(tree->root);

	char* input= malloc(1000); //need to make sure input does not go out of bounds

	char* token;

	//keep looping until input is 'q'

	while(fgets(input, 1000, stdin)){ //need to fix input != 'q'

		//put terminating bit at end of word, so we can quit with just 'q'
		input[strlen(input) -1] = '\0';
		
		if (strcmp(input, "q") == 0){
			break;
		}

		token = strtok(input, " ");
		
		if(token==NULL){
			fprintf(stderr,"incorrect input.\n");
			continue;
		}
		
		if(strcmp(token, "so") == 0){
			flag = 0;		
		}else if(strcmp(token, "sa") == 0){
			flag = 1;
		}else if(strcmp(token, "sxo") == 0){
			flag = 2;
		}else if(strcmp(token, "sno") == 0){
			flag = 3;
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

		//Make new list to find count
		struct List *ls2 = (struct List*)malloc(sizeof(struct List));
		ls2->head = head;
		struct fileNode* result;
		int count = 0;

		switch(flag){
		case 0: //SO
			result = so(head, tree);
			printResult(result, 0, 0);
			break;

		case 1: //SA
			count = countNodes(ls2);
			result = sa(head, tree);
			printResult(result, 1, count);
			break;
		case 2: //SXOR
			result = sa(head, tree);
			printResult(result, 1, 1);
			break;
		case 3: //SNO
			result = sno(head, tree, allfilehead);
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
