#include <stdlib.h>
#include <stdio.h>
#include "sorted-list.h"


/*sorted-list.c */
/*

 *  * Iterator type for user to "walk" through the list item by item, from
 *   * beginning to end.  You need to fill in the type as part of your implementation.
 *    */

/*
 *  * When your sorted list is used to store objects of some type, since the
 *   * type is opaque to you, you will need a comparator function to order
 *    * the objects in your sorted list.
 *     *
 *      * You can expect a comparator function to return -1 if the 1st object is
 *       * smaller, 0 if the two objects are equal, and 1 if the 2nd object is
 *        * smaller.
 *         *
 *          * Note that you are not expected to implement any comparator or destruct
 *           * functions.  You will be given a comparator function and a destruct
 *            * function when a new sorted list is created.
 *             */

/*
 *  * SLCreate creates a new, empty sorted list.  The caller must provide
 *   * a comparator function that can be used to order objects that will be
 *    * kept in the list, and a destruct function that gets rid of the objects
 *     * once they are no longer in the list or referred to in an iterator.
 *      * 
 *       * If the function succeeds, it returns a (non-NULL) SortedListT object,
 *        * otherwise, it returns NULL.
 *         *
 *          * You need to fill in this function as part of your implementation.
 *           */

SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df){
	
	
	SortedListPtr sortedList = NULL;
	sortedList= (struct SortedList*) malloc(sizeof(struct SortedList));
	sortedList->compareF = cf;
	sortedList->destroyF = df;

	if(cf != NULL && df != NULL){
		return sortedList;
	}else{
		return NULL;
	}

}

/*
 *  * SLDestroy destroys a list, freeing all dynamically allocated memory.
 *   *
 *    * You need to fill in this function as part of your implementation.
 *     */
void SLDestroy(SortedListPtr list){

	SLNodePtr target, temp;
	list->destroyF = NULL;
	
	if(list->head==NULL){
		free(list);
		return;
	}

	target=list->head;
	temp=NULL;

	while(target!=NULL){
		temp=target->next;
		free(temp);
		target=temp;

	}
	
	free(list);
	list=NULL;
	return;


}


/*
 *  * SLInsert inserts a given object into a sorted list, maintaining sorted
 *   * order of all objects in the list.  If the new object is equal to a subset
 *    * of existing objects in the list, then the subset can be kept in any
 *     * order.
 *      *
 *       * If the function succeeds, it returns 1, othrewise it returns 0.
 *        *
 *         * You need to fill in this function as part of your implementation.
 *          */

int SLInsert(SortedListPtr list, void *newObj){

	int cmp;

	SLNodePtr newNode = NULL;
	newNode= (struct SLNode*) malloc(sizeof(struct SLNode));
	newNode->refCount = 0;
	newNode->next = NULL;
	newNode->data = newObj; 

	SLNodePtr temp = list->head;
	SLNodePtr tempPrev = NULL;

	while(temp->next != NULL){

		cmp = list->compareF(newNode->data, temp->data);

		if(cmp > 0){ //must insert newNode now
			
			if(tempPrev == NULL){ //newNode must become head node
				list->head = newNode;
				newNode->next = temp;
				return 1;

			}else{ //newNode is not head node

				newNode->next = temp;
				tempPrev->next = newNode;	
				newNode->refCount++;
				return 1;
			}
	
		}else if(cmp == 0){ //same object, insert in front
		
			fprintf(stderr, "Dublicate item, cannot insert new item into list\n");
	
			return 0;

		}
		
		tempPrev = temp;
		temp = temp->next;

	}

	return 0; //unreachable code
}


/*
 *  * SLRemove removes a given object from a sorted list.  Sorted ordering
 *   * should be maintained.  SLRemove may not change the object whose
 *    * pointer is passed as the second argument.  This allows you to pass
 *     * a pointer to a temp object equal to the object in the sorted list you
 *      * want to remove.
 *       *
 *        * If the function succeeds, it returns 1, otherwise it returns 0.
 *         *
 *          * You need to fill in this function as part of your implementation.
 *           */

int SLRemove(SortedListPtr list, void *newObj){
	
	if(list->head==NULL){
		return 0;
	}

	SLNodePtr temp=list->head;
	SLNodePtr prev;
	int cmp;

	while(temp!=NULL){
	cmp=list->compareF(temp->data,newObj);

		if(cmp<0){
			return 0;	//object is not in list
		}else if(cmp==0){
			if (temp==list->head){	//removing first element
				list->head=list->head->next;
				temp->refCount--;
				list->head->refCount++;
				return 1;
			}else {
				prev->next=temp->next;
				temp->refCount--;
				temp->next->refCount++;
				return 1;
				
			}
			

		}else{
			prev=temp;
			temp=temp->next;
		
		}
	
	
	}	

	

	return 0;

}

/*
 *  * SLCreateIterator creates an iterator object that will allow the caller
 *   * to "walk" through the list from beginning to the end using SLNextItem.
 *    *
 *     * If the function succeeds, it returns a non-NULL pointer to a
 *      * SortedListIterT object, otherwise it returns NULL.  The SortedListT
 *       * object should point to the first item in the sorted list, if the sorted
 *        * list is not empty.  If the sorted list object is empty, then the iterator
 *         * should have a null pointer.
 *          *
 *           * You need to fill in this function as part of your implementation.
 *            */

SortedListIteratorPtr SLCreateIterator(SortedListPtr list){

	SortedListIteratorPtr iPtr=NULL;
	iPtr = (struct SortedListIterator*) malloc(sizeof(struct SortedListIterator));
	iPtr->ptr=list->head;
	
	if (list->head!=NULL){
		list->head->refCount++;
	}

	if(iPtr->ptr==NULL){
		return NULL;
	}
	return iPtr; 




}


/*
 *  * SLDestroyIterator destroys an iterator object that was created using
 *   * SLCreateIterator().  Note that this function should destroy the
 *    * iterator but should NOT affect the original list used to create
 *     * the iterator in any way.
 *      *
 *       * You need to fill in this function as part of your implementation.
 *        */

void SLDestroyIterator(SortedListIteratorPtr iter){
	if (iter->ptr!=NULL){
		iter->ptr->refCount--;
	}
	iter->ptr=NULL;
	free(iter);
	iter=NULL;
	
	return;

}


/*
 *  * SLGetItem returns the pointer to the data associated with the
 *   * SortedListIteratorPtr.  It should return 0 if the iterator
 *    * advances past the end of the sorted list.
 *     * 
 *      * You need to fill in this function as part of your implementation.
 *      */

void * SLGetItem( SortedListIteratorPtr iter ){

	if((iter==NULL)||(iter->ptr==NULL)){
		return 0;
	}

	return iter->ptr->data;

}

/*
 *  * SLNextItem returns the next object in the list encapsulated by the
 *   * given iterator.  It should return a NULL when the end of the list
 *    * has been reached.
 *     *
 *      * One complication you MUST consider/address is what happens if a
 *       * sorted list encapsulated within an iterator is modified while that
 *        * iterator is active.  For example, what if an iterator is "pointing"
 *         * to some object in the list as the next one to be returned but that
 *          * object is removed from the list using SLRemove() before SLNextItem()
 *           * is called.
 *            *
 *             * You need to fill in this function as part of your implementation.
 *              */

void * SLNextItem(SortedListIteratorPtr iter){

	iter->ptr=iter->ptr->next;
	if(iter->ptr==NULL){
		return NULL;
	}
	
	return iter->ptr->data;
			
}
