#include "AttackProc.h"
#include "../Galaxy/StringEnums.h"
#include "BattleTimer.h"
#include <thread>
#include <chrono>
#include "HydrusActorStats.h"

extern GalaxyGame* p_gGame;

AttackProc::AttackProc(ActorId aAttacker,
					   ActorId aTarget)
					   : Process(),
						 mAttacker(aAttacker),
					     mTarget(aTarget),
						 mTimeScale(2000),
						 mProgress(0)
{

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

	

	if (mProgress == 100)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10000));
		StrongActorPtr attacker = p_gGame->GetActor(mAttacker);
		StrongActorPtr target = p_gGame->GetActor(mTarget);
		this->Attack(attacker,target);
		attacker->GetComponent<BattleTimer>("battletimer")->ResetBattleTimer();
		return SUCCESS;
	}


	return STALL;
}

void AttackProc::Attack(StrongActorPtr aAttacker, StrongActorPtr aTarget)
{
	int attackerDamage = -1;
	int targetDamage = -10;

	HydrusActorStats* attackerStats = aAttacker->GetComponent<HydrusActorStats>("stats");
	attackerStats->ModifyStats(attackerDamage,"health",aTarget->GetName(),COUNTER_ATTACK_DAMAGE);

	HydrusActorStats* targetStats = aTarget->GetComponent<HydrusActorStats>("stats");
	targetStats->ModifyStats(targetDamage,"health",aAttacker->GetName(),ATTACK_DAMAGE);

}
