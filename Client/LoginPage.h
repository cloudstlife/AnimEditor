#ifndef LOGINPAGE_H
#define LOGINPAGE_H
#include "IBaseUI.h"

namespace Ogre
{
	class LoginPage: public IBaseUI
	{
	public:
		LoginPage();
		~LoginPage();

		virtual void Initialize(IUiElement* ui, UIState* state);
		virtual void injectAppMsg( uint uMsg, int wParam, int lParam );
		virtual void update( float timeLapse );
		bool CheckLogin(const Message::Base& msg);
		bool LoginPageCompelete(const Message::Base& msg);
		void OpenLoginTips();
		void SetLoginPageFocusControl();
		void ResetLoginPageMiMa();

	private:
		IUiElement*		m_pUi;
		UIState*		m_pCurState;
	};
}
#endif