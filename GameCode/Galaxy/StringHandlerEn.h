#pragma once
#include "GalaxyDefs.h"
#include "StringHandler.h"

class StringHandlerEn : public StringHandler 
{
	friend class GalaxyFactory;
private:
	StringHandlerEn();

protected:

public:

	void GenerateStrings();

};