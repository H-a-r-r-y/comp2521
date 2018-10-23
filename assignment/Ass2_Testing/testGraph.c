#ifndef GRAPH
	#define GRAPH
	#include "Graph.h"
#endif
#include "GraphVis.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	// some very simple code to show you
	// how to use graph vis
Graph g = newGraph(5);
    insertEdge(g,1,2,1);
	insertEdge(g,1,3,5);
    insertEdge(g,2,1,10);
    insertEdge(g,4,2,60);
    insertEdge(g,3,2,6);
	AdjList new = outIncident(g,1);
	while (new != NULL){
		 printf("%d\n", new->w);
		 new=new->next;
	}
    showGraph(g);

	// draws the graph
  graphVis(g, DEFAULT);
	return EXIT_SUCCESS;
}
