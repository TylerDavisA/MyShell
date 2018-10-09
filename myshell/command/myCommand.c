#include "myCommand.h"
#include "../utils/myUtils.h"

void * buildCommand(FILE * stream){
  char word[100];
  int n;
  char c;

  fgets(word, 100, stream);
  strip(word);
  MyCommand * myCommand = (MyCommand *) calloc(1, sizeof(MyCommand));
  char * temp = (char *)calloc(strlen(word)+1, sizeof(char));
  strcpy(temp ,word);
  *myCommand = (MyCommand){.command = temp};
  //while((c = getchar()) != '\n' && c != EOF){}
  return myCommand;
}
void * buildCommandString(char * s){

  
  MyCommand * myCommand = (MyCommand *) calloc(1, sizeof(MyCommand));
  char * temp = (char *)calloc(strlen(s)+1, sizeof(char));
  strcpy(temp ,s);
  *myCommand = (MyCommand){.command = temp};
  //while((c = getchar()) != '\n' && c != EOF){}
  return myCommand;
}
void printCommand(void * ptr){
  MyCommand mycommand= *(MyCommand*) ptr;
  printf("%s\n", mycommand.command);
}
void printCommandFile(FILE * out, void * ptr){
  MyCommand mycommand= *(MyCommand*) ptr;
  fprintf(out, "%s\n", mycommand.command);
}
void cleanCommand(void * ptr){
  MyCommand mycommand = *(MyCommand*) ptr;
  free((char*)mycommand.command);
  free((MyCommand*)ptr);
  
}
