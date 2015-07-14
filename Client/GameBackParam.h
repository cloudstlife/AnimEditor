#ifndef GAMEBACKPARAM_H
#define GAMEBACKPARAM_H

#define PlayerName "Player"
namespace Ogre
{
	struct IScene;
	class GameBackParam
	{
	public:
		GameBackParam(IScene* scene);
		~GameBackParam();

		void	initialize();
		void	setPlayerNum(int val);
		void	setMaxBet(int64 val);
		void	setMinBet(int64 val);
		void	setMinChange(int64 val);
		int64	getMaxBet();
		int64	getMinBet();
		int64	getMinChange();
		void	setInCoins(int64 val);
		int64	getInCoins();
		void	setDownFenRatio(int64 val);
		int64	getDownFenRatio();
		void	setUpFenRatio(int64 val);
		int64	getUpFenRatio();
		void	setTicketRatio(int64 val);
		void	setTotalCurProfit(int64 val);
		int64	getTotalCurProfit();
		int64	getTicketRatio();
		void	updatePlayerCurrentBet();
		void	setCurrentProfitByPlayer(int64 val);
		void	setTotalUpFenByPlayer(int64 val);
		void	setTotalDownFenByPlayer(int64 val);
		void	setTotalOutCoinsByPlayer(int64 val);
		void	setTotalTicketByPlayer(int64 val);
		void	setTotalInCoinsByPlayer(int64 val);
		void	reSetCurretProfit();
		//void	setTotalPostCodeNum(int val);
		void	update(float timeLapse);

	private:
		void	_loadGameParam();
		void	_getTotalUpFenFromDB();
		void	_getTotalDownFenFromDB();
		void	_getTotalOutCoinsFromDB();
		void	_getTotalTicketFromDB();
		void	_getTotalPostCodeNumFromDB();
		void	_getTotalInCoinsNumFromDB();
		void	_saveGamePara();
		String _int64ToString(int64 val);

	private:
		int		mPlayerNum;
		int64	mMaxBet;
		int64	mMinBet;
		int64	mMinChange;
		int64	mInCoins; // 投币兑换比率
		bool	mSaved;
		int64	mTotalCurProfit;// 本次总盈利
		int64	mTotalProfit;// 总盈利
		int64	mTotalUpFen;// 总上分
		int64	mTotalDownFen;// 总下分
		int64	mTotalInCoins;// 总投币
		int64	mTotalOutCoins;// 总退币
		int64	mTotalTicket;// 总彩票
		int		mTotalPostCodeNum;// 总报码次数
		int64	mDownFenRatio;// 下分比率
		int64	mUpFenRatio;// 上分比率
		int64	mTicketRatio;// 彩票兑换比率
		int64	mCurrentProfit;// 本次盈利
		IScene*	mScene;
	};
}

#endif