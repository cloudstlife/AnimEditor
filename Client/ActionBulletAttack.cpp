#include "SystemPrerequisites.h"
#include "ActionBulletAttack.h"
#include "ISprite2D.h"
#include "IAnimation2D.h"
#include "ISprite2DManager.h"
#include "IAnimation2DManager.h"
#include "ISceneNode2D.h"
#include "ActorBullet.h"
#include "NormalActorFish.h"
#include "ActionFishHurt.h"
#include "ActionFishDied.h"
#include "ICollision2D.h"

namespace Ogre
{	
	struct ActionDescBulletAttack : public ActionDesc
	{
		AnimElement		body;
	};

	//---
	ActionBulletAttack::ActionBulletAttack( Actor* owner, ActionDesc* desc )
	: Action( desc, owner )
	{
		mActorBullet = static_cast< ActorBullet* >( owner );
		ActionDescBulletAttack* actionDesc = static_cast< ActionDescBulletAttack* >( desc );

		mBulletAttack = gEnv->mAnimationMgr->create( actionDesc->body.id );
		mBulletAttack->setRenderQueue( actionDesc->body.layer );
	}

	ActionBulletAttack::~ActionBulletAttack()
	{
		mBulletAttack->destroy();
		mBulletAttack = 0;
	}

	void	ActionBulletAttack::initailze()
	{

	}

	const String&	ActionBulletAttack::type() const
	{
		return ActionFactoryBulletAttack::TypeName;
	}

	void	ActionBulletAttack::begin()
	{
		Action::begin();
		mOwner->getSceneNode()->attachObject( mBulletAttack );
		mCollision->refresh();
	}

	void	ActionBulletAttack::end()
	{
		mOwner->getSceneNode()->detachObject( mBulletAttack ); 

		Action::end();
	}

	void	ActionBulletAttack::update( Real timelapse )
	{
		if ( mLifeTimeLapse >= mLifeTime )
		{
			mOwner->valid();
		}

		mLifeTimeLapse += timelapse;
	}

	void	ActionBulletAttack::beginContact( Actor* other )
	{
		if ( RTTI::IsKindOf( other->getRTTI(), GETRTTI( NormalActorFish ) ) )
		{
			NormalActorFish* fish = static_cast< NormalActorFish* >( other );

			if ( mFishHited.find( fish ) == mFishHited.end() )
			{
				if ( fish->currentAction()->type() != ActionFactoryFishDied::TypeName )
				{
					fish->setActorPlayer(mActorBullet->getActorPlayer());
					fish->changeActionTo( ActionFactoryFishHurt::TypeName );
					mFishHited.insert( fish );
					
				}
			}
			
		}

	}

	void	ActionBulletAttack::endContact( Actor* other )
	{

	}

	//---
	const String ActionFactoryBulletAttack::TypeName = "Attack";
	ActionFactoryBulletAttack::ActionFactoryBulletAttack()
	{

	}

	ActionFactoryBulletAttack::~ActionFactoryBulletAttack()
	{

	}

	const String&	ActionFactoryBulletAttack::type() const
	{

		return TypeName;
	}

	Action*	ActionFactoryBulletAttack::createInstance( Actor* owner, ActionDesc* desc )
	{
		ActionBulletAttack* action = new ActionBulletAttack( owner, desc );
		
		return action;
	}

	ActionDesc*	ActionFactoryBulletAttack::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActionDescBulletAttack* actionDesc = new ActionDescBulletAttack;

		_loadBaseActionDesc( actionDesc, xmlNode, filename );

		xml_node<>* xmlNodeBody = xmlNode->first_node( "body" );
		if ( xmlNodeBody == 0 )
		{
			EXCEPTEX( "fish actor. move action. need body label. filename: " << filename );
		}

		nodeAttr = xmlNodeBody->first_attribute( "animId" );
		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "fish actor. move action. body need animId label. filename: " << filename );
		}

		actionDesc->body.id = nodeAttr->value();

		nodeAttr = xmlNodeBody->first_attribute( "layer" );
		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "fish actor. move action. body need layer label. filename: " << filename );
		}
		actionDesc->body.layer = StringConverter::parseInt( nodeAttr->value() );

		return actionDesc;
	}

}