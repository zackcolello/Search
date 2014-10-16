//sorted-list.h//

#include <stdio.h>
#include <stdlib.h>


struct fileNode {
	char* path;
	int count;
	struct fileNode *child; //if node is not head node, will have a child

};


struct tokenNode {
	char* token;
	struct tokenNode *sibling;
	struct fileNode *child;
};

void SLInsert(char* string);
