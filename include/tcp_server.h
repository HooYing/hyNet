#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <functional>
#include "tcp_session.h"
#include "callback.h"

using namespace boost::asio::ip;

class tcp_server
{
public:
	tcp_server(boost::asio::io_context& _io_context)
		: m_io_context(_io_context), m_acceptor(_io_context), m_callback()
	{
		
	}

	void start(const int port)
	{	
		tcp::endpoint endpoint(tcp::v4(), port);
		m_acceptor.open(endpoint.protocol());
		m_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
		m_acceptor.bind(endpoint);
		m_acceptor.listen();
		do_accept();
	}

	void do_accept()
	{
		tcp_session::Ptr session = tcp_session::create(m_io_context, m_callback);
		m_acceptor.async_accept(session->socket(),
			boost::bind(&tcp_server::handle_accept, this, session,
				boost::asio::placeholders::error));
	}

	void handle_accept(tcp_session::Ptr session,
		const boost::system::error_code& error)
	{
		if (!error) {
			std::cout << "accept suc" << std::endl;
			session->start();
			do_accept();
		}
	}

	template<class F>
	void bind_accept(F&& func)
	{
		m_callback.bind(callback::accept_type,
			callback_type<tcp_session::Ptr&>(std::forward<F>(func)));
	}

	template<class F>
	void bind_read(F&& func)
	{
		m_callback.bind(callback::read_type,
			callback_type<tcp_session::Ptr&, std::string>(std::forward<F>(func)));
	}
	
private:
	boost::asio::io_context& m_io_context;
	tcp::acceptor m_acceptor;
	callback m_callback;
};

#endif