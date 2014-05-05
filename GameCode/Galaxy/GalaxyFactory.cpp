#include "GalaxyFactory.h"
#include "GalaxyGame.h"
#include "StringHandlerEn.h"
#include "Actor.h"

StringHandler* GalaxyFactory::CreateStringHandler()
 {
	 StringHandler* stringHandler = GALAXY_NEW StringHandlerEn();
	 stringHandler->GenerateStrings();

	 return stringHandler;
 }

 std::pair<ActorId,WeakActorPtr> GalaxyFactory::CreateActor(GalaxyGame* aGame, const std::string& aName)
{
	return aGame->CreateActor(aName);
}





