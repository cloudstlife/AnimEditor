#ifndef IBASEUI_H
#define IBASEUI_H

#include "GameData.h"
#include "IUiElement.h"
namespace Ogre
{
  struct IBaseUI
  {
	friend class UIState;

  public:
    virtual void Initialize(IUiElement* ui, UIState* state) = 0;
    virtual void injectAppMsg( uint uMsg, int wParam, int lParam ) = 0;
	virtual	void update( float timeLapse ) = 0;
  };
}
#endif