#include "myUtils.h"
#include <ctype.h>

char * trim(char * s){
if(s != NULL && strlen(s) > 1){
	while(s[0] == ' '){
			char * token, *save = NULL;
			char copy[MAX];
			strcpy(copy, s);
			token = strtok_r(copy, " ", &save);
			strcpy(s, token);
		}
	/*if(s != NULL && strlen(s) > 2){
	int i, j = 0;
		for(i = 0; s[i] != '\0'; i++){
			if(s[i] == ' '){
				s = &s[1];
				i--;
				/*for(j = i; j+1 != '\0'; j++)
					s[j] = s[j+1];
				s[j] = '\0';*/
			/*}
		}
		
	}*/
}	
	if(s[strlen(s)-1 ] == ' ')
		s[strlen(s)-1] = '\0';
	
return s;
}

char * trimmem(char * s){
while(s[0] == ' '){
			/*char * token, *save = NULL;
			char copy[MAX];
			strcpy(copy, s);
			token = strtok_r(copy, " ", &save);
			strcpy(s, token);*/
		memmove(s, s+1, strlen(s));

}
if(s[strlen(s)-1 ] == ' ')
		s[strlen(s)-1] = '\0';
return s;
}

void strip(char *array)
{
	if(array == NULL)
	{
		perror("array is null");
		exit(-99);
	}// end if

	int len = strlen(array), x = 0;
   
	while(array[x] != '\0' && x < len)
	{
	  if(array[x] == '\r')
		 array[x] = '\0';

	  else if(array[x] == '\n')
		 array[x] = '\0';
	

	  x++;

	}// end while
   
}// end strip

int menu()
{
   char temp[MAX];
   int choice;
   printf("1) Print the list\n");
   printf("2) Add First\n");
   printf("3) Add Last\n");
   printf("4) Sort\n");
   printf("5) Remove Item\n"); 
   printf("6) Quit\n"); 
   printf("Choice --> ");
   fgets(temp, MAX, stdin);
   choice = atoi(temp);

   
   while(choice < 1 || choice > 6)
   {
      printf("1) Print the list\n");
      printf("2) Add First\n");
      printf("3) Add Last\n");
      printf("4) Sort\n");
      printf("5) Remove Item\n"); 
      printf("6) Quit\n"); 
      printf("Choice --> ");
      fgets(temp, MAX, stdin);
      choice = atoi(temp);
   
   }// end while

   return choice;
   
}// end menu
