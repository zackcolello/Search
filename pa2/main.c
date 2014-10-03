/*
 *main.c
 */

#include	<string.h>
#include	"sorted-list.h"
#include	<stdlib.h>
#include	<stdio.h>
#include	<time.h>


int compareInts(void *p1, void *p2)
{

	int i1 = *(int*)p1;
	int i2 = *(int*)p2;

	return i1 - i2;
}

int compareDoubles(void *p1, void *p2)
{
	double d1 = *(double*)p1;
	double d2 = *(double*)p2;

	return (d1 < d2) ? -1 : ((d1 > d2) ? 1 : 0);
}

int compareStrings(void *p1, void *p2)
{
	char *s1 = p1;
	char *s2 = p2;

	return strcmp(s1, s2);
}

//Destructor functions
void destroyBasicTypeAlloc(void *p){
	//For pointers to basic data types (int*,char*,double*,...)
	//Use for allocated memory (malloc,calloc,etc.)
	free(p);
}

void destroyBasicTypeNoAlloc(void *p) {
	//For pointers to basic data types (int*,char*,double*,...)
	//Use for memory that has not been allocated (e.g., "int x = 5;SLInsert(mylist,&x);SLRemove(mylist,&x);")
	return;
}


void buildList(SortedListPtr list, int listSize){

	srand(time(NULL));

	void* i1 =malloc(sizeof(int));
	int i;
	void* n;	
	
	for (i = 0; i < listSize; i++){
		n = (rand() % 50); //throwing warning here, needs to be void or something
		i1 = n;
		
		SLInsert(list, i1);
	}

}

void printList(SortedListPtr list){


	SLNodePtr ptr = list->head;
	int i=0;
	for(ptr = list->head; ptr != NULL; ptr = ptr->next){
		i++;
		printf("%d: %d\n", i, ptr->data) ;
	}
}

int main()
{
	SortedListPtr list = (SLCreate(compareInts, destroyBasicTypeNoAlloc));
	buildList(list, 10);
	printList(list);

	SLDestroy(list);

	return 0;

}
