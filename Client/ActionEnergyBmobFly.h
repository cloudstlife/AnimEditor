#ifndef ACTIONENERGYBMOBFLY_H
#define ACTIONENERGYBMOBFLY_H

#include "Action.h"

namespace Ogre
{
	class ActorEnergyBmob;
	struct IAnimation2D;

	class ActionEnergyBmobFly: public Action
	{
	public:
		ActionEnergyBmobFly(Actor* owner, ActionDesc* desc);
		~ActionEnergyBmobFly();

		virtual void initailze();
		virtual const String& type() const;
		virtual void begin();
		virtual void end();
		virtual void update(Real timelapse);
		IAnimation2D* getBody();

	private:
		ActorEnergyBmob*	mActorEnergyBmob;
		IAnimation2D*		mEnergyBmobBody;
		Real				mSpeed;
	};

	class ActionFactoryEnergyBmobFly:public ActionFactory
	{
	public:
		ActionFactoryEnergyBmobFly();
		virtual ~ActionFactoryEnergyBmobFly();
		virtual const String& type() const;
		virtual Action*  createInstance( Actor* owner, ActionDesc* desc );
		virtual  ActionDesc*	load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const	String	TypeName;
	};
}

#endif