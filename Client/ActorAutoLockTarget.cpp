#include "SystemPrerequisites.h"
#include "ISceneNode2D.h"
#include "ActorAutoLockTarget.h"
#include "ActionAutoLockTarget.h"

namespace Ogre
{
	struct ActorDescAutoLockTarget: public ActorDesc
	{

	};

	DYNAMIC_IMPLEMENT(ActorAutoLockTarget, GETRTTI(Actor))
		ActorAutoLockTarget::ActorAutoLockTarget(ActorDesc* desc, ISceneNode2D* node, IScene* scene)
		: Actor(desc, node, scene)
		, mPlayer(0)
	{
		ActorDescAutoLockTarget *genDesc = static_cast<ActorDescAutoLockTarget*>(desc);

	}

	ActorAutoLockTarget::~ActorAutoLockTarget()
	{

	}

	void ActorAutoLockTarget::initailze()
	{
		initailzeActions();
	}

	void ActorAutoLockTarget::updateLogic( Real timeLapse )
	{
		Actor::updateLogic(timeLapse);
	}

	const String& ActorAutoLockTarget::type() const
	{
		return ActorFactoryAutoLockTarget::TypeName;
	}

	void ActorAutoLockTarget::setActorPlayer(Actor* actor)
	{
		mPlayer = actor;
	}

	Actor* ActorAutoLockTarget::getActorPlayer()
	{
		return mPlayer;
	}

	const String ActorFactoryAutoLockTarget::TypeName = "AutoLockTarget";
	ActorFactoryAutoLockTarget::ActorFactoryAutoLockTarget()
	{
		registActionFactory(new ActionFactoryAutoLockTarget);
	}

	ActorFactoryAutoLockTarget::~ActorFactoryAutoLockTarget()
	{

	}

	const String& ActorFactoryAutoLockTarget::type() const
	{
		return ActorFactoryAutoLockTarget::TypeName;
	}

	Actor* ActorFactoryAutoLockTarget::createInstance( ActorDesc* actorDesc, ISceneNode2D* node, IScene* scene, const String& name )
	{
		ActorAutoLockTarget* actor = new ActorAutoLockTarget(actorDesc, node, scene);
		_createActions(actor, actorDesc);
		actor->initailze();
		return actor;
	}

	ActorDesc*	ActorFactoryAutoLockTarget::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActorDescAutoLockTarget* actorDesc = new ActorDescAutoLockTarget;

		_loadBaseActorDesc( actorDesc, xmlNode, filename );

		_loadActionDesc( actorDesc, xmlNode, filename );

		return actorDesc;
	}
}