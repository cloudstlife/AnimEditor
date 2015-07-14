#ifndef NAVIATION2DSIMPLEDIR_H
#define NAVIATION2DSIMPLEDIR_H
#include "Navigation2D.h"

namespace Ogre
{
	class SceneNode2D;

	class Naviagtion2DSimpleDir: public Navigation2D
	{
	public:
		Naviagtion2DSimpleDir(ISceneNode2D* sceneNode, Navigation2DDesc* desc, NameValuePairList& param);
		~Naviagtion2DSimpleDir();

		virtual void			destroy() { delete this; }
		virtual	void			setPos( Real time );
		virtual const String&	getType();
		virtual void			stop();

		Real		getSpeed();
		void		setSpeed( Real val );
		void		update( Real timeLapse );

	private:
		Vector3			mDir;
		Vector3			mDirOrignal;
		Real			mRotate;
		Real			mProceedTime;
		Real			mTimes;
		Real			mAffectTimes;
		Real			mTotalTime;
		Real			mDividePoint;
		Real			mFirstAffect;
		Real			mSecondAffect;
	};

	class Navigation2DFactorySimpleDir : public Navigation2DFactory
	{
	public:
		Navigation2DFactorySimpleDir();
		virtual ~Navigation2DFactorySimpleDir();

		virtual const String&			type() const;

		virtual Navigation2D*			createInstance( Navigation2DDesc* desc, ISceneNode2D* node, NameValuePairList& param);

		virtual  Navigation2DDesc*		load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const String		TypeName;
	};
}
#endif