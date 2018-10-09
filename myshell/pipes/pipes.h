#ifndef PIPES_H
#define PIPES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../linkedlist/linkedList.h"
#include "../alias/myAlias.h"

int containsPipe(char *s);
char ** parsePrePipe(char *s, int * preCount, char * delimeter, LinkedList * aliasList);
char ** parsePostPipe(char *s, int * postCount, char * delimeter, LinkedList * aliasList);
char ** parseLastPipe(char *s, int * postCount, LinkedList * aliasList);
void pipeIt(char ** prePipe, char ** postPipe, char ** path);
void pipeItTwo(char ** prePipe, char ** postPipe, char ** lastPipe, char ** path);
void pipeItInputRedirect(char ** postPipe, FILE * fin, char ** path);
void pipeItOutputRedirect(char ** postPipe, FILE * fout, char ** path);
void pipeItInputRedirectLeftFirst(char ** prePipe,char ** postPipe, FILE * fin, char ** path);
void pipeItInputRedirectRightLast(char ** prePipe,char ** postPipe, FILE * fin, char ** path);
void pipeItLeftRight(char ** prePipe,FILE * fin, FILE * fout);


#endif 
