namespace GENERATOR
{
#define MAXSIZE 1000
	struct dataPackage
	{
		unsigned char a[MAXSIZE];
		int len;
	};
	dataPackage Main(const char *type, const char *name, bool canRD);
}