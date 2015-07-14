#include "SystemPrerequisites.h"
#include "ActorFish.h"

namespace Ogre
{
	struct ActorDescFish : public ActorDesc
	{
	};

	//---
	DYNAMIC_IMPLEMENT( ActorFish, GETRTTI( Actor ) )
		ActorFish::ActorFish( ActorDesc* desc, ISceneNode2D* node, IScene* scene, const String& name )
		: Actor( desc, node, scene, "" )
	{
	}

	ActorFish::~ActorFish()
	{
	}

	void ActorFish::initailze()
	{

	}

	void ActorFish::updateLogic( Real timeLapse )
	{
		Actor::updateLogic( timeLapse );
		mTimes += timeLapse;
		if (mTimes> mLifeTime && mLifeTime > 0)
		{
			valid();
			mTimes = 0;
		}
	}

	const String& ActorFish::type() const
	{
		return ActorFactoryFish::TypeName;
	}

	void ActorFish::setProperty( const String& name, const Any& val )
	{

	}

	const String ActorFactoryFish::TypeName = "Fish";
	ActorFactoryFish::ActorFactoryFish()
	{
	}

	ActorFactoryFish::~ActorFactoryFish()
	{

	}

	const String&	ActorFactoryFish::type() const
	{
		return ActorFactoryFish::TypeName;
	}

	Actor*	ActorFactoryFish::createInstance( ActorDesc* actorDesc, ISceneNode2D* node, IScene* scene )
	{
		ActorFish* actor = new ActorFish( actorDesc, node, scene );

		//	create actions
		_createActions( actor, actorDesc );


		actor->initailze();

		return actor;
	}

	ActorDesc*	ActorFactoryFish::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActorDescFish* actorDesc = new ActorDescFish;

		_loadBaseActorDesc( actorDesc, xmlNode, filename );

		_loadActionDesc( actorDesc, xmlNode, filename );

		return actorDesc;
	}
}