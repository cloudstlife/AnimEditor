#ifndef MANAGERUI_H
#define MANAGERUI_H
#include "MainPage.h"
#include "CheckAccountPage.h"
#include "MainTestPage.h"
#include "PostMoneyPage.h"
#include "ParamSettingPage.h"
#include "DeCodeAdjustPage.h"
#include "SystemSettingPage.h"
#include "KeyTestPage.h"
#include "InOutCoinsTestPage.h"
#include "LoginPage.h"
#include "UIState.h"

namespace Ogre
{
	enum EUIPage
	{
		EUI_None = 0,
		EUI_MainPage,
		EUI_Max,
	};

	class ManagerUI
	{
	public:
		ManagerUI();
		~ManagerUI();
		void	Initialize();
		void	SetGameInstance();
		void	injectAppMsg( uint uMsg, int wParam, int lParam );
		void	SetPageVisible(bool visible);
		bool	GetPageVisible(){ return mbOpenPage; };
		void	update( float timeLapse );
		void	setRenderDebugTxt( const WString& content );
		void	closeRenderDebugTxt();

  public:
    IUiElement* GetUIElement();

  private:
    void RegisterDelegate_UI();

  private:
    // UI����
    MainPage *m_pMainPage;
    CheckAccountPage *m_pCheckAccountPage;
    MainTestPage *m_pMainTestPage;
    PostMoneyPage *m_pPostMoneyPage;
    ParamSettingPage *m_pParamSettingPage;
    DeCodeAdjustPage *m_pDeCodeAdjustPage;
    SystemSettingPage *m_pSystemSettingPage;
    KeyTestPage *m_pKeyTestPage;
    InOutCoinsTestPage *m_pInOutCoinsTestPage;
	LoginPage*			m_pLoginPage;

	UIState*			m_pCurState;
    IUiElement			*m_pManagerUI;// ����UI��ͨ��(ֻ��һ��UI������flash���Լ��໥����)
	IUiElement			*m_pDubugUI;	// ֻ������ʾ������Ϣ
    IScene*				mScene;
    ISceneNode2D*		mSceneNode;
	ISceneNode2D*		mScenenDebugUINode;
	bool				mbOpenPage;
  };
}
#endif