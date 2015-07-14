#ifndef ACTORENERGYBMOB_H
#define ACTORENERGYBMOB_H

#include "Actor.h"

namespace Ogre
{
	class ActorEnergyBmob:public Actor
	{
	public:
		ActorEnergyBmob(ActorDesc* desc, ISceneNode2D* node, IScene* scene);
		virtual ~ActorEnergyBmob();

		virtual void			initailze();
		virtual void			updateLogic( Real timeLapse );
		virtual const String&	type() const;
		void					fireBmob();
		void					setDir( Real z, Real y ); 
		const Vector2&			getDir();
		void					setActorPlayer(Actor* actor);
		Actor*					getActorPlayer();
		Real					getDistance();

	public:
		DYNAMIC_DECLARE(ActorEnergyBmob);
		
	private:
		Vector2		mDir;
		Actor*		mPlayer;
		Real		mDistance;
	};

	class ActorFactoryEnergyBmob : public ActorFactory
	{
	public:
		ActorFactoryEnergyBmob();
		virtual ~ActorFactoryEnergyBmob();
		virtual const String& type() const;
		virtual Actor* createInstance( ActorDesc* actorDesc, ISceneNode2D* node, IScene* scene, const String& name = "" );
		virtual ActorDesc* load( rapidxml::xml_node<>* xmlNode, const String& filename );
		static const String TypeName;
	};
}

#endif