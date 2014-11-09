#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

struct bstNode* LLtoBST(struct List* ls){
	int count;
	count = countNodes(ls);

//	printBST(BSTbuild(&(ls->head), count));

	return BSTbuild(&(ls->head),count);
}

int countNodes(struct List* ls){

	int count=0;
	struct tokenNode *tn;
	tn= ls->head;

	while(tn){

		count++;
		tn=tn->sibling;

	}
	return count;

}

struct bstNode* BSTbuild(struct tokenNode** head, int nodeCount){

	if (nodeCount<=0){
		return NULL;
	}
	struct bstNode *left = BSTbuild(head, nodeCount/2);


	struct bstNode *root = (struct bstNode*) malloc(sizeof(struct bstNode));
	root->token=(*head)->token;


	root->child=(*head)->child;
	root->left=NULL;
	root->right=NULL;
	root->left=left;

	*head=(*head)->sibling;

	root->right=BSTbuild(head, nodeCount-(nodeCount/2)-1);

	return root;

	 

}


void printBST(struct bstNode* root){

	if (root==NULL){
		return;

	}
	printBST(root->left);
	printf("root is %s\n",root->token);
	printBST(root->right);
}
