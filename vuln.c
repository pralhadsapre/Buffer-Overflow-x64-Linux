#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

unsigned long long *hold;
int i;


unsigned long long get_sp(void) { 
	__asm__("movq %rsp,%rax"); 
} 

void dumb(char *arg)
{
	long long *test;
	hold=(unsigned long long*)&test;
	char filename[1024];   //Buffer to hold filename.
	printf("\n\nValue of Test:%x",(unsigned long long)&test);
	printf("\nValue of filename[0]:%x\n",(unsigned long long)filename);
	printf("\nYou are going to need a buffer a little larger than:%d\n\n",(int)((long long)&test-(long long)filename));

	// puts (arg);
	strcpy (filename, arg);

	/*
	for (i=0;i<3;i++)
	{
		*hold=filename;
		hold=hold+1;
	}
	*/

	return;
}

int main(int argc, char* argv[])
{
	char holding[10000];               //This is just here as a buffer to try and keep you from overwriting main's return address, and into safe pages
	char *string;
	string=argv[1];
	unsigned long long stack; 
	stack=get_sp();

	if(argc>1)                //Make sure that a filename was provided.
	{
		printf("\nLength of Input String:%d\n", strlen(string));
		// puts(string);
		dumb(argv[1]);   
	}
	else
	{
		printf("\n\nError: No Command Line arg for vuln was given\n\n");
		dumb("Useless Text");
	}
	return (0);
}
