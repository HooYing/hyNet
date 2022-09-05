#include <iostream>
#include "tcp_client.h"
int main()
{
	boost::asio::io_context io;
	tcp_client client(io);
	client.bind_connect([&]() {
		client.do_write("nimenhao");
		client.do_read();
		});
	client.bind_read([&](std::string data) {
		std::cout << "data:" << data << std::endl;
		client.do_write(data);
		});
	client.start("127.0.0.1", 9123);
	io.run();
}