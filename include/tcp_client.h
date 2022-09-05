#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <functional>
#include "callback.h"

using namespace boost::asio::ip;

class tcp_client
{
public:
	tcp_client(boost::asio::io_context& _io_context)
		: m_io_context(_io_context), m_socket(_io_context), m_callback()
	{

	}
	void start(const std::string host, const int port)
	{
		tcp::endpoint endpoint(address::from_string(host), port);
		m_socket.async_connect(endpoint, 
			boost::bind(&tcp_client::handle_connect, this,
				boost::asio::placeholders::error));
	}

	void handle_connect(const boost::system::error_code& error)
	{
		if (!error) {
			std::cout << "connect suc" << std::endl;
			m_callback.notify(callback::connect_type);
		}
	}

	void do_read()
	{
		m_readBuf.clear();
		m_readBuf.resize(1024);
		boost::asio::async_read(m_socket, boost::asio::buffer(m_readBuf), boost::asio::transfer_at_least(5),
			boost::bind(&tcp_client::handle_read, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}

	void handle_read(const boost::system::error_code& error, size_t len)
	{
		if (!error)
		{
			std::cout << "m_readBuf:" << m_readBuf << std::endl;
			m_callback.notify(callback::read_type, m_readBuf);
		}
	}

	void do_write(const std::string data)
	{
		m_writeBuf = data;
		boost::asio::async_write(m_socket, boost::asio::buffer(m_writeBuf),
			boost::bind(&tcp_client::handle_write, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}

	void handle_write(const boost::system::error_code& error, size_t len)
	{
		if (!error)
		{

		}
	}

	template<class F>
	void bind_connect(F&& func)
	{
		m_callback.bind(callback::connect_type,
			callback_type<>(std::forward<F>(func)));
	}

	template<class F>
	void bind_read(F&& func)
	{
		m_callback.bind(callback::read_type,
			callback_type<std::string>(std::forward<F>(func)));
	}

private:
	boost::asio::io_context& m_io_context;
	tcp::socket m_socket;
	callback m_callback;
	std::string m_readBuf;
	std::string m_writeBuf;
};

#endif