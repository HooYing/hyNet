#ifndef TCP_SESSION_H
#define TCP_SESSION_H

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace boost::asio::ip;

class tcp_session
	: public boost::enable_shared_from_this<tcp_session>
{
public:
	typedef boost::shared_ptr<tcp_session> Ptr;
	
	static Ptr create(boost::asio::io_context& _io_context)
	{
		return Ptr(new tcp_session(_io_context));
	}

	tcp::socket& socket()
	{
		return m_socket;
	}

	void start()
	{

	}
	
private:
	tcp_session(boost::asio::io_context& _io_context)
		: m_socket(_io_context)
	{

	}
	tcp::socket m_socket;
};

#endif