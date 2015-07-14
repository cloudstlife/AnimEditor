#ifndef ACTORPLAYER_H
#define ACTORPLAYER_H
#include "Actor.h"

namespace Ogre
{
	class ActorEnergyBmob;
	struct ISprite2D;
	struct ISceneNode2D;
	struct ILabelNumber2D;
	struct ISound;
	struct GunLevelAction
	{
	  Action*		common;
	  Action*		fire;
	  int64			minScore;
	  int64			maxScore;
	};
	struct GunLevelNode
	{
	  String		common;
	  String		fire;
	  int64			minScore;
	  int64			maxScore;
	};

	struct BetScoreLabel
	{
		String		id;
		int			layer;
		Vector2		pos;
		int			defaultScore;
	};

	struct PlayerToDataBase
	{
		int		currentPoints; // 剩余分数
		int		currentGuns; // 炮台押分
		int		currentEnergy; // 能量
	};

	struct BulletRotScope
	{
		Real	minScope;
		Real	maxScope;
	};

	struct BmobProperty
	{
		String		id;
		Vector2		pos;
		int			appearValue;
	};

	typedef BetScoreLabel PointLabel;
	typedef std::list< GunLevelNode >				ListGunLevelNode;
	class ActorPlayer: public Actor 
	{
		typedef std::list< GunLevelAction* >			ListGunLevelAction;

		enum EBusinessMode
		{
			// 与数据库中数据一致
			EPressKeyOutCoins = 1,
			EPressKeyOutTicket,
			EFiredOutCoins,
			EFiredOutTicket,
			EFiredOutCoinsAndTicket,
		};

		public:
			enum EPlayerFireState
			{
				ENormalState = 1,
				EAutoFireState = 2,
				ELockFireState = 3,
			};

		ActorPlayer( ActorDesc* desc, ISceneNode2D* node, IScene* scene, const String& name = "" );
		virtual ~ActorPlayer();
		virtual	void			initailze();
		virtual	void			updateLogic( Real timeLapse );
		virtual const String&	type() const;
		virtual void			setProperty( const String& name, const Any& val );
		void					injectWinMsg( uint uMsg, int wParam, int lParam );

		public:
		DYNAMIC_DECLARE( ActorPlayer );
		int64				getCurrentBet();
		void				addCurrentPointByFish(int point, int energy);
		int64				getCurrentDecPoint(); // 当前减少分数
		void				updateCurrentBetByUI(int64 bet);
		void				businessDecFen(bool keyDown = false);
		void				changeFireState(EPlayerFireState state);
		int					getFireState();
		bool				isBmobFire();
		Real				getFireInternalTime();
		Action*				getActionFire();
		Action*				getActionCommon();
		bool				checkFire();


		private:
			void				_checkBmobFire();
			void				_applyGunFromScore( int64 score );
			void				_updatePlayerToDataBase(int64 betScore, int64 curPoint, int64 energyVal);
			int					_getPlayerId(const String& str);
			void				_setCurrentPointByInCoin(int64 point);
			void				_addCurrentPoint(int64 point);
			void				_setBmobFireData();
			

		private:
			Real		mTimes;
			Real		mShowTimes;
			Real		mRot;
			bool		mKeyLeftDown;
			bool		mKeyRightDown;

			Action*				mActionFire;
			Action*				mActionCommon;
			Action*				mCurActionState;// 发炮状态（自动发炮，自动锁定，常规。。。）
			ActorEnergyBmob*	mActorEnergyBmob;
			ISprite2D*			mSprites;
			ISceneNode2D*		mPlayerNodeBg;
			ISceneNode2D*		mSceneNodePaoGuang;
			ISceneNode2D*		mBetNumberNode;
			ISceneNode2D*		mPointNode;
			ISceneNode2D*		mBmobNode;
			ILabelNumber2D*		mBetNumber;
			ILabelNumber2D*		mPoint;
			ListGunLevelAction	mGunLevelActions;
			ListGunLevelNode	mGunLevelNodes;
			int64				mCurrentBetScore;
			int64				mCurrentPoint;
			int64				mCurrentEnergy;
			PlayerToDataBase	mPlayerToDataBase;
			BulletRotScope		mBulletRotScope;
			int64				mCurrnetDecPoint;// 放一炮的分，不足押注时
			EPlayerFireState	mFireState;
			BmobProperty		mBmobProperty;
			bool				mBmobFire;
			Real				mFireInternalTime;
			//ISound				*mSound;
	};

	class ActorFactoryPlayer : public ActorFactory
	{
		public:
		ActorFactoryPlayer();
		virtual ~ActorFactoryPlayer();

		virtual const String&	type() const;

		virtual Actor*			createInstance( ActorDesc* actorDesc, ISceneNode2D* node, IScene* scene, const String& name = "" );

		virtual  ActorDesc*		load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const String		TypeName;
	};
}
#endif