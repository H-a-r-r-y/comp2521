// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <limits.h>
#define VISITED 1
#define NOT_VISITED -1



//function signature
void updatePredArray(int prev[], ShortestPaths paths, Vertex src);
PredNode *insertList (PredNode *L, int v);
PredNode *updatePred(PredNode *L, int v);

ShortestPaths dijkstra(Graph g, Vertex v) {
	//create a paths struct, allocate memory for it
	ShortestPaths paths;
	paths.noNodes = numVerticies(g);
	paths.src = v;
	paths.dist = malloc(sizeof(int) * paths.noNodes);
	paths.pred = malloc(sizeof(struct PredNode) * paths.noNodes);
	//check if inputs are valid
	if(g == NULL || v >= numVerticies(g) || v < 0){
		ShortestPaths throwAway = {0};
		return throwAway;
	}
	//initialise pred array of list
	for(int i=0; i<paths.noNodes; i++){
		paths.pred[i] = NULL;
	}
	//creat a PQ
	PQ q = newPQ();
	ItemPQ item = {v, 0};
	addPQ(q, item);
	//initialize dist array to maximun number
	for(int i=0; i<paths.noNodes; i++){
		paths.dist[i] = INT_MAX;
	}
	paths.dist[v] = 0;
	AdjList list = outIncident(g, v);
	for(AdjList curr = list; curr != NULL; curr = curr->next){
		paths.dist[curr->w] = curr->weight;
		//put the neighbours of src into PQ
		ItemPQ item = {curr->w, curr->weight};
		addPQ(q, item);
	}
	//initialise the visited array
	int visited[paths.noNodes];
	for(int i=0;i<paths.noNodes;i++){
		visited[i] = NOT_VISITED;
	}
	visited[v] = VISITED;	

	//main loop to find shortest paths
	int shortestPath;  //current mini weight
	int vertex;	//current vertex	
	for(int i=0; i<paths.noNodes;i++){
		ItemPQ item = dequeuePQ(q);
		shortestPath = item.value;
		vertex = item.key;
		visited[vertex] = VISITED;
		//edges relaxation 
		AdjList currEdges = outIncident(g, vertex); //get a list of nodes outIncident to indexed node
		for(AdjList curr = currEdges; curr != NULL; curr = curr->next){
			if(visited[curr->w] == NOT_VISITED ){
				//update the distance and put the predecessor to pred array
				if((shortestPath + curr->weight) < paths.dist[curr->w]){
					paths.dist[curr->w] = shortestPath + curr->weight;
					ItemPQ AItem = {curr->w, paths.dist[curr->w]};
					addPQ(q, AItem);
					paths.pred[curr->w] = updatePred(paths.pred[curr->w], vertex);				
				}else if((shortestPath + curr->weight) == paths.dist[curr->w]){
					paths.pred[curr->w] = insertList(paths.pred[curr->w], vertex);
				}			
			}
		}		
	}
	//if there is no path, make it 0
	for(int i=0; i<paths.noNodes; i++){
		if(paths.dist[i] == INT_MAX){
			paths.dist[i] = 0;
		}
	}
	return paths;
}
//update the pred linked list
PredNode *updatePred(PredNode *L, int v){
	PredNode *temp, *curr;
	if(L == NULL){
		L = insertList(L, v);
		return L;
	}
	for(curr = L; curr->next != NULL; curr = curr->next){
		temp = curr;
		free(temp);
	}
	curr->v = v;
	return curr;	
}
// insert a node to linked list
PredNode *insertList (PredNode *L, int v){
	//insert at tail
	PredNode *new = malloc(sizeof(struct PredNode));
	assert(new != NULL);	
	new->v = v;
	if(L == NULL){
		new->next = NULL;
		return new;
	}
	PredNode *curr = L;
	while(curr != NULL){
		if(curr->next == NULL){
			new->next = NULL;
			curr->next = new;
			break;
		}
		curr = curr->next;
	}	
	return L;
}
//show the shortest paths
void showShortestPaths(ShortestPaths paths) {
	for(int i=0; i<paths.noNodes; i++){
		PredNode *curr = paths.pred[i];
		if(curr == NULL){
			printf("I am the src\n");
			continue;
		}
		printf("vertex %d has predecessor :", i);
		for(curr = paths.pred[i]; curr != NULL; curr = curr->next){
			printf("%d -> ", curr->v);
		}
		printf("NULL\n");
	}
}
//free the memory
void  freeShortestPaths(ShortestPaths paths) {
	free(paths.dist);
	PredNode *temp, *curr;
	for(int i=0; i<paths.noNodes; i++){
		for(curr = paths.pred[i]; curr != NULL; curr = curr->next){
			temp = curr;
			free(temp);
		}
	}	
}
