#ifndef ACTIONSCREENANIMIDLE_H
#define ACTIONSCREENANIMIDLE_H
#include "Action.h"

namespace Ogre
{
	class ActorBackground;
	struct ISprite2D;

	class ActionScreenAnimIdle :public Action
	{
	public:
		ActionScreenAnimIdle(Actor* owner, ActionDesc* desc);
		~ActionScreenAnimIdle();

		virtual void  initailze();
		virtual const String& type() const;
		virtual void  begin();
		virtual void  end();
		virtual void  update(Real timeLapse);

	private:
		ActorBackground*	mActorBackground;
		ISprite2D*			mBackMapSprite2D;
		bool				mOpenDefaultMap;
		String				mId;
		int					mLayer;
	};

	class ActionFactoryScreenAnimIdle:public ActionFactory
	{
	public:
		ActionFactoryScreenAnimIdle();
		virtual ~ActionFactoryScreenAnimIdle();

		virtual const String& type() const;
		virtual Action* createInstance( Actor* owner, ActionDesc* desc );
		virtual ActionDesc* load( rapidxml::xml_node<>* xmlNode, const String& filename );
		static const String TypeName;
	};
}
#endif