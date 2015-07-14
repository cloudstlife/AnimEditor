#ifndef ACTIONENERGYBMOBATTACK_H
#define ACTIONENERGYBMOBATTACK_H

#include "Action.h"

namespace Ogre
{
	class ActorEnergyBmob;
	struct IAnimation2D;

	class ActionEnergyBmobAttack: public Action
	{
		typedef std::set< Actor* >		SetActorHited;
	public:
		ActionEnergyBmobAttack(Actor* owner, ActionDesc* desc);
		~ActionEnergyBmobAttack();

		virtual void initailze();
		virtual const String& type() const;
		virtual void begin();
		virtual void end();
		virtual void update(Real timelapse);
		virtual	void			beginContact( Actor* other );
		virtual	void			endContact( Actor* other );

		IAnimation2D* getBody();

	private:
		ActorEnergyBmob*	mActorEnergyBmob;
		IAnimation2D*		mEnergyBmobBody;
		SetActorHited		mFishHited;

	};

	class ActionFactoryEnergyBmobAttack:public ActionFactory
	{
	public:
		ActionFactoryEnergyBmobAttack();
		virtual ~ActionFactoryEnergyBmobAttack();
		virtual const String& type() const;
		virtual Action*  createInstance( Actor* owner, ActionDesc* desc );
		virtual  ActionDesc*	load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const	String	TypeName;
	};
}

#endif