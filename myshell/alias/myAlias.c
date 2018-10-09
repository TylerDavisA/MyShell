#include "myAlias.h"
#include "../utils/myUtils.h"


void * buildAlias(FILE * stream){//TODO ADD METHOD TO COUNT ALIASES
  char word[100];//READS IN LINES LIKE: alias o = "ls -l"
  int n;
  char c;
  char copy[100];
  char *save = NULL;
  fgets(word, 100, stream);
  MyAlias * myAlias = NULL;
  
  if(word[0] != '\n'){
    char * token;
    myAlias = (MyAlias *) calloc(1, sizeof(MyAlias));
    strcpy(copy, word);
    token = strtok_r(copy, "alias ", &save);
    token = strtok_r(NULL, "=", &save);


    trim(token);
    strip(token);
    char * a = (char *)calloc(strlen(token)+1, sizeof(char));
    strcpy(a ,token);
    myAlias->alias = a;
    strcpy(copy, word);
    token = strtok_r(copy, "\"", &save);
    token = strtok_r(NULL, "\"", &save);
    char * c = (char *) calloc(strlen(token) +1, sizeof(char));
    strcpy(c, token);
    myAlias->command = c;    
  }
  
  

  //while((c = getchar()) != '\n' && c != EOF){}
  return myAlias;
}
int compareAlias(const void * p1, const void * p2){
  MyAlias * temp1 = (MyAlias *) p1;
  MyAlias * temp2 = (MyAlias *) p2;

  return strcmp(temp1->alias, temp2->alias);
}
void * buildAliasString(char * word){
  int n;
  char copy[100];
  char *save = NULL;
  MyAlias * myAlias;
  
  if(strpbrk(word, "\"") != NULL){
    char * token;
    myAlias = (MyAlias *) calloc(1, sizeof(MyAlias));
    strcpy(copy, word);
    token = strtok_r(copy, " ", &save);
    token = strtok_r(NULL, "=", &save);

    trim(token);
    strip(token);
    char * a = (char *)calloc(strlen(token)+1, sizeof(char));
    strcpy(a ,token);
    myAlias->alias = a;
    strcpy(copy, word);
    token = strtok_r(copy, "\"", &save);
    token = strtok_r(NULL, "\"", &save);
    char * c = (char *) calloc(strlen(token) +1, sizeof(char));
    strcpy(c, token);
    myAlias->command = c; 
  }
  else{
    char * token;
    myAlias = (MyAlias *) calloc(1, sizeof(MyAlias));
    strcpy(copy, word);
    token = strtok_r(copy, " ", &save);
    token = strtok_r(NULL, "=", &save);

    trim(token);
    strip(token);
    char * a = (char *)calloc(strlen(token)+1, sizeof(char));
    strcpy(a ,token);
    myAlias->alias = a;
    strcpy(copy, word);
    token = strtok_r(copy, "=", &save);
    token = strtok_r(NULL, "=", &save);
    trimmem(token);
    char * c = (char *) calloc(strlen(token) +1, sizeof(char));
    strcpy(c, token);
    myAlias->command = c; 
  }
//printf("token for command is : %s\n", token);
  
  return myAlias;
}
void * buildUnAliasString(char * word){
  int n;
  char copy[100];
  char *save = NULL;
  
  
    char * token;
    MyAlias * myAlias = (MyAlias *) calloc(1, sizeof(MyAlias));
    strcpy(copy, word);
    token = strtok_r(copy, " ", &save);
    token = strtok_r(NULL, " ", &save);
	

    trim(token);
    strip(token);
    char * a = (char *)calloc(strlen(token)+1, sizeof(char));
    strcpy(a ,token);
    myAlias->alias = a;
    char * c = (char *) calloc(strlen(token) +1, sizeof(char));
    strcpy(c, token);
    myAlias->command = c; 
//printf("token for command is : %s\n", token);
  
  return myAlias;
}
void findAliasMatch(LinkedList *theList, char * str){
if(theList == NULL || str == NULL){
    printf("null ptr in findALias");
    exit(-99);
  }
  if(theList->size == 0){

  }
  else{
    Node * cur = theList->head->next;
    Node * prev = theList->head;
    while(cur != NULL){
	MyAlias *myAlias = (MyAlias*)cur->data;
      if(strcmp(myAlias->alias, str) == 0){
	strcpy(str, myAlias->command);
	}
      prev = cur;
      cur = cur->next;
      
    }
  }
}
int replaceAliasMatch(LinkedList *theList, char * str){
char * token, *save, *token2;
char copy[100];


if(theList == NULL || str == NULL){
    printf("null ptr in findALias");
    exit(-99);
  }
  if(theList->size == 0){

  }
  else{
strcpy(copy, str);
token = strtok_r(copy, " ", &save);
token = strtok_r(NULL, "=", &save);
strip(token);
trim(token);
    Node * cur = theList->head->next;
    Node * prev = theList->head;
    while(cur != NULL){
	MyAlias *myAlias = (MyAlias*)cur->data;
        if(strcmp(myAlias->alias, token) == 0){
		if(strpbrk(str, "\"") != NULL){
		  strcpy(copy, str);
		  token2 = strtok_r(copy, "\"", &save);
		  token2 = strtok_r(NULL, "\"", &save);
		  strip(token2);
		  trimmem(token2);
		}
		else{
			strcpy(copy, str);
    			token2 = strtok_r(copy, "=", &save);
    			token2 = strtok_r(NULL, "=", &save);
			strip(token2);
			trimmem(token2);
		
		}
	token = myAlias->command;
	myAlias->command = (char*)calloc(strlen(token2)+1, sizeof(char));
	  strcpy(myAlias->command,token2);
	free(token);
	  return 1;

	}
      prev = cur;
      cur = cur->next;
      
    }
  }
	return 0;
}
void printAlias(void * ptr){
  MyAlias *myalias = (MyAlias*) ptr;
  printf("alias %s = \"%s\"\n", myalias->alias, myalias->command);
}
void printAliasFile(FILE * out, void * ptr){
  MyAlias *myalias= (MyAlias*) ptr;
  fprintf(out, "alias %s = \"%s\"\n", myalias->alias, myalias->command);
}
void cleanAlias(void * ptr){
  MyAlias * myalias = (MyAlias*) ptr;
  free(myalias->command);
  free(myalias->alias);
  free((MyAlias*)ptr);
  
}
