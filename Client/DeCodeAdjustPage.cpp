#include "SystemPrerequisites.h"
#include "DeCodeAdjustPage.h"
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

#define  SetArrayMsgToPageUI(arrayName, arrayMsg)\
	{\
		this->m_pUi->invokeActionscriptArray(arrayName, arrayMsg);\
	}

#define SetMessageToPageUINoParam(control)\
{\
	this->m_pUi->invokeActionscript( control );\
	}
  DeCodeAdjustPage::DeCodeAdjustPage()
	  : m_iCurOperState(EInCoinsRatio)
	  , m_iCurParamState(1)
	  , m_pUi(NULL)
	  , m_pCurState(NULL)
	  , m_bVisibleTips(NULL)
	  , m_fTime(0.0f)
  {
  }

  DeCodeAdjustPage::~DeCodeAdjustPage()
  {
    SafeDelete(m_pUi);
	SafeDelete(m_pCurState);
  }

  void DeCodeAdjustPage::Initialize(IUiElement* ui, UIState* state)
  {
    m_pUi = ui;
	m_pCurState = state;
  }

  void DeCodeAdjustPage::injectAppMsg( uint uMsg, int wParam, int lParam )
  {
    switch(uMsg)
    {
    case WM_KEYDOWN:
      {
        switch(wParam)
        {
        case VK_ESCAPE:
			{
				DeCodeAdjustPageReturnToTestMainPage();
			}
			break;
		case VK_UP:
			{
				m_iCurParamState = 1;
			}
			break;
		case VK_DOWN:
			{
				m_iCurParamState = 1;
			}
			break;
        }
        break;
      }
    }
  }

  void DeCodeAdjustPage::update( float timeLapse )
  {
		if(m_bVisibleTips)
		{
			m_fTime += timeLapse;
			if (m_fTime> LEAVESECOND)
			{
				m_bVisibleTips = false;
				SetMessageToPageUINoParam("DeCodeAdjustPageSetCloseTipsTxt");
				m_fTime = 0.0f;
			}
		}
  }

  bool DeCodeAdjustPage::DeCodeAdjustPageCompelete(const Message::Base& msg)
  {
    m_pCurState->changeCurState(this);
    _getViewDeCodeAdjust();
    _setPageControlViewDesc();
	gEnvGame.mGameData->GetCurrentDeAdjustByGame();
	SetMessageToPageUINoParam("DeCodeAdjustPageSetCloseTipsTxt");
	m_bVisibleTips = false;
    return true;
  }

  bool DeCodeAdjustPage::SceneTypeBtn_Click(const Message::Base& msg)
  {
    return true;
  }

  bool DeCodeAdjustPage::PlayCodeDaysBtn_Click(const Message::Base& msg)
  {
    return true;
  }

  bool DeCodeAdjustPage::SystemTimeBtn_Click(const Message::Base& msg)
  {
    return true;
  }

  bool DeCodeAdjustPage::PostCodeSucessBtn_Click(const Message::Base& msg)
  {
    return true;
  }

  bool DeCodeAdjustPage::DeCodeCheckBtn_Click(const Message::Base& msg)
  {
		// �������ر���ֱ�ӱ���
		if (gEnvGame.mGameData->GetPostCodeOnOff() == 1)
		{
			SetDeCodeAdjustVisiblePage(ESubPage_2);
		}
		else
		{
			if(gEnvGame.mGameData->SaveDeCodeAdjustParam() == true)
			{
				// �޸���Ϸ��Ͷ�ұ���
				gEnvGame.mGameBackParam->setInCoins(gEnvGame.mGameData->GetGameCurInCoinsRatio());
				if(gEnvGame.mGameData->GetDeCodeAdjustParamData().m_bVisibleSucess == true)
				{
					// ��ʾ�ɹ���ʾ
					SetDeCodeAdjustPageTipsTxt( L"����ɹ�.");
					m_bVisibleTips = true;
				}
			}
		}
		return true;
  }

  bool DeCodeAdjustPage::ExitDeCodeBtn_Click(const Message::Base& msg)
  {
    SetMessageToPageUI("SetVisibleMainPage", true);
    return true;
  }

  bool DeCodeAdjustPage::KeyEnterBtn_Click(const Message::Base& msg)
  {
	  // ͨ������õ�
	  // ����
	  gEnvGame.mGameData->SaveDeCodeAdjustParam();
	  return true;
  }

  bool DeCodeAdjustPage::Btn_DeCodeLeftClick(const Message::Base& msg)
  {
	  const UiMessage& uiMsg = static_cast< const UiMessage& >( msg );
	  m_iCurOperState = uiMsg[0].get<double>();
	  _setCurOperParam(true);
	  return true;
  }
  bool DeCodeAdjustPage::Btn_DeCodeRightClick(const Message::Base& msg)
  {
	  const UiMessage& uiMsg = static_cast< const UiMessage& >( msg );
	  m_iCurOperState = uiMsg[0].get<double>();
	  _setCurOperParam(false);
	  return true;
  }


  void DeCodeAdjustPage::SetDeCodeAdjustVisiblePage(Real msg)
  {
    SetMessageToPageUI("SetDeCodeAdjustVisiblePage", msg);
  }

  void DeCodeAdjustPage::SetDeCodeAdjustInCoinsRatioDesc(const WString& msg)
  {
    SetMessageToPageUI("SetDeCodeAdjustInCoinsRatioDesc", msg);
  }

  void DeCodeAdjustPage::SetDeCodeAdjustSenceTypeDesc(const WString& msg)
  {
    SetMessageToPageUI("SetDeCodeAdjustSenceTypeDesc", msg);
  }

  void DeCodeAdjustPage::SetDeCodeAdjustPostCodeDaysDesc(const WString& msg)
  {
    SetMessageToPageUI("SetDeCodeAdjustPostCodeDaysDesc", msg);
  }

  void DeCodeAdjustPage::SetDeCodeAdjustSystemTimesDesc(const WString& msg)
  {
    SetMessageToPageUI("SetDeCodeAdjustSystemTimesDesc", msg);
  }

  void DeCodeAdjustPage::SetDeCodeAdjustCodeVisible(const WString& msg)
  {
    SetMessageToPageUI("SetDeCodeAdjustCodeVisible", msg);
  }

  void DeCodeAdjustPage::SetDeCodeAdjustPageTipsTxt(const WString& msg)
  {
	  SetMessageToPageUI("DeCodeAdjustPageSetTipsTxt", msg);
  }

  void DeCodeAdjustPage::SetDeCodeAdjustPagePostCodeOnOffTxt(const WString& msg)
  {
	  SetMessageToPageUI("DeCodeAdjustPageSetPostCodeOnOffTxt", msg);
  }

  void DeCodeAdjustPage::SetDeCodeAdjustInputCode(const WString& msg)
  {
    SetMessageToPageUI("SetDeCodeAdjustInputCode", msg);
  }

  void DeCodeAdjustPage::SetDeCodeAdjustEditDeCode(const WString& msg)
  {
    SetMessageToPageUI("SetDeCodeAdjustCheck", msg);
  }

  void DeCodeAdjustPage::DeCodeAdjustPageReturnToTestMainPage()
  {
    this->m_pUi->invokeActionscript( "DeCodeAdjustPageReturnToTestMainPage" );
  }

  void DeCodeAdjustPage::_getViewDeCodeAdjust()
  {
	  IDataBaseTable *table = gEnvGame.mGameSql->GetViewDeCodeAdjustData();
	  if (table)
	  {
		  m_DeCodeAdjustData.m_strInCoinsRatio = "1:" + table->toString(0, "InCoinsRatio") + "��";
		  m_DeCodeAdjustData.m_strSceneType = table->toString(0, "SceneDesc");
		  m_DeCodeAdjustData.m_strPostCodeDays = table->toString(0, "DaysDesc") + "��";
		  m_DeCodeAdjustData.m_strSystemTime = "2013-5-1 00:00:00";
		  m_DeCodeAdjustData.m_bPostCodeTips = table->toInt32(0, "PostCodeTips");
		  m_DeCodeAdjustData.m_bPostCodeOnOff = table->toInt32(0, "PostCodeOnOff");
	  }
  }

  void DeCodeAdjustPage::_setInCoinsRatioArray()
  {
	  // ��ǰ��
	  SetMessageToPageUI("DeCodeAdjustPageSetCurInCoins", 3);
		//DeCodeAdjustPageSetCurInCoins
	  UiMessage exMsg(gEnvGame.mGameData->GetCoinsRatioNum());
	  for (int i = 0; i< gEnvGame.mGameData->GetCoinsRatioNum(); ++i)
	  {
			int64 iValue = gEnvGame.mGameData->GetCoinsRatio(i+1)->m_iInCoinsRatio;
			exMsg[i] = iValue;
	  }
	  SetArrayMsgToPageUI("mcDeCodeAdjustPage.InCoinsArray", exMsg);
	  SetMessageToPageUINoParam("DeCodeAdjustPageSetCurInCoinsShowDesc");
  }

  void DeCodeAdjustPage::_setPageControlViewDesc()
  {
    // ����ҳ
    SetDeCodeAdjustVisiblePage(ESubPage_1);

    // Ͷ�ұ���
	//_setInCoinsRatioArray();
    wchar_t wszChar[256] = {0};
    StringHelper::ANSIToUnicode(m_DeCodeAdjustData.m_strInCoinsRatio.c_str(), wszChar);
    SetDeCodeAdjustInCoinsRatioDesc(wszChar);

    // ��������
    StringHelper::ANSIToUnicode(m_DeCodeAdjustData.m_strSceneType.c_str(), wszChar);
    SetDeCodeAdjustSenceTypeDesc(wszChar);

    // ��������
    StringHelper::ANSIToUnicode(m_DeCodeAdjustData.m_strPostCodeDays.c_str(), wszChar);
    SetDeCodeAdjustPostCodeDaysDesc(wszChar);

    // ϵͳʱ��
    StringHelper::ANSIToUnicode(m_DeCodeAdjustData.m_strSystemTime.c_str(), wszChar);
    SetDeCodeAdjustSystemTimesDesc(wszChar);

    // ���������
    SetDeCodeAdjustEditDeCode(L"test");

    // ����ɹ���ʾ
    WString wstrVisibleDesc = L"";
    wstrVisibleDesc = m_DeCodeAdjustData.m_bPostCodeTips == 1?L"��ʾ":L"����ʾ";
    SetDeCodeAdjustCodeVisible(wstrVisibleDesc);

	// ���뿪��
	wstrVisibleDesc = m_DeCodeAdjustData.m_bPostCodeOnOff ==1?L"��":L"��";
	SetDeCodeAdjustPagePostCodeOnOffTxt(wstrVisibleDesc);
  }

  int DeCodeAdjustPage::_getCurOperState()
  {
	  return m_iCurOperState;
  }

  void DeCodeAdjustPage::_setCurOperParam(bool pressDir)
  {
	  switch (_getCurOperState())
	  {
	  case EInCoinsRatio:
		  {
			  if (pressDir)
			  {
				  m_iCurParamState--;
				  m_iCurParamState = m_iCurParamState<1?gEnvGame.mGameData->GetCoinsRatioNum():m_iCurParamState;
			  }
			  else
			  {
				  m_iCurParamState++;
				  m_iCurParamState = m_iCurParamState>gEnvGame.mGameData->GetCoinsRatioNum()?1:m_iCurParamState;
			  }
			  _setInCoinsRatio(m_iCurParamState);
		  }
		  break;
	  case ESceneType:
		  {
			  if (pressDir)
			  {
				  m_iCurParamState--;
				  m_iCurParamState = m_iCurParamState<1?gEnvGame.mGameData->GetSceneTypeNum():m_iCurParamState;
			  }
			  else
			  {
				  m_iCurParamState++;
				  m_iCurParamState = m_iCurParamState>gEnvGame.mGameData->GetSceneTypeNum()?1:m_iCurParamState;
			  }
			  _setSceneType(m_iCurParamState);
		  }
		  break;
	  case EPostCodeDays:
		  {
			  if (pressDir)
			  {
				  m_iCurParamState--;
				  m_iCurParamState = m_iCurParamState<1?gEnvGame.mGameData->GetPostCodeNum():m_iCurParamState;
			  }
			  else
			  {
				  m_iCurParamState++;
				  m_iCurParamState = m_iCurParamState>gEnvGame.mGameData->GetPostCodeNum()?1:m_iCurParamState;
			  }
			  _setPostCodeDays(m_iCurParamState);
		  }
		  break;
	  case ESystemTime:
		  {
		  }
		  break;
	  case EDeCodeCheck:
		  {
		  }
		  break;
	  case EPostSucessTips:
		  {
			  if (pressDir)
			  {
				  m_iCurParamState--;
				  m_iCurParamState = m_iCurParamState<0?1:m_iCurParamState;
			  }
			  else
			  {
				  m_iCurParamState++;
				  m_iCurParamState = m_iCurParamState>1?0:m_iCurParamState;
			  }
			  _setVisibleSuccess(m_iCurParamState);
		  }
		  break;
	  case EPostCodeOnOff:
		  {
			  if (pressDir)
			  {
				  m_iCurParamState--;
				  m_iCurParamState = m_iCurParamState<0?1:m_iCurParamState;
			  }
			  else
			  {
				  m_iCurParamState++;
				  m_iCurParamState = m_iCurParamState>1?0:m_iCurParamState;
			  }
			  //_setVisibleSuccess(m_iCurParamState);
		  }
		  break;
	  case EDeCodeAdjust:
		  {
		  }
		  break;
	  }
  }

  void DeCodeAdjustPage::_setInCoinsRatio(int lv)
  {
	  m_pInCoinRaio = gEnvGame.mGameData->GetCoinsRatio(lv);
	  // ������ʾ
	  wchar_t wszChar[256] = {0};
	  StringHelper::ANSIToUnicode(m_pInCoinRaio->m_strInCoinsRatio.c_str(), wszChar);
	  SetDeCodeAdjustInCoinsRatioDesc(wszChar);
  }

  void DeCodeAdjustPage::_setSceneType(int lv)
  {
	  m_pSceneType = gEnvGame.mGameData->GetSceneType(lv);
	  // ������ʾ
	  wchar_t wszChar[256] = {0};
	  StringHelper::ANSIToUnicode(m_pSceneType->m_strDesc.c_str(), wszChar);
	  SetDeCodeAdjustSenceTypeDesc(wszChar);
  }

  void DeCodeAdjustPage::_setPostCodeDays(int lv)
  {
	  m_pPostCodeDays  = gEnvGame.mGameData->GetPostCodeDays(lv);
	  // ������ʾ
	  String strDays = StringConverter::toString(m_pPostCodeDays->DaysDesc) + "��";
	  wchar_t wszChar[256] = {0};
	  StringHelper::ANSIToUnicode(strDays.c_str(), wszChar);
	  SetDeCodeAdjustPostCodeDaysDesc(wszChar);
  }

  void DeCodeAdjustPage::_setVisibleSuccess(int lv)
  {
	  bool bVisibleSuccess = false;
	  if (lv == 0)
	  {
		  SetDeCodeAdjustCodeVisible(L"����ʾ");
		  bVisibleSuccess = false;
	  }
	  else if (lv == 1)
	  {
		  SetDeCodeAdjustCodeVisible(L"��ʾ");
		  bVisibleSuccess = true;
	  }
	  gEnvGame.mGameData->SetVisibleSucessDeCode(bVisibleSuccess);
  }

  void DeCodeAdjustPage::_setPostCodeOnOff(int lv)
  {
	  bool bVisibleSuccess = false;
	  if (lv == 0)
	  {
		  SetDeCodeAdjustPagePostCodeOnOffTxt(L"��");
		  bVisibleSuccess = false;
	  }
	  else if (lv == 1)
	  {
		  SetDeCodeAdjustPagePostCodeOnOffTxt(L"��");
		  bVisibleSuccess = true;
	  }
	  gEnvGame.mGameData->SetPostCodeOnOff(bVisibleSuccess);
  }
}