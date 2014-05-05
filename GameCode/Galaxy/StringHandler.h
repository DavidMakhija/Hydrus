#pragma once
#include "GalaxyDefs.h"
#include "StringEnums.h"


class StringHandler
{
private:


protected:
	std::map<enum OutputStrings, std::string > mStringMap;

public:
	StringHandler();

	void PrintString(const enum OutputStrings aStringEnum) const
	{
		std::cout << mStringMap.find(aStringEnum)->second << std::endl;
	}

	template<typename T>
    void PrintString(const enum OutputStrings aStringEnum, T aExtraInfo) const
	{
		std::cout << mStringMap.find(aStringEnum)->second << aExtraInfo << std::endl;
	}

	void PrintStringNoReturn(const enum OutputStrings aStringEnum) const
	{
		std::cout << mStringMap.find(aStringEnum)->second << " ";
	}

	virtual void GenerateStrings() = 0;

};