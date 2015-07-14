#include "SystemPrerequisites.h"
#include "IComponent.h"
#include "Game.h"
#include "GameState.h"
#include "NormalActorFish.h"
#include "ActorBullet.h"
#include "ActorStatic.h"
#include "ActorGoldCoin.h"
#include "ActorPlayer.h"
#include "ActorBackground.h"
#include "ActorGeneratorDefault.h"
#include "ActorParallelGenerator.h"
#include "ActorMixParallelGenerator.h"
#include "ActorGeneratorDiffuse.h"
#include "ActorGeneratorRoundDiffuse.h"
#include "ActorBoundaryScreen.h"
#include "ActorGeneratorRandomChase.h"
#include "ActorEnergyBmob.h"
#include "ActorAutoLockTarget.h"
#include "Navigation2DDefault.h"
#include "Navigation2DParallel.h"
#include "Naviagtion2DSimpleDir.h"
#include "Naviagtion2DRoundDiffuse.h"
#include "Navigation2DRandomChase.h"
#include "INavigation2DManager.h"
#include "IFrameWork.h"

#ifdef _DEBUG
static const char* SystemDllName = "System_d.dll";
#else
static const char* SystemDllName = "System.dll";
#endif

namespace Ogre
{
	Game::Game()
	{

	}

	Game::~Game()
	{
		mCompntSystem->destroy();
		UnloadComponent( mCompntSystem );
	}

	void	Game::initialize()
	{
		Ogre::NameValuePairList param;

		param["FSAA"] = "0";
		param["vsync"] = "false";
		param["gamma"] = "false";
		param["useNVPerfHUD"] = "true";
		param["depthBuffer"] = "true";

		param["frameWork"] = "true";
		param["appTitle"] = "AllBlue";
		param["appIcon"] = "gfx.ico";
		param["appWidth"] = "1366";
		param["appHeight"] = "700";
		param["appIsFullScreen"] = "false";

		param["log"] = "AllBlue.log";

		mCompntSystem = Ogre::LoadComponent( SystemDllName );

		mCompntSystem->setPerporty( param );

		gEnv = mCompntSystem->initialize( NULL );
		
		registerActor();
		registerActorGenerator();
		registerNavigation();

		gEnv->mSystem->registerState( new GameState, true );
		
	}

	void	Game::registerActor()
	{
		gEnv->mSystem->registerActorFactory( new Ogre::ActorFactoryStatic );
		gEnv->mSystem->registerActorFactory( new Ogre::ActorFactoryNormalFish );
		gEnv->mSystem->registerActorFactory( new Ogre::ActorFactoryBullet );
		gEnv->mSystem->registerActorFactory( new Ogre::ActorFactoryGoldCoin );
		gEnv->mSystem->registerActorFactory( new Ogre::ActorFactoryEnergyBmob);
		gEnv->mSystem->registerActorFactory( new Ogre::ActorFactoryAutoLockTarget);


		// Player
		gEnv->mSystem->registerActorFactory(new Ogre::ActorFactoryPlayer);
		// BackMap
		gEnv->mSystem->registerActorFactory(new Ogre::ActorFactoryBackground);
		// 世界边界(电网)
		gEnv->mSystem->registerActorFactory(new Ogre::ActorFactoryBoundaryScreen);
	}

	void	Game::registerActorGenerator()
	{
		gEnv->mSystem->registerActorGeneratorFactory(new Ogre::ActorGeneratorFactoryDefault);
		gEnv->mSystem->registerActorGeneratorFactory(new Ogre::ActorGeneratorFactoryParallel);
		gEnv->mSystem->registerActorGeneratorFactory(new Ogre::ActorGeneratorFactoryMixParallel);
		gEnv->mSystem->registerActorGeneratorFactory(new Ogre::ActorGeneratorFactoryDiffuse);
		gEnv->mSystem->registerActorGeneratorFactory(new Ogre::ActorGeneratorFactoryRoundDiffuse);
		gEnv->mSystem->registerActorGeneratorFactory(new Ogre::ActorGeneratorFactoryRandomChase);
	}

	void	Game::registerNavigation()
	{
		// 导航
		gEnv->mNavigationMgr->registerFactory(new Ogre::Navigation2DFactoryDefault);
		gEnv->mNavigationMgr->registerFactory(new Ogre::Navigation2DFactoryParallel);
		gEnv->mNavigationMgr->registerFactory(new Ogre::Navigation2DFactorySimpleDir);
		gEnv->mNavigationMgr->registerFactory(new Ogre::Navigation2DFactoryRoundDiffuse);
		gEnv->mNavigationMgr->registerFactory(new Ogre::Navigation2DFactoryRandomChase);
	}

	void	Game::go()
	{
		gEnv->mFrameWork->go();
	}
}