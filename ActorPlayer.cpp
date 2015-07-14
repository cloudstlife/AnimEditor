#include "SystemPrerequisites.h"
#include "ActorPlayer.h"
#include "ISceneNode2D.h"
#include "IScene.h"
#include "ISprite2D.h"
#include "ISprite2DManager.h"
#include "ActionPlayerCommonGunLV1.h"
#include "ActionPlayerFireLV1.h"
#include "ActionPlayerCommonGunLV2.h"
#include "ActionPlayerFireLV2.h"
#include "ActionPlayerAutoFire.h"
#include "ActionPlayerNormalFire.h"
#include "ILabelNumber2DManager.h"
#include "ILabelNumber2D.h"
#include "GameSql.h"
#include "GameData.h"
#include "GameBackParam.h"
#include "GameEnvironment.h"
#include "ISound.h"
#include "ISoundManager.h"
#include "ActorEnergyBmob.h"

namespace Ogre
{
	struct ActionDescPlayer: public ActorDesc
	{
		SpriteElement		sprite;
		BetScoreLabel		betScore;
		ListGunLevelNode	guns;
		PointLabel			points;
		BulletRotScope		rotScope;
		BmobProperty		bmobProperty;
		Real				internalTime;
	};

	DYNAMIC_IMPLEMENT( ActorPlayer, GETRTTI( Actor ) )
	ActorPlayer::ActorPlayer( ActorDesc* desc, ISceneNode2D* node, IScene* scene, const String& name )
	: Actor( desc, node, scene, name )
	, mTimes(0.0f)
	, mCurrentBetScore(0)
	, mActionCommon(0)
	, mActionFire(0)
	, mPointNode(0)
	, mBmobNode(0)
	, mCurrentPoint(0)
	, mRot(0.0f)
	, mCurrnetDecPoint(0)
	, mFireState(ENormalState)
	, mCurrentEnergy(0)
	, mBmobFire( false )
	, mCurActionState(0)
	, mFireInternalTime(0.0f)
	//, mSound(NULL)
	{
		ActionDescPlayer* actionDesc = static_cast< ActionDescPlayer* >( desc );
		//	精灵
		mSprites = gEnv->mSpriteMgr->create(actionDesc->sprite.id);
		mSprites->setRenderQueue(actionDesc->sprite.layer);
		mPlayerNodeBg = getSceneNode()->createChild();
		mPlayerNodeBg->setPosition(actionDesc->sprite.pos.x, actionDesc->sprite.pos.y);
		mBetNumber = gEnv->mLabelNumberMgr->create(actionDesc->betScore.id);
		mCurrentBetScore = gEnvGame.mGameBackParam->getMinBet();
		mBetNumber->setRenderQueue( actionDesc->betScore.layer );
		mBetNumberNode = getSceneNode()->createChild();
		mBetNumberNode->setPosition(actionDesc->betScore.pos.x, actionDesc->betScore.pos.y);
		mPoint = gEnv->mLabelNumberMgr->create(actionDesc->points.id);
		mPoint->setNumber( mCurrentPoint );
		mPoint->setRenderQueue( actionDesc->points.layer );
		mPointNode = getSceneNode()->createChild();
		mPointNode->setPosition(actionDesc->points.pos.x, actionDesc->points.pos.y);
		mPointNode->setScale(0.5f, 0.5f);
		mSceneNodePaoGuang = mSceneNode->createChild();
		mGunLevelNodes = actionDesc->guns;
		mBulletRotScope.minScope = actionDesc->rotScope.minScope;
		mBulletRotScope.maxScope = actionDesc->rotScope.maxScope;
		mBmobProperty.id = actionDesc->bmobProperty.id;
		mBmobProperty.pos = actionDesc->bmobProperty.pos;
		mBmobProperty.appearValue = actionDesc->bmobProperty.appearValue;
		mFireInternalTime = actionDesc->internalTime;
	}

	ActorPlayer::~ActorPlayer()
	{
		mPlayerNodeBg->detachObject(mSprites);
		mBetNumberNode->detachObject(mBetNumber);
		mPointNode->detachObject(mPoint);
		getSceneNode()->deleteChild(mPlayerNodeBg);
		getSceneNode()->deleteChild(mBetNumberNode);
		getSceneNode()->deleteChild(mPointNode);
		getSceneNode()->deleteChild(mBmobNode);
		mSprites->destroy();
		mSprites = 0;
		mBetNumber->destroy();
		mBetNumber = 0;
		mPoint->destroy();
		mPoint = 0;
	}

	void ActorPlayer::initailze()
	{
		mPlayerNodeBg->attachObject(mSprites);
		mBetNumberNode->attachObject(mBetNumber);
		mPointNode->attachObject(mPoint);
		ListGunLevelNode::iterator iterGunLevel = mGunLevelNodes.begin();
		ListGunLevelNode::iterator iterGunLevelEnd = mGunLevelNodes.end();
		while ( iterGunLevel != iterGunLevelEnd )
		{
			GunLevelAction *pGunLvAction = new GunLevelAction();
			pGunLvAction->common = static_cast<Action*>(this->getAction(iterGunLevel->common));
			if (pGunLvAction->common)
			{
				pGunLvAction->common->setProperty( "SceneNodePaoGuan", Any( mSceneNodePaoGuang ) );
			}
			pGunLvAction->fire = static_cast<Action*>(this->getAction(iterGunLevel->fire)) ;
			if (pGunLvAction->fire)
			{
				pGunLvAction->fire->setProperty( "SceneNodePaoGuan", Any( mSceneNodePaoGuang ) );
			}
			// 设置第一级
			if (!mActionCommon && !mActionFire)
			{
				mActionCommon = pGunLvAction->common;
				mActionFire = pGunLvAction->fire;
			}
			pGunLvAction->minScore = iterGunLevel->minScore;
			pGunLvAction->maxScore = iterGunLevel->maxScore;

			mGunLevelActions.push_back(pGunLvAction);
			++iterGunLevel;
		}

		initailzeActions();
		
		// 读取上回对应玩家数据库中的数据(断电后处理)
		PlayerDataByStart* pPlayerData = gEnvGame.mGameData->GetPlayerDataById(_getPlayerId(this->mGroupName));
		mPoint->setNumber( pPlayerData->m_CurrentPoints );
		if (pPlayerData->m_CurrentGuns> 0 )
		{
			mCurrentBetScore = pPlayerData->m_CurrentGuns;
		}
		mBetNumber->setNumber( mCurrentBetScore );
		// 选中炮台
		_applyGunFromScore(mCurrentBetScore);
		mCurrentPoint = pPlayerData->m_CurrentPoints;

		// 当前发炮模式
		mCurActionState = static_cast<Action*>(this->getAction("Gun_NormalFire"));
	}

	void	ActorPlayer::updateLogic( Real timeLapse )
	{
		mTimes += timeLapse;
		Actor::updateLogic( timeLapse );
		mCurActionState->update(timeLapse);
	}

	const String& ActorPlayer::type() const
	{
		return ActorFactoryPlayer::TypeName;
	}

	void	ActorPlayer::setProperty( const String& name, const Any& val )
	{
		Actor::setProperty( name, val );
	}

	void ActorPlayer::injectWinMsg(uint uMsg, int wParam, int lParam)
	{
		if ( uMsg == WM_KEYDOWN )
		{
			if ( wParam == VK_SPACE )
			{
				/*if(ENormalState != mFireState)
				{
					changeFireState(ENormalState);
					mCurActionState = static_cast<Action*>(this->getAction("Gun_NormalFire"));
					return;
				}
				if (mBmobFire)
				{
					_checkBmobFire();
				}
				changeActionTo(mCurActionState->type());*/
				changeActionTo( mActionFire->type() );
			}
			if (wParam == VK_LEFT)
			{
				// 左旋转
				if (mTimes>0.01)
				{
					mRot--;
					if (mRot<= mBulletRotScope.minScope)
					{
						mRot = mBulletRotScope.minScope;
					}
					mSceneNodePaoGuang->setRotateX(mRot);
					mTimes = 0;
				}
			}
			else if ( wParam == VK_RIGHT)
			{
				// 右旋转
				if (mTimes>0.01)
				{
					mRot ++;
					if (mRot>= mBulletRotScope.maxScope)
					{
						mRot = mBulletRotScope.maxScope;
					}
					mSceneNodePaoGuang->setRotateX(mRot);
					mTimes = 0;
				}
			}
		}
		else if (uMsg == WM_KEYUP)
		{
			if (wParam == VK_NUMPAD0)
			{
				mCurrentBetScore += gEnvGame.mGameBackParam->getMinChange();
				mCurrentBetScore = mCurrentBetScore>
					gEnvGame.mGameBackParam->getMaxBet()?gEnvGame.mGameBackParam->getMaxBet():mCurrentBetScore;
				mBetNumber->setNumber( mCurrentBetScore );
				_applyGunFromScore(mCurrentBetScore);
			}
			else if (wParam == VK_NUMPAD1)
			{
				mCurrentBetScore -= gEnvGame.mGameBackParam->getMinChange();
				mCurrentBetScore = mCurrentBetScore<
					gEnvGame.mGameBackParam->getMinBet()?gEnvGame.mGameBackParam->getMinBet():mCurrentBetScore;
				mBetNumber->setNumber( mCurrentBetScore );
				_applyGunFromScore(mCurrentBetScore);
			}

			if (wParam == '1')
			{
				// 投币加分
				_setCurrentPointByInCoin(gEnvGame.mGameBackParam->getInCoins());
				// 更新投币数据库
				gEnvGame.mGameBackParam->setTotalInCoinsByPlayer(gEnvGame.mGameBackParam->getInCoins());
			}
			else if (wParam == '2')
			{
				// 按键上分
				int64 iCurUpFen = gEnvGame.mGameBackParam->getUpFenRatio() * gEnvGame.mGameBackParam->getInCoins();
				// 判断上分极限
				if ((mCurrentPoint + iCurUpFen)< gEnvGame.mGameData->GetGameUpLimit())
				{
					_setCurrentPointByInCoin(iCurUpFen);
					// 更新上分数据库
					gEnvGame.mGameBackParam->setTotalUpFenByPlayer(gEnvGame.mGameBackParam->getUpFenRatio());
				}
			}
			else if (wParam == '3')
			{
				// 按键下分
				int64 iCurDownFen = gEnvGame.mGameBackParam->getDownFenRatio() * gEnvGame.mGameBackParam->getInCoins();
				// 判断是否下分足够
				if (mCurrentPoint>= iCurDownFen)
				{
					_setCurrentPointByInCoin(-iCurDownFen);
					// 更新下分数据库
					gEnvGame.mGameBackParam->setTotalDownFenByPlayer(gEnvGame.mGameBackParam->getDownFenRatio());
				}
			}
			else if (wParam == '4')
			{
				businessDecFen(true);
			}
			else if (wParam == '5')
			{
				businessDecFen(true);
			}
			// 测试发炮状态
			else if (wParam == '7')
			{
				// ELockFireState
				changeFireState(ELockFireState);
			}
			else if (wParam == VK_DOWN)
			{
				changeFireState(EAutoFireState);
				mCurActionState = static_cast<Action*>(this->getAction("Gun_AutoFire"));
			}
			mTimes = 0;
		}
	}

	int64 ActorPlayer::getCurrentBet()
	{
		return mCurrentBetScore;
	}

	void ActorPlayer::addCurrentPointByFish(int point, int energy)
	{
		mCurrentPoint = mCurrentPoint + (mCurrnetDecPoint* static_cast<int64>(point));
		mPoint->setNumber( mCurrentPoint );
		mCurrentEnergy += static_cast<int64>(energy);
		// 存储数据至数据库
		_updatePlayerToDataBase(mCurrnetDecPoint, mCurrentPoint, mCurrentEnergy);

		// 能量值达到就转换
		if (mCurrentEnergy>= static_cast<int64>(mBmobProperty.appearValue))
		{
			_setBmobFireData();
		}
	}

	int64 ActorPlayer::getCurrentDecPoint()
	{
		return mCurrnetDecPoint;
	}

	void ActorPlayer::updateCurrentBetByUI(int64 bet)
	{
		mCurrentBetScore = bet;
		mBetNumber->setNumber( mCurrentBetScore );
	}

	void ActorPlayer::businessDecFen(bool keyDown)
	{
		// 当前商业模式
		int iCurMode = gEnvGame.mGameData->GetGameCurBusinessMode();
		switch (iCurMode)
		{
		case EPressKeyOutCoins:
		case EFiredOutCoins:
			{
				if (!keyDown && EPressKeyOutCoins == iCurMode)
				{
					return;
				}
				// 退币
				if (mCurrentPoint>= gEnvGame.mGameBackParam->getInCoins())
				{
					_setCurrentPointByInCoin(-gEnvGame.mGameBackParam->getInCoins());
					// 更新退币数据库
					gEnvGame.mGameBackParam->setTotalOutCoinsByPlayer(1);
				}
			}
			break;
		case EPressKeyOutTicket:
		case EFiredOutTicket:
			{
				if (!keyDown && EPressKeyOutTicket == iCurMode)
				{
					return;
				}
				// 退彩票
				int64 iCurTicket = gEnvGame.mGameBackParam->getTicketRatio()* gEnvGame.mGameBackParam->getInCoins();
				// 判断是否分数足够
				if (mCurrentPoint>= iCurTicket)
				{
					_setCurrentPointByInCoin(-iCurTicket);
					// 更新彩票数据库
					gEnvGame.mGameBackParam->setTotalTicketByPlayer(gEnvGame.mGameBackParam->getTicketRatio());
				}
			}
			break;
		case EFiredOutCoinsAndTicket:
			{

			}
			break;
		}
	}

	void ActorPlayer::changeFireState(EPlayerFireState state)
	{
		mFireState = state;
	}

	int ActorPlayer::getFireState()
	{
		return mFireState;
	}

	bool ActorPlayer::isBmobFire()
	{
		return mBmobFire;
	}

	Real	ActorPlayer::getFireInternalTime()
	{
		return mFireInternalTime;
	}

	Action*	ActorPlayer::getActionFire()
	{
		return mActionFire;
	}

	Action*	ActorPlayer::getActionCommon()
	{
		return mActionCommon;
	}

	void ActorPlayer::_setCurrentPointByInCoin(int64 point)
	{
		// 计算本次实际盈利
		gEnvGame.mGameBackParam->setCurrentProfitByPlayer(point);
		_addCurrentPoint(point);
	}

	void ActorPlayer::_addCurrentPoint(int64 point)
	{
		mCurrentPoint += point;
		mPoint->setNumber( mCurrentPoint );
	}

	void ActorPlayer::_setBmobFireData()
	{
		if (mBmobFire)
		{
			return;
		}
		mBmobFire = true;
		// 创建bmobActor
		mBmobNode = mSceneNodePaoGuang->createChild();
		mActorEnergyBmob = static_cast< ActorEnergyBmob* >( mScene->createActor( mBmobProperty.id, mBmobNode ) );
		mBmobNode->setPosition(mBmobProperty.pos.x, mBmobProperty.pos.y);
	}

	bool ActorPlayer::checkFire()
	{
		bool ret = false;
		if (mCurrentPoint>= mCurrentBetScore)
		{
			mCurrnetDecPoint = mCurrentBetScore;
			mCurrentPoint -= mCurrentBetScore;
			mCurrentPoint = mCurrentPoint<0?0:mCurrentPoint;
			mPoint->setNumber( mCurrentPoint );
			// 存储数据至数据库
			_updatePlayerToDataBase(mCurrentBetScore, mCurrentPoint, mCurrentEnergy);
			ret = true;
		}
		else if (mCurrentPoint> 0 && mCurrentPoint< mCurrentBetScore)
		{
			// 直接用完当前分板上的分数
			changeActionTo( mActionFire->type() );
			mCurrnetDecPoint = mCurrentPoint;
			mCurrentPoint -= mCurrentPoint;
			mPoint->setNumber(mCurrentPoint);
			// 存储数据至数据库
			_updatePlayerToDataBase(mCurrentBetScore, mCurrentPoint, mCurrentEnergy);
			ret = true;
		}
		return ret;
	}

	void ActorPlayer::_checkBmobFire()
	{
		changeActionTo( mActionFire->type() );
		mSceneNodePaoGuang->deleteChild(mBmobNode);
		mCurrnetDecPoint = mCurrentBetScore;
		mCurrentEnergy = 0;
		// 能量清空 to do
		_updatePlayerToDataBase(mCurrentBetScore, mCurrentPoint, 0);
		mBmobFire = false;
	}

	void ActorPlayer::_updatePlayerToDataBase(int64 betScore, int64 curPoint, int64 energyVal)
	{
		int playerId = _getPlayerId(this->mGroupName);
		char szSql[128];
		memset(szSql, 0, sizeof(szSql));
		sprintf_s(szSql, "CurrentPoints = %I64d, CurrentGuns = %I64d , Energy = %d Where ConsumerID = %d", curPoint, betScore, energyVal, playerId);
		String strSql = szSql;
		gEnvGame.mGameSql->UpdatePlayersData(strSql);
	}

	int	ActorPlayer::_getPlayerId(const String& str)
	{
		int index = str.find_last_of("Player");
		String strNo = str.substr(index+1, str.length()- index);
		int retNo = atoi(strNo.c_str());
		return retNo;
	}

	void ActorPlayer::_applyGunFromScore( int64 score )
	{
		ListGunLevelAction::iterator iterGunAction = mGunLevelActions.begin();
		ListGunLevelAction::iterator iterGunActionEnd = mGunLevelActions.end();

		while ( iterGunAction != iterGunActionEnd )
		{
			GunLevelAction* pGunAction = (*iterGunAction);
			if (pGunAction->minScore<= score && pGunAction->maxScore>= score )
			{
				if ( mActionCommon && mActionCommon->type() != pGunAction->common->type())
				{
					changeActionTo(pGunAction->common->type());
					mActionCommon = pGunAction->common;
					mActionFire = pGunAction->fire;
					break;
				}
			}
			++iterGunAction;
		}
	}

	const String ActorFactoryPlayer::TypeName = "Player";
	ActorFactoryPlayer::ActorFactoryPlayer()
	{
		registActionFactory( new ActionFactoryPlayerCommonGunLV1 );
		registActionFactory( new ActionFactoryPlayerFireLV1 );
		registActionFactory( new ActionFactoryPlayerCommonGunLV2 );
		registActionFactory( new ActionFactoryPlayerFireLV2 );
		registActionFactory( new ActionFactoryPlayerNormalFire );
		registActionFactory( new ActionFactoryPlayerAutoFire );
	}

	ActorFactoryPlayer::~ActorFactoryPlayer()
	{

	}

	const String&	ActorFactoryPlayer::type() const
	{
		return ActorFactoryPlayer::TypeName;
	}

	Actor*	ActorFactoryPlayer::createInstance( ActorDesc* actorDesc, ISceneNode2D* node, IScene* scene, const String& name )
	{
		ActorPlayer* actor = new ActorPlayer( actorDesc, node, scene, name );
		//	create actions
		_createActions( actor, actorDesc );
		actor->initailze();
		return actor;
	}

	ActorDesc*	ActorFactoryPlayer::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActionDescPlayer* actionDesc = new ActionDescPlayer;

		_loadBaseActorDesc( actionDesc, xmlNode, filename );

		_loadActionDesc( actionDesc, xmlNode, filename );

		// internalTime
		nodeAttr = xmlNode->first_attribute("internalTime");
		if (!nodeAttr)
		{
			EXCEPTEX( "player actor. need internalTime label. filename: " << filename );
		}
		actionDesc->internalTime = StringConverter::parseReal(nodeAttr->value());

		// sprite
		xml_node<>* xmlScoreBody = xmlNode->first_node("sprite");
		if (!xmlScoreBody)
		{
			EXCEPTEX( "player actor. score body. need score label. filename: " << filename );
		}
		nodeAttr = xmlScoreBody->first_attribute("id");
		if (nodeAttr == 0)
		{
		  EXCEPTEX( "player actor. score spriteId. body need sprite label. filename: " << filename );
		}
		actionDesc->sprite.id = nodeAttr->value();
		nodeAttr = xmlScoreBody->first_attribute("layer");
		if (nodeAttr == 0)
		{
			EXCEPTEX( "player actor. score layer. body need sprite label. filename: " << filename );
		}
		actionDesc->sprite.layer = StringConverter::parseInt( nodeAttr->value() );
		nodeAttr = xmlScoreBody->first_attribute("pos");
		if (nodeAttr == 0)
		{
		  EXCEPTEX( "player actor. score pos. body need sprite label. filename: " << filename );
		}
		actionDesc->sprite.pos = StringConverter::parseVector2( nodeAttr->value() );

		// rotscope
		xml_node<>* xmlRotScopeNode = xmlNode->first_node("rotScope");
		if (!xmlRotScopeNode)
		{
			EXCEPTEX( "player actor. rotScopeNode body. filename: " << filename );
		}
		nodeAttr = xmlRotScopeNode->first_attribute("min");
		if (!nodeAttr)
		{
			EXCEPTEX( "player actor. rotScopeNode. body need min label. filename: " << filename );
		}
		actionDesc->rotScope.minScope = StringConverter::parseReal(nodeAttr->value());
		nodeAttr = xmlRotScopeNode->first_attribute("max");
		if (!nodeAttr)
		{
			EXCEPTEX( "player actor. rotScopeNode. body need max label. filename: " << filename );
		}
		actionDesc->rotScope.maxScope = StringConverter::parseReal(nodeAttr->value());


		// number 押注分数
		xml_node<>* numberNode = xmlNode->first_node("number");
		if (!numberNode)
		{
			EXCEPTEX( "player actor. numberNode body. need numberNode label. filename: " << filename );
		}
		nodeAttr = numberNode->first_attribute("id");
		if (!nodeAttr)
		{
			EXCEPTEX( "player actor. score numberNode. body need id label. filename: " << filename );
		}
		actionDesc->betScore.id = nodeAttr->value();
		nodeAttr = numberNode->first_attribute("layer");
		if (!nodeAttr)
		{
			EXCEPTEX( "player actor. score numberNode. body need layer label. filename: " << filename );
		}
		actionDesc->betScore.layer = StringConverter::parseInt( nodeAttr->value() );
		nodeAttr = numberNode->first_attribute("pos");
		if (!nodeAttr)
		{
			EXCEPTEX( "player actor. score numberNode. body need pos label. filename: " << filename );
		}
		actionDesc->betScore.pos = StringConverter::parseVector2( nodeAttr->value() );
		nodeAttr = numberNode->first_attribute("defaultScore");
		if (!nodeAttr)
		{
			EXCEPTEX( "player actor. score numberNode. body need pos defaultscore. filename: " << filename );
		}
		actionDesc->betScore.defaultScore = StringConverter::parseInt(nodeAttr->value());

		// points 剩余分数
		xml_node<>* pointNode = xmlNode->first_node("point");
		if (!pointNode)
		{
			EXCEPTEX( "player actor. pointNode body. need pointNode label. filename: " << filename );
		}
		nodeAttr = pointNode->first_attribute("id");
		if (!nodeAttr)
		{
			EXCEPTEX( "player actor. score pointNode. body need id label. filename: " << filename );
		}
		actionDesc->points.id = nodeAttr->value();
		nodeAttr = pointNode->first_attribute("layer");
		if (!nodeAttr)
		{
			EXCEPTEX( "player actor. score numberNode. body need layer label. filename: " << filename );
		}
		actionDesc->points.layer = StringConverter::parseInt( nodeAttr->value() );
		nodeAttr = pointNode->first_attribute("pos");
		if (!nodeAttr)
		{
			EXCEPTEX( "player actor. score numberNode. body need pos label. filename: " << filename );
		}
		actionDesc->points.pos = StringConverter::parseVector2( nodeAttr->value() );
		nodeAttr = pointNode->first_attribute("defaultScore");
		if (!nodeAttr)
		{
			EXCEPTEX( "player actor. score numberNode. body need pos defaultscore. filename: " << filename );
		}
		actionDesc->points.defaultScore = StringConverter::parseInt(nodeAttr->value());
		// gunlv
		xml_node<>* gunLVNode = xmlNode->first_node( "GunLV" );
		while ( gunLVNode )
		{
			GunLevelNode gunLevelNode;
			nodeAttr = gunLVNode->first_attribute("Common");
			gunLevelNode.common = nodeAttr->value();
			nodeAttr = gunLVNode->first_attribute("Fire");
			gunLevelNode.fire = nodeAttr->value();
			nodeAttr = gunLVNode->first_attribute("MinScore");
			gunLevelNode.minScore = StringConverter::parseLong( nodeAttr->value() );
			nodeAttr = gunLVNode->first_attribute("MaxScore");
			gunLevelNode.maxScore = StringConverter::parseLong( nodeAttr->value() );
			actionDesc->guns.push_back( gunLevelNode );

			gunLVNode = gunLVNode->next_sibling( "GunLV" );
		}

		// bmob
		xml_node<>* bmobNode = xmlNode->first_node("Bmob");;
		if (!bmobNode)
		{
			EXCEPTEX( "player actor. Bmob body. need pointNode label. filename: " << filename );
		}

		nodeAttr = bmobNode->first_attribute("id");
		if (!nodeAttr)
		{
			EXCEPTEX( "player actor. bmob id. body need pos defaultscore. filename: " << filename );
		}
		actionDesc->bmobProperty.id = nodeAttr->value();

		nodeAttr = bmobNode->first_attribute("pos");
		if (!nodeAttr)
		{
			EXCEPTEX( "player actor. bmob pos. filename: " << filename );
		}
		actionDesc->bmobProperty.pos = StringConverter::parseVector2(nodeAttr->value());

		nodeAttr = bmobNode->first_attribute("appearValue");
		if (!nodeAttr)
		{
			EXCEPTEX( "player actor. bmob appearValue. filename: " << filename );
		}
		actionDesc->bmobProperty.appearValue = StringConverter::parseInt(nodeAttr->value());

		return actionDesc;
		}
	}