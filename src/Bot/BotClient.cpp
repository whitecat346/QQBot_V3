#include "../../include/Internet/hv/WebSocketClient.h"
#include "../../include/Bot/BotClient.h"
#include "../../include/Bot/Message.h"
#include "../../include/json/simdjson.h"
#include "../json/json.hpp"

#include <string>
#include <algorithm>
#include <any>

BotClient::BotClient()
{
	// set ping interval
	_HVwsClient.setPingInterval(10000);

	// reconnect time 1 2 4 8 10 10
	reconn_setting_init(&reconn);
	reconn.min_delay = 1000;
	reconn.max_delay = 10000;
	reconn.delay_policy = 2;
	_HVwsClient.setReconnect(&reconn);


}

BotClient::BotClient(const std::string serverUrl) : _serverUrl(serverUrl)
{
	// set ping interval
	_HVwsClient.setPingInterval(10000);

	// reconnect time 1 2 4 8 10 10
	reconn_setting_init(&reconn);
	reconn.min_delay = 1000;
	reconn.max_delay = 10000;
	reconn.delay_policy = 2;
	_HVwsClient.setReconnect(&reconn);

	// try to connect on server
	_HVwsClient.open(serverUrl.c_str());
}

void BotClient::Send(RequestMsg& _sendRequest)
{
	try
	{
		// try connect
		if (_HVwsClient.isConnected())
			_HVwsClient.send(_sendRequest.getJSONMsg());
		else
			throw 410;
	}
	catch (int)
	{
		std::cerr << "Server is not connect!\n";
	}
}

void BotClient::Close() { _HVwsClient.close(); }

void BotClient::SetOnOpenMethoud(void(* _functionPtr)) { onOpenMethod = _functionPtr; }

void BotClient::SetResponseMethod(void(* _functionPtr)(Bot::Response& _response)) { responseMethod = _functionPtr; }

void BotClient::onMessageMethod(std::string _msg)
{
	// string msg to json
	simdjson::ondemand::parser parser;
	simdjson::padded_string json = simdjson::padded_string::load(_msg);
	simdjson::ondemand::document _JSONMsg = parser.iterate(json);

	if (_JSONMsg.find_field("status"))
	{
		Bot::Response _tmpRes
		{
			std::string(_JSONMsg["status"]),
			std::string(_JSONMsg["retcode"]),
			int(_JSONMsg["data"]),
			""
		};

		if (_JSONMsg.find_field("echo"))
			_tmpRes._echo = std::string(_JSONMsg["echo"]);

		responseMethod(_tmpRes);
	}

	// meta event
	if (_JSONMsg["post_type"] == "meta_event")
		metaEventMethod(_msg);
	else if (_JSONMsg["post_type"] == "message")
		messageEventMethod(_msg);
	else if (_JSONMsg["post_type"] == "notice")
		noticeEventMethod(_msg);
	else if (_JSONMsg["post_type"] == "request")
		requestEventMethod(_msg);
}

// class Request Message
RequestMsg::RequestMsg(const std::string& _action) { _rqsMsg._action = _action; }

void RequestMsg::AddParams(const std::string _id, const std::string _value) { _rqsMsg._params.insert_or_assign(_id, _value); }

void RequestMsg::AddEcho(const std::string& _echo) { _rqsMsg._echo = _echo; }

void RequestMsg::DelParams(const std::string _id) { _rqsMsg._params.erase(_id); }

void RequestMsg::DelEcho() { _rqsMsg._echo.clear(); }

void RequestMsg::ChangeParams(const std::string _id, const std::string _newValue) { _rqsMsg._params.insert_or_assign(_id, _newValue); }

void RequestMsg::ChangeParams(const std::string _id, const std::string _newID, const std::string _newValue)
{
	_rqsMsg._params.erase(_id);
	_rqsMsg._params.insert_or_assign(_newID, _newValue);
}

void RequestMsg::ChangeAction(const std::string& _newAction) { _rqsMsg._action = _newAction; }

void RequestMsg::ChangeEcho(const std::string& _newEcho) { _rqsMsg._echo = _newEcho; }

//std::string RequestMsg::getJSONMsg()
//{
//	std::string _tempJSON{ "{\"action\":\"" + _rqsMsg._action + "\",\"params\":{" };
//
//	std::for_each(_rqsMsg._params.begin(), _rqsMsg._params.end(), [&_tempJSON] (const std::string& id, const std::string& value)
//		{
//			_tempJSON.append("\"" + id + "\":");
//
//			// add params json
//			if (std::ranges::all_of(value.begin(), value.end(), [] (const char _ch)->bool { return isdigit(_ch); })
//				|| value == "true" || value == "false")
//				_tempJSON.append(value + ",");
//			else _tempJSON.append("\"" + value + "\",");
//		});
//	_tempJSON.erase(_tempJSON.end() - 1);
//
//	// add echo, if have
//	if (_rqsMsg._echo.empty()) _tempJSON.append("}}");
//	else _tempJSON.append("},\"echo\":" + _rqsMsg._echo + "\"}");
//
//	return _tempJSON;
//}

void testFun()
{
	std::string str{ R"({"action":"name","str":"hello world!")" };
	nlohmann::json j = nlohmann::json::parse(str);

	j.at("str");
}
