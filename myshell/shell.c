#include "./pipes/pipes.h"
#include "./utils/myUtils.h"
#include "./process/process.h"
#include "./tokenize/makeArgs.h"
#include "./linkedlist/linkedList.h"
#include "./linkedlist/listUtils.h"
#include "./utils/fileUtils.h"
#include "./alias/myAlias.h"
#include <string.h>
void readHistValues(int *histcount, int *filecount);
char * getPath(char * s);


//TODO MAKE A MAKEARGS FOR PATH $PATH
// /data/myprogs
// NULL
//AND THEN READ IN PATH AND PRINT IT TO FILE

int main()
{
  int argc, pipeCount;	
  char **argv = NULL, s[300];
  char copy[MAX], *saveptr = NULL, *token;
  int preCount = 0, postCount = 0, lastCount = 0;
  int histCount = 100, histFileCount = 1000;
  char ** prePipe = NULL, ** postPipe = NULL, ** lastPipe = NULL;
  LinkedList *historyList = linkedList();
  LinkedList *aliasList = linkedList();
  char ** path = NULL;
  int goAgain = 0;
  char * oldenv = strdup(getenv("PATH"));
  char * newPath = NULL;
  char pathfromfile[100] = "\\0";


	if( access( ".msshrc", F_OK) != -1){
		//file exists
		readHistValues(&histCount, &histFileCount);
		if(access(".mssh_history", F_OK) != -1){
			int total = 0;
			FILE * fin = NULL;
			fin = fopen(".mssh_history", "r");
			total = countRecords(fin, 1);
			
			if(total > 0){
				buildListTotal(historyList, total, fin, buildCommand);
			}
			fclose(fin);
		}//file exists
		FILE * inrc = fopen(".msshrc", "r");
		fgets(s, 300, inrc);
		fgets(s, 300, inrc);//reads in hist and file count
		fgets(s, 300, inrc);//prime read
		while(!feof(inrc)){
			if(strncmp("alias", s, 5) == 0){
				addLast(aliasList, buildNodeString(s, buildAliasString));
			}
			
			if(strncmp("PATH", s, 4) == 0){
				path = NULL;
				newPath = getPath(s);
				strcpy(pathfromfile, newPath);
				setenv("PATH", newPath, 1);
			}
			fgets(s, 300, inrc);
		}
		//printf("Now printing alias:\n");
		//printList(aliasList, printAlias);
		
		fclose(inrc);
	}
  
  printf("command?: ");
  fgets(s, MAX, stdin);
  strip(s);
  addLast(historyList, buildNodeString(s, buildCommandString));
  findAliasMatch(aliasList, s);
  while(strcmp(s, "exit") != 0)
  {
	pipeCount = containsPipe(s);
	if(strncmp("alias ", s, 6) == 0){
		
			int res = 0;
			res = replaceAliasMatch(aliasList, s);
			if(res != 1)
				addLast(aliasList, buildNodeString(s, buildAliasString));		
	}
	else if(strncmp("alias", s, 5) == 0){
		printList(aliasList, printAlias);
	}
	else if(strncmp("unalias", s, 7) == 0){
		removeItem(aliasList, buildNodeString(s, buildUnAliasString), cleanAlias, compareAlias);

	}
	else if(pipeCount > 0)
	{
		
		if(pipeCount == 1){
			if(strpbrk(s, "<") != NULL){
				int first = 0, x;
				
				for(x = 0; x < strlen(s); x++){
					if(s[x] == '|')
						first = 1;
					if(s[x] == '<')
						first = 0;
				}
				if(first == 1){// < appeared first | second e.g. ./a.out < in.txt | wc -w
					char * filename;
					char helper[100];
					int countpre = 0, countpost = 0;
					char ** pre = parsePrePipe(s, &countpre, "<", aliasList);
					strcpy(copy, s);
					token = strtok_r(copy, "<", &saveptr);
					token = strtok_r(NULL, "<", &saveptr);
					strcpy(helper, token);
					token = strtok_r(helper, "|", &saveptr);
					filename = token;
					filename = trim(filename);
					char ** post = parsePostPipe(s, &countpost, "|", aliasList);
					if( access( filename, F_OK) != -1){
						FILE * fin = fopen(filename, "r");
						pipeItInputRedirectLeftFirst(pre, post, fin, path);
						fclose(fin);
					}
					else
						printf("ERROR: FILE NOT FOUND\n");
					clean(countpre, pre);
					clean(countpost, post);
				}
				else{//
					printf("not acceptable command\n");
				}
			}
			else if(strpbrk(s, ">") != NULL){
				int first = 0, x;
				
				for(x = 0; x < strlen(s); x++){
					if(s[x] == '|')
						first = 1;
					if(s[x] == '>')
						first = 0;
				}
				if(first == 0){// | appeared first > second e.g.  ls -l | wc -w > output.txt
					char * filename;
					char helper[100];
					int countpre = 0, countpost = 0;
					char ** pre = parsePrePipe(s, &countpre, "|", aliasList);
					strcpy(copy, s);
					token = strtok_r(copy, "|", &saveptr);
					token = strtok_r(NULL, "|", &saveptr);
					char ** post = parsePrePipe(token, &countpost, ">", aliasList);
					strcpy(copy, s);
					token = strtok_r(copy, ">", &saveptr);
					token = strtok_r(NULL, ">", &saveptr);
					filename = token;
					filename = trim(filename);
					if( access( filename, F_OK) != -1){
						FILE * fin = fopen(filename, "w");
						pipeItInputRedirectRightLast(pre, post, fin, path);
						fclose(fin);
					}
					else
						printf("ERROR: FILE NOT FOUND\n");
					clean(countpre, pre);
					clean(countpost, post);
				}
				else{//
					printf("not acceptable command\n");
				}
			}
			else{
				prePipe = parsePrePipe(s, &preCount, "|", aliasList);
				postPipe = parsePostPipe(s, &postCount, "|", aliasList);
				pipeIt(prePipe, postPipe, path);
				clean(preCount, prePipe);
				clean(postCount, postPipe);
			}
		}
		else if(pipeCount == 2){
			prePipe = parsePrePipe(s, &preCount, "|", aliasList);
			postPipe = parsePostPipe(s, &postCount, "|", aliasList);
			lastPipe = parseLastPipe(s, &lastCount, aliasList);
			pipeItTwo(prePipe, postPipe, lastPipe, path);
			clean(preCount, prePipe);
			clean(postCount, postPipe);
			clean(lastCount, lastPipe);
		}
		
	}// end if pipeCount	
	
	else if(strstr(s, ">") != NULL && strstr(s, "<") == NULL){
		char * filename;
		int countpre = 0;
		char ** pre = parsePrePipe(s, &countpre, ">", aliasList);
		strcpy(copy, s);
		token = strtok_r(copy, ">", &saveptr);
		token = strtok_r(NULL, ">", &saveptr);
		filename = token;
		strip(filename);
		filename = trim(filename);
		FILE * fin = fopen(filename, "w");
		if(fin == NULL)
			printf("FILE NULL\n");
		pipeItOutputRedirect(pre, fin, path);
		fclose(fin);
		
		clean(countpre, pre);
	}
	else if(strstr(s, "<") != NULL && strstr(s, ">") == NULL){
		
		char * filename;
		int countpre = 0;
		char ** pre = parsePrePipe(s, &countpre, "<", aliasList);
		strcpy(copy, s);
		token = strtok_r(copy, "<", &saveptr);
		token = strtok_r(NULL, "<", &saveptr);
		filename = token;
		filename = trim(filename);
		if( access( filename, F_OK) != -1){
			FILE * fin = fopen(filename, "r");
			pipeItInputRedirect(pre, fin, path);
			fclose(fin);
		}
		else
			printf("ERROR: FILE NOT FOUND\n");
		clean(countpre, pre);
		


	}
	else if(strpbrk(s, ">") != NULL && strpbrk(s, "<") != NULL){
		char * letter = strstr(s, "<");
		char * letter2 = strstr(s, ">");
		int countpre1 = 0;

		char ** pre1;
		FILE * inputfile, *outputfile;
		
		if( letter < letter2){
			pre1 = parsePrePipe(s, &countpre1, "<", aliasList);
			strcpy(copy, s);
			token = strtok_r(copy, "<", &saveptr);
			token = strtok_r(NULL, ">", &saveptr);
			strip(token);
			trim(token);
			inputfile = fopen(token, "r");
			if(inputfile != NULL){
				strcpy(copy, s);
				token = strtok_r(copy, ">", &saveptr);
				token = strtok_r(NULL, ">", &saveptr);
				strip(token);
				trim(token);
				outputfile = fopen(token, "w");
				if(outputfile != NULL){
					pipeItLeftRight(pre1,inputfile, outputfile);
				}
				else
					printf("output file not found\n");

			}
			else
				printf("input file not found\n");
		}
		else{
			pre1 = parsePrePipe(s, &countpre1, ">", aliasList);
			strcpy(copy, s);
			token = strtok_r(copy, ">", &saveptr);
			token = strtok_r(NULL, "<", &saveptr);
			strip(token);
			trim(token);
			outputfile = fopen(token, "w");
			if(outputfile != NULL){
				strcpy(copy, s);
				token = strtok_r(copy, "<", &saveptr);
				token = strtok_r(NULL, "<", &saveptr);
				strip(token);
				trim(token);
				inputfile = fopen(token, "r");
				if(inputfile != NULL){
					//CALL FUNCTION HERE
					pipeItLeftRight(pre1,inputfile, outputfile);
				}
				else
					printf("input file not found\n");

			}
			else
				printf("output file not found\n");
			
		}
		if(inputfile != NULL)
		fclose(inputfile);
		if(outputfile != NULL)
		fclose(outputfile);
		clean(countpre1, pre1);
		
	}
	else if(s[0] == '!'){
		if(s[1] == '!'){
			MyCommand * command = (MyCommand*)printListByIndex(historyList, (historyList->size), printCommand);
			strcpy(s, command->command);
			argc = makeargs(s, &argv);
		  	if(argc != -1)
		  		forkIt(argv, path);
		  
		  	clean(argc, argv);
		  	argv = NULL;
			//goAgain = 1;
		}
		else{
			strcpy(copy, s);
			token = strtok_r(copy, "!", &saveptr);
			int index = atoi(token);
			MyCommand * command = (MyCommand*)printListByIndex(historyList, (index+1), printCommand);

			strcpy(s, command->command);
			goAgain = 1;
			
		}
	}//end !! commands
	else if(strcmp(s, "history") == 0){
		printListIndexRange(historyList, (historyList->size - histCount), printCommand);
		strcpy(s, "s");
	}// end if history
	else if(s[0] == 'c' && s[1] == 'd'){
		strcpy(copy, s);
		token = strtok_r(copy, "cd ", &saveptr);
		
		if(chdir(token)== -1)
			printf("That directory doesn't exist\n");

	}
	else if(strncmp("PATH", s, 4) == 0){
		//PATH=$PATH:/data/myprogs
		if(newPath != NULL)
			free(newPath);
		newPath = getPath(s);
		setenv("PATH", newPath, 1);
	}

	else
	{
		argc = makeargs(s, &argv);
	  	if(argc != -1)
	  		forkIt(argv, path);
	  
	  	clean(argc, argv);
	  	argv = NULL;
	}
	if(strcmp(s, "history") == 0){
		goAgain = 1;
	}
	
	
	if( goAgain == 0){
	printf("command?: ");
	fgets(s, MAX, stdin);
      	strip(s);
	if(strcmp(s, "!!") != 0)
		addLast(historyList, buildNodeString(s, buildCommandString));
	}
	goAgain = 0;
	
	findAliasMatch(aliasList, s);


  }// end while
  //Print to the mssh files
  FILE * outHist = fopen(".mssh_history", "w");
  if(outHist != NULL && historyList->size > 0)
    printListToFile(historyList, outHist, histFileCount, printCommandFile);

  //clean everything
  if(path != NULL){
  	free(path[0]);
  	free(path);
  }
  setenv("PATH", oldenv, 1);
  free(oldenv);
  free(newPath);
  fclose(outHist);
  clearList(historyList, cleanCommand);
  free(historyList);
  clearList(aliasList, cleanAlias);
  free(aliasList);
  return 0;

}// end main


void readHistValues(int *histcount, int *filecount){
	char s[MAX], copy[MAX];
	char *token, *saveptr = NULL;
	FILE *finrc = NULL;
	finrc = fopen(".msshrc", "r");
	if(finrc != NULL){
		fgets(s, 100, finrc);
		strip(s);
		strcpy(copy, s);

		token = strtok_r(copy, "=", &saveptr);
		token = strtok_r(NULL, "=", &saveptr);
		if(strncmp("HISTF",s,5) ==0)
		*filecount = atoi(token);
		else
		*histcount = atoi(token);
		fgets(s, 100, finrc);
		strcpy(copy, s);
		saveptr = NULL;
		token = strtok_r(copy, "=", &saveptr);
		token = strtok_r(NULL, "=", &saveptr);
		if(strncmp("HISTF",s,5) ==0)
		*filecount = atoi(token);
		else
		*histcount = atoi(token);
		fclose(finrc);
	}

}

char * getPath(char * s){
	char * temp;
	char copy[400];
	char * token, *saveptr = NULL;
	strip(s);
	strcpy(copy, s);
	token = strtok_r(copy, ":", &saveptr);
	token = strtok_r(NULL, "=", &saveptr);
	temp = (char *) calloc(strlen(token)+1, sizeof(char));
	strcpy(temp, token);
	return temp;
}

