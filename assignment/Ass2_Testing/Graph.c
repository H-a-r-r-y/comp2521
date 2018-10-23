// Graph ADT interface for Ass2 (COMP2521)
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Graph.h"

//graph implemented by array of list 
struct GraphRep{
   AdjList *edges;  // array of lists
   int   nV;     // #vertices
   int   nE;     // #edges
};


//function signature
bool validVertex(Graph g, Vertex v);
AdjList deleteAdjList(AdjList L, Vertex v);
AdjList insertAdjList(AdjList L, Vertex neighbour, int weight);

//create a new graph
Graph newGraph(int noNodes) {
	//allocate memory for graph
	Graph g;
	if((g = malloc(sizeof(struct GraphRep))) == NULL){
		fprintf(stderr, "couldnot allocate memory\n");
		exit(1);
	}
	g->nV = noNodes;
	g->nE = 0;
	//allocate memory for array
	if((g->edges = malloc(sizeof(AdjList)*noNodes)) == NULL){
		fprintf(stderr, "couldnot allocate memory\n");
		exit(1);
	}
	//initialise array
	for(int i=0; i<noNodes; i++){
		g->edges[i] = NULL;
	}
	return g;
}
//return the number of verticies in graph
int numVerticies(Graph g) {
	assert(g != NULL);
	return g->nV;
}

//add a egde to graph
void  insertEdge(Graph g, Vertex src, Vertex dest, int weight) {
	assert(g != NULL && validVertex(g,src) && validVertex(g,dest));
	if(!adjacent(g, src, dest)){
		g->edges[src] = insertAdjList(g->edges[src], dest, weight);
		g->nE++;
	}
}

//remove a edge in graph
void  removeEdge(Graph g, Vertex src, Vertex dest) {
	assert(g != NULL && validVertex(g, src) && validVertex(g, dest));
	if(adjacent(g, src, dest)){
		g->edges[src] = deleteAdjList(g->edges[src], dest);
		g->nE--;
	}
}

//if two inputed verticies are adjcent, return true, otherwise return false 
bool adjacent(Graph g, Vertex src, Vertex dest) {
	assert(g != NULL && validVertex(g, src) && validVertex(g, dest));
	for(AdjList curr = g->edges[src]; curr != NULL; curr = curr->next){
		if(curr->w == dest) return true;
	}
	return false;
}

//Returns a list of adjacent vertices
 //on outgoing edges from a given vertex.
AdjList outIncident(Graph g, Vertex v) {
	assert(g != NULL && validVertex(g, v));
	return g->edges[v];
}

//Returns a list of adjacent vertices
 //on incoming edges from a given vertex.
AdjList inIncident(Graph g, Vertex v) {
	assert(g != NULL && validVertex(g,v));
	AdjList new = NULL;//not sure 
	int weight;
	for(int i=0; i<g->nV; i++){
		if(adjacent(g, i, v)){
			for(AdjList curr = g->edges[i]; curr != NULL; curr = curr->next){
				if(curr->w == v){
					weight = curr->weight;
					break;
				}
			}
			new = insertAdjList(new, i, weight);
		}
	}
	return new;
}

//show the graph
void  showGraph(Graph g) {
	 assert(g != NULL);  
    printf("#Vertices = %d, #edges = %d\n", g->nV, g->nE);
    for (int i = 0; i < g->nV; i++) {
       printf("vertex%d : connected to Vertex-", i);
       for(AdjList curr = g->edges[i]; curr != NULL; curr = curr->next){
       		printf("%d ",curr->w);
       }
       putchar('\n');
    }
}

//release the momory used by graph
void  freeGraph(Graph g) {
	if(g == NULL) return;
	for(int i=0;i<g->nV;i++){
		for(AdjList curr = g->edges[i]; curr != NULL; curr = curr->next){
			AdjList freeNode = curr;
			free(freeNode);
		}
	}
	free(g->edges);
	free(g);
}
//check if a vertex is in the graph
bool validVertex(Graph g, Vertex v) {
   return (g != NULL && v >= 0 && v < g->nV);
}

//insert a node to linked list(insert at head)
AdjList insertAdjList(AdjList L, Vertex neighbour, int weight){
	AdjList new = malloc(sizeof(struct _adjListNode));
	assert(new != NULL);
	new->w = neighbour;
	new->weight = weight;
	new->next = L;
	return new;
}	
//delete a node in linked list
AdjList deleteAdjList(AdjList L, Vertex v){
	if(L == NULL) return L;
	AdjList curr = NULL, prev = NULL;
	for(curr = L; curr != NULL; curr = curr->next){
		if(curr->w == v) break;
		prev = curr;
	}
	if(prev == NULL){
	   return L->next;
	}
	else {
		prev->next = curr->next;
		free(curr);
	}
	return L;
}

