#pragma once

#include "../Internet/hv/WebSocketClient.h"
#include "../Methould/Default.h"
#include "Message.h"
#include <map>



class BotClient
{
public:
	BotClient() noexcept;
	explicit BotClient(const std::string __serverUrl) noexcept;

	void Send(const Bot::Request& _sendRequest);
	void Close();

	void AddMethoud(const std::string _command, const void* _functionPtr);
	void SetOnOpenMethoud(const void* _functionPtr);
	void SetResponseMethod(const void* _functionPtr);

private:

	// WebSocket
	std::string _serverUrl { "ws://127.0.0.1:3001" };
	hv::WebSocketClient _HVwsClient;
	bool _isConnect = false;
	reconn_setting_t reconn;

	// user command function
	std::map<std::string, void*> _funcMap;

	// Method
	void* responseMethod = &MethodDefault::responseMet;
	void* onMessageMethod = &MethodDefault::onMessageMet;
};
