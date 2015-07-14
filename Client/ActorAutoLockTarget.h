#ifndef ACTORAUTOLOCKTARGET_H
#define ACTORAUTOLOCKTARGET_H

#include "Actor.h"

namespace Ogre
{
	class ActorAutoLockTarget: public Actor
	{
	public:
		ActorAutoLockTarget(ActorDesc* desc, ISceneNode2D* node, IScene* scene);
		virtual ~ActorAutoLockTarget();

		virtual void			initailze();
		virtual void			updateLogic( Real timeLapse );
		virtual const String&	type() const;
		void					setActorPlayer(Actor* actor);
		Actor*					getActorPlayer();

	public:
		DYNAMIC_DECLARE(ActorAutoLockTarget);

	private:
		Actor*			mPlayer;
	};

	class ActorFactoryAutoLockTarget : public ActorFactory
	{
	public:
		ActorFactoryAutoLockTarget();
		virtual ~ActorFactoryAutoLockTarget();
		virtual const String& type() const;
		virtual Actor* createInstance( ActorDesc* actorDesc, ISceneNode2D* node, IScene* scene, const String& name = "" );
		virtual ActorDesc* load( rapidxml::xml_node<>* xmlNode, const String& filename );
		static const String TypeName;
	};
}
#endif