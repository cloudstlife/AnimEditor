#include "SystemPrerequisites.h"
#include "Naviagtion2DRoundDiffuse.h"
#include "INavigation2DDesc.h"
#include "ISceneNode2D.h"
#include "ogre_src_v1-8-1/OgreMath.h"

namespace Ogre
{
	struct Naviagtion2DDescRoundDiffuse: public Navigation2DDesc
	{
		Naviagtion2DDescRoundDiffuse()
			: time(0.0f)
		{

		}
		Real			time;
	};

	Naviagtion2DRoundDiffuse::Naviagtion2DRoundDiffuse(ISceneNode2D* sceneNode,
		Navigation2DDesc* desc, NameValuePairList& param)
		: Navigation2D(sceneNode, desc)
		, mRotate(0.0f)
		, mProceedTime(0.0f)
		, mTimes(0.0f)
		, mAffectTimes(0.0f)
		, mTotalTime(0.0f)
		, mDividePoint(0.0f)
		, mFirstAffect(0.0f)
		, mSecondAffect(0.0f)
		, mCenterPos(Vector2::ZERO)
		, mRadius(0.0f)
		, mPos(Vector2::ZERO)
		, mRotateDir(0)
		, mDiffuseTime(0.0f)
		, mDiffTuseLeftTime(0.0f)
	{
		Naviagtion2DDescRoundDiffuse* navigDesc = static_cast<Naviagtion2DDescRoundDiffuse*>(desc);
		mProceedTime = navigDesc->time;
		mTotalTime = StringConverter::parseReal( param["totalTime"] );
		mDividePoint = StringConverter::parseReal( param["dividePoint"] );
		mFirstAffect = StringConverter::parseReal( param["firstAffect"] );
		mSecondAffect = StringConverter::parseReal( param["secondAffect"] );
		mPos = StringConverter::parseVector2( param["pos"] );
		mCenterPos = StringConverter::parseVector2( param["centerPos"] );
		mRadius =  StringConverter::parseReal( param["radius"] );
		mDiffuseTime = StringConverter::parseReal( param["diffuseTime"] );
		mRotate = StringConverter::parseReal( param["rotate"] );
		mRotateDir = StringConverter::parseReal( param["dir"] );

		pSSpline = new SimpleSpline();
		// 计算出12点的插值
		if (mRotateDir == 0)
		{
			// 顺时针
			_setRoundVertex(mRotate, mRotateDir);
			
		}
		else if (mRotateDir == 1)
		{
			// 逆时针
			_setRoundVertex(mRotate, mRotateDir);
		}
	}

	Naviagtion2DRoundDiffuse::~Naviagtion2DRoundDiffuse()
	{

	}

	void	Naviagtion2DRoundDiffuse::update( Real timeLapse )
	{
		if ( mSceneNode == NULL || mStop)
		{
			return ;
		}
		// 影响器取值
		Real affectTimes = 0.0f;
		mDiffTuseLeftTime += timeLapse;

		if (mDiffTuseLeftTime< mDiffuseTime)
		{
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
				mTimes = 0;
			}
		}
		else
		{
			// 散开朝各自方向前进
			Vector3 v3Dir = mDir;
			v3Dir = mLastPos - v3Dir;
			Vector2 tran = Vector2::ZERO;
			// 单位化
			tran.x = v3Dir.z/(sqrt(v3Dir.z*v3Dir.z+v3Dir.y*v3Dir.y));
			tran.y = v3Dir.y/(sqrt(v3Dir.z*v3Dir.z+v3Dir.y*v3Dir.y));

			mSceneNode->translate(tran);
		}
	}

	Real Naviagtion2DRoundDiffuse::_calcDegree( const Vector3& pos1, const Vector3& pos2 )
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

	void Naviagtion2DRoundDiffuse::_setRoundVertex(Real rotate, int dir)
	{	
		Vector2 v2Pos = Vector2::ZERO;
		for (int i = 0; i< 13; ++i)
		{
			v2Pos.x = mCenterPos.x + mRadius * Math::Cos(rotate * Math.PI/180);
			v2Pos.y = mCenterPos.y + mRadius * Math::Sin(rotate * Math.PI/180);
			VectPos.push_back(v2Pos);
			// 增加步长
			rotate += ANGLE;
			if (rotate>= 360)
			{
				rotate = rotate - 360;
			}
		}
		
		if (dir == 0)
		{
			std::vector<Vector2>::iterator iter = VectPos.begin();
			std::vector<Vector2>::iterator iterEnd = VectPos.end();
			for(; iter != iterEnd; ++iter)
			{
				Vector3 pos = Vector3::ZERO;
				pos.z = iter->x;
				pos.y = iter->y;
				pSSpline->addPoint(pos);
			}
		}
		else if (dir == 1)
		{
			std::vector<Vector2>::reverse_iterator rIter = VectPos.rbegin();
			std::vector<Vector2>::reverse_iterator rIterEnd = VectPos.rend();
			for(; rIter != rIterEnd; ++rIter)
			{
				Vector3 pos = Vector3::ZERO;
				pos.z = rIter->x;
				pos.y = rIter->y;
				pSSpline->addPoint(pos);
			}
		}
		
	}

	void	Naviagtion2DRoundDiffuse::setPos( Real time )
	{
		update(time);
	}

	const String&	Naviagtion2DRoundDiffuse::getType()
	{
		return Navigation2DFactoryRoundDiffuse::TypeName;
	}

	Real	Naviagtion2DRoundDiffuse::getSpeed()
	{
		return mSpeed;
	}

	void	Naviagtion2DRoundDiffuse::setSpeed( Real val )
	{
		mSpeed = val;
	}

	void	Naviagtion2DRoundDiffuse::stop()
	{
		mStop = true;
	}

	const String Navigation2DFactoryRoundDiffuse::TypeName = "RoundDiffuse";

	Navigation2DFactoryRoundDiffuse::Navigation2DFactoryRoundDiffuse()
	{

	}

	Navigation2DFactoryRoundDiffuse::~Navigation2DFactoryRoundDiffuse()
	{

	}

	const String&	Navigation2DFactoryRoundDiffuse::type() const
	{
		return TypeName;
	}

	Navigation2D*	Navigation2DFactoryRoundDiffuse::createInstance( Navigation2DDesc* desc, ISceneNode2D* node, NameValuePairList& param)
	{
		Naviagtion2DRoundDiffuse* navigation = new Naviagtion2DRoundDiffuse
			( node, desc, param ); 

		return navigation;
	}

	Navigation2DDesc*		Navigation2DFactoryRoundDiffuse::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		Naviagtion2DDescRoundDiffuse* desc = new Naviagtion2DDescRoundDiffuse; 

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