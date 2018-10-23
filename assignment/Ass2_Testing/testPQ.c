
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

int main(void){


	ItemPQ a = {2, 5};
	ItemPQ b = {4, 6};
	ItemPQ c = {3, 4};
	ItemPQ d = {9, 2};
	ItemPQ e = {10, 10};
	ItemPQ f = {13, 1};
	ItemPQ g = {15, 1};
	PQ q = newPQ();
	addPQ(q, a);
	addPQ(q, b);
	addPQ(q, c);
	addPQ(q, e);
	addPQ(q, f);
	addPQ(q, g);
	//showPQ(q);
	addPQ(q, d);
	showPQ(q);
	ItemPQ i = dequeuePQ(q);
	showPQ(q);
	//showPQ(q);
	//b.value = 1;
	/*addPQ(q, b);
	showPQ(q);
	b.value = 10;
	addPQ(q, b);
	
	//printf("nitems = %d\n", q->nitems);
	showPQ(q);
	ItemPQ i = dequeuePQ(q);
	//printf("nitems = %d\n", q->nitems);
	showPQ(q);
	b.value = 1;
	updatePQ(q, b);
	showPQ(q);*/
	freePQ(q);
  return EXIT_SUCCESS;
}
