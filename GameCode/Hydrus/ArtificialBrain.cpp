#include "ArtificialBrain.h"
#include "../Galaxy/GalaxyGame.h"
#include "HydrusActorStats.h"

extern GalaxyGame* p_gGame;

int ArtificialBrain::SelectTarget(ActorId aActorId, HydrusEncounter* aEncounter, enum ActionType aAction)
{
	std::vector<ActorId> enemyActors = aEncounter->GetOppenentIdVec(aActorId);
	// For now, just attack the guy with the max health
	auto it = std::max_element(enemyActors.begin(), enemyActors.end() , [](ActorId i, ActorId j) -> bool
	{
        int health_i = (p_gGame->GetActor(i))->GET_COMPONENT(HydrusActorStats)->GetHealth();
		int health_j = (p_gGame->GetActor(j))->GET_COMPONENT(HydrusActorStats)->GetHealth();
		return health_i < health_j;
	});
	return *it;
}
