#ifndef ACTIONPLAYERAUTOFIRE_H
#define ACTIONPLAYERAUTOFIRE_H

#include "Action.h"

namespace Ogre
{
	class ActorPlayer;
	class ActionPlayerAutoFire: public Action
	{
	public:
		ActionPlayerAutoFire(Actor* owner, ActionDesc* desc);
		~ActionPlayerAutoFire();

		virtual void  initailze();
		virtual const String& type() const;
		virtual void  begin();
		virtual void  end();
		virtual void  update(Real timeLapse);

	private:
		ActorPlayer*		mActorPlayer;
		Real				mTimes;
		bool				mIsFired;
	};

	class ActionFactoryPlayerAutoFire:public ActionFactory
	{
	public:
		ActionFactoryPlayerAutoFire();
		virtual ~ActionFactoryPlayerAutoFire();

		virtual const String& type() const;
		virtual Action* createInstance( Actor* owner, ActionDesc* desc );
		virtual ActionDesc* load( rapidxml::xml_node<>* xmlNode, const String& filename );
		static const String TypeName;
	};
}
#endif