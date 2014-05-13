#include "../Galaxy/GalaxyDefs.h"
#include "HydrusEncounter.h"
#include "HydrusEvents.h"
#include "AttackProc.h"
#include "EventData_Hydrus.h"
#include "HydrusActorStats.h"

extern GalaxyGame* p_gGame;

HydrusEncounter::HydrusEncounter(const std::vector<ActorId>& aActorIdsSide1, const std::vector<ActorId>& aActorIdsSide2)
					: Process(), mActorIdSeqs()
{
	mActorIdSeqs[0] = aActorIdsSide1;
	mActorIdSeqs[1] = aActorIdsSide2;
	for (auto j : mActorIdSeqs)
	{
		for (auto i : j.second)
		{
			StrongActorPtr actor = p_gGame->GetActor(i);
			if (actor->GET_COMPONENT(BattleTimer) == nullptr)
			{
				actor->AddComponent("battletimer", GALAXY_NEW BattleTimer(actor));
			}
			actor->GET_COMPONENT(BattleTimer)->SetEncounter(this);
		}
	}
}

enum Process::ProcessResult HydrusEncounter::Update(unsigned long aElapsedTime)
{
	bool allMainCharactersDead =
		std::all_of(mActorIdSeqs[0].begin(), mActorIdSeqs[0].end(), [](ActorId i)
		{
			return p_gGame->GetActor(i)->GET_COMPONENT(HydrusActorStats)->IsMinHealth();
		});

	if (allMainCharactersDead || (mActorIdSeqs[1].size() == 0))
	{
		std::cout << "THE BATTLE IS OVER!\n";
		return SUCCESS;
	}
	this->UpdateBattleTimers(aElapsedTime);
	return STALL;
}

void HydrusEncounter::UpdateBattleTimers(unsigned long aElapsedTime)
{
	for (auto j : mActorIdSeqs)
	{
		for (auto i : j.second)
		{
			StrongActorPtr actor = p_gGame->GetActor(i);
			ActorComponent* battleTimer = actor->GetComponent<BattleTimer>("battletimer");
			battleTimer->Update(aElapsedTime);
		}
	}
}

void HydrusEncounter::PrintTargets(ActorId aCurrentActor)
{
	std::cout << std::endl;
	int count = 0;
	std::cout << "Allies\n";
	for (ActorId i : this->GetAllyIdVec(aCurrentActor))
	{
		std::cout << count++ << ". " << p_gGame->GetActorName(i) << std::endl;
	}

	std::cout << "Enemies\n";
	for (ActorId i : this->GetOppenentIdVec(aCurrentActor))
	{
		std::cout << count++ << ". " << p_gGame->GetActorName(i) << std::endl;
	}
}


ActorId HydrusEncounter::GetActorIdFromIndex(ActorId aCurrentActor, int actorIndex)
{
	// Well this got complicated quickly
	std::pair<int, int> allyEnemyPair = this->GetAllyEnemyPair(aCurrentActor);
	if (actorIndex < mActorIdSeqs[allyEnemyPair.first].size())
	{
		return mActorIdSeqs[allyEnemyPair.first][actorIndex];
	}
	return mActorIdSeqs[allyEnemyPair.second][(actorIndex - mActorIdSeqs[allyEnemyPair.first].size())];
}


HydrusEncounter::~HydrusEncounter()
{
}

void HydrusEncounter::CreateTargetedProc(ActorId attackerId, ActorId targetId, enum ActionType aAction)
{
	switch (aAction)
	{
	case ATTACK:
		p_gGame->AddProcess(StrongProcessPtr(GALAXY_NEW AttackProc(attackerId, targetId)));
		break;
	default:
		assert(0);
		break;
	}
	
}

std::pair<int, int> HydrusEncounter::GetAllyEnemyPair(ActorId aCurrentActor)
{
	auto it = std::find(mActorIdSeqs[0].begin(), mActorIdSeqs[0].end(), aCurrentActor);
	if (it != mActorIdSeqs[0].end())
	{
		return std::pair<int, int>(0,1);

	}
	else
	{
		assert(std::find(mActorIdSeqs[1].begin(), mActorIdSeqs[1].end(), aCurrentActor) != mActorIdSeqs[1].end());
		return std::pair<int, int>(1, 0);
	}
	assert(0);
	return std::pair<int, int>(0, 1);
}

std::vector<ActorId> HydrusEncounter::GetOppenentIdVec(ActorId aActorId)
{
	std::pair<int, int> allyEnemyPair = this->GetAllyEnemyPair(aActorId);

	return mActorIdSeqs[allyEnemyPair.second];
}

std::vector<ActorId> HydrusEncounter::GetAllyIdVec(ActorId aActorId)
{
	std::pair<int, int> allyEnemyPair = this->GetAllyEnemyPair(aActorId);

	return mActorIdSeqs[allyEnemyPair.first];
}

bool HydrusEncounter::OnActorDeath(ActorId aActorId)
{
	auto it = std::find(mActorIdSeqs[0].begin(), mActorIdSeqs[0].end(), aActorId);
	if (it != mActorIdSeqs[0].end())
	{
		mActorIdSeqs[0].erase(it);
	}


	it = std::find(mActorIdSeqs[1].begin(), mActorIdSeqs[1].end(), aActorId);
	if (it != mActorIdSeqs[1].end())
	{
		mActorIdSeqs[1].erase(it);
	}
	return false; //Do not erase this process unless all are dead
}