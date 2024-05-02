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
		const std::string _echo{};
	};

	struct Report
	{
		const long _time{ NULL };
		const long _self_id{ NULL };
		const std::string _post_type{};
	};

	namespace Event
	{
		
	}
}
