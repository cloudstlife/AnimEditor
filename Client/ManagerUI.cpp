#include "SystemPrerequisites.h"
#include "ManagerUI.h"
#include "IScene.h"
#include "ISceneNode2D.h"
#include "IUiElementManager.h"
#include "IResLoadManager.h"
#include "GameEnvironment.h"
#include "IBaseUI.h"


namespace Ogre
{
	ManagerUI::ManagerUI():
	mbOpenPage(false)
	, m_pMainPage(NULL)
	, m_pManagerUI(NULL)
	, m_pCheckAccountPage(NULL)
	, m_pMainTestPage(NULL)
	, m_pPostMoneyPage(NULL)
	, m_pParamSettingPage(NULL)
	, m_pDeCodeAdjustPage(NULL)
	, m_pSystemSettingPage(NULL)
	, m_pKeyTestPage(NULL)
	, m_pInOutCoinsTestPage(NULL)
	, m_pLoginPage(NULL)
	, mSceneNode(NULL)
	, mScenenDebugUINode(NULL)
	, m_pDubugUI(NULL)
  {
  }

  ManagerUI::~ManagerUI()
  {
    m_pMainPage = NULL;
	m_pDubugUI = NULL;
	m_pManagerUI = NULL;
    m_pCheckAccountPage = NULL;
    m_pMainTestPage = NULL;
    m_pPostMoneyPage = NULL;
    m_pParamSettingPage = NULL;
    m_pDeCodeAdjustPage = NULL;
    m_pSystemSettingPage = NULL;
    m_pKeyTestPage = NULL;
    m_pInOutCoinsTestPage = NULL;
	m_pLoginPage = NULL;
  }

  void ManagerUI::Initialize()
  {
    mScene = gEnv->mSystem->findScene( "Game" );
    mSceneNode = mScene->getRootSceneNode()->createChild();
    m_pManagerUI = gEnv->mUiMgr->create( "MainPage" );
	SetGameInstance();
	RegisterDelegate_UI();

	// renderDebugUI
	mScenenDebugUINode = mScene->getRootSceneNode()->createChild();
	m_pDubugUI = gEnv->mUiMgr->create( "DebugUIPage" );
	mScenenDebugUINode->attachObject( m_pDubugUI );
  }

  void ManagerUI::SetGameInstance()
  {
	m_pCurState = new UIState();
    m_pMainPage = new MainPage();
	m_pMainPage->Initialize(m_pManagerUI, m_pCurState);
    m_pCheckAccountPage = new CheckAccountPage();
    m_pCheckAccountPage->Initialize(m_pManagerUI, m_pCurState);
    m_pMainTestPage = new MainTestPage();
    m_pMainTestPage->Initialize(m_pManagerUI, m_pCurState);
    m_pPostMoneyPage = new PostMoneyPage();
    m_pPostMoneyPage->Initialize(m_pManagerUI, m_pCurState);
    m_pParamSettingPage  = new ParamSettingPage();
    m_pParamSettingPage->Initialize(m_pManagerUI, m_pCurState);
    m_pDeCodeAdjustPage = new DeCodeAdjustPage();
    m_pDeCodeAdjustPage->Initialize(m_pManagerUI, m_pCurState);
    m_pSystemSettingPage = new SystemSettingPage();
    m_pSystemSettingPage->Initialize(m_pManagerUI, m_pCurState);
    m_pKeyTestPage = new KeyTestPage();
    m_pKeyTestPage->Initialize(m_pManagerUI, m_pCurState);
    m_pInOutCoinsTestPage = new InOutCoinsTestPage();
    m_pInOutCoinsTestPage->Initialize(m_pManagerUI, m_pCurState);
	m_pLoginPage = new LoginPage();
	m_pLoginPage->Initialize(m_pManagerUI, m_pCurState);
  }

  void ManagerUI::injectAppMsg( uint uMsg, int wParam, int lParam )
  {
		m_pManagerUI->injectAppMsg(uMsg, wParam, lParam);
		m_pDubugUI->injectAppMsg(uMsg, wParam, lParam);
		m_pCurState->injectAppMsg(uMsg, wParam, lParam);
  }

  void ManagerUI::SetPageVisible(bool visible)
  {
	if (visible)
	{
		mSceneNode->attachObject( m_pManagerUI );
		m_pCurState->changeCurState(m_pMainPage);
		m_pMainPage->ResetPageVisible();
	}
	else
	{
		mSceneNode->detachObject( m_pManagerUI );
	}
	mbOpenPage = visible;
  }

  void ManagerUI::update( float timeLapse )
  {
		m_pCurState->update(timeLapse);
  }

  void	ManagerUI::setRenderDebugTxt( const WString& content )
  {
		m_pDubugUI->invokeActionscript( "SetRenderDebugTxt", content );
  }

  void	ManagerUI::closeRenderDebugTxt()
  {
		m_pDubugUI->invokeActionscript("CloseRenderDebugTxt");
  }

  void ManagerUI::RegisterDelegate_UI()
  {
    // 主界面
    m_pManagerUI->subscribeEvent( "MainPage.OpenCheckAccount", EventSlot( &MainPage::OpenCheckAccountPage, m_pMainPage) );
    m_pManagerUI->subscribeEvent( "MainPage.OpenMainTestPage", EventSlot(&MainPage::OpenMainTestPage, m_pMainPage) );
    m_pManagerUI->subscribeEvent( "MainPage.OpenPostMoneyPage", EventSlot(&MainPage::OpenPostMoneyPage, m_pMainPage));
    m_pManagerUI->subscribeEvent( "MainPage.OpenSystemSetPage", EventSlot(&MainPage::OpenSystemSetPage, m_pMainPage));
	m_pManagerUI->subscribeEvent( "MainPage.MainPageCompelete", EventSlot(&MainPage::MainPageCompelete, m_pMainPage));

    // 查帐界面
    m_pManagerUI->subscribeEvent("MainPage.CheckAccountPageCompelete", EventSlot(&CheckAccountPage::CheckAccountPageCompelete, m_pCheckAccountPage));

    // 主测试界面
    m_pManagerUI->subscribeEvent("MainPage.OpenMainTestPageCompelete", EventSlot(&MainTestPage::OpenMainTestPageCompelete, m_pMainTestPage));
    // 子测试界面
    m_pManagerUI->subscribeEvent("MainPage.OpenMainTestPageCompelete", EventSlot(&MainTestPage::OpenMainTestPageCompelete, m_pMainTestPage));
    m_pManagerUI->subscribeEvent("MainPage.OpenKeyTestPage", EventSlot(&MainTestPage::OpenKeyTestPage, m_pMainTestPage));
    m_pManagerUI->subscribeEvent("MainPage.OpenSoundTestPage", EventSlot(&MainTestPage::OpenSoundTestPage, m_pMainTestPage));
    m_pManagerUI->subscribeEvent("MainPage.OpenCodeTestPage", EventSlot(&MainTestPage::OpenCodeTestPage, m_pMainTestPage));
    m_pManagerUI->subscribeEvent("MainPage.OpenInOutCoinPage", EventSlot(&MainTestPage::OpenInOutCoinPage, m_pMainTestPage));
	m_pManagerUI->subscribeEvent("MainPage.OpenInOutCoinPageCompelete", EventSlot(&InOutCoinsTestPage::OpenInOutCoinPageCompelete, m_pInOutCoinsTestPage));
	m_pManagerUI->subscribeEvent("MainPage.KeyWordTestPageCompelete", EventSlot(&KeyTestPage::KeyWordTestPageCompelete, m_pKeyTestPage));

    // 报账界面
    m_pManagerUI->subscribeEvent("MainPage.PostMoneyPageCompelete", EventSlot(&PostMoneyPage::PostMoneyPageCompelete, m_pPostMoneyPage));
    m_pManagerUI->subscribeEvent("MainPage.PostCodeNoBtn_Click", EventSlot(&PostMoneyPage::PostCodeNoBtn_Click, m_pPostMoneyPage));
    m_pManagerUI->subscribeEvent("MainPage.Save_ExitBtn_Click", EventSlot(&PostMoneyPage::Save_ExitBtn_Click, m_pPostMoneyPage));
	m_pManagerUI->subscribeEvent("MainPage.PostMoneyEnter_Click", EventSlot(&PostMoneyPage::PostMoneyEnter_Click, m_pPostMoneyPage));

    // 参数调整
    m_pManagerUI->subscribeEvent("MainPage.ParamSettingPageCompelete", EventSlot(&ParamSettingPage::ParamSettingPageCompelete, m_pParamSettingPage));
	m_pManagerUI->subscribeEvent("MainPage.GameLevelBtn_Click", EventSlot(&ParamSettingPage::GameLevelBtn_Click, m_pParamSettingPage));
	m_pManagerUI->subscribeEvent("MainPage.MaxBetBtn_Click", EventSlot(&ParamSettingPage::MaxBetBtn_Click, m_pParamSettingPage));
	m_pManagerUI->subscribeEvent("MainPage.MinBetBtn_Click", EventSlot(&ParamSettingPage::MinBetBtn_Click, m_pParamSettingPage));
	m_pManagerUI->subscribeEvent("MainPage.MinChangeBtn_Click", EventSlot(&ParamSettingPage::MinChangeBtn_Click, m_pParamSettingPage));
	m_pManagerUI->subscribeEvent("MainPage.InCoinsScaleBtn_Click", EventSlot(&ParamSettingPage::InCoinsScaleBtn_Click, m_pParamSettingPage));
	m_pManagerUI->subscribeEvent("MainPage.UpScoreScaleBtn_Click", EventSlot(&ParamSettingPage::UpScoreScaleBtn_Click, m_pParamSettingPage));
	m_pManagerUI->subscribeEvent("MainPage.DownScoreScaleBtn_Click", EventSlot(&ParamSettingPage::DownScoreScaleBtn_Click, m_pParamSettingPage));
	m_pManagerUI->subscribeEvent("MainPage.TicketScaleBtn_Click", EventSlot(&ParamSettingPage::TicketScaleBtn_Click, m_pParamSettingPage));
	m_pManagerUI->subscribeEvent("MainPage.UpLimitBtn_Click", EventSlot(&ParamSettingPage::UpLimitBtn_Click, m_pParamSettingPage));
	m_pManagerUI->subscribeEvent("MainPage.BrustScoreBtn_Click", EventSlot(&ParamSettingPage::BrustScoreBtn_Click, m_pParamSettingPage));
	m_pManagerUI->subscribeEvent("MainPage.InOutCoinsBtn_Click", EventSlot(&ParamSettingPage::InOutCoinsBtn_Click, m_pParamSettingPage));
	m_pManagerUI->subscribeEvent("MainPage.UpDownScoreBtn_Click", EventSlot(&ParamSettingPage::UpDownScoreBtn_Click, m_pParamSettingPage));
	m_pManagerUI->subscribeEvent("MainPage.MuiscBgBtn_Click", EventSlot(&ParamSettingPage::MuiscBgBtn_Click, m_pParamSettingPage));
	m_pManagerUI->subscribeEvent("MainPage.OpenVoiceBtn_Click", EventSlot(&ParamSettingPage::OpenVoiceBtn_Click, m_pParamSettingPage));
	m_pManagerUI->subscribeEvent("MainPage.MachineTypeBtn_Click", EventSlot(&ParamSettingPage::MachineTypeBtn_Click, m_pParamSettingPage));
	m_pManagerUI->subscribeEvent("MainPage.SaveExit_Click", EventSlot(&ParamSettingPage::SaveExit_Click, m_pParamSettingPage));
	m_pManagerUI->subscribeEvent("MainPage.NoSaveExit_Click", EventSlot(&ParamSettingPage::NoSaveExit_Click, m_pParamSettingPage));
	m_pManagerUI->subscribeEvent("MainPage.Btn_LeftClick", EventSlot(&ParamSettingPage::Btn_LeftClick, m_pParamSettingPage));
	m_pManagerUI->subscribeEvent("MainPage.Btn_RightClick", EventSlot(&ParamSettingPage::Btn_RightClick, m_pParamSettingPage));

    // 解码调整
    m_pManagerUI->subscribeEvent("MainPage.DeCodeAdjustPageCompelete", EventSlot(&DeCodeAdjustPage::DeCodeAdjustPageCompelete, m_pDeCodeAdjustPage));
    m_pManagerUI->subscribeEvent("MainPage.SceneTypeBtn_Click", EventSlot(&DeCodeAdjustPage::SceneTypeBtn_Click, m_pDeCodeAdjustPage));
    m_pManagerUI->subscribeEvent("MainPage.PlayCodeDaysBtn_Click", EventSlot(&DeCodeAdjustPage::PlayCodeDaysBtn_Click, m_pDeCodeAdjustPage));
    m_pManagerUI->subscribeEvent("MainPage.SystemTimeBtn_Click", EventSlot(&DeCodeAdjustPage::SystemTimeBtn_Click, m_pDeCodeAdjustPage));
    m_pManagerUI->subscribeEvent("MainPage.PostCodeSucessBtn_Click", EventSlot(&DeCodeAdjustPage::PostCodeSucessBtn_Click, m_pDeCodeAdjustPage));
    m_pManagerUI->subscribeEvent("MainPage.DeCodeCheckBtn_Click", EventSlot(&DeCodeAdjustPage::DeCodeCheckBtn_Click, m_pDeCodeAdjustPage));
    m_pManagerUI->subscribeEvent("MainPage.ExitDeCodeBtn_Click", EventSlot(&DeCodeAdjustPage::ExitDeCodeBtn_Click, m_pDeCodeAdjustPage));
	m_pManagerUI->subscribeEvent("MainPage.DeCodeAdjust_Btn_LeftClick", EventSlot(&DeCodeAdjustPage::Btn_DeCodeLeftClick, m_pDeCodeAdjustPage));
	m_pManagerUI->subscribeEvent("MainPage.DeCodeAdjust_Btn_RightClick", EventSlot(&DeCodeAdjustPage::Btn_DeCodeRightClick, m_pDeCodeAdjustPage));
	m_pManagerUI->subscribeEvent("MainPage.DeCodeAdjust_KeyEnterBtn_Click", EventSlot(&DeCodeAdjustPage::KeyEnterBtn_Click, m_pDeCodeAdjustPage));

    // 系统设置
    m_pManagerUI->subscribeEvent("MainPage.SystemSettingPageCompelete", EventSlot(&SystemSettingPage::SystemSettingPageCompelete, m_pSystemSettingPage));
    m_pManagerUI->subscribeEvent("MainPage.MachineNoBtn_Click", EventSlot(&SystemSettingPage::MachineNoBtn_Click, m_pSystemSettingPage));
    m_pManagerUI->subscribeEvent("MainPage.DeCheckCodeBtn_Click", EventSlot(&SystemSettingPage::DeCheckCodeBtn_Click, m_pSystemSettingPage));
    m_pManagerUI->subscribeEvent("MainPage.EditMiMaBtn_Click", EventSlot(&SystemSettingPage::EditMiMaBtn_Click, m_pSystemSettingPage));
    m_pManagerUI->subscribeEvent("MainPage.Save_ExitBtn_Click", EventSlot(&SystemSettingPage::Save_ExitBtn_Click, m_pSystemSettingPage));
    m_pManagerUI->subscribeEvent("MainPage.NoSave_ExitBtn", EventSlot(&SystemSettingPage::NoSave_ExitBtn, m_pSystemSettingPage));
	m_pManagerUI->subscribeEvent("MainPage.OriginalMima", EventSlot(&SystemSettingPage::CompareOriginalMima, m_pSystemSettingPage));
	m_pManagerUI->subscribeEvent("MainPage.NewMima", EventSlot(&SystemSettingPage::EidtNewMima, m_pSystemSettingPage));
	m_pManagerUI->subscribeEvent("MainPage.MachineNoEdit", EventSlot(&SystemSettingPage::MachineNoEdit, m_pSystemSettingPage));

	// 登录
	m_pManagerUI->subscribeEvent("LoginPage.keyEnterBtn_Click", EventSlot(&LoginPage::CheckLogin, m_pLoginPage));
	m_pManagerUI->subscribeEvent("LoginPage.LoginPageCompelete", EventSlot(&LoginPage::LoginPageCompelete, m_pLoginPage));
  }

  IUiElement* ManagerUI::GetUIElement()
  {
    return m_pManagerUI;
  }
}