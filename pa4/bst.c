#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"


//LLtoBST takes in a list ptr to a LL. It calls a recursive function to build a BST from the bottom up.
//LLtoBST returns a bstNode pointer to the root of the newly created BST.
struct bstNode* LLtoBST(struct List* ls){
	int count;
	count = countNodes(ls);

	return BSTbuild(&(ls->head),count);
}

//countNodes takes in a list pointer to a LL. It counts all of the tokenNodes in a Linked List, and returns
//the total count of nodes.
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

//BSTbuild is the recursive algorithm that takes in a tokenNode ptr ptr head, and the total num of nodes.
//It returns a bstNode root of a BST.
struct bstNode* BSTbuild(struct tokenNode** head, int nodeCount){


	//base case
	if (nodeCount<=0){
		return NULL;
	}


	//recursive call on left node
	struct bstNode *left = BSTbuild(head, nodeCount/2);
	
	//create root node and assign values
	struct bstNode *root = (struct bstNode*) malloc(sizeof(struct bstNode));

	root->token=(*head)->token;
	root->child=(*head)->child;
	root->left=NULL;
	root->right=NULL;
	root->left=left;

	*head=(*head)->sibling;

	//recursive call on right node
	root->right=BSTbuild(head, nodeCount-(nodeCount/2)-1);

	return root;

}

//printBST takes in the root of a BST, returns void, and prints out a BST
//printBST uses an inorder traversal of a BST to print the values. Used for testing.
void printBST(struct bstNode* root){

	if (root==NULL){
		return;

	}
	printBST(root->left);
	printf("root is %s\n",root->token);
	printBST(root->right);
}
