#include "AttackProc.h"
#include "../Galaxy/StringEnums.h"
#include "BattleTimer.h"
#include <thread>
#include <chrono>
#include "HydrusActorStats.h"
#include "EventData_Hydrus.h"

extern GalaxyGame* p_gGame;

AttackProc::AttackProc(ActorId aAttacker,
					   ActorId aTarget)
					   : Process(),
						 mAttacker(aAttacker),
					     mTarget(aTarget),
						 mTimeScale(2000),
						 mProgress(0)
{
	//Set target to busy so they can not mutally attack
	StrongActorPtr attacker = p_gGame->GetActor(mAttacker);
	StrongActorPtr target = p_gGame->GetActor(mTarget);
	attacker->GET_COMPONENT(BattleTimer)->SetActorState(BattleTimerState::ATTACKING, true);
	target->GET_COMPONENT(BattleTimer)->SetActorState(BattleTimerState::BEING_ATTACKED,true);
}

enum Process::ProcessResult AttackProc::Update(unsigned long aElapsedTime)
{
	mProgress += int(100*double(aElapsedTime)/mTimeScale);
	mProgress = std::min(mProgress,100);

	std::cout << p_gGame->GetActorName(mAttacker);
	for (int i = 0; i < mProgress; ++i)
	{
		std::cout << ".";
	}
	for (int i = mProgress; i < 100; ++i)
	{
		std::cout << " ";
	}
	std::cout << p_gGame->GetActorName(mTarget);
	std::cout << std::endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	if (mProgress == 100)
	{
		StrongActorPtr attacker = p_gGame->GetActor(mAttacker);
		StrongActorPtr target = p_gGame->GetActor(mTarget);
		this->Attack(attacker,target);
		attacker->GET_COMPONENT(BattleTimer)->ResetBattleTimer();
		attacker->GET_COMPONENT(BattleTimer)->SetActorState(BattleTimerState::ATTACKING, false);
		target->GET_COMPONENT(BattleTimer)->SetActorState(BattleTimerState::BEING_ATTACKED,false);
		return SUCCESS;
	}


	return STALL;
}

void AttackProc::Attack(StrongActorPtr aAttacker, StrongActorPtr aTarget)
{
	int attackerDamage = -1;
	int targetDamage = -10;

	HydrusActorStats* attackerStats = aAttacker->GET_COMPONENT(HydrusActorStats);
	attackerStats->ModifyStats(attackerDamage,"health",aTarget->GetName(),COUNTER_ATTACK_DAMAGE);

	HydrusActorStats* targetStats = aTarget->GET_COMPONENT(HydrusActorStats);
	targetStats->ModifyStats(targetDamage,"health",aAttacker->GetName(),ATTACK_DAMAGE);

}


bool AttackProc::ProcessRemovalTest(EventData* aEventData) const
{
	EventData_RemoveProcessIf* eventData = static_cast<EventData_RemoveProcessIf*> (aEventData);

	ActorId removedActorId = eventData->GetActorBeingRemovedFromProcs();

	if ((mAttacker == removedActorId) || (mTarget == removedActorId))
	{
		return true;
	}
	return false;
}

AttackProc::~AttackProc()
{
	//Set target to busy so they can not mutally attack
	StrongActorPtr attacker = p_gGame->GetActor(mAttacker);
	StrongActorPtr target = p_gGame->GetActor(mTarget);
	attacker->GET_COMPONENT(BattleTimer)->SetActorState(BattleTimerState::ATTACKING, false);
	target->GET_COMPONENT(BattleTimer)->SetActorState(BattleTimerState::BEING_ATTACKED, false);
}
