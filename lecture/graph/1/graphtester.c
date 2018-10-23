// Graph ADT tester ... COMP2521 
#include "Graph.h"
#include <stdio.h>

#define NODES 5

int main(void) {
   Graph g = newGraph(NODES);
   Edge e;

   e.v = 0; e.w = 4;
   insertEdge(g, e);
   e.v = 1; e.w = 3;
   insertEdge(g, e);
   e.v = 3; e.w = 1;
   insertEdge(g, e);
   e.v = 3; e.w = 4;
   insertEdge(g, e);
   showGraph(g);
   printf("%d\n", findNei(g,0));

	
   putchar('\n');

   
   freeGraph(g);

   return 0;
}
