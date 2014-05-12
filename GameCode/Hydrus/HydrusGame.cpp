#include "../Galaxy/GalaxyGame.h"
#include "../Galaxy/StringHandler.h"
#include "../Galaxy/GalaxyAlgorithms.h"
#include "HydrusEncounter.h"
#include "HydrusGame.h"
#include "HydrusFactory.h"
#include "EventData_Hydrus.h"
#include "HydrusConsoleView.h"
#include "HydrusEvents.h"

extern StringHandler* g_pStringHandler;
extern EventManager* p_gEventManager;

HydrusConsoleView* p_gHydrusConsoleView;


HydrusGame::HydrusGame()
{
	using namespace std::placeholders;
	p_gEventManager->RegisterDelegate(ActorMinHealthEvent::sEventId, std::bind(&HydrusGame::ActorMinimumHealthDelegate, this, _1));
}

HydrusGame::~HydrusGame()
{


}
void HydrusGame::SetupGameState(UInt& aGameSaveData)
{
	p_gHydrusConsoleView = GALAXY_NEW HydrusConsoleView();


	// Ask the user if they would like to start a 
	// new game or load one
	g_pStringHandler->PrintString(GAME_NEW_OR_LOAD);

	UInt gameOption = 0;
	std::string gameOptionStr;
	GalaxyAlgorithms::StringInput(gameOptionStr, "1");
	gameOption = stoi(gameOptionStr);

	switch (gameOption)
	{
	case 1:
		{
			// Initialize new game data here
			system("cls");

			// placeholder for something cool for initializing
			aGameSaveData = 1;
		}
		break;

	case 2:
		{
			assert(0); // load from save not available yet!
		}
		break;

	default:
		{
			system("cls");

			// In case a character was entered.
			throw gameOption;
		}
		break;
	}
}


void HydrusGame::InitializePlayers()
{
	// Create a main character controlled by the user
	system("cls");
	g_pStringHandler->PrintString(ENTER_MAIN_CHARACTER_NAME);
	ActorId dieselId = this->CreateActorFromUserName("Diesel");
	mMainActorMap["Diesel"] = dieselId;

	system("cls");
	g_pStringHandler->PrintString(WELL, this->GetActorName(dieselId));
	g_pStringHandler->PrintString(KICKASS);


	// Create companion
	g_pStringHandler->PrintString(ENTER_SECOND_CHARACTER_NAME);
	ActorId bomberId = this->CreateActorFromUserName("Bomber");
	mMainActorMap["Bomber"] = bomberId;
}


void HydrusGame::InitializeGameState(UInt& aGameSaveState)
{
	system("cls");
	while (aGameSaveState == 0)
	{
		try
		{
			this->SetupGameState(aGameSaveState);
			break; // while loop
		}
		catch (UInt& eGameOption)
		{
			g_pStringHandler->PrintString(OPTION_NOT_FOUND,eGameOption);
			g_pStringHandler->PrintString(PICK_VALID_OPTION);
		}
	}
}

void HydrusGame::LoadLevel(const std::string& aLevel)
{
	// Let the base object load generic parts like maps
	this->LoadLevelBase(aLevel);

	// Here I will parse an XML file with Hydrus specific data
	if (aLevel == "developerGym")
	{

	}
}


void HydrusGame::InitializeMainLoopProcesses()
{
	// For right now, lets start off with a battle
	std::vector<ActorId> initBattleAllyActorIds;
	initBattleAllyActorIds.push_back(mMainActorMap["Diesel"]);
	initBattleAllyActorIds.push_back(mMainActorMap["Bomber"]);

	// Make a marine enemy
	std::vector<ActorId> initBattleEnemyActorIds;
	initBattleEnemyActorIds.push_back(HydrusFactory::CreateActor("marine", AI));
	initBattleEnemyActorIds.push_back(HydrusFactory::CreateActor("marine", AI));
	initBattleEnemyActorIds.push_back(HydrusFactory::CreateActor("marine", AI));

	StrongProcessPtr initialBattle(GALAXY_NEW HydrusEncounter(initBattleAllyActorIds, initBattleEnemyActorIds));
	this->AddProcess(initialBattle);
}


ActorId HydrusGame::CreateActorFromUserName(const std::string& aDefaultName)
{
	std::string actorName;
	GalaxyAlgorithms::StringInput(actorName, aDefaultName);
	return HydrusFactory::CreateActor(actorName,USER);

}

void HydrusGame::ActorMinimumHealthDelegate(EventData* aEventData)
{
	EventData_ActorMinHealth* eventData = static_cast<EventData_ActorMinHealth*> (aEventData);

	ActorId minHealthActor = eventData->GetActorId();

	auto it = find_if(mMainActorMap.begin(), mMainActorMap.end(), [=](std::pair<std::string, ActorId> i) -> bool
	{
		return (i.second == minHealthActor);
	});

	if (it == mMainActorMap.end())
	{
		this->OnActorDeath(minHealthActor);
	}
	else
	{
		// Main actors do not terminate here
		EventData_RemoveProcessIf removalData(minHealthActor);
		this->RemoveProcessesIf(&removalData);
	}
}

