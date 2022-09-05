#include <iostream>
#include "tcp_server.h"
int main()
{
	boost::asio::io_context io;
	tcp_server server(io);
	server.bind_accept([](tcp_session::Ptr& session) {
		std::cout << "address:" << session->socket().remote_endpoint().address() << std::endl;
		session->do_read();
		});
	server.bind_read([](tcp_session::Ptr& session, std::string data) {
		std::cout << "data:" << data << std::endl;
		session->do_write(data);
		session->do_read();
		});
	server.start(9123);
	io.run();
}