#include<stdio.h>
#include<string.h>
#include<unistd.h>

char data[]="password";
int main(int argc, char **argv){
	char tmp[512];
	char buf[512];
	printf("Locate address: %p\n",&data);
//	memset(buf,'\0', 512);
	read(0, buf, 512);
	sprintf(tmp, buf);
	printf("%s", tmp);

}
