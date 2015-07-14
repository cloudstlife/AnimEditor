#include "SystemPrerequisites.h"
#include "MainPage.h"
#include "UIState.h"

namespace Ogre
{
#define SetMessageToPageUIByNoParam(control)\
	{\
	this->m_pUi->invokeActionscript( control );\
	}
	MainPage::MainPage():
		m_pUi(NULL)
		, m_pCurState(NULL)
  {
  }

  MainPage::~MainPage()
  {
	SafeDelete(m_pCurState);
  }

  void MainPage::Initialize(IUiElement* ui, UIState* state)
  {
	m_pUi = ui;
	m_pCurState = state;
  }

  void MainPage::injectAppMsg( uint uMsg, int wParam, int lParam )
  {
  }

  void MainPage::update( float timeLapse )
  {

  }

  bool MainPage::OpenCheckAccountPage(const Message::Base& msg)
  {
    return true;
  }

  bool MainPage::OpenMainTestPage(const Message::Base& msg)
  {
    return true;
  }

  bool MainPage::OpenPostMoneyPage(const Message::Base& msg)
  {
    return true;
  }

  bool MainPage::OpenSystemSetPage(const Message::Base& msg)
  {
    return true;
  }

  bool MainPage::MainPageCompelete(const Message::Base& msg)
  {
		m_pCurState->changeCurState(this);
		return true;
  }

  void MainPage::ResetPageVisible()
  {
	  SetMessageToPageUIByNoParam("ResetPageVisible");
  }
}