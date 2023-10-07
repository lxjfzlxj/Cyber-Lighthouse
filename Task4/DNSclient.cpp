#include "client.h"
#include "generator.h"
#include "resolver.h"
#include <bits/stdc++.h>
std::string queryType;
std::string DNSaddress;
int DNSport;
std::string domainName;
bool canRD;
int main(int argc, char *argv[])
{
	int argPos = 1;
	if (argv[argPos][0] == '@')
	{
		int i;
		for (i = 1; argv[argPos][i] != ':'; i++)
		{
			DNSaddress[i - 1] = argv[argPos][i];
		}
		sscanf(&argv[argPos][i + 1], "%d", &DNSport);
		argPos++;
	}
	else
	{
		DNSaddress = "8.8.8.8";
		DNSport = 53;
	}
	domainName = argv[argPos++];
	if (argv[argPos++][0] == 'Y')
	{
		queryType = "NS";
	}
	else
	{
		queryType = "A";
	}
	canRD=true;
	GENERATOR::dataPackage queryDNS = GENERATOR::Main(queryType.c_str(), domainName.c_str(), canRD);
	CLIENT::dataPackage resultDNS = CLIENT::Main("UDP", DNSaddress.c_str(), DNSport, queryDNS.a, queryDNS.len);
	RESOLVER::Main(resultDNS.a, resultDNS.len);
	return 0;
}