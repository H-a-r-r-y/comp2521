/*
 * Question 2
 * ===============================================
 * Write a function that takes in a list and builds
 * a new list of only the even nodes, then returns
 * that list. The new list should take the nodes
 * out of the original list, not copy them.
 *
 * [1]->[2]->[3]->[4]->NULL
 * becomes
 * [1]->[3]->NULL and the function returns
 * [2]->[4]->NULL
 *
 * You do not need to make new nodes but you will
 * need to make a new list struct to return
 * ================================================
 * > input list can be empty
 */

#include <stdlib.h>
#include <stdio.h>

// Node
typedef struct _node {
  int value;
  struct _node *next;
} node;
typedef node *Node;

// List
typedef struct _list {
  Node head;
  Node tail;
} list;
typedef list *List;

// prototypes
List newList();
void freeNode(Node n);
Node makeNode(int num);
void addNode(List L, Node n);
void showList(List L);
List getEven(List L);

// main function
int main(int argc, char* argv[]) {
  int num;
  int readIn;
  List L = newList();
  readIn = scanf("%d",&num);
  while(readIn > 0) {
    addNode(L,makeNode(num));
    readIn = scanf("%d",&num);
  }
  List eL = getEven(L);
  showList(L);printf(" || ");showList(eL);

  // i'm a good boy and free my memory
  Node curr = L->head;
  while(curr != NULL){
    Node next = curr->next;
    freeNode(curr);
    curr = next;
  }
  free(L);
  return EXIT_SUCCESS;
}

void freeNode(Node n) {
  free(n);
}

List newList(){
  List L = malloc(sizeof(list));
  L->head = NULL;
  L->tail = NULL;
  return L;
}

Node makeNode(int num){
  Node new = malloc(sizeof(node));
  new->value = num;
  new->next = NULL;
  return new;
}

void addNode(List L, Node n){
  if (L->head == NULL) {
    L->head = n;
    L->tail = n;
  }else{
    L->tail->next = n;
    L->tail = n;
  }
}

void showList(List L){
  Node curr = L->head;
  if (L->head != NULL)
    printf("(H:%d|T:%d) ",L->head->value,L->tail->value);
  else
    printf("(H:NULL|T:NULL) ");

  while(curr != NULL){
    printf("[%d]->",curr->value);
    curr = curr->next;
  }
  printf("NULL");
}

// =============================
// TODO: Complete this function
// =============================
List getEven(List L) {
	if(L->head == NULL || L->head->next = NULL) return L;
	
	Node freenode = L->head;
	L->head = L->head->next;
	free(freenode);
	Node curr = L->head;
	Node prev = NULL;
	int i = 1;
	while(curr != NULL){
		if((curr->next == NULL) && ((i % 2) == 0)){
			L->tail = prev;
			Node freenode = curr;
			free(freenode);
		}
		if((i % 2) == 0){
			Node freenode = curr;
			prev->next = curr->next;
			free(freenode);
				
		}
		i ++;
		prev = curr;
		curr = curr->next;
	}
	
  return L;
}
