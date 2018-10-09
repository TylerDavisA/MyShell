#ifndef MYCOMMAND_H
#define MYCOMMAND_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct my_command
{
  char * command;
};

typedef struct my_command MyCommand;
void * buildCommandString(char * s);
void * buildCommand(FILE * stream);
void printCommand(void * ptr);
void printCommandFile(FILE * out, void * ptr);
void cleanCommand(void * ptr);

#endif
