#ifndef ACTIONENERGYBMOBSTOP_H
#define ACTIONENERGYBMOBSTOP_H

#include "Action.h"

namespace Ogre
{
	class ActorEnergyBmob;
	struct IAnimation2D;

	class ActionEnergyBmobStop: public Action
	{
	public:
		ActionEnergyBmobStop(Actor* owner, ActionDesc* desc);
		~ActionEnergyBmobStop();

		virtual void initailze();
		virtual const String& type() const;
		virtual void begin();
		virtual void end();
		virtual void update(Real timelapse);

	private:
		Real				mTimes;
		Real				mWaitTime;
		IAnimation2D*		mEnergyBmobBody;
	};

	class ActionFactoryEnergyBmobStop:public ActionFactory
	{
	public:
		ActionFactoryEnergyBmobStop();
		virtual ~ActionFactoryEnergyBmobStop();
		virtual const String& type() const;
		virtual Action*  createInstance( Actor* owner, ActionDesc* desc );
		virtual  ActionDesc*	load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const	String	TypeName;
	};
}

#endif