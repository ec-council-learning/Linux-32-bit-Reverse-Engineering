#include <string.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#define VERSION "1.00"
#define DEFAULT_BUFLEN 4096
#define DEFAULT_PORT "9999"


void Function1(char *Input);

DWORD WINAPI ConnectionHandler(LPVOID CSocket);


int main( int argc, char *argv[] ) {
	char PortNumber[6];
	const char Usage[94] = "Usage: %s [port_number]\n\nIf no port number is provided, the default port of %s will be used.\n";
	if ( argc > 2) {
		printf(Usage, argv[0], DEFAULT_PORT);
		return 1;
	} else if ( argc == 2 ) {
		if ( (atoi(argv[1]) > 0) && (atoi(argv[1]) < 65536) && (strlen(argv[1]) < 7) ) {
			strncpy(PortNumber, argv[1], 6);
		} else {
			printf(Usage, argv[0], DEFAULT_PORT);
			return 1;
		}
	} else {		
		strncpy(PortNumber, DEFAULT_PORT, 6);
	}
	printf("Starting vulnserver version %s\n", VERSION);
	EssentialFunc1(); // Call function from external dll
	printf("\nThis is vulnerable software!\nDo not allow access from untrusted systems or networks!\n\n");
	WSADATA wsaData;
	SOCKET ListenSocket = INVALID_SOCKET,
	ClientSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL, hints;
	int Result;
	struct sockaddr_in ClientAddress;
	int ClientAddressL = sizeof(ClientAddress);

	Result = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (Result != 0) {
		printf("WSAStartup failed with error: %d\n", Result);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	Result = getaddrinfo(NULL, PortNumber, &hints, &result);
	if ( Result != 0 ) {
		printf("Getaddrinfo failed with error: %d\n", Result);
		WSACleanup();
		return 1;
	}

	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("Socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	Result = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (Result == SOCKET_ERROR) {
		printf("Bind failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	Result = listen(ListenSocket, SOMAXCONN);
	if (Result == SOCKET_ERROR) {
		printf("Listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}		

	while(ListenSocket) {	
		printf("Waiting for client connections...\n");

		ClientSocket = accept(ListenSocket, (SOCKADDR*)&ClientAddress, &ClientAddressL);
		if (ClientSocket == INVALID_SOCKET) {
			printf("Accept failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}

		printf("Received a client connection from %s:%u\n", inet_ntoa(ClientAddress.sin_addr), htons(ClientAddress.sin_port));
		CreateThread(0,0,ConnectionHandler, (LPVOID)ClientSocket , 0,0);
		
	}

	closesocket(ListenSocket);
	WSACleanup();

	return 0;
}

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
