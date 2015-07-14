#include "SystemPrerequisites.h"
#include "Navigation2DRandomChase.h"
#include "ActorGeneratorRandomChase.h"
#include "INavigation2DDesc.h"
#include "ISceneNode2D.h"

namespace Ogre
{
	struct Navigation2DDescRamdomChase: public Navigation2DDesc
	{

	};

	Navigation2DRandomChase::Navigation2DRandomChase(ISceneNode2D* sceneNode, Navigation2DDesc* desc, NameValuePairList& param)
		: Navigation2D(sceneNode, desc)
		, pSSpline(NULL)
		, mLastPos(Vector3::ZERO)
		, mTimes(0.0f)
		, mDestTimes(0.0f)
		, mDefaultSpeed(0.0f)
		, mRandomChase(NULL)
		, mNextPos(Vector3::ZERO)
		, mBeginPos(Vector3::ZERO)
		, mRefreshFishCount(0)
		, mDir(Vector3::ZERO)
		, mPrePos(Vector3::ZERO)
		, mToEnd(false)
	{
		mDestTimes = StringConverter::parseReal(param["destTime"]);
		mBeginPos = StringConverter::parseVector3(param["pos"]);
		mDefaultSpeed = StringConverter::parseReal(param["defaultSpeed"]);
		void* data = (void*)(StringConverter::parseLong(param["GeneratorChasePtr"]));
		mRandomChase = static_cast<ActorGeneratorRandomChase*>
			((void*)(StringConverter::parseLong(param["GeneratorChasePtr"])));
		//pSSpline = new Ogre::SimpleSpline;
		//pSSpline->addPoint(mBeginPos);
		mLastPos = mBeginPos;
	}

	Navigation2DRandomChase::~Navigation2DRandomChase()
	{

	}

	void	Navigation2DRandomChase::setPos( Real time )
	{
		update( time );
	}

	const String&	Navigation2DRandomChase::getType()
	{
		return Navigation2DFactoryRandomChase::TypeName;
	}

	void	Navigation2DRandomChase::update( Real timeLapse )
	{
		if (mStop)
		{
			return ;
		}

		mTimes += timeLapse;
		if (mTimes<= mDestTimes && !mToEnd)
		{
			// 检测目标点
			Vector3 pos = mRandomChase->getDestPos();
			if (pos != mBeginPos)
			{
				mSceneNode->setPosition(mLastPos);
				// 得到方向
				mDir = pos - mLastPos;
				Real angle = _calcDegree( mLastPos, pos );
				mSceneNode->setRotateX( angle );

				mBeginPos = mRandomChase->getDestPos();
				mRefreshFishCount++;
			}

			Vector3 v3Pos = mSceneNode->getPosition();
			Real rLength = sqrt((v3Pos.z-pos.z)*(v3Pos.z-pos.z) + (v3Pos.y-pos.y)*(v3Pos.y-pos.y));
			if (rLength<= 1)
			{
				// 当任一条到达目标点后，马上修正坐标
				mRandomChase->updateDestPos();
				mLastPos = v3Pos;
				return;
			}
			Vector2 tran = Vector2::ZERO;
			// 单位化
			tran.x = mDir.z/(sqrt(mDir.z*mDir.z+mDir.y*mDir.y));
			tran.y = mDir.y/(sqrt(mDir.z*mDir.z+mDir.y*mDir.y));
			tran = tran * (timeLapse/1.0f*mDefaultSpeed);
			mSceneNode->translate(tran);
			mPrePos = mLastPos;
			mLastPos = mSceneNode->getPosition();
		}
		else if(mTimes> mDestTimes)
		{
			mTimes = 0;
		}

		if (mRefreshFishCount> mRandomChase->getRefreshFishCount())
		{
			// 朝当前方向前进
			Vector3 v3Dir = mPrePos;
			v3Dir = mLastPos - v3Dir;
			Vector2 tran = Vector2::ZERO;
			// 单位化
			tran.x = v3Dir.z/(sqrt(v3Dir.z*v3Dir.z+v3Dir.y*v3Dir.y));
			tran.y = v3Dir.y/(sqrt(v3Dir.z*v3Dir.z+v3Dir.y*v3Dir.y));
			tran = tran * (timeLapse/1.0f*mDefaultSpeed);
			mSceneNode->translate(tran);
			mToEnd = true;
		}
	}

	Real	Navigation2DRandomChase::getSpeed()
	{
		return mSpeed;
	}

	void	Navigation2DRandomChase::setSpeed(Real val)
	{
		mSpeed = val;
	}


	Real	Navigation2DRandomChase::_calcDegree( const Vector3& pos1, const Vector3& pos2 )
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

	void	Navigation2DRandomChase::stop()
	{
		mStop = true;
	}

	const String Navigation2DFactoryRandomChase::TypeName = "RamdomChase";

	Navigation2DFactoryRandomChase::Navigation2DFactoryRandomChase()
	{

	}

	Navigation2DFactoryRandomChase::~Navigation2DFactoryRandomChase()
	{

	}

	const String&	Navigation2DFactoryRandomChase::type() const
	{
		return TypeName;
	}

	Navigation2D*	Navigation2DFactoryRandomChase::createInstance( Navigation2DDesc* desc, ISceneNode2D* node, NameValuePairList& param)
	{
		Navigation2DRandomChase* navigation = new Navigation2DRandomChase( node, desc, param ); 

		return navigation;
	}

	Navigation2DDesc*		Navigation2DFactoryRandomChase::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		Navigation2DDescRamdomChase* desc = new Navigation2DDescRamdomChase; 

		xml_attribute<>* nodeAttr = 0;

		_loadBaseDesc( desc, xmlNode, filename );

		//xml_node<>* xmlPropertyBody = xmlNode->first_node("property");
		//if (!xmlPropertyBody)
		//{
		//	EXCEPTEX( "param:property in config file is empty! file name: " << filename );
		//}

		//nodeAttr = xmlPropertyBody->first_attribute("time");
		//if (!nodeAttr)
		//{
		//	EXCEPTEX( "param:time in config file is empty! file name: " << filename );
		//}
		//desc->time = StringConverter::parseReal(nodeAttr->value());


		//xml_node<>* navigPosNode = xmlPropertyBody->first_node( "navig" );
		//while ( navigPosNode )
		//{
		//	Vector3 vPos;
		//	nodeAttr = navigPosNode->first_attribute("pos");
		//	vPos = StringConverter::parseVector3(nodeAttr->value());
		//	// 下一个
		//	navigPosNode = navigPosNode->next_sibling( "navig" );
		//	desc->vecNavigationPos.push_back(vPos);
		//}
		return desc;
	}
}