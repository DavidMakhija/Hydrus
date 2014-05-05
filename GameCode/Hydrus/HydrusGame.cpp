#include "../Galaxy/GalaxyGame.h"
#include "../Galaxy/StringHandler.h"
#include "../Galaxy/GalaxyAlgorithms.h"
#include "HydrusEncounter.h"
#include "HydrusGame.h"
#include "HydrusFactory.h"
extern StringHandler* g_pStringHandler;

HydrusGame::HydrusGame()
{

}

HydrusGame::~HydrusGame()
{


}
void HydrusGame::SetupGameState(UInt& aGameSaveData)
{
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
	std::vector<ActorId> initBattleActorIds;
	initBattleActorIds.push_back(mMainActorMap["Diesel"]);
	initBattleActorIds.push_back(mMainActorMap["Bomber"]);

	// Make a marine enemy
	initBattleActorIds.push_back(HydrusFactory::CreateActor(this,"marine",AI));
	initBattleActorIds.push_back(HydrusFactory::CreateActor(this,"marine",AI));
	initBattleActorIds.push_back(HydrusFactory::CreateActor(this,"marine",AI));

	StrongProcessPtr initialBattle(GALAXY_NEW HydrusEncounter(initBattleActorIds));
	this->AddProcess(initialBattle);
}


ActorId HydrusGame::CreateActorFromUserName(const std::string& aDefaultName)
{
	std::string actorName;
	GalaxyAlgorithms::StringInput(actorName, aDefaultName);
	return HydrusFactory::CreateActor(this,actorName,USER);

}