#include "SystemPrerequisites.h"
#include "ActorGeneratorDiffuse.h"
#include "IActorGeneratorDesc.h"
#include "IScene.h"
#include "ISceneNode2D.h"
#include "NormalActorFish.h"


namespace Ogre
{
	struct DiffuseNode
	{
		Real dir;
	};

	struct ActorGeneratorDescDiffuse: public ActorGeneratorDesc
	{
		ActorGeneratorDescDiffuse()
			: centerPos( Vector2::ZERO )
			, count(0)
			, speed(0.f)
			, loopTime(0.f)
			, lifeTime(0.f)
			, actorName("")
			, fishCount(0)
			, navigName("")
			, fishTime(0.0f)
		{

		}

		Vector2				centerPos; // 中心点
		int					count;	   // 次数（一个周期）
		Real				speed;			//	产生速度
		Real				loopTime;		//	产生周期
		Real				lifeTime;		//	生命周期
		Real				fishTime;		//	鱼的生命周期
		String				actorName;		//  actor名称
		int					fishCount;		// 鱼的数量
		String				navigName;		//	导航名
	};

	ActorGeneratorDiffuse::ActorGeneratorDiffuse(IScene* scene, ActorGeneratorDesc* desc, Vector2 vPos )
		: ActorGenerator( scene, desc )
		, mCenterPos(Vector2::ZERO)
		, mActorName("")
		, mSpeed(1.f)
		, mLoopTime(30.f)
		, mCount( 10 )
		, mFishCount(0)
		, mCurLoopTime(0.0f)
		, mCurCount(0)
		, mCurSpeed(0.0f)
		, mNavigName("")
		, mTimes(0.0f)
		, mFishTime(0.0f)
	{
		ActorGeneratorDescDiffuse *genDesc = static_cast<ActorGeneratorDescDiffuse*>(desc);
		mLifeTime = genDesc->lifeTime;
		mCount = genDesc->count;
		mLoopTime = genDesc->loopTime;
		mSpeed = genDesc->speed;
		mActorName = genDesc->actorName;
		mNavigName = genDesc->navigName;
		mFishCount = genDesc->fishCount;
		mFishTime = genDesc->fishTime;
		mCenterPos = vPos;

		// 计算各自鱼的方向
		Real rStepRotate = 360.0f/mFishCount;// 步长
		Real rRotate = 0;
		for (int iCount = 0; iCount< mFishCount; ++iCount)
		{
			DiffuseNode diffuseNode;
			diffuseNode.dir = 0;
			if (iCount != 0)
			{
				diffuseNode.dir += rRotate;
			}
			listDiffuseNode.push_back(diffuseNode);
			rRotate += rStepRotate;
		}
	}

	ActorGeneratorDiffuse::~ActorGeneratorDiffuse()
	{

	}

	void ActorGeneratorDiffuse::update( Real timeLapse )
	{
		mCurLoopTime += timeLapse;
		mCurSpeed += timeLapse;
		mTimes += timeLapse;
		if (mTimes<= mLifeTime)
		{
			if (mCurLoopTime< mLoopTime)
			{
				if (mCurCount< mCount && mCurSpeed> mSpeed)
				{
					ListDiffuseNode::iterator iter = listDiffuseNode.begin();
					ListDiffuseNode::iterator iterEnd = listDiffuseNode.end();
					for (; iter!= iterEnd; ++iter)
					{
						
						ISceneNode2D* fishNode = mScene->getRootSceneNode()->createChild();
						Actor* actor = mScene->createActor(mActorName, fishNode);
						// 设置鱼的生命周期
						actor->setLifeTime(mFishTime);
						NormalActorFish* actorFish = static_cast<NormalActorFish*>(actor);
						// 创建导航
						Ogre::NameValuePairList param;
						param["pos"] = StringConverter::toString(mCenterPos);
						param["totalTime"] = StringConverter::toString(actorFish->getTotalTime());
						param["dividePoint"] = StringConverter::toString(actorFish->getDividePoint());
						param["firstAffect"] = StringConverter::toString(actorFish->getFirstAffect());
						param["secondAffect"] = StringConverter::toString(actorFish->getSecondAffect());
						param["rotate"] = StringConverter::toString(iter->dir);
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
	}

	const String ActorGeneratorFactoryDiffuse::TypeName = "Diffuse";

	ActorGeneratorFactoryDiffuse::ActorGeneratorFactoryDiffuse()
	{

	}

	ActorGeneratorFactoryDiffuse::~ActorGeneratorFactoryDiffuse()
	{

	}

	const String&	ActorGeneratorFactoryDiffuse::type() const
	{
		return TypeName;
	}

	ActorGenerator*	ActorGeneratorFactoryDiffuse::createInstance( ActorGeneratorDesc* desc, IScene* scene, Vector2 vPos )
	{
		ActorGeneratorDiffuse* actorGen = new ActorGeneratorDiffuse( scene, desc, vPos ); 

		return actorGen;
	}

	ActorGeneratorDesc*		ActorGeneratorFactoryDiffuse::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		ActorGeneratorDescDiffuse* desc = new ActorGeneratorDescDiffuse; 

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

		//-- pos
		/*nodeAttr = xmlNode->first_attribute("pos");
		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "param:pos in config file is empty! file name: " << filename );
		}*/
		//desc->centerPos = StringConverter::parseVector2(nodeAttr->value());

		//-- fishCount
		nodeAttr = xmlNode->first_attribute("fishCount");
		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "param:fishCount in config file is empty! file name: " << filename );
		}
		desc->fishCount = StringConverter::parseInt(nodeAttr->value());
		
		//-- lifeTime
		nodeAttr = xmlNode->first_attribute("lifeTime");
		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "param:fishCount in config file is empty! file name: " << filename );
		}
		desc->lifeTime = StringConverter::parseReal(nodeAttr->value());

		//-- navigName
		nodeAttr = xmlNode->first_attribute("navigName");
		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "param:navigName in config file is empty! file name: " << filename );
		}
		desc->navigName = nodeAttr->value();
		
		//-- fishTime
		nodeAttr = xmlNode->first_attribute("fishTime");
		if (!nodeAttr)
		{
			EXCEPTEX( "param:fishTime in config file is empty! file name: " << filename );
		}
		desc->fishTime = StringConverter::parseReal(nodeAttr->value());
		return desc;
	}
}