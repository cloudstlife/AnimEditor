#ifndef DECODEADJUSTPAGE_H
#define DECODEADJUSTPAGE_H
#include "IBaseUI.h"

#define LEAVESECOND 5
namespace Ogre
{
  struct DeCodeAdjustData
  {
    String m_strInCoinsRatio;
    String m_strSceneType;
    String m_strPostCodeDays;
    String m_strSystemTime;
    int	   m_bPostCodeTips; // 打码成功信息
	int	   m_bPostCodeOnOff;
  };

  enum EVisiblePageType
  {
		ESubPage_1 = 1,
		ESubPage_2 = 2,
  };

  enum EOperState
  {
		EInCoinsRatio = 1,
		ESceneType,
		EPostCodeDays,
		ESystemTime,
		EDeCodeCheck,
		EPostSucessTips,
		EPostCodeOnOff,
		EDeCodeAdjust,
		EExit,
  };

  class DeCodeAdjustPage:public IBaseUI
  {
  public:
    DeCodeAdjustPage();
    ~DeCodeAdjustPage();

    virtual void Initialize(IUiElement* ui, UIState* state);
    virtual void injectAppMsg( uint uMsg, int wParam, int lParam );
	virtual void update( float timeLapse );
    bool DeCodeAdjustPageCompelete(const Message::Base& msg);
    bool SceneTypeBtn_Click(const Message::Base& msg);
    bool PlayCodeDaysBtn_Click(const Message::Base& msg);
    bool SystemTimeBtn_Click(const Message::Base& msg);
    bool PostCodeSucessBtn_Click(const Message::Base& msg);
    bool DeCodeCheckBtn_Click(const Message::Base& msg);
    bool ExitDeCodeBtn_Click(const Message::Base& msg);
	bool KeyEnterBtn_Click(const Message::Base& msg);
	bool Btn_DeCodeLeftClick(const Message::Base& msg);
	bool Btn_DeCodeRightClick(const Message::Base& msg);
	bool DeCodeAdjustBtn_Click(const Message::Base& msg);

    void SetDeCodeAdjustVisiblePage(Real msg);
    void SetDeCodeAdjustInCoinsRatioDesc(const WString& msg);
    void SetDeCodeAdjustSenceTypeDesc(const WString& msg);
    void SetDeCodeAdjustPostCodeDaysDesc(const WString& msg);
    void SetDeCodeAdjustSystemTimesDesc(const WString& msg);
    void SetDeCodeAdjustCodeVisible(const WString& msg);
	void SetDeCodeAdjustPageTipsTxt(const WString& msg);
	void SetDeCodeAdjustPagePostCodeOnOffTxt(const WString& msg);
    void SetDeCodeAdjustInputCode(const WString& msg);
    void SetDeCodeAdjustEditDeCode(const WString& msg);
    void DeCodeAdjustPageReturnToTestMainPage();

  private:
    void _getViewDeCodeAdjust();
	void _setInCoinsRatioArray();
    void _setPageControlViewDesc();
	int _getCurOperState();
	void _setCurOperParam(bool pressDir);// 左:true,右:false
	void _setInCoinsRatio(int lv);
	void _setSceneType(int lv);
	void _setPostCodeDays(int lv);
	void _setVisibleSuccess(int lv);
	void _setPostCodeOnOff(int lv);

  private:
    IUiElement*		m_pUi;
	int				m_iCurOperState;
	int				m_iCurParamState;
	InCoinsRatio*	m_pInCoinRaio;
	SceneBackground* m_pSceneType;
	PostCodeDays*	m_pPostCodeDays;
	UIState*		m_pCurState;
	bool			m_bVisibleTips;
	float			m_fTime;

    DeCodeAdjustData m_DeCodeAdjustData;
  };
}
#endif