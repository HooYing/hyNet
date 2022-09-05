#ifndef CALLBACK_H
#define CALLBACK_H

#include <functional>
#include <memory>
#include <array>
#include <iostream>

// 因为callback_type是类模板，所以搞个基类
class Icallback_type
{
public:
	virtual ~Icallback_type() noexcept {}
};

template<class... Args>
class callback_type : public Icallback_type
{
public:
	using func_type = std::function<void(Args...)>;

	explicit callback_type(const callback_type<Args...>& other) : m_fn(other.m_fn) {}
	explicit callback_type(callback_type<Args...>&& other) : m_fn(std::move(other.m_fn)) {}

	template<class F>
	explicit callback_type(F&& f)
	{
		this->m_fn = func_type(std::forward<F>(f));
	}

	void operator () (Args&&... args)
	{
		if (m_fn)
			m_fn(std::forward<Args>(args)...);
	}

private:
	func_type m_fn;
};

class callback
{
public:
	typedef enum
	{
		accept_type = 0,
		connect_type,
		read_type,
		write_type,
		NUM
	} EventType;

	template<class T>
	void bind(EventType type, T&& ct)
	{
		m_callbackArray[type] = 
			std::unique_ptr<Icallback_type>(new T(std::forward<T>(ct)));
	}

	template<class... Args>
	void notify(EventType e, Args&&... args)
	{
		using _callback_type = callback_type<Args...>;
		// 这里用dynamic_cast返回了一个空指针
		_callback_type* callback_ptr = static_cast<_callback_type*>(m_callbackArray[e].get());
		if (callback_ptr) 
		{
			(*callback_ptr)(std::forward<Args>(args)...);
		}
	}

	callback(){}

private:
	std::array<std::unique_ptr<Icallback_type>, EventType::NUM> m_callbackArray;
};

#endif