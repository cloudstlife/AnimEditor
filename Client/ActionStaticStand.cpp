#include "SystemPrerequisites.h"
#include "ActionStaticStand.h"
#include "ISprite2D.h"
#include "IAnimation2D.h"
#include "ISprite2DManager.h"
#include "IAnimation2DManager.h"
#include "ISceneNode2D.h"
#include "ActorStatic.h"

namespace Ogre
{	
	struct ActionDescStaticStand : public ActionDesc
	{
		ListSpriteElem		sprites;
		ListAnimElem		anims;
	};

	//---
	ActionStaticStand::ActionStaticStand( Actor* owner, ActionDesc* desc )
	: Action( desc, owner )
	{
		mActorStatic = static_cast< ActorStatic* >( owner );
		ActionDescStaticStand* actionDesc = static_cast< ActionDescStaticStand* >( desc );

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

	ActionStaticStand::~ActionStaticStand()
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

	void	ActionStaticStand::initailze()
	{

	}

	const String&	ActionStaticStand::type() const
	{
		return ActionFactoryStaticStand::TypeName;
	}

	void	ActionStaticStand::begin()
	{
		Action::begin();

		ListAnim::iterator iterAnim = mAnims.begin();
		ListAnim::iterator iterAnimEnd = mAnims.end();

		while ( iterAnim != iterAnimEnd )
		{
			IAnimation2D* anim = (*iterAnim);

			mOwner->getSceneNode()->attachObject( anim );

			++iterAnim;
		}

		ListSprite::iterator iterSprite = mSprites.begin();
		ListSprite::iterator iterSpriteEnd = mSprites.end();

		while ( iterSprite != iterSpriteEnd )
		{
			ISprite2D* sprite = (*iterSprite);

			mOwner->getSceneNode()->attachObject( sprite );

			++iterSprite;
		}
	}

	void	ActionStaticStand::end()
	{
		ListAnim::iterator iterAnim = mAnims.begin();
		ListAnim::iterator iterAnimEnd = mAnims.end();

		while ( iterAnim != iterAnimEnd )
		{
			IAnimation2D* anim = (*iterAnim);

			mOwner->getSceneNode()->detachObject( anim ); ;

			++iterAnim;
		}

		ListSprite::iterator iterSprite = mSprites.begin();
		ListSprite::iterator iterSpriteEnd = mSprites.end();

		while ( iterSprite != iterSpriteEnd )
		{
			ISprite2D* sprite = (*iterSprite);

			mOwner->getSceneNode()->detachObject( sprite );

			++iterSprite;
		}

		Action::end();
	}

	void	ActionStaticStand::update( Real timelapse )
	{
		
	}

	//---
	const String ActionFactoryStaticStand::TypeName = "Stand";
	ActionFactoryStaticStand::ActionFactoryStaticStand()
	{

	}

	ActionFactoryStaticStand::~ActionFactoryStaticStand()
	{

	}

	const String&	ActionFactoryStaticStand::type() const
	{

		return TypeName;
	}

	Action*	ActionFactoryStaticStand::createInstance( Actor* owner, ActionDesc* desc )
	{
		ActionStaticStand* action = new ActionStaticStand( owner, desc );
		
		return action;
	}

	ActionDesc*	ActionFactoryStaticStand::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActionDescStaticStand* actionDesc = new ActionDescStaticStand;

		_loadBaseActionDesc( actionDesc, xmlNode, filename );

		//	sprite
		xml_node<>* spriteNode = xmlNode->first_node( "sprite" );
		while ( spriteNode )
		{
			SpriteElement spriteEle;

			nodeAttr = spriteNode->first_attribute( "id" );

			spriteEle.id = nodeAttr->value();

			nodeAttr = spriteNode->first_attribute( "layer" );
			spriteEle.layer = StringConverter::parseInt( nodeAttr->value() );

			actionDesc->sprites.push_back( spriteEle );

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

			actionDesc->anims.push_back( animEle );

			animNode = animNode->next_sibling( "anim" );
		}

		return actionDesc;
	}

}