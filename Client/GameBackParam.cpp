#include "SystemPrerequisites.h"
#include "GameBackParam.h"
#include "IScene.h"
#include "GameSql.h"
#include "GameData.h"
#include "ActorPlayer.h"
#include "GameEnvironment.h"

namespace Ogre
{
	GameBackParam::GameBackParam(IScene* scene)
		: mScene( NULL )
		, mPlayerNum(0)
		, mMaxBet(0)
		, mMinBet(0)
		, mMinChange(0)
		, mInCoins(0)
		, mSaved(false)
		, mCurrentProfit(0)
		, mTotalProfit(0)
		, mTotalUpFen(0)
		, mTotalDownFen(0)
		, mTotalInCoins(0)
		, mTotalOutCoins(0)
		, mTotalTicket(0)
		, mDownFenRatio(0)
		, mUpFenRatio(0)
		, mTotalCurProfit(0)
		, mTotalPostCodeNum(0)
	{
		mScene = scene;
		initialize();
	}

	GameBackParam::~GameBackParam()
	{

	}

	void GameBackParam::initialize()
	{
		_loadGameParam();
	}

	void GameBackParam::update(float timeLapse)
	{
		if (mSaved)
		{
			ActorPlayer *pActorPlayer = static_cast<ActorPlayer*>(mScene->findActor("Player0"));
			if (!pActorPlayer)
			{
				// 没有找到一个创建（一群中一个）
				String strNum = StringConverter::toString(mPlayerNum);
				mScene->createActorGroup(strNum);
				mSaved = false;
			}

			//_saveGamePara();
		}
	}

	int64 GameBackParam::getInCoins()
	{
		return mInCoins;
	}

	void	GameBackParam::setDownFenRatio(int64 val)
	{
		mDownFenRatio = val;
	}

	int64	GameBackParam::getDownFenRatio()
	{
		return mDownFenRatio;
	}

	void	GameBackParam::setUpFenRatio(int64 val)
	{
		mUpFenRatio = val;
	}

	int64	GameBackParam::getUpFenRatio()
	{
		return mUpFenRatio;
	}

	void	GameBackParam::setTicketRatio(int64 val)
	{
		mTicketRatio = val;
	}

	void	GameBackParam::setTotalCurProfit(int64 val)
	{
		mTotalCurProfit = val;
	}

	int64	GameBackParam::getTotalCurProfit()
	{
		return mTotalCurProfit;
	}

	int64	GameBackParam::getTicketRatio()
	{
		return mTicketRatio;
	}

	void GameBackParam::updatePlayerCurrentBet()
	{
		// 当前押注小于最小押注，则当前押注设为最小押注
		// 当前押注大于最大押注，则当前押注设为最大押注
		for (int i = 0; i<10; ++i)
		{
			String name = PlayerName + StringConverter::toString(i);
			ActorPlayer *pActorPlayer = static_cast<ActorPlayer*>(mScene->findActor(name));
			if (pActorPlayer)
			{
				// 设置
				if (pActorPlayer->getCurrentBet()> mMaxBet)
				{
					pActorPlayer->updateCurrentBetByUI(mMaxBet);
				}
				else if (pActorPlayer->getCurrentBet()< mMinBet)
				{
					pActorPlayer->updateCurrentBetByUI(mMinBet);
				}
			}
		}
	}

	void GameBackParam::setCurrentProfitByPlayer(int64 val)
	{
		// 这里只记录币值(抚把分值换算成币值，根据当前比值换算，这里传入的分数会有负数)
		// 上分 +， 下分、退币、退彩票-
		val = val/ mInCoins;
		mCurrentProfit = val;
		// 本次总盈利增加
		mTotalCurProfit += mCurrentProfit;
		// 保存入库
		String strTotalCurProfit = _int64ToString(mTotalCurProfit);
		gEnvGame.mGameSql->UpdateCurProfit(strTotalCurProfit);
	}

	void	GameBackParam::setTotalUpFenByPlayer(int64 val)
	{
		mTotalUpFen += val;
		String strTotalUpFen = _int64ToString(mTotalUpFen);
		gEnvGame.mGameSql->UpdateUpPoints(strTotalUpFen);
	}

	void	GameBackParam::setTotalDownFenByPlayer(int64 val)
	{
		mTotalDownFen += val;
		String strTotalDownFen = _int64ToString(mTotalDownFen);
		gEnvGame.mGameSql->UpdateDownPoints(strTotalDownFen);
	}

	void	GameBackParam::setTotalOutCoinsByPlayer(int64 val)
	{
		mTotalOutCoins += val;
		String strTotalOutCoins = _int64ToString(mTotalOutCoins);
		gEnvGame.mGameSql->UpdateOutCoins(strTotalOutCoins);
	}

	void	GameBackParam::setTotalTicketByPlayer(int64 val)
	{
		mTotalTicket += val;
		String strTotalTicket = _int64ToString(mTotalTicket);
		gEnvGame.mGameSql->UpdateRaffleTickets(strTotalTicket);
	}

	void	GameBackParam::setTotalInCoinsByPlayer(int64 val)
	{
		val = val/ mInCoins;
		mTotalInCoins += val;
		String strTotalInCoins = _int64ToString(mTotalInCoins);
		gEnvGame.mGameSql->UpdateInCoins(strTotalInCoins);
	}

	void	GameBackParam::reSetCurretProfit()
	{
		mCurrentProfit = 0;
		mTotalCurProfit = 0;
		// 保存入库
		String strTotalCurProfit = _int64ToString(mTotalCurProfit);
		gEnvGame.mGameSql->UpdateCurProfit(strTotalCurProfit);
	}

	void GameBackParam::setPlayerNum(int val)
	{
		// 改变游戏中玩家数量
		if (mPlayerNum == val)
		{
			return;
		}
		mPlayerNum = val;
		mScene->destroyActorGroup("Player");
		mSaved = true;
	}

	void GameBackParam::setMaxBet(int64 val)
	{
		mMaxBet = val;
	}

	void GameBackParam::setMinBet(int64 val)
	{
		mMinBet = val;
	}

	void GameBackParam::setMinChange(int64 val)
	{
		mMinChange = val;
	}

	int64 GameBackParam::getMaxBet()
	{
		return mMaxBet;
	}

	int64 GameBackParam::getMinBet()
	{
		return mMinBet;
	}

	int64 GameBackParam::getMinChange()
	{
		return mMinChange;
	}

	void GameBackParam::setInCoins(int64 val)
	{
		mInCoins = val;
	}

	void GameBackParam::_loadGameParam()
	{
		setPlayerNum(gEnvGame.mGameData->GetGamePlayerNum());
		setMaxBet(gEnvGame.mGameData->GetGameCurMaxBet());
		setMinBet(gEnvGame.mGameData->GetGameCurMinBet());
		setMinChange(gEnvGame.mGameData->GetGameCurMinChange());
		setInCoins(gEnvGame.mGameData->GetGameCurInCoinsRatio());
		setDownFenRatio(gEnvGame.mGameData->GetGameCurDownFenRatio());
		setUpFenRatio(gEnvGame.mGameData->GetGameCurUpFenRatio());
		setTicketRatio(gEnvGame.mGameData->GetGameCurTicketRatio());
		setTotalCurProfit(gEnvGame.mGameData->GetGameCurProfit());
		_getTotalUpFenFromDB();
		_getTotalDownFenFromDB();
		_getTotalOutCoinsFromDB();
		_getTotalTicketFromDB();
		_getTotalPostCodeNumFromDB();
		_getTotalInCoinsNumFromDB();
		// 设置AcotrPlayer数据
		//_saveGamePara();
	}

	void	GameBackParam::_getTotalUpFenFromDB()
	{
		mTotalUpFen = gEnvGame.mGameData->GetGameTotalUpFen();
	}

	void	GameBackParam::_getTotalDownFenFromDB()
	{
		mTotalDownFen = gEnvGame.mGameData->GetGameTotalDownFen();
	}

	void	GameBackParam::_getTotalOutCoinsFromDB()
	{
		mTotalOutCoins = gEnvGame.mGameData->GetGameTotalOutCoinsNum();
	}

	void	GameBackParam::_getTotalTicketFromDB()
	{
		mTotalTicket = gEnvGame.mGameData->GetGameTotalTicketNum();
	}

	void	GameBackParam::_getTotalPostCodeNumFromDB()
	{
		mTotalPostCodeNum = gEnvGame.mGameData->GetGameTotalPostCodeNum();
	}

	void	GameBackParam::_getTotalInCoinsNumFromDB()
	{
		mTotalInCoins = gEnvGame.mGameData->GetGameTotalInCoinsNum();
	}

	void GameBackParam::_saveGamePara()
	{
		//for (int i = 0; i<10; ++i)
		//{
		//	String name = PlayerName + i;
		//	ActorPlayer *pActorPlayer = static_cast<ActorPlayer*>(mScene->findActor(name));
		//	if (pActorPlayer)
		//	{
		//		// 设置
		//		pActorPlayer->setCurrentPointByFirst(mPlayerNum);
		//	}
		//}
	}

	String GameBackParam::_int64ToString(int64 val)
	{
		char szBuffer[32];
		memset(szBuffer, 0, sizeof(szBuffer));
		sprintf_s(szBuffer, "%I64d", val);
		String retStr;
		retStr = szBuffer;
		return retStr;
	}
}