#include<stdio.h>
#include<string.h>
#include<unistd.h>

void main()
{
  char tmp[512];
  char buf[512];

  while(1)
  {
    memset(buf,'\0', 512);
    read(0, buf, 512);
    sprintf(tmp, buf);
    printf("%s", tmp);
  }
}
