#include "SystemPrerequisites.h"
#include "IActorGeneratorDesc.h"
#include "IScene.h"
#include "ISceneNode2D.h"
#include "NormalActorFish.h"
#include "ActorGeneratorRoundDiffuse.h"
#pragma   comment(lib, "winmm.lib ")

namespace Ogre
{
	struct ActorGeneratorDescRoundDiffuse: public ActorGeneratorDesc
	{
		ActorGeneratorDescRoundDiffuse()
			: actorName("")
			, count(0)
			, diffuseTime(0.0f)
			, lifeTime(0.0f)
			, navigName("")
			, dir(0)
		{

		}

		String			actorName;
		int				count;
		Real			diffuseTime;
		Real			lifeTime;
		String			navigName;
		Real			radius;
		int				dir;
	};

	ActorGeneratorRoundDiffuse::ActorGeneratorRoundDiffuse(IScene* scene, ActorGeneratorDesc* desc, Vector2 vPos)
		: ActorGenerator(scene, desc)
		, mFishCount(0)
		, mActorName("")
		, mCurSpeed(0.0f)
		, mNavigName("")
		, mLifeTime(0.0f)
		, mDiffuseTime(0.0f)
		, mTimes(0.0f)
		, mBStart(false)
		, mCenterPos(Vector2::ZERO)
		, mRotateDir(0)
	{
		ActorGeneratorDescRoundDiffuse *genDesc = static_cast<ActorGeneratorDescRoundDiffuse*>(desc);
		mFishCount = genDesc->count;
		mActorName = genDesc->actorName;
		mDiffuseTime = genDesc->diffuseTime;
		mLifeTime = genDesc->lifeTime;
		mNavigName = genDesc->navigName;
		mRadius = genDesc->radius;
		mRotateDir = genDesc->dir;
		mBStart = true;
		mCenterPos = vPos;
		// 计算各自鱼的开始位置
		Real rStepRotate = 360.0f/mFishCount;// 步长
		Real rRotate = 0.0f;
		for (int iCount = 0; iCount< mFishCount; ++iCount)
		{
			if (iCount == 0)
			{
				rRotate = 0.0f;
			}
			else
			{
				rRotate += rStepRotate;
			}
			vectFishNode.push_back(rRotate);
		}
		//vectFishNode
	}

	ActorGeneratorRoundDiffuse::~ActorGeneratorRoundDiffuse()
	{

	}

	void ActorGeneratorRoundDiffuse::update(Real timeLapse)
	{
		if (mBStart)
		{
			std::vector<Real>::iterator iter = vectFishNode.begin();
			std::vector<Real>::iterator iterEnd = vectFishNode.end();
			for (; iter!= iterEnd; ++iter)
			{
				DWORD leaveTime = timeGetTime();
				printf("roundleaveTime = %u\n", leaveTime);
				ISceneNode2D* fishNode = mScene->getRootSceneNode()->createChild();
				Actor* actor = mScene->createActor(mActorName, fishNode);
				// 设置鱼的生命周期
				actor->setLifeTime(mLifeTime);
				NormalActorFish* actorFish = static_cast<NormalActorFish*>(actor);
				// 创建导航
				Ogre::NameValuePairList param;
				param["pos"] = StringConverter::toString(mCenterPos);
				param["totalTime"] = StringConverter::toString(actorFish->getTotalTime());
				param["dividePoint"] = StringConverter::toString(actorFish->getDividePoint());
				param["firstAffect"] = StringConverter::toString(actorFish->getFirstAffect());
				param["secondAffect"] = StringConverter::toString(actorFish->getSecondAffect());
				param["centerPos"] = StringConverter::toString(mCenterPos);
				param["radius"] = StringConverter::toString(mRadius);
				param["diffuseTime"] = StringConverter::toString(mDiffuseTime);
				param["rotate"] = StringConverter::toString(*iter);
				param["dir"] = StringConverter::toString(mRotateDir);
				param["defaultSpeed"] = StringConverter::toString(actorFish->getDefaultSpeed());

				fishNode->createNavigation(mNavigName, param);

				DWORD newLeaveTime = timeGetTime();
				printf("roundFishLeaveTime = %u\n", newLeaveTime);
				newLeaveTime -= leaveTime;
				printf("ccnewroundLeaveTime = %u\n", newLeaveTime);
			}
			mBStart = false;
		}
	}

	const String ActorGeneratorFactoryRoundDiffuse::TypeName = "RoundDiffuse";

	ActorGeneratorFactoryRoundDiffuse::ActorGeneratorFactoryRoundDiffuse()
	{

	}

	ActorGeneratorFactoryRoundDiffuse::~ActorGeneratorFactoryRoundDiffuse()
	{

	}

	const String&	ActorGeneratorFactoryRoundDiffuse::type() const
	{
		return TypeName;
	}

	ActorGenerator*	ActorGeneratorFactoryRoundDiffuse::createInstance( ActorGeneratorDesc* desc, IScene* scene, Vector2 vPos )
	{
		ActorGeneratorRoundDiffuse* actorGen = new ActorGeneratorRoundDiffuse( scene, desc, vPos ); 

		return actorGen;
	}

	ActorGeneratorDesc*		ActorGeneratorFactoryRoundDiffuse::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		ActorGeneratorDescRoundDiffuse* desc = new ActorGeneratorDescRoundDiffuse; 

		xml_attribute<>* nodeAttr = 0;

		_loadBaseDesc( desc, xmlNode, filename );

		//-- count
		nodeAttr = xmlNode->first_attribute( "fishCount" );

		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "param:count in config file is empty! file name: " << filename );
		}

		desc->count = StringConverter::parseInt( nodeAttr->value() );


		//-- actorName
		nodeAttr = xmlNode->first_attribute( "actorName" );
		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "param:actorName in config file is empty! file name: " << filename );
		}
		desc->actorName = nodeAttr->value();

		//-- fishCount
		nodeAttr = xmlNode->first_attribute("fishCount");
		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "param:fishCount in config file is empty! file name: " << filename );
		}
		desc->count = StringConverter::parseInt(nodeAttr->value());
		
		//-- lifeTime
		nodeAttr = xmlNode->first_attribute("lifeTime");
		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "param:fishCount in config file is empty! file name: " << filename );
		}
		desc->lifeTime = StringConverter::parseReal(nodeAttr->value());

		//-- diffuseTime
		nodeAttr = xmlNode->first_attribute("diffuseTime");
		if (nodeAttr== 0)
		{
			EXCEPTEX( "param:diffuseTime in config file is empty! file name: " << filename );
		}
		desc->diffuseTime = StringConverter::parseReal(nodeAttr->value());

		nodeAttr = xmlNode->first_attribute("dir");
		if (nodeAttr== 0)
		{
			EXCEPTEX( "param:dir in config file is empty! file name: " << filename );
		}
		desc->dir = StringConverter::parseInt(nodeAttr->value());

		nodeAttr = xmlNode->first_attribute("radius");
		if (nodeAttr== 0)
		{
			EXCEPTEX( "param:radius in config file is empty! file name: " << filename );
		}
		desc->radius = StringConverter::parseReal(nodeAttr->value());

		//-- navigName
		nodeAttr = xmlNode->first_attribute("navigName");
		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "param:navigName in config file is empty! file name: " << filename );
		}
		desc->navigName = nodeAttr->value();
		return desc;
	}
}