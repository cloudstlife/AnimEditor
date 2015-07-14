#include "SystemPrerequisites.h"
#include "ActionFishMove.h"
#include "ISprite2D.h"
#include "IAnimation2D.h"
#include "ISprite2DManager.h"
#include "IAnimation2DManager.h"
#include "ISceneNode2D.h"
#include "NormalActorFish.h"

namespace Ogre
{	
	struct ActionDescFishMove : public ActionDesc
	{
		AnimElement		body;
	};

	//---
	ActionFishMove::ActionFishMove( Actor* owner, ActionDesc* desc )
	: Action( desc, owner )
	{
		mActorFish = static_cast< NormalActorFish* >( owner );
		ActionDescFishMove* actionDesc = static_cast< ActionDescFishMove* >( desc );
		mFishBody = gEnv->mAnimationMgr->create( actionDesc->body.id );
		mFishBody->setRenderQueue( actionDesc->body.layer );
	}

	ActionFishMove::~ActionFishMove()
	{
		mFishBody->destroy();
		mFishBody = 0;
	}

	void	ActionFishMove::initailze()
	{

	}

	const String&	ActionFishMove::type() const
	{
		return ActionFactoryFishMove::TypeName;
	}

	void	ActionFishMove::begin()
	{
		Action::begin();

		mOwner->getSceneNode()->attachObject( mFishBody );
	}

	void	ActionFishMove::end()
	{
		mOwner->getSceneNode()->detachObject( mFishBody );

		Action::end();
	}

	void	ActionFishMove::update( Real timelapse )
	{
		
	}

	IAnimation2D*	ActionFishMove::getBody()
	{
		return mFishBody;
	}

	//---
	const String ActionFactoryFishMove::TypeName = "Move";
	ActionFactoryFishMove::ActionFactoryFishMove()
	{

	}

	ActionFactoryFishMove::~ActionFactoryFishMove()
	{

	}

	const String&	ActionFactoryFishMove::type() const
	{

		return TypeName;
	}

	Action*	ActionFactoryFishMove::createInstance( Actor* owner, ActionDesc* desc )
	{
		ActionFishMove* action = new ActionFishMove( owner, desc );
		
		return action;
	}

	ActionDesc*	ActionFactoryFishMove::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActionDescFishMove* actionDesc = new ActionDescFishMove;

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