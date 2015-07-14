#include "SystemPrerequisites.h"
#include "GameState.h"
#include "IResLoadManager.h"
#include "IScene.h"
#include "ISceneNode2D.h"
#include "ActorPlayer.h"
#include "IActorGeneratorManager.h"
#include "GameSql.h"
#include "ISprite2DManager.h"
#include "ISprite2D.h"
#include "GameBackParam.h"
#include "GameEnvironment.h"

namespace Ogre
{
	const String GameState::StateName = "Game";

	GameState::GameState()
		: mScene( 0 )
		, m_pManager(0)
	{
		initialize();
	}

	GameState::~GameState()
	{

	}

	void	GameState::initialize()
	{
		//	��������
		ResourceGroupManager& resourceGroupMgr = ResourceGroupManager::getSingleton();
		resourceGroupMgr.initialiseResourceGroup( "game" );

		//	������Դ
		gEnv->mResLoadMgr->begin( "essential" );
		gEnv->mResLoadMgr->loadAll();

		gEnv->mResLoadMgr->begin( "game" );
		gEnv->mResLoadMgr->loadAll();

		//	��������
		mScene = gEnv->mSystem->createScene( "Game" );
		
		// ��ʼ�����ݿⲿ��
		initializeSql();

		// ��Ϸ��������
		initializeGameParam();

		//	����sceneGroup
		mScene->createActorGroup( "scene" );

		// ���� �����߽�
		mScene->createActorGroup("boundaryScreenGroup");

		gEnvGame.mMainUi = m_pManager = new ManagerUI();

		m_pManager->Initialize();
	}

	void	GameState::destroy()
	{
		delete this;
	}

	const String&	GameState::getName()
	{
		return StateName;
	}

	void	GameState::update( float timeLapse )
	{
		mScene->update( timeLapse );
		gEnvGame.mGameBackParam->update( timeLapse );
		m_pManager->update(timeLapse);
	}

	void	GameState::procAppMessage( uint uMsg, int wParam, int lParam )
	{
		// test
		if ( uMsg == WM_KEYDOWN )
		{
			if ( wParam == VK_HOME && GetAsyncKeyState(VK_CONTROL) )
			{
				if (m_pManager && !m_pManager->GetPageVisible())
				{
					m_pManager->SetPageVisible(true);
				}
				else if (m_pManager && m_pManager->GetPageVisible())
				{
					m_pManager->SetPageVisible(false);
				}
			}
		}
		if (m_pManager && m_pManager->GetUIElement() && m_pManager->GetPageVisible())
		{
			m_pManager->injectAppMsg(uMsg, wParam, lParam);
		}
		ActorPlayer *pActorPlayer = static_cast<ActorPlayer*>(mScene->findActor("Player0"));
		if (pActorPlayer)
		{
		  pActorPlayer->injectWinMsg(uMsg, wParam, lParam);
		}
	}

	void	GameState::initializeSql()
	{
		gEnvGame.mGameSql = new GameSql();
		gEnvGame.mGameData = new GameData();
	}

	void	GameState::initializeGameParam()
	{
		gEnvGame.mGameBackParam = new GameBackParam(mScene);
	}

	void	GameState::createSceneBackgroud()
	{

	}
}