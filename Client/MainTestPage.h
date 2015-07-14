#ifndef MAINTESTPAGE_H
#define MAINTESTPAGE_H
#include "IBaseUI.h"

namespace Ogre
{
  class MainTestPage:public IBaseUI
  {
  public:
    MainTestPage();
    ~MainTestPage();

    virtual void Initialize(IUiElement* ui, UIState* state);
    virtual void injectAppMsg( uint uMsg, int wParam, int lParam );
	virtual void update( float timeLapse );
    bool OpenMainTestPageCompelete(const Message::Base& msg);
    bool OpenKeyTestPage(const Message::Base& msg);
    bool OpenSoundTestPage(const Message::Base& msg);
    bool OpenCodeTestPage(const Message::Base& msg);
    bool OpenOutTestPage(const Message::Base& msg);
    bool OpenInOutCoinPage(const Message::Base& msg);
    void MainTestPageReturnToTestMainPage();

  private:
    IUiElement*   m_pUi;
	UIState*	  m_pCurState;
  };
}
#endif