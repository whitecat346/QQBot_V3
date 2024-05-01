
#include "../include/Internet/hv/WebSocketClient.h"
#include "../include/Bot/BotClient.h"
#include "throwProcessing.hpp"

BotClient::BotClient() {};

BotClient::BotClient(const std::string serverUrl) : _serverUrl(serverUrl)
{
	_isConnect = true;
}

void BotClient::Send(const Bot::Request& _sendRequest)
{
	std::string requestJSON = "{\"action\":\"";
	requestJSON.append(_sendRequest._action).append("\",\"params\":{");

	// params analyse
	try
	{
		if (_sendRequest._params.size() != _sendRequest._paramsID.size())
			throw throwProcessing::BadRequestParams();
	}
	catch (throwProcessing::BadRequestParams& brp)
	{
		brp.what();
	}



}

