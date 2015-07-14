#ifndef NORMALACTORFISH_H
#define NORMALACTORFISH_H
//#include "Actor.h"
#include "ActorFish.h"

namespace Ogre
{
	class NormalActorFish : public ActorFish
	{
	public:
		NormalActorFish( ActorDesc* desc, ISceneNode2D* node, IScene* scene );
		virtual ~NormalActorFish();

		virtual	void			initailze();
		virtual	void			updateLogic( Real timeLapse );
		virtual const String&	type() const;
		virtual void			setProperty( const String& name, const Any& val );
		void					setActorPlayer(Actor* actor);
		Actor*					getActorPlayer();
	public:
		DYNAMIC_DECLARE( NormalActorFish );

		Real		getTotalTime();
		Real		getDividePoint();
		Real		getFirstAffect();
		Real		getSecondAffect();
		int			getOdds();
		int			getEnergy();
		Real		getDefaultSpeed();

	private:
		Actor*		mPlayer;
		Real		mTotalTime;
		Real		mDividePoint;
		Real		mFirstAffect;
		Real		mSecondAffect;
		Real		mDefaultSpeed;
		int			mOdds;
		int			mEnergy;
	};

	class ActorFactoryNormalFish : public ActorFactory
	{
	public:
		ActorFactoryNormalFish();
		virtual ~ActorFactoryNormalFish();

		virtual const String&	type() const;

		virtual Actor*			createInstance( ActorDesc* actorDesc, ISceneNode2D* node, IScene* scene, const String& name = "" );

		virtual  ActorDesc*		load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const String		TypeName;
	};
}


#endif