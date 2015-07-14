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
		int64	mInCoins; // Ͷ�Ҷһ�����
		bool	mSaved;
		int64	mTotalCurProfit;// ������ӯ��
		int64	mTotalProfit;// ��ӯ��
		int64	mTotalUpFen;// ���Ϸ�
		int64	mTotalDownFen;// ���·�
		int64	mTotalInCoins;// ��Ͷ��
		int64	mTotalOutCoins;// ���˱�
		int64	mTotalTicket;// �ܲ�Ʊ
		int		mTotalPostCodeNum;// �ܱ������
		int64	mDownFenRatio;// �·ֱ���
		int64	mUpFenRatio;// �Ϸֱ���
		int64	mTicketRatio;// ��Ʊ�һ�����
		int64	mCurrentProfit;// ����ӯ��
		IScene*	mScene;
	};
}

#endif