#pragma once

#include "../Internet/hv/WebSocketClient.h"
#include "../Methould/Default.h"
#include "Message.h"

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
	std::string _serverUrl { "ws://127.0.0.1:3001" };
	hv::WebSocketClient _HVwsClient;
	bool _isConnect = false;



	// Method
	void* responseMethod = &MethodDefault::responseMet;
	void* onMessageMethod = &MethodDefault::onMessageMet;
};
