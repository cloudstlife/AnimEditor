#ifndef ACTORBOUNDARYSCREEN_H
#define ACTORBOUNDARYSCREEN_H
#include "Actor.h"

namespace Ogre
{
	struct ISprite2D;
	struct ActorDescBoundary;

	class ActorBoundaryScreen: public Actor
	{
	public:
		ActorBoundaryScreen(ActorDesc* desc, ISceneNode2D* node, IScene* scene, const String& name = "");
		virtual ~ActorBoundaryScreen();
		virtual	void			initailze();
		virtual	void			updateLogic( Real timeLapse );
		virtual const String&	type() const;
		virtual void			setProperty( const String& name, const Any& val );
		void					injectWinMsg( uint uMsg, int wParam, int lParam );

	public:
		DYNAMIC_DECLARE( ActorBoundaryScreen );

	private:
		Action*				mBoundaryScreen;
		ISprite2D*			mBoundaryScreenSprite2D;
		Real				mTimes;
		ActorDescBoundary*	mDesc;
		ManualObject*		mDrawLine;
	};

	class ActorFactoryBoundaryScreen : public ActorFactory
	{
	public:
		ActorFactoryBoundaryScreen();
		virtual ~ActorFactoryBoundaryScreen();
		virtual const String&	type() const;
		virtual Actor*			createInstance( ActorDesc* actorDesc, ISceneNode2D* node, IScene* scene, const String& name = "" );
		virtual  ActorDesc*		load( rapidxml::xml_node<>* xmlNode, const String& filename );
		static const String		TypeName;
	};
}
#endif