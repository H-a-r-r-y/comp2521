// crawl.c ... build a graph of part of the web
// Written by John Shepherd, September 2015
// Uses the cURL library and functions by Vincent Sanders <vince@kyllikki.org>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <curl/curl.h>
#include "queue.h"
#include "stack.h"
#include "set.h"
#include "graph.h"
#include "html.h"
#include "url_file.h"

#define BUFSIZE 1024

void setFirstURL(char *, char *);
void normalise(char *, char *, char *, char *, int);

int main(int argc, char **argv)
{
	URL_FILE *handle;
	char buffer[BUFSIZE];
	char baseURL[BUFSIZE];
	char firstURL[BUFSIZE];
	char next[BUFSIZE];
	int  maxURLs;

	if (argc > 2) {
		strcpy(baseURL,argv[1]);
		setFirstURL(baseURL,firstURL);
		maxURLs = atoi(argv[2]);
		if (maxURLs < 40) maxURLs = 40;
	}
	else {
		fprintf(stderr, "Usage: %s BaseURL MaxURLs\n",argv[0]);
		exit(1);
	}

	// You need to modify the code below to implement:
	//
	// add firstURL to the ToDo list
	Stack ToDo = newStack();
	pushOnto(ToDo, firstURL);
	// initialise Graph to hold up to maxURLs
	Graph URL = newGraph(maxURLs);
	// initialise set of Seen URLs
	Set seenURL = newSet();
	// while (ToDo list not empty and Graph not filled) {
	char curr[BUFSIZE];
	while(!emptyStack(ToDo) && nVertices(URL) <= maxURLs){
		memset(curr, 0, BUFSIZE);
		strcpy(curr, popFrom(ToDo));
		printf("%s\n", curr);
		if (!(handle = url_fopen(curr, "r"))) {
			fprintf(stderr, "couldn't open the URL file\n");
			return 1;
		}
		//    grab Next URL from ToDo list
		//    foreach line in the opened URL {
		//    if (not allowed) continue
		//       foreach URL on that line {
		//          if (Graph not filled or both URLs in Graph)
		//             add an edge from Next to this URL
		//          if (this URL not Seen already) {
		//             add it to the Seen set
		//             add it to the ToDo list


		while(!url_feof(handle)){
			url_fgets(buffer, sizeof(buffer), handle);
			int pos = 0;
			while ((pos = GetNextURL(buffer, curr, next, pos)) > 0) {
				if (nVertices(URL) < maxURLs || isConnected(URL, curr, next)) {
					addEdge(URL, curr, next);
				}
				if (!isElem(seenURL, next)) {
					insertInto(seenURL, next);
					pushOnto(ToDo, next);
				}

			}
		}
		url_fclose(handle);
		//sleep(0);
	}
		showGraph(URL, 0);


	return 0;
	}

	// setFirstURL(Base,First)
	// - sets a "normalised" version of Base as First
	// - modifies Base to a "normalised" version of itself
	void setFirstURL(char *base, char *first)
	{
		char *c;
		if ((c = strstr(base, "/index.html")) != NULL) {
			strcpy(first,base);
			*c = '\0';
		}
		else if (base[strlen(base)-1] == '/') {
			strcpy(first,base);
			strcat(first,"index.html");
			base[strlen(base)-1] = '\0';
		}
		else {
			strcpy(first,base);
			strcat(first,"/index.html");
		}
	}
