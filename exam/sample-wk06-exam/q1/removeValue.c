// removeValue.c 
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"


/*
void removeValue(DLList L, int value){
	if(L->nitems == 0) return;
	
	DLListNodeP curr = L->first;
	while(curr != NULL){
		if(L->nitems == 1){
			if(curr->value == value){	
				DLListNodeP freenode = L->first; 
				free(freenode);
				L->first =L->last = L->curr = NULL;
				L->nitems --;
			}
		}else if((curr == L->first) &&(curr->value == value)){
			DLListNodeP freenode = curr;
			L->first = L->first->next;
			free(freenode);
			L->first->prev = NULL;
			L->nitems --;
		
		}else if((curr == L->last) &&(curr->value == value)){
			DLListNodeP freenode = curr;
			L->last = L->last->prev;
			free(freenode);
			L->last->next = NULL;
			L->nitems--;
		}else{
			if(curr->value == value){
				DLListNodeP freenode = curr;
				curr->prev->next = curr->next;
				curr->next->prev = curr->prev;
				free(freenode);
				L->nitems--;
			}
		}
		curr = curr->next;
	}	
}
*/
void removeValue(DLList L, int value){
	if(L == NULL || L->nitems == 0) return;
	DLListNodeP curr = L->first;
	DLListNodeP temp;
	while(curr != NULL){
		if(L->nitems == 1 && curr->value == value){
			temp = curr;
			free(temp);
			L->last = L->first = L->curr= NULL;
			L->nitems--;
		}else if(curr == L->first && curr->value == value){
			temp = curr;
			curr->next->prev = NULL;
			L->first = curr->next;
			L->nitems--;
			free(temp);
		}else if(curr == L->last && curr->value == value){
			temp = curr;
			curr->prev->next  = curr->next;
			L->last = curr->prev;
			L->nitems--;
			free(curr);
		}else if(curr->value == value){
			temp = curr;
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			free(temp);
			L->nitems--;
		}
		curr = curr->next;
	}
}


/*

void deleteDuplicate(List L){
	DLListNodeP curr = NULL;
	DLListNodeP currnext = NULL;
	
	if(L->first == L->last || L->first == NULL){
		return;
	}
	curr = L->first;
	while(curr->next != NULL){
		currnext = curr->next;
		if(curr->next->next == NULL){
			if(curr->next->value == curr->value){
				curr->next = curr->next->next;
				free(currnext);
				L->last = curr;
			}	
		}else{
			if(curr->next->value == curr->value){
				curr->next->next->prev = curr;
				curr->next = curr->next->next;
				free(currnext);
			}else{
				curr = curr->next;
			}
		}	
	}
}*/
