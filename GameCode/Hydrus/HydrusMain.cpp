#include "../Galaxy/GalaxyDefs.h"
#include "../Galaxy/GalaxyGame.h"
#include "HydrusGame.h"
#include "../Galaxy/GalaxyFactory.h"
#include "../Galaxy/StringHandler.h"
#include "HydrusFactory.h"
#include "../Galaxy/EventManager.h"

int* gMediaController = nullptr;
StringHandler* g_pStringHandler = nullptr;
GalaxyGame* p_gGame = nullptr;
EventManager* p_gEventManager = nullptr;

int _tmain(int argc, _TCHAR* argv[])
{
	// Initialize global media object
	try
	{
	    gMediaController = new int[5]; //Dummy, just for practice
	}
	catch(std::exception& e)
	{
		fprintf(stdout,"Error generating media controller\n");
		return 1;
	}

	try
	{
		g_pStringHandler = GalaxyFactory::CreateStringHandler();
	}
	catch(std::exception& e)
	{
		fprintf(stdout,"Error generating strings\n");
		return 1;
	}

	try
	{
		p_gEventManager = GALAXY_NEW EventManager();
	}
	catch (std::exception& e)
	{
		fprintf(stdout, "Error generating EventManager\n");
		return 1;
	}

	HydrusGame* game = GALAXY_NEW HydrusGame();
	p_gGame = game;

	game->CreateFactories();

	game->Initialize();

	game->LoadLevel();

	game->ProcessMainLoop();

	SAFE_DELETE(p_gEventManager);

	SAFE_DELETE(game);

	SAFE_DELETE(gMediaController);
	
	return 0;
}
