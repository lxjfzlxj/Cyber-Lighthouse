namespace CLIENT
{
#define MAXSIZE 1000
	struct dataPackage
	{
		unsigned char a[MAXSIZE];
		int len;
	};
	dataPackage Main(const char *protocol, const char *address, int port, unsigned char *sendData, int dataSize);
}