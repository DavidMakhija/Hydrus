#include "../Galaxy/GalaxyDefs.h"
#include "HydrusEncounter.h"
#include "ActorReadyProc.h"
#include "AttackProc.h"

extern GalaxyGame* p_gGame;

HydrusEncounter::HydrusEncounter(const std::vector<ActorId>& aActorIds) 
					: Process(), mActorIdSeq(aActorIds)
{
	for (int i : mActorIdSeq)
	{
		StrongActorPtr actor = p_gGame->GetActor(i);
		if (actor->GetComponent<BattleTimer>("battletimer") == nullptr)
		{
			actor->AddComponent("battletimer",GALAXY_NEW BattleTimer(actor));
		}
		actor->GetComponent<BattleTimer>("battletimer")->SetEncounter(this);
	}
}

enum Process::ProcessResult HydrusEncounter::Update(unsigned long aElapsedTime)
{
	this->UpdateBattleTimers(aElapsedTime);
	return STALL;
}

void HydrusEncounter::UpdateBattleTimers(unsigned long aElapsedTime)
{
	for (int i : mActorIdSeq)
	{
		StrongActorPtr actor = p_gGame->GetActor(i);
		ActorComponent* battleTimer = actor->GetComponent<BattleTimer>("battletimer");
		battleTimer->Update(aElapsedTime);
	}
}

void HydrusEncounter::PrintTargets()
{
	std::cout << std::endl;

	const int length = mActorIdSeq.size();
	for (int i = 0; i < length; ++i)
	{
		std::cout << i << ". " << p_gGame->GetActorName(mActorIdSeq[i]) << std::endl;
	}

}


ActorId HydrusEncounter::GetActorId(int actorIndex)
{
	return mActorIdSeq[actorIndex];
}

HydrusEncounter::~HydrusEncounter()
{
}


void HydrusEncounter::CreateAttackProc(ActorId attackerId, ActorId targetId)
{
	StrongProcessPtr attackProc(GALAXY_NEW AttackProc(attackerId,targetId));
	p_gGame->AddProcess(attackProc);
}