#ifndef UISTATE_H
#define UISTATE_H
#include "IBaseUI.h"

namespace Ogre
{
	class UIState
	{
	public:
		UIState();
		~UIState();

		void changeCurState(IBaseUI* state);
		void injectAppMsg( uint uMsg, int wParam, int lParam );
		void update( float timeLapse );

	private:
		IBaseUI*		mCurPage;
	};
}
#endif