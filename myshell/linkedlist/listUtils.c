#include "listUtils.h"
#include "requiredIncludes.h"

Node * buildNode(FILE * fin, void *(*buildData)(FILE * in) ){
  Node * nn = (Node *) calloc(1, sizeof(Node));
  nn->data = buildData(fin);
  nn->next = NULL;
  nn->prev = NULL;
  return nn;
}

Node * buildNodeString(char * str, void *(*buildData)(char * s) ){
  Node * nn = (Node *) calloc(1, sizeof(Node));
  nn->data = buildData(str);
  nn->next = NULL;
  nn->prev = NULL;
  return nn;
}

Node * buildNode_Type(void * passedIn){
  Node * nn = (Node *)calloc(1, sizeof(Node));
  nn->data = passedIn;
  nn->next = NULL;
  nn->prev = NULL;
  return nn;
}
void sort(LinkedList * theList, int (*compare)(const void *, const void *)){
  
  if(theList == NULL){
    printf("Null ptr in sort\n");
    exit(-99);
  }

  if(theList->size == 0 || theList->size == 1)
    return;
  Node * search;
  Node * min;
  Node * cur = theList->head->next;
  Node * curNext, * curPrev;
  while(cur != NULL){
    search = cur->next;
    min = cur;
    while(search != NULL){
      if(compare(search->data, min->data) < 0){
	min = search;
      }
search = search->next;
    }
if(cur->next != min)
    curNext = cur->next;
else
    curNext = cur;
    curPrev = cur->prev;
    cur->next = min->next;
if(min->prev != cur)
    cur->prev = min->prev;
else
    cur->prev = min;
if(cur->next != NULL)
       cur->next->prev = cur;
    cur->prev->next = cur;
    min->next = curNext;
    min->prev = curPrev;
    if(min->next != NULL)
       min->next->prev = min;

    min->prev->next = min;
   
    cur = min->next;
    
  }
  
}
void buildListTotal(LinkedList * myList, int total, FILE * fin, void * (*buildData)(FILE * in)){
  if(myList == NULL || total <= 0 || fin ==NULL){
    printf("null ptr or total == 0 in buildListTotal");
    exit(-99);
  }
  int x;
  for(x = 0; x < total; x++){
    addLast(myList, buildNode(fin, buildData));
  }
}
