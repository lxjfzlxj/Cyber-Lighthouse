#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
const int DOMAIN = AF_INET;
int main()
{
	/*
	create socket
	domain
		AF_INET: between different hosts with IPV4
		AF_LOCAL: on the same host
	type
		SOCK_STREAM: TCP
		SOCK_DGRAM: UDP
	protocol: 0
	*/
	int mySocket = socket(DOMAIN, SOCK_STREAM, 0);
	if (mySocket == -1)
	{
		fprintf(stderr, "Failed to create socket!\n");
		return 1;
	}
	else
	{
		printf("Succeed to create socket!\n");
	}
	// describe an Internet socket address
	sockaddr_in serverAddress;
	serverAddress.sin_family = DOMAIN;												   // address family
	serverAddress.sin_addr.s_addr = inet_addr("0.0.0.0");							   // IP address
	serverAddress.sin_port = htons(8080);											   // port
	int status = connect(mySocket, (sockaddr *)&serverAddress, sizeof(serverAddress)); // connect
	// status	0: success	-1: failed
	if (status < 0)
	{
		fprintf(stderr, "Failed to connect!\n");
		return 2;
	}
	else
	{
		printf("Succeed to connect!\n");
	}
	char *sendData = "12345";
	char *readData;
	send(mySocket, sendData, strlen(sendData), 0);
	read(mySocket, readData, 100);
	printf("%s\n", readData);
	close(mySocket);
	return 0;
}