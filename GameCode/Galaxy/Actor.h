#pragma once
#include "GalaxyDefs.h"

class BattleTimer;
class HydrusEncounter;
class ActorStats;
class ActorComponent;
class Actor
{
	friend class ActorSet;
private:
	typedef std::map<std::string,ActorComponent*> ActorComponents;

	ActorComponents mComponents;

	ActorId mActorId;

	std::string mName;

	Actor(const std::string& aName, const ActorId aActorId);

	enum ActionType HumanInputAction();

public:

	const std::string& GetName() {return mName;}

	template<typename ComponentType>
	ComponentType* GetComponent(ComponentId aId)
	{
		auto it = mComponents.find(aId);
		if (it != mComponents.end())
		{
			return static_cast<ComponentType*> (it->second);
		}
		return nullptr;
	}

	void AddComponent(ComponentId aId, ActorComponent* aComponent)
	{
		auto it = mComponents.insert(std::make_pair(aId,aComponent));
		assert(it.second); // Component already exists
	}

	enum ActionType DetermineAction();

	void AttackAction(HydrusEncounter* aEncounter);

	void HumanAttackAction(HydrusEncounter* aEncounter);

	void ActorOnDeath();

	ActorId GetActorId() {return mActorId;}
};