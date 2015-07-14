#include "SystemPrerequisites.h"
#include "Navigation2DParallel.h"
#include "INavigation2DDesc.h"
#include "ISceneNode2D.h"

namespace Ogre
{
	struct Navigation2DDescParallel : public Navigation2DDesc
	{
		//Vector3			 originPos;
		Real			 time;
		VecNavigationPos vecNavigationPos;
	};

	Navigation2DParallel::Navigation2DParallel( ISceneNode2D* sceneNode, Navigation2DDesc* desc,NameValuePairList& param)
		: Navigation2D( sceneNode, desc)
		, mTimes(0.0f)
		, mLastPos(Vector3::ZERO)
		, mProceedTime(0.0f)
		, mTotalTime(0.0f)
		, mDividePoint(0.0f)
		, mFirstAffect(0.0f)
		, mSecondAffect(0.0f)
		, mAffectTimes(0.0f)
		, mPos(Vector2::ZERO)
		, mOffsetPos(Vector2::ZERO)
		, mDefaultSpeed(0.0f)
	{
		Navigation2DDescParallel* navigDesc = static_cast< Navigation2DDescParallel* >( desc );
		mVecNavigPos = navigDesc->vecNavigationPos;
		mProceedTime = navigDesc->time;
		mTotalTime = StringConverter::parseReal( param["totalTime"] );
		mDividePoint = StringConverter::parseReal( param["dividePoint"] );
		mFirstAffect = StringConverter::parseReal( param["firstAffect"] );
		mSecondAffect = StringConverter::parseReal( param["secondAffect"] );
		mOffsetPos = StringConverter::parseVector2( param["offset"] );
		mPos = StringConverter::parseVector2( param["pos"] );
		mDefaultSpeed = StringConverter::parseReal( param["defaultSpeed"] );

		pSSpline = new Ogre::SimpleSpline();

		// �����ĵ����õ�������
		VecNavigationPos::iterator iterNavigPos = mVecNavigPos.begin();
		VecNavigationPos::iterator iterNavigPosEnd = mVecNavigPos.end();
		for (;iterNavigPos!= iterNavigPosEnd; ++iterNavigPos)
		{
			pSSpline->addPoint(*iterNavigPos);
		}
		// ����λ���뷽��
		sceneNode->setPosition(mPos);
		Vector3 retPos = pSSpline->interpolate( 0 );
		Real angle = _calcDegree( mLastPos, retPos );
		mSceneNode->setRotateX( angle );
		mLastPos = retPos;
	}

	Navigation2DParallel::~Navigation2DParallel()
	{
		pSSpline = NULL;
	}

	void	Navigation2DParallel::update( Real timeLapse )
	{
		if ( mSceneNode == NULL || mStop )
		{
			return ;
		}

		// Ӱ����ȡֵ
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
			Vector3 tmpOffsetPos = Vector3(0, mOffsetPos.y, mOffsetPos.x);
			retPos += tmpPos;
			retPos += tmpOffsetPos;
			if (mLastPos != retPos)
			{
				// ����ͬһ��ʱ�����������ת����
				Real angle = _calcDegree( mLastPos, retPos );
				mSceneNode->setPosition( retPos );
				mSceneNode->setRotateX( angle );
			}
			mLastPos = retPos;
			if (affectTimes)
			{
				timeLapse = timeLapse * affectTimes;
			}
			mTimes += timeLapse;
		}
		else 
		{
			// ����ǰ����ǰ��
			Vector3 v3Dir = mLastPos;
			Vector2 prePos = mPos;
			prePos = prePos + mOffsetPos;
			v3Dir.y = v3Dir.y - prePos.y;
			v3Dir.z = v3Dir.z - prePos.x;
			Vector2 tran = Vector2::ZERO;
			// ��λ��
			tran.x = v3Dir.z/(sqrt(v3Dir.z*v3Dir.z+v3Dir.y*v3Dir.y));
			tran.y = v3Dir.y/(sqrt(v3Dir.z*v3Dir.z+v3Dir.y*v3Dir.y));
			tran = tran * (timeLapse/1.0f*mDefaultSpeed);
			mSceneNode->translate(tran);
		}
	}

	void	Navigation2DParallel::setPos( Real time )
	{
		update( time );
	}

	const String&	Navigation2DParallel::getType()
	{
		return Navigation2DFactoryParallel::TypeName;
	}

	Real	Navigation2DParallel::getSpeed()
	{
		return mSpeed;
	}

	void	Navigation2DParallel::setSpeed( Real val )
	{
		mSpeed = val;
	}

	Real Navigation2DParallel::_calcDegree( const Vector3& pos1, const Vector3& pos2 )
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

	void Navigation2DParallel::stop()
	{
		mStop = true;
	}

	//--
	const String Navigation2DFactoryParallel::TypeName = "Parallel";

	Navigation2DFactoryParallel::Navigation2DFactoryParallel()
	{

	}

	Navigation2DFactoryParallel::~Navigation2DFactoryParallel()
	{

	}

	const String&	Navigation2DFactoryParallel::type() const
	{
		return TypeName;
	}

	Navigation2D*	Navigation2DFactoryParallel::createInstance( Navigation2DDesc* desc, ISceneNode2D* node, NameValuePairList& param)
	{
		Navigation2DParallel* navigation = new Navigation2DParallel( node, desc, param ); 

		return navigation;
	}

	Navigation2DDesc*		Navigation2DFactoryParallel::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		Navigation2DDescParallel* desc = new Navigation2DDescParallel; 

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
			// ��һ��
			navigPosNode = navigPosNode->next_sibling( "navig" );
			desc->vecNavigationPos.push_back(vPos);
		}
		return desc;
	}
}