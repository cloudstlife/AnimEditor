#include "SystemPrerequisites.h"
#include "CheckAccountPage.h"
#include "GameEnvironment.h"
#include "UIState.h"

namespace Ogre
{
#define SetMessageToPageUI(control, showMsg)\
  {\
  this->m_pUi->invokeActionscript( control, showMsg );\
  }

#define SetMessageToPageUIByNoParam(control)\
	{\
	this->m_pUi->invokeActionscript( control );\
}
  CheckAccountPage::CheckAccountPage()
  {
    m_pUi = NULL;
	m_pCurState = NULL;
  }

  CheckAccountPage::~CheckAccountPage()
  {
    SafeDelete(m_pUi);
    SafeDelete(m_pCurState);
  }

  void CheckAccountPage::Initialize(IUiElement* ui, UIState* state)
  {
    m_pUi = ui;
	m_pCurState = state;
  }

  void CheckAccountPage::injectAppMsg( uint uMsg, int wParam, int lParam )
  {
	  switch(uMsg)
	  {
	  case WM_KEYDOWN:
		  {
			  switch(wParam)
			  {
			  case VK_ESCAPE:
				  {
					  CheckAccountPageReturnToMainPage();
				  }
				  break;
			  }
		  }
	  }
  }

  void CheckAccountPage::update( float timeLapse )
  {

  }

  bool CheckAccountPage::CheckAccountPageCompelete(const Message::Base& msg)
  {
	// ����״̬
	m_pCurState->changeCurState(this);
    // ��������
	_getViewCheckAccountTop();
	_getCheckAccoutData();
	_setPageControlViewDesc();
    return true;
  }

  void CheckAccountPage::SetBusinessMode(const WString& msg)
  {
    SetMessageToPageUI("SetBusinessMode", msg);
  }

  void CheckAccountPage::SetInCoinsRatio(const String& msg)
  {
    SetMessageToPageUI("SetInCoinNum_top", msg);
  }

  void CheckAccountPage::SetTicketRation(const String& msg)
  {
    SetMessageToPageUI("SetMoneyNum_top", msg);
  }

  void CheckAccountPage::SetTotalGainNum(const String& msg)
  {
    SetMessageToPageUI("SetTotalGainNum", msg);
  }

  void CheckAccountPage::SetPreTotalGainNum(const String& msg)
  {
    SetMessageToPageUI("SetPreTotalGainNum", msg);
  }

  void CheckAccountPage::SetCurMoney(const String& msg)
  {
    SetMessageToPageUI("SetCurMoney", msg);
  }

  void CheckAccountPage::SetPreFen(const String& msg)
  {
    SetMessageToPageUI("SetPreFen", msg);
  }

  void CheckAccountPage::SetNextFen(const String& msg)
  {
    SetMessageToPageUI("SetNextFen", msg);
  }

  void CheckAccountPage::SetInCoinNum(const String& msg)
  {
    SetMessageToPageUI("SetInCoinNum", msg);
  }

  void CheckAccountPage::SetOutCoin(const String& msg)
  {
    SetMessageToPageUI("SetOutCoin", msg);
  }

  void CheckAccountPage::SetMoneyNum(const String& msg)
  {
    SetMessageToPageUI("SetMoneyNum", msg);
  }

  void CheckAccountPage::SetLineNo(const String& msg)
  {
    SetMessageToPageUI("SetLineNo", msg);
  }

  void CheckAccountPage::SetEngineCode(const String& msg)
  {
    SetMessageToPageUI("SetEngineCode", msg);
  }

  void CheckAccountPage::SetLeaveRunTime(const String& msg)
  {
    SetMessageToPageUI("SetLeaveRunTime", msg);
  }

  void CheckAccountPage::SetSendCount(int msg)
  {
    SetMessageToPageUI("SetSendCount", msg);
  }

  void CheckAccountPage::SetInCoinNum_top(const String& msg)
  {
    SetMessageToPageUI("SetInCoinNum_top", msg);
  }

  void CheckAccountPage::SetMoneyNum_top(const String& msg)
  {
    SetMessageToPageUI("SetMoneyNum_top", msg);
  }

  void CheckAccountPage::CheckAccountPageReturnToMainPage()
  {
		SetMessageToPageUIByNoParam("CheckAccountPageReturnToMainPage");
  }

  void CheckAccountPage::_getViewCheckAccountTop()
  {
	  IDataBaseTable* table = gEnvGame.mGameData->GetViewCheckAccountTop();
	  if (table)
	  {
		  m_CheckAccountData_Top.m_strInCoinsRatio = "1:" + table->toString(0, "InCoinsRatio");
		  m_CheckAccountData_Top. m_strModeDesc = table->toString(0, "ModeDesc");
		  m_CheckAccountData_Top.m_strTicketRatio = "1:" + table->toString(0, "TicketRatio");
	  }
  }

  void CheckAccountPage::_getCheckAccoutData()
  {
	  IDataBaseTable* table = gEnvGame.mGameData->GetCheckAccountData();
	  if (table)
	  {
		  m_CheckAccountData.m_iTotalProfit = table->toInt64(0, "TotalProfit");
		  m_CheckAccountData.m_iPreProfit = table->toInt64(0, "PreProfit");
		  m_CheckAccountData.m_iCurrentProfit = table->toInt64(0, "CurrentProfit");
		  m_CheckAccountData.m_iUpPoints = table->toInt64(0, "UpPoints");
		  m_CheckAccountData.m_iDownPoints = table->toInt64(0, "DownPoints");
		  m_CheckAccountData.m_iInCoins = table->toInt64(0, "InCoins");
		  m_CheckAccountData.m_iOutCoins = table->toInt64(0, "OutCoins");
		  m_CheckAccountData.m_iRaffleTickets = table->toInt64(0, "RaffleTickets");
		  m_CheckAccountData.m_iPostCodeCount = table->toInt32(0, "PostCodeCount");
	  }
  }

  void CheckAccountPage::_setPageControlViewDesc()
  {
    // Ӫҵģʽ
    wchar_t wszChar[256] = {0};
    StringHelper::ANSIToUnicode(m_CheckAccountData_Top. m_strModeDesc.c_str(), wszChar);
    SetBusinessMode(wszChar);

    // Ͷ�ұ���
    SetInCoinsRatio(m_CheckAccountData_Top.m_strInCoinsRatio);

    // ��Ʊ����
    SetTicketRation(m_CheckAccountData_Top.m_strTicketRatio);

    // ȫ����ӯ��
	String strTotalProfit = _int64ToString(m_CheckAccountData.m_iTotalProfit);
    SetTotalGainNum(strTotalProfit);

    // �ϴ���ӯ��
	String strPreProfit = _int64ToString(m_CheckAccountData.m_iPreProfit);
    SetPreTotalGainNum(strPreProfit);

    // ����ʵ������
	String strCurrentProfit = _int64ToString(m_CheckAccountData.m_iCurrentProfit);
    SetCurMoney(strCurrentProfit);

    // �Ϸ�
	String strUpPoints = _int64ToString(m_CheckAccountData.m_iUpPoints);
    SetPreFen(strUpPoints);

    // �·�
	String strDownPoints = _int64ToString(m_CheckAccountData.m_iDownPoints);
    SetNextFen(strDownPoints);

    // Ͷ��
	String strInCoins = _int64ToString(m_CheckAccountData.m_iInCoins);
    SetInCoinNum(strInCoins);

    // �˱�
	String strOutCoins = _int64ToString(m_CheckAccountData.m_iOutCoins);
    SetOutCoin(strOutCoins);

    // ��Ʊ
	String strRaffleTickets = _int64ToString(m_CheckAccountData.m_iRaffleTickets);
    SetMoneyNum(strRaffleTickets);

    // �ߺ�
    SetLineNo(gEnvGame.mGameData->GetViewSystemSettingParamByGame().m_strLineNo);
    // ʣ��ʱ��
    SetLeaveRunTime("2013");
    // �������
    SetSendCount(m_CheckAccountData.m_iPostCodeCount);
  }

  String CheckAccountPage::_int64ToString(int64 val)
  {
	  char buffer[32] = {0};
	  String retStr;
	  memset(buffer, 0, sizeof(buffer));
	  sprintf_s(buffer, "%I64d", val);
	  retStr = buffer;
	  return retStr;
  }
}