#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <functional>
#include "tcp_session.h"

class tcp_server
{
public:
	tcp_server(boost::asio::io_context& _io_context)
		: m_io_context(_io_context)
	{
		
	}
	void start(const int port)
	{
		m_port = port;
		tcp::acceptor acceptor(m_io_context, tcp::endpoint(tcp::v4(), port));
		tcp_session::Ptr session = tcp_session::create(m_io_context);
		acceptor.async_accept(session->socket(),
			boost::bind(&tcp_server::handle_accept, this, session,
				boost::asio::placeholders::error));
	}

	void handle_accept(tcp_session::Ptr session,
		const boost::system::error_code& error)
	{
		if (!error && session) {
			session->start();
		}
		start(m_port);
	}

	template<class F>
	void bind_read(F&& fun)
	{
		std::forward<F>(fun)
	}
private:
	boost::asio::io_context& m_io_context;
	int m_port;
};

#endif