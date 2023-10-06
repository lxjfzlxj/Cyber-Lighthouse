#include "generator.h"
#include <bits/stdc++.h>

namespace GENERATOR
{
#define MAXSIZE 1000
	unsigned int ID;
	unsigned int QR, OPCODE, AA, TC, RD, RA, Z, RCODE;
	unsigned int QDCOUNT, ANCOUNT, NSCOUNT, ARCOUNT;
	int now = 0;
	unsigned char a[MAXSIZE];
	std::string domainName_Q;
	unsigned int QTYPE, QCLASS;
	void GenerateHeader()
	{
		a[now++] = ID >> 8;
		a[now++] = ID & 255;
		a[now++] = QR << 7 | OPCODE << 3 | AA << 2 | TC << 1 | RD;
		a[now++] = RA << 7 | Z << 4 | RCODE;
		a[now++] = QDCOUNT >> 8;
		a[now++] = QDCOUNT & 15;
		a[now++] = ANCOUNT >> 8;
		a[now++] = ANCOUNT & 15;
		a[now++] = NSCOUNT >> 8;
		a[now++] = NSCOUNT & 15;
		a[now++] = ARCOUNT >> 8;
		a[now++] = ARCOUNT & 15;
	}
	void GenerateQuestion()
	{
		for (int i = 0; i < domainName_Q.length(); i++)
		{
			int endPos;
			for (endPos = i; endPos < domainName_Q.length() && domainName_Q[endPos] != '.'; endPos++)
				;
			a[now++] = endPos - i;
			for (int j = i; j < endPos; j++)
				a[now++] = domainName_Q[j];
			i = endPos;
		}
		a[now++] = 0;

		a[now++] = QTYPE >> 8;
		a[now++] = QTYPE & 15;
		a[now++] = QCLASS >> 8;
		a[now++] = QCLASS & 15;
	}
	void Generate()
	{
		GenerateHeader();
		GenerateQuestion();
	}
	dataPackage answer;
	dataPackage Main(const char *type, const char *name, bool canRD)
	{
		answer.len = -1;
		srand((unsigned long long)(new char));
		if (strcmp(type, "A") == 0)
		{
			ID = rand() % 65536;
			QR = 0;
			OPCODE = 0;
			TC = 0;
			RD = canRD;
			QDCOUNT = 1;
			ANCOUNT = 0;
			NSCOUNT = 0;
			ARCOUNT = 0;
			domainName_Q = name;
			QTYPE = 1;
			QCLASS = 1;
		}
		else if(strcmp(type,"NS")==0) {
			ID = rand() % 65536;
			QR = 0;
			OPCODE = 0;
			TC = 0;
			RD = canRD;
			QDCOUNT = 1;
			ANCOUNT = 0;
			NSCOUNT = 0;
			ARCOUNT = 0;
			domainName_Q = name;
			QTYPE = 2;
			QCLASS = 1;
		}
		else
		{
			puts("[Failed to query]: Only queries of type A,NS are supported!");
			return answer;
		}
		Generate();
		memcpy(answer.a, a, sizeof(a));
		answer.len = now;
		return answer;
	}
}