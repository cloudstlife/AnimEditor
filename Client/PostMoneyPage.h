#ifndef POSTMONEYPAGE_H
#define POSTMONEYPAGE_H
#include "IBaseUI.h"

namespace Ogre
{
  struct PostMoneyData_Top
  {
    String m_strInCoinsRatio;
    String m_strModeDesc;
    String m_strTicketRatio;
  };

  struct PostMoneyData
  {
    int64 m_iTotalProfit;
    int64 m_iCurrentProfit;
    String m_strMachineNo;
    int   m_iPostCodeCount;
  };

  class PostMoneyPage:public IBaseUI
  {
    enum EVisibleSubPage
    {
      ESubPage_1 = 1,
      ESubPage_2 = 2,
    };
  public:
    PostMoneyPage();
    ~PostMoneyPage();

    virtual void Initialize(IUiElement* ui, UIState* state);
    virtual void injectAppMsg( uint uMsg, int wParam, int lParam );
	virtual void update( float timeLapse );
    bool PostMoneyPageCompelete(const Message::Base& msg);
    bool PostCodeNoBtn_Click(const Message::Base& msg);
    bool Save_ExitBtn_Click(const Message::Base& msg);
	bool PostMoneyEnter_Click(const Message::Base& msg);

    void SetVisiblePage(Real msg);
    void SetTotalGainNum(const WString& msg);
    void SetCurMoney(const WString& msg);
    void SetMachineNo(const String& msg);
    void SetSendCount(int msg);
    void SetBusinessMode(const WString& msg);
    void SetInCoinsRatio(const WString& msg);
    void SetTicketRation(const WString& msg);
    void SetVerifyCode(const String& msg);
	void PostMoneyPageReturnToMainPage();

  private:
    void _getViewPostMoneyTop();
    void _getPostMoneyData();
    void _setPageControlViewDesc();
	String _int64ToString(int64 val);

  private:
    IUiElement*			m_pUi;
	UIState*			m_pCurState;

    PostMoneyData_Top m_PostMoneyData_Top;
    PostMoneyData m_PostMoneyData;
  };
}
#endif