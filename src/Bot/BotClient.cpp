#include "../../include/Internet/hv/WebSocketClient.h"
#include "../../include/Bot/BotClient.h"
#include "../throwProcessing.hpp"
#include "../../include/Bot/Message.h"
#include <string>
#include <algorithm>



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
	_isConnect = true;
}

void BotClient::Send(const RequestMsg& _sendRequest)
{
	std::string _tmpMsgJSON;
}

RequestMsg::RequestMsg(const std::string& _action)
{
	_rqsMsg._action = _action;
}

void RequestMsg::AddParams(const std::string _id, const std::string _value)
{
	_rqsMsg._params.insert_or_assign(_id, _value);
}

void RequestMsg::AddEcho(const std::string& _echo)
{
	_rqsMsg._echo = _echo;
}

void RequestMsg::DelParams(const std::string _id)
{
	_rqsMsg._params.erase(_id);
}

void RequestMsg::DelEcho()
{
	_rqsMsg._echo.clear();
}

void RequestMsg::ChangeParams(const std::string _id, const std::string _newValue)
{
	_rqsMsg._params.insert_or_assign(_id, _newValue);
}

void RequestMsg::ChangeParams(const std::string _id, const std::string _newID, const std::string _newValue)
{
}

void RequestMsg::ChangeAction(const std::string& _newAction)
{
	_rqsMsg._action = _newAction;
}

void RequestMsg::ChangeEcho(const std::string& _newEcho)
{
	_rqsMsg._echo = _newEcho;
}

std::string RequestMsg::getJSONMsg()
{
	std::string _tempJSON{ "{\"action\":\"" + _rqsMsg._action + "\",\"params\":{" };

	std::for_each(_rqsMsg._params.begin(), _rqsMsg._params.end(), [&_tempJSON] (const std::string& id, const std::string& value)
		{
			_tempJSON.append("\"" + id + "\":");

			// add params json
			if (std::ranges::all_of(value.begin(), value.end(), [] (const char _ch)->bool { return isdigit(_ch); })
				|| value == "true" || value == "false")
				_tempJSON.append(value + ",");
			else _tempJSON.append("\"" + value + "\",");
		});
	_tempJSON.erase(_tempJSON.end() - 1);

	if (_rqsMsg._echo.empty()) _tempJSON.append("}}");
	else _tempJSON.append("},\"echo\":" + _rqsMsg._echo + "\"}");

	return _tempJSON;
}
