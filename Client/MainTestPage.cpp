#include "SystemPrerequisites.h"
#include "MainTestPage.h"
#include "UIState.h"

namespace Ogre
{
  MainTestPage::MainTestPage()
	  : m_pUi(NULL)
	  , m_pCurState(NULL)
  {
  }

  MainTestPage::~MainTestPage()
  {
    SafeDelete(m_pUi);
    SafeDelete(m_pCurState);
  }

  void MainTestPage::Initialize(IUiElement* ui, UIState* state)
  {
    m_pUi = ui;
	m_pCurState = state;
  }

  void MainTestPage::injectAppMsg( uint uMsg, int wParam, int lParam )
  {
    switch(uMsg)
    {
      case WM_KEYDOWN:
        {
          switch(wParam)
          {
            case VK_ESCAPE:
              {
                MainTestPageReturnToTestMainPage();
              }
              break;
          }
          break;
        }
        break;
    }
  }

  void MainTestPage::update( float timeLapse )
  {

  }


  bool MainTestPage::OpenMainTestPageCompelete(const Message::Base& msg)
  {
		m_pCurState->changeCurState(this);
		return true;
  }

  bool MainTestPage::OpenKeyTestPage(const Message::Base& msg)
  {
    return true;
  }

  bool MainTestPage::OpenSoundTestPage(const Message::Base& msg)
  {
    return true;
  }

  bool MainTestPage::OpenCodeTestPage(const Message::Base& msg)
  {
    return true;
  }

  bool MainTestPage::OpenOutTestPage(const Message::Base& msg)
  {
    return true;
  }

  bool MainTestPage::OpenInOutCoinPage(const Message::Base& msg)
  {
    return true;
  }

  void MainTestPage::MainTestPageReturnToTestMainPage()
  {
    this->m_pUi->invokeActionscript( "MainTestPageReturnToTestMainPage" );
  }
}