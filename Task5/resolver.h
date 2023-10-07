#include <bits/stdc++.h>

namespace RESOLVER
{
#define MAXCOUNT 100
	struct OneResult
	{
		unsigned int TTL;
		unsigned int A_DATA;
	};
	struct ResolveResult
	{
		int num;
		std::string name;
		OneResult result[MAXCOUNT];
	};
	// struct ResolveResult{
	// 	int signal;
	// 	std::string name;
	// 	unsigned int address;
	// 	unsigned int TTL;
	// };
	ResolveResult Main(unsigned char *data, int dataSize);
}