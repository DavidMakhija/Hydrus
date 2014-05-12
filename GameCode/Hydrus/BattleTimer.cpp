#include "BattleTimer.h"
#include "HydrusEvents.h"
#include "../Galaxy/Actor.h"
#include "../Galaxy/GalaxyGame.h"
#include "../Galaxy/EventManager.h"
#include "EventData_Hydrus.h"

extern EventManager* p_gEventManager;

const std::string BattleTimer::sName = "battletimer";

void BattleTimer::Update(unsigned long aElapsedTime)
{
	if (mStateSet.AdvanceIsOk())
	{
		mProgress += int(100 * double(aElapsedTime) / mTimeScale);
		mProgress = std::min(mProgress, 100);

		if (mProgress == 100)
		{
			StrongActorPtr actor = this->GetActor().lock();
			EventData_ActorReady* data = GALAXY_NEW EventData_ActorReady(actor->GetActorId(), mEncounter);
			StrongEventPtr readyEvent(GALAXY_NEW ActorReadyEvent(data));
			p_gEventManager->AddEventToQueue(readyEvent);
			this->SetActorState(BattleTimerState::MAX_ALREADY_PROCESSED,true);
		}
	}
}