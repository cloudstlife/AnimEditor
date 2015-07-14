#ifndef GAMEENVIRONMENT_H
#define GAMEENVIRONMENT_H

namespace Ogre
{
	class GameSql;
	class GameData;
	class GameBackParam;
	class ManagerUI;

	struct GameEnvironment
	{
		GameEnvironment()
		{
			memset( this, 0, sizeof( GameEnvironment ) );
		}

		GameSql*				mGameSql;
		GameData*				mGameData;
		GameBackParam*			mGameBackParam;
		ManagerUI*				mMainUi;
	};
}

extern Ogre::GameEnvironment		gEnvGame;

#endif