#pragma once

#include <string>
#include <vector>
#include <any>

namespace Bot
{
	// API Request form
	struct Request
	{
		const std::string _action{};
		const std::vector<std::string> _paramsID{};
		const std::vector<std::any> _params{};
		const std::string _echo{};
	};

	// Message response
	struct Response
	{
		const std::string _status{};
		const std::string _retcode{};
		const int _data{ NULL };
		const std::string _echo{};
	};

	struct Report
	{
		const long _time{ NULL };
		const long _self_id{ NULL };
		const std::string _post_type{};
	};

	namespace Event
	{
		struct PrivateMessage
		{
			const int64_t time{ NULL };
			const int64_t self_id{ NULL };
			const std::string post_type{ "message" };
			const std::string message_type{ "private" };
			const std::string sub_type;
			const int32_t message_id{ NULL };
			const int64_t user_id{ NULL };
			const std::string message{};
			const std::string raw_message{};
			const int32_t font{ NULL };
			const struct sender
			{
				const int64_t user_id{ NULL };
				const std::string nickname{};
				const std::string sex{};
				const int32_t age{ NULL };
			};
		};

		struct GroupMessage
		{
			const int64_t time{ NULL };
			const int64_t self_id{ NULL };
			const std::string post_type{ "message" };
			const std::string message_type{ "group" };
			const int32_t message_id{ NULL };
			const int64_t group_id{ NULL };
			const int64_t user_id{ NULL };
			const struct anonymous
			{
				const int64_t id{ NULL };
				const std::string name{};
				const std::string flag{};
			};
			const std::string message{};
			const std::string raw_message{};
			const int32_t font{ NULL };
			const struct sender
			{
				const int64_t user_id{ NULL };
				const std::string nickname{};
				const std::string card{};
				const std::string sex{};
				const int32_t age{ NULL };
				const std::string area{};
				const std::string level{};
				const std::string rold{};
				const std::string title{};
			};
		};
	}
}
