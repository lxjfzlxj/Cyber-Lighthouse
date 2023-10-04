#include <bits/stdc++.h>
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
int main(int argc, char *argv[])
{
	srand((unsigned long long)(new char));
	if (strcmp(argv[1], "A") == 0)
	{
		ID = rand() % 65536;
		QR = 0;
		OPCODE = 0;
		TC = 0;
		RD = 1;
		QDCOUNT = 1;
		ANCOUNT = 0;
		NSCOUNT = 0;
		ARCOUNT = 0;
		domainName_Q = argv[2];
		QTYPE = 1;
		QCLASS = 1;
	}
	else
	{
		puts("[Failed to query]: Only queries of type A are supported!");
		return 0;
	}
	Generate();
	FILE *file = fopen(argv[3], "wb");
	if (file == NULL)
	{
		fprintf(stderr, "Can't open the file!\n");
		return -1;
	}
	fwrite(a, sizeof(unsigned char), now, file);
	return 0;
}