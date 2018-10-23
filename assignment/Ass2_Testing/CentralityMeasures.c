// Graph ADT interface for Ass2 (COMP2521)
#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

double numReachable(int v, Graph g);
NodeValues outDegreeCentrality(Graph g){
	if (g == NULL){
	    NodeValues throwAway = {0};
	    return throwAway;
	}
	NodeValues result;
	result.noNodes = numVerticies(g);
	result.values = malloc(sizeof(double)*numVerticies(g));
	double num;
	for(int i=0; i<numVerticies(g); i++){
	    num = 0;
	    for(AdjList curr = outIncident(g,i); curr != NULL; curr = curr->next){
	        num++;
	    }
	    result.values[i] = num;
	}	
	return result;
}

NodeValues inDegreeCentrality(Graph g){
    if(g == NULL){
	    NodeValues throwAway = {0};
	    return throwAway;
	}
	NodeValues result;
	result.noNodes = numVerticies(g);
	result.values = malloc(sizeof(double)*numVerticies(g));
	double num;
    for(int i=0; i<numVerticies(g); i++){
        num = 0;
        for(AdjList curr = inIncident(g,i); curr != NULL; curr = curr->next){
            num++;            
        }
        result.values[i] = num;
    }
    return result;
}

NodeValues degreeCentrality(Graph g){
    NodeValues degree;
    degree.noNodes = numVerticies(g);
    degree.values = malloc(sizeof(double)*numVerticies(g));
    if(g == NULL){
	    NodeValues throwAway = {0};
	    return throwAway;
	}
    else{
        for(int i=0;i<numVerticies(g);i++){
            degree.values[i] = outDegreeCentrality(g).values[i]+inDegreeCentrality(g).values[i];
        }
        return degree;
    }
}
NodeValues closenessCentrality(Graph g){	
	NodeValues closeness;
	closeness.noNodes = numVerticies(g);
	closeness.values = malloc(sizeof(double)*numVerticies(g));
	double n ,p;
    if(g == NULL){
	    NodeValues throwAway = {0};
	    return throwAway;
    }
    else{
        for(int i=0; i<numVerticies(g); i++){
        	p = 0;
            n = numReachable(i,g)+1;
            ShortestPaths path = dijkstra(g,i);
            for(int w=0;w<closeness.noNodes;w++){
            	p = p + path.dist[w];
            }
            if(p == 0){
            	closeness.values[i]= 0;
            }else{
            	closeness.values[i]=((n-1)/(numVerticies(g)-1))*((n-1)/p); 
            }        
        }
        return closeness;
    }
}
 
NodeValues betweennessCentrality(Graph g){

    	NodeValues throwAway = {0};
  
	return throwAway;
}

NodeValues betweennessCentralityNormalised(Graph g){
	NodeValues throwAway = {0};
	return throwAway;
}

void showNodeValues(NodeValues values){
    for(int i=0;i<values.noNodes;i++){
        printf("%d: %lf\n", i, values.values[i]);
    }  
}

void freeNodeValues(NodeValues values){
    free(values.values);
}

double numReachable(int v, Graph g){
	ShortestPaths path = dijkstra(g,v);
	double num = 0;
	for(int i = 0;i<path.noNodes;i++){
		if(path.dist[i] != 0){
			num++;
		}
	}
	return num;
}

