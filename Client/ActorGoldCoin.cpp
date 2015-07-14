#include "SystemPrerequisites.h"
#include "ActorGoldCoin.h"
#include "ISceneNode2D.h"
#include "ActionGoldCoinGet.h"

namespace Ogre
{
	struct ActorDescGoldCoin: public ActorDesc
	{

	};

	DYNAMIC_IMPLEMENT(ActorGoldCoin, GETRTTI(Actor))
	ActorGoldCoin::ActorGoldCoin(ActorDesc* desc, ISceneNode2D* node, IScene* scene)
	:Actor(desc, node, scene)
	, mPlayer(NULL)
	, mOdds(0)
	, mEnergy(0)
	{

	}

	ActorGoldCoin::~ActorGoldCoin()
	{
		mOdds = 0;
		mEnergy = 0;
	}

	void ActorGoldCoin::initailze()
	{
		initailzeActions();
	}

	void ActorGoldCoin::updateLogic( Real timeLapse )
	{
		Actor::updateLogic(timeLapse);
	}

	const String& ActorGoldCoin::type() const
	{
		return ActorFactoryGoldCoin::TypeName;
	}

	void ActorGoldCoin::setProperty(const String& name, const Any& val)
	{
		Actor::setProperty(name, val);
	}

	void ActorGoldCoin::setActorPlayer(Actor* actor)
	{
		mPlayer = actor;
	}

	Actor* ActorGoldCoin::getActorPlayer()
	{
		return mPlayer;
	}

	void	ActorGoldCoin::setFishOdds(int val)
	{
		mOdds = val;
	}

	int		ActorGoldCoin::getFishOdds()
	{
		return mOdds;
	}

	void	ActorGoldCoin::setEnergy(int val)
	{
		mEnergy = val;
	}

	int		ActorGoldCoin::getEnergy()
	{
		return mEnergy;
	}

	const String ActorFactoryGoldCoin::TypeName = "Gold";
	ActorFactoryGoldCoin::ActorFactoryGoldCoin()
	{
		registActionFactory(new ActionFactoryGoldCoin);
	}

	ActorFactoryGoldCoin::~ActorFactoryGoldCoin()
	{

	}

	const String& ActorFactoryGoldCoin::type() const
	{
		return ActorFactoryGoldCoin::TypeName;
	}

	Actor* ActorFactoryGoldCoin::createInstance( ActorDesc* actorDesc, ISceneNode2D* node, IScene* scene, const String& name )
	{
		ActorGoldCoin* actor = new ActorGoldCoin(actorDesc, node, scene);
		_createActions(actor, actorDesc);
		actor->initailze();
		return actor;
	}

	ActorDesc*	ActorFactoryGoldCoin::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActorDescGoldCoin* actorDesc = new ActorDescGoldCoin;

		_loadBaseActorDesc( actorDesc, xmlNode, filename );

		_loadActionDesc( actorDesc, xmlNode, filename );

		return actorDesc;
	}
}