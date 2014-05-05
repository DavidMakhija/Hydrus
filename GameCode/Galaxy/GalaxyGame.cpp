#include "GalaxyGame.h"
#include "GalaxyAlgorithms.h"
#include "Process.h"


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

	mProcessQueue.PrepareProcessing();

	while (true)
	{
		clock_t currentTime = clock();
		auto it =  mProcessQueue.GetNextProcess();
		enum Process::ProcessResult result = (*it)->ProcessUpdate(currentTime);

		switch (result)
		{
		case Process::STALL:
			break;
		case Process::SUCCESS:
			mProcessQueue.erase(it);
			break;
		case Process::FAIL:
			mProcessQueue.erase(it);
			break;
		default:
			break;
		}
	}
}

void GalaxyGame::AddProcess(StrongProcessPtr& aProcess)
{
	mProcessQueue.AddProcessToQueue(aProcess);
}

void GalaxyGame::ActorDeath(StrongActorPtr aActor)
{

}


