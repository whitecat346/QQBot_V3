#pragma once

#include "../Internet/hv/WebSocketClient.h"
#include "../Methould/Default.h"
#include  "../json/simdjson.h"
#include "Message.h"
#include <map>

class RequestMsg
{
public:
	explicit RequestMsg(const std::string& _action) noexcept;

	void AddParams(const std::string _id, const std::string _value) noexcept;
	void AddEcho(const std::string& _echo) noexcept;

	void DelParams(const std::string _id) noexcept;
	void DelEcho();

	void ChangeParams(const std::string _id, const std::string _newValue) noexcept;
	void ChangeParams(const std::string _id, const std::string _newID, const std::string _newValue) noexcept;

	void ChangeAction(const std::string& _newAction) noexcept;
	void ChangeEcho(const std::string& _newEcho) noexcept;

	std::string getJSONMsg() noexcept;
private:

	// Raw Data
	Bot::Request _rqsMsg;
};


class BotClient
{
public:
	BotClient() noexcept;
	explicit BotClient(const std::string __serverUrl) noexcept;

	void Send(RequestMsg& _sendRequestMsg);
	void Close();

	void AddMethoud(const std::string _command, void(* _functionPtr));
	void SetOnOpenMethoud(void(* _functionPtr));
	void SetResponseMethod(void(* _functionPtr) (Bot::Response& _response));

private:
	// WebSocket
	std::string _serverUrl { "ws://127.0.0.1:3001" };
	hv::WebSocketClient _HVwsClient;
	reconn_setting_t reconn;

	// user command function
	std::map<std::string, void*> _funcNotice;
	std::map<std::string, void*> _funcMessage;
	std::map<std::string, void*> _funcMeta;
	std::map<std::string, void*> _funcRequest;

	// Method
	// User Event
	void(*responseMethod) (Bot::Response& _res) = &MethodDefault::responseEventMet;
	void(*metaEventMethod) (std::string& _msg) = &MethodDefault::metaEventMet;
	void(*noticeEventMethod) (std::string& _msg) = &MethodDefault::noticeEventMet;
	void(*messageEventMethod) (std::string& _msg) = &MethodDefault::messageEventMet;
	void(*requestEventMethod) (std::string& _msg) = &MethodDefault::requestEventMet;

	// WebSocket Server Event
	void onMessageMethod(std::string _msg);
	void(*onCloseMethod) = &MethodDefault::onCloseMet;
	void(*onOpenMethod) = &MethodDefault::onOpenMet;
};
