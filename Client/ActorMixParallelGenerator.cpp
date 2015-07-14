#include "SystemPrerequisites.h"
#include "ActorMixParallelGenerator.h"
#include "IActorGeneratorDesc.h"
#include "IScene.h"
#include "ISceneNode2D.h"
#include "NormalActorFish.h"

namespace Ogre
{
	struct MixParallelNode
	{
		String		actorName;
		Vector2		pos;
	};

	typedef std::list< MixParallelNode >ListMixParallelNode;

	struct ActorGeneratorDescMixParallel: public ActorGeneratorDesc
	{
		ActorGeneratorDescMixParallel()
			: pos( Vector2::ZERO )
			, speed( 1.f )
			, loopTime( 30.f )
			, count( 10 )
			, lifeTime(0.0f)
		{

		}

		Vector2				pos;			//	产生点
		int					count;			//	产生数量
		Real				speed;			//	产生速度
		Real				loopTime;		//	产生周期
		String				navigName;		//	导航名
		Real				lifeTime;		//	
		ListMixParallelNode listMixParallNode;
	};

	ActorMixParallelGenerator::ActorMixParallelGenerator(IScene* scene, ActorGeneratorDesc* desc, Vector2 vPos)
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
		ActorGeneratorDescMixParallel *genDesc = static_cast<ActorGeneratorDescMixParallel*>(desc);
		mCount = genDesc->count;
		mLoopTime = genDesc->loopTime;
		mSpeed = genDesc->speed;
		mNavigName = genDesc->navigName;
		mLifeTime = genDesc->lifeTime;
		mPos = vPos;
		mDesc = genDesc;
	}

	ActorMixParallelGenerator::~ActorMixParallelGenerator()
	{

	}

	void ActorMixParallelGenerator::update(Real timeLapse)
	{
		mCurLoopTime += timeLapse;
		mCurSpeed += timeLapse;
		if (mCurLoopTime< mLoopTime)
		{
			if (mCurCount< mCount && mCurSpeed> mSpeed)
			{
				ListMixParallelNode::iterator iter = mDesc->listMixParallNode.begin();
				ListMixParallelNode::iterator iterEnd = mDesc->listMixParallNode.end();
				for (; iter!= iterEnd; ++iter)
				{
					ISceneNode2D* fishNode = mScene->getRootSceneNode()->createChild();
					Actor* actor = mScene->createActor(iter->actorName, fishNode);
					NormalActorFish* actorFish = static_cast<NormalActorFish*>(actor);
					actorFish->setLifeTime(mLifeTime);
					// 创建导航
					Ogre::NameValuePairList param;
					param["pos"] = StringConverter::toString(mPos);
					param["totalTime"] = StringConverter::toString(actorFish->getTotalTime());
					param["dividePoint"] = StringConverter::toString(actorFish->getDividePoint());
					param["firstAffect"] = StringConverter::toString(actorFish->getFirstAffect());
					param["secondAffect"] = StringConverter::toString(actorFish->getSecondAffect());
					param["offset"] = StringConverter::toString(iter->pos);
					param["defaultSpeed"] = StringConverter::toString(actorFish->getDefaultSpeed());

					fishNode->createNavigation(mNavigName, param);
				}
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

	const String ActorGeneratorFactoryMixParallel::TypeName = "MixParallel";

	ActorGeneratorFactoryMixParallel::ActorGeneratorFactoryMixParallel()
	{

	}

	ActorGeneratorFactoryMixParallel::~ActorGeneratorFactoryMixParallel()
	{

	}

	const String&	ActorGeneratorFactoryMixParallel::type() const
	{
		return TypeName;
	}

	ActorGenerator*	ActorGeneratorFactoryMixParallel::createInstance( ActorGeneratorDesc* desc, IScene* scene, Vector2 vPos )
	{
		ActorMixParallelGenerator* actorGen = new ActorMixParallelGenerator( scene, desc, vPos ); 

		return actorGen;
	}

	ActorGeneratorDesc*		ActorGeneratorFactoryMixParallel::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		ActorGeneratorDescMixParallel* desc = new ActorGeneratorDescMixParallel; 

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

		//-- navigName
		nodeAttr = xmlNode->first_attribute( "navigName" );
		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "param:navigName in config file is empty! file name: " << filename );
		}
		desc->navigName = nodeAttr->value();

		//-- lifeTime
		nodeAttr = xmlNode->first_attribute("lifeTime");
		if (nodeAttr == 0)
		{
			EXCEPTEX( "param:lifeTime in config file is empty! file name: " << filename );
		}
		desc->lifeTime = StringConverter::parseReal(nodeAttr->value());

		// body
		xml_node<>* bodyNode = xmlNode->first_node("body");
		while (bodyNode)
		{
			MixParallelNode mixParallelNode;
			nodeAttr = bodyNode->first_attribute("actorName");
			mixParallelNode.actorName = nodeAttr->value();
			nodeAttr = bodyNode->first_attribute("pos");
			mixParallelNode.pos = StringConverter::parseVector2(nodeAttr->value());
			desc->listMixParallNode.push_back(mixParallelNode);
			bodyNode = bodyNode->next_sibling("body");
		}
		return desc;
	}
}