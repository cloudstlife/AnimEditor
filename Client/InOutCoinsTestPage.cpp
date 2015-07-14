#include "SystemPrerequisites.h"
#include "InOutCoinsTestPage.h"
#include "UIState.h"

namespace Ogre
{
#define SetMessagePageUI(control, msg)\
  {\
  this->m_pUi->invokeActionscript(control, msg);\
  }

  InOutCoinsTestPage::InOutCoinsTestPage()
	  : m_pUi(NULL)
	  , m_pCurState(NULL)
  {
  }

  InOutCoinsTestPage::~InOutCoinsTestPage()
  {
    SafeDelete(m_pUi);
	SafeDelete(m_pCurState);
  }

  void InOutCoinsTestPage::Initialize(IUiElement* ui, UIState* state)
  {
    m_pUi = ui;
	m_pCurState = state;
  }

  void InOutCoinsTestPage::injectAppMsg( uint uMsg, int wParam, int lParam )
  {
    _setKeyParamByUI(uMsg, wParam, lParam);
  }

  void InOutCoinsTestPage::update( float timeLapse )
  {

  }

  bool InOutCoinsTestPage::OpenInOutCoinPageCompelete(const Message::Base& msg)
  {
		m_pCurState->changeCurState(this);
		return true;
  }

  void InOutCoinsTestPage::SetInOutCoinNoMaincheNum(Real pos, Real val)
  {
    UiMessage exMsg(2);
    exMsg[0] = pos;
    exMsg[1] = val;
    SetMessagePageUI("SetInOutCoinNoMaincheNum", exMsg);
  }

  void InOutCoinsTestPage::SetInOutCoinOutCoinNum(Real pos, Real val)
  {
    UiMessage exMsg(2);
    exMsg[0] = pos;
    exMsg[1] = val;
    SetMessagePageUI("SetInOutCoinOutCoinNum", exMsg);
  }

  void InOutCoinsTestPage::SetInOutCoinOutMoneyNum(Real pos, Real val)
  {
    UiMessage exMsg(2);
    exMsg[0] = pos;
    exMsg[1] = val;
    SetMessagePageUI("SetInOutCoinOutMoneyNum", exMsg);
  }

  void InOutCoinsTestPage::InOutCoinPageReturnToTestMainPage()
  {
    this->m_pUi->invokeActionscript("InOutCoinPageReturnToTestMainPage");
  }

  void InOutCoinsTestPage::_setKeyParamByUI(uint uMsg, int wParam, int lParam)
  {
    switch(uMsg)
    {
    case WM_KEYDOWN:
      {
        switch(wParam)
        {
        case VK_ESCAPE:
          {
            InOutCoinPageReturnToTestMainPage();
          }
          break;
        case '1':
          {
            if (GetAsyncKeyState(VK_LEFT))
            {
              SetInOutCoinNoMaincheNum(EPP_1, 1);
            }
            else if (GetAsyncKeyState(VK_RIGHT))
            {
              SetInOutCoinOutCoinNum(EPP_1, 1);
            }
            else if (GetAsyncKeyState(VK_DOWN))
            {
              SetInOutCoinOutMoneyNum(EPP_1, 1);
            }
          }
          break;
        case '2':
          {
            if (GetAsyncKeyState(VK_LEFT))
            {
              SetInOutCoinNoMaincheNum(EPP_2, 1);
            }
            else if (GetAsyncKeyState(VK_RIGHT))
            {
              SetInOutCoinOutCoinNum(EPP_2, 1);
            }
            else if (GetAsyncKeyState(VK_DOWN))
            {
              SetInOutCoinOutMoneyNum(EPP_2, 1);
            }
          }
          break;
        case '3':
          {
            if (GetAsyncKeyState(VK_LEFT))
            {
              SetInOutCoinNoMaincheNum(EPP_3, 1);
            }
            else if (GetAsyncKeyState(VK_RIGHT))
            {
              SetInOutCoinOutCoinNum(EPP_3, 1);
            }
            else if (GetAsyncKeyState(VK_DOWN))
            {
              SetInOutCoinOutMoneyNum(EPP_3, 1);
            }
          }
          break;
        case '4':
          {
            if (GetAsyncKeyState(VK_LEFT))
            {
              SetInOutCoinNoMaincheNum(EPP_4, 1);
            }
            else if (GetAsyncKeyState(VK_RIGHT))
            {
              SetInOutCoinOutCoinNum(EPP_4, 1);
            }
            else if (GetAsyncKeyState(VK_DOWN))
            {
              SetInOutCoinOutMoneyNum(EPP_4, 1);
            }
          }
          break;
        case '5':
          {
            if (GetAsyncKeyState(VK_LEFT))
            {
              SetInOutCoinNoMaincheNum(EPP_5, 1);
            }
            else if (GetAsyncKeyState(VK_RIGHT))
            {
              SetInOutCoinOutCoinNum(EPP_5, 1);
            }
            else if (GetAsyncKeyState(VK_DOWN))
            {
              SetInOutCoinOutMoneyNum(EPP_5, 1);
            }
          }
          break;
        case '6':
          {
            if (GetAsyncKeyState(VK_LEFT))
            {
              SetInOutCoinNoMaincheNum(EPP_6, 1);
            }
            else if (GetAsyncKeyState(VK_RIGHT))
            {
              SetInOutCoinOutCoinNum(EPP_6, 1);
            }
            else if (GetAsyncKeyState(VK_DOWN))
            {
              SetInOutCoinOutMoneyNum(EPP_6, 1);
            }
          }
          break;
        case '7':
          {
            if (GetAsyncKeyState(VK_LEFT))
            {
              SetInOutCoinNoMaincheNum(EPP_7, 1);
            }
            else if (GetAsyncKeyState(VK_RIGHT))
            {
              SetInOutCoinOutCoinNum(EPP_7, 1);
            }
            else if (GetAsyncKeyState(VK_DOWN))
            {
              SetInOutCoinOutMoneyNum(EPP_7, 1);
            }
          }
          break;
        case '8':
          {
            if (GetAsyncKeyState(VK_LEFT))
            {
              SetInOutCoinNoMaincheNum(EPP_8, 1);
            }
            else if (GetAsyncKeyState(VK_RIGHT))
            {
              SetInOutCoinOutCoinNum(EPP_8, 1);
            }
            else if (GetAsyncKeyState(VK_DOWN))
            {
              SetInOutCoinOutMoneyNum(EPP_8, 1);
            }
          }
          break;
        case '9':
          {
            if (GetAsyncKeyState(VK_LEFT))
            {
              SetInOutCoinNoMaincheNum(EPP_9, 1);
            }
            else if (GetAsyncKeyState(VK_RIGHT))
            {
              SetInOutCoinOutCoinNum(EPP_9, 1);
            }
            else if (GetAsyncKeyState(VK_DOWN))
            {
              SetInOutCoinOutMoneyNum(EPP_9, 1);
            }
          }
          break;
        case '0':
          {
            if (GetAsyncKeyState(VK_LEFT))
            {
              SetInOutCoinNoMaincheNum(EPP_10, 1);
            }
            else if (GetAsyncKeyState(VK_RIGHT))
            {
              SetInOutCoinOutCoinNum(EPP_10, 1);
            }
            else if (GetAsyncKeyState(VK_DOWN))
            {
              SetInOutCoinOutMoneyNum(EPP_10, 1);
            }
          }
          break;
        }
        break;
      }
    }
  }
}