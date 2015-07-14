#ifndef CHECKACCOUNTPAGE_H
#define CHECKACCOUNTPAGE_H
#include "IBaseUI.h"
#include "UIState.h"

namespace Ogre
{
  struct CheckAccountData
  {
    int64 m_iTotalProfit;
    int64 m_iPreProfit;
    int64 m_iCurrentProfit;
    int64 m_iUpPoints;
    int64 m_iDownPoints;
    int64 m_iInCoins;
    int64 m_iOutCoins;
    int64 m_iRaffleTickets;
    int   m_iPostCodeCount;
  };

  struct CheckAccountData_Top
  {
    String m_strInCoinsRatio;
    String m_strModeDesc;
    String m_strTicketRatio;
  };

  class CheckAccountPage:public IBaseUI
  {
  public:
    CheckAccountPage();
    ~CheckAccountPage();

    virtual void Initialize(IUiElement* ui, UIState* state);
    virtual void injectAppMsg( uint uMsg, int wParam, int lParam );
	virtual void update( float timeLapse );
    bool CheckAccountPageCompelete(const Message::Base& msg);
    void SetBusinessMode(const WString& msg);
    void SetInCoinsRatio(const String& msg);
    void SetTicketRation(const String& msg);
    void SetTotalGainNum(const String& msg);
    void SetPreTotalGainNum(const String& msg);
    void SetCurMoney(const String& msg);
    void SetPreFen(const String& msg);
    void SetNextFen(const String& msg);
    void SetInCoinNum(const String& msg);
    void SetOutCoin(const String& msg);
    void SetMoneyNum(const String& msg);
    void SetLineNo(const String& msg);
    void SetEngineCode(const String& msg);
    void SetLeaveRunTime(const String& msg);
    void SetSendCount(int msg);
    void SetInCoinNum_top(const String& msg);
    void SetMoneyNum_top(const String& msg);
	void CheckAccountPageReturnToMainPage();

  private:
    void _getViewCheckAccountTop();
    void _getCheckAccoutData();
    void _setPageControlViewDesc();
	String _int64ToString(int64 val);

  private:
    IUiElement*		m_pUi;

    CheckAccountData_Top m_CheckAccountData_Top;
    CheckAccountData  m_CheckAccountData;
	UIState*		  m_pCurState;
  };
}
#endif