#include "makeArgs.h"

void clean(int argc, char **argv)
{
  if(argc >0){
    int x = 0;

    for(x = 0; x < argc; x++){
      free(argv[x]);
      argv[x];
    }
    free(argv);
  }
}// end clean

void printargs(int argc, char **argv)
{
	int x;
	for(x = 0; x < argc; x++)
		printf("%s\n", argv[x]);

}// end printargs

int makeargs(char *s, char *** argv)
{
  char copy[MAX];
 
  strcpy(copy, s);
  char * saveptr = NULL;

  char * token = strtok_r(copy, " ", &saveptr);
  int count = 0;
  while(token != NULL){
    count++;
    token = strtok_r(NULL, " ", &saveptr);
    }
  if(count < 1){
    return -1;
  }
  else{
    (*argv) = (char **) calloc(count+1, sizeof(char*));
    int x;
    token = strtok_r(s, " ", &saveptr);
    (*argv)[0] = (char *)calloc(strlen(token) + 1, sizeof(char *));
    strcpy((*argv)[0], token);
    for(x = 1; x < count; x++){
      token = strtok_r(NULL, " ", &saveptr);
      (*argv)[x] = (char *)calloc(strlen(token) + 1, sizeof(char *));
      strcpy((*argv)[x], token);
    }
  }
  return count;

}// end makeArgs
