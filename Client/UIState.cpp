#include "UIState.h"

namespace Ogre
{
	UIState::UIState()
	{
		mCurPage = NULL;
	}

	UIState::~UIState()
	{
		mCurPage = NULL;
	}

	void UIState::changeCurState(IBaseUI* state)
	{
		mCurPage = state;
	}

	void UIState::injectAppMsg( uint uMsg, int wParam, int lParam )
	{
		if (mCurPage)
		{
			mCurPage->injectAppMsg(uMsg, wParam, lParam);
		}
	}

	void UIState::update( float timeLapse )
	{
		if (mCurPage)
		{
			mCurPage->update(timeLapse);
		}
	}
}