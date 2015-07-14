#include "SystemPrerequisites.h"
#include "KeyTestPage.h"
#include "UIState.h"

namespace Ogre
{
#define SetMessageToPageUI(control, showMsg)\
  {\
  this->m_pUi->invokeActionscript( control, showMsg );\
  }

  KeyTestPage::KeyTestPage()
	  : m_pUi(NULL)
	  , m_pCurState(NULL)
  {
  }

  KeyTestPage::~KeyTestPage()
  {
	  SafeDelete(m_pUi);
	  SafeDelete(m_pCurState);
  }

  void KeyTestPage::injectAppMsg( uint uMsg, int wParam, int lParam )
  {
    _setKeyParamByUI(uMsg, wParam, lParam);
  }

  void KeyTestPage::update( float timeLapse )
  {
	  
  }

  bool KeyTestPage::KeyWordTestPageCompelete(const Message::Base& msg)
  {
		m_pCurState->changeCurState(this);
		return true;
  }

  void KeyTestPage::Initialize(IUiElement* ui, UIState* state)
  {
    m_pUi = ui;
	m_pCurState = state;
  }

  void KeyTestPage::SetKeyTestLeftBtnFocus(Real pos)
  {
    SetMessageToPageUI("SetKeyTestLeftBtnFocus", pos);
  }

  void KeyTestPage::SetKeyTestLeftBtnDisFocus(Real pos)
  {
    SetMessageToPageUI("SetKeyTestLeftBtnDisFocus", pos);
  }

  void KeyTestPage::SetKeyTestRightBtnFocus(Real pos)
  {
    SetMessageToPageUI("SetKeyTestRightBtnFocus", pos);
  }

  void KeyTestPage::SetKeyTestRightBtnDisFocus(Real pos)
  {
    SetMessageToPageUI("SetKeyTestRightBtnDisFocus", pos);
  }

  void KeyTestPage::SetKeyTestUpBtnFocus(Real pos)
  {
    SetMessageToPageUI("SetKeyTestUpBtnFocus", pos);
  }

  void KeyTestPage::SetKeyTestUpBtnDisFocus(Real pos)
  {
    SetMessageToPageUI("SetKeyTestUpBtnDisFocus", pos);
  }

  void KeyTestPage::SetKeyTestDownBtnFocus(Real pos)
  {
    SetMessageToPageUI("SetKeyTestDownBtnFocus", pos);
  }

  void KeyTestPage::SetKeyTestDownBtnDisFocus(Real pos)
  {
    SetMessageToPageUI("SetKeyTestDownBtnDisFocus", pos);
  }

  void KeyTestPage::SetKeyTestPowerBtnFocus(Real pos)
  {
    SetMessageToPageUI("SetKeyTestPowerBtnFocus", pos);
  }

  void KeyTestPage::SetKeyTestPowerBtnDisFocus(Real pos)
  {
    SetMessageToPageUI("SetKeyTestPowerBtnDisFocus", pos);
  }

  void KeyTestPage::SetKeyTestFireBtn(Real pos)
  {
    SetMessageToPageUI("SetKeyTestFireBtn", pos);
  }

  void KeyTestPage::SetKeyTestFireDisBtn(Real pos)
  {
    SetMessageToPageUI("SetKeyTestFireDisBtn", pos);
  }

  void KeyTestPage::SetKeyTestReturnCoinBtnFocus(Real pos)
  {
    SetMessageToPageUI("SetKeyTestReturnCoinBtnFocus", pos);
  }

  void KeyTestPage::SetKeyTestReturnCoinBtnDisFocus(Real pos)
  {
    SetMessageToPageUI("SetKeyTestReturnCoinBtnDisFocus", pos);
  }

  void KeyTestPage::SetKeyTestOpenScoreBtnFocus(Real pos)
  {
    SetMessageToPageUI("SetKeyTestOpenScoreBtnFocus", pos);
  }

  void KeyTestPage::SetKeyTestOpenScoreBtnDisFocus(Real pos)
  {
    SetMessageToPageUI("SetKeyTestOpenScoreBtnDisFocus", pos);
  }

  void KeyTestPage::SetKeyTestWashScoreBtn(Real pos)
  {
    SetMessageToPageUI("SetKeyTestWashScoreBtn", pos);
  }

  void KeyTestPage::SetKeyTestWashScoreBtnDis(Real pos)
  {
    SetMessageToPageUI("SetKeyTestWashScoreBtnDis", pos);
  }

  void KeyTestPage::KeyTestPageReturnToTestMainPage()
  {
    this->m_pUi->invokeActionscript( "KeyTestPageReturnToTestMainPage" );
  }

  void KeyTestPage::_setKeyParamByUI(uint uMsg, int wParam, int lParam)
  {
    switch(uMsg)
    {
    case WM_KEYUP:
      {
        switch(wParam)
        {
        case '1':
          {
            if (GetAsyncKeyState(VK_LEFT))
              SetKeyTestLeftBtnDisFocus(EPP_1);
            else if(GetAsyncKeyState(VK_RIGHT))
              SetKeyTestRightBtnDisFocus(EPP_1);
            else if(GetAsyncKeyState(VK_UP))
              SetKeyTestUpBtnDisFocus(EPP_1);
            else if(GetAsyncKeyState(VK_DOWN))
              SetKeyTestDownBtnDisFocus(EPP_1);
            else if(GetAsyncKeyState(VK_F1))
              SetKeyTestPowerBtnDisFocus(EPP_1);
            else if(GetAsyncKeyState(VK_F2))
              SetKeyTestFireDisBtn(EPP_1);
            else if(GetAsyncKeyState(VK_F3))
              SetKeyTestReturnCoinBtnDisFocus(EPP_1);
            else if(GetAsyncKeyState(VK_F4))
              SetKeyTestOpenScoreBtnDisFocus(EPP_1);
            else if(GetAsyncKeyState(VK_F5))
              SetKeyTestWashScoreBtnDis(EPP_1);
          }
          break;
        case '2':
          {
            if (GetAsyncKeyState(VK_LEFT))
              SetKeyTestLeftBtnDisFocus(EPP_2);
            else if(GetAsyncKeyState(VK_RIGHT))
              SetKeyTestRightBtnDisFocus(EPP_2);
            else if(GetAsyncKeyState(VK_UP))
              SetKeyTestUpBtnDisFocus(EPP_2);
            else if(GetAsyncKeyState(VK_DOWN))
              SetKeyTestDownBtnDisFocus(EPP_2);
            else if(GetAsyncKeyState(VK_F1))
              SetKeyTestPowerBtnDisFocus(EPP_2);
            else if(GetAsyncKeyState(VK_F2))
              SetKeyTestFireDisBtn(EPP_2);
            else if(GetAsyncKeyState(VK_F3))
              SetKeyTestReturnCoinBtnDisFocus(EPP_2);
            else if(GetAsyncKeyState(VK_F4))
              SetKeyTestOpenScoreBtnDisFocus(EPP_2);
            else if(GetAsyncKeyState(VK_F5))
              SetKeyTestWashScoreBtnDis(EPP_2);
          }
          break;
        case '3':
          {
            if (GetAsyncKeyState(VK_LEFT))
              SetKeyTestLeftBtnDisFocus(EPP_3);
            else if(GetAsyncKeyState(VK_RIGHT))
              SetKeyTestRightBtnDisFocus(EPP_3);
            else if(GetAsyncKeyState(VK_UP))
              SetKeyTestUpBtnDisFocus(EPP_3);
            else if(GetAsyncKeyState(VK_DOWN))
              SetKeyTestDownBtnDisFocus(EPP_1);
            else if(GetAsyncKeyState(VK_F1))
              SetKeyTestPowerBtnDisFocus(EPP_3);
            else if(GetAsyncKeyState(VK_F2))
              SetKeyTestFireDisBtn(EPP_3);
            else if(GetAsyncKeyState(VK_F3))
              SetKeyTestReturnCoinBtnDisFocus(EPP_3);
            else if(GetAsyncKeyState(VK_F4))
              SetKeyTestOpenScoreBtnDisFocus(EPP_3);
            else if(GetAsyncKeyState(VK_F5))
              SetKeyTestWashScoreBtnDis(EPP_3);
          }
          break;
        case '4':
          {
            if (GetAsyncKeyState(VK_LEFT))
              SetKeyTestLeftBtnDisFocus(EPP_4);
            else if(GetAsyncKeyState(VK_RIGHT))
              SetKeyTestRightBtnDisFocus(EPP_4);
            else if(GetAsyncKeyState(VK_UP))
              SetKeyTestUpBtnDisFocus(EPP_4);
            else if(GetAsyncKeyState(VK_DOWN))
              SetKeyTestDownBtnDisFocus(EPP_4);
            else if(GetAsyncKeyState(VK_F1))
              SetKeyTestPowerBtnDisFocus(EPP_4);
            else if(GetAsyncKeyState(VK_F2))
              SetKeyTestFireDisBtn(EPP_4);
            else if(GetAsyncKeyState(VK_F3))
              SetKeyTestReturnCoinBtnDisFocus(EPP_4);
            else if(GetAsyncKeyState(VK_F4))
              SetKeyTestOpenScoreBtnDisFocus(EPP_4);
            else if(GetAsyncKeyState(VK_F5))
              SetKeyTestWashScoreBtnDis(EPP_4);
          }
          break;
        case '5':
          {
            if (GetAsyncKeyState(VK_LEFT))
              SetKeyTestLeftBtnDisFocus(EPP_5);
            else if(GetAsyncKeyState(VK_RIGHT))
              SetKeyTestRightBtnDisFocus(EPP_5);
            else if(GetAsyncKeyState(VK_UP))
              SetKeyTestUpBtnDisFocus(EPP_5);
            else if(GetAsyncKeyState(VK_DOWN))
              SetKeyTestDownBtnDisFocus(EPP_5);
            else if(GetAsyncKeyState(VK_F1))
              SetKeyTestPowerBtnDisFocus(EPP_5);
            else if(GetAsyncKeyState(VK_F2))
              SetKeyTestFireDisBtn(EPP_5);
            else if(GetAsyncKeyState(VK_F3))
              SetKeyTestReturnCoinBtnDisFocus(EPP_5);
            else if(GetAsyncKeyState(VK_F4))
              SetKeyTestOpenScoreBtnDisFocus(EPP_5);
            else if(GetAsyncKeyState(VK_F5))
              SetKeyTestWashScoreBtnDis(EPP_5);
          }
          break;
        case '6':
          {
            if (GetAsyncKeyState(VK_LEFT))
              SetKeyTestLeftBtnDisFocus(EPP_6);
            else if(GetAsyncKeyState(VK_RIGHT))
              SetKeyTestRightBtnDisFocus(EPP_6);
            else if(GetAsyncKeyState(VK_UP))
              SetKeyTestUpBtnDisFocus(EPP_6);
            else if(GetAsyncKeyState(VK_DOWN))
              SetKeyTestDownBtnDisFocus(EPP_6);
            else if(GetAsyncKeyState(VK_F1))
              SetKeyTestPowerBtnDisFocus(EPP_6);
            else if(GetAsyncKeyState(VK_F2))
              SetKeyTestFireDisBtn(EPP_6);
            else if(GetAsyncKeyState(VK_F3))
              SetKeyTestReturnCoinBtnDisFocus(EPP_6);
            else if(GetAsyncKeyState(VK_F4))
              SetKeyTestOpenScoreBtnDisFocus(EPP_6);
            else if(GetAsyncKeyState(VK_F5))
              SetKeyTestWashScoreBtnDis(EPP_6);
          }
          break;
        case '7':
          {
            if (GetAsyncKeyState(VK_LEFT))
              SetKeyTestLeftBtnDisFocus(EPP_7);
            else if(GetAsyncKeyState(VK_RIGHT))
              SetKeyTestRightBtnDisFocus(EPP_7);
            else if(GetAsyncKeyState(VK_UP))
              SetKeyTestUpBtnDisFocus(EPP_7);
            else if(GetAsyncKeyState(VK_DOWN))
              SetKeyTestDownBtnDisFocus(EPP_7);
            else if(GetAsyncKeyState(VK_F1))
              SetKeyTestPowerBtnDisFocus(EPP_7);
            else if(GetAsyncKeyState(VK_F2))
              SetKeyTestFireDisBtn(EPP_7);
            else if(GetAsyncKeyState(VK_F3))
              SetKeyTestReturnCoinBtnDisFocus(EPP_7);
            else if(GetAsyncKeyState(VK_F4))
              SetKeyTestOpenScoreBtnDisFocus(EPP_7);
            else if(GetAsyncKeyState(VK_F5))
              SetKeyTestWashScoreBtnDis(EPP_7);
          }
          break;
        case '8':
          {
            if (GetAsyncKeyState(VK_LEFT))
              SetKeyTestLeftBtnDisFocus(EPP_8);
            else if(GetAsyncKeyState(VK_RIGHT))
              SetKeyTestRightBtnDisFocus(EPP_8);
            else if(GetAsyncKeyState(VK_UP))
              SetKeyTestUpBtnDisFocus(EPP_8);
            else if(GetAsyncKeyState(VK_DOWN))
              SetKeyTestDownBtnDisFocus(EPP_8);
            else if(GetAsyncKeyState(VK_F1))
              SetKeyTestPowerBtnDisFocus(EPP_8);
            else if(GetAsyncKeyState(VK_F2))
              SetKeyTestFireDisBtn(EPP_8);
            else if(GetAsyncKeyState(VK_F3))
              SetKeyTestReturnCoinBtnDisFocus(EPP_8);
            else if(GetAsyncKeyState(VK_F4))
              SetKeyTestOpenScoreBtnDisFocus(EPP_8);
            else if(GetAsyncKeyState(VK_F5))
              SetKeyTestWashScoreBtnDis(EPP_8);
          }
          break;
        case '9':
          {
            if (GetAsyncKeyState(VK_LEFT))
              SetKeyTestLeftBtnDisFocus(EPP_9);
            else if(GetAsyncKeyState(VK_RIGHT))
              SetKeyTestRightBtnDisFocus(EPP_9);
            else if(GetAsyncKeyState(VK_UP))
              SetKeyTestUpBtnDisFocus(EPP_9);
            else if(GetAsyncKeyState(VK_DOWN))
              SetKeyTestDownBtnDisFocus(EPP_9);
            else if(GetAsyncKeyState(VK_F1))
              SetKeyTestPowerBtnDisFocus(EPP_9);
            else if(GetAsyncKeyState(VK_F2))
              SetKeyTestFireDisBtn(EPP_9);
            else if(GetAsyncKeyState(VK_F3))
              SetKeyTestReturnCoinBtnDisFocus(EPP_9);
            else if(GetAsyncKeyState(VK_F4))
              SetKeyTestOpenScoreBtnDisFocus(EPP_9);
            else if(GetAsyncKeyState(VK_F5))
              SetKeyTestWashScoreBtnDis(EPP_9);
          }
          break;
        case '0':
          {
            if (GetAsyncKeyState(VK_LEFT))
              SetKeyTestLeftBtnDisFocus(EPP_10);
            else if(GetAsyncKeyState(VK_RIGHT))
              SetKeyTestRightBtnDisFocus(EPP_10);
            else if(GetAsyncKeyState(VK_UP))
              SetKeyTestUpBtnDisFocus(EPP_10);
            else if(GetAsyncKeyState(VK_DOWN))
              SetKeyTestDownBtnDisFocus(EPP_10);
            else if(GetAsyncKeyState(VK_F1))
              SetKeyTestPowerBtnDisFocus(EPP_10);
            else if(GetAsyncKeyState(VK_F2))
              SetKeyTestFireDisBtn(EPP_10);
            else if(GetAsyncKeyState(VK_F3))
              SetKeyTestReturnCoinBtnDisFocus(EPP_10);
            else if(GetAsyncKeyState(VK_F4))
              SetKeyTestOpenScoreBtnDisFocus(EPP_10);
            else if(GetAsyncKeyState(VK_F5))
              SetKeyTestWashScoreBtnDis(EPP_10);
          }
          break;
        }
      }
      break;
    case WM_KEYDOWN:
      {
        switch(wParam)
        {
        case VK_ESCAPE:
          {
            KeyTestPageReturnToTestMainPage();
          }
          break;
        case '1':
          {
            if (GetAsyncKeyState(VK_LEFT))
              SetKeyTestLeftBtnFocus(EPP_1);
            else if(GetAsyncKeyState(VK_RIGHT))
              SetKeyTestRightBtnFocus(EPP_1);
            else if(GetAsyncKeyState(VK_UP))
              SetKeyTestUpBtnFocus(EPP_1);
            else if(GetAsyncKeyState(VK_DOWN))
              SetKeyTestDownBtnFocus(EPP_1);
            else if(GetAsyncKeyState(VK_F1))
              SetKeyTestPowerBtnFocus(EPP_1);
            else if(GetAsyncKeyState(VK_F2))
              SetKeyTestFireBtn(EPP_1);
            else if(GetAsyncKeyState(VK_F3))
              SetKeyTestReturnCoinBtnFocus(EPP_1);
            else if(GetAsyncKeyState(VK_F4))
              SetKeyTestOpenScoreBtnFocus(EPP_1);
            else if(GetAsyncKeyState(VK_F5))
              SetKeyTestWashScoreBtn(EPP_1);
          }
          break;
        case '2':
          {
            if (GetAsyncKeyState(VK_LEFT))
              SetKeyTestLeftBtnFocus(EPP_2);
            else if(GetAsyncKeyState(VK_RIGHT))
              SetKeyTestRightBtnFocus(EPP_2);
            else if(GetAsyncKeyState(VK_UP))
              SetKeyTestUpBtnFocus(EPP_2);
            else if(GetAsyncKeyState(VK_DOWN))
              SetKeyTestDownBtnFocus(EPP_2);
            else if(GetAsyncKeyState(VK_F1))
              SetKeyTestPowerBtnFocus(EPP_2);
            else if(GetAsyncKeyState(VK_F2))
              SetKeyTestFireBtn(EPP_2);
            else if(GetAsyncKeyState(VK_F3))
              SetKeyTestReturnCoinBtnFocus(EPP_2);
            else if(GetAsyncKeyState(VK_F4))
              SetKeyTestOpenScoreBtnFocus(EPP_2);
            else if(GetAsyncKeyState(VK_F5))
              SetKeyTestWashScoreBtn(EPP_2);
          }
          break;
        case '3':
          {
            if (GetAsyncKeyState(VK_LEFT))
              SetKeyTestLeftBtnFocus(EPP_3);
            else if(GetAsyncKeyState(VK_RIGHT))
              SetKeyTestRightBtnFocus(EPP_3);
            else if(GetAsyncKeyState(VK_UP))
              SetKeyTestUpBtnFocus(EPP_3);
            else if(GetAsyncKeyState(VK_DOWN))
              SetKeyTestDownBtnFocus(EPP_3);
            else if(GetAsyncKeyState(VK_F1))
              SetKeyTestPowerBtnFocus(EPP_3);
            else if(GetAsyncKeyState(VK_F2))
              SetKeyTestFireBtn(EPP_3);
            else if(GetAsyncKeyState(VK_F3))
              SetKeyTestReturnCoinBtnFocus(EPP_3);
            else if(GetAsyncKeyState(VK_F4))
              SetKeyTestOpenScoreBtnFocus(EPP_3);
            else if(GetAsyncKeyState(VK_F5))
              SetKeyTestWashScoreBtn(EPP_3);
          }
          break;
        case '4':
          {
            if (GetAsyncKeyState(VK_LEFT))
              SetKeyTestLeftBtnFocus(EPP_4);
            else if(GetAsyncKeyState(VK_RIGHT))
              SetKeyTestRightBtnFocus(EPP_4);
            else if(GetAsyncKeyState(VK_UP))
              SetKeyTestUpBtnFocus(EPP_4);
            else if(GetAsyncKeyState(VK_DOWN))
              SetKeyTestDownBtnFocus(EPP_4);
            else if(GetAsyncKeyState(VK_F1))
              SetKeyTestPowerBtnFocus(EPP_4);
            else if(GetAsyncKeyState(VK_F2))
              SetKeyTestFireBtn(EPP_4);
            else if(GetAsyncKeyState(VK_F3))
              SetKeyTestReturnCoinBtnFocus(EPP_4);
            else if(GetAsyncKeyState(VK_F4))
              SetKeyTestOpenScoreBtnFocus(EPP_4);
            else if(GetAsyncKeyState(VK_F5))
              SetKeyTestWashScoreBtn(EPP_4);
          }
          break;
        case '5':
          {
            if (GetAsyncKeyState(VK_LEFT))
              SetKeyTestLeftBtnFocus(EPP_5);
            else if(GetAsyncKeyState(VK_RIGHT))
              SetKeyTestRightBtnFocus(EPP_5);
            else if(GetAsyncKeyState(VK_UP))
              SetKeyTestUpBtnFocus(EPP_5);
            else if(GetAsyncKeyState(VK_DOWN))
              SetKeyTestDownBtnFocus(EPP_5);
            else if(GetAsyncKeyState(VK_F1))
              SetKeyTestPowerBtnFocus(EPP_5);
            else if(GetAsyncKeyState(VK_F2))
              SetKeyTestFireBtn(EPP_5);
            else if(GetAsyncKeyState(VK_F3))
              SetKeyTestReturnCoinBtnFocus(EPP_5);
            else if(GetAsyncKeyState(VK_F4))
              SetKeyTestOpenScoreBtnFocus(EPP_5);
            else if(GetAsyncKeyState(VK_F5))
              SetKeyTestWashScoreBtn(EPP_5);
          }
          break;
        case '6':
          {
            if (GetAsyncKeyState(VK_LEFT))
              SetKeyTestLeftBtnFocus(EPP_6);
            else if(GetAsyncKeyState(VK_RIGHT))
              SetKeyTestRightBtnFocus(EPP_6);
            else if(GetAsyncKeyState(VK_UP))
              SetKeyTestUpBtnFocus(EPP_6);
            else if(GetAsyncKeyState(VK_DOWN))
              SetKeyTestDownBtnFocus(EPP_6);
            else if(GetAsyncKeyState(VK_F1))
              SetKeyTestPowerBtnFocus(EPP_6);
            else if(GetAsyncKeyState(VK_F2))
              SetKeyTestFireBtn(EPP_6);
            else if(GetAsyncKeyState(VK_F3))
              SetKeyTestReturnCoinBtnFocus(EPP_6);
            else if(GetAsyncKeyState(VK_F4))
              SetKeyTestOpenScoreBtnFocus(EPP_6);
            else if(GetAsyncKeyState(VK_F5))
              SetKeyTestWashScoreBtn(EPP_6);
          }
          break;
        case '7':
          {
            if (GetAsyncKeyState(VK_LEFT))
              SetKeyTestLeftBtnFocus(EPP_7);
            else if(GetAsyncKeyState(VK_RIGHT))
              SetKeyTestRightBtnFocus(EPP_7);
            else if(GetAsyncKeyState(VK_UP))
              SetKeyTestUpBtnFocus(EPP_7);
            else if(GetAsyncKeyState(VK_DOWN))
              SetKeyTestDownBtnFocus(EPP_7);
            else if(GetAsyncKeyState(VK_F1))
              SetKeyTestPowerBtnFocus(EPP_7);
            else if(GetAsyncKeyState(VK_F2))
              SetKeyTestFireBtn(EPP_7);
            else if(GetAsyncKeyState(VK_F3))
              SetKeyTestReturnCoinBtnFocus(EPP_7);
            else if(GetAsyncKeyState(VK_F4))
              SetKeyTestOpenScoreBtnFocus(EPP_7);
            else if(GetAsyncKeyState(VK_F5))
              SetKeyTestWashScoreBtn(EPP_7);
          }
          break;
        case '8':
          {
            if (GetAsyncKeyState(VK_LEFT))
              SetKeyTestLeftBtnFocus(EPP_8);
            else if(GetAsyncKeyState(VK_RIGHT))
              SetKeyTestRightBtnFocus(EPP_8);
            else if(GetAsyncKeyState(VK_UP))
              SetKeyTestUpBtnFocus(EPP_8);
            else if(GetAsyncKeyState(VK_DOWN))
              SetKeyTestDownBtnFocus(EPP_8);
            else if(GetAsyncKeyState(VK_F1))
              SetKeyTestPowerBtnFocus(EPP_8);
            else if(GetAsyncKeyState(VK_F2))
              SetKeyTestFireBtn(EPP_8);
            else if(GetAsyncKeyState(VK_F3))
              SetKeyTestReturnCoinBtnFocus(EPP_8);
            else if(GetAsyncKeyState(VK_F4))
              SetKeyTestOpenScoreBtnFocus(EPP_8);
            else if(GetAsyncKeyState(VK_F5))
              SetKeyTestWashScoreBtn(EPP_8);
          }
          break;
        case '9':
          {
            if (GetAsyncKeyState(VK_LEFT))
              SetKeyTestLeftBtnFocus(EPP_9);
            else if(GetAsyncKeyState(VK_RIGHT))
              SetKeyTestRightBtnFocus(EPP_9);
            else if(GetAsyncKeyState(VK_UP))
              SetKeyTestUpBtnFocus(EPP_9);
            else if(GetAsyncKeyState(VK_DOWN))
              SetKeyTestDownBtnFocus(EPP_9);
            else if(GetAsyncKeyState(VK_F1))
              SetKeyTestPowerBtnFocus(EPP_9);
            else if(GetAsyncKeyState(VK_F2))
              SetKeyTestFireBtn(EPP_9);
            else if(GetAsyncKeyState(VK_F3))
              SetKeyTestReturnCoinBtnFocus(EPP_9);
            else if(GetAsyncKeyState(VK_F4))
              SetKeyTestOpenScoreBtnFocus(EPP_9);
            else if(GetAsyncKeyState(VK_F5))
              SetKeyTestWashScoreBtn(EPP_9);
          }
          break;
        case '0':
          {
            if (GetAsyncKeyState(VK_LEFT))
              SetKeyTestLeftBtnFocus(EPP_10);
            else if(GetAsyncKeyState(VK_RIGHT))
              SetKeyTestRightBtnFocus(EPP_10);
            else if(GetAsyncKeyState(VK_UP))
              SetKeyTestUpBtnFocus(EPP_10);
            else if(GetAsyncKeyState(VK_DOWN))
              SetKeyTestDownBtnFocus(EPP_10);
            else if(GetAsyncKeyState(VK_F1))
              SetKeyTestPowerBtnFocus(EPP_10);
            else if(GetAsyncKeyState(VK_F2))
              SetKeyTestFireBtn(EPP_10);
            else if(GetAsyncKeyState(VK_F3))
              SetKeyTestReturnCoinBtnFocus(EPP_10);
            else if(GetAsyncKeyState(VK_F4))
              SetKeyTestOpenScoreBtnFocus(EPP_10);
            else if(GetAsyncKeyState(VK_F5))
              SetKeyTestWashScoreBtn(EPP_10);
          }
          break;
        }
      }
      break;
    }
  }
}