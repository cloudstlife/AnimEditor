#ifndef ACTIONSCREENANIMOPEN_H
#define ACTIONSCREENANIMOPEN_H
#include "Action.h"

namespace Ogre
{
	class ActorBackground;
	struct ISprite2D;
	struct IAnimation2D;

	class ActionScreenAnimOpen: public Action
	{
	public:
		ActionScreenAnimOpen(Actor* owner, ActionDesc* desc);
		~ActionScreenAnimOpen();

		virtual void  initailze();
		virtual const String& type() const;
		virtual void  begin();
		virtual void  end();
		virtual void  update(Real timeLapse);
		IAnimation2D* getBody();

	private:
		ActorBackground*	mActorBackground;
		IAnimation2D*		mScreenOpenBody;
		ISprite2D*			mBackMapBody;
		String				mId;
		int					mLayer;
		//Real				mDuration;
		//String				mGeneratorGroupId;
	};

	class ActionFactoryScreenAnimOpen:public ActionFactory
	{
	public:
		ActionFactoryScreenAnimOpen();
		virtual ~ActionFactoryScreenAnimOpen();

		virtual const String& type() const;
		virtual Action* createInstance( Actor* owner, ActionDesc* desc );
		virtual ActionDesc* load( rapidxml::xml_node<>* xmlNode, const String& filename );
		static const String TypeName;
	};
}
#endif