#include "HumanBrain.h"
#include "../Galaxy/GalaxyAlgorithms.h"
#include "HydrusEncounter.h"
#include "../Galaxy/StringHandler.h"
#include "HydrusEvents.h"
#include "../Galaxy/EventManager.h"

extern StringHandler* g_pStringHandler;
extern EventManager* p_gEventManager;

void HumanBrain::DetermineAction(HydrusEncounter* aEncounter)
{

	StrongActorPtr actor = MakeStrongPointer(this->GetActor());
	std::string actionType;

	system("cls");
	std::cout << actor->GetName() << std::endl;
	g_pStringHandler->PrintString(READY_OPTIONS);
	GalaxyAlgorithms::StringInput(actionType, "a");

	enum ActionType act = GalaxyAlgorithms::ConvertStringToAction(actionType);

	switch (act)
	{
	case ATTACK:
		p_gEventManager->FireEvent(StrongEventPtr(GALAXY_NEW TargetingEvent(GALAXY_NEW EventData_Targeting(actor->GetActorId(), aEncounter, ATTACK))));
		break;

	case PASS:
		// Nothing?
		break;
	default:
		assert(0);
		break;
	}
}


int HumanBrain::SelectTarget(ActorId aActorId, HydrusEncounter* aEncounter, enum ActionType aAction)
{
	std::cout << "Select Target to attack\n";
	aEncounter->PrintTargets(aActorId);
	int targetIndex = GalaxyAlgorithms::AskForTargetIndex(std::string("2"));

	return aEncounter->GetActorIdFromIndex(aActorId, targetIndex);

}
