#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "client.h"
#include "resolver.h"
#include "responser.h"
#define MAXSIZE 1000
#define MAXCOUNT 100
unsigned char query[MAXSIZE];
struct HistoryQuery
{
	unsigned char query[1000];
	int queryLength;
};
bool operator<(const HistoryQuery &query1, const HistoryQuery &query2)
{
	return query1.queryLength < query2.queryLength ||
		   query1.queryLength == query2.queryLength &&
			   memcmp(query1.query + 2, query2.query + 2, query1.queryLength - 2) < 0;
}
std::map<HistoryQuery, QueryInfomation> queryMap;
void printAddress(unsigned int result)
{
	printf("	Address: %u.%u.%u.%u\n", (result >> 24) & 255, (result >> 16) & 255, (result >> 8) & 255, result & 255);
}
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
		HistoryQuery historyQuery;
		QueryInfomation information;
		memcpy(historyQuery.query, query, MAXSIZE);
		historyQuery.queryLength = recvLength;
		if (!queryMap.count(historyQuery) || queryMap[historyQuery].endTime < clock())
		{

			std::string serverAddress = "202.114.0.131";
			CLIENT::dataPackage response = CLIENT::Main("UDP", serverAddress.c_str(), 53, query, recvLength);
			RESOLVER::ResolveResult allResult = RESOLVER::Main(response.a, response.len);
			information.num = allResult.num;
			information.name=allResult.name;
			for (int i = 0; i < allResult.num; i++)
			{
				information.result[i] = allResult.result[i].A_DATA;
				if (i == 0)
				{
					information.endTime = time(NULL) + allResult.result[i].TTL;
					information.TTL = allResult.result[i].TTL;
				}
				else
				{
					information.endTime = std::min(information.endTime, time(NULL) + allResult.result[i].TTL);
					information.TTL = std::min(information.TTL, allResult.result[i].TTL);
				}
			}
			queryMap[historyQuery] = information;
		}
		
		RESPONSER::dataPackage result = RESPONSER::Main("A", queryMap[historyQuery]);
		sendto(mySocket, result.a, result.len, 0, (struct sockaddr *)&clientAddress, addressLength);
	}
	return 0;
}