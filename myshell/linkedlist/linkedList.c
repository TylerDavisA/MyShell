#include "linkedList.h"
#include "requiredIncludes.h"

LinkedList * linkedList(){
  LinkedList * theList = (LinkedList *)calloc(1, sizeof(LinkedList));
  Node * nn = (Node *)calloc(1, sizeof(Node));
  nn->next = NULL;
  nn->prev = NULL;
  theList->head = nn;
  theList->size = 0;
  return theList;
}

void addLast(LinkedList * theList, Node * nn){
  if(theList == NULL || nn == NULL){
    printf("null ptr in addLast");
    exit(-99);
  }
  nn->index = theList->size;
  if(theList->size == 0)
    addFirst(theList, nn);
  else{
    Node * cur = theList->head->next;
    Node * prev = theList->head;
    while(cur != NULL){
      prev = cur;
      cur = cur->next;
      
    }
    nn->prev = prev;
    prev->next = nn;
    theList->size = theList->size + 1;
  }
 
}

void addFirst(LinkedList * theList, Node * nn){
  if(theList == NULL || nn == NULL){
    printf("null ptr in addFirst");
    exit(-99);
  }
  if(theList->size == 0){
    nn->prev = theList->head;
    theList->head->next = nn;
    theList->size = theList->size + 1;
  }
  else{
    
    
    nn->next = theList->head->next;
    nn->prev = theList->head;
    theList->head->next->prev = nn;
    theList->head->next = nn;
    theList->size = theList->size + 1;
  }
}
void removeFirst(LinkedList * theList, void (*removeData)(void *)){
  if(theList == NULL){
    printf("null ptr in removeFirst");
    exit(-99);
  }
  if(theList->size != 0){
    Node * toDelete = theList->head->next;
    theList->head->next = toDelete->next;
    if(toDelete->next != NULL)
      toDelete->next->prev = theList->head;
    removeData(toDelete->data);
    free(toDelete);
    theList->size = theList->size -1;
  }
}
void removeLast(LinkedList * theList, void (*removeData)(void *)){
  if(theList == NULL){
    printf("null ptr in removeLast");
    exit(-99);
  }
  if(theList->size != 0){
    Node * cur = theList->head->next;
    Node * prev = theList->head;
    while(cur != NULL){
      prev = cur;
      cur = cur->next;
    }
    Node * last = prev->prev;
    
    last->next = NULL;
    removeData(prev->data);
    free(prev);
    theList->size = theList->size -1;
  }

    
}
void removeItem(LinkedList * theList, Node * nn, void (*removeData)(void *), int (*compare)(const void *, const void *)){
  if(theList == NULL || nn == NULL){
    printf("null ptr in removeItem");
    exit(-99);
  }
  if(theList->size != 0){
    Node * cur = theList->head->next;
    Node * prev = theList->head;
      while(cur != NULL && compare(cur->data, nn->data) != 0){
        prev = cur;
        cur = cur->next;
      }
    if(cur != NULL){
      Node * toDelete = cur;
      prev->next = cur->next;
      if(cur->next != NULL)
        cur->next->prev = prev;
    
      removeData(toDelete->data);
      free(toDelete);
    removeData(nn->data);
  free(nn);
      theList->size = theList->size -1;
    }
  }
  else
  {
    removeData(nn->data);
    free(nn);
  }
  
}

void clearList(LinkedList * theList, void (*removeData)(void *)){
  if(theList == NULL){
    printf("Null ptr in clearList.\n");
    exit(-99);
  }
  Node * cur = theList->head->next;
  Node * temp = NULL;
  while(cur != NULL){
    temp = cur;
    cur = cur->next;
    removeData(temp->data);
    free(temp);
  }
  free(theList->head);
  theList->head = NULL;
}
void printList(const LinkedList * theList, void (*convertData)(void *)){
  if(theList == NULL){
    printf("Empty List.\n");
  }
  else if(theList->size == 0){
    printf("Empty List.\n");
  }
  else{
    Node * cur = theList->head->next;
    while(cur != NULL){
      convertData(cur->data);
      cur = cur->next;
    }
  }
}
void printListIndexRange(const LinkedList * theList, int startIndex, void (*convertData)(void *)){
  if(theList == NULL){
    printf("Empty List.\n");
  }
  else if(theList->size == 0){
    printf("Empty List.\n");
  }
  else{
    Node * cur = theList->head->next;
    while(cur != NULL){
	if(cur->index > startIndex-1){
		printf("%d: ", cur->index);
      		convertData(cur->data);
	}
      cur = cur->next;
    }
  }
}
void * printListByIndex(const LinkedList * theList, int index, void (*convertData)(void *)){
  if(theList == NULL){
    printf("Empty List.\n");
  }
  else if(theList->size == 0){
    printf("Empty List.\n");
  }
  else{
    Node * cur = theList->head->next;
    while(cur != NULL){
	if(cur->index == index -1){
		//printf("%d: ", cur->index);
      		//convertData(cur->data);
		return cur->data;
	}
      cur = cur->next;
    }
  }
}
void printListToFile(const LinkedList * theList, FILE * out, int total, void (*convertData)(FILE * out, void *)){
	if(theList == NULL){
		printf("Empty List \n");
	}
	else if(theList->size == 0){
		printf("Empty List \n");
	}
	else if(out == NULL)
		printf("file is null");
	else{
		int res = 0;
		/*if(total >= theList->size){
			Node * cur = theList->head->next;
    			while(cur != NULL){
      			convertData(out, cur->data);
      			cur = cur->next;
			}
		}
		else{
			int res = theList->size - total;// base index to start printing
			
		}*/
		if(total < theList->size)
			res = theList->size - total;

		Node * cur = theList->head->next;
    		while(cur != NULL){
			if(cur->index >= res)
	      			convertData(out, cur->data);
	      		cur = cur->next;
		}
	}


}
