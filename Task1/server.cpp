#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <thread>
int TCPport;
int UDPport;
bool UDPok;
void Input()
{
	printf("allow to receive UDP package?(Y/N): ");
	char ch;
	scanf("%c", &ch);
	if (ch == 'Y')
		UDPok = true;
	else
		UDPok = false;
	printf("set TCP port: ");
	scanf("%d", &TCPport);
	printf("set UDP port: ");
	scanf("%d", &UDPport);
}
int main()
{
	Input(); 
	int TCPsocket = socket(AF_INET, SOCK_STREAM, 0);
	if (TCPsocket == -1)
	{
		fprintf(stderr, "Failed to create TCP socket!\n");
		return -1;
	}

	struct sockaddr_in TCPaddress;
	TCPaddress.sin_family = AF_INET;
	TCPaddress.sin_port = htons(TCPport);
	TCPaddress.sin_addr.s_addr = INADDR_ANY;

	if (bind(TCPsocket, (struct sockaddr *)&TCPaddress, sizeof(TCPaddress)) == -1) //将 socket 和端口绑定
	{
		fprintf(stderr, "Failed to bind TCP socket!\n");
		close(TCPsocket);
		return -1;
	}

	if (listen(TCPsocket, 5) == -1) //监听端口
	{
		fprintf(stderr, "Failed to listen on TCP socket!\n");
		close(TCPsocket);
		return -1;
	}

	int UDPsocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (UDPsocket == -1)
	{
		fprintf(stderr, "Failed to create UDP socket!\n");
		close(TCPsocket);
		return -1;
	}
	sockaddr_in UDPaddress;
	UDPaddress.sin_family = AF_INET;
	UDPaddress.sin_port = htons(UDPport);
	UDPaddress.sin_addr.s_addr = INADDR_ANY;

	if (bind(UDPsocket, (struct sockaddr *)&UDPaddress, sizeof(UDPaddress)) == -1)
	{
		fprintf(stderr, "Failed to bind UDP socket!\n");
		close(TCPsocket);
		close(UDPsocket);
		return -1;
	}
	//双线程处理 TCP 和 UDP 请求 
	std::thread TCPthread([&]()
						  {
    	while (1) {
			char data[100];
			sockaddr_in clientAddress;
			socklen_t addressLength = sizeof(clientAddress);
			int clientSocket = accept(TCPsocket, (struct sockaddr*)&clientAddress, &addressLength);
			if (clientSocket == -1) {
				fprintf(stderr, "Failed to connect with TCP!\n");
				continue;
			}
			ssize_t dataLength = recv(clientSocket, data, sizeof(data), 0);
			send(clientSocket, data, dataLength, 0);
			close(clientSocket);} });

	std::thread UDPthread([&]()
						  {
		while (1)
		{
			char data[100];
			sockaddr_in clientAddress;
			socklen_t addressLength = sizeof(clientAddress);
			ssize_t recvLength = recvfrom(UDPsocket, data, sizeof(data), 0, (struct sockaddr *)&clientAddress, &addressLength);
			if (recvLength == -1)
			{
				fprintf(stderr, "Failed to receive UDP package!\n");
				continue;
			}
			else if(UDPok == false) {
				fprintf(stderr, "UDP is not allowed!\n");
				continue;
			}
			sendto(UDPsocket, data, sizeof(data), 0, (struct sockaddr *)&clientAddress, addressLength);

		} });
	UDPthread.join();
}