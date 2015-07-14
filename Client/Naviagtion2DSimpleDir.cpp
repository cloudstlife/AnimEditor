#include "SystemPrerequisites.h"
#include "Naviagtion2DSimpleDir.h"
#include "INavigation2DDesc.h"
#include "ISceneNode2D.h"

namespace Ogre
{
	struct Naviagtion2DDescSimpleDir: public Navigation2DDesc
	{
		Real			time;
	};

	Naviagtion2DSimpleDir::Naviagtion2DSimpleDir(ISceneNode2D* sceneNode, Navigation2DDesc* desc, 
		NameValuePairList& param)
		: Navigation2D(sceneNode, desc)
		, mDir(Vector3::UNIT_Z)
		, mDirOrignal(Vector3::UNIT_Z)
		, mProceedTime(0.0f)
		, mTimes(0.0f)
		, mAffectTimes(0.0f)
		, mTotalTime(0.0f)
		, mDividePoint(0.0f)
		, mFirstAffect(0.0f)
		, mSecondAffect(0.0f)
	{
		Naviagtion2DDescSimpleDir* navigDesc = static_cast<Naviagtion2DDescSimpleDir*>(desc);
		mProceedTime = navigDesc->time;
		mTotalTime = StringConverter::parseReal( param["totalTime"] );
		mDividePoint = StringConverter::parseReal( param["dividePoint"] );
		mFirstAffect = StringConverter::parseReal( param["firstAffect"] );
		mSecondAffect = StringConverter::parseReal( param["secondAffect"] );
		mPos = StringConverter::parseVector2( param["pos"] );

		mSceneNode->setPosition(mPos);
		mSceneNode->setRotateX(StringConverter::parseReal( param["rotate"] ));
		const Quaternion& quat = mSceneNode->getDerivedOrientation();
		mDir = quat * mDirOrignal;
	}

	Naviagtion2DSimpleDir::~Naviagtion2DSimpleDir()
	{

	}

	void	Naviagtion2DSimpleDir::update( Real timeLapse )
	{
		if (mStop)
		{
			return ;
		}
		// Ó°ÏìÆ÷È¡Öµ
		Real affectTimes = 0.0f;
		if (mAffectTimes<= mTotalTime)
		{
			if (mAffectTimes<= mDividePoint)
			{
				affectTimes = mFirstAffect;
			}
			else
			{
				affectTimes = mSecondAffect;
			}
			mAffectTimes += timeLapse;
		}
		else
		{
			mAffectTimes = 0;
			affectTimes = mFirstAffect;
		}
		{
			if (mTimes>= mProceedTime)
			{
				mTimes = 0;
			}
			Real tRace = mTimes/mProceedTime;
			Vector2 dir = Vector2::ZERO;
			dir.x = mDir.z;
			dir.y = mDir.y;
			Vector2 step = dir * tRace;
			mSceneNode->translate(step);
			if (affectTimes)
			{
				timeLapse = timeLapse * affectTimes;
			}
			mTimes += timeLapse;
		}
	}

	void	Naviagtion2DSimpleDir::setPos(Real time)
	{
		update(time);
	}

	const String&	Naviagtion2DSimpleDir::getType()
	{
		return Navigation2DFactorySimpleDir::TypeName;
	}

	Real	Naviagtion2DSimpleDir::getSpeed()
	{
		return mSpeed;
	}

	void	Naviagtion2DSimpleDir::setSpeed( Real val )
	{
		mSpeed = val;
	}

	void	Naviagtion2DSimpleDir::stop()
	{
		mStop = true;
	}

	const String Navigation2DFactorySimpleDir::TypeName = "Dir";

	Navigation2DFactorySimpleDir::Navigation2DFactorySimpleDir()
	{

	}

	Navigation2DFactorySimpleDir::~Navigation2DFactorySimpleDir()
	{

	}

	const String&	Navigation2DFactorySimpleDir::type() const
	{
		return TypeName;
	}

	Navigation2D*	Navigation2DFactorySimpleDir::createInstance( Navigation2DDesc* desc, ISceneNode2D* node, NameValuePairList& param)
	{
		Naviagtion2DSimpleDir* navigation = new Naviagtion2DSimpleDir
			( node, desc, param ); 

		return navigation;
	}

	Navigation2DDesc*		Navigation2DFactorySimpleDir::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		Naviagtion2DDescSimpleDir* desc = new Naviagtion2DDescSimpleDir; 

		xml_attribute<>* nodeAttr = 0;

		_loadBaseDesc( desc, xmlNode, filename );

		nodeAttr = xmlNode->first_attribute("time");
		if (!nodeAttr)
		{
			EXCEPTEX( "param:time in config file is empty! file name: " << filename );
		}
		desc->time = StringConverter::parseReal(nodeAttr->value());

		return desc;
	}
}