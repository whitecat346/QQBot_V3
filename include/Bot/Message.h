#pragma once

#include <string>
#include <map>

namespace Bot
{
	// API Request form
	struct Request
	{
		std::string _action;
		std::map<std::string, std::string> _params;
		std::string _echo;

		
	};

	// Message response
	struct Response
	{
		const std::string _status{};
		const std::string _retcode{};
		const int _data{ NULL };
		std::string _echo{};
	};

	struct Report
	{
		const long _time{ NULL };
		const long _self_id{ NULL };
		const std::string _post_type{};
	};

}

template<typename T>
struct _ParamsStr
{
	std::string _id;
	T _value;

	_ParamsStr* _after = nullptr;
	_ParamsStr* _next = nullptr;
};

class Pramas
{
public:
	Pramas() noexcept;

	template<typename T>
	void append(const std::string _id, T _value);
	void clear();

	void at(const std::string _id);
	void at(const unsigned int _Pos);

	void erase(const std::string _id);
	void erase(const unsigned int _Pos);
	void erase(const unsigned int _Pos, const unsigned int _Size);

	void getJSON();

	
};
