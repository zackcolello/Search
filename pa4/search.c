//search.c -- our main function is here

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parsefile.h"
#include "bst.h"

//printList takes in a list pointer, and prints all tokens in this list,
//along with the files that include those tokens. Used for testing.
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


//so -- Search Or. Takes in the first tokenNode ptr query in a linked list of queries,
//as well as the binary tree to search.
//Returns the first fileNode ptr in a linked list with all files in the tree that
//contain at least one of the queries in the query list.
struct fileNode* so(struct tokenNode* query, struct Tree* tree){

	struct fileNode *resulthead = (struct fileNode*)malloc(sizeof(struct fileNode));
	resulthead->child = NULL;
	resulthead->parent = NULL;
	resulthead->path = NULL;
	struct fileNode *printPtr;	
	struct tokenNode *ptr = query;


	//traverse through query linked list to search BST for each ptr node
	while(ptr != NULL){

		//traverse BStree for given ptr
		struct bstNode *BSTptr = tree->root;

		while(BSTptr != NULL){
			
			//found token in BStree
			if(strcmp(BSTptr->token, ptr->token) == 0){
				
				struct fileNode *childptr;				
				childptr = BSTptr->child;


				//search through BSTptr's filenodes and add to list
				while(childptr != NULL){
				
					struct fileNode *resultPtr;
				
					//first filenode, make resultHead
					if(resulthead->path == NULL){
						resulthead->path = (char*)malloc(strlen(childptr->path));
						strcpy(resulthead->path, childptr->path);
					
					//not first filenode, see if it's already in result linked list
					}else{
						resultPtr=resulthead;
						
						//iterate through fileNodes to find where in the list it goes
						while(resultPtr != NULL){
							
							//path is already there, break out, do not add duplicate
							if(strcmp(resultPtr->path,childptr->path)==0){
								break;
							}else{
								resultPtr=resultPtr->child;
							}

						
						}
				
						//traversed result list, did not find duplicate. Add to LL
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
	
	return resulthead;
}


//sa -- Search And. Takes in tokenNode ptr query, the first token node in an LL of terms, and a BStree to search.
//Returns the first fileNode in an LL that contains all files in the tree that contain ALL the terms given in query.
struct fileNode* sa(struct tokenNode* query, struct Tree* tree){
	 
	 struct List *ls= (struct List*)malloc(sizeof(struct List));
	 ls->head=query;
	 int count = countNodes(ls);
	 int printFlag=0; 
	free(ls);
	struct fileNode *resulthead = (struct fileNode*)malloc(sizeof(struct fileNode));
	resulthead->child = NULL;
	resulthead->parent = NULL;
	resulthead->path = NULL;
	struct fileNode *printPtr;	
	struct tokenNode *ptr = query;


	//traverse through query list
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
				
					//not first filenode, update counts of result LL
					}else{
						resultPtr=resulthead;

						while(resultPtr != NULL){

							//increase count of result nodes in LL
							if(strcmp(resultPtr->path,childptr->path)==0){
								resultPtr->count++;
								break;
							}else{
								resultPtr=resultPtr->child;
							}

						
						}

						//did not find fileNode in result list, first occurence of path
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
	
	return resulthead;


}

//sno -- Search NOR. Takes in first tokenNode ptr query in a list of terms to search, a tree to search,
//and an LL of all paths in the entire binary tree. Returns the first fileNode ptr that contains 
//none of the given search terms in query.
struct fileNode* sno(struct tokenNode* query, struct Tree* tree, struct fileNode* head){

	int print=1; //flag used to know whether to print a node
	int firstflag = 1; //flag used for printing to know whether node is first or not

	struct fileNode *temp, *stemp, *results, *new;

	temp = head;

	//Create a LL from so (search or) function
	struct fileNode* soNode= so(query, tree);

	if(soNode->path == NULL){//None of the given terms are in the LL
		
		//print all paths since terms did not exist in LL
		while(temp){

			if(firstflag){
				printf("%s",temp->path);
				firstflag = 0;
			}else{
				printf(", %s", temp->path);
			
			}

			temp=temp->child;
		
		}
		printf("\n");
		return soNode;
	}
	stemp=soNode;

		if(temp == NULL){
		printf("No results found.\n");
		return soNode;
	}
	
	//Traverse all nodes that exist in the file
	while(temp){
		print=1;

		//Traverse all nodes returned by so function
		while(stemp){

			//if a node from the file appears in so, set print flag to false
			if (strcmp(temp->path,stemp->path)==0){
				print=0;
			}
			stemp=stemp->child;
		}
		stemp=soNode;

		if (print){

			//path is in file but not in so LL, so it is NOR, print
			//use flags to know when to use commas, space etc to get correct output
			if(firstflag == 1){
				printf("%s", temp->path);
				firstflag = 0;
			}


			else if(firstflag == 0){
				printf(", %s",temp->path);
			}
		}
		temp=temp->child;

	}
	if (firstflag){
	printf("No results found.");
	}
	printf("\n");
	return soNode;
}

struct fileNode* sna(struct tokenNode* query, struct Tree* tree, struct fileNode* head){

	struct List* ls = (struct List*)malloc(sizeof(struct List));
	ls->head=query;

	int count = countNodes(ls);
	int print=1; //flag used to know whether to print a node
	int firstflag = 1; //flag used for printing to know whether node is first or not
	free(ls);	
	struct fileNode *temp, *stemp, *results, *new;

	temp = head;

	//Create a LL from so (search or) function
	struct fileNode* saNode= sa(query, tree);

	if(saNode->path == NULL){//None of the given terms are in the LL
		
		//print all paths since terms did not exist in LL
		while(temp){

			if(firstflag){
				printf("%s",temp->path);
				firstflag = 0;
			}else{
				printf(", %s", temp->path);
			
			}

			temp=temp->child;
		
		}
		printf("\n");
		return saNode;
	}
	stemp=saNode;

		if(temp == NULL){
		printf("No results found.\n");
		return saNode;
	}
	
	//Traverse all nodes that exist in the file
	while(temp){
		print=1;

		//Traverse all nodes returned by so function
		while(stemp){

			//if a node from the file appears in so, set print flag to false
			if (strcmp(temp->path,stemp->path)==0&&stemp->count==count){
				print=0;
			}
			stemp=stemp->child;
		}
		stemp=saNode;


		if (print){

			//path is in file but not in so LL, so it is NOR, print
			//use flags to know when to use commas, space etc to get correct output
			if(firstflag == 1){
				printf("%s", temp->path);
				firstflag = 0;
			}


			else if(firstflag == 0){
				printf(", %s",temp->path);
			}
		}
		temp=temp->child;

	}
	if (firstflag){
	printf("No results found.");
	}
	printf("\n");
	return saNode;

}


//printResult takes in a fileNode head ptr of an LL to print, a flag of what search type was used, and
//a count that stores the size of the LL.
//printResult returns void and prints the LL.
void printResult(struct fileNode* head, int flag, int count){

	struct fileNode* printPtr;
	printPtr=head;
	int printFlag = 0;

	switch(flag){
	case 0: //search OR
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
	
	case 1: //search AND
	
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

			//only print fileNodes that contain all terms
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
void recDestroy (struct bstNode* root){

	if(root==NULL){
		return;
	}
	recDestroy(root->left);
	recDestroy(root->right);
	struct fileNode *target=root->child;
	while(target){
		root->child=root->child->child;
		free(target->path);
		free(target);
		target=root->child;
	}
	free(root->token);
	free(root);

}
void destroyTree(struct Tree *tree){
	struct bstNode* target=tree->root;
	recDestroy(target);
	free(tree);

}

void destroyResults(struct fileNode* resulthead){

	struct fileNode* target=resulthead;
	while(target){
		resulthead=resulthead->child;
		if (target->path){
		free(target->path);
		}
		free(target);
		target=resulthead;
	
	}

}
void destroyQ(struct List* ls){
	struct tokenNode* target=ls->head;
	while(target){
		ls->head=ls->head->sibling;
		free(target);
		target=ls->head;
	}
	free(ls);
}


//Main provides the interface for the user to enter search terms.
//so <terms> : Search OR
//sa <terms> : Search AND
//sxo <terms> : Search Exclusive OR
//sno <terms> : Search NOR
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
	fclose(fp);

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

	char* input= malloc(1000);
	char* token;

	//keep looping until input is 'q'

	while(fgets(input, 1000, stdin)){

		//put terminating bit at end of word, so we can quit with just 'q'
		input[strlen(input) -1] = '\0';
		
		if (strcmp(input, "q") == 0){
			struct fileNode* target;
			target=allfilehead;
			while(target){
				allfilehead=allfilehead->child;
				free(target->path);
				free(target);
				target=allfilehead;
			
			}
			free(input);
			destroyTree(tree);
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
		}else if(strcmp(token,"sna")==0){
			flag = 4;
		
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
		


		//switch cased used to call the correct function based on user input.
		switch(flag){
		case 0: //SO
			result = so(head, tree);
			printResult(result, 0, 0);
			destroyResults(result);
			destroyQ(ls2);
			break;

		case 1: //SA
			count = countNodes(ls2);
			result = sa(head, tree);
			printResult(result, 1, count);
			destroyResults(result);
			destroyQ(ls2);
			break;
		case 2: //SXOR
			result = sa(head, tree);
			printResult(result, 1, 1);
			destroyResults(result);
			destroyQ(ls2);
			break;
		case 3: //SNO
			result = sno(head, tree, allfilehead);
			destroyResults(result);
			destroyQ(ls2);
			break;
		case 4://SNA
			result = sna(head, tree, allfilehead);
			destroyResults(result);
			destroyQ(ls2);
			break;
			
		}
		

	}

	printf("Session ended.\n");

	return 0;
}
