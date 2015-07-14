#ifndef ACTIONSCREENANIMCLOSE_H
#define ACTIONSCREENANIMCLOSE_H
#include "Action.h"

namespace Ogre
{
	class ActorBackground;
	struct ISprite2D;
	struct IAnimation2D;

	class ActionScreenAnimClose: public Action
	{
	public:
		ActionScreenAnimClose(Actor* owner, ActionDesc* desc);
		~ActionScreenAnimClose();

		virtual void  initailze();
		virtual const String& type() const;
		virtual void  begin();
		virtual void  end();
		virtual void  update(Real timeLapse);
		IAnimation2D* getBody();

	private:
		ActorBackground*	mActorBackground;
		ISprite2D*			mBackMapSprite2D;
		IAnimation2D*		mScreenCloseBody;
		String				mId;
		int					mLayer;
	};

	class ActionFactoryScreenAnimClose:public ActionFactory
	{
	public:
		ActionFactoryScreenAnimClose();
		virtual ~ActionFactoryScreenAnimClose();

		virtual const String& type() const;
		virtual Action* createInstance( Actor* owner, ActionDesc* desc );
		virtual ActionDesc* load( rapidxml::xml_node<>* xmlNode, const String& filename );
		static const String TypeName;
	};
}
#endif