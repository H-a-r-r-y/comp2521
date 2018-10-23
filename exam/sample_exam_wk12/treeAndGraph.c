int count(Tree t){
	if(t == NULL){
		return 0;
	}else if(t->right == NULL && t->left != NULL){
		return 1 + count(t->left);
	}else if(t->left == NULL && t->right != NULL){
		return 1 + count(t->right);
	}else if(t->left == NULL && t->right == NULL){
		return 0;
	}
	return count(t->right) + count(t->left);


}
