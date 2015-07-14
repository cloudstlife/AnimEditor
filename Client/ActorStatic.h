#ifndef ACTORSTATIC_H
#define ACTORSTATIC_H
#include "Actor.h"

namespace Ogre
{
	class ActorStatic : public Actor
	{
	public:
		ActorStatic( ActorDesc* desc, ISceneNode2D* node, IScene* scene, const String& name = "" );
		virtual ~ActorStatic();

		virtual	void			initailze();
		virtual	void			updateLogic( Real timeLapse );
		virtual const String&	type() const;
		virtual void			setProperty( const String& name, const Any& val );

	public:
		DYNAMIC_DECLARE( ActorStatic );

	private:
		int		testProperty;
	};

	class ActorFactoryStatic : public ActorFactory
	{
	public:
		ActorFactoryStatic();
		virtual ~ActorFactoryStatic();

		virtual const String&	type() const;

		virtual Actor*			createInstance( ActorDesc* actorDesc, ISceneNode2D* node, IScene* scene, const String& name = "" );

		virtual  ActorDesc*		load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const String		TypeName;
	};
}


#endif