#include <iostream>
#include <vector>

int main(int argc, char** argv)
{
	const std::vector<std::string> vargv = [&]
		{
			std::vector<std::string> tempArgv;
			for(unsigned int it = 0; it != argc; it++)
				tempArgv.emplace_back(argv[it]);
			return tempArgv;
		}();
}