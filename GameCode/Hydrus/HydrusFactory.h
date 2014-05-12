#pragma once
#include "../Galaxy/GalaxyFactory.h"

class HydrusGame;

enum ActorType
{
	USER,
	AI
};

typedef std::vector<std::string> AttributeVec;

class HydrusFactory : public GalaxyFactory
{
private:
	static AttributeVec ActorAttributes(const enum ActorType);

public:
	static void Initialize();

	static ActorId CreateActor(const std::string& aName, const enum ActorType aType);

};