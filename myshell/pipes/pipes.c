#define _GNU_SOURCE
#include "pipes.h"
#include "../tokenize/makeArgs.h"



int containsPipe(char *s){
	int x, counter = 0;
	for(x = 0; x < strlen(s); x++){
		if(s[x] == '|'){
			counter++;
		}
	}
	return counter;
}
char ** parsePrePipe(char *s, int * preCount, char * delimeter, LinkedList * aliasList){
	char **argv = NULL;
	char copy[100];
	strcpy(copy, s);
	char *save = NULL;
	char *token = strtok_r(copy, delimeter, &save);
	strip(token);
	trimmem(token);
	findAliasMatch(aliasList, token);
	//printf("Prepipe: %s3\n", token);
	int total = makeargs(token, &argv);
	*preCount = total;
	
	return argv;
}
char ** parsePostPipe(char *s, int * postCount, char * delimeter, LinkedList * aliasList){
	char **argv = NULL;
	char copy[100];
	strcpy(copy, s);
	char *save = NULL;
	char *token = strtok_r(copy, delimeter, &save);
	
	token = strtok_r(NULL, delimeter, &save);
	//strip(token);
	trimmem(token);
	
	findAliasMatch(aliasList, token);
//printf("the token in postpipe: %s\n", token);
	int total = makeargs(token, &argv);
	
	*postCount = total;

	return argv;
}
char ** parseLastPipe(char *s, int * postCount, LinkedList * aliasList){
	char **argv = NULL;
	char *save = NULL;
	char *token = strtok_r(s, "|", &save);

	token = strtok_r(NULL, "|", &save);
	token = strtok_r(NULL, "|", &save);
	strip(token);
	trimmem(token);
	findAliasMatch(aliasList, token);
	int total = makeargs(token, &argv);
	
	*postCount = total;

	return argv;
}
void pipeItTwo(char ** prePipe, char ** postPipe, char ** lastPipe, char ** path){

	int status, res, respipe2;
	pid_t pid1 = fork();
	if(pid1 != 0)
		waitpid(pid1, &status, 0);
	else
	{
		//pipe
		pid_t pid;
		int fd[2];
		int fd2[2];
		respipe2 = pipe(fd2);

		if(respipe2 < 0)
		{
			printf("Pipe2 Failure\n");
			exit(-1);
		}// end if

		pid = fork();

		if(pid != 0)
		{
	   		close(fd2[1]);
			close(0);
			dup(fd2[0]);
			close(fd2[0]);
			int res2 = execvpe(lastPipe[0],lastPipe, path);
			exit(res2);		

		}// end if AKA parent
		else
		{
			
			//pipe
			pid_t pid2;

			res = pipe(fd);

			if(res < 0)
			{
				printf("Pipe Failure\n");
				exit(-1);
			}// end if

			pid2 = fork();

			if(pid2 != 0)
			{
		   		close(fd[1]);
				close(0);
				dup(fd[0]);
				close(fd[0]);

				close(fd2[0]);
				close(1);
				dup(fd2[1]);
				close(fd2[1]);
				int res3 = execvpe(postPipe[0],postPipe, path);// wc -w
				exit(res3);		

			}// end if AKA parent
			else
			{
			
				close(fd[0]);
				close(1);
				dup(fd[1]);
				close(fd[1]);
				int res3 = execvpe(prePipe[0], prePipe, path); // ls -l
				exit(res3);
			}// end else AKA child
		}// end else AKA child

		
	}
}
void pipeIt(char ** prePipe, char ** postPipe, char ** path){
	int status, res;
	pid_t pid1 = fork();
	if(pid1 != 0)
		waitpid(pid1, &status, 0);
	else
	{
		//pipe
		pid_t pid;
		int fd[2];

		res = pipe(fd);

		if(res < 0)
		{
			printf("Pipe Failure\n");
			exit(-1);
		}// end if

		pid = fork();

		if(pid != 0)
		{
	   		close(fd[1]);
			close(0);
			dup(fd[0]);
			close(fd[0]);
			int res2 = execvpe(postPipe[0],postPipe, path);//wc -w
			exit(res2);		

		}// end if AKA parent
		else
		{
			close(fd[0]);
			close(1);
			dup(fd[1]);
			close(fd[1]);
			int res1 = execvpe(prePipe[0], prePipe, path);//ls -l
			exit(res1);
		}// end else AKA child
	}
}

void pipeItInputRedirect(char ** postPipe, FILE * fin, char ** path){
	int status, res;
	pid_t pid1 = fork();
	if(pid1 != 0)
		waitpid(pid1, &status, 0);
	else
	{
		//pipe
		pid_t pid;
		int fd[2];

		res = pipe(fd);

		if(res < 0)
		{
			printf("Pipe Failure\n");
			exit(-1);
		}// end if

		pid = fork();

		if(pid != 0)
		{
	   		close(fd[1]);
			close(0);
			dup(fd[0]);
			close(fd[0]);
			int res2 = execvpe(postPipe[0],postPipe, path);//wc -w
			exit(res2);		

		}// end if AKA parent
		else
		{
			char temp[100];
			close(fd[0]);
			close(1);
			dup(fd[1]);
			close(fd[1]);
			fgets(temp, 100, fin);
	
			   while(!feof(fin))
			   {
			      fgets(temp, 100, fin);
				printf("%s", temp);
			   }// end while
			exit(1);
		}// end else AKA child
	}
}
void pipeItOutputRedirect(char ** postPipe, FILE * fout, char ** path){
	int status, res;
	pid_t pid1 = fork();
	
	if(pid1 != 0){
		waitpid(pid1, &status, 0);
	}
	else
	{
		//pipe
		pid_t pid;
		int fd[2];

		res = pipe(fd);
		if(res < 0)
		{
			printf("Pipe Failure\n");
			exit(-1);
		}// end if

		pid = fork();

		if(pid != 0)
		{
			
	   		close(fd[1]);
			close(0);
			dup(fd[0]);
			close(fd[0]);
			char temp[1000];

			fgets(temp, 1000, stdin);
			int x;
			   while(!feof(stdin))
			   {

				fprintf(fout,"%s", temp);
				fgets(temp, 1000, stdin);
				
			   }// end while
				exit(1);	

		}// end if AKA parent
		else
		{
			close(fd[0]);
			close(1);
			dup(fd[1]);
			close(fd[1]);
			int res1 = execvpe(postPipe[0], postPipe, path);//ls -l
			printf("\\0");
			exit(res1);
		}// end else AKA child
	}
}

void pipeItInputRedirectLeftFirst(char ** prePipe,char ** postPipe, FILE * fout, char ** path){
	int status, res, respipe2;
	pid_t pid1 = fork();
	if(pid1 != 0)
		waitpid(pid1, &status, 0);
	else
	{
		//pipe
		pid_t pid;
		int fd[2];
		int fd2[2];
		respipe2 = pipe(fd2);

		if(respipe2 < 0)
		{
			printf("Pipe2 Failure\n");
			exit(-1);
		}// end if

		pid = fork();

		if(pid != 0)
		{
	   		close(fd2[1]);
			close(0);
			dup(fd2[0]);
			close(fd2[0]);
			int res2 = execvpe(postPipe[0],postPipe, path);
			exit(res2);		

		}// end if AKA parent
		else
		{
			//pipe
			pid_t pid2;

			res = pipe(fd);

			if(res < 0)
			{
				printf("Pipe Failure\n");
				exit(-1);
			}// end if

			pid2 = fork();

			if(pid2 != 0)
			{
		   		close(fd[1]);
				close(0);
				dup(fd[0]);
				close(fd[0]);

				close(fd2[0]);
				close(1);
				dup(fd2[1]);
				close(fd2[1]);
				int res3 = execvpe(prePipe[0],prePipe, path);// wc -w
				exit(res3);		

			}// end if AKA parent
			else
			{
				
				char temp[100];
				close(fd[0]);
				close(1);
				dup(fd[1]);
				close(fd[1]);
				fgets(temp, 100, fout);
	
			        while(!feof(fout))
			        {
					fgets(temp, 100, fout);
					printf("%s", temp);
			        }// end while
				exit(1);
			}// end else AKA child
		}// end else AKA child

		
	}
}

void pipeItInputRedirectRightLast(char ** prePipe,char ** postPipe, FILE * fout, char ** path){
	int status, res, respipe2;
	pid_t pid1 = fork();
	if(pid1 != 0)
		waitpid(pid1, &status, 0);
	else
	{
		//pipe
		pid_t pid;
		int fd[2];
		int fd2[2];
		respipe2 = pipe(fd2);

		if(respipe2 < 0)
		{
			printf("Pipe2 Failure\n");
			exit(-1);
		}// end if

		pid = fork();

		if(pid != 0)
		{
	   		close(fd2[1]);
			close(0);
			dup(fd2[0]);
			close(fd2[0]);
			char temp[1000];

			fgets(temp, 1000, stdin);
			int x;
			   while(!feof(stdin))
			   {

				fprintf(fout,"%s", temp);
				fgets(temp, 1000, stdin);
				
			   }// end while
				exit(1);		

		}// end if AKA parent
		else
		{
			
			//pipe
			pid_t pid2;

			res = pipe(fd);

			if(res < 0)
			{
				printf("Pipe Failure\n");
				exit(-1);
			}// end if

			pid2 = fork();
// | appeared first > second e.g.  ls -l | wc -w > output.txt
			if(pid2 != 0)
			{
		   		close(fd[1]);
				close(0);
				dup(fd[0]);
				close(fd[0]);

				close(fd2[0]);
				close(1);
				dup(fd2[1]);
				close(fd2[1]);
				int res3 = execvpe(postPipe[0],postPipe, path);// wc -w
				exit(res3);		

			}// end if AKA parent
			else
			{
			
				close(fd[0]);
				close(1);
				dup(fd[1]);
				close(fd[1]);
				int res3 = execvpe(prePipe[0], prePipe, path); // ls -l
				exit(res3);
			}// end else AKA child
		}// end else AKA child

		
	}
}

void pipeItLeftRight(char ** prePipe,FILE * fin, FILE * fout){
	int status, res, respipe2;
	pid_t pid1 = fork();
	if(pid1 != 0)
		waitpid(pid1, &status, 0);
	else
	{
		//pipe
		pid_t pid;
		int fd[2];
		int fd2[2];
		respipe2 = pipe(fd2);

		if(respipe2 < 0)
		{
			printf("Pipe2 Failure\n");
			exit(-1);
		}// end if

		pid = fork();

		if(pid != 0)
		{
	   		close(fd2[1]);
			close(0);
			dup(fd2[0]);
			close(fd2[0]);
			char temp[1000];

			fgets(temp, 1000, stdin);
			int x;
			   while(!feof(stdin))
			   {

				fprintf(fout,"%s", temp);
				fgets(temp, 1000, stdin);
				
			   }// end while
				exit(1);		

		}// end if AKA parent
		else
		{
			//pipe
			pid_t pid2;

			res = pipe(fd);

			if(res < 0)
			{
				printf("Pipe Failure\n");
				exit(-1);
			}// end if

			pid2 = fork();

			if(pid2 != 0)
			{
		   		close(fd[1]);
				close(0);
				dup(fd[0]);
				close(fd[0]);

				close(fd2[0]);
				close(1);
				dup(fd2[1]);
				close(fd2[1]);
				int res3 = execvpe(prePipe[0],prePipe, NULL);// wc -w

				exit(res3);		

			}// end if AKA parent
			else
			{
				
				char temp[100];
				close(fd[0]);
				close(1);
				dup(fd[1]);
				close(fd[1]);
				fgets(temp, 100, fin);
	
			        while(!feof(fin))
			        {
					fgets(temp, 100, fin);
					printf("%s", temp);
			        }// end while
				exit(1);
			}// end else AKA child
		}// end else AKA child

		
	}
}
