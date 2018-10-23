#include <stdlib.h>
#include <stdio.h>
#include "BSTree.h"


int main(void){
	
	Tree t = newTree();
	int value;
	for(int i=0;i<5;i++){
		scanf("%d", &value);
		t = TreeInsert(t, value);
	}
	
	showTree(t);
	printf("# of one-child node if %d\n", count(t));
	freeTree(t);
	return 0;
}
