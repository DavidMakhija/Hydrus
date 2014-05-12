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

	static int AskForTargetIndex(std::string& aString)
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

	static unsigned long ToMilliseconds(clock_t aStartTime, clock_t aEndTime)
	{
		return unsigned long(double(aEndTime - aStartTime) / CLOCKS_PER_SEC * 1000);
	}

	static long TimeRemaining(unsigned long aMaxTime, clock_t aRefTime, clock_t aCurrTime)
	{
		long timeRemaining = aMaxTime - GalaxyAlgorithms::ToMilliseconds(aRefTime, aCurrTime);
		return timeRemaining;
	}
}