#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

int copier(char *str) {
	char buffer[2000];
	strcpy(buffer, str);
}
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int s, new_socket, port;
     socklen_t clilen;
     char buffer[3500], reply[5100];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     s = socket(AF_INET, SOCK_STREAM, 0);
     if (s < 0) 
        error("ERROR creating socket connection");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     port = 9999;
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(port);
     if (bind(s, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("Error");
     listen(s,5);
     clilen = sizeof(cli_addr);
     new_socket = accept(s, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (new_socket < 0) 
          error("Cannot accept data");
     while (1) {
        n = write(new_socket,"Buffer Overflow Practice!\n",25);
        bzero(buffer,3500);
        n = read(new_socket,buffer,3499);
        if (n < 0) error("Couldn't read sent data");

       
	copier(buffer);

        printf("Here is the message: %s\n",buffer);
        strcpy(reply, "I got this message: ");
        strcat(reply, buffer);
        n = write(new_socket, reply, strlen(reply));
        if (n < 0) error("ERROR writing to socket");
        }
     close(new_socket);
     close(s);
     return 0; 
}
