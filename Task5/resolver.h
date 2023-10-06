namespace RESOLVER{
	struct ResolveResult{
		int signal;
		std::string name;
		unsigned int address;
	};
	void Main(unsigned char *data,int dataSize);
}