// getPeaks.c 
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"


/* 
    You will submit only this one file.

    Implement the function "getPeaks" below. Read the exam paper for 
    detailed specification and description of your task.  

    - DO NOT modify code in the file DLList.h . 
    - You can add helper functions in this file.  
    - DO NOT add "main" function in this file. 
    
*/

DLList getPeaks(DLList L){
	DLList new = newDLList();
	DLListNodeP curr = L->first->next;
	if(L->nitems < 3){
		return new;
	}
	while(curr->next != NULL){
		if(curr->next->value < curr->value && curr->prev->value < curr->value){
			if(new->nitems == 0){
				DLListNodeP new2 = newDLListNode(curr->value);
				new->first = new->last = new->curr = new2;
				new->nitems++;
			}else {
				DLListNodeP new2 = newDLListNode(curr->value);
				new->curr->next = new2;
				new->curr->next->prev = new->curr;
				new->curr = new->curr->next;
				new->nitems++;
			}
		}
		curr = curr->next;
	}
	new->last = new->curr;
	return new;
}







/*





DLList getPeaks(DLList L){
	DLList peaksL = newDLList();

	if(L->nitems < 3) return peaksL;
	
	DLListNodeP curr = L->first->next;
	while(curr->next != NULL){
		if(curr->next->value < curr->value && curr->prev->value < curr->value){
			if(peaksL->nitems == 0){
				DLListNodeP new = newDLListNode(curr->value);
				peaksL->curr = peaksL->last = peaksL->first = new;
				peaksL->nitems++;
			}else {
				DLListNodeP new = newDLListNode(curr->value);
				peaksL->curr->next = new;
				peaksL->last = peaksL->curr;
				peaksL->curr = peaksL->curr->next;
				peaksL->nitems++;
				 
			}
		}
		curr = curr->next;
	}
	return peaksL;
}

*/
