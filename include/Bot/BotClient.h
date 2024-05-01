#pragma once

#include "../Internet/hv/WebSocketClient.h"

namespace Bot
{
	// API Request form
	struct Request
	{
		const std::string _action{};
		const std::vector<std::string> _params{};
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
	explicit BotClient(const std::string serverUrl) noexcept;

	void Send();
	void Close();

private:
	std::string _serverUrl { "" };
	hv::WebSocketClient _HVwsClient;
};
