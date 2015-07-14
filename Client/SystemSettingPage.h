#ifndef SYSTEMSETTINGPGE_H
#define SYSTEMSETTINGPGE_H
#include "IBaseUI.h"

#define LEAVESECOND 5
namespace Ogre
{
  class SystemSettingPage: public IBaseUI
  {
  public:
    SystemSettingPage();
    ~SystemSettingPage();

    virtual void Initialize(IUiElement* ui, UIState* state);
    virtual void injectAppMsg( uint uMsg, int wParam, int lParam );
	virtual void update( float timeLapse );
    bool SystemSettingPageCompelete(const Message::Base& msg);
    bool MachineNoBtn_Click(const Message::Base& msg);
    bool DeCheckCodeBtn_Click(const Message::Base& msg);
    bool EditMiMaBtn_Click(const Message::Base& msg);
    bool Save_ExitBtn_Click(const Message::Base& msg);
    bool NoSave_ExitBtn(const Message::Base& msg);
	bool MachineNoEdit(const Message::Base& msg);
	bool CompareOriginalMima(const Message::Base& msg);
	bool EidtNewMima(const Message::Base& msg);

    void SetSystemSettingEditEngineCode(const WString& msg);
    void SetSystemSettingEditMina(const WString& msg);
    void SetSystemSettingOpenEditMiMaPage();
    void SetSystemSettingCloseEditMiMaPage();
    void SystemSettingPageReturnToMainPage();
	void SystemSettingPageOpenTips();
	void SystemSettingPageCloseTips();
	void SystemSettingPageSetTipsTxt(const WString& msg);
	void SystemSettingPageSetInputMimaOption(int msg);

  private:
    void _getViewSystemSetting();
    void _setPageControlViewDesc();

  private:
    IUiElement* m_pUi;
	bool		m_bEditMiMaSucess;
	bool		m_bEditMachineNoSucess;
	bool		m_bEditMiMaError;
	float		m_fTime;
	UIState*	m_pCurState;

    SystemSettingParam m_SystemSettingPageData;
  };
}
#endif