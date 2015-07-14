#include "SystemPrerequisites.h"
#include "GameData.h"
#include "LoginPage.h"
#include "GameEnvironment.h"
#include "UIState.h"

namespace Ogre
{
#define SetMessageToPageUI(control, showMsg)\
	{\
	this->m_pUi->invokeActionscript( control, showMsg );\
	}

#define SetMessageToPageUIByName(control)\
	{\
	this->m_pUi->invokeActionscript( control );\
	}
	LoginPage::LoginPage():
		m_pUi(NULL)
		, m_pCurState(NULL)
	{

	}

	LoginPage::~LoginPage()
	{
		SafeDelete(m_pUi);
		SafeDelete(m_pCurState);
	}

	void LoginPage::Initialize(IUiElement* ui, UIState* state)
	{
		m_pUi = ui;
		m_pCurState = state;
	}

	void LoginPage::injectAppMsg( uint uMsg, int wParam, int lParam )
	{

	}

	void LoginPage::update( float timeLapse )
	{

	}

	bool LoginPage::CheckLogin(const Message::Base& msg)
	{

		const UiMessage& uiMsg = static_cast< const UiMessage& >( msg );
		String strMiMa = uiMsg[0].get<String>();
		// 比较
		String strOriMiMa = gEnvGame.mGameData->GetViewSystemSettingParamByGame().m_strMiMa;
		if (strOriMiMa.compare(strMiMa) == 0)
		{
			// 打开主界面
			SetMessageToPageUI("SetVisibleLoginPage", false);
			SetMessageToPageUI("SetVisibleMainPage", true);
		}
		else
		{
			// 打开错误提示
			OpenLoginTips();
		}
		return true;
	}

	bool LoginPage::LoginPageCompelete(const Message::Base& msg)
	{
		// 设置状态
		m_pCurState->changeCurState(this);
		SetLoginPageFocusControl();
		ResetLoginPageMiMa();
		return true;
	}

	void LoginPage::OpenLoginTips()
	{
		SetMessageToPageUIByName("OpenLoginTips");
	}

	void LoginPage::SetLoginPageFocusControl()
	{
		SetMessageToPageUIByName("SetLoginPageFocusControl");
	}

	void LoginPage::ResetLoginPageMiMa()
	{
		SetMessageToPageUIByName("ResetLoginPageMiMa");
	}
}