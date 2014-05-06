#include "Actor.h"
#include "GalaxyAlgorithms.h"
#include "StringHandler.h"
#include "../Hydrus/HydrusEncounter.h"

extern StringHandler* g_pStringHandler;

Actor::Actor(const std::string& aName, const ActorId aActorId) :
	mName(aName),
	mActorId(aActorId)
{

}
