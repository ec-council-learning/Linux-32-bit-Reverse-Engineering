#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

char memleak[]="password";
int main(int argc,char **argv){
	printf("Locate address here %p\n",&memleak);
	char buf[512];
	gets(buf);
	printf(buf);
	printf("\n");
}
