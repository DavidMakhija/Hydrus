#include "ActorReadyProc.h"
#include "../Galaxy/GalaxyAlgorithms.h"
#include "../Galaxy/StringHandler.h"
#include "HydrusEncounter.h"
#include "AttackProc.h"

extern StringHandler* g_pStringHandler;

extern GalaxyGame* p_gGame;


ActorReadyProc::ActorReadyProc(ActorId aActorId,
							   HydrusEncounter* aEncounter)
			    : Process(), mActorId(aActorId), mEncounter(aEncounter)
{

}

enum Process::ProcessResult ActorReadyProc::Update(unsigned long aElapsedTime)
{
	StrongActorPtr actor = p_gGame->GetActor(mActorId);
	enum ActionType act = actor->DetermineAction();

	switch (act)
	{
	case ATTACK:
		{
			actor->AttackAction(mEncounter);

			return SUCCESS;
		}
		break;
	default:
		{

		}
		break;
	}

	return STALL;
}

