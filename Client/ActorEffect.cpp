#include "SystemPrerequisites.h"
#include "ActorEffect.h"
#include "ISceneNode2D.h"
#include "ActionEffectUpdate.h"
#include "ISprite2D.h"
#include "IAnimation2D.h"
#include "ISprite2DManager.h"
#include "IAnimation2DManager.h"

namespace Ogre
{
	struct ActorDescEffect : public ActorDesc
	{
		ActorDescEffect()
			: loop( false )
		{

		}

		ListSpriteElem		sprites;
		ListAnimElem		anims;
		bool				loop;
	};

	//---
	DYNAMIC_IMPLEMENT( ActorEffect, GETRTTI( Actor ) )
	ActorEffect::ActorEffect( ActorDesc* desc, ISceneNode2D* node, IScene* scene )
		: Actor( desc, node, scene )
	{

		ActorDescEffect* actionDesc = static_cast< ActorDescEffect* >( desc );

		mLoop = actionDesc->loop;

		//	¶¯»­
		ListAnimElem::iterator iterAnim = actionDesc->anims.begin();
		ListAnimElem::iterator iterAnimEnd = actionDesc->anims.end();

		while ( iterAnim != iterAnimEnd )
		{
			AnimElement& animEle = (*iterAnim);

			IAnimation2D* anim = gEnv->mAnimationMgr->create( animEle.id );
			anim->setRenderQueue( animEle.layer );

			mAnims.push_back( anim );

			++iterAnim;
		}

		//	¾«Áé
		ListSpriteElem::iterator iterSprite = actionDesc->sprites.begin();
		ListSpriteElem::iterator iterSpriteEnd = actionDesc->sprites.end();

		while ( iterSprite != iterSpriteEnd )
		{
			SpriteElement& spriteEle = (*iterSprite);

			ISprite2D* sprite = gEnv->mSpriteMgr->create( spriteEle.id );
			sprite->setRenderQueue( spriteEle.layer );

			mSprites.push_back( sprite );

			++iterSprite;
		}
	}

	ActorEffect::~ActorEffect()
	{
		ListAnim::iterator iterAnim = mAnims.begin();
		ListAnim::iterator iterAnimEnd = mAnims.end();

		while ( iterAnim != iterAnimEnd )
		{
			IAnimation2D* anim = (*iterAnim);

			anim->destroy();

			++iterAnim;
		}
		mAnims.clear();

		ListSprite::iterator iterSprite = mSprites.begin();
		ListSprite::iterator iterSpriteEnd = mSprites.end();

		while ( iterSprite != iterSpriteEnd )
		{
			ISprite2D* sprite = (*iterSprite);

			sprite->destroy();

			++iterSprite;
		}
		mSprites.clear();
	}
	
	void	ActorEffect::initailze()
	{
		Actor::initailze();

		ListAnim::iterator iterAnim = mAnims.begin();
		ListAnim::iterator iterAnimEnd = mAnims.end();

		while ( iterAnim != iterAnimEnd )
		{
			IAnimation2D* anim = (*iterAnim);

			mSceneNode->attachObject( anim );

			++iterAnim;
		}

		ListSprite::iterator iterSprite = mSprites.begin();
		ListSprite::iterator iterSpriteEnd = mSprites.end();

		while ( iterSprite != iterSpriteEnd )
		{
			ISprite2D* sprite = (*iterSprite);

			mSceneNode->attachObject( sprite );

			++iterSprite;
		}
	}

	void	ActorEffect::updateLogic( Real timeLapse )
	{
		Actor::updateLogic( timeLapse );
	}

	const String& ActorEffect::type() const
	{
		return ActorFactoryEffect::TypeName;
	}

	void	ActorEffect::setProperty( const String& name, const Any& val )
	{
		Actor::setProperty( name, val );

		if ( name == "alpha" )
		{
			_applyAlpha( val.get<Real>() );
		}
		else if ( name == "rot" )
		{
			_applyRot( val.get<Real>() );
		}
		else if ( name == "scale" )
		{
			_applyScale( val.get<Vector2>() );
		}
		else if ( name == "posOff" )
		{
			_applyPosOff( val.get<Vector2>() );
		}
		else if ( name == "colorAdd" )
		{
			_applyColorAdd( val.get<Vector3>() );
		}
		else if ( name == "colorMuti" )
		{
			_applyColorMuti( val.get<Vector3>() );
		}
	}

	bool	ActorEffect::isLoop()
	{
		return mLoop;
	}


	void	ActorEffect::_applyAlpha( Real alpha )
	{
		ListAnim::iterator iterAnim = mAnims.begin();
		ListAnim::iterator iterAnimEnd = mAnims.end();

		while ( iterAnim != iterAnimEnd )
		{
			IAnimation2D* anim = (*iterAnim);
	
			anim->setAlpha( alpha );

			++iterAnim;
		}

		ListSprite::iterator iterSprite = mSprites.begin();
		ListSprite::iterator iterSpriteEnd = mSprites.end();

		while ( iterSprite != iterSpriteEnd )
		{
			ISprite2D* sprite = (*iterSprite);

			sprite->setAlpha( alpha );

			++iterSprite;
		}
	}

	void	ActorEffect::_applyRot( Real rot )
	{
		mSceneNode->setRotateX( rot );
	}

	void	ActorEffect::_applyScale( const Vector2& scale )
	{
		mSceneNode->setScale( scale );
	}

	void	ActorEffect::_applyPosOff( const Vector2& posOff )
	{
		mSceneNode->addPositionOffset( posOff );
	}

	void	ActorEffect::_applyColorAdd( const Vector3& colorAdd )
	{
		ListAnim::iterator iterAnim = mAnims.begin();
		ListAnim::iterator iterAnimEnd = mAnims.end();

		while ( iterAnim != iterAnimEnd )
		{
			IAnimation2D* anim = (*iterAnim);

			anim->setColorAdd( colorAdd );

			++iterAnim;
		}

		ListSprite::iterator iterSprite = mSprites.begin();
		ListSprite::iterator iterSpriteEnd = mSprites.end();

		while ( iterSprite != iterSpriteEnd )
		{
			ISprite2D* sprite = (*iterSprite);

			sprite->setColorAdd( colorAdd );

			++iterSprite;
		}
	}

	void	ActorEffect::_applyColorMuti( const Vector3& colorMuti )
	{
		ListAnim::iterator iterAnim = mAnims.begin();
		ListAnim::iterator iterAnimEnd = mAnims.end();

		while ( iterAnim != iterAnimEnd )
		{
			IAnimation2D* anim = (*iterAnim);

			anim->setColorMuti( colorMuti );

			++iterAnim;
		}

		ListSprite::iterator iterSprite = mSprites.begin();
		ListSprite::iterator iterSpriteEnd = mSprites.end();

		while ( iterSprite != iterSpriteEnd )
		{
			ISprite2D* sprite = (*iterSprite);

			sprite->setColorMuti( colorMuti );

			++iterSprite;
		}
	}


	//--
	const String ActorFactoryEffect::TypeName = "Effect";
	ActorFactoryEffect::ActorFactoryEffect()
	{
		registActionFactory( new ActionFactoryEffectUpdate );
	}

	ActorFactoryEffect::~ActorFactoryEffect()
	{

	}

	const String&	ActorFactoryEffect::type() const
	{
		return ActorFactoryEffect::TypeName;
	}

	Actor*	ActorFactoryEffect::createInstance( ActorDesc* actorDesc, ISceneNode2D* node, IScene* scene, const String& name )
	{
		ActorEffect* actor = new ActorEffect( actorDesc, node, scene );

		//	create actions
		_createActions( actor, actorDesc );

		actor->initailze();

		return actor;
	}

	ActorDesc*	ActorFactoryEffect::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActorDescEffect* actorDesc = new ActorDescEffect;

		_loadBaseActorDesc( actorDesc, xmlNode, filename );

		_loadActionDesc( actorDesc, xmlNode, filename );

		nodeAttr = xmlNode->first_attribute( "loop" );

		if ( nodeAttr )
		{
			actorDesc->loop = StringConverter::parseBool( nodeAttr->value() );
		}
		else
		{
			actorDesc->loop = false;
		}

		//	sprite
		xml_node<>* spriteNode = xmlNode->first_node( "sprite" );
		while ( spriteNode )
		{
			SpriteElement spriteEle;

			nodeAttr = spriteNode->first_attribute( "id" );

			spriteEle.id = nodeAttr->value();

			nodeAttr = spriteNode->first_attribute( "layer" );
			spriteEle.layer = StringConverter::parseInt( nodeAttr->value() );

			actorDesc->sprites.push_back( spriteEle );

			spriteNode = spriteNode->next_sibling( "sprite" );
		}


		//	animation
		xml_node<>* animNode = xmlNode->first_node( "anim" );
		while ( animNode )
		{
			AnimElement animEle;
			nodeAttr = animNode->first_attribute( "id" );

			animEle.id = nodeAttr->value();

			nodeAttr = animNode->first_attribute( "layer" );
			animEle.layer = StringConverter::parseInt( nodeAttr->value() );

			actorDesc->anims.push_back( animEle );

			animNode = animNode->next_sibling( "anim" );
		}

		return actorDesc;
	}
}