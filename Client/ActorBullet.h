#ifndef ACTORBULLET_H
#define ACTORBULLET_H
#include "Actor.h"

namespace Ogre
{
	class ActorBullet : public Actor
	{
	public:
		ActorBullet( ActorDesc* desc, ISceneNode2D* node, IScene* scene );
		virtual ~ActorBullet();

		virtual	void			initailze();
		virtual	void			updateLogic( Real timeLapse );
		virtual const String&	type() const;
		virtual void			setProperty( const String& name, const Any& val );

		void					setDir( Real z, Real y ); 
		const Vector2&			getDir();
		void					setActorPlayer(Actor* actor);
		Actor*					getActorPlayer();

	public:
		DYNAMIC_DECLARE( ActorBullet );

	private:
		Vector2		mDir;
		Actor*		mPlayer;
	};

	class ActorFactoryBullet : public ActorFactory
	{
	public:
		ActorFactoryBullet();
		virtual ~ActorFactoryBullet();

		virtual const String&	type() const;

		virtual Actor*			createInstance( ActorDesc* actorDesc, ISceneNode2D* node, IScene* scene, const String& name = "" );

		virtual  ActorDesc*		load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const String		TypeName;
	};
}


#endif