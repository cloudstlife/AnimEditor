#ifndef NAVIGATION2DPARALLEL_H
#define NAVIGATION2DPARALLEL_H
#include "Navigation2D.h"
#include "ogre_src_v1-8-1/OgreSimpleSpline.h"

namespace Ogre
{
	class SceneNode2D;
	typedef std::vector<Vector3>		VecNavigationPos;
	class Navigation2DParallel: public Navigation2D
	{
	public:
		Navigation2DParallel( ISceneNode2D* sceneNode, Navigation2DDesc* desc, NameValuePairList& param);
		~Navigation2DParallel();

		virtual void			destroy() { delete this; }
		virtual	void			setPos( Real time );
		virtual const String&	getType();
		virtual void			stop();

		Real		getSpeed();
		void		setSpeed( Real val );
		void		update( Real timeLapse );
	private:
		Real _calcDegree( const Vector3& pos1, const Vector3& pos2 );

	private:
		VecNavigationPos	mVecNavigPos;
		Ogre::SimpleSpline*	pSSpline;
		Vector3				mLastPos;
		Real				mProceedTime;
		Real				mTimes;
		Real				mAffectTimes;
		Real				mTotalTime;
		Real				mDividePoint;
		Real				mFirstAffect;
		Real				mSecondAffect;
		Real				mDefaultSpeed;
		Vector2				mPos;
		Vector2				mOffsetPos;
	};

	class Navigation2DFactoryParallel : public Navigation2DFactory
	{
	public:
		Navigation2DFactoryParallel();
		virtual ~Navigation2DFactoryParallel();

		virtual const String&			type() const;

		virtual Navigation2D*			createInstance( Navigation2DDesc* desc, ISceneNode2D* node, NameValuePairList& param);

		virtual  Navigation2DDesc*		load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const String		TypeName;
	};
}
#endif