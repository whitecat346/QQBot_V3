#pragma once

#include "../Internet/hv/WebSocketClient.h"
#include "../Methould/Default.h"
#include "Message.h"
#include <map>

class RequestMsg
{
public:
	explicit RequestMsg(const std::string& _action) noexcept;

	void AddParams(const std::string _id, const std::string _value);
	void AddEcho(const std::string& _echo);

	void DelParams(const std::string _id);
	void DelEcho();

	void ChangeParams(const std::string _id, const std::string _newValue);
	void ChangeParams(const std::string _id, const std::string _newID, const std::string _newValue);

	void ChangeAction(const std::string& _newAction);
	void ChangeEcho(const std::string& _newEcho);

	std::string getJSONMsg();
private:

	// Raw Data
	Bot::Request _rqsMsg;
};


class BotClient
{
public:
	BotClient() noexcept;
	explicit BotClient(const std::string __serverUrl) noexcept;

	void Send(const RequestMsg& _sendRequest);
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
	std::map<std::string, void*> _funcNotice;
	std::map<std::string, void*> _funcMessage;
	std::map<std::string, void*> _funcMeta;
	std::map<std::string, void*> _funcRequest;

	// Method
	void* responseMethod = &MethodDefault::responseMet;
	void* onMessageMethod = &MethodDefault::onMessageMet;
};
