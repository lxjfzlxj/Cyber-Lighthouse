#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
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
	int sendStatus = send(mySocket, sendData, strlen(sendData), 0);
	if (sendStatus < 0)
	{
		fprintf(stderr, "Failed to send data!\n");
		return;
	}
	else
	{
		printf("Succeed to send data!\n");
	}
	sleep(3);
	int readStatus = read(mySocket, readData, 100);
	if (readStatus < 0)
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
char udpString[10] = "UDPUDP";
void UDPwork()
{
	InputAddressAndData();
	int myTCPSocket = socket(DOMAIN, SOCK_STREAM, 0);
	if (myTCPSocket == -1)
	{
		fprintf(stderr, "Failed to create TCP socket!\n");
		return;
	}
	else
	{
		printf("Succeed to create TCP socket!\n");
	}
	int myUDPSocket = socket(DOMAIN, SOCK_DGRAM, 0);
	if (myUDPSocket == -1)
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
	serverAddress.sin_family = DOMAIN;													  // address family
	serverAddress.sin_addr.s_addr = inet_addr(address);									  // IP address
	serverAddress.sin_port = htons(port);												  // port
	int status = connect(myTCPSocket, (sockaddr *)&serverAddress, sizeof(serverAddress)); // connect
	// status	0: success	-1: failed
	if (status < 0)
	{
		fprintf(stderr, "Failed to connect(TCP)!\n");
		return;
	}
	else
	{
		printf("Succeed to connect(TCP)!\n");
	}
	int sendStatus = send(myTCPSocket, udpString, strlen(udpString), 0);
	if (sendStatus < 0)
	{
		fprintf(stderr, "Failed to send UDPUDP!\n");
		return;
	}
	else
	{
		printf("Succeed to send UDPUDP!\n");
	}
	sleep(3); //
	printf("senddata:%s\n", sendData);
	sendStatus = sendto(myUDPSocket, sendData, strlen(sendData), MSG_CONFIRM, (const sockaddr *)&serverAddress, sizeof(serverAddress));
	if (sendStatus < 0)
	{
		fprintf(stderr, "Failed to send data!\n");
		return;
	}
	else
	{
		printf("Succeed to send data!\n");
	}
	sleep(3);
	socklen_t socklen;
	int recvStatus = recvfrom(myUDPSocket, readData, 100, MSG_WAITALL, (sockaddr *)&serverAddress, &socklen);
	if (recvStatus < 0)
	{
		fprintf(stderr, "Failed to receive data!\n");
		return;
	}
	else
	{
		printf("Succeed to receive data!\n");
	}
	printf("result: %s\n", readData);
	close(myTCPSocket);
	close(myUDPSocket);
}
int main()
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