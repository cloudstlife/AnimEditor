#include "SystemPrerequisites.h"
#include "ActorGeneratorRandomChase.h"
#include "IActorGeneratorDesc.h"
#include "IScene.h"
#include "ISceneNode2D.h"
#include "NormalActorFish.h"
#include "ogre_src_v1-8-1/OgreViewport.h"

#include <ctime>

namespace Ogre
{
	struct ActorGeneratorDescRandomChase:public ActorGeneratorDesc 
	{
		ActorGeneratorDescRandomChase()
			: actorName("")
			//, centerPos(Vector2::ZERO)
			, width(0.0f)
			, height(0.0f)
			, fishCount(0)
			, destCount(0)
			, refreshDestTime(0.0f)
			, refreshFishTime(0.0f)
			, navigName("")
		{

		}
		String			actorName;
		//Vector2			centerPos;
		Real			width;
		Real			height;
		int				fishCount;
		int				destCount;
		Real			refreshDestTime;
		Real			refreshFishTime;
		String			navigName;
	};

	ActorGeneratorRandomChase::ActorGeneratorRandomChase(IScene* scene, ActorGeneratorDesc* desc, Vector2 vPos)
		: ActorGenerator(scene, desc)
		, mActorName("")
		, mCenterPos(Vector2::ZERO)
		, mWidth(0)
		, mHeight(0)
		, mFishCount(0)
		, mDestCount(0)
		, mRefreshDestTime(0.0f)
		, mRefreshFishTime(0.0f)
		, mNavigName("")
		, mTimes(0.0f)
		, mPutFished(false)
		, mLocalDestCount(0)
		, mLocalDestTime(0)
		, DestPost(Vector3::ZERO)
		, mScreenHeight(0)
		, mScreenWidth(0)

	{
		ActorGeneratorDescRandomChase *genDesc = static_cast<ActorGeneratorDescRandomChase*>(desc);
		mActorName = genDesc->actorName;
		//mCenterPos = genDesc->centerPos;
		mWidth = genDesc->width;
		mHeight = genDesc->height;
		mFishCount = genDesc->fishCount;
		mDestCount = genDesc->destCount;
		mRefreshDestTime = genDesc->refreshDestTime;
		mRefreshFishTime = genDesc->refreshFishTime;
		mNavigName = genDesc->navigName;
		mCenterPos = vPos;

		// 计算鱼群中各鱼的开始位置(在矩形内使用随机放)
		//Vector2 v2LBPos = Vector2(mCenterPos.x-mWidth/2, mCenterPos.y-mHeight/2);// 左下
		//Vector2 v2RBPos = Vector2(mCenterPos.x+mWidth/2, mCenterPos.y-mHeight/2);// 右下
		//Vector2 v2LUPos = Vector2(mCenterPos.x-mWidth/2, mCenterPos.y+mHeight/2);// 左上
		//Vector2 v2RUPos = Vector2(mCenterPos.x+mWidth/2, mCenterPos.y+mHeight/2);// 右上

		mScreenWidth = gEnv->mSystem->getMainViewport()->getActualWidth();
		mScreenHeight = gEnv->mSystem->getMainViewport()->getActualHeight();
		srand((unsigned)time(0));// 以时间随机
		for (int i= 0; i<mFishCount; ++i)
		{
			Vector3 oriPos = Vector3::ZERO;
			oriPos.z = (rand()%static_cast<int>((mCenterPos.x+(mWidth/2)) - mCenterPos.x))+mCenterPos.x;
			oriPos.y =(rand()%static_cast<int>((mCenterPos.y+(mHeight/2)) - mCenterPos.y))+mCenterPos.y;
			mVecPos.push_back(oriPos);
		}
	}

	ActorGeneratorRandomChase::~ActorGeneratorRandomChase()
	{

	}

	void ActorGeneratorRandomChase::update( Real timeLapse )
	{
		mTimes += timeLapse;
		mLocalDestTime += timeLapse;
		if (mTimes< mRefreshFishTime && mLocalDestCount< mDestCount)
		{
			if (!mPutFished)
			{
				// 创建导航
				VecPos::iterator iter = mVecPos.begin();
				VecPos::iterator iterEnd = mVecPos.end();
				for (; iter!= iterEnd; ++iter)
				{
					ISceneNode2D* fishNode = mScene->getRootSceneNode()->createChild();
					Actor* actor = mScene->createActor(mActorName, fishNode);
					NormalActorFish* actorFish = static_cast<NormalActorFish*>(actor);
					actorFish->setLifeTime(0);

					Ogre::NameValuePairList param;
					param["pos"] = StringConverter::toString(*iter);
					param["destTime"] = StringConverter::toString(mRefreshDestTime);
					param["GeneratorChasePtr"] = StringConverter::toString((size_t)this);
					param["defaultSpeed"] = StringConverter::toString(actorFish->getDefaultSpeed());

					fishNode->createNavigation(mNavigName, param);
				}
				// 开始计算随机目标点
				DestPost.z = rand()%mScreenWidth;
				DestPost.y = rand()%mScreenHeight;
				if (DestPost.z> 1366|| DestPost.y> 700)
				{
					int xx = 0;
				}

				mLocalDestCount++;
				mLocalDestTime = 0.0f;

				// 放鱼频率
				mPutFished = true;
			}
			//if (mPutFished && mLocalDestCount < mDestCount && mRefreshDestTime< mLocalDestTime)
			//{
			//	// 开始计算随机目标点
			//	DestPost.z = rand()%mScreenWidth;
			//	DestPost.y = rand()%mScreenHeight;
			//	if (DestPost.z> 1366|| DestPost.y> 700)
			//	{
			//		int xx = 0;
			//	}

			//	mLocalDestCount++;
			//	mLocalDestTime = 0.0f;
			//}
			
		}
		else
		{
			mPutFished = false;
			mLocalDestCount = 0;
			mTimes = 0;
		}
	}

	Vector3	ActorGeneratorRandomChase::getDestPos()
	{
		return DestPost;
	}

	int		ActorGeneratorRandomChase::getRefreshFishCount()
	{
		return mDestCount;
	}

	void	ActorGeneratorRandomChase::updateDestPos()
	{
		DestPost.z = rand()%mScreenWidth;
		DestPost.y = rand()%mScreenHeight;
	}

	const String ActorGeneratorFactoryRandomChase::TypeName = "RamdomChase";

	ActorGeneratorFactoryRandomChase::ActorGeneratorFactoryRandomChase()
	{

	}

	ActorGeneratorFactoryRandomChase::~ActorGeneratorFactoryRandomChase()
	{

	}

	const String&	ActorGeneratorFactoryRandomChase::type() const
	{
		return TypeName;
	}

	ActorGenerator*	ActorGeneratorFactoryRandomChase::createInstance( ActorGeneratorDesc* desc, IScene* scene, Vector2 vPos )
	{
		ActorGeneratorRandomChase* actorGen = new ActorGeneratorRandomChase( scene, desc, vPos ); 

		return actorGen;
	}

	ActorGeneratorDesc*		ActorGeneratorFactoryRandomChase::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		ActorGeneratorDescRandomChase* desc = new ActorGeneratorDescRandomChase; 

		xml_attribute<>* nodeAttr = 0;

		_loadBaseDesc( desc, xmlNode, filename );

		// actorName
		nodeAttr = xmlNode->first_attribute("actorName");
		if (!nodeAttr)
		{
			EXCEPTEX( "param:actorName config file is empty! file name: " << filename );
		}
		desc->actorName = nodeAttr->value();
		//-- count

		// centerPos
		/*nodeAttr = xmlNode->first_attribute("cetnerPos");
		if (!nodeAttr)
		{
			EXCEPTEX( "param:cetnerPos config file is empty! file name: " << filename );
		}
		desc->centerPos = StringConverter::parseVector2(nodeAttr->value());*/

		// width
		nodeAttr = xmlNode->first_attribute("width");
		if (!nodeAttr)
		{
			EXCEPTEX( "param:width config file is empty! file name: " << filename );
		}
		desc->width = StringConverter::parseReal(nodeAttr->value());

		// height
		nodeAttr = xmlNode->first_attribute("height");
		if (!nodeAttr)
		{
			EXCEPTEX( "param:height config file is empty! file name: " << filename );
		}
		desc->height = StringConverter::parseReal(nodeAttr->value());

		// fishCount
		nodeAttr = xmlNode->first_attribute("fishCount");
		if (!nodeAttr)
		{
			EXCEPTEX( "param:fishCount config file is empty! file name: " << filename );
		}
		desc->fishCount = StringConverter::parseInt(nodeAttr->value());

		// destCount
		nodeAttr = xmlNode->first_attribute("destCount");
		if (!nodeAttr)
		{
			EXCEPTEX( "param:destCount config file is empty! file name: " << filename );
		}
		desc->destCount = StringConverter::parseInt(nodeAttr->value());

		// refreshDestTime
		nodeAttr = xmlNode->first_attribute("refreshDestTime");
		if (!nodeAttr)
		{
			EXCEPTEX( "param:refreshDestTime config file is empty! file name: " << filename );
		}
		desc->refreshDestTime = StringConverter::parseReal(nodeAttr->value());

		// refreshFishTime
		nodeAttr = xmlNode->first_attribute("refreshFishTime");
		if (!nodeAttr)
		{
			EXCEPTEX( "param:refreshFishTime config file is empty! file name: " << filename );
		}
		desc->refreshFishTime = StringConverter::parseReal(nodeAttr->value());

		// navigName
		nodeAttr = xmlNode->first_attribute("navigName");
		if (!nodeAttr)
		{
			EXCEPTEX( "param:navigName config file is empty! file name: " << filename );
		}
		desc->navigName = nodeAttr->value();
		
		return desc;
	}
}