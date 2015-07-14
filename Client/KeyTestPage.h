#ifndef KEYTESTPAGE_H
#define KEYTESTPAGE_H
#include "IBaseUI.h"
namespace Ogre
{
  class KeyTestPage: public IBaseUI
  {
    enum EPlayerPos
    {
      EPP_1 = 1,
      EPP_2 = 2,
      EPP_3 = 3,
      EPP_4 = 4,
      EPP_5 = 5,
      EPP_6 = 6,
      EPP_7 = 7,
      EPP_8 = 8,
      EPP_9 = 9,
      EPP_10 = 10,
    };
  public:
    KeyTestPage();
    ~KeyTestPage();

    virtual void Initialize(IUiElement* ui, UIState* state);
    virtual void injectAppMsg( uint uMsg, int wParam, int lParam );
	virtual void update( float timeLapse );
	bool KeyWordTestPageCompelete(const Message::Base& msg);
    void SetKeyTestLeftBtnFocus(Real pos);
    void SetKeyTestLeftBtnDisFocus(Real pos);
    void SetKeyTestRightBtnFocus(Real pos);
    void SetKeyTestRightBtnDisFocus(Real pos);
    void SetKeyTestUpBtnFocus(Real pos);
    void SetKeyTestUpBtnDisFocus(Real pos);
    void SetKeyTestDownBtnFocus(Real pos);
    void SetKeyTestDownBtnDisFocus(Real pos);
    void SetKeyTestPowerBtnFocus(Real pos);
    void SetKeyTestPowerBtnDisFocus(Real pos);
    void SetKeyTestFireBtn(Real pos);
    void SetKeyTestFireDisBtn(Real pos);
    void SetKeyTestReturnCoinBtnFocus(Real pos);
    void SetKeyTestReturnCoinBtnDisFocus(Real pos);
    void SetKeyTestOpenScoreBtnFocus(Real pos);
    void SetKeyTestOpenScoreBtnDisFocus(Real pos);
    void SetKeyTestWashScoreBtn(Real pos);
    void SetKeyTestWashScoreBtnDis(Real pos);
    void KeyTestPageReturnToTestMainPage();

  private:
    void _setKeyParamByUI(uint uMsg, int wParam, int lParam);

private:
    IUiElement*			m_pUi;
	UIState*			m_pCurState;
  };
}
#endif