#include "SystemPrerequisites.h"
#include "ActorStatic.h"
#include "ISceneNode2D.h"
#include "ActionStaticStand.h"

namespace Ogre
{
	struct ActorDescStatic : public ActorDesc
	{

	};

	//---
	DYNAMIC_IMPLEMENT( ActorStatic, GETRTTI( Actor ) )
	ActorStatic::ActorStatic( ActorDesc* desc, ISceneNode2D* node, IScene* scene, const String& name )
		: Actor( desc, node, scene, "" )
	{

	}

	ActorStatic::~ActorStatic()
	{

	}
	
	void	ActorStatic::initailze()
	{



		initailzeActions();
	}

	void	ActorStatic::updateLogic( Real timeLapse )
	{
		Actor::updateLogic( timeLapse );
	}

	const String& ActorStatic::type() const
	{
		return ActorFactoryStatic::TypeName;
	}

	void	ActorStatic::setProperty( const String& name, const Any& val )
	{
		Actor::setProperty( name, val );

		if ( name == "testProperty" )
		{
			testProperty = val.get< int >();
		}
	}

	//--
	const String ActorFactoryStatic::TypeName = "Static";
	ActorFactoryStatic::ActorFactoryStatic()
	{
		registActionFactory( new ActionFactoryStaticStand );
	}

	ActorFactoryStatic::~ActorFactoryStatic()
	{

	}

	const String&	ActorFactoryStatic::type() const
	{
		return ActorFactoryStatic::TypeName;
	}

	Actor*	ActorFactoryStatic::createInstance( ActorDesc* actorDesc, ISceneNode2D* node, IScene* scene, const String& name )
	{
		ActorStatic* actor = new ActorStatic( actorDesc, node, scene );

		//	create actions
		_createActions( actor, actorDesc );

		actor->initailze();

		return actor;
	}

	ActorDesc*	ActorFactoryStatic::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActorDescStatic* actorDesc = new ActorDescStatic;

		_loadBaseActorDesc( actorDesc, xmlNode, filename );

		_loadActionDesc( actorDesc, xmlNode, filename );

		return actorDesc;
	}
}