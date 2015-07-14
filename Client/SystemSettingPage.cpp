#include "SystemPrerequisites.h"
#include "SystemSettingPage.h"
#include "GameEnvironment.h"
#include "IBaseUI.h"
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


  SystemSettingPage::SystemSettingPage():
		m_bEditMiMaSucess(false)
		, m_bEditMachineNoSucess(false)
		, m_bEditMiMaError(false)
		, m_fTime(0.f)
		, m_pUi(NULL)
		, m_pCurState(NULL)
  {

  }

  SystemSettingPage::~SystemSettingPage()
  {
		SafeDelete(m_pUi);
		SafeDelete(m_pCurState);
  }

  void SystemSettingPage::Initialize(IUiElement* ui, UIState* state)
  {
    m_pUi = ui;
	m_pCurState = state;
  }

  void SystemSettingPage::injectAppMsg( uint uMsg, int wParam, int lParam )
  {
    switch(uMsg)
    {
    case WM_KEYDOWN:
      {
        switch(wParam)
        {
        case VK_ESCAPE:
          {
            SystemSettingPageReturnToMainPage();
          }
          break;
        }
        break;
      }
      break;
    }
  }

  bool SystemSettingPage::SystemSettingPageCompelete(const Message::Base& msg)
  {
		m_pCurState->changeCurState(this);
		_getViewSystemSetting();
		_setPageControlViewDesc();
		return true;
  }

  bool SystemSettingPage::MachineNoBtn_Click(const Message::Base& msg)
  {
		return true;
  }

  bool SystemSettingPage::DeCheckCodeBtn_Click(const Message::Base& msg)
  {
		return true;
  }

  bool SystemSettingPage::EditMiMaBtn_Click(const Message::Base& msg)
  {
		SetSystemSettingOpenEditMiMaPage();
		return true;
  }

  bool SystemSettingPage::Save_ExitBtn_Click(const Message::Base& msg)
  {
		SetMessageToPageUI("SetVisibleMainPage", true);
		return true;
  }

  bool SystemSettingPage::NoSave_ExitBtn(const Message::Base& msg)
  {
		SetMessageToPageUI("SetVisibleMainPage", true);
		return true;
  }

  void SystemSettingPage::SetSystemSettingEditEngineCode(const WString& msg)
  {
		SetMessageToPageUI("SystemSettingEditEngineCode", msg);
  }

  bool SystemSettingPage::MachineNoEdit(const Message::Base& msg)
  {
		// �޸Ļ�̨��
		const UiMessage& uiMsg = static_cast< const UiMessage& >( msg );
		String strMachineNo = uiMsg[0].get<String>();
		strMachineNo = "\'" + strMachineNo + "\'";
		m_bEditMachineNoSucess = gEnvGame.mGameSql->UpdateMachineNo(strMachineNo);
		if (m_bEditMachineNoSucess)
		{
			SystemSettingPageSetTipsTxt(L"�޸ĳɹ���5��󣬷��ء�");
		}
		return true;
  }

  bool SystemSettingPage::CompareOriginalMima(const Message::Base& msg)
  {
		const UiMessage& uiMsg = static_cast< const UiMessage& >( msg );
		String strMiMa = uiMsg[0].get<String>();
		// ��ȡԭʼ����
		SystemSettingParam sysData = gEnvGame.mGameData->GetViewSystemSettingParamByGame();
		if (sysData.m_strMiMa != strMiMa)
		{
			// ����������ʾ
			SystemSettingPageSetTipsTxt(L"����ԭ���벻һ�¡�");
			m_bEditMiMaError = true;
		}
		else
		{
			// �����뽹���Ƶ���������
			SystemSettingPageSetInputMimaOption(2);
		}
		return true;
  }

  bool SystemSettingPage::EidtNewMima(const Message::Base& msg)
  {
	  // ��������
	  const UiMessage uiMsg = static_cast<const UiMessage&>(msg);
	  String strMiMa = uiMsg[0].get<String>();
	  strMiMa = "\'" + strMiMa + "\'";
	  m_bEditMiMaSucess = gEnvGame.mGameSql->UpdateMiMa(strMiMa);
	  if (m_bEditMiMaSucess)
	  {
		  SystemSettingPageSetTipsTxt(L"�޸ĳɹ���5��󣬷��ء�");
	  }
	  return true;
  }

  bool SystemSettingPageEidtNewMima(const Message::Base& msg)
  {
		return true;
  }


  void SystemSettingPage::SetSystemSettingEditMina(const WString& msg)
  {
		SetMessageToPageUI("SystemSettingEditMina", msg);
  }

  void SystemSettingPage::SetSystemSettingOpenEditMiMaPage()
  {
		SetMessageToPageUIByName("SystemSettingOpenEditMiMaPage");
  }

  void SystemSettingPage::SetSystemSettingCloseEditMiMaPage()
  {
		SetMessageToPageUIByName("SystemSettingCloseEditMiMaPage");
  }

  void SystemSettingPage::SystemSettingPageReturnToMainPage()
  {
		SetMessageToPageUIByName( "SystemSettingPageReturnToMainPage" );
  }

  void SystemSettingPage::SystemSettingPageOpenTips()
  {
		SetMessageToPageUIByName("SystemSettingPageOpenTips");
  }

  void SystemSettingPage::SystemSettingPageCloseTips()
  {
		SetMessageToPageUIByName("SystemSettingPageCloseTips");
  }

  void SystemSettingPage::SystemSettingPageSetTipsTxt(const WString& msg)
  {
		SetMessageToPageUI("SystemSettingPageSetTipsTxt", msg);
  }

  void SystemSettingPage::SystemSettingPageSetInputMimaOption(int msg)
  {
		SetMessageToPageUI("SystemSettingPageSetInputMimaOption", msg);
  }

  void SystemSettingPage::update( float timeLapse )
  {
	  if(m_bEditMiMaSucess || m_bEditMachineNoSucess || m_bEditMiMaError)
	  {
			m_fTime += timeLapse;
			if (m_fTime> LEAVESECOND && !m_bEditMiMaError)
			{
				// �رյ�ǰ���棬�����ϼ�����
				SetMessageToPageUIByName("SystemSettingPageKeyReturnPrePage");
				m_bEditMiMaSucess = false;
				m_bEditMachineNoSucess = false;
				_getViewSystemSetting();
				_setPageControlViewDesc();
				m_fTime = 0;
			}
			else if (m_fTime> LEAVESECOND && m_bEditMiMaError)
			{
				// �ر���ʾ
				SetMessageToPageUIByName("SystemSettingPageCloseTips");
				m_bEditMiMaError = false;
				m_fTime = 0;
			}
	  }
	 
  }

  void SystemSettingPage::_getViewSystemSetting()
  {
		gEnvGame.mGameData->GetViewSystemSettingData();
		m_SystemSettingPageData = gEnvGame.mGameData->GetViewSystemSettingParamByGame();
  }

  void SystemSettingPage::_setPageControlViewDesc()
  {
		SetSystemSettingCloseEditMiMaPage();

		// ��̨���
		wchar_t wszChar[256] = {0};
		StringHelper::ANSIToUnicode(m_SystemSettingPageData.m_strMachineNo.c_str(), wszChar);
		SetSystemSettingEditEngineCode(wszChar);

		// ����У����
		//SetSystemSettingEditDeCode(L"test");

		// ����
		SetSystemSettingEditMina(L"******");
  }
}