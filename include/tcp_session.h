#ifndef TCP_SESSION_H
#define TCP_SESSION_H

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind/bind.hpp>
#include "callback.h"

using namespace boost::asio::ip;

class tcp_session
	: public boost::enable_shared_from_this<tcp_session>
{
public:
	typedef boost::shared_ptr<tcp_session> Ptr;
	
	static Ptr create(boost::asio::io_context& _io_context, callback& _callback)
	{
		return Ptr(new tcp_session(_io_context, _callback));
	}

	tcp::socket& socket()
	{
		return m_socket;
	}

	void start()
	{
		m_callback.notify(callback::accept_type, shared_from_this());
		// std::cout << shared_from_this().use_count() << std::endl; //4
	}

	void do_read()
	{
		m_readBuf.clear();
		m_readBuf.resize(1024);
		boost::asio::async_read(m_socket, boost::asio::buffer(m_readBuf), boost::asio::transfer_at_least(5),
					boost::bind(&tcp_session::handle_read, shared_from_this(),
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
	}

	void do_write(const std::string data)
	{
		m_writeBuf = data;
		boost::asio::async_write(m_socket, boost::asio::buffer(m_writeBuf),
			boost::bind(&tcp_session::handle_write, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}

	void handle_read(const boost::system::error_code& error, size_t len)
	{
		if (!error)
		{
			std::cout << "m_readBuf:" << m_readBuf << std::endl;
			m_callback.notify(callback::read_type, shared_from_this(), m_readBuf);
			// std::cout << shared_from_this().use_count() << std::endl; //2
		}
	}

	void handle_write(const boost::system::error_code& error, size_t len)
	{
		if (!error)
		{

		}
	}
	

private:
	tcp_session(boost::asio::io_context& _io_context, callback& _callback)
		: m_socket(_io_context), m_callback(_callback)
	{
		
	}
	tcp::socket m_socket;
	callback& m_callback;
	std::string m_readBuf;
	std::string m_writeBuf;
};

#endif