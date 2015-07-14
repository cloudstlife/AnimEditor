#include "SystemPrerequisites.h"
#include "ISceneNode2D.h"
#include "ActorEnergyBmob.h"
#include "ActionEnergyBmobIdle.h"
#include "ActionEnergyBmobFly.h"
#include "ActionEnergyBmobAttack.h"
#include "ActionEnergyBmobStop.h"

namespace Ogre
{
	struct ActorDescEnergyBmob: public ActorDesc
	{
		Real			distance;
	};

	DYNAMIC_IMPLEMENT(ActorEnergyBmob, GETRTTI(Actor))
		ActorEnergyBmob::ActorEnergyBmob(ActorDesc* desc, ISceneNode2D* node, IScene* scene)
		: Actor(desc, node, scene)
		, mPlayer(0)
		, mDir(Vector2::ZERO)
		, mDistance(0.0f)
	{
		ActorDescEnergyBmob *genDesc = static_cast<ActorDescEnergyBmob*>(desc);
		mDistance = genDesc->distance;
	}

	ActorEnergyBmob::~ActorEnergyBmob()
	{
		mDir = Vector2::ZERO;
		mDistance = 0.0f;
	}

	void ActorEnergyBmob::initailze()
	{
		initailzeActions();
	}

	void ActorEnergyBmob::updateLogic( Real timeLapse )
	{
		Actor::updateLogic(timeLapse);
	}

	const String& ActorEnergyBmob::type() const
	{
		return ActorFactoryEnergyBmob::TypeName;
	}

	void ActorEnergyBmob::fireBmob()
	{
		this->changeActionTo(ActionFactoryEnergyBmobFly::TypeName);
	}

	void	ActorEnergyBmob::setDir( Real z, Real y )
	{
		mDir.x = z;
		mDir.y = y;
	}

	const Vector2&	ActorEnergyBmob::getDir()
	{
		return mDir;
	}

	void ActorEnergyBmob::setActorPlayer(Actor* actor)
	{
		mPlayer = actor;
	}

	Actor* ActorEnergyBmob::getActorPlayer()
	{
		return mPlayer;
	}

	Real ActorEnergyBmob::getDistance()
	{
		return mDistance;
	}

	const String ActorFactoryEnergyBmob::TypeName = "EnergyBmob";
	ActorFactoryEnergyBmob::ActorFactoryEnergyBmob()
	{
		registActionFactory(new ActionFactoryEnergyBmobIdle);
		registActionFactory(new ActionFactoryEnergyBmobFly);
		registActionFactory(new ActionFactoryEnergyBmobAttack);
		registActionFactory(new ActionFactoryEnergyBmobStop);
	}

	ActorFactoryEnergyBmob::~ActorFactoryEnergyBmob()
	{

	}

	const String& ActorFactoryEnergyBmob::type() const
	{
		return ActorFactoryEnergyBmob::TypeName;
	}

	Actor* ActorFactoryEnergyBmob::createInstance( ActorDesc* actorDesc, ISceneNode2D* node, IScene* scene, const String& name )
	{
		ActorEnergyBmob* actor = new ActorEnergyBmob(actorDesc, node, scene);
		_createActions(actor, actorDesc);
		actor->initailze();
		return actor;
	}

	ActorDesc*	ActorFactoryEnergyBmob::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActorDescEnergyBmob* actorDesc = new ActorDescEnergyBmob;

		_loadBaseActorDesc( actorDesc, xmlNode, filename );

		_loadActionDesc( actorDesc, xmlNode, filename );

		nodeAttr = xmlNode->first_attribute("distance");
		if (!nodeAttr)
		{
			EXCEPTEX( "bmob actor.  need distance. filename: " << filename );
		}

		actorDesc->distance = StringConverter::parseReal(nodeAttr->value());
		return actorDesc;
	}

}