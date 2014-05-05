#pragma once
#include "GalaxyDefs.h"
class StringHandler;
class GalaxyGame;

class GalaxyFactory
{
private:
protected:
	static  std::pair<ActorId,WeakActorPtr> CreateActor(GalaxyGame* aGame, const std::string& aName);
public:
	static StringHandler* CreateStringHandler();

};