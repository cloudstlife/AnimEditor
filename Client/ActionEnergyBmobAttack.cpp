#include "SystemPrerequisites.h"
#include "ActionEnergyBmobAttack.h"
#include "IAnimation2D.h"
#include "IAnimation2DManager.h"
#include "ISceneNode2D.h"
#include "ActorEnergyBmob.h"
#include "NormalActorFish.h"
#include "ActionFishHurt.h"
#include "ActionFishDied.h"
#include "ICollision2D.h"

namespace Ogre
{
	struct ActionDescEnergyBmobAttack: public ActionDesc
	{
		AnimElement	body;
	};

	ActionEnergyBmobAttack::ActionEnergyBmobAttack(Actor* owner, ActionDesc* desc)
		: Action(desc, owner)
		, mActorEnergyBmob( 0 )
		, mEnergyBmobBody( 0 )
	{
		mActorEnergyBmob = static_cast<ActorEnergyBmob*>(owner);
		ActionDescEnergyBmobAttack* actionDesc = static_cast<ActionDescEnergyBmobAttack*>(desc);

		mEnergyBmobBody = gEnv->mAnimationMgr->create(actionDesc->body.id);
		mEnergyBmobBody->setRenderQueue(actionDesc->body.layer);
	}

	ActionEnergyBmobAttack::~ActionEnergyBmobAttack()
	{
		mEnergyBmobBody->destroy();
		mEnergyBmobBody = 0;

	}

	void ActionEnergyBmobAttack::initailze()
	{

	}

	const String& ActionEnergyBmobAttack::type() const
	{
		return ActionFactoryEnergyBmobAttack::TypeName;
	}

	void ActionEnergyBmobAttack::begin()
	{
		Action::begin();
		mOwner->getSceneNode()->attachObject(mEnergyBmobBody);
		mCollision->refresh();
	}

	void ActionEnergyBmobAttack::end()
	{
		mOwner->getSceneNode()->detachObject(mEnergyBmobBody);
		Action::end();
	}

	void ActionEnergyBmobAttack::update(Real timelapse)
	{
		if ( mLifeTimeLapse >= mLifeTime )
		{
			mOwner->valid();
		}

		mLifeTimeLapse += timelapse;
	}

	IAnimation2D* ActionEnergyBmobAttack::getBody()
	{
		return mEnergyBmobBody;
	}

	void	ActionEnergyBmobAttack::beginContact( Actor* other )
	{
		if ( RTTI::IsKindOf( other->getRTTI(), GETRTTI( NormalActorFish ) ) )
		{
			NormalActorFish* fish = static_cast< NormalActorFish* >( other );

			if ( mFishHited.find( fish ) == mFishHited.end() )
			{
				if ( fish->currentAction()->type() != ActionFactoryFishDied::TypeName )
				{
					fish->setActorPlayer(mActorEnergyBmob->getActorPlayer());
					fish->changeActionTo( ActionFactoryFishHurt::TypeName );
					mFishHited.insert( fish );
				}
			}
		}
	}

	void	ActionEnergyBmobAttack::endContact( Actor* other )
	{

	}

	const String ActionFactoryEnergyBmobAttack::TypeName = "BmobAttack";
	ActionFactoryEnergyBmobAttack::ActionFactoryEnergyBmobAttack()
	{

	}

	ActionFactoryEnergyBmobAttack::~ActionFactoryEnergyBmobAttack()
	{
	}

	const String& ActionFactoryEnergyBmobAttack::type() const
	{
		return TypeName;
	}

	Action* ActionFactoryEnergyBmobAttack::createInstance( Actor* owner, ActionDesc* desc )
	{
		ActionEnergyBmobAttack *action = new ActionEnergyBmobAttack(owner, desc);
		return action;
	}

	ActionDesc*	ActionFactoryEnergyBmobAttack::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActionDescEnergyBmobAttack* actionDesc = new ActionDescEnergyBmobAttack;

		_loadBaseActionDesc( actionDesc, xmlNode, filename );

		xml_node<>* xmlNodeBody = xmlNode->first_node( "body" );
		if ( xmlNodeBody == 0 )
		{
			EXCEPTEX( "coin actor. move action. need body label. filename: " << filename );
		}
		nodeAttr = xmlNodeBody->first_attribute( "animId" );
		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "coin actor. move action. body need animId label. filename: " << filename );
		}
		actionDesc->body.id = nodeAttr->value();
		nodeAttr = xmlNodeBody->first_attribute( "layer" );
		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "coin actor. move action. body need layer label. filename: " << filename );
		}
		actionDesc->body.layer = StringConverter::parseInt( nodeAttr->value() );

		return actionDesc;
	}
}