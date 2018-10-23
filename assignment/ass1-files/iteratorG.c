/* iteratorG.c
   Generic Iterator implementation, using doubly linked list

   Written by: Haoran Wang
   Date: 4.16

    You need to submit ONLY this file.... 

*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "iteratorG.h"

typedef struct Node {
  	void *value;
  	struct Node *prev;
  	struct Node *next; 

} Node;

typedef struct cursor {
	struct Node *prev;
	struct Node *next;
} Cursor;

typedef struct IteratorGRep {
	 struct Node *head;
	 struct Node *tail;
	 struct cursor *cursor;
	 ElmCompareFp cmpElm;
	 ElmNewFp newElm;
	 ElmFreeFp freeElm;
} IteratorGRep;


/*
  Your  functions below .... 
 */


IteratorG newIterator(ElmCompareFp cmpFp, ElmNewFp newFp, ElmFreeFp freeFp){
	// initialise the iterator
	IteratorG iterator;
	if ((iterator = malloc(sizeof(struct IteratorGRep))) == NULL) {
	  fprintf(stderr, "Error!! Thats wrong\n"); 
	}
 	iterator->cmpElm = cmpFp;
	iterator->newElm = newFp;
	iterator->freeElm = freeFp;
	iterator->head = NULL;
	iterator->tail = NULL;
	//malloc memory for cursor
	iterator->cursor = malloc(sizeof(struct cursor));
	iterator->cursor->prev = iterator->cursor->next = NULL;
	return iterator;
}

int  add(IteratorG it, void *vp){
	// implement function here and change return value 
	assert(it != NULL);
	struct Node *newNode = malloc(sizeof(struct Node));
	assert(newNode != NULL);
	newNode->value = it->newElm(vp);
	newNode->prev = NULL;
	newNode->next = NULL;
	
	if(it->head == NULL){				// if list is empty
		it->head = it->tail = newNode;	
		it->cursor->next = it->head;	
		it->cursor->prev = NULL;
		return 1;
	}else if(it->cursor->prev == NULL){  // add before head
		newNode->next = it->head;
		it->head->prev = newNode;
		it->head = newNode;
		it->cursor->next = it->head;
		it->cursor->prev = NULL;
		return 1;
	}else if(it->cursor->next == NULL){ // cursor after tail
		newNode->prev = it->tail;
		it->tail->next = newNode;
		it->tail = newNode;
		it->cursor->prev = it->tail->prev;
		it->cursor->next = it->tail;	
		return 1;
	}else{								// cursor somewhere in the middle
		it->cursor->prev->next = newNode;
		it->cursor->next->prev = newNode;
		newNode->next = it->cursor->next;
		newNode->prev = it->cursor->prev;
		it->cursor->next = newNode;
		it->cursor->prev = newNode->prev;
		return 1;
	}	
	return 0;
}
int  hasNext(IteratorG it){
	// implement function here and change return value 
	if(it->cursor->next == NULL) return 0;
	return 1;
}
int  hasPrevious(IteratorG it){
	// implement function here and change return value 
	if(it->cursor->prev == NULL) return 0;
	return 1;
}
void *next(IteratorG it){
	// return the memeory address of next value if having next, 
	// otherwise, return NULL 
	assert(it != NULL);
	if(it->cursor->next != NULL){
		it->cursor->prev = it->cursor->next;
		it->cursor->next = it->cursor->next->next;
		return it->cursor->prev->value;
	}	
	return NULL;
}
void *previous(IteratorG it){
	// implement function here  
	void *returnValue = NULL;
	if(it->cursor->prev != NULL){
		returnValue = it->cursor->prev->value;
		it->cursor->next = it->cursor->prev;
		it->cursor->prev = it->cursor->prev->prev;
	}	
	return returnValue;
}
int  del(IteratorG it){
	// implement function here and change return value 
	
	struct Node *freenode = NULL;
	//only one node?
	if((it->head == it->tail) && (it->cursor->prev == it->head)){
		freenode = it->tail;
		free(freenode);
		it->cursor->prev = it->cursor->next = it->head = it->tail = NULL;
	}//cursor at the end of list
	else if(it->cursor->next == NULL){
		freenode = it->tail;
		it->tail = it->tail->prev;
		it->cursor->prev = it->tail;
		free(freenode);
		it->tail->next = NULL;		
	}	//cursor at the beginning of list
	else if(it->cursor->prev == NULL){		
		return 0;
	}	//cursor between the first element and second element
	else if(it->cursor->prev == it->head && it->cursor->next == it->head->next){	
		freenode = it->head;
		it->head = it->head->next;
		it->cursor->prev = NULL;
		free(freenode);
		it->head->prev = NULL;	
	}//cursor at the somewhere middle of list 
	else {							
		freenode = it->cursor->prev;
		it->cursor->prev = it->cursor->prev->prev;
		it->cursor->prev->next = it->cursor->next;
		it->cursor->next->prev = it->cursor->prev;
		free(freenode);
	}
	return 1;

}
int  set(IteratorG it, void *vp){
	// implement function here and change return value 	
	//cursor at the beginning of list
	if(it->cursor->prev == NULL){
		return 0;
	}else{
		it->cursor->prev->value = it->newElm(vp);
		return 1;
	}
}
IteratorG advance(IteratorG it, int n){
	// implement function here and change return value 
	IteratorG newIt = newIterator(it->cmpElm, it->newElm, it->freeElm);
	int distancetoend = distanceToEnd(it);
	int distancefromstart = distanceFromStart(it);
	//add elements in forward direction first, then reverse;
	if(n > 0 && n <= distancetoend){
		for(int i = 0; i < n ;i ++)
			add(newIt, next(it));					
			reverse(newIt);
			reset(newIt);
		return newIt;
	}else if(n < 0 && n >= (distancefromstart * (-1))){
		for(int i = 0; i < (n*(-1)); i ++)
			add(newIt, previous(it));
			reverse(newIt);
			reset(newIt);
		return newIt;
	}else{
		
		return NULL;
	}
}
void reverse(IteratorG it){
	// implement function here  
	assert(it != NULL);
	int distancetoend = distanceToEnd(it);
	if(it->head == NULL) return;  //empty list does nothing
	if(it->head == it->tail){	  //only one node? change the position of iterator
		if(it->cursor->prev == it->head)
			reset(it);
		else 
			it->cursor->next = NULL;
			it->cursor->prev = it->head;	
	}
	// 1. reverse the whole list first by keeping moving 
	// the next node to the first 
	// 2. move the cursor to corresponding position
	struct Node *curr = it->head;
	struct Node *currnext = NULL;
	while(curr->next != NULL){
		//consider the last node here
		if(curr->next->next == NULL){
			currnext = curr->next;
			curr->next = currnext->next;	
			currnext->next = it->head;
			currnext->prev = NULL;
			it->head->prev = currnext;
			it->head = currnext;
		}// normal case
		else {
			currnext = curr->next;
			curr->next = currnext->next;
			curr->next->prev = curr;	
			currnext->next = it->head;  
			currnext->prev = NULL;
			it->head->prev = currnext;
			it->head = currnext;
		}
	}
	it->tail = curr;
	reset(it);
	//set the cursor to correct position
	for(int i = 0; i < distancetoend; i ++){
		it->cursor->next = it->cursor->next->next;
	}
	if(it->cursor->next == NULL){
		it->cursor->prev = it->tail;
	}else{
		it->cursor->prev = it->cursor->next->prev;
	}
	return;
}
IteratorG find(IteratorG it, int (*fp) (void *vp) ){
	// find the nodes that satisfies given condition
	assert(it != NULL);
	struct Node *curr1 = it->cursor->prev;
	struct Node *curr2 = NULL;
	IteratorG newIt = newIterator(it->cmpElm, it->newElm, it->freeElm);
	for(curr2 = it->tail; curr2 != curr1; curr2 = curr2->prev){
		if(fp(curr2->value)) add(newIt, curr2->value);
	}
	return newIt;
}
int distanceFromStart(IteratorG it){
	//return #nodes from start to cursor
	assert(it != NULL);
	int distance = 0;
	struct Node *curr = NULL;
	for(curr = it->cursor->prev;curr != NULL;curr = curr->prev)
		distance++;
	return distance;
}
int distanceToEnd(IteratorG it){
	//return #nodes from cursor to the end
	assert(it != NULL);
	int distance = 0;
	struct Node *curr = NULL;
	for(curr = it->cursor->next;curr != NULL;curr = curr->next)
		distance ++;
	return distance;;
}
void reset(IteratorG it){
	// implement function here 
	assert(it != NULL);
	it->cursor->next = it->head;
	it->cursor->prev = NULL; 
	return;
}
void freeIt(IteratorG it){
	// free the value, then free list 
	struct Node *curr = it->head; 
	while(curr != NULL){
		struct Node *freenode = curr;
		free(freenode->value);
		free(freenode);
		curr = curr->next;
	}
	free(it);
	return;
}

// --------------------------------------





