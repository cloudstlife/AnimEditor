#include "SystemPrerequisites.h"
#include "ActorBullet.h"
#include "ISceneNode2D.h"
#include "ActionBulletFly.h"
#include "ActionBulletAttack.h"

namespace Ogre
{
	struct ActorDescBullet : public ActorDesc
	{
	};

	//---
	DYNAMIC_IMPLEMENT( ActorBullet, GETRTTI( Actor ) )
	ActorBullet::ActorBullet( ActorDesc* desc, ISceneNode2D* node, IScene* scene )
		: Actor( desc, node, scene )
		, mDir( Vector2::UNIT_Y )
		, mPlayer(NULL)
	{
		ActorDescBullet* actorDesc = static_cast< ActorDescBullet* >( desc );
		
		
	}

	ActorBullet::~ActorBullet()
	{
		mPlayer =NULL;
	}
	
	void	ActorBullet::initailze()
	{
		initailzeActions();
	}

	void	ActorBullet::updateLogic( Real timeLapse )
	{
		Actor::updateLogic( timeLapse );
	}

	const String& ActorBullet::type() const
	{
		return ActorFactoryBullet::TypeName;
	}

	void	ActorBullet::setProperty( const String& name, const Any& val )
	{
		Actor::setProperty( name, val );

		
	}

	void	ActorBullet::setDir( Real z, Real y )
	{
		mDir.x = z;
		mDir.y = y;
	}

	const Vector2&	ActorBullet::getDir()
	{
		return mDir;
	}

	void ActorBullet::setActorPlayer(Actor* actor)
	{
		mPlayer = actor;
	}

	Actor* ActorBullet::getActorPlayer()
	{
		return mPlayer;
	}

	//--
	const String ActorFactoryBullet::TypeName = "Bullet";
	ActorFactoryBullet::ActorFactoryBullet()
	{
		registActionFactory( new ActionFactoryBulletFly );
		registActionFactory( new ActionFactoryBulletAttack );
	}

	ActorFactoryBullet::~ActorFactoryBullet()
	{

	}

	const String&	ActorFactoryBullet::type() const
	{
		return ActorFactoryBullet::TypeName;
	}

	Actor*	ActorFactoryBullet::createInstance( ActorDesc* actorDesc, ISceneNode2D* node, IScene* scene, const String& name )
	{
		ActorBullet* actor = new ActorBullet( actorDesc, node, scene );

		//	create actions
		_createActions( actor, actorDesc );

		actor->initailze();

		return actor;
	}

	ActorDesc*	ActorFactoryBullet::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActorDescBullet* actorDesc = new ActorDescBullet;
		_loadBaseActorDesc( actorDesc, xmlNode, filename );
		_loadActionDesc( actorDesc, xmlNode, filename );
		return actorDesc;
	}
}