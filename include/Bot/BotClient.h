#pragma once

#include "../Internet/hv/WebSocketClient.h"

namespace Bot
{
	// API Request form
	struct RequestMsg
	{
		std::string _action{};
		std::vector<std::string> _params{};
		std::string _echo{};
	};

	struct Response
	{
		std::string _status{};
		std::string _retcode{};
		int _data{ NULL };
		std::string _echo{};
	};

	struct Report
	{
		long _time{ NULL };
		long _self_id{ NULL };
		std::string _post_type{};
	};
}

class BotClient
{
public:
	BotClient() noexcept;
	explicit BotClient(const std::string serverUrl) noexcept;

	void Close(const int _outCode = 0);
	void Send();

private:
	std::string _serverUrl { "" };
	hv::WebSocketClient _HVwsClient;
};
