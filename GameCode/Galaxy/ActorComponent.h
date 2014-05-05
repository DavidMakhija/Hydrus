#pragma once
#include "../Galaxy/GalaxyDefs.h"


class ActorComponent
{
public:
	virtual const std::string GetComponentString() = 0;

	virtual void Update(unsigned long aElapsedTime) {}

	WeakActorPtr GetActor() {return mActor;}
protected:
	ActorComponent(WeakActorPtr aActor) : mActor(aActor) {}

	~ActorComponent() {}
private:



	ActorComponent(const ActorComponent& aActorComponent) {assert(0);}
	ActorComponent& operator=(const ActorComponent& aActorComponent) {assert(0);}

private:
	WeakActorPtr mActor;

};