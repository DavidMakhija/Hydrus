#include "../Galaxy/GalaxyDefs.h"
#include "../Galaxy/GalaxyGame.h"
#include "HydrusGame.h"
#include "../Galaxy/GalaxyFactory.h"
#include "../Galaxy/StringHandler.h"
#include "HydrusFactory.h"

int* gMediaController = NULL;
StringHandler* g_pStringHandler = NULL;
GalaxyGame* p_gGame = NULL;

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

	HydrusGame* game = new HydrusGame();
	p_gGame = game;

	game->CreateFactories();

	game->Initialize();

	game->LoadLevel();

	game->ProcessMainLoop();

	SAFE_DELETE(game);

	SAFE_DELETE(gMediaController);
	
	return 0;
}
