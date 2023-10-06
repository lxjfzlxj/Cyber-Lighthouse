#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "client.h"
#include "resolver.h"
#define MAXSIZE 1000
unsigned char query[MAXSIZE];
int main(int argc, char *argv[])
{
	bool canRD;
	if (argv[1][0] == 'Y')
		canRD = true;
	else
		canRD = false;
	int port;
	sscanf(argv[2], "%d", &port);
	int mySocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (mySocket == -1)
	{
		fprintf(stderr, "Failed to create UDP socket!\n");
		return -1;
	}
	sockaddr_in UDPaddress;
	UDPaddress.sin_family = AF_INET;
	UDPaddress.sin_port = htons(port);
	UDPaddress.sin_addr.s_addr = INADDR_ANY;
	if (bind(mySocket, (struct sockaddr *)&UDPaddress, sizeof(UDPaddress)) == -1)
	{
		fprintf(stderr, "Failed to bind UDP socket!\n");
		close(mySocket);
		return -1;
	}
	while (1)
	{
		sockaddr_in clientAddress;
		socklen_t addressLength = sizeof(clientAddress);
		ssize_t recvLength = recvfrom(mySocket, query, sizeof(query), 0, (struct sockaddr *)&clientAddress, &addressLength);
		if (recvLength == -1)
		{
			fprintf(stderr, "Failed to receive UDP package!\n");
			continue;
		}
		while (1)
		{
			CLIENT::dataPackage response = CLIENT::Main("UDP", "198.41.0.4", 53, query, recvLength);
			RESOLVER::Main(response.a,response.len);
			printf("length:%d\n", response.len);
			break;
		}
	}
	return 0;
}