#include "HydrusConsoleView.h"
#include "EventData_Hydrus.h"
#include "../Galaxy/GalaxyGame.h"
#include "Brain.h"
#include "HydrusEncounter.h"
#include "HydrusEvents.h"

extern GalaxyGame* p_gGame;
extern EventManager* p_gEventManager;

HydrusConsoleView::HydrusConsoleView()
{
	using namespace std::placeholders;
	p_gEventManager->RegisterDelegate(ActorReadyEvent::sEventId, std::bind(&HydrusConsoleView::ActorReadyDelegate, this, _1));
	p_gEventManager->RegisterDelegate(TargetingEvent::sEventId, std::bind(&HydrusConsoleView::TargetingDelegate, this, _1));
}

void HydrusConsoleView::ActorReadyDelegate(EventData* aEventData)
{
	EventData_ActorReady* eventData = static_cast<EventData_ActorReady*> (aEventData);
	ActorId actorId = eventData->GetActorId();
	HydrusEncounter* encounter = eventData->GetEncounter();

	StrongActorPtr actor = p_gGame->GetActor(actorId);
	Brain* actorBrain = actor->GET_COMPONENT(Brain);
	actorBrain->DetermineAction(encounter);

}

void HydrusConsoleView::TargetingDelegate(EventData* aEventData)
{
	EventData_Targeting* eventData = static_cast<EventData_Targeting*> (aEventData);
	ActorId actorId = eventData->GetActorId();
	HydrusEncounter* encounter = eventData->GetEncounter();
	enum ActionType action = eventData->GetActionType();

	StrongActorPtr actor = p_gGame->GetActor(actorId);
	Brain* actorBrain = actor->GET_COMPONENT(Brain);

	ActorId attackTargetId = actorBrain->SelectTarget(actor->GetActorId(), encounter, action);

	encounter->CreateTargetedProc(actorId, attackTargetId, action);
}
