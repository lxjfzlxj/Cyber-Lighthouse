#include <bits/stdc++.h>
#include "resolver.h"
namespace RESOLVER
{
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
	std::string GetDomainName(int pointer)
	{
		std::string domainName = "";
		bool isFirst = true;
		while (1)
		{
			unsigned char x = a[pointer++];
			if (!x)
				break;
			if ((x >> 7) & 1)
			{
				unsigned char y = a[pointer++];
				if (pointer > now)
					now = pointer;
				pointer = ((x & 63) << 8) | y;
			}
			else
			{
				if (isFirst)
					isFirst = false;
				else
					domainName += ".";
				for (int i = 1; i <= x; i++)
					domainName += a[pointer++];
			}
		}
		if (pointer > now)
			now = pointer;
		return domainName;
	}
	void GetQuestion_QNAME(int id)
	{
		domainName_Q[id] = GetDomainName(now);
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
	void Print_TYPE(int value, bool isQTYPE)
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
		Print_TYPE(QTYPE[id], true);
	}
	void Print_CLASS(int value, bool isQCLASS)
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
		Print_CLASS(QCLASS[id], true);
	}
	struct RR
	{
		std::string NAME;
		unsigned int TYPE;
		unsigned int CLASS;
		unsigned int TTL;
		unsigned int RDLENGTH;
		int DATApos;
		unsigned int A_DATA;
		std::string CNAME_DATA;
		std::string NS_DATA;
		void GetNAME()
		{
			NAME = GetDomainName(now);
		}
		void GetTYPE()
		{
			unsigned char x = a[now++], y = a[now++];
			TYPE = (unsigned int)x << 8 | y;
		}
		void GetCLASS()
		{
			unsigned char x = a[now++], y = a[now++];
			CLASS = (unsigned int)x << 8 | y;
		}
		void GetTTL()
		{
			unsigned char x = a[now++], y = a[now++], z = a[now++], w = a[now++];
			TTL = (unsigned int)x << 24 | (unsigned int)y << 16 | (unsigned int)z << 8 | w;
		}
		void GetRDLENGTH()
		{
			unsigned char x = a[now++], y = a[now++];
			RDLENGTH = (unsigned int)x << 8 | y;
		}
		void GetRDATA()
		{
			DATApos = now;
			now += RDLENGTH;
		}
		void GetRDATA_TypeA()
		{
			unsigned char x = a[DATApos], y = a[DATApos + 1], z = a[DATApos + 2], w = a[DATApos + 3];
			A_DATA = (unsigned int)x << 24 | (unsigned int)y << 16 | (unsigned int)z << 8 | w;
		}
		void GetRDATA_TypeCNAME()
		{
			CNAME_DATA = GetDomainName(DATApos);
		}
		void GetRDATA_TypeNS()
		{
			NS_DATA = GetDomainName(DATApos);
		}
		void GetAll()
		{
			GetNAME();
			GetTYPE();
			GetCLASS();
			GetTTL();
			GetRDLENGTH();
			GetRDATA();
			switch (TYPE)
			{
			case 1:
				GetRDATA_TypeA();
				break;
			case 5:
				GetRDATA_TypeCNAME();
				break;
			case 2:
				GetRDATA_TypeNS();
				break;
			}
		}
		void PrintNAME()
		{
			printf("	Domain Name: %s\n", NAME.c_str());
		}
		void PrintTYPE()
		{
			printf("	Data Type: ");
			Print_TYPE(TYPE, false);
		}
		void PrintCLASS()
		{
			printf("	Data Class: ");
			Print_CLASS(CLASS, false);
		}
		void printTTL()
		{
			printf("	Time to live: %u second(s)\n", TTL);
		}
		void printRDLENGTH()
		{
			printf("	Data Length: %u\n", RDLENGTH);
		}
		void printRDATA_TYPEA()
		{
			printf("	Address: %u.%u.%u.%u\n", (A_DATA >> 24) & 255, (A_DATA >> 16) & 255, (A_DATA >> 8) & 255, A_DATA & 255);
		}
		void printRDATA_TYPECNAME()
		{
			printf("	C Name: %s\n", CNAME_DATA.c_str());
		}
		void printRDATA_TYPENS()
		{
			printf("	NS Name: %s\n", NS_DATA.c_str());
		}
		void Print()
		{
			PrintNAME();
			PrintTYPE();
			PrintCLASS();
			printTTL();
			printRDLENGTH();
			switch (TYPE)
			{
			case 1:
				printRDATA_TYPEA();
				break;
			case 5:
				printRDATA_TYPECNAME();
				break;
			case 2:
				printRDATA_TYPENS();
				break;
			default:
				puts("	[Failed to show data] Only records of Type A, CNAME are supported!");
			}
		}
	} Answer[MAXCOUNT], Authority[MAXCOUNT], Additional[MAXCOUNT];
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
		printf("\n");

		if (QDCOUNT)
		{
			puts("Question:");
			for (int i = 0; i < QDCOUNT; i++)
			{
				PrintQuestion_QNAME(i);
				PrintQuestion_QTYPE(i);
				PrintQuestion_QCLASS(i);
				printf("\n");
			}
		}

		if (ANCOUNT)
		{
			puts("Answer:");
			for (int i = 0; i < ANCOUNT; i++)
			{
				printf("	Answer %d:\n", i + 1);
				Answer[i].Print();
				printf("\n");
			}
		}
		if (NSCOUNT)
		{
			puts("Authority:");
			for (int i = 0; i < NSCOUNT; i++)
			{
				printf("	Authority %d:\n", i + 1);
				Authority[i].Print();
				printf("\n");
			}
		}
		if (ARCOUNT)
		{
			puts("Additional:");
			for (int i = 0; i < ARCOUNT; i++)
			{
				printf("	Additional %d:\n", i + 1);
				Additional[i].Print();
				printf("\n");
			}
		}
	}
	ResolveResult Main(unsigned char *data, int dataSize)
	{
		now = 0;
		memcpy(a, data, dataSize);

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
			Answer[i].GetAll();
		}

		for (int i = 0; i < NSCOUNT; i++)
		{
			Authority[i].GetAll();
		}

		for (int i = 0; i < ARCOUNT; i++)
		{
			Additional[i].GetAll();
		}

		// PrintResult();
		ResolveResult allResult;
		allResult.num = 0;
		allResult.name = domainName_Q[0];
		for (int i = 0; i < ANCOUNT; i++)
		{
			if (Answer[i].TYPE == 1)
			{
				allResult.result[allResult.num++] = (OneResult){Answer[i].TTL, Answer[i].A_DATA};
			}
			// else if (Answer[i].TYPE == 5)
			// {
			// 	result.signal = 1;
			// 	result.name = Answer[i].CNAME_DATA;
			// 	return result;
			// }
		}
		return allResult;
	}
}
// int main()
// {
// 	FILE *file = fopen("7.bin", "rb");
// 	unsigned char a[1000];
// 	int len = fread(a, sizeof(unsigned char), 1000, file);
// 	RESOLVER::Main(a, len);
// 	return 0;
// }