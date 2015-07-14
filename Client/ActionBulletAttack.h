#ifndef ACTIONBULLETATTACK_H
#define ACTIONBULLETATTACK_H
#include "Action.h"

namespace Ogre
{
	class ActorBullet; 
	struct IAnimation2D;

	class ActionBulletAttack : public Action
	{
		typedef std::set< Actor* >		SetActorHited;
	public:
		ActionBulletAttack( Actor* owner, ActionDesc* desc );
		~ActionBulletAttack();

		virtual	void			initailze();
		virtual const String&	type() const;
		virtual	void			begin();
		virtual	void			end();
		virtual	void			update( Real timelapse );

		virtual	void			beginContact( Actor* other );
		virtual	void			endContact( Actor* other );

	private:
		ActorBullet*		mActorBullet;
		IAnimation2D*		mBulletAttack;
		SetActorHited		mFishHited;
	};


	class ActionFactoryBulletAttack : public ActionFactory
	{
	public:
		ActionFactoryBulletAttack();
		virtual ~ActionFactoryBulletAttack();

		virtual const String&	type() const;

		virtual Action*			createInstance( Actor* owner, ActionDesc* desc );

		virtual  ActionDesc*	load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const	String	TypeName;
	};
}

#endif