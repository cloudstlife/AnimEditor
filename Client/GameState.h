#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "IState.h"
#include "ManagerUI.h"



namespace Ogre
{
	struct IScene;
	struct ISceneNode2D;
	class  GameBackParam;

	class GameState : public IState
	{
	public:
		GameState();
		~GameState();

		virtual	void			initialize();
		virtual void			destroy();
		virtual const String&	getName();
		virtual	void			update( float timeLapse );
		virtual	void			procAppMessage( uint uMsg, int wParam, int lParam );
		void					initializeSql();
		void					initializeGameParam();
		void					createSceneBackgroud();

	public:
		static const String		StateName;
	private:
		IScene*				mScene;
		ISceneNode2D*		mSceneNode;
		// º”‘ÿUI
		ManagerUI *m_pManager;
	};
}


#endif