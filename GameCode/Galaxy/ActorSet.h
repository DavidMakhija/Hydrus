#pragma once
#include "GalaxyDefs.h"
#include <stack>
#include "Actor.h"


typedef std::vector<StrongActorPtr> ActorPointerContainer;

class ActorSet
{
private:
	ActorPointerContainer mActorPointers;

	std::stack<int> mFreeActorIds;

	ActorId GetFreeActorId();
	
protected:

public:
	ActorSet();

	std::pair<ActorId,WeakActorPtr> CreateActor(const std::string& aName);

	void RemoveActor(const ActorId aActorId);

	const std::string& GetActorName(const UInt aActorId) {return mActorPointers[aActorId]->GetName(); }

	StrongActorPtr GetActorPointer(const UInt aActorId) {return mActorPointers[aActorId];}

	void UpdateAllActors();

	void UpdateActor(const UInt aActorId);

};