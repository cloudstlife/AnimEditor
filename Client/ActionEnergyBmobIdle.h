#ifndef ACTIONENERGYBMOBIDLE_H
#define ACTIONENERGYBMOBIDLE_H

#include "Action.h"

namespace Ogre
{
	class ActorEnergyBmob;
	struct IAnimation2D;

	class ActionEnergyBmobIdle: public Action
	{
	public:
		ActionEnergyBmobIdle(Actor* owner, ActionDesc* desc);
		~ActionEnergyBmobIdle();

		virtual void initailze();
		virtual const String& type() const;
		virtual void begin();
		virtual void end();
		virtual void update(Real timelapse);
		IAnimation2D* getBody();

	private:
		ActorEnergyBmob*	mActorEnergyBmob;
		IAnimation2D*		mEnergyBmobBody;

	};

	class ActionFactoryEnergyBmobIdle:public ActionFactory
	{
	public:
		ActionFactoryEnergyBmobIdle();
		virtual ~ActionFactoryEnergyBmobIdle();
		virtual const String& type() const;
		virtual Action*  createInstance( Actor* owner, ActionDesc* desc );
		virtual  ActionDesc*	load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const	String	TypeName;
	};
}

#endif