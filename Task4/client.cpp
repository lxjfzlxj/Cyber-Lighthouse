#include "client.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <bits/stdc++.h>
namespace CLIENT
{
	const int DOMAIN = AF_INET;
	char address[100];
	char sendData[100];
	char readData[100];
	int port;
	void InputAddressAndData()
	{
		printf("IP address: ");
		scanf("%s", address);
		printf("port: ");
		scanf("%d", &port);
		printf("data: ");
		scanf("%s", sendData);
	}
	void TCPwork()
	{
		InputAddressAndData();
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
		ssize_t sendLength = send(mySocket, sendData, strlen(sendData), 0);
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
		ssize_t readLength = read(mySocket, readData, 100);
		if (readLength < 0)
		{
			fprintf(stderr, "Failed to read data!\n");
			return;
		}
		else
		{
			printf("Succeed to read data!\n");
		}
		printf("result: %s\n", readData);
		close(mySocket);
	}
	void UDPwork()
	{
		InputAddressAndData();
		int mySocket = socket(DOMAIN, SOCK_DGRAM, 0);
		if (mySocket == -1)
		{
			fprintf(stderr, "Failed to create UDP socket!\n");
			return;
		}
		else
		{
			printf("Succeed to create UDP socket!\n");
		}
		// describe an Internet socket address
		sockaddr_in serverAddress;
		serverAddress.sin_family = DOMAIN;					// address family
		serverAddress.sin_addr.s_addr = inet_addr(address); // IP address
		serverAddress.sin_port = htons(port);				// port
		ssize_t sendLength = sendto(mySocket, sendData, strlen(sendData), 0, (const sockaddr *)&serverAddress, sizeof(serverAddress));
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
		socklen_t socklen = sizeof(serverAddress);
		ssize_t recvLength = recvfrom(mySocket, readData, 100, 0, (sockaddr *)&serverAddress, &socklen);
		if (recvLength < 0)
		{
			fprintf(stderr, "Failed to receive data!\n");
			return;
		}
		else
		{
			printf("Succeed to receive data!\n");
		}
		printf("result: %s\n", readData);
		close(mySocket);
	}
	int Main(int _)
	{
		char chosenProtocol[10];
		printf("Choose TCP/UDP protocol: ");
		scanf("%s", chosenProtocol);
		if (strcmp(chosenProtocol, "TCP") == 0)
			TCPwork();
		else if (strcmp(chosenProtocol, "UDP") == 0)
			UDPwork();
		else
		{
			fprintf(stderr, "Input invalid protocol!\n");
			return 0;
		}
		return 0;
	}
}