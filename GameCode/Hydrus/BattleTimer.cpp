#include "BattleTimer.h"
#include "ActorReadyProc.h"
#include "../Galaxy/Actor.h"
#include "../Galaxy/GalaxyGame.h"

extern GalaxyGame* p_gGame;

const std::string BattleTimer::gName = "battletimer";

void BattleTimer::Update(unsigned long aElapsedTime)
{
	mProgress += int(100*double(aElapsedTime)/mTimeScale);
	mProgress = std::min(mProgress,100);
	if (mProgress == 100)
	{
		StrongActorPtr actor = this->GetActor().lock();
		StrongProcessPtr readyProc(GALAXY_NEW ActorReadyProc(actor->GetActorId(),mEncounter));
		mBusy = true;
		p_gGame->AddProcess(readyProc);
	}
}