#include "SystemPrerequisites.h"
#include "ActorGeneratorDefault.h"
#include "IActorGeneratorDesc.h"
#include "IScene.h"
#include "ISceneNode2D.h"
#include "NormalActorFish.h"

namespace Ogre
{
	struct ActorGeneratorDescDefault : public ActorGeneratorDesc
	{
		ActorGeneratorDescDefault()
			: pos( Vector2::ZERO )
			, speed( 1.f )
			, loopTime( 30.f )
			, count( 10 )
		{

		}

		Vector2		pos;			//	产生点
		int			count;			//	产生数量
		Real		speed;			//	产生速度
		Real		loopTime;		//	产生周期
		String		actorName;		//	角色名
		String		navigName;		//	导航名
		Real		lifeTime;		//	鱼的生命周期
	};

	ActorGeneratorDefault::ActorGeneratorDefault( IScene* scene, ActorGeneratorDesc* desc,Vector2 vPos )
		: ActorGenerator( scene, desc )
		, mPos( Vector2::ZERO )
		, mSpeed( 1.f )
		, mLoopTime( 30.f )
		, mCount( 10 )
		, mCurLoopTime(0.0f)
		, mCurCount(0)
		, mCurSpeed(0.0f)
		, mLifeTime(0.0f)
	{
		ActorGeneratorDescDefault* genDesc = static_cast< ActorGeneratorDescDefault* >( desc );

		mCount = genDesc->count;
		mLoopTime = genDesc->loopTime;
		mSpeed = genDesc->speed;
		mActorName = genDesc->actorName;
		mNavigName = genDesc->navigName;
		mLifeTime = genDesc->lifeTime;
		mPos = vPos;
	}

	ActorGeneratorDefault::~ActorGeneratorDefault()
	{

	}

	void	ActorGeneratorDefault::update( Real timeLapse )
	{
		mCurLoopTime += timeLapse;
		mCurSpeed += timeLapse;
		if (mCurLoopTime< mLoopTime)
		{
			if (mCurCount< mCount && mCurSpeed> mSpeed)
			{
				ISceneNode2D* fishNode = mScene->getRootSceneNode()->createChild();
				Actor* actor = mScene->createActor(mActorName, fishNode);
				NormalActorFish* actorFish = static_cast<NormalActorFish*>(actor);
				actorFish->setLifeTime(mLifeTime);
				// 创建导航
				Ogre::NameValuePairList param;
				param["pos"] = StringConverter::toString(mPos);
				param["totalTime"] = StringConverter::toString(actorFish->getTotalTime());
				param["dividePoint"] = StringConverter::toString(actorFish->getDividePoint());
				param["firstAffect"] = StringConverter::toString(actorFish->getFirstAffect());
				param["secondAffect"] = StringConverter::toString(actorFish->getSecondAffect());
				param["defaultSpeed"] = StringConverter::toString(actorFish->getDefaultSpeed());

				fishNode->createNavigation(mNavigName, param);
				mCurCount++;
				mCurSpeed = 0;
			}
		}
		else
		{
			mCurCount = 0;
			mCurSpeed = 0;
			mCurLoopTime = 0;
		}
	}


	const String ActorGeneratorFactoryDefault::TypeName = "Default";

	ActorGeneratorFactoryDefault::ActorGeneratorFactoryDefault()
	{

	}

	ActorGeneratorFactoryDefault::~ActorGeneratorFactoryDefault()
	{

	}

	const String&	ActorGeneratorFactoryDefault::type() const
	{
		return TypeName;
	}

	ActorGenerator*	ActorGeneratorFactoryDefault::createInstance( ActorGeneratorDesc* desc, IScene* scene, Vector2 vPos )
	{
		ActorGeneratorDefault* actorGen = new ActorGeneratorDefault( scene, desc, vPos ); 

		return actorGen;
	}

	ActorGeneratorDesc*		ActorGeneratorFactoryDefault::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		ActorGeneratorDescDefault* desc = new ActorGeneratorDescDefault; 

		xml_attribute<>* nodeAttr = 0;

		_loadBaseDesc( desc, xmlNode, filename );

		//-- count
		nodeAttr = xmlNode->first_attribute( "count" );

		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "param:count in config file is empty! file name: " << filename );
		}
		desc->count = StringConverter::parseInt( nodeAttr->value() );

		//-- speed
		nodeAttr = xmlNode->first_attribute( "speed" );

		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "param:speed in config file is empty! file name: " << filename );
		}
		desc->speed = StringConverter::parseReal( nodeAttr->value() );

		//-- loopTime
		nodeAttr = xmlNode->first_attribute( "loopTime" );

		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "param:loopTime in config file is empty! file name: " << filename );
		}
		desc->loopTime = StringConverter::parseReal( nodeAttr->value() );

		//-- actorName
		nodeAttr = xmlNode->first_attribute( "actorName" );

		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "param:actorName in config file is empty! file name: " << filename );
		}
		desc->actorName = nodeAttr->value();

		//-- navigName
		nodeAttr = xmlNode->first_attribute( "navigName" );

		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "param:navigName in config file is empty! file name: " << filename );
		}
		desc->navigName = nodeAttr->value();

		//-- lifeTime
		nodeAttr = xmlNode->first_attribute("lifeTime");
		if (!nodeAttr)
		{
			EXCEPTEX( "param:lifeTime in config file is empty! file name: " << filename );
		}
		desc->lifeTime = StringConverter::parseReal(nodeAttr->value());

		return desc;
	}
}