#pragma once
#include <string>

#include "../Bot/Message.h"

namespace MethodDefault
{
	// User Method
	void responseEventMet(Bot::Response& _res);

	// WebSocket Server Event
	void metaEventMet(std::string& _msg);
	void noticeEventMet(std::string& _msg);
	void messageEventMet(std::string& _msg);
	void requestEventMet(std::string& _msg);

	// Private
	// call user event function
	void onOpenMet();
	void onCloseMet();
}
