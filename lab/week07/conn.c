// Determine if/how two Places are adjacent

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"
#include "Places.h"
#include <assert.h>
void tests(void){
	Map europe = newMap();
    TransportID t[MAX_TRANSPORT];
    // the # of connection between AMTERDAM and COLOGNE is 1
    assert(connections(europe, AMSTERDAM,COLOGNE,t) == 1);
     // the # of connection between AMTERDAM and ROME is 0
      assert(connections(europe, AMSTERDAM,ROME,t) == 0);
     //the connection between MARSEILLES and BARCELONA  is BOAT;
     connections(europe, MARSEILLES,BARCELONA,t);
     assert(t[0] == BOAT);
     //the connection between TYRRHENIAN_SEA  and MEDITERRANEAN_SEA  is BOAT;
      connections(europe, TYRRHENIAN_SEA,MEDITERRANEAN_SEA,t);
     assert(t[0] == BOAT);
     
     printf("if there is not assertion fault, U passed all tests\n");
}
int main(int argc, char **argv)
{
	int id1, id2, errs=0; 

	if (argc < 3) {
		fprintf(stderr, "Usage: %s Place1 Place2\n", argv[0]);
		exit(1);
	}

	// convert args to place IDs
	id1 = (strlen(argv[1]) == 2) ? abbrevToID(argv[1]) : nameToID(argv[1]);
	id2 = (strlen(argv[1]) == 2) ? abbrevToID(argv[2]) : nameToID(argv[2]);

	// check place validity
	if (id1 == NOWHERE) {
		errs++;
		fprintf(stderr, "Invalid place name: %s\n", argv[1]);
	}
	if (id2 == NOWHERE) {
		errs++;
		fprintf(stderr, "Invalid place name: %s\n", argv[2]);
	}
	if (errs > 0) exit(1);

	Map europe;
	europe = newMap();

	// check for direct connection
    TransportID t[MAX_TRANSPORT];  int i, n;

	printf("Between %s and %s ...\n", idToName(id1), idToName(id2));
	n = connections(europe, id1, id2, t);
	if (n == 0)
		printf("No direct connection\n");
	else {
		for (i = 0; i < n; i++) {
			switch (t[i]) {
			case ROAD: printf("Road connection\n"); break;
			case RAIL: printf("Rail connection\n"); break;
			case BOAT: printf("Boat connection\n"); break;
			default:   printf("Weird connection\n"); break;
			}
		}
	}
	
	tests();
	return 0;
}
