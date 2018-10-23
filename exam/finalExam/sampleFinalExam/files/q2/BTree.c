int isHeap(BTree  t){
	if(t == NULL)
		return 1;
	if(t->left != NULL && t->right != NULL){
		if(t->left->value > t->value || t->right->value > t->value)
			return 0;
		if(!isHeap(t->right))
			return 0;
		if(!isHeap(t->left))
			return 0;
	}else if(t->left != NULL && t->right == NULL){
		if(t->left->value > t->value)
			return 0;
		return isHeap(t->left);
	}else if(t->right != NULL && t->left == NULL){
		if(t->right->value > t->value)
			return 0;
		return isHeap(t->right);
	}
	return 1;

}
