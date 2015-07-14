#ifndef ACTIONSCREENANIMWAIT_H
#define ACTIONSCREENANIMWAIT_H
#include "Action.h"

namespace Ogre
{
	class ActorBackground;
	struct ISprite2D;
	struct IAnimation2D;

	class ActionScreenAnimWait :public Action
	{
	public:
		ActionScreenAnimWait(Actor* owner, ActionDesc* desc);
		~ActionScreenAnimWait();

		virtual void  initailze();
		virtual const String& type() const;
		virtual void  begin();
		virtual void  end();
		virtual void  update(Real timeLapse);

	private:
		ActorBackground*	mActorBackground;
		ISprite2D*			mBackMapSprite2D;
		IAnimation2D*		mScreenWaitBody;
		bool				mOpenDefaultMap;
		String				mId;
		int					mLayer;
	};

	class ActionFactoryScreenAnimWait:public ActionFactory
	{
	public:
		ActionFactoryScreenAnimWait();
		virtual ~ActionFactoryScreenAnimWait();

		virtual const String& type() const;
		virtual Action* createInstance( Actor* owner, ActionDesc* desc );
		virtual ActionDesc* load( rapidxml::xml_node<>* xmlNode, const String& filename );
		static const String TypeName;
	};
}
#endif