#ifndef NAVIAGTION2DROUNDDIFFUSE_H
#define NAVIAGTION2DROUNDDIFFUSE_H
#include "Navigation2D.h"

#define ANGLE 30

namespace Ogre
{
	class SceneNode2D;

	class Naviagtion2DRoundDiffuse: public Navigation2D
	{
	public:
		Naviagtion2DRoundDiffuse(ISceneNode2D* sceneNode, Navigation2DDesc* desc, NameValuePairList& param);
		~Naviagtion2DRoundDiffuse();

		virtual void			destroy() { delete this; }
		virtual	void			setPos( Real time );
		virtual const String&	getType();
		virtual void			stop();

		Real		getSpeed();
		void		setSpeed( Real val );
		void		update( Real timeLapse );
		Real		_calcDegree( const Vector3& pos1, const Vector3& pos2 );

	private:
		void		_setRoundVertex(Real rotate, int dir);

	private:
		Real			mRotate;
		Real			mProceedTime;
		Real			mTimes;
		Real			mDiffTuseLeftTime; // 到计散开时间累计
		Real			mAffectTimes;
		Real			mTotalTime;
		Real			mDividePoint;
		Real			mFirstAffect;
		Real			mSecondAffect;
		Real			mDiffuseTime;
		Vector3			mDir;
		Vector2			mCenterPos;
		Vector2			mPos;
		Real			mRadius;
		Vector3			mLastPos;
		int				mRotateDir;
		SimpleSpline*	pSSpline;

		std::vector<Vector2>	VectPos;
	};

	class Navigation2DFactoryRoundDiffuse : public Navigation2DFactory
	{
	public:
		Navigation2DFactoryRoundDiffuse();
		virtual ~Navigation2DFactoryRoundDiffuse();

		virtual const String&			type() const;

		virtual Navigation2D*			createInstance( Navigation2DDesc* desc, ISceneNode2D* node, NameValuePairList& param);

		virtual  Navigation2DDesc*		load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const String		TypeName;
	};
}
#endif