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

struct Tree* LLtoBST(struct List* ls); 
