#ifndef ACTORFISH_H
#define ACTORFISH_H
#include "Actor.h"

namespace Ogre
{
	class ActorFish: public Actor
	{
	public:
		ActorFish( ActorDesc* desc, ISceneNode2D* node, IScene* scene, const String& name = "" );
		virtual ~ActorFish();
		virtual	void			initailze();
		virtual	void			updateLogic( Real timeLapse );
		virtual const String&	type() const;
		virtual void			setProperty( const String& name, const Any& val );
	public:
		DYNAMIC_DECLARE( ActorFish );
	};

	class ActorFactoryFish : public ActorFactory
	{
	public:
		ActorFactoryFish();
		virtual ~ActorFactoryFish();

		virtual const String&	type() const;

		virtual Actor*			createInstance( ActorDesc* actorDesc, ISceneNode2D* node, IScene* scene );

		virtual  ActorDesc*		load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const String		TypeName;
	};
}
#endif