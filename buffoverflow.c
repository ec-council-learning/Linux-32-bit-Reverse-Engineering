#include <stdio.h>
#include <string.h>
void overflow(){
printf(“Buffer Overflow practice script initiated!\n”);
}
int main(int argc, char *argv[])
{
	char buf[2000];
	strcpy(buf, argv[1]);
	printf(“%s”,buf);
	return(0);
}
