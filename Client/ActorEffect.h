#ifndef ACTOREFFECT_H
#define ACTOREFFECT_H
#include "Actor.h"

namespace Ogre
{
	struct ISprite2D;
	struct IAnimation2D;

	class ActorEffect : public Actor
	{
		typedef std::list< IAnimation2D* >		ListAnim;
		typedef std::list< ISprite2D* >			ListSprite;

	public:
		ActorEffect( ActorDesc* desc, ISceneNode2D* node, IScene* scene );
		virtual ~ActorEffect();

		virtual	void			initailze();
		virtual	void			updateLogic( Real timeLapse );
		virtual const String&	type() const;
		virtual void			setProperty( const String& name, const Any& val );
		
		bool					isLoop();

	private:
		void	_applyAlpha( Real alpha );
		void	_applyRot( Real rot );
		void	_applyScale( const Vector2& scale );
		void	_applyPosOff( const Vector2& posOff );
		void	_applyColorAdd( const Vector3& colorAdd );
		void	_applyColorMuti( const Vector3& colorMuti );

	public:
		DYNAMIC_DECLARE( ActorEffect );

	private:
		ListAnim				mAnims;
		ListSprite				mSprites;
		bool					mLoop;
	};

	class ActorFactoryEffect : public ActorFactory
	{
	public:
		ActorFactoryEffect();
		virtual ~ActorFactoryEffect();

		virtual const String&	type() const;

		virtual Actor*			createInstance( ActorDesc* actorDesc, ISceneNode2D* node, IScene* scene, const String& name = 0 );

		virtual  ActorDesc*		load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const String		TypeName;
	};
}


#endif