#include "SystemPrerequisites.h"
#include "ActionEnergyBmobIdle.h"
#include "IAnimation2D.h"
#include "IAnimation2DManager.h"
#include "ISceneNode2D.h"
#include "ActorEnergyBmob.h"


namespace Ogre
{
	struct ActionDescEnergyBmobIdle: public ActionDesc
	{
		AnimElement	body;
	};

	ActionEnergyBmobIdle::ActionEnergyBmobIdle(Actor* owner, ActionDesc* desc)
		: Action(desc, owner)
		, mActorEnergyBmob( NULL )
		, mEnergyBmobBody( NULL )
	{
		mActorEnergyBmob = static_cast<ActorEnergyBmob*>(owner);
		ActionDescEnergyBmobIdle* actionDesc = static_cast<ActionDescEnergyBmobIdle*>(desc);

		mEnergyBmobBody = gEnv->mAnimationMgr->create(actionDesc->body.id);
		mEnergyBmobBody->setRenderQueue(actionDesc->body.layer);
	}

	ActionEnergyBmobIdle::~ActionEnergyBmobIdle()
	{
		mEnergyBmobBody->destroy();
		mEnergyBmobBody = 0;

	}

	void ActionEnergyBmobIdle::initailze()
	{

	}

	const String& ActionEnergyBmobIdle::type() const
	{
		return ActionFactoryEnergyBmobIdle::TypeName;
	}

	void ActionEnergyBmobIdle::begin()
	{
		Action::begin();
		mOwner->getSceneNode()->attachObject(mEnergyBmobBody);
	}

	void ActionEnergyBmobIdle::end()
	{
		mOwner->getSceneNode()->detachObject(mEnergyBmobBody);
		Action::end();
	}

	void ActionEnergyBmobIdle::update(Real timelapse)
	{

	}

	IAnimation2D* ActionEnergyBmobIdle::getBody()
	{
		return mEnergyBmobBody;
	}

	const String ActionFactoryEnergyBmobIdle::TypeName = "BmobIdle";
	ActionFactoryEnergyBmobIdle::ActionFactoryEnergyBmobIdle()
	{

	}

	ActionFactoryEnergyBmobIdle::~ActionFactoryEnergyBmobIdle()
	{
	}

	const String& ActionFactoryEnergyBmobIdle::type() const
	{
		return TypeName;
	}

	Action* ActionFactoryEnergyBmobIdle::createInstance( Actor* owner, ActionDesc* desc )
	{
		ActionEnergyBmobIdle *action = new ActionEnergyBmobIdle(owner, desc);
		return action;
	}

	ActionDesc*	ActionFactoryEnergyBmobIdle::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActionDescEnergyBmobIdle* actionDesc = new ActionDescEnergyBmobIdle;

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