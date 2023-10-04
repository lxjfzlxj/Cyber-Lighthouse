#include <bits/stdc++.h>
#define MAXSIZE 1000
#define MAXCOUNT 100
char base16Char[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
unsigned int ID;
unsigned int QR, OPCODE, AA, TC, RD, RA, RCODE;
unsigned int QDCOUNT, ANCOUNT, NSCOUNT, ARCOUNT;
int now = 0;
unsigned char a[MAXSIZE];
std::string domainName_Q[MAXCOUNT];
unsigned int QTYPE[MAXCOUNT], QCLASS[MAXCOUNT];
std::map<int, std::string> domainNameMap;
std::string domainName_A[MAXCOUNT];
unsigned int TYPE_A[MAXCOUNT], CLASS_A[MAXCOUNT], TTL_A[MAXCOUNT], LENGTH_A[MAXCOUNT];
unsigned char DATA_A[MAXCOUNT][MAXSIZE];
unsigned int typeA_Address[MAXCOUNT];
std::string domainName_Auth[MAXCOUNT];
unsigned int TYPE_Auth[MAXCOUNT], CLASS_Auth[MAXCOUNT], TTL_Auth[MAXCOUNT], LENGTH_Auth[MAXCOUNT];
unsigned char DATA_Auth[MAXCOUNT][MAXSIZE];
std::string domainName_Add[MAXCOUNT];
unsigned int TYPE_Add[MAXCOUNT], CLASS_Add[MAXCOUNT], TTL_Add[MAXCOUNT], LENGTH_Add[MAXCOUNT];
unsigned char DATA_Add[MAXCOUNT][MAXSIZE];
void PrintBase16Char(unsigned char x)
{
	putchar(base16Char[x]);
}
void GetHeader_ID()
{
	unsigned char x = a[now++], y = a[now++];
	ID = (unsigned int)x << 8 | y;
}
void GetHeader_CODE()
{
	unsigned char x = a[now++], y = a[now++];
	QR = (x >> 7) & 1;
	OPCODE = (x >> 3) & 15;
	if (QR)
	{
		AA = (x >> 2) & 1;
	}
	TC = (x >> 1) & 1;
	RD = x & 1;
	if (QR)
		RA = (y >> 7) & 1;
	if (QR)
		RCODE = y & 15;
}
void GetHeader_QDCOUNT()
{
	unsigned char x = a[now++], y = a[now++];
	QDCOUNT = (unsigned int)x << 8 | y;
}
void GetHeader_ANCOUNT()
{
	unsigned char x = a[now++], y = a[now++];
	ANCOUNT = (unsigned int)x << 8 | y;
}
void GetHeader_NSCOUNT()
{
	unsigned char x = a[now++], y = a[now++];
	NSCOUNT = (unsigned int)x << 8 | y;
}
void GetHeader_ARCOUNT()
{
	unsigned char x = a[now++], y = a[now++];
	ARCOUNT = (unsigned int)x << 8 | y;
}
std::string GetDomainName()
{
	unsigned char x = a[now++];
	std::string domainName = "";
	if ((x >> 7) & 1)
	{
		unsigned char y = a[now++];
		domainName = domainNameMap[((x & 63) << 8) | y];
	}
	else
	{
		bool isFirst = true;
		now--;
		int startPos = now;
		while (1)
		{
			unsigned char labelCount = a[now++];
			if (labelCount == 0)
				break;
			if (isFirst)
				isFirst = false;
			else
				domainName += ".";
			for (int i = 1; i <= labelCount; i++)
			{
				domainName += a[now++];
			}
		}
		domainNameMap[startPos] = domainName;
	}
	return domainName;
}
void GetQuestion_QNAME(int id)
{
	domainName_Q[id] = GetDomainName();
}
void GetQuestion_QTYPE(int id)
{
	unsigned char x = a[now++], y = a[now++];
	QTYPE[id] = (unsigned int)x << 8 | y;
}
void GetQuestion_QCLASS(int id)
{
	unsigned char x = a[now++], y = a[now++];
	QCLASS[id] = (unsigned int)x << 8 | y;
}
void GetRR_NAME(std::string &str)
{
	str = GetDomainName();
}
void GetRR_TYPE(unsigned int &value)
{
	unsigned char x = a[now++], y = a[now++];
	value = (unsigned int)x << 8 | y;
}
void GetRR_CLASS(unsigned int &value)
{
	unsigned char x = a[now++], y = a[now++];
	value = (unsigned int)x << 8 | y;
}
void GetRR_TTL(unsigned int &value)
{
	unsigned char x = a[now++], y = a[now++], z = a[now++], w = a[now++];
	value = (unsigned int)x << 24 | (unsigned int)y << 16 | (unsigned int)z << 8 | w;
}
void GetRR_RDLENGTH(unsigned int &value)
{
	unsigned char x = a[now++], y = a[now++];
	value = (unsigned int)x << 8 | y;
}
void GetRR_RDATA(unsigned char *dataPos, unsigned int &length)
{
	memcpy(dataPos, a + now, length);
	now += length;
}
void GetRR_RDATA_TypeA(int id, unsigned int &value)
{
	unsigned char x = DATA_A[id][0], y = DATA_A[id][1], z = DATA_A[id][2], w = DATA_A[id][3];
	value = (unsigned int)x << 24 | (unsigned int)y << 16 | (unsigned int)z << 8 | w;
}
void PrintHeader_ID()
{
	printf("	DNS ID: 0x");
	PrintBase16Char((ID >> 12) & 15);
	PrintBase16Char((ID >> 8) & 15);
	PrintBase16Char((ID >> 4) & 15);
	PrintBase16Char(ID & 15);
	printf("\n");
}
void PrintHeader_QR()
{
	printf("	QR: ");
	switch (QR)
	{
	case 0:
		puts("query");
		break;
	case 1:
		puts("response");
		break;
	}
}
void PrintHeader_OPCODE()
{
	printf("	OPCODE: ");
	switch (OPCODE)
	{
	case 0:
		puts("QUERY");
		break;
	case 1:
		puts("IQUERY");
		break;
	case 2:
		puts("STATUS");
		break;
	default:
		puts("???");
	}
}
void PrintHeader_AA()
{
	if (QR)
	{
		printf("	Authoritative Answer: ");
		if (AA)
			puts("Yes");
		else
			puts("No");
	}
}
void PrintHeader_TC()
{
	printf("	TrunCated: ");
	if (TC)
		puts("Yes");
	else
		puts("No");
}
void PrintHeader_RD()
{
	printf("	Recursion Desired: ");
	if (RD)
		puts("Yes");
	else
		puts("No");
}
void PrintHeader_RA()
{
	if (QR)
	{
		printf("	Recursion Available: ");
		if (RA)
			puts("Yes");
		else
			puts("No");
	}
}
void PrintHeader_RCODE()
{
	if (QR)
	{
		printf("	Response code: ");
		switch (RCODE)
		{
		case 0:
			puts("No error condition");
			break;
		case 1:
			puts("Format error");
			break;
		case 2:
			puts("Server failure");
			break;
		case 3:
			puts("Name Error");
			break;
		case 4:
			puts("Not Implemented");
			break;
		case 5:
			puts("Refused");
			break;
		default:
			puts("???");
			break;
		}
	}
}
void PrintHeader_COUNT()
{
	printf("	Questions: %u\n", QDCOUNT);
	printf("	Answer RRs: %u\n", ANCOUNT);
	printf("	Authority RRs: %u\n", NSCOUNT);
	printf("	Additional RRs: %u\n", ARCOUNT);
}
void PrintQuestion_QNAME(int id)
{
	printf("	Domain Name: %s\n", domainName_Q[id].c_str());
}
void PrintTYPE(int value, bool isQTYPE)
{
	switch (value)
	{
	case 1:
		puts("A");
		break;
	case 2:
		puts("NS");
		break;
	case 3:
		puts("MD");
		break;
	case 4:
		puts("MF");
		break;
	case 5:
		puts("CNAME");
		break;
	case 6:
		puts("SOA");
		break;
	case 7:
		puts("MB");
		break;
	case 8:
		puts("MG");
		break;
	case 9:
		puts("MR");
		break;
	case 10:
		puts("NULL");
		break;
	case 11:
		puts("WKS");
		break;
	case 12:
		puts("PTR");
		break;
	case 13:
		puts("HINFO");
		break;
	case 14:
		puts("MINFO");
		break;
	case 15:
		puts("MX");
		break;
	case 16:
		puts("TXT");
		break;
	default:
		if (isQTYPE)
		{
			switch (value)
			{
			case 252:
				puts("AXFR");
				break;
			case 253:
				puts("MAILB");
				break;
			case 254:
				puts("MAILA");
				break;
			case 255:
				puts("*");
				break;
			default:
				puts("???");
			}
		}
		else
		{
			puts("???");
		}
	}
}
void PrintQuestion_QTYPE(int id)
{
	printf("	Query Type: ");
	PrintTYPE(QTYPE[id], true);
}
void PrintCLASS(int value, bool isQCLASS)
{
	switch (value)
	{
	case 1:
		puts("IN");
		break;
	case 2:
		puts("CS");
		break;
	case 3:
		puts("CH");
		break;
	case 4:
		puts("HS");
		break;
	default:
		if (isQCLASS)
		{
			switch (value)
			{
			case 5:
				puts("*");
				break;
			default:
				puts("???");
			}
		}
		else
		{
			puts("???");
		}
	}
}
void PrintQuestion_QCLASS(int id)
{
	printf("	Query Class: ");
	PrintCLASS(QCLASS[id], true);
}
void PrintRR_NAME(std::string name)
{
	printf("	Domain Name: %s\n", name.c_str());
}
void PrintRR_TYPE(unsigned int value)
{
	printf("	Data Type: ");
	PrintTYPE(value, false);
}
void PrintRR_CLASS(unsigned int value)
{
	printf("	Data Class: ");
	PrintCLASS(value, false);
}
void printRR_TTL(unsigned int value)
{
	printf("	Time to live: %u second(s)\n", value);
}
void printRR_RDLENGTH(unsigned int value)
{
	printf("	Data Length: %u\n", value);
}
void printTypeA_Address(unsigned int value)
{
	printf("	Address: %u.%u.%u.%u\n", (value >> 24) & 255, (value >> 16) & 255, (value >> 8) & 255, value & 255);
}
void PrintResult()
{
	puts("Header:");
	PrintHeader_ID();
	PrintHeader_QR();
	PrintHeader_OPCODE();
	PrintHeader_AA();
	PrintHeader_TC();
	PrintHeader_RD();
	PrintHeader_RA();
	PrintHeader_RCODE();
	PrintHeader_COUNT();

	if (QDCOUNT)
		puts("Question:");
	for (int i = 0; i < QDCOUNT; i++)
	{
		PrintQuestion_QNAME(i);
		PrintQuestion_QTYPE(i);
		PrintQuestion_QCLASS(i);
	}

	if (ANCOUNT)
		puts("Answer:");
	for (int i = 0; i < ANCOUNT; i++)
	{
		PrintRR_NAME(domainName_A[i]);
		PrintRR_TYPE(TYPE_A[i]);
		PrintRR_CLASS(CLASS_A[i]);
		printRR_TTL(TTL_A[i]);
		printRR_RDLENGTH(LENGTH_A[i]);
		switch (TYPE_A[i])
		{
		case 1:
			printTypeA_Address(typeA_Address[i]);
			break;
		default:
			puts("[Failed to show data] Only records of Type A are supported!\n");
		}
	}
}
int main(int argc, char *argv[])
{
	FILE *file = fopen(argv[1], "rb");
	if (file == NULL)
	{
		fprintf(stderr, "Can't read the file!\n");
		return -1;
	}
	fread(a, sizeof(unsigned char), MAXSIZE, file);

	GetHeader_ID();
	GetHeader_CODE();
	GetHeader_QDCOUNT();
	GetHeader_ANCOUNT();
	GetHeader_NSCOUNT();
	GetHeader_ARCOUNT();

	for (int i = 0; i < QDCOUNT; i++)
	{
		GetQuestion_QNAME(i);
		GetQuestion_QTYPE(i);
		GetQuestion_QCLASS(i);
	}

	for (int i = 0; i < ANCOUNT; i++)
	{
		GetRR_NAME(domainName_A[i]);
		GetRR_TYPE(TYPE_A[i]);
		GetRR_CLASS(CLASS_A[i]);
		GetRR_TTL(TTL_A[i]);
		GetRR_RDLENGTH(LENGTH_A[i]);
		GetRR_RDATA(DATA_A[i], LENGTH_A[i]);
		switch (TYPE_A[i])
		{
		case 1:
			GetRR_RDATA_TypeA(i, typeA_Address[i]);
			break;
		}
	}

	for (int i = 0; i < NSCOUNT; i++)
	{
		GetRR_NAME(domainName_Auth[i]);
		GetRR_TYPE(TYPE_Auth[i]);
		GetRR_CLASS(CLASS_Auth[i]);
		GetRR_TTL(TTL_Auth[i]);
		GetRR_RDLENGTH(LENGTH_Auth[i]);
		GetRR_RDATA(DATA_Auth[i], LENGTH_Auth[i]);
	}

	for (int i = 0; i < ARCOUNT; i++)
	{
		GetRR_NAME(domainName_Add[i]);
		GetRR_TYPE(TYPE_Add[i]);
		GetRR_CLASS(CLASS_Add[i]);
		GetRR_TTL(TTL_Add[i]);
		GetRR_RDLENGTH(LENGTH_Add[i]);
		GetRR_RDATA(DATA_Add[i], LENGTH_Add[i]);
	}
	
	PrintResult();
	return 0;
}