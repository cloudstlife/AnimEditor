#ifndef ACTORBACKGROUND_H
#define ACTORBACKGROUND_H
#include "Actor.h"

namespace Ogre
{
	struct ISprite2D;
	
	struct ActionDescBackground;
	
	struct BackMapNode;

	class ActorBackground: public Actor
	{
	public:
		ActorBackground(ActorDesc* desc, ISceneNode2D* node, IScene* scene, const String& name = "");
		virtual ~ActorBackground();
		virtual	void			initailze();
		virtual	void			updateLogic( Real timeLapse );
		virtual const String&	type() const;
		virtual void			setProperty( const String& name, const Any& val );
		void					injectWinMsg( uint uMsg, int wParam, int lParam );
		String					getNextBackground();
		void					setBackgroundImage();

	public:
		DYNAMIC_DECLARE( ActorBackground );
	private:
		BackMapNode			_getNextBackMapInfo();
	private:
		Action*			mBackMapScreen;
		ISprite2D*		mBackMapSprite2D;
		int				mCurBackMapLv;
		Real			mCurBackMapLvTimes;
		Real			mTimes;
		String			mNextMap;
		int				mLayer;
		String			mGeneratorGroupId;
		int				mCurBackMapIter;


		ActionDescBackground*	mDesc;
	};

	class ActorFactoryBackground : public ActorFactory
	{
	public:
		ActorFactoryBackground();
		virtual ~ActorFactoryBackground();
		virtual const String&	type() const;
		virtual Actor*			createInstance( ActorDesc* actorDesc, ISceneNode2D* node, IScene* scene, const String& name = "" );
		virtual  ActorDesc*		load( rapidxml::xml_node<>* xmlNode, const String& filename );
		static const String		TypeName;
	};
}
#endif