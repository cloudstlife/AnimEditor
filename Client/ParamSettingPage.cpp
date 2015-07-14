#include "SystemPrerequisites.h"
#include "ParamSettingPage.h"
#include "GameBackParam.h"
#include "GameEnvironment.h"
#include "UIState.h"

namespace Ogre
{
#define SetMessageToPageUI(control, showMsg)\
  {\
  this->m_pUi->invokeActionscript( control, showMsg );\
  }

#define SetMessageToPageUI_NoParam(control)\
	{\
		this->m_pUi->invokeActionscript( control );\
	}

  ParamSettingPage::ParamSettingPage()
	  : m_iCurOperState(EOper_GameLv)
	  , m_iCurParamState(1)
	  , m_pGameLevel(NULL)
	  , m_pMaxBetData(NULL)
	  , m_pMinBetData(NULL)
	  , m_pMinChangeData(NULL)
	  , m_pUpRatioData(NULL)
	  , m_pDownRatioData(NULL)
	  , m_pBusinessModeData(NULL)
	  , m_pTicketRatioData(NULL)
	  , m_pUpLimitData(NULL)
	  , m_pBrustScoreData(NULL)
	  , m_pMachineType(NULL)
	  , m_pUpDownFenData(NULL)
	  , m_bOutCoins(false)
	  , m_bBackMusic(false)
	  , m_bVoice(false)
	  , m_pUi(NULL)
	  , m_pCurState(NULL)
  {
  }

  ParamSettingPage::~ParamSettingPage()
  {
   
  }

  void ParamSettingPage::Initialize(IUiElement* ui, UIState* state)
  {
    m_pUi = ui;
    m_pCurState = state;
  }
	
  /*void ParamSettingPage::injectHardwareMsg( HKeyId key, bool down )
  {
		if ( key == HKI_Ctl_Down )
		{
			if ( down )
			{
				injectAppMsg( WM_KEYDOWN, VK_UP, 0 );
			}
			else
			{
				injectAppMsg( WM_KEYUP, VK_UP, 0 );
			}
			
		}
  }*/

  void ParamSettingPage::injectAppMsg( uint uMsg, int wParam, int lParam )
  {
	  if ( uMsg == WM_KEYDOWN )
	  {
			if (wParam == VK_UP)
			{
				m_iCurParamState = 1;
			}
			else if (wParam == VK_DOWN)
			{
				m_iCurParamState = 1;
			}
	  }
	  //{
		 // // 参数项选择(循环设置)
		 // if (wParam == VK_UP && GetAsyncKeyState(VK_CONTROL))
		 // {
			//  m_iCurOperState--;
			//  m_iCurOperState = m_iCurOperState<EOper_GameLv?EOper_GameLv:m_iCurOperState;
			//  m_iCurParamState = 1;
			//  SetParamSettingFocusButton(m_iCurOperState);
		 // }
		 // else if(wParam == VK_DOWN && GetAsyncKeyState(VK_CONTROL))
		 // {
			//  m_iCurOperState++;
			//  m_iCurOperState = m_iCurOperState>EOper_NoSaveExit?EOper_NoSaveExit:m_iCurOperState;
			//  m_iCurParamState = 1;
			//  SetParamSettingFocusButton(m_iCurOperState);
		 // }
		 // // 对应数据项选择
		 // else if (wParam == VK_LEFT && GetAsyncKeyState(VK_CONTROL))
		 // {
			//  _setCurOperParam(true);
		 // }
		 // else if (wParam == VK_RIGHT && GetAsyncKeyState(VK_CONTROL))
		 // {
			//  _setCurOperParam(false);
		 // }
		 // else if (wParam == VK_END && GetAsyncKeyState(VK_CONTROL))
		 // {
			//  if (m_iCurOperState == EOper_SaveExit)
			//  {
			//	  //SaveExit_Click();
			//  }
			//  else if (m_iCurOperState == EOper_NoSaveExit)
			//  {
			//	  //NoSaveExit_Click();
			//  }
		 // }
	  //}
  }

  void ParamSettingPage::update( float timeLapse )
  {

  }

  bool ParamSettingPage::ParamSettingPageCompelete(const Message::Base& msg)
  {
		m_pCurState->changeCurState(this);
		_getViewParamSetting();
		_setPageControlViewDesc();
		gEnvGame.mGameData->GetCurrentGameParmByGame();
		return true;
  }

  bool ParamSettingPage::GameLevelBtn_Click(const Message::Base& msg)
  {
		return true;
  }

  bool ParamSettingPage::MaxBetBtn_Click(const Message::Base& msg)
  {
		return true;
  }

  bool ParamSettingPage::MinBetBtn_Click(const Message::Base& msg)
  {
		return true;
  }

  bool ParamSettingPage::MinChangeBtn_Click(const Message::Base& msg)
  {
		return true;
  }

  bool ParamSettingPage::InCoinsScaleBtn_Click(const Message::Base& msg)
  {
		return true;
  }

  bool ParamSettingPage::UpScoreScaleBtn_Click(const Message::Base& msg)
  {
		return true;
  }
  bool ParamSettingPage::DownScoreScaleBtn_Click(const Message::Base& msg)
  {
		return true;
  }

  bool ParamSettingPage::TicketScaleBtn_Click(const Message::Base& msg)
  {
		return true;
  }

  bool ParamSettingPage::UpLimitBtn_Click(const Message::Base& msg)
  {
		return true;
  }

  bool ParamSettingPage::BrustScoreBtn_Click(const Message::Base& msg)
  {
		return true;
  }

  bool ParamSettingPage::InOutCoinsBtn_Click(const Message::Base& msg)
  {
	  return true;
  }

  bool ParamSettingPage::UpDownScoreBtn_Click(const Message::Base& msg)
  {
	  return true;
  }

  bool ParamSettingPage::MuiscBgBtn_Click(const Message::Base& msg)
  {
	  return true;
  }

  bool ParamSettingPage::OpenVoiceBtn_Click(const Message::Base& msg)
  {
	  return true;
  }

  bool ParamSettingPage::MachineTypeBtn_Click(const Message::Base& msg)
  {
	  return true;
  }

  bool ParamSettingPage::SaveExit_Click(const Message::Base& msg)
  {
	  gEnvGame.mGameData->SaveGameParam();
	  ParamSettingPageReturnToMainPage();
	  // 设置游戏运行数据
	  gEnvGame.mGameBackParam->setPlayerNum(gEnvGame.mGameData->GetGamePlayerNum());
	  gEnvGame.mGameBackParam->setMaxBet(gEnvGame.mGameData->GetGameCurMaxBet());
	  gEnvGame.mGameBackParam->setMinBet(gEnvGame.mGameData->GetGameCurMinBet());
	  gEnvGame.mGameBackParam->setMinChange(gEnvGame.mGameData->GetGameCurMinChange());
	  gEnvGame.mGameBackParam->updatePlayerCurrentBet();
	  //gEnvGame.mGameBackParam->setInCoins(gSqlEnv->mGameData->GetGameCurInCoinsRatio());移到解码中
	  return true;
  }

  bool ParamSettingPage::NoSaveExit_Click(const Message::Base& msg)
  {
	  ParamSettingPageReturnToMainPage();
	  return true;
  }

  bool ParamSettingPage::Btn_LeftClick(const Message::Base& msg)
  {
		const UiMessage& uiMsg = static_cast< const UiMessage& >( msg );
		m_iCurOperState = uiMsg[0].get<double>();
		_setCurOperParam(true);
		return true;
  }

  bool ParamSettingPage::Btn_RightClick(const Message::Base& msg)
  {
		const UiMessage& uiMsg = static_cast< const UiMessage& >( msg );
		m_iCurOperState = uiMsg[0].get<double>();
		_setCurOperParam(false);
		return true;
  }

  void ParamSettingPage::SetParamSettingGameLevelDesc(const WString& msg)
  {
    SetMessageToPageUI("SetParamSettingGameLevelDesc", msg);
  }

  void ParamSettingPage::SetParamSettingMaxBetDesc(const String& msg)
  {
    SetMessageToPageUI("SetParamSettingMaxBetDesc", msg);
  }

  void ParamSettingPage::SetParamSettingMinBetDesc(const String& msg)
  {
    SetMessageToPageUI("SetParamSettingMinBetDesc", msg);
  }

  void ParamSettingPage::SetParamSettingMinChangeDesc(const String& msg)
  {
    SetMessageToPageUI("SetParamSettingMinChangeDesc", msg);
  }

  void ParamSettingPage::SetParamSettingInCoinsScaleDesc(const WString& msg)
  {
    SetMessageToPageUI("SetParamSettingInCoinsScaleDesc", msg);
  }

  void ParamSettingPage::SetParamSettingUpScoreScaleDesc(const WString& msg)
  {
    SetMessageToPageUI("SetParamSettingUpScoreScaleDesc", msg);
  }

  void ParamSettingPage::SetParamSettingDownScoreScaleDesc(const String& msg)
  {
    SetMessageToPageUI("SetParamSettingDownScoreScaleDesc", msg);
  }

  void ParamSettingPage::SetParamSettingBusinessModeDesc(const WString& msg)
  {
    SetMessageToPageUI("SetParamSettingBusinessModeDesc", msg);
  }

  void ParamSettingPage::SetParamSettingTicketScaleDesc(const WString& msg)
  {
    SetMessageToPageUI("SetParamSettingTicketScaleDesc", msg);
  }

  void ParamSettingPage::SetParamSettingUpLimitDesc(const String& msg)
  {
    SetMessageToPageUI("SetParamSettingUpLimitDesc", msg);
  }

  void ParamSettingPage::SetParamSettingBrustScoreDesc(const String& msg)
  {
    SetMessageToPageUI("SetParamSettingBrustScoreDesc", msg);
  }

  void ParamSettingPage::SetParamSettingInOutCoinsDesc(const WString& msg)
  {
    SetMessageToPageUI("SetParamSettingInOutCoinsDesc", msg);
  }

  void ParamSettingPage::SetParamSettingUpDownScoreDesc(const WString& msg)
  {
    SetMessageToPageUI("SetParamSettingUpDownScoreDesc", msg);
  }
  
  void ParamSettingPage::SetParamSettingMusicBgDesc(const WString& msg)
  {
    SetMessageToPageUI("SetParamSettingMusicBgDesc", msg);
  }

  void ParamSettingPage::SetParamSettingOpenVoiceDesc(const WString& msg)
  {
    SetMessageToPageUI("SetParamSettingOpenVoiceDesc", msg);
  }

  void ParamSettingPage::SetParamSettingMachineTypeDesc(const WString& msg)
  {
    SetMessageToPageUI("SetParamSettingMachineTypeDesc", msg);
  }

  void ParamSettingPage::SetParamSettingRunTimeDesc(const WString& msg)
  {
    SetMessageToPageUI("SetParamSettingRunTimeDesc", msg);
  }

  void ParamSettingPage::SetParamSettingUpDownSceneTypeDesc(const WString& msg)
  {
    SetMessageToPageUI("SetParamSettingUpDownSceneTypeDesc", msg);
  }

  void ParamSettingPage::SetParamSettingFocusButton(int msg)
  {
		SetMessageToPageUI("SetParamSettingFocusButton", msg);
  }

  void ParamSettingPage::ParamSettingPageSetVisibleTips(int msg)
  {
		SetMessageToPageUI("ParamSettingPageSetVisibleTips", msg);
  }

  void ParamSettingPage::ParamSettingPageReturnToMainPage()
  {
		SetMessageToPageUI_NoParam("ParamSettingPageReturnToMainPage");
  }

  void ParamSettingPage::_getViewParamSetting()
  {
    if (gEnvGame.mGameData)
    {
      IDataBaseTable *table = gEnvGame.mGameData->GetViewParamSettingData();
      if (table)
      {
        m_ParamSettingData.m_strLevelDesc = table->toString(0, "LevelDesc");
        m_ParamSettingData.m_strMaxBetRatio = table->toString(0, "MaxBetRatio");
        m_ParamSettingData.m_strMinBetRatio = table->toString(0, "MinBetRatio");
        m_ParamSettingData.m_strMinChangeRatio = table->toString(0, "MinBetRatio");
        m_ParamSettingData.m_strInCoinsRatio = "1:" + table->toString(0, "InCoinsRatio") + "分";
        m_ParamSettingData.m_strUpFenRatio = table->toString(0, "UpRatio");
        m_ParamSettingData.m_strDownFenRatio = table->toString(0, "DownRatio");
        m_ParamSettingData.m_strBusinessMode = table->toString(0, "ModeDesc");
        m_ParamSettingData.m_strTicketRatio = "1币" + table->toString(0, "TicketRatio") + "彩票";
        m_ParamSettingData.m_strUpLimit = table->toString(0, "UpLimit");
        m_ParamSettingData.m_strBrustScore = table->toString(0, "BrustSocre");
        m_ParamSettingData.m_iOutCoinsFun = table->toInt32(0, "OutCoinFunction");
        m_ParamSettingData.m_strUpDownFenFun = table->toString(0,"desc");
        m_ParamSettingData.m_iMusicBgFun = table->toInt32(0, "MusicBg");
        m_ParamSettingData.m_iVoiceFun = table->toInt32(0, "Voice");
        m_ParamSettingData.m_strMachineType = table->toString(0, "TypeDesc");
        m_ParamSettingData.m_iMachineType = table->toInt32(0, "MachineType");
        m_ParamSettingData.m_strSceneType = table->toString(0, "SceneDesc");
      }
    }
  }

  void ParamSettingPage::_setPageControlViewDesc()
  {
    // 游戏难度
    wchar_t wszChar[256] = {0};
    StringHelper::ANSIToUnicode(m_ParamSettingData.m_strLevelDesc.c_str(), wszChar);
    SetParamSettingGameLevelDesc(wszChar);

    // 最大押注
    SetParamSettingMaxBetDesc(m_ParamSettingData.m_strMaxBetRatio);

    // 最小押注
    SetParamSettingMinBetDesc(m_ParamSettingData.m_strMinBetRatio);

    // 最小切换
    SetParamSettingMinChangeDesc(m_ParamSettingData.m_strMinChangeRatio);

    // 投币比例
	memset(wszChar,0, sizeof(wszChar));
    StringHelper::ANSIToUnicode(m_ParamSettingData.m_strInCoinsRatio.c_str(), wszChar);
    SetParamSettingInCoinsScaleDesc(wszChar);

    // 上分比例
	StringHelper::ANSIToUnicode(m_ParamSettingData.m_strUpFenRatio.c_str(), wszChar);
    SetParamSettingUpScoreScaleDesc(wszChar);

    // 下分比例
    SetParamSettingDownScoreScaleDesc(m_ParamSettingData.m_strDownFenRatio);

    // 营业模式
    StringHelper::ANSIToUnicode(m_ParamSettingData.m_strBusinessMode.c_str(), wszChar);
    SetParamSettingBusinessModeDesc(wszChar);

    // 彩票比例
    StringHelper::ANSIToUnicode(m_ParamSettingData.m_strTicketRatio.c_str(), wszChar);
    SetParamSettingTicketScaleDesc(wszChar);

    // 上分极限
    SetParamSettingUpLimitDesc(m_ParamSettingData.m_strUpLimit);

    // 爆机分数
    SetParamSettingBrustScoreDesc(m_ParamSettingData.m_strBrustScore);

    // 退币开关
    WString wstrVal = L"";
    wstrVal = m_ParamSettingData.m_iOutCoinsFun == 1? L"开":L"关";
    SetParamSettingInOutCoinsDesc(wstrVal);

    // 上下分开关
	StringHelper::ANSIToUnicode(m_ParamSettingData.m_strUpDownFenFun.c_str(), wszChar);
    SetParamSettingUpDownScoreDesc(wszChar);

    // 背景开关
    wstrVal = m_ParamSettingData.m_iMusicBgFun == 1? L"开":L"关";
    SetParamSettingMusicBgDesc(wstrVal);

    // 语单开关
    wstrVal = m_ParamSettingData.m_iVoiceFun == 1? L"开":L"关";
    SetParamSettingOpenVoiceDesc(wstrVal);

    // 机台类型
    StringHelper::ANSIToUnicode(m_ParamSettingData.m_strMachineType.c_str(), wszChar);
    SetParamSettingMachineTypeDesc(wszChar);

	// 机台类型对应图片显示
	ParamSettingPageSetVisibleTips(m_ParamSettingData.m_iMachineType);

    // 运行时间
    //SetParamSettingRunTimeDesc(L"test");

    // 场景类型
    StringHelper::ANSIToUnicode(m_ParamSettingData.m_strSceneType.c_str(), wszChar);
    SetParamSettingUpDownSceneTypeDesc(wszChar);
  }

  int ParamSettingPage::_getCurOperState()
  {
	  return m_iCurOperState;
  }

  void ParamSettingPage::_setGameLevel(int lv)
  {
	  m_pGameLevel = gEnvGame.mGameData->GetGameLevel(lv);
	  // 设置显示
	  wchar_t wszChar[256] = {0};
	  StringHelper::ANSIToUnicode(m_pGameLevel->m_strLevelDesc.c_str(), wszChar);
	  SetParamSettingGameLevelDesc(wszChar);
  }

  void ParamSettingPage::_setMaxBetData(int lv)
  {
	  m_pMaxBetData = gEnvGame.mGameData->GetMaxBetData(lv);
	  // 设置显示
	  SetParamSettingMaxBetDesc(m_pMaxBetData->m_strBetRatio);
  }

  void ParamSettingPage::_setMinBetData(int lv)
  {
	  m_pMinBetData = gEnvGame.mGameData->GetMinBetData(lv);
	  // 设置显示
	  SetParamSettingMinBetDesc(m_pMinBetData->m_strBetRatio);
  }

  void ParamSettingPage::_setMinChangeData(int lv)
  {
	  m_pMinChangeData = gEnvGame.mGameData->GetMinChangeData(lv);
	  // 设置显示
	  SetParamSettingMinChangeDesc(m_pMinChangeData->m_strChangeRatio);
  }

  void ParamSettingPage::_setUpRatio(int lv)
  {
	  m_pUpRatioData = gEnvGame.mGameData->GetUpRatioData(lv);
	  wchar_t wszChar[256] = {0};
	  StringHelper::ANSIToUnicode(m_pUpRatioData->m_strUpRatio.c_str(), wszChar);
	  SetParamSettingUpScoreScaleDesc(wszChar);
  }

  void ParamSettingPage::_setDownRatio(int lv)
  {
	  m_pDownRatioData = gEnvGame.mGameData->GetDownRatioData(lv);
	  SetParamSettingDownScoreScaleDesc(m_pDownRatioData->m_strDownRatio);
  }

  void ParamSettingPage::_setBusinessMode(int lv)
  {
	  m_pBusinessModeData = gEnvGame.mGameData->GetBusinessModeData(lv);
	  wchar_t wszChar[256] = {0};
	  StringHelper::ANSIToUnicode(m_pBusinessModeData->m_strModeDesc.c_str(), wszChar);
	  SetParamSettingBusinessModeDesc(wszChar);
  }

  void ParamSettingPage::_setTicketRatio(int lv)
  {
	  m_pTicketRatioData = gEnvGame.mGameData->GetTicketRatioData(lv);
	  wchar_t wszChar[256] = {0};
	  StringHelper::ANSIToUnicode(m_pTicketRatioData->m_strTicketRatio.c_str(), wszChar);
	  SetParamSettingTicketScaleDesc(wszChar);
  }

  void ParamSettingPage::_setUpLimit(int lv)
  {
	  m_pUpLimitData = gEnvGame.mGameData->GetUpLimitData(lv);
	  SetParamSettingUpLimitDesc(m_pUpLimitData->m_strUpLimit);
  }

  void ParamSettingPage::_setBrustScore(int lv)
  {
	  m_pBrustScoreData = gEnvGame.mGameData->GetBrustScoreData(lv);
	  SetParamSettingBrustScoreDesc(m_pBrustScoreData->m_strBrustSocre);
  }

  void ParamSettingPage::_setOutCoinsFun(int lv)
  {
	if (lv == 0)
	{
		SetParamSettingInOutCoinsDesc(L"关");
		m_bOutCoins = false;
	}
	else if (lv == 1)
	{
		SetParamSettingInOutCoinsDesc(L"开");
		m_bOutCoins = true;
	}
	gEnvGame.mGameData->SetOutCoinsFun(m_bOutCoins);
  }

  void ParamSettingPage::_setUpDownFenFun(int lv)
  {
	m_pUpDownFenData = gEnvGame.mGameData->GetUpDownFenData(lv);
	wchar_t wszChar[256] = {0};
	StringHelper::ANSIToUnicode(m_pUpDownFenData->m_strDesc.c_str(), wszChar);
	SetParamSettingUpDownScoreDesc(wszChar);
  }

  void ParamSettingPage::_setBackMusic(int lv)
  {
	if (lv == 0)
	{
		SetParamSettingMusicBgDesc(L"关");
		m_bBackMusic = false;
	}
	else if (lv == 1)
	{
		SetParamSettingMusicBgDesc(L"开");
		m_bBackMusic = true;
	}
	gEnvGame.mGameData->SetBackMusic(m_bBackMusic);
  }

  void ParamSettingPage::_setVoice(int lv)
  {
	if (lv == 0)
	{
		SetParamSettingOpenVoiceDesc(L"关");
		m_bVoice = false;
	}
	else if (lv == 1)
	{
		SetParamSettingOpenVoiceDesc(L"开");
		m_bVoice = true;
	}
	gEnvGame.mGameData->SetVoice(m_bVoice);
  }

  void ParamSettingPage::_setMachineType(int lv)
  {
	  m_pMachineType = gEnvGame.mGameData->GetMachineTypeData(lv);
	  ParamSettingPageSetVisibleTips(m_pMachineType->m_iTypeID);
	  wchar_t wszChar[256] = {0};
	  StringHelper::ANSIToUnicode(m_pMachineType->m_strTypeDesc.c_str(), wszChar);
	  SetParamSettingMachineTypeDesc(wszChar);
  }

  void ParamSettingPage::_setCurOperParam(bool pressDir)
  {
	switch (_getCurOperState())
	{
	case EOper_GameLv:
		{
			if (pressDir)
			{
				m_iCurParamState--;
				m_iCurParamState = m_iCurParamState<1?gEnvGame.mGameData->GetGameLeveNum():m_iCurParamState;
			}
			else
			{
				m_iCurParamState++;
				m_iCurParamState = m_iCurParamState>gEnvGame.mGameData->GetGameLeveNum()?1:m_iCurParamState;
			}
			_setGameLevel(m_iCurParamState);
		}
		break;
	case EOper_MaxBet:
		{
			if (pressDir)
			{
				m_iCurParamState--;
				m_iCurParamState = m_iCurParamState<1?gEnvGame.mGameData->GetMaxBetNum():m_iCurParamState;
			}
			else
			{
				m_iCurParamState++;
				m_iCurParamState = m_iCurParamState>gEnvGame.mGameData->GetMaxBetNum()?1:m_iCurParamState;
			}
			_setMaxBetData(m_iCurParamState);
		}
		break;
	case EOper_MinBet:
		{
			if (pressDir)
			{
				m_iCurParamState--;
				m_iCurParamState = m_iCurParamState<1?gEnvGame.mGameData->GetMinBetNum():m_iCurParamState;
			}
			else
			{
				m_iCurParamState++;
				m_iCurParamState = m_iCurParamState>gEnvGame.mGameData->GetMinBetNum()?1:m_iCurParamState;
			}
			_setMinBetData(m_iCurParamState);
		}
		break;
	case EOper_MinChange:
		{
			if (pressDir)
			{
				m_iCurParamState--;
				m_iCurParamState = m_iCurParamState<1?gEnvGame.mGameData->GetMinChangeNum():m_iCurParamState;
			}
			else
			{
				m_iCurParamState++;
				m_iCurParamState = m_iCurParamState>gEnvGame.mGameData->GetMinChangeNum()?1:m_iCurParamState;
			}
			_setMinChangeData(m_iCurParamState);
		}
		break;
	case EOper_UpRatio:
		{
			if (pressDir)
			{
				m_iCurParamState--;
				m_iCurParamState = m_iCurParamState<1?gEnvGame.mGameData->GetUpRatioNum():m_iCurParamState;
			}
			else
			{
				m_iCurParamState++;
				m_iCurParamState = m_iCurParamState>gEnvGame.mGameData->GetUpRatioNum()?1:m_iCurParamState;
			}
			_setUpRatio(m_iCurParamState);
		}
		break;
	case EOper_DownRatio:
		{
			if (pressDir)
			{
				m_iCurParamState--;
				m_iCurParamState = m_iCurParamState<1?gEnvGame.mGameData->GetDownRatioNum():m_iCurParamState;
			}
			else
			{
				m_iCurParamState++;
				m_iCurParamState = m_iCurParamState>gEnvGame.mGameData->GetDownRatioNum()?1:m_iCurParamState;
			}
			_setDownRatio(m_iCurParamState);
		}
		break;
	case EOper_BusinessMode:
		{
			if (pressDir)
			{
				m_iCurParamState--;
				m_iCurParamState = m_iCurParamState<1?gEnvGame.mGameData->GetBusinessNum():m_iCurParamState;
			}
			else
			{
				m_iCurParamState++;
				m_iCurParamState = m_iCurParamState>gEnvGame.mGameData->GetBusinessNum()?1:m_iCurParamState;
			}
			_setBusinessMode(m_iCurParamState);
		}
		break;
	case EOper_TicketRatio:
		{
			if (pressDir)
			{
				m_iCurParamState--;
				m_iCurParamState = m_iCurParamState<1?gEnvGame.mGameData->GetTicketRatioNum():m_iCurParamState;
			}
			else
			{
				m_iCurParamState++;
				m_iCurParamState = m_iCurParamState>gEnvGame.mGameData->GetTicketRatioNum()?1:m_iCurParamState;
			}
			_setTicketRatio(m_iCurParamState);
		}
		break;
	case EOper_UpLimit:
		{
			if (pressDir)
			{
				m_iCurParamState--;
				m_iCurParamState = m_iCurParamState<1?gEnvGame.mGameData->GetUpLimitNum():m_iCurParamState;
			}
			else
			{
				m_iCurParamState++;
				m_iCurParamState = m_iCurParamState>gEnvGame.mGameData->GetUpLimitNum()?1:m_iCurParamState;
			}
			_setUpLimit(m_iCurParamState);
		}
		break;
	case  EOper_BrustScore:
		{
			if (pressDir)
			{
				m_iCurParamState--;
				m_iCurParamState = m_iCurParamState<1?gEnvGame.mGameData->GetBrustNum():m_iCurParamState;
			}
			else
			{
				m_iCurParamState++;
				m_iCurParamState = m_iCurParamState>gEnvGame.mGameData->GetBrustNum()?1:m_iCurParamState;
			}
			_setBrustScore(m_iCurParamState);
		}
		break;
	case EOper_OutCoinsFun:
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
			_setOutCoinsFun(m_iCurParamState);
		}
		break;
	case EOper_UpDownFun:
		{
			if (pressDir)
			{
				m_iCurParamState--;
				m_iCurParamState = m_iCurParamState<1?gEnvGame.mGameData->GetUpDownFenNum():m_iCurParamState;
			}
			else
			{
				m_iCurParamState++;
				m_iCurParamState = m_iCurParamState>gEnvGame.mGameData->GetUpDownFenNum()?1:m_iCurParamState;
			}
			_setUpDownFenFun(m_iCurParamState);
		}
		break;
	case EOper_BackMusic:
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
			_setBackMusic(m_iCurParamState);
		}
		break;
	case EOper_Voice:
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
			_setVoice(m_iCurParamState);
		}
		break;
	case EOper_MachineTyp:
		{
			if (pressDir)
			{
				m_iCurParamState--;
				m_iCurParamState = m_iCurParamState<1?gEnvGame.mGameData->GetMachineTypeNum():m_iCurParamState;
			}
			else
			{
				m_iCurParamState++;
				m_iCurParamState = m_iCurParamState>gEnvGame.mGameData->GetMachineTypeNum()?1:m_iCurParamState;
			}
			_setMachineType(m_iCurParamState);
		}
		break;
	case EOper_SaveExit:
		{

		}
		break;
	case EOper_NoSaveExit:
		{

		}
		break;
	}
  }
}