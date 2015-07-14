#include "SystemPrerequisites.h"
#include "Navigation2DDefault.h"
#include "INavigation2DDesc.h"
#include "ISceneNode2D.h"

namespace Ogre
{
	struct Navigation2DDescDefault : public Navigation2DDesc
	{
		Vector3			 originPos;
		Real			 time;
		VecNavigationPos vecNavigationPos;
	};

	Navigation2DDefault::Navigation2DDefault( ISceneNode2D* sceneNode, Navigation2DDesc* desc, NameValuePairList& param)
		: Navigation2D( sceneNode, desc)
		, mTimes(0.0f)
		, mLastPos(Vector3::ZERO)
		, mDir(Vector3::ZERO)
		, mProceedTime(0.0f)
		, mTotalTime(0.0f)
		, mDividePoint(0.0f)
		, mFirstAffect(0.0f)
		, mSecondAffect(0.0f)
		, mAffectTimes(0.0f)
		, mPos(Vector2::ZERO)
		, mDefaultSpeed(0.0f)
	{
		Navigation2DDescDefault* navigDesc = static_cast< Navigation2DDescDefault* >( desc );
		mVecNavigPos = navigDesc->vecNavigationPos;
		mProceedTime = navigDesc->time;
		mTotalTime = StringConverter::parseReal( param["totalTime"] );
		mDividePoint = StringConverter::parseReal( param["dividePoint"] );
		mFirstAffect = StringConverter::parseReal( param["firstAffect"] );
		mSecondAffect = StringConverter::parseReal( param["secondAffect"] );
		mPos = StringConverter::parseVector2( param["pos"] );
		mDefaultSpeed = StringConverter::parseReal( param["defaultSpeed"] );

		pSSpline = new Ogre::SimpleSpline();

		// 根据文档配置导航坐标
		//mPos = vPos;
		VecNavigationPos::iterator iterNavigPos = mVecNavigPos.begin();
		VecNavigationPos::iterator iterNavigPosEnd = mVecNavigPos.end();
		for (;iterNavigPos!= iterNavigPosEnd; ++iterNavigPos)
		{
			pSSpline->addPoint(*iterNavigPos);
		}
		// 计算位置与方向
		mSceneNode->setPosition(mPos);
		Vector3 retPos = pSSpline->interpolate( 0 );
		Real angle = _calcDegree( mLastPos, retPos );
		mSceneNode->setRotateX( angle );
		mLastPos = retPos;
	}

	Navigation2DDefault::~Navigation2DDefault()
	{
		pSSpline = NULL;
	}

	void	Navigation2DDefault::update( Real timeLapse )
	{
		if ( mSceneNode == NULL || mStop)
		{
			return ;
		}

		// 影响器取值
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

		if ( mTimes <= mProceedTime )
		{
			Real tRace = mTimes/mProceedTime;
			Vector3 retPos = pSSpline->interpolate( tRace );
			Vector3 tmpPos = Vector3(0, mPos.y, mPos.x);
			retPos += tmpPos;
			if (mLastPos != retPos)
			{
				// 不在同一点时处理，否则会旋转问题
				Real angle = _calcDegree( mLastPos, retPos );
				mSceneNode->setPosition( retPos );
				mSceneNode->setRotateX( angle );
			}
			mDir = mLastPos;
			mLastPos = retPos;
			
			if (affectTimes)
			{
				timeLapse = timeLapse * affectTimes;
			}
			mTimes += timeLapse;
		}
		else 
		{
			// 朝当前方向前进
			Vector3 v3Dir = mDir;
			v3Dir = mLastPos - v3Dir;
			Vector2 tran = Vector2::ZERO;
			// 单位化
			tran.x = v3Dir.z/(sqrt(v3Dir.z*v3Dir.z+v3Dir.y*v3Dir.y));
			tran.y = v3Dir.y/(sqrt(v3Dir.z*v3Dir.z+v3Dir.y*v3Dir.y));
			tran = tran * (timeLapse/1.0f*mDefaultSpeed);
			mSceneNode->translate(tran);
		}
	}

	void	Navigation2DDefault::setPos( Real time )
	{
		update( time );
	}

	const String&	Navigation2DDefault::getType()
	{
		return Navigation2DFactoryDefault::TypeName;
	}

	Real	Navigation2DDefault::getSpeed()
	{
		return mSpeed;
	}

	void	Navigation2DDefault::setSpeed( Real val )
	{
		mSpeed = val;
	}
	
	Real Navigation2DDefault::_calcDegree( const Vector3& pos1, const Vector3& pos2 )
	{
		Vector2 dir = Vector2( pos2.z, pos2.y ) - Vector2( pos1.z, pos1.y );
		Real angle1 = atan2( dir.y, dir.x );   
		Radian  radi1( angle1 );
		Degree deg1( radi1 );
		Real res = deg1.valueDegrees();
		if ( res < 0 )
		{
			res = -res;
		}
		else if ( res > 0 )
		{
			res = 360.f - res;
		}
		return res;
	}

	void Navigation2DDefault::stop()
	{
		mStop = true;
	}

	//--
	const String Navigation2DFactoryDefault::TypeName = "Default";

	Navigation2DFactoryDefault::Navigation2DFactoryDefault()
	{

	}

	Navigation2DFactoryDefault::~Navigation2DFactoryDefault()
	{

	}

	const String&	Navigation2DFactoryDefault::type() const
	{
		return TypeName;
	}

	Navigation2D*	Navigation2DFactoryDefault::createInstance( Navigation2DDesc* desc, ISceneNode2D* node, NameValuePairList& param)
	{
		Navigation2DDefault* navigation = new Navigation2DDefault( node, desc, param ); 

		return navigation;
	}

	Navigation2DDesc*		Navigation2DFactoryDefault::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		Navigation2DDescDefault* desc = new Navigation2DDescDefault; 

		xml_attribute<>* nodeAttr = 0;

		_loadBaseDesc( desc, xmlNode, filename );

		xml_node<>* xmlPropertyBody = xmlNode->first_node("property");
		if (!xmlPropertyBody)
		{
			EXCEPTEX( "param:property in config file is empty! file name: " << filename );
		}

		nodeAttr = xmlPropertyBody->first_attribute("time");
		if (!nodeAttr)
		{
			EXCEPTEX( "param:time in config file is empty! file name: " << filename );
		}
		desc->time = StringConverter::parseReal(nodeAttr->value());

		
		xml_node<>* navigPosNode = xmlPropertyBody->first_node( "navig" );
		while ( navigPosNode )
		{
			Vector3 vPos;
			nodeAttr = navigPosNode->first_attribute("pos");
			vPos = StringConverter::parseVector3(nodeAttr->value());
			// 下一个
			navigPosNode = navigPosNode->next_sibling( "navig" );
			desc->vecNavigationPos.push_back(vPos);
		}
		return desc;
	}
}