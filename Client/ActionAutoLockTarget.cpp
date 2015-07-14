#include "SystemPrerequisites.h"
#include "ActionAutoLockTarget.h"
#include "IAnimation2D.h"
#include "IAnimation2DManager.h"
#include "ISceneNode2D.h"
#include "ActorAutoLockTarget.h"

namespace Ogre
{
	struct ActionDescAutoLockTarget: public ActionDesc
	{
		AnimElement body;
	};

	ActionAutoLockTarget::ActionAutoLockTarget(Actor* owner, ActionDesc* desc)
		: Action(desc, owner)
		, mActorLockTarget(0)
		, mLockTargetAnim(0)
	{
		mActorLockTarget = static_cast<ActorAutoLockTarget*>(owner);
		ActionDescAutoLockTarget* actionDesc = static_cast<ActionDescAutoLockTarget*>(desc);

		mLockTargetAnim = gEnv->mAnimationMgr->create(actionDesc->body.id);
		mLockTargetAnim->setRenderQueue(actionDesc->body.layer);
	}

	ActionAutoLockTarget::~ActionAutoLockTarget()
	{
		mLockTargetAnim->destroy();
		mLockTargetAnim = 0;
	}

	void ActionAutoLockTarget::initailze()
	{

	}

	const String& ActionAutoLockTarget::type() const
	{
		return ActionFactoryAutoLockTarget::TypeName;
	}

	void ActionAutoLockTarget::begin()
	{
		Action::begin();
		mOwner->getSceneNode()->attachObject(mLockTargetAnim);
	}

	void ActionAutoLockTarget::end()
	{
		mOwner->getSceneNode()->detachObject(mLockTargetAnim);
		Action::end();
	}

	void ActionAutoLockTarget::update(Real timelapse)
	{

	}

	IAnimation2D* ActionAutoLockTarget::getBody()
	{
		return mLockTargetAnim;
	}

	const String ActionFactoryAutoLockTarget::TypeName = "LockTarget";
	ActionFactoryAutoLockTarget::ActionFactoryAutoLockTarget()
	{

	}

	ActionFactoryAutoLockTarget::~ActionFactoryAutoLockTarget()
	{
	}

	const String& ActionFactoryAutoLockTarget::type() const
	{
		return TypeName;
	}

	Action* ActionFactoryAutoLockTarget::createInstance( Actor* owner, ActionDesc* desc )
	{
		ActionAutoLockTarget *action = new ActionAutoLockTarget(owner, desc);
		return action;
	}

	ActionDesc*	ActionFactoryAutoLockTarget::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActionDescAutoLockTarget* actionDesc = new ActionDescAutoLockTarget;

		_loadBaseActionDesc( actionDesc, xmlNode, filename );

		xml_node<>* xmlNodeBody = xmlNode->first_node( "body" );
		if ( xmlNodeBody == 0 )
		{
			EXCEPTEX( "bmob actor. move action. need body label. filename: " << filename );
		}

		nodeAttr = xmlNodeBody->first_attribute( "animId" );
		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "bmob actor. move action. body need animId label. filename: " << filename );
		}
		actionDesc->body.id = nodeAttr->value();
		nodeAttr = xmlNodeBody->first_attribute( "layer" );
		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "bmob actor. move action. body need layer label. filename: " << filename );
		}
		actionDesc->body.layer = StringConverter::parseInt( nodeAttr->value() );;

		return actionDesc;
	}
}