// PQ ADT interface for Ass2 (COMP2521)
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define MAX_SIZE 1024

//implemented by heap
//array representation
typedef struct PQRep {
    ItemPQ *items;//array of items
    int nitems;   //#items currtently
    int nslots;	  //maximum items
}PQRep;	

//function signature
void fixUp(ItemPQ items[], int index);
void swap(ItemPQ items[], int i, int j);
void fixDown(ItemPQ items[], int i, int N);
void balanceHeap(PQ pq, ItemPQ items[], int index);

//create a new priority queue
PQ newPQ() {
    PQ new = malloc(sizeof(PQRep));
    new->items = malloc(sizeof(ItemPQ)*(MAX_SIZE + 1));
    assert(new != NULL && new->items != NULL);
    new->nitems = 0;
    new->nslots = MAX_SIZE;
    return new;
}
//cheak if PQ is empty
int PQEmpty(PQ p){
        return (p->nitems == 0);
}
/* Adds item (ItemPQ) to the priority queue.
   If an item with 'key' exists, it's 'value' is updated.
*/
void addPQ(PQ pq, ItemPQ element) {
    assert(pq != NULL && pq->nitems < pq->nslots);
    for(int i = 1; i <= pq->nitems; i++){
    	if(pq->items[i].key == element.key){
    		pq->items[i].value = element.value;
    		balanceHeap(pq, pq->items, i);
    		return;
    	}
    }
    pq->nitems++;
    pq->items[pq->nitems] = element;//not sure
    fixUp(pq->items, pq->nitems);
}
/* Removes and returns the item (ItemPQ) with smallest 'value'.
   For items with equal 'value', observes FIFO.
*/
ItemPQ dequeuePQ(PQ pq) {
    if (pq == NULL || PQEmpty(pq)){
        ItemPQ throwAway = {0};
        return throwAway;
    }
    ItemPQ top = pq->items[1];
    pq->items[1] = pq->items[pq->nitems];
    pq->nitems--;
    fixDown(pq->items, 1, pq->nitems);
    return top;
}
/* Updates item with a given 'key' value, by updating that item's value to the given 'value'.
   If item with 'key' does not exist in the queue, no action is taken
*/
void updatePQ(PQ pq, ItemPQ element){
    for(int i=1; i<=pq->nitems; i++){
        if(pq->items[i].key == element.key){
            pq->items[i].value = element.value;
            balanceHeap(pq, pq->items, i);
            break;
         }
    }
}
//show the PQ
void  showPQ(PQ pq) {
	printf("last:\n");
	if(pq->nitems == 0){
		printf("Empty Queue\n");
	}
    for(int i=pq->nitems; i>=1; i--){
      printf("index: %d, key: %d, value: %d\n", i, pq->items[i].key, pq->items[i].value);
    }
	printf("first\n");
}
//release the memory used by PQ
void  freePQ(PQ pq) {
	free(pq->items);
    free(pq);
}

//update value at items[i] into correct position
void fixUp(ItemPQ items[], int i){
    while(i > 1 && items[i].value <= items[i/2].value){
        swap(items,i,i/2);
        i = i/2;
    }
}

//update value at items[i] into correct position
void fixDown(ItemPQ items[], int i, int N){
    while(2*i<=N){
        int j = 2*i;
        if(j<N && items[j].value > items[j+1].value)j++; // compare two children, find the smaller one
        if(items[i].value < items[j].value)break;
        swap(items,i,j);
        i=j;
    }
}
//swap two element in heap
void swap(ItemPQ items[], int i, int j){
    ItemPQ tmp = items[i];
    items[i] = items[j];
    items[j] = tmp;
}

//balance heap if some values are changed
void balanceHeap(PQ pq, ItemPQ items[], int index){
	if(index == 1){
		fixDown(items, 1, pq->nitems);
	}else if(items[index].value < items[index/2].value){
		fixUp(items, index);
	}else{
		fixDown(items, index, pq->nitems);	
	}
}
