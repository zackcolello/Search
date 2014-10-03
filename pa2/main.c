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

//buildList creates a list of a given size with random values. It takes in a SortedListPtr, the size of the list to be created,
//and the type of elements to be used. 
//Type 1: Ints
//Type 2: Doubles
//Type 3: Strings
void buildList(SortedListPtr list, int listSize, int type){

	srand(time(NULL));

	void* i1 = malloc(sizeof(int));
	void* d1 = malloc(sizeof(double));
	void* s1 = malloc(100000);
	void* n;	
	int i;	

	double d;

	for (i = 0; i < listSize; i++){

		if(type == 1){ //fill list with ints

			n = (rand() % 50); //throwing warning here, needs to be void or something
			i1 = n;
			SLInsert(list, i1);
	
		}else if(type == 2){ //fill list with doubles
		
			//n = ((rand()/RAND_MAX) * 100);
			//printf("n is now %f\n", n);
			//d1 = 3.4;
			//SLInsert(list, d1);
			//d1 = d1 + 1.1;
		}
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
	buildList(list, 10, 1);
	printList(list);

	SLDestroy(list);

	return 0;

}
