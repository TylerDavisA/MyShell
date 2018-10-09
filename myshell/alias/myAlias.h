#ifndef MYALIAS_H
#define MYALIAS_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../linkedlist/linkedList.h"

struct my_alias
{
  char * command;
  char * alias;
};

typedef struct my_alias MyAlias;
void * buildAliasString(char * s);
void * buildAlias(FILE * stream);
void printAlias(void * ptr);
void printAliasFile(FILE * out, void * ptr);
void cleanAlias(void * ptr);
void findAliasMatch(LinkedList *theList, char * str);
int compareAlias(const void * p1, const void * p2);
void * buildUnAliasString(char * word);
int replaceAliasMatch(LinkedList *theList, char * str);

#endif
