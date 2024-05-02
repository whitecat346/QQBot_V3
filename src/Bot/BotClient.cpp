#include "../../include/Internet/hv/WebSocketClient.h"
#include "../../include/Bot/BotClient.h"
#include "../throwProcessing.hpp"
#include "../../include/Bot/Message.h"
#include <string>

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

void BotClient::Send(const Bot::Request& _sendRequest)
{
	

	// params analyse
	try
	{
		if (_isConnect == false)	// analyse connect on server
			throw 1;

		if (_sendRequest._params.size() != _sendRequest._paramsID.size())	// analyse params array is standard
			throw throwProcessing::BadRequestParams();
	}
	catch (throwProcessing::BadRequestParams& brp)
	{
		brp.what();
	}
	catch (int)
	{
		std::cerr << "Not connect on server." << std::endl;
		abort();
	}

	std::string requestJSON = "{\"action\":\"";
	requestJSON.append(_sendRequest._action).append("\",\"params\":{");

	// build request json
	for ( int i = 0; i < _sendRequest._params.size(); i ++ )
	{
		requestJSON.append("\"" + _sendRequest._paramsID.at(i) + "\": ");	// params id
		if (_sendRequest._params.at(i).type() == typeid(std::string))
			requestJSON.append("\"" + std::any_cast<std::string>(_sendRequest._params.at(i)) + "\"");	// params is string
		else requestJSON.append(std::any_cast<std::string>(_sendRequest._params.at(i)));

		if (++i != _sendRequest._params.size()) requestJSON.append(",");	// not last params
	}

	// add echo (if have)
	if (!_sendRequest._echo.empty())
		requestJSON.append("},\"echo\": \"" + _sendRequest._echo + "\"}");
	else
		requestJSON.append("}}");

	_HVwsClient.send(requestJSON);
}

