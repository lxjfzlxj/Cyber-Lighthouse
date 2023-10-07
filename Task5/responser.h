#include <bits/stdc++.h>
struct QueryInfomation
	{
		int num;
		unsigned int result[100];
		unsigned int TTL;
		time_t endTime;
		std::string name;
	};
namespace RESPONSER
{
#define MAXSIZE 1000
	struct dataPackage
	{
		unsigned char a[MAXSIZE];
		int len;
	};
	
	dataPackage Main(const char *type, QueryInfomation information);

}