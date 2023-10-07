#include "responser.h"
#include <bits/stdc++.h>

namespace RESPONSER
{
#define MAXSIZE 1000
	unsigned int ID;
	unsigned int QR, OPCODE, AA, TC, RD, RA, Z, RCODE;
	unsigned int QDCOUNT, ANCOUNT, NSCOUNT, ARCOUNT;
	int now = 0;
	unsigned char a[MAXSIZE];
	std::string domainName_A;
	unsigned int A_TYPE, A_CLASS, A_TTL, A_RDLENGTH;
	void GenerateHeader()
	{
		a[now++] = ID >> 8;
		a[now++] = ID & 255;
		a[now++] = QR << 7 | OPCODE << 3 | AA << 2 | TC << 1 | RD;
		a[now++] = RA << 7 | Z << 4 | RCODE;
		a[now++] = QDCOUNT >> 8;
		a[now++] = QDCOUNT & 255;
		a[now++] = ANCOUNT >> 8;
		a[now++] = ANCOUNT & 255;
		a[now++] = NSCOUNT >> 8;
		a[now++] = NSCOUNT & 255;
		a[now++] = ARCOUNT >> 8;
		a[now++] = ARCOUNT & 255;
	}
	void GenerateAnswer(unsigned int answer)
	{
		for (int i = 0; i < domainName_A.length(); i++)
		{
			int endPos;
			for (endPos = i; endPos < domainName_A.length() && domainName_A[endPos] != '.'; endPos++)
				;
			a[now++] = endPos - i;
			for (int j = i; j < endPos; j++)
				a[now++] = domainName_A[j];
			i = endPos;
		}
		a[now++] = 0;

		a[now++] = A_TYPE >> 8;
		a[now++] = A_TYPE & 255;
		a[now++] = A_CLASS >> 8;
		a[now++] = A_CLASS & 255;
		a[now++] = (A_TTL >> 24) & 255;
		a[now++] = (A_TTL >> 16) & 255;
		a[now++] = (A_TTL >> 8) & 255;
		a[now++] = A_TTL & 255;
		a[now++] = A_RDLENGTH >> 8;
		a[now++] = A_RDLENGTH & 255;
		a[now++] = (answer >> 24) & 255;
		a[now++] = (answer >> 16) & 255;
		a[now++] = (answer >> 8) & 255;
		a[now++] = answer & 255;
	}
	void Generate(QueryInfomation information)
	{
		GenerateHeader();
		for (int i = 0; i < ANCOUNT; i++)
		{
			GenerateAnswer(information.result[i]);
		}
	}
	dataPackage answer;
	dataPackage Main(const char *type, QueryInfomation information)
	{
		answer.len = -1;
		now=0;
		srand((unsigned long long)(new char));
		if (strcmp(type, "A") == 0)
		{
			ID = rand() % 65536;
			QR = 1;
			OPCODE = 0;
			TC = 0;
			RD = 1;
			RA = 1;
			RCODE = 0;
			QDCOUNT = 0;
			ANCOUNT = information.num;
			NSCOUNT = 0;
			ARCOUNT = 0;
			domainName_A = information.name;
			A_TYPE = 1;
			A_CLASS = 1;
			A_TTL = information.endTime - time(NULL);
			A_RDLENGTH = 4;
		}
		else
		{
			puts("[Failed to query]: Only queries of type A are supported!");
			return answer;
		}
		Generate(information);
		memcpy(answer.a, a, sizeof(a));
		answer.len = now;
		return answer;
	}
}