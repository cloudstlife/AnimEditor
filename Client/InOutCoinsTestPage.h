#ifndef INOUTCOINSTESTPAGE_H
#define INOUTCOINSTESTPAGE_H
#include "IBaseUI.h"

namespace Ogre
{
  class InOutCoinsTestPage:public IBaseUI
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
    InOutCoinsTestPage();
    ~InOutCoinsTestPage();
    virtual void Initialize(IUiElement* ui, UIState* state);
    virtual void injectAppMsg( uint uMsg, int wParam, int lParam );
	virtual void update( float timeLapse );
	bool OpenInOutCoinPageCompelete(const Message::Base& msg);

    void SetInOutCoinNoMaincheNum(Real pos, Real val);
    void SetInOutCoinOutCoinNum(Real pos, Real val);
    void SetInOutCoinOutMoneyNum(Real pos, Real val);
    void InOutCoinPageReturnToTestMainPage();
	
  private:
    void _setKeyParamByUI(uint uMsg, int wParam, int lParam);
  private:
     IUiElement*			m_pUi;
	 UIState*				m_pCurState;
  };
}
#endif