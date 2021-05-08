#pragma once

#include "Core.h"

#include <string>
#include <vector>
#include <regex>

namespace Command
{
	//	This returns a vector of each command (indexed by spaces)
	//	The first word typed is the last in the vector
	std::vector<const char*> Sanitize(std::string command)
	{
		#if Dr_DEBUG
		//	Check how many spaces in command
			int iSpaces = 0;
			for (int i = 0; i < command.length(); i++)
			{
				if (command[i] == ' ')
					iSpaces++;
			}
		#endif

		std::vector<const char*> UsrCommands;

		size_t lastPhrase = (command.find_last_of(' '));
		size_t nLastPhrase = (command.find_last_of(' '));
		while (true)
		{
			size_t lastPhrase = (command.find_last_of(' '));
			if (lastPhrase > command.size())
			{
				UsrCommands.push_back(command.c_str());
				command.erase();
				break;	//	Reached the end of the string
			}
			else
			{
				std::string pushCommand = (command.substr(lastPhrase + 1, command.size()));
				UsrCommands.push_back(pushCommand.c_str());

				while (nLastPhrase == lastPhrase)
				{
					command.pop_back();
					nLastPhrase = (command.find_last_of(' '));
				}
			}
		}

		return UsrCommands;
	}

	void FindCommand(std::string command)
	{
		std::vector<const char*> Commands;

		if (!command.empty())	//	Ensure a command is specified
		{
			Commands = Sanitize(command);
		}
		else
			return;

		int cOne = Commands.size();

		if (std::regex_match(Commands[cOne], std::regex("(move)|(mv)|(m)")))	//	MOVE
		{
			cLOG(Level::Trace, "Move command issued!");
		}
		else if (std::regex_match(Commands[cOne], std::regex("(check)|(cmove)|(movecheck)")))	//	CHECK MOVE
		{
			cLOG(Level::Trace, "Check Move command issued!");
		}
	}

	//	Commands (defined in Commands.cpp)
	void Move();
	void CheckMove();

}	//	END namespace Command