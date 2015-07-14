#ifndef PARAMSETTINGPAGE_H
#define PARAMSETTINGPAGE_H
#include "IBaseUI.h"

namespace Ogre
{
  struct ParamSettingData
  {
    String  m_strLevelDesc;
    String  m_strMaxBetRatio;
    String  m_strMinBetRatio;
    String  m_strMinChangeRatio;
    String  m_strInCoinsRatio;
    String  m_strUpFenRatio;
    String  m_strDownFenRatio;
    String  m_strBusinessMode;
    String  m_strTicketRatio;
    String  m_strUpLimit;
    String  m_strBrustScore;
    int     m_iOutCoinsFun;
    String  m_strUpDownFenFun;
    int     m_iMusicBgFun;
    int     m_iVoiceFun;
    String  m_strMachineType;
    int     m_iMachineType; // 此数据建议从公共数据中得到
    String  m_strSceneType;
  };

  class ParamSettingPage:public IBaseUI
  {

	  enum OperState
	  {
		  EOper_GameLv = 1, // 游戏难度
		  EOper_MaxBet,
		  EOper_MinBet,
		  EOper_MinChange,
		  EOper_UpRatio,
		  EOper_DownRatio,
		  EOper_TicketRatio,
		  EOper_UpLimit,
		  EOper_BrustScore,
		  EOper_OutCoinsFun,
		  EOper_UpDownFun,
		  EOper_BackMusic,
		  EOper_Voice,
		  EOper_MachineTyp,
		  EOper_SaveExit,
		  EOper_NoSaveExit,
		  EOper_BusinessMode,
	  };
  public:
    ParamSettingPage();
    ~ParamSettingPage();

    virtual void Initialize(IUiElement* ui, UIState* state);
    virtual void injectAppMsg( uint uMsg, int wParam, int lParam );
	virtual void update( float timeLapse );
	//void injectHardwareMsg( HKeyId key, bool down );
    bool ParamSettingPageCompelete(const Message::Base& msg);
	bool GameLevelBtn_Click(const Message::Base& msg);
	bool MaxBetBtn_Click(const Message::Base& msg);
	bool MinBetBtn_Click(const Message::Base& msg);
	bool MinChangeBtn_Click(const Message::Base& msg);
	bool InCoinsScaleBtn_Click(const Message::Base& msg);
	bool UpScoreScaleBtn_Click(const Message::Base& msg);
	bool DownScoreScaleBtn_Click(const Message::Base& msg);
	bool TicketScaleBtn_Click(const Message::Base& msg);
	bool UpLimitBtn_Click(const Message::Base& msg);
	bool BrustScoreBtn_Click(const Message::Base& msg);
	bool InOutCoinsBtn_Click(const Message::Base& msg);
	bool UpDownScoreBtn_Click(const Message::Base& msg);
	bool MuiscBgBtn_Click(const Message::Base& msg);
	bool OpenVoiceBtn_Click(const Message::Base& msg);
	bool MachineTypeBtn_Click(const Message::Base& msg);
	bool SaveExit_Click(const Message::Base& msg);
	bool NoSaveExit_Click(const Message::Base& msg);
	bool Btn_LeftClick(const Message::Base& msg);
	bool Btn_RightClick(const Message::Base& msg);

    void SetParamSettingGameLevelDesc(const WString& msg);
    void SetParamSettingMaxBetDesc(const String& msg);
    void SetParamSettingMinBetDesc(const String& msg);
    void SetParamSettingMinChangeDesc(const String& msg);
    void SetParamSettingInCoinsScaleDesc(const WString& msg);
    void SetParamSettingUpScoreScaleDesc(const WString& msg);
    void SetParamSettingDownScoreScaleDesc(const String& msg);
    void SetParamSettingBusinessModeDesc(const WString& msg);
    void SetParamSettingTicketScaleDesc(const WString& msg);
    void SetParamSettingUpLimitDesc(const String& msg);
    void SetParamSettingBrustScoreDesc(const String& msg);
    void SetParamSettingInOutCoinsDesc(const WString& msg);
    void SetParamSettingUpDownScoreDesc(const WString& msg);
    void SetParamSettingMusicBgDesc(const WString& msg);
    void SetParamSettingOpenVoiceDesc(const WString& msg);
    void SetParamSettingMachineTypeDesc(const WString& msg);
    void SetParamSettingRunTimeDesc(const WString& msg);
    void SetParamSettingUpDownSceneTypeDesc(const WString& msg);
	void SetParamSettingFocusButton(int msg);
	void ParamSettingPageSetVisibleTips(int msg);
	void ParamSettingPageReturnToMainPage();
    
  private:
    void _getViewParamSetting();
    void _setPageControlViewDesc();
	int	 _getCurOperState();
	void _setGameLevel(int lv);
	void _setMaxBetData(int lv);
	void _setMinBetData(int lv);
	void _setMinChangeData(int lv);
	void _setUpRatio(int lv);
	void _setDownRatio(int lv);
	void _setBusinessMode(int lv);
	void _setTicketRatio(int lv);
	void _setUpLimit(int lv);
	void _setBrustScore(int lv);
	void _setOutCoinsFun(int lv);
	void _setUpDownFenFun(int lv);
	void _setBackMusic(int lv);
	void _setVoice(int lv);
	void _setMachineType(int lv);
	void _setCurOperParam(bool pressDir);// 左:true,右:false
	

  private:
    IUiElement*		m_pUi;
	int				m_iCurOperState;
	int				m_iCurParamState;
	GameLevel*		m_pGameLevel;
	MaxBetData*		m_pMaxBetData;
	MinBetData*		m_pMinBetData;
	MinChangeData*	m_pMinChangeData;
	UpRatioData*	m_pUpRatioData;
	DownRatio*		m_pDownRatioData;
	BusinessMode*	m_pBusinessModeData;
	TicketRatio*	m_pTicketRatioData;
	UpLimitData*	m_pUpLimitData;
	BrustScore*		m_pBrustScoreData;
	MachineType*	m_pMachineType;
	UpDownFenData*	m_pUpDownFenData;
	bool			m_bOutCoins;
	bool			m_bBackMusic;
	bool			m_bVoice;
	UIState*		m_pCurState;

    ParamSettingData m_ParamSettingData;
  };
}
#endif