#ifndef ACTIONPLAYERNORMALFIRE_H
#define ACTIONPLAYERNORMALFIRE_H

#include "Action.h"

namespace Ogre
{
	class ActorPlayer;
	class ActionPlayerNormalFire: public Action
	{
	public:
		ActionPlayerNormalFire(Actor* owner, ActionDesc* desc);
		~ActionPlayerNormalFire();

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

	class ActionFactoryPlayerNormalFire:public ActionFactory
	{
	public:
		ActionFactoryPlayerNormalFire();
		virtual ~ActionFactoryPlayerNormalFire();

		virtual const String& type() const;
		virtual Action* createInstance( Actor* owner, ActionDesc* desc );
		virtual ActionDesc* load( rapidxml::xml_node<>* xmlNode, const String& filename );
		static const String TypeName;
	};
}
#endif