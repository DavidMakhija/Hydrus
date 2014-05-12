#include "GalaxyGame.h"
#include "GalaxyAlgorithms.h"
#include "Process.h"

static const int MAX_MILLISECONDS = 20;
extern EventManager* p_gEventManager;

GalaxyGame::GalaxyGame() : 
	mActorSet(),
	mProcessQueue()
{
    
}

void GalaxyGame::InitializeBase()
{
	UInt gameSaveData = 0;

	// Create new game or load saved
	this->InitializeGameState(gameSaveData);

	// Generate human and AI players that generally persist
	this->InitializePlayers();

}

void GalaxyGame::LoadLevelBase(const std::string& aLevel)
{
	// Here I will parse an XML file with level details
	if (aLevel == "developerGym")
	{

	}
}

void GalaxyGame::ProcessMainLoop()
{
	this->InitializeMainLoopProcesses();
	unsigned long maxTime = MAX_MILLISECONDS;
	while (true)
	{
		mProcessQueue.DoProcesses(maxTime);
		p_gEventManager->DoEvents(maxTime);

	}
}

void GalaxyGame::AddProcess(StrongProcessPtr& aProcess)
{
	mProcessQueue.AddProcessToQueue(aProcess);
}

void GalaxyGame::OnActorDeath(ActorId aActorId)
{
	for (auto& it : mProcessQueue)
	{
		it->OnActorDeath(aActorId);
	}
}