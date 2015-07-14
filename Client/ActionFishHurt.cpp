#include "SystemPrerequisites.h"
#include "ActionFishHurt.h"
#include "ISprite2D.h"
#include "IAnimation2D.h"
#include "ISprite2DManager.h"
#include "IAnimation2DManager.h"
#include "ISceneNode2D.h"
#include "NormalActorFish.h"
#include "ActionFishMove.h"
#include "ActionFishDied.h"

namespace Ogre
{	
	struct ActionDescBulletHurt : public ActionDesc
	{
		Vector3		hurtColorNormal;
	};

	//---
	ActionFishHurt::ActionFishHurt( Actor* owner, ActionDesc* desc )
	: Action( desc, owner )
	, mCanChangleColor( true )
	{
		mActorFish = static_cast< NormalActorFish* >( owner );
		ActionDescBulletHurt* actionDesc = static_cast< ActionDescBulletHurt* >( desc );

		mHurtColorNormal = actionDesc->hurtColorNormal;
	}

	ActionFishHurt::~ActionFishHurt()
	{
		
	}

	void	ActionFishHurt::initailze()
	{
		ActionFishMove* actionMove = static_cast< ActionFishMove* >( mOwner->getAction( ActionFactoryFishMove::TypeName ) );

		mFishBody = actionMove->getBody();
	}

	const String&	ActionFishHurt::type() const
	{
		return ActionFactoryFishHurt::TypeName;
	}

	void	ActionFishHurt::begin()
	{
		Action::begin();

		if ( mCanChangleColor )
		{
			mCanChangleColor = false;

			mFishBody->setColorAdd( mHurtColorNormal );

			mOwner->getSceneNode()->attachObject( mFishBody );
		}

		//	todo: 检测一次鱼是否会死掉
		Real result = Math::UnitRandom();
		if ( result > 0.8f )
		{
			mOwner->changeActionTo( ActionFactoryFishDied::TypeName );
		}
	}

	void	ActionFishHurt::end()
	{
		mCanChangleColor = true;

		mFishBody->setColorAdd( Vector3::ZERO );

		mOwner->getSceneNode()->detachObject( mFishBody );

		Action::end();
	}

	void	ActionFishHurt::update( Real timelapse )
	{
		mLifeTimeLapse += timelapse;

		if ( mLifeTimeLapse > mLifeTime )
		{
			mOwner->changeActionToDefault();

			mLifeTimeLapse = 0.f;
		}
	}

	//---
	const String ActionFactoryFishHurt::TypeName = "Hurt";
	ActionFactoryFishHurt::ActionFactoryFishHurt()
	{

	}

	ActionFactoryFishHurt::~ActionFactoryFishHurt()
	{

	}

	const String&	ActionFactoryFishHurt::type() const
	{

		return TypeName;
	}

	Action*	ActionFactoryFishHurt::createInstance( Actor* owner, ActionDesc* desc )
	{
		ActionFishHurt* action = new ActionFishHurt( owner, desc );
		
		return action;
	}

	ActionDesc*	ActionFactoryFishHurt::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActionDescBulletHurt* actionDesc = new ActionDescBulletHurt;

		_loadBaseActionDesc( actionDesc, xmlNode, filename );
		
		xml_node<>* xmlNodeHurtColor = xmlNode->first_node( "hurtColor" );
		if ( xmlNodeHurtColor )
		{
			nodeAttr = xmlNodeHurtColor->first_attribute( "val" );

			if ( nodeAttr )
			{
				actionDesc->hurtColorNormal = StringConverter::parseVector3( nodeAttr->value() );
			}
		}

		return actionDesc;
	}

}