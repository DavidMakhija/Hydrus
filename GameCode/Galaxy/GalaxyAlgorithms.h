#pragma once
#include "GalaxyDefs.h"
#include <sstream>

namespace GalaxyAlgorithms
{
	static void StringInput(std::string& aString, const std::string& aDefault)
	{
		std::string input;
		std::getline( std::cin, input );
		// For whatever reason compare returns 0 if the same
	    if (!input.empty())
	    {
		    std::istringstream stream( input );
            stream >> aString;
	    }
		else
		{
			aString = aDefault;
		}
	}

	static int AskForTargetId(std::string& aString)
	{
		// Get the target
		std::string targetId;
		GalaxyAlgorithms::StringInput(targetId, aString);
		return stoi(targetId);
	}


	static enum ActionType ConvertStringToAction(std::string& aAction)
	{
		if (aAction == "a")
		{
			return ATTACK;
		}
		else if (aAction == "p")
		{
			return PASS;
		}
		else
		{
			return ATTACK;
		}
		return ATTACK;
	}
}