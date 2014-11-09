#include "sorted-list.h"

struct bstNode{

	char* token;
	struct bstNode* left;
	struct bstNode* right;
	struct fileNode*  child;

};

struct Tree{

	struct bstNode*  root;

};

struct bstNode* LLtoBST(struct List* ls);

struct bstNode* BSTbuild(struct tokenNode** head, int nodeCount);

int countNodes(struct List* ls);

void printBST(struct bstNode* root);
