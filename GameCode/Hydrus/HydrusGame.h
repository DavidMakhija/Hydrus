#pragma once
#include "../Galaxy/GalaxyGame.h"
#include "HydrusFactory.h"

class HydrusGame : public GalaxyGame
{
	friend int _tmain(int argc, _TCHAR* argv[]);
	typedef std::map<std::string, ActorId> MainActorMap;
	typedef std::vector<ActorId> AllyActorVec;
	typedef std::vector<ActorId> EnemyActorVec;

private:
	MainActorMap      mMainActorMap;
	AllyActorVec      mAllyActorVec;
	EnemyActorVec     mEnemyActorVec;

	void SetupGameState(UInt& aGameSaveData);

	void InitializeGameState(UInt& aGameSaveState);

	void InitializePlayers();

	void InitializeMainLoopProcesses();

	HydrusGame();

	~HydrusGame();

	void Initialize() {this->InitializeBase();}

	void LoadLevel() {this->LoadLevelBase("developerGym");}

	void LoadLevel(const std::string& aLevel);

	void CreateFactories() {HydrusFactory::Initialize();}

protected:

public:

	virtual ActorId CreateActorFromUserName(const std::string& aDefaultName);

	void ActorMinimumHealthDelegate(EventData* aEventData);

};