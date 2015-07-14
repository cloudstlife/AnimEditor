#include "SystemPrerequisites.h"
#include "NormalActorFish.h"
#include "ISceneNode2D.h"
#include "ActionFishMove.h"
#include "ActionFishHurt.h"
#include "ActionFishDied.h"

namespace Ogre
{
	struct ActorDescNormalFish : public ActorDesc
	{
		ActorDescNormalFish::ActorDescNormalFish()
			: defaultSpeed(0.0f)
			, odds(0)
			, lifeTime(0.0f)
			, totalTime(0.0f)
			, dividePoint(0.0f)
			, firstAffect(0.0f)
			, secondAffect(0.0f)
			, energy(0)
		{

		}
		Real			defaultSpeed;
		int				odds;
		Real			lifeTime;
		Real			totalTime;
		Real			dividePoint;
		Real			firstAffect;
		Real			secondAffect;
		int				energy;
	};

	//---
	DYNAMIC_IMPLEMENT( NormalActorFish, GETRTTI( ActorFish ) )
	NormalActorFish::NormalActorFish( ActorDesc* desc, ISceneNode2D* node, IScene* scene )
		: ActorFish( desc, node, scene )
		, mPlayer(NULL)
		, mTotalTime(0)
		, mDividePoint(0)
		, mFirstAffect(0)
		, mSecondAffect(0)
		, mOdds(0)
		, mDefaultSpeed(0.0f)
		, mEnergy(0)
	{
		ActorDescNormalFish *actorDesc = static_cast<ActorDescNormalFish*>(desc);
		mTotalTime = actorDesc->totalTime;
		mDividePoint = actorDesc->dividePoint;
		mFirstAffect = actorDesc->firstAffect;
		mSecondAffect = actorDesc->secondAffect;
		mDefaultSpeed = actorDesc->defaultSpeed;
		mEnergy = actorDesc->energy;
		mOdds = actorDesc->odds;
	}

	NormalActorFish::~NormalActorFish()
	{
		mOdds = 0;
		mTotalTime = 0;
		mDividePoint = 0;
		mFirstAffect = 0;
		mSecondAffect = 0;
		mDefaultSpeed = 0;
		mEnergy = 0;
	}
	
	void	NormalActorFish::initailze()
	{
		initailzeActions();
	}

	void	NormalActorFish::updateLogic( Real timeLapse )
	{
		ActorFish::updateLogic( timeLapse );
	}

	const String& NormalActorFish::type() const
	{
		return ActorFactoryNormalFish::TypeName;
	}

	void	NormalActorFish::setProperty( const String& name, const Any& val )
	{
		ActorFish::setProperty( name, val );
	}

	void NormalActorFish::setActorPlayer(Actor* actor)
	{
		mPlayer = actor;
	}

	Actor* NormalActorFish::getActorPlayer()
	{
		return mPlayer;
	}

	Real		NormalActorFish::getTotalTime()
	{
		return mTotalTime;
	}

	Real		NormalActorFish::getDividePoint()
	{
		return mDividePoint;
	}

	Real		NormalActorFish::getFirstAffect()
	{
		return mFirstAffect;
	}

	Real		NormalActorFish::getSecondAffect()
	{
		return mSecondAffect;
	}

	int		NormalActorFish::getOdds()
	{
		return mOdds;
	}

	int		NormalActorFish::getEnergy()
	{
		return mEnergy;
	}

	Real	NormalActorFish::getDefaultSpeed()
	{
		return mDefaultSpeed;
	}

	//--
	const String ActorFactoryNormalFish::TypeName = "NormalFish";
	ActorFactoryNormalFish::ActorFactoryNormalFish()
	{
		registActionFactory( new ActionFactoryFishMove );
		registActionFactory( new ActionFactoryFishHurt );
		registActionFactory( new ActionFactoryFishDied );
	}

	ActorFactoryNormalFish::~ActorFactoryNormalFish()
	{

	}

	const String&	ActorFactoryNormalFish::type() const
	{
		return ActorFactoryNormalFish::TypeName;
	}

	Actor*	ActorFactoryNormalFish::createInstance( ActorDesc* actorDesc, ISceneNode2D* node, IScene* scene, const String& name )
	{
		NormalActorFish* actor = new NormalActorFish( actorDesc, node, scene );

		//	create actions
		_createActions( actor, actorDesc );
		

		actor->initailze();

		return actor;
	}

	ActorDesc*	ActorFactoryNormalFish::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActorDescNormalFish* actorDesc = new ActorDescNormalFish;

		_loadBaseActorDesc( actorDesc, xmlNode, filename );

		_loadActionDesc( actorDesc, xmlNode, filename );

		//defaultSpeed
		nodeAttr = xmlNode->first_attribute("defaultSpeed");
		if (!nodeAttr)
		{
			EXCEPTEX( "param:defaultSpeed in config file is empty! file name: " << filename );
		}
		actorDesc->defaultSpeed = StringConverter::parseReal(nodeAttr->value());

		// odds
		nodeAttr = xmlNode->first_attribute("odds");
		if (nodeAttr)
		{
			actorDesc->odds = StringConverter::parseInt(nodeAttr->value());
		}

		// affect
		nodeAttr = xmlNode->first_attribute("totalTime");
		if (nodeAttr)
		{
			actorDesc->totalTime = StringConverter::parseReal(nodeAttr->value());
		}

		nodeAttr = xmlNode->first_attribute("dividePoint");
		if (nodeAttr)
		{
			actorDesc->dividePoint = StringConverter::parseReal(nodeAttr->value());
		}

		nodeAttr = xmlNode->first_attribute("firstAffect");
		if (nodeAttr)
		{
			actorDesc->firstAffect = StringConverter::parseReal(nodeAttr->value());
		}

		nodeAttr = xmlNode->first_attribute("secondAffect");
		if (nodeAttr)
		{
			actorDesc->secondAffect = StringConverter::parseReal(nodeAttr->value());
		}

		nodeAttr = xmlNode->first_attribute("energy");
		if (nodeAttr)
		{
			actorDesc->energy = StringConverter::parseInt(nodeAttr->value());
		}

		return actorDesc;
	}
}