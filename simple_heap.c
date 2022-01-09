#define BUFSIZE 256
int main(int argc, char **argv) {
  char *buf;
  buf = (char *)malloc(sizeof(char)*BUFSIZE);
  strcpy(buf, argv[1]);
}

insecure functions:
strcpy
strcat
printf/sprintf
gets

Alternative:
strlcpy*, strcpy_s*
strlcat*, strcat_s*
snprintf*, sprintf_s*
fgets
