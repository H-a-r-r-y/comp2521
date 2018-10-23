
/* hasPath.c 
   Written by Ashesh Mahidadia, October 2017
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Graph.h"



/* 
    You will submit only this one file.

    Implement the function "hasPath" below. Read the exam paper for 
    detailed specification and description of your task.  

    - You can add helper functions in this file, if required.  

    - DO NOT modify code in the file BSTree.h . 
    - DO NOT add "main" function in this file. 
*/


int dfsFindPath(Graph g, Vertex src, Vertex dest);

int *visited;  // array of visit

int hasPath(Graph g, Vertex src, Vertex dest)
{	
	visited = malloc(g->nV*4);
	int i;
	for( i=0; i<g->nV;i++){
		visited[i] = -1;
	}
	visited[src] = 1;
   return dfsFindPath(g, src, dest);
}

int dfsFindPath(Graph g, Vertex src, Vertex dest){
	int i;
	for( i = 0; i<g->nV; i++){
		if(adjacent(g,src,i) && visited[i] == -1){
			visited[i] = 1;
			if(i == dest) return 1;
			else if (dfsFindPath(g, i, dest)){
				return 1;
			}
		}
	}
	return 0;
}


int order = 0;
void getOrder(Graph g, Vertex src, int visited[]){	
	visited[src] = order++;
	for(int i=0;i<g->nV;i++){
		if(adjcent && visied[i] ==-1){
			getorder(g,i,v);
		}
	}

}

int order = 0;
void getOrder(Graph g, Vertex src, int visited[]){	
	visited[src] = order++;
	for(int i=0;i->nV;i++){
		if(adjcent(g,src,i) && visited[i] == -1){
			visited[i] = order++;
			getOrder(g, i, visited);
		}
	}
}

int count(t){
	if(t == NULL){
		return 0;
	}
	int counter;
	if(t->left != NULL && t->right != NULL){
		counter = 0;
	}else if(t->left == NULL && t->right == NULL){
		counter = 0;
	}else{
		counter = 1;
	}
	return counter + right + left;

}
int count(){
	if(t == NULL)return 0;
	int counter;
	if(right ! NULL && left != null){
		counter =1;
	}
	else ocunter = 0;
	return counter + right 



}
//count the node with only one child
int count(Tree t){
	if(t == NULL){
		return 0;
	}else if(right(t) == NULL && left(t) != NULL){
		return 1 + count(left(t));
	}else if(t->left == NULL && t->right != NULL){
		return 1 + count(t->right);
	}else if(t->left == NULL && t->right == NULL){
		return 0;
	}
	return count(t->right) + count(t->left);
}

int TwoChild(tree t){
	if(t =NULL) return 0;
	if(right(t) != NULL && left(t) != NULL){
		return 1 + TwoChild(left) + TwoChild(right);
	}else if(right(t) == NULL && left(t) == NULL){
		return 0;
	}else if(right(t) == NULL){
		return TwoChild(left);
	}else{
		return TwoChild(right);
	}

}
int numReachable(Graph g, Vertex src){
	int count = 0;
	for(int i=0; i<g->nV; i++){
		if(ajdcent(g, src, i) && i notvisied){
			i = visited;
			count = count + 1 + numReachable(g, src);
		}
	}
	return count;
}

int order = 0;
void getOrder(Graph g, Vertex src){
	visited[src] = order++;
	for(int i=0;i<g->nV;i++){
		if(adjcent(g,src,i) && visited[i] == -1){
			visited[i] = order++;
			getOder(g,i);
		}
	}
}
