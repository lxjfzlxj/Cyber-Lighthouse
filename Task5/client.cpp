#include "client.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <bits/stdc++.h>
namespace CLIENT
{
#define MAXSIZE 1000
	const int DOMAIN = AF_INET;
	unsigned char readData[MAXSIZE];
	dataPackage answer;
	void TCPwork(const char *address, int port, unsigned char *sendData, int dataSize)
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
			return;
		}
		else
		{
			printf("Succeed to create socket!\n");
		}
		// describe an Internet socket address
		sockaddr_in serverAddress;
		serverAddress.sin_family = DOMAIN;												   // address family
		serverAddress.sin_addr.s_addr = inet_addr(address);								   // IP address
		serverAddress.sin_port = htons(port);											   // port
		int status = connect(mySocket, (sockaddr *)&serverAddress, sizeof(serverAddress)); // connect
		// status	0: success	-1: failed
		if (status < 0)
		{
			fprintf(stderr, "Failed to connect!\n");
			return;
		}
		else
		{
			printf("Succeed to connect!\n");
		}
		ssize_t sendLength = send(mySocket, sendData, dataSize, 0);
		if (sendLength < 0)
		{
			fprintf(stderr, "Failed to send data!\n");
			return;
		}
		else
		{
			printf("Succeed to send data!\n");
		}
		sleep(3);
		ssize_t readLength = read(mySocket, readData, MAXSIZE);
		if (readLength < 0)
		{
			fprintf(stderr, "Failed to read data!\n");
			return;
		}
		else
		{
			printf("Succeed to read data!\n");
		}
		close(mySocket);
		answer.len = readLength;
		memcpy(answer.a, readData, sizeof(readData));
	}
	void UDPwork(const char *address, int port, unsigned char *sendData, int dataSize)
	{
		int mySocket = socket(DOMAIN, SOCK_DGRAM, 0);
		if (mySocket == -1)
		{
			fprintf(stderr, "Failed to create UDP socket!\n");
			return;
		}
		// else
		// {
		// 	printf("Succeed to create UDP socket!\n");
		// }
		// describe an Internet socket address
		sockaddr_in serverAddress;
		serverAddress.sin_family = DOMAIN;					// address family
		serverAddress.sin_addr.s_addr = inet_addr(address); // IP address
		serverAddress.sin_port = htons(port);				// port
		ssize_t sendLength = sendto(mySocket, sendData, dataSize, 0, (const sockaddr *)&serverAddress, sizeof(serverAddress));
		if (sendLength < 0)
		{
			fprintf(stderr, "Failed to send data!\n");
			return;
		}
		// else
		// {
		// 	printf("Succeed to send data!\n");
		// }
		socklen_t socklen = sizeof(serverAddress);
		ssize_t recvLength = recvfrom(mySocket, readData, MAXSIZE, 0, (sockaddr *)&serverAddress, &socklen);
		if (recvLength < 0)
		{
			fprintf(stderr, "Failed to receive data!\n");
			return;
		}
		// else
		// {
		// 	printf("Succeed to receive data!\n");
		// }
		close(mySocket);
		answer.len = recvLength;
		memcpy(answer.a, readData, sizeof(readData));
	}
	dataPackage Main(const char *protocol, const char *address, int port, unsigned char *sendData, int dataSize)
	{
		answer.len = -1;
		if (strcmp(protocol, "TCP") == 0)
			TCPwork(address, port, sendData, dataSize);
		else if (strcmp(protocol, "UDP") == 0)
			UDPwork(address, port, sendData, dataSize);
		else
		{
			fprintf(stderr, "Input invalid protocol!\n");
		}
		return answer;
	}
}