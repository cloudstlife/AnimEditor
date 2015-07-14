#include "SystemPrerequisites.h"
#include "PostMoneyPage.h"
#include "GameBackParam.h"
#include "GameEnvironment.h"
#include "IBaseUI.h"
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

  PostMoneyPage::PostMoneyPage()
	  : m_pUi(NULL)
	  , m_pCurState( NULL )
  {
  }

  PostMoneyPage::~PostMoneyPage()
  {
    SafeDelete(m_pUi);
    SafeDelete(m_pCurState);
  }

  void PostMoneyPage::Initialize(IUiElement* ui, UIState* state)
  {
    m_pUi = ui;
	m_pCurState = state;
  }

  void PostMoneyPage::injectAppMsg( uint uMsg, int wParam, int lParam )
  {
	  switch(uMsg)
	  {
	  case WM_KEYDOWN:
		  {
			  switch(wParam)
			  {
			  case VK_ESCAPE:
				  {
					  PostMoneyPageReturnToMainPage();
				  }
				  break;
			  }
		  }
	  }
  }

  void PostMoneyPage::update( float timeLapse )
  {

  }

  bool PostMoneyPage::PostMoneyPageCompelete(const Message::Base& msg)
  {
		// ��������
		m_pCurState->changeCurState(this);
		_getViewPostMoneyTop();
		_getPostMoneyData();
		_setPageControlViewDesc();
		return true;
  }

  bool PostMoneyPage::PostCodeNoBtn_Click(const Message::Base& msg)
  {
		SetVisiblePage(ESubPage_2);
		return true;
  }

  bool PostMoneyPage::Save_ExitBtn_Click(const Message::Base& msg)
  {
		SetMessageToPageUI("SetVisibleMainPage", true);
		return true;
  }

  bool PostMoneyPage::PostMoneyEnter_Click(const Message::Base& msg)
  {
		const UiMessage& uiMsg = static_cast< const UiMessage& >( msg );
		String strPostCode = uiMsg[0].get<String>();

		// �Ա��������У����

		//////to do//

		// ����ӯ=�Ϸ�+Ͷ��-�·�-�˱�-��Ʊ
		int64 iTotalProfit = gEnvGame.mGameData->GetGameTotalProfit();
		int64 iTotalUpFen = gEnvGame.mGameData->GetGameTotalUpFen();
		int64 iTotalDownFen = gEnvGame.mGameData->GetGameTotalDownFen();
		int64 iTotalInCoins = gEnvGame.mGameData->GetGameTotalInCoinsNum();
		int64 iTotalOutCoins = gEnvGame.mGameData->GetGameTotalOutCoinsNum();
		int64 iTotalTicketNum = gEnvGame.mGameData->GetGameTotalTicketNum();

		// �����ϴ���ӯ��
		String strTotalCurProfit = _int64ToString(iTotalProfit);
		gEnvGame.mGameSql->UpdatePreProfit(strTotalCurProfit);

		iTotalProfit = (iTotalUpFen + iTotalInCoins - iTotalDownFen - iTotalOutCoins - iTotalTicketNum);
		String strTotalProfit = _int64ToString(iTotalProfit);
		gEnvGame.mGameSql->UpdateTotalProfit(strTotalProfit);

		// ���±������
		int iPostCodeCount = gEnvGame.mGameData->GetGameTotalPostCodeNum();
		iPostCodeCount++;// ����+1
		String strPostCodeCount = StringConverter::toString(iPostCodeCount);
		gEnvGame.mGameSql->UpdatePostCodeCount(strPostCodeCount);
		// ��ձ���ӯ��
		gEnvGame.mGameBackParam->reSetCurretProfit();

		// ˢ������
		_getViewPostMoneyTop();
		_getPostMoneyData();
		_setPageControlViewDesc();
		return true;
  }

  void PostMoneyPage::SetVisiblePage(Real msg)
  {
		SetMessageToPageUI("SetPostVisiblePage", msg);
  }

  void PostMoneyPage::SetTotalGainNum(const WString& msg)
  {
		SetMessageToPageUI("SetPostTotalProfitDesc", msg);
  }

  void PostMoneyPage::SetCurMoney(const WString& msg)
  {
		SetMessageToPageUI("SetPostCurrentProfitDesc", msg);
  }

  void PostMoneyPage::SetMachineNo(const String& msg)
  {
		SetMessageToPageUI("SetPostMachineNoDesc", msg);
  }

  void PostMoneyPage::SetSendCount(int msg)
  {
		SetMessageToPageUI("SetPostCodeCountDesc", msg);
  }

  void PostMoneyPage::SetBusinessMode(const WString& msg)
  {
		SetMessageToPageUI("SetPostBusinessMode", msg);
  }

  void PostMoneyPage::SetInCoinsRatio(const WString& msg)
  {
		SetMessageToPageUI("SetPostInCoinsRatioDesc", msg);
  }

  void PostMoneyPage::SetTicketRation(const WString& msg)
  {
		SetMessageToPageUI("SetPostTicketRatioDesc", msg);
  }

  void PostMoneyPage::SetVerifyCode(const String& msg)
  {
		SetMessageToPageUI("SetPostVerifyCodeDesc", msg);
  }

  void PostMoneyPage::_getViewPostMoneyTop()
  {
		IDataBaseTable* table = gEnvGame.mGameData->GetViewCheckAccountTop();
		if (table)
		{
			m_PostMoneyData_Top.m_strInCoinsRatio = "1:" + table->toString(0, "InCoinsRatio");
			m_PostMoneyData_Top. m_strModeDesc = table->toString(0, "ModeDesc");
			m_PostMoneyData_Top.m_strTicketRatio = "1:" + table->toString(0, "TicketRatio");
		}
  }

  void PostMoneyPage::PostMoneyPageReturnToMainPage()
  {
		SetMessageToPageUIByNoParam("PostMoneyPageReturnToMainPage");
  }

  void PostMoneyPage::_getPostMoneyData()
  {
		IDataBaseTable *table = gEnvGame.mGameData->GetPostMessageData();
		if (table)
		{
			m_PostMoneyData.m_iTotalProfit = table->toInt64(0, "TotalProfit");
			m_PostMoneyData.m_iCurrentProfit = table->toInt64(0, "CurrentProfit");
			m_PostMoneyData.m_strMachineNo = table->toString(0, "MachineNo");
			m_PostMoneyData.m_iPostCodeCount = table->toInt32(0, "PostCodeCount");
		}
  }

  void PostMoneyPage::_setPageControlViewDesc()
  {
		// Ӫҵģʽ
		wchar_t wszChar[256] = {0};
		StringHelper::ANSIToUnicode(m_PostMoneyData_Top. m_strModeDesc.c_str(), wszChar);
		SetBusinessMode(wszChar);

		// Ͷ�ұ���
		memset(wszChar,0, sizeof(wszChar));
		StringHelper::ANSIToUnicode(m_PostMoneyData_Top.m_strInCoinsRatio.c_str(), wszChar);
		wcscat_s(wszChar, L"��");
		SetInCoinsRatio(wszChar);

		// ��Ʊ����
		memset(wszChar,0, sizeof(wszChar));
		StringHelper::ANSIToUnicode(m_PostMoneyData_Top.m_strTicketRatio.c_str(), wszChar);
		wcscat_s(wszChar, L"��");
		SetTicketRation(wszChar);
		// ��ǰҳ
		SetVisiblePage( ESubPage_1 );

		// ȫ����ӯ��
		String strTotalProfit = _int64ToString(m_PostMoneyData.m_iTotalProfit);
		strTotalProfit += "��";
		memset(wszChar,0, sizeof(wszChar));
		StringHelper::ANSIToUnicode(strTotalProfit.c_str(), wszChar);
		SetTotalGainNum(wszChar);

		// ����ʵ������
		String strCurrentProfit = _int64ToString(m_PostMoneyData.m_iCurrentProfit);
		strCurrentProfit += "��";
		memset(wszChar,0, sizeof(wszChar));
		StringHelper::ANSIToUnicode(strCurrentProfit.c_str(), wszChar);
		SetCurMoney(wszChar);
		// ��̨����
		SetMachineNo(m_PostMoneyData.m_strMachineNo);
		// �������
		SetSendCount(m_PostMoneyData.m_iPostCodeCount);
		// ������
		SetVerifyCode("test");
  }

  String PostMoneyPage::_int64ToString(int64 val)
  {
		char buffer[32] = {0};
		String retStr;
		memset(buffer, 0, sizeof(buffer));
		sprintf_s(buffer, "%I64d", val);
		retStr = buffer;
		return retStr;
  }
}