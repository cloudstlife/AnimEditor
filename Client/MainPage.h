#ifndef MAINPAGE_H
#define MAINPAGE_H
#include "IBaseUI.h"

namespace Ogre
{
  class MainPage:public IBaseUI
  {
  public:
    MainPage();
    ~MainPage();

    virtual void Initialize(IUiElement* ui, UIState* state);
    virtual void injectAppMsg( uint uMsg, int wParam, int lParam );
	virtual void update( float timeLapse );
    bool OpenCheckAccountPage(const Message::Base& msg);
    bool OpenMainTestPage(const Message::Base& msg);
    bool OpenPostMoneyPage(const Message::Base& msg);
    bool OpenSystemSetPage(const Message::Base& msg);
	bool MainPageCompelete(const Message::Base& msg);
	void ResetPageVisible();

  private:
	IUiElement*			m_pUi;
	UIState*			m_pCurState;
  };
}
#endif