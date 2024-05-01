#pragma once

#include "../Internet/hv/WebSocketClient.h"
#include <any>

namespace Bot
{
	// API Request form
	struct Request
	{
		const std::string _action{};
		const std::vector<std::any> _params{};
		const std::vector<std::string> _paramsID{};
		const std::string _echo{};
	};

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
}

class BotClient
{
public:
	BotClient() noexcept;
	explicit BotClient(const std::string __serverUrl) noexcept;

	void Send(const Bot::Request& _sendRequest);
	void Close();

private:
	std::string _serverUrl { "ws://127.0.0.1:3001" };
	hv::WebSocketClient _HVwsClient;
	bool _isConnect = false;
};
