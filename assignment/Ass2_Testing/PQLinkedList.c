// PQ ADT interface for Ass2 (COMP2521)
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct node *Node;
typedef struct node{
	ItemPQ element;
	Node next;
}node;

struct PQRep {
	int length;
	Node head;
};

//helper function
Node makeNewNode(ItemPQ element);
Node findFirstNode(Node curr);

PQ newPQ() {
	PQ pq = malloc(sizeof(struct PQRep));
	assert(pq != NULL);
	pq->head = NULL;
	pq->length = 0;
	return pq;
}

int PQEmpty(PQ pq) {
	if(pq->length == 0) return true;
	return false;
}

void addPQ(PQ pq, ItemPQ element) {
	Node curr = NULL;
	int found = false;
	Node new = makeNewNode(element);
	for(curr = pq->head; curr != NULL; curr = curr->next){
		if(curr->element.key == element.key){
			curr->element.value = element.value;
			found = true;
			break;
		}
	}
	if(found == false){
		pq->head = new;
		pq->length ++;
	}
}

ItemPQ dequeuePQ(PQ pq) {
	ItemPQ throwAway = {0};
	if(PQEmpty(pq)) return throwAway;   
	ItemPQ result;                
	int smallest = pq->head->element.key;
	Node curr = NULL;
	Node prev = NULL;
	Node target = NULL;
	for(curr = pq->head->next; curr != NULL; curr = curr->next){
		if(curr->element.key < smallest){
			smallest = curr->element.key;
		}
	}
	for(curr = pq->head; curr != NULL; curr = curr->next){
		if(curr->element.key == smallest){
			target = findFirstNode(curr);
			result = target->element;
			break;
		}
	}
	for(curr = pq->head; curr != NULL; curr = curr->next){
		if(curr == target){
			
			if(prev == NULL){
				pq->head = curr->next;
				free(curr);
			}else{
				prev->next = curr->next;
				free(curr);
			}
			break;
		}
		prev = curr;
	}
	return result;
}

void updatePQ(PQ pq, ItemPQ element) {
	Node curr;
	for(curr = pq->head; curr != NULL; curr = curr->next){
		if(curr->element.key == element.key){
			curr->element.value = element.value;
			break;
		}
	}
}

void  showPQ(PQ pq) {
	Node curr;
	if(pq->head == NULL){
		printf("this queue is empty\n");
		return;
	}
	printf("this queue looks like: ");
	for(curr = pq->head; curr != NULL; curr = curr->next){
		printf("%d -> ", curr->element.value);
	}
	printf("NULL\n");
}

void  freePQ(PQ pq) {
	Node curr = NULL;
	Node temp = NULL;
	for(curr = pq->head; curr != NULL; curr = curr->next){
		temp = curr;
		free(temp);
	}
}


//make a new node
Node makeNewNode(ItemPQ element){
	Node new = malloc(sizeof(node));
	assert(new != NULL);
	new->element = element;
	new->next = NULL;
	return new;
}

Node findFirstNode(Node curr){
	Node curr2 = NULL;
	Node firstNode = curr;
	for(curr2 = curr->next; curr2 != NULL; curr = curr->next){
		if(curr2->element.key == curr->element.key){
			firstNode = findFirstNode(curr2);
		}
	}
	return 	firstNode;
}
