/*
  testIteratorG.c 
  Client to test Generic Iterator 
  
  Written by: Ashesh Mahidadia
  Date: April 2018 
*/ 

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "iteratorG.h"
#include "positiveIntType.h"
#include "stringType.h" 

#define MAXARRAY 5

/* Helper Functions Below */

/* Returns 1 if marks >= 50, 0 otherwise  */
int passMarks(void *marks){
  return (*((int *) marks) >= 50); 
  
  /* Easy to understand below .. 
     int *ip = (int *) marks;
     if(*ip >= 50) { return 1; }
     else { return 0; } 
  */
}

/* Returns 1 if str starts with "jo" */
int prefixJo(void *str){
  return (strncmp("jo", (char *) str, 2) == 0) ; 
}

/* A function to print a string from a void pointer */
void prnStr(void *vp){
  assert(vp != NULL);
  printf(" %s", (char *) vp );  	
}

/* A function to print an integer from a void pointer */
void prnInt(void *vp){
  assert(vp != NULL);
  printf(" %d", *((int *) vp) );  	
}

/* Prints previous element using the given function 'fp'
   examples: prnPrev(it1, prnInt); prnPrev(it2, prnStr);
*/
void prnPrev(IteratorG it, void (*fp) (void *p) ){
  void *prevP = previous(it);
  assert(prevP != NULL);
  printf("> Previous value is: "); 
  fp(prevP);
  printf("\n"); 
}

/* Prints next element using the given function 'fp'
   examples:   prnNext(it1, prnInt); prnNext(it2, prnStr);
*/
void prnNext(IteratorG it, void (*fp) (void *p) ){
  void *nextP = next(it);
  assert(nextP != NULL);
  printf("> Next value is: "); 
  fp(nextP);
  printf("\n"); 
}

/* Prints elements of 'it' from current to last position 
   using the given function 'fp'. The current position 
   of 'it' will change to the end of the list.
   examples: prnIt(it1, prnInt); prnIt(it2, prnStr);
*/
void prnIt(IteratorG it, void (*fp) (void *p) ){
  int count = 0;
  while(hasNext(it)){
    void *nextP = next(it);	
    count++;
    if(count > 1) { printf(", "); }
    fp(nextP); 		
  }
  printf("\n"); 
}


/* Few Tests Below  */

void test1(){
  printf("\n--====  Test-01       ====------\n");
 
  IteratorG it1 = newIterator(positiveIntCompare, positiveIntNew, positiveIntFree);

  int a[MAXARRAY] = { 25, 78, 6, 82 , 11};
  for(int i=0; i<MAXARRAY; i++){

    int result = add(it1 , &a[i]);
    printf("> Inserting %d: %s \n", a[i], (result==1 ? "Success" : "Failed") );
  }
   prnNext(it1, prnInt); prnNext(it1, prnInt); prnNext(it1, prnInt); prnNext(it1, prnInt); prnNext(it1, prnInt);
    prnPrev(it1, prnInt); prnPrev(it1, prnInt); prnPrev(it1, prnInt); prnPrev(it1, prnInt); prnPrev(it1, prnInt);
    int c = hasNext(it1);
    int b = hasPrevious(it1);
    printf("%d%d\n", c, b);
  freeIt(it1);
  printf("--====  End of Test-01 ====------\n");
}

void test2(){
  printf("\n--====  Test-02       ====------\n");
  IteratorG it1 = newIterator(positiveIntCompare, positiveIntNew, positiveIntFree);
  int a[MAXARRAY] = { 72, 14, 62, 8, 93};
  for(int i=0; i<MAXARRAY; i++){
    int result = add(it1 , &a[i]); 
    printf("> Inserting %d: %s \n", a[i], (result==1 ? "Success" : "Failed") );
  }

  prnNext(it1, prnInt);
  prnNext(it1, prnInt);
  prnPrev(it1, prnInt);
  
  int newVal1 = 55;
  int result1 = set(it1, &newVal1);
  printf("> Set value: %d ; return val: %d \n", newVal1,  result1 );  
  
  prnPrev(it1, prnInt);

  freeIt(it1);
 
  printf("--====  End of Test-02 ====------\n");
}

void test3(){
  printf("\n--====  Test-03       ====------\n");
  IteratorG it1 = newIterator(positiveIntCompare, positiveIntNew, positiveIntFree);
  int a[MAXARRAY] = { 04, 54, 15, 12, 34};
  for(int i=0; i<MAXARRAY; i++){
    int result = add(it1 , &a[i]); 
    printf("> Inserting %d: %s \n", a[i], (result==1 ? "Success" : "Failed") );
  }

   prnIt(it1, prnInt);
      prnPrev(it1, prnInt);
  	reset(it1);
  	   prnNext(it1, prnInt);
  printf("> it1 (after reset): \n");
  prnIt(it1, prnInt);
	reset(it1);
	
  IteratorG advIt1 = advance(it1, 4);
   prnNext(it1, prnInt);
  printf("> advance(it1, 4) returns: \n");
   prnNext(advIt1, prnInt);
   reset(advIt1);
  prnIt(advIt1, prnInt);
  

  
  IteratorG advIt2 = advance(it1, -3);
  printf("> advance(it1, -3) returns: \n");
  prnNext(advIt2, prnInt);
  reset(advIt2);
  prnIt(advIt2, prnInt);
 // prnNext(advIt2, prnInt);
  
  printf("> In 'it1', ");
  prnPrev(it1, prnInt);
      
  freeIt(it1);
  freeIt(advIt1);
  freeIt(advIt2);

  printf("--====  End of Test-03 ====------\n");
}

void test4(){
  printf("\n--====  Test-04       ====------\n");
  IteratorG it1 = newIterator(positiveIntCompare, positiveIntNew, positiveIntFree);
  int a[MAXARRAY] = { 97, 10, 61, 47, 73};
  for(int i=0; i<MAXARRAY; i++){
    int result = add(it1 , &a[i]); 
    printf("> Inserting %d: %s \n", a[i], (result==1 ? "Success" : "Failed") );
  }

  reset(it1);
  printf("> it1 (after reset): \n");
  prnIt(it1, prnInt);
  reset(it1);
  
  IteratorG findIt1 = find(it1, passMarks);
  printf("> find(it1, passMarks) returns: \n");
  prnNext(findIt1, prnInt);
  reset(findIt1);
  prnIt(findIt1, prnInt);
  
  printf("> In 'it1', \n");
  prnNext(it1, prnInt);
  prnNext(it1, prnInt);
     
  int delResult = del(it1);
  printf("\n> del(it1) results in the following and returns %d: \n", delResult );
   prnNext(it1, prnInt);
  reset(it1);
  printf("> it1 (after reset): \n");
  prnIt(it1, prnInt);

  freeIt(it1);
  freeIt(findIt1);

  printf("--====  End of Test-04 ====------\n");
}


void test5(){
  printf("\n--====  Test-05       ====------\n");
  IteratorG it = newIterator(stringCompare, stringNew, stringFree);
  
  char *strA[MAXARRAY];
  strA[0] = strdup("joe");
  strA[1] = strdup("rita");
  strA[2] = strdup("john");
  strA[3] = strdup("abby"); 
  strA[4] = strdup("peter"); 
  
  int j;
  for(j=0; j<MAXARRAY; j++){
    int result = add(it , strA[j]); 
    printf("> Inserting %s: %s \n", strA[j], (result==1 ? "Success" : "Failed") );
  }

  prnNext(it, prnStr);
  prnNext(it, prnStr);
  prnPrev(it, prnStr);
  
  char *newStr1 = "sydney";
  int result2 = set(it, newStr1);
  printf("> Set value: %s ; return val: %d \n", newStr1,  result2 );  
  
  prnPrev(it, prnStr);

  freeIt(it);
  printf("--====  End of Test-05 ====------\n");
}


void test6(){
  printf("\n--====  Test-06       ====------\n");
  IteratorG it = newIterator(stringCompare, stringNew, stringFree);
  
  char *strA[MAXARRAY];
  strA[0] = strdup("kylie");
  strA[1] = strdup("lian");
  strA[2] = strdup("john");
  strA[3] = strdup("arnav"); 
  strA[4] = strdup("joe"); 
  
  int j;
  for(j=0; j<MAXARRAY; j++){
    int result = add(it , strA[j]); 
    printf("> Inserting %s: %s \n", strA[j], (result==1 ? "Success" : "Failed") );
  }

  reset(it);
  printf("> it (after reset): \n");
  prnIt(it, prnStr);
  reset(it);

  IteratorG advIt3 = advance(it, 3);
  printf("> advance(it, 3) returns: \n");
  prnIt(advIt3, prnStr);
 
  IteratorG advIt4 = advance(it, -2);
  printf("> advance(it, -2) returns: \n");
  prnIt(advIt4, prnStr);

  reset(it);
  printf("> it (after reset): \n");
  prnIt(it, prnStr);
  reset(it);

  IteratorG findit = find(it, prefixJo);
  printf("> find(it, prefixJo) returns: \n");
  prnIt(findit, prnStr);
  printf("\n> In 'it',  \n");
  prnNext(it, prnStr);
  prnNext(it, prnStr);

  freeIt(it);
  freeIt(findit);
  freeIt(advIt3);
  freeIt(advIt4);
  printf("--====  End of Test-06 ====------\n\n");
}

void test7(){
  printf("\n--====  Test-7 for rever       ====------\n");
  IteratorG it1 = newIterator(positiveIntCompare, positiveIntNew, positiveIntFree);
  int a[3] = { 5,56,72};
  for(int i=0; i<3; i++){
    int result = add(it1 , &a[i]); 
    printf("> Inserting %d: %s \n", a[i], (result==1 ? "Success" : "Failed") );
  }
	  prnIt(it1, prnInt);
	  reset(it1);
	  prnNext(it1, prnInt);
	  prnNext(it1, prnInt);
	  prnNext(it1, prnInt);
	  printf("now, cursor is between 5 and null\n");
	  reverse(it1);
	  printf("after reverse\n");
	 prnNext(it1, prnInt);
	 prnNext(it1, prnInt);
	 prnNext(it1, prnInt);
	  reset(it1);
	  prnIt(it1, prnInt);
  freeIt(it1);
 
  printf("--====  End of Test-07 ====------\n");
}
void test9()
{
 printf("\n--====  Test-09       ====------\n");
    IteratorG it1 = newIterator(positiveIntCompare, positiveIntNew, positiveIntFree);
    int a[MAXARRAY] = { 25, 78, 6, 82 , 11};
    for(int i=0; i<MAXARRAY; i++){
      int result = add(it1 , &a[i]); 
      printf("> Inserting %d: %s \n", a[i], (result==1 ? "Success" : "Failed") );
    }
    
     // 11 ^ 82 6 78 25
    assert(*(int *)next(it1) == 11);

    // try to reset the value
    int newVal1 = 44;
    int result1 = set(it1, &newVal1);
    printf("> Set value: %d ; return val: %d \n", newVal1,  result1 );

    // 44 ^ 82 6 78 25
    assert(*(int *)previous(it1) == 44);
    assert(distanceToEnd(it1) == 5);
    // now: ^ 44 82 6 78 25

    // 44 82 ^ 6 78 25
    assert(*(int *)next(it1) == 44);
    assert(*(int *)next(it1) == 82);
    newVal1 = 15;
    result1 = set(it1, &newVal1);
    printf("> Set value: %d ; return val: %d \n", newVal1,  result1 );
    assert(*(int *)previous(it1) == 15);
    assert(*(int *)previous(it1) == 44);

    reset(it1);

    // 44 15 6 78 25
    // this is new link list

    // if the len more than the length of the link list, it should be NULL
    IteratorG it2 = advance(it1, 6);
    assert(it2 == NULL);

    // if the len is 0, so it shoule be NULL
  // it2 = advance(it1, 0);
   // assert(hasNext(it2) == 0);printf("1\n");

    // if the len is shorter than before
    it2 = advance(it1, -1);
    assert(it2 == NULL);

    reset(it1);
    // test some normal number
    it2 = advance(it1, 3);

    // printf("%d\n", *(int *)next(it2));
    // it should be: 44 15 6
    assert(*(int *)next(it2) == 44);
    assert(*(int *)previous(it2) == 44);
    assert(*(int *)next(it2) == 44);
    assert(*(int *)next(it2) == 15);
    assert(*(int *)previous(it2) == 15);

    assert(*(int *)next(it2) == 15);
    assert(*(int *)next(it2) == 6);
    assert(*(int *)previous(it2) == 6);

    // it1: 44 15 6 ^ 78 25
    reset(it1);
    // test if it is -3
    assert(*(int *)next(it1) == 44);
    assert(*(int *)next(it1) == 15);
    assert(*(int *)next(it1) == 6);

    // it3: 6 15 44
    IteratorG it3 = advance(it1, -3);
    assert(*(int *)next(it3) == 6);
    assert(*(int *)next(it3) == 15);
    assert(*(int *)next(it3) == 44);

    reset(it1);
    // ^ 44 15 6 78 25

    // it4: 78
    IteratorG it4 = find(it1, passMarks);
    assert(*(int *)next(it4) == 78);
    assert(hasNext(it4) == 0);
    assert(*(int *)next(it1) == 44);

    // try to use it3: 6 15 44 to test that
    // empty link lisk
    it4 = find(it3, passMarks);
    assert(hasNext(it4) == 0);

    // this is test is test that curror not change
    reset(it1);
    assert(*(int *)next(it1) == 44);
    assert(*(int *)next(it1) == 15);
    assert(*(int *)next(it1) == 6);
    assert(*(int *)next(it1) == 78);

    it4 = find(it1, passMarks);
    assert(hasNext(it4) == 0);
    assert(*(int *)next(it1) == 25);

    // test reverse
    // before: ^ 44 15 6 78 25
    reset(it1);
    reverse(it1);
    // after: 25 78 6 15 44 ^
    assert(*(int *)previous(it1) == 44);
    assert(*(int *)previous(it1) == 15);
    assert(*(int *)previous(it1) == 6);
    assert(*(int *)previous(it1) == 78);
    assert(*(int *)previous(it1) == 25);
     // ^ 25 78 6 15 44
    assert(*(int *)next(it1) == 25);
    assert(*(int *)next(it1) == 78);
    assert(*(int *)next(it1) == 6);
    assert(*(int *)next(it1) == 15);
    assert(*(int *)next(it1) == 44);

    // 25 78 6 15 44 ^
    reverse(it1);

    // // ^ 44 15 6 78 25

    // assert(*(int *)next(it1) == 44);
    // assert(*(int *)next(it1) == 15);
    // assert(*(int *)next(it1) == 6);
    // assert(*(int *)next(it1) == 78);
    // assert(*(int *)next(it1) == 25);

    // ^ 44 15 6 78 25
    reset(it1);

    // 44 ^ 15 6 78 25
    assert(*(int *)next(it1) == 44);

    // 25 78 15 ^ 44
    reverse(it1);
    assert(*(int *)previous(it1) == 15);
    assert(*(int *)next(it1) == 15);
    assert(*(int *)next(it1) == 44);
    assert(hasNext(it1) == 0);


    freeIt(it1);
    freeIt(it2);
    freeIt(it3);
    freeIt(it4);

    printf("--====  End of Test-09 ====------\n");
}
int main(int argc, char *argv[])
{
  /* The code in this file is provided in case you find it difficult 
     to understand how to test your generic iterator. In case you have 
     difficulty understanding a generic ADT, please study SetG example 
     we discussed in the lectures in detail. You may also want to 
     (again) watch the lectures on this topic and/or see a tutor 
     during one of the Help Sessions (see the class web page).

     The code below only tests basic operations, however make sure 
     that you do test all the required functions properly by adding more 
     tests in this or another file. 

     Remove comments below as required. The expected output for each test is in 
     the file 'expected_output.txt'.
  */
  
 //test1();
 //test2();
 // test3();
 // test4();
//  test5();
//  test6();
 // test7();
 // test8();
 test9();

  return EXIT_SUCCESS;
  
}
