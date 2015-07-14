#include "SystemPrerequisites.h"
#include "Game.h"


Ogre::SystemGlobalEnvironment*		gEnv = 0;


int main()
{
	Ogre::Game game;

	game.initialize();

	game.go();

	return 0;
}