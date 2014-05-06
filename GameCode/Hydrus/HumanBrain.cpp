#include "HumanBrain.h"
#include "../Galaxy/GalaxyAlgorithms.h"
#include "HydrusEncounter.h"
#include "../Galaxy/StringHandler.h"

extern StringHandler* g_pStringHandler;

void HumanBrain::AttackAction(HydrusEncounter* aEncounter)
{
	std::cout << "Select Target to attack\n";
	aEncounter->PrintTargets();
	int targetId = GalaxyAlgorithms::AskForTargetId(std::string("2"));

	ActorId attackTargetId = aEncounter->GetActorId(targetId);

	StrongActorPtr actor = MakeStrongPointer(this->GetActor());
	aEncounter->CreateAttackProc(actor->GetActorId(), attackTargetId);

}

enum ActionType HumanBrain::DetermineAction(HydrusEncounter* aEncounter)
{
	StrongActorPtr actor = MakeStrongPointer(this->GetActor());
	std::string actionType;

	system("cls");
	std::cout << actor->GetName() << std::endl;
	g_pStringHandler->PrintString(READY_OPTIONS);
	GalaxyAlgorithms::StringInput(actionType, "a");

	return GalaxyAlgorithms::ConvertStringToAction(actionType);
}