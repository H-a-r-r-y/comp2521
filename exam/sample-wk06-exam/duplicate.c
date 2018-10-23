void removeD(DLList L){
	int size = DLListLength(L);

	int array[size] = {0};
	array[0] = L->first->value;
	DLListNodeP curr = L->first->next;
	int i = 0;
	if(L->nitems <= 1) return;
	
	while(curr!=NULL){
		int a = 0;
		while(a <= i)
		int state = 0;
			if(curr->value == array[a]){
				DLListNodeP freenode = curr;
				curr->prev->next = curr->next;
				curr->next->perv = curr->prev;
				free(freenode);
				L->nitems--;
				state = 1;
				}
			a ++;
		}
		if(state = 0){
			array[++i] = curr->value;
			state = 1;
			}
		
		curr = curr->next;
	}
	
	for(int c = 0; c < i+1; c++){
		DLListNodeP ppcurr = L->first;
		ppcurr = ppcurr->next;
		L->last = ppcurr;
		
	}

}



//
if(L->nitems <= 1){
	return;
}
DLListNodeP curr = L->first;
	while(curr->next != NULL){
		Node currnext = curr->next;
			if(currnext->value == curr->value){
				Node freenode = currnext;
				currnext->prev->next = currnext->next;
				curenext->next->prev = currnext->prev;
				free(freenode);
				currnext = curr->next;
				L->nitems--;
			}
		}else{	 
			curr = curr->next;
		}		
	L->last = currnext;
