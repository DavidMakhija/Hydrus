#pragma once
#include "GalaxyDefs.h"
#include "ActorSet.h"
#include "ProcessQueue.h"
#include "GalaxyFactory.h"


class GalaxyGame
{
	friend class GalaxyFactory;
	friend int _tmain(int argc, _TCHAR* argv[]);
private:
	ActorSet mActorSet;

	ProcessQueue mProcessQueue;

	virtual void SetupGameState(UInt& aGameSaveData) = 0;
	
	virtual void InitializeGameState(UInt& aGameSaveState) = 0;

	virtual void InitializePlayers() = 0;

	virtual void InitializeMainLoopProcesses() = 0;

	 std::pair<ActorId,WeakActorPtr> CreateActor(const std::string& aName){ return mActorSet.CreateActor(aName);}

	virtual ActorId CreateActorFromUserName(const std::string& aDefaultName) = 0;
	
	void ProcessMainLoop();

protected:

	void InitializeBase();

	void LoadLevelBase(const std::string& aLevel);

public:
	GalaxyGame();

	virtual ~GalaxyGame() {}

	void AddProcess(StrongProcessPtr& aProcess);

	const std::string& GetActorName(const ActorId aActorId){return mActorSet.GetActorName(aActorId);}

	const StrongActorPtr GetActor(const ActorId aActorId) {return mActorSet.GetActorPointer(aActorId);}

	void ActorDeath(StrongActorPtr aActor);

};