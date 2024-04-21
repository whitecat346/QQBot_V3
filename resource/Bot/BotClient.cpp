
#include "../../include/Internet/hv/WebSocketClient.h"
#include "../../include/Bot/BotClient.h"

BotClient::BotClient()
{
}

BotClient::BotClient(const std::string serverUrl) : _serverUrl(serverUrl)
{
}

void BotClient::Close(const int _outCode)
{
}
