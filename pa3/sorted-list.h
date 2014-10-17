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

struct List {
	struct tokenNode *head;

};
struct List* SLCreate();
void SLInsert(struct List *list, char* string, const char* path);
void printList(struct tokenNode *head);
