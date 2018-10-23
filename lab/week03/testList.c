// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"

int main(int argc, char *argv[])
{
	DLList newList = newDLList();
	assert(DLListIsEmpty(newList) == 1);
	
	char node[] = "0";

	DLListBefore(newList, node);   assert(validDLList(newList));  printf("111\n");
	/*
	//------test for insert before
	printf("some test for insert before\n");
	// creating a new empty list
	DLList newList = newDLList();
	assert(validDLList(newList));
	assert(DLListIsEmpty(newList) == 1);
	// 1. inserting items into the empty list
	char item[] = "insert before into a empty list";
	DLListBefore(newList, item);
	assert(validDLList(newList));
	printf("now the list has only one node\n");
	
	//2. insert item before curr before first node(only one node)
	char item2[] = "insert before the first node";
	DLListBefore(newList, item2);
	assert(validDLList(newList));
	printf("now the list has 2 nodes\n");
	
	//3. normal case
	char item3[] = "normal case";
	DLListBefore(newList, item3);
	assert(validDLList(newList));
	
	
	printf("pased all the insert before test\n");
	
	
	
	//------test for insert after
	printf("some test for insert after\n");
	// creating a new empty list
	DLList newList10 = newDLList();
	assert(validDLList(newList10));
	assert(DLListIsEmpty(newList10) == 1);
	// 1. inserting items into the empty list
	char item10[] = "insert after into a empty list";
	DLListAfter(newList10, item10);
	assert(validDLList(newList));
	printf("now the list has only one node\n");
	
	//2. insert item before curr before first node(only one node)
	char item20[] = "insert after the first node";
	DLListAfter(newList10, item20);
	assert(validDLList(newList10));
	printf("now the list has 2 nodes\n");
	
	//3. normal case
	char item30[] = "normal case";
	DLListAfter(newList10, item30);
	assert(validDLList(newList10));
	
	
	//-----------------test for insert after
	//-------------------------------
	DLList newList5 = newDLList();
	assert(DLListIsEmpty(newList5) == 1);
	assert(validDLList(newList5));
	printf("some test for insert after\n");
	// 1. inserting items into the empty list
	char item4[] = "insert after a empty list";

	DLListAfter(newList5, item4);
	assert(DLListLength(newList5) == 1);	printf("1\n");
	assert(validDLList(newList5));
	printf("1\n");
	
	printf("there is only one node in the list\n");
	//2. insert item after first node(only one node)
	char item5[] = "insert after the first node";
	DLListAfter(newList5, item5);
	assert(validDLList(newList5));
	printf("there is two nodes in the list\n");
	//3. normal case
	char item6[] = "normal case";
	DLListAfter(newList5, item6);
	assert(validDLList(newList5));
	printf("pased all the insert after test\n");
	
	
	
	
	//--------test for delete function
	printf("some test for delete function\n");
	// 1. deleting empty list
	DLList newList2 = newDLList();
	DLListDelete(newList2);
	assert(validDLList(newList2));
	
	//2. for the case where there is only node
	DLList newList3 = newDLList();
	assert(DLListIsEmpty(newList3) == 1);
	char test0[] = "insert one node to empty list";
	DLListBefore(newList3, test0);
	DLListDelete(newList3);printf("1\n");
	assert(DLListIsEmpty(newList3) == 1);
	assert(validDLList(newList2));printf("1\n");
	
	
	
	//3. for the normal case(delete the node in the middle)
	DLList newList4 = newDLList();
	assert(DLListIsEmpty(newList4) == 1);
	
	char node0[] = "node0";
	char node1[] = "node1";
	char node2[] = "node2";
	DLListBefore(newList4, node0); printf("1\n");
	DLListBefore(newList4, node1);  assert(validDLList(newList4));  
	DLListBefore(newList4, node2);	assert(validDLList(newList4));	
	DLListLength(newList4);
	assert(DLListLength(newList4) == 3);
	DLListDelete(newList4);printf("1\n");
	assert(DLListLength(newList4) == 2);
	assert(validDLList(newList4));printf("1\n");
	

	printf("pased all the delete test\n");
	
	
	DLList newList100 = newDLList();
	assert(DLListIsEmpty(newList100) == 1);
	
	char node99[] = "0";
	char node100[] = "1";
	char node101[] = "2";
	DLListBefore(newList100, node99);   assert(validDLList(newList100));  printf("111\n");
	DLListBefore(newList100, node100);  assert(validDLList(newList100));  printf("111\n");
	DLListAfter(newList100, node101);	assert(validDLList(newList100));	printf("1\n");
	DLListLength(newList100);
	assert(DLListLength(newList100) == 3);
	DLListDelete(newList100);printf("1\n");
	assert(DLListLength(newList100) == 2);
	assert(validDLList(newList100));printf("1\n");
	printf("okok\n");
	
	    DLList myList;
    myList = getDLList(stdin);
    putDLList(stdout,myList);
    assert(validDLList(myList));
    // TODO: more tests needed here
    //creating a new list
    printf("creating a new list\n");
    DLList newList = newDLList();
    assert(validDLList(newList));
    putDLList(stdout, newList);
    //deleting an empty list(which will do nothing)
    printf("deleting an empty list(which will do nothing)\n");
    DLListDelete(newList);
    assert(validDLList(newList));
    putDLList(stdout, newList);
    //inserting an item into an empty list (before)
    printf("inserting an item into an empty list (before)\n");
    char a[] = "%";
    DLListBefore(newList,a);
    assert(validDLList(newList));
    putDLList(stdout, newList);
    //deleting an item in a one-item list
    printf("deleting an item in a one-item list\n");
    DLListDelete(newList);
    assert(validDLList(newList));
    putDLList(stdout, newList);
    //inserting an item into an empty list (after)
    printf("inserting an item into an empty list (after)\n");
    DLListAfter(newList,a);
    assert(validDLList(newList));
    putDLList(stdout, newList);
    //inserting an item into the beginning of a one item list
    printf("inserting an item into the beginning of a one item list\n");
    char b[] = "i";
    DLListBefore(newList,b);
    assert(validDLList(newList));
    putDLList(stdout, newList);
    //inserting an item into the end of a one item list
    printf("inserting an item into the end of a list\n");
    char d[] = "a";   
    DLListAfter(newList,d);
    assert(validDLList(newList));
    putDLList(stdout, newList);
    //inserting an item to the end of the list
    printf("inserting an item to the end of the list\n");
    DLListMove(newList, 1);
    DLListAfter(newList,d);
    assert(validDLList(newList));
    putDLList(stdout, newList);
    //insert one more item, change current to the middle item and delete the middle item
    printf("insert one more item, change current to the middle item and delete the middle item\n");
    char c[] = "n";
    DLListAfter(newList,c);
    DLListMove(newList, -2);
    DLListDelete(newList);
    putDLList(stdout, newList);
	*/
	return 0;
}
