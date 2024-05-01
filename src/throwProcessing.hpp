#pragma once

#include <exception>

namespace throwProcessing
{
	class BadRequestParams : std::exception
	{
	public:
		char const* what() const override
		{
			return "The size of _params<vector> and _paramsID<vector> are not same.";
		};
	};
}
