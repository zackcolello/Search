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
	
	int n;	
	int i;	

	double DoubleList1[] = 
	{2.58, 4.64, 23.3, 47.3, 1.54, 6.72, 6.24, 16.26, 4.13, 4.0, 16.32, 63.54, 87.3, 93.7, 29.84, 
	99.9, 77.3, 54.2, 52.3, 2.54,
	};	


	for (i = 0; i < listSize; i++){

		if(type == 1){ //fill list with random ints

			n = (rand() % 100); //throwing warning here, needs to be void or something
			i1 =n;
			SLInsert(list, i1);
	
		}else if(type == 2){ //fill list with one double array


			d1 = &(DoubleList1[i]);	
			SLInsert(list, (void*)2.58);			

			
	
		}
	}

}

void printList(SortedListPtr list){


	SLNodePtr ptr = list->head;
	int i=0;
	for(ptr = list->head; ptr != NULL; ptr = ptr->next){
		i++;
		
		if(list->type == 1){
			printf("%d: Data is %d, refCount: %d\n", i, ptr->data, ptr->refCount);
		}else if(list->type == 2){
			printf("%d: Data is %2.3f, refCount: %d\n", i, ptr->data, ptr->refCount);
		}else if(list->type == 3){
			printf("%d: Data is %s, refCount %d\n", i, ptr->data, ptr->refCount);
		}else{
			printf("%d: Data is %p, refCount %d\n", i, ptr->data, ptr->refCount);

		}



	}
}


int main()
{
	SortedListPtr list = (SLCreate(compareInts, destroyBasicTypeNoAlloc));
	
	printf("enter type of data in list: 1) int, 2) double, 3) string, or 4) other\n");

	//scan user input
	scanf("%d", &(list->type));
	

	buildList(list, 20, list->type);
		
	printList(list);


	SortedListIteratorPtr iter = SLCreateIterator(list);
	int iterdata= SLGetItem(iter);

//	printf("iters head is %d\n", iter->ptr->data);	
	
	SLNodePtr temp = malloc(sizeof(struct SLNode));
	temp = iter->ptr;	

	//Testing iterator
/*	while(temp!=NULL){

		iterdata = temp->data;
		temp=(SLNextItem(iter));	
		
		printf("iter points to %d\n",iterdata);
	}
*/

	void* x = malloc(1000);
	x = 13;
//	SLRemove(list, x);
	printList(list);	

	SLDestroy(list);

	return 0;
}

