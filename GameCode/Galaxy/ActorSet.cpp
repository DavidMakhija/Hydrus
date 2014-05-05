#include "ActorSet.h"

ActorSet::ActorSet()
{
    
}

ActorId ActorSet::GetFreeActorId()
{
	// Use last freed ID, if it exists
	if (!mFreeActorIds.empty())
	{
		ActorId freeActorId = mFreeActorIds.top();
		mFreeActorIds.pop();

		return freeActorId;
	}
	// Otherwise, increment the vector of actor pointers by 1
	else
	{
		ActorId freeActorId = mActorPointers.size();
		mActorPointers.push_back(NULL);

		return freeActorId;
	}

	//Previous cases should always return
	assert(0);
	return 0;

}

void ActorSet::RemoveActor(const ActorId aActorId)
{
	// Removes this actor (should call dtor of Actor)
	mActorPointers[aActorId].reset();

	mFreeActorIds.push(aActorId);
}

 std::pair<ActorId,WeakActorPtr> ActorSet::CreateActor(const std::string& aName)
{
	ActorId actorId = this->GetFreeActorId();

	StrongActorPtr pActor (GALAXY_NEW Actor(aName,actorId));
	mActorPointers[actorId] = pActor;

	return std::pair<ActorId,WeakActorPtr>(actorId,pActor);
}

