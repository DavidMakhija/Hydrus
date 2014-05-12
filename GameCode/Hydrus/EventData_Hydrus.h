#pragma once
#include "../Galaxy/GalaxyDefs.h"
#include "../Galaxy/EventData.h"
#include "../Galaxy/GalaxyGame.h"
#include "BattleTimer.h"
extern GalaxyGame* p_gGame;

class HydrusEncounter;

//-----------------------------------------------------------------------------

class EventData_ActorCreated : public EventData
{
public:
	EventData_ActorCreated(IdWeakPtrPair aIdActorPair) : mIdActorPair(aIdActorPair) {}

private:
	IdWeakPtrPair mIdActorPair;
};

//-----------------------------------------------------------------------------

class EventData_ActorReady : public EventData
{
public:
	EventData_ActorReady(ActorId aActorId, HydrusEncounter* aEncounter)
		: mActorId(aActorId), mEncounter(aEncounter) {}
	~EventData_ActorReady()
	{
		p_gGame->GetActor(mActorId)->GET_COMPONENT(BattleTimer)->SetActorState(BattleTimerState::MAX_ALREADY_PROCESSED, false);
	}
	ActorId GetActorId() { return mActorId; }
	HydrusEncounter* GetEncounter() { return mEncounter; }

private:
	ActorId mActorId;
	HydrusEncounter* mEncounter;
};

//-----------------------------------------------------------------------------

class EventData_Targeting : public EventData
{
public:
	EventData_Targeting(ActorId aActorId, HydrusEncounter* aEncounter, enum ActionType aAction)
		: mActorId(aActorId), mEncounter(aEncounter), mAction(aAction) {}

	ActorId GetActorId() { return mActorId; }
	HydrusEncounter* GetEncounter() { return mEncounter; }
	enum ActionType GetActionType() { return mAction; }

private:
	ActorId mActorId;
	HydrusEncounter* mEncounter;

	enum ActionType mAction;
};


//-----------------------------------------------------------------------------

class EventData_ActorMinHealth : public EventData
{
public:
	EventData_ActorMinHealth(ActorId aActorId)
		: mActorId(aActorId) {}

	ActorId GetActorId() { return mActorId; }

private:
	ActorId mActorId;

};


//-----------------------------------------------------------------------------

class EventData_RemoveProcessIf : public EventData
{
public:
	EventData_RemoveProcessIf(ActorId aActorId) : mRemoveActor(aActorId) {}

	ActorId GetActorBeingRemovedFromProcs() { return mRemoveActor; }

private:
	ActorId mRemoveActor;
};