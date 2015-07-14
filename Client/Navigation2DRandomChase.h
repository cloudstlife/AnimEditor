#ifndef NAVIGATION2DRAMDOMCHASE_H
#define NAVIGATION2DRAMDOMCHASE_H
#include "Navigation2D.h"
#include "ogre_src_v1-8-1/OgreSimpleSpline.h"

namespace Ogre
{
	class ActorGeneratorRandomChase;
	class SceneNode2D;
	class Navigation2DRandomChase: public Navigation2D
	{
	public:
		Navigation2DRandomChase( ISceneNode2D* sceneNode, Navigation2DDesc* desc, NameValuePairList& param);
		~Navigation2DRandomChase();

		virtual void		destroy(){ delete this; }
		virtual void		setPos( Real time );
		virtual const		String& getType();
		virtual void		stop();
		Real				getSpeed();
		void				setSpeed( Real val );
		void				update( Real timeLapse );

	private:
		Real _calcDegree( const Vector3& pos1, const Vector3& pos2 );

	private:
		Ogre::SimpleSpline*		pSSpline;
		Vector3					mPrePos;
		Vector3					mLastPos;
		Real					mTimes;
		Real					mDestTimes;
		Real					mDefaultSpeed;
		ActorGeneratorRandomChase* mRandomChase;
		Vector3					mNextPos;
		Vector3					mBeginPos;
		Vector3					mDir;
		int						mRefreshFishCount;
		bool					mToEnd;
	};

	class Navigation2DFactoryRandomChase : public Navigation2DFactory
	{
	public:
		Navigation2DFactoryRandomChase();
		virtual ~Navigation2DFactoryRandomChase();

		virtual const String&			type() const;

		virtual Navigation2D*			createInstance( Navigation2DDesc* desc, ISceneNode2D* node, NameValuePairList& param);

		virtual  Navigation2DDesc*		load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const String		TypeName;
	};
}
#endif