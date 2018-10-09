#define _GNU_SOURCE
#include "process.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void forkIt(char ** argv, char ** s)
{
	int status;
	pid_t pid = fork();
	//char ** t;
	//t = (char**)calloc(2, sizeof(char *));
	//t[0] = (char*)calloc(strlen("/etc")+1, sizeof(char));
	//strcpy(t[0], "/etc");
	if(pid != 0 ){
		waitpid(pid, &status, 0);
	}
	else
	{
		//printf("PATH is %s\n%s not found\n", getenv("PATH"), argv[0]);
		int res = execvpe(argv[0], argv, s);
		if(res == -1)
		{
			printf("PATH is %s\n%s not found\n", getenv("PATH"), argv[0]);
		}
		exit(res);
	}

}
