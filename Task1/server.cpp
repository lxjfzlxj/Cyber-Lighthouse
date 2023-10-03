#include <iostream>
#include <boost/asio.hpp>
using namespace std;
using namespace boost;
using namespace asio;
using namespace asio::ip;
const char udpString[10] = "UDPUDP";
bool udpok;
int port;
void InputRequestAndPort() {
	char Y_N;
	printf("allow to receive udp package?(Y/N) ");
	scanf("%c",Y_N);
	if(Y_N=='Y') udpok=true;
	else udpok=false;
	printf("port: ");
	scanf("%d",&port);
}
int main()
{
	InputRequestAndPort();
	try
	{
		io_context ioContext;												  //管理各项网络任务
		tcp::acceptor tcpAcceptor(ioContext, tcp::endpoint(tcp::v4(), 8080)); //获取客户端 ip+port
		tcp::socket tcpSocket(ioContext);
		tcpAcceptor.accept(tcpSocket); //接受客户端连接
		printf("client IP:%s\n", tcpSocket.remote_endpoint().address().to_string().c_str());
		bool useUDP = false;
		while (1)
		{
			char data[100] = {0};
			// buffer(...) 管理传入的内存，作为缓冲区，所有收发数据都要用这玩意
			tcpSocket.receive(buffer(data)); // receive() 接受客户端发送的数据
			puts(data);
			if (strcmp(data, udpString) == 0)
			{
				if(udpok) {
					useUDP = true;
					break;
				}
			}
			tcpSocket.send(buffer(data)); // send() 向客户端发送数据
		}
		if (useUDP)
		{
			io_context ioContext;
			udp::socket udpSocket(ioContext, udp::endpoint(udp::v4(), 8080));
			while (1)
			{
				char data[100] = {0};
				udp::endpoint datafrom;
				udpSocket.receive_from(buffer(data), datafrom);
				udpSocket.send_to(buffer(data), datafrom);
			}
		}
	}
	catch (std::exception &e)
	{
		fprintf(stderr, "Exception: %s\n", e.what());
	}

	return 0;
}