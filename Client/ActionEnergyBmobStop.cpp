#include "SystemPrerequisites.h"
#include "ActionEnergyBmobStop.h"
#include "IAnimation2D.h"
#include "IAnimation2DManager.h"
#include "ISceneNode2D.h"
#include "ActorEnergyBmob.h"
#include "ActionEnergyBmobAttack.h"
#include "ActionEnergyBmobFly.h"

namespace Ogre
{
	struct ActionDescEnergyBmobStop: public ActionDesc
	{
		Real		waitTime;
	};

	ActionEnergyBmobStop::ActionEnergyBmobStop(Actor* owner, ActionDesc* desc)
		: Action(desc, owner)
		, mTimes(0.0f)
		, mWaitTime(0.0f)
		, mEnergyBmobBody(NULL)
	{
		ActionDescEnergyBmobStop* actionDesc = static_cast<ActionDescEnergyBmobStop*>(desc);

		mWaitTime = actionDesc->waitTime;
	}

	ActionEnergyBmobStop::~ActionEnergyBmobStop()
	{

	}

	void ActionEnergyBmobStop::initailze()
	{
		ActionEnergyBmobFly* actionFly = static_cast< ActionEnergyBmobFly* >( mOwner->getAction( ActionFactoryEnergyBmobFly::TypeName ) );
		mEnergyBmobBody = actionFly->getBody();
	}

	const String& ActionEnergyBmobStop::type() const
	{
		return ActionFactoryEnergyBmobStop::TypeName;
	}

	void ActionEnergyBmobStop::begin()
	{
		Action::begin();
		mOwner->getSceneNode()->attachObject( mEnergyBmobBody );
	}

	void ActionEnergyBmobStop::end()
	{
		mOwner->getSceneNode()->detachObject( mEnergyBmobBody );
		Action::end();
	}

	void ActionEnergyBmobStop::update(Real timelapse)
	{
		mTimes += timelapse;
		if (mTimes> mWaitTime)
		{
			// ÇÐ»»×´Ì¬
			mOwner->changeActionTo(ActionFactoryEnergyBmobAttack::TypeName);
			mTimes = 0;
		}
	}

	const String ActionFactoryEnergyBmobStop::TypeName = "BmobStop";
	ActionFactoryEnergyBmobStop::ActionFactoryEnergyBmobStop()
	{

	}

	ActionFactoryEnergyBmobStop::~ActionFactoryEnergyBmobStop()
	{
	}

	const String& ActionFactoryEnergyBmobStop::type() const
	{
		return TypeName;
	}

	Action* ActionFactoryEnergyBmobStop::createInstance( Actor* owner, ActionDesc* desc )
	{
		ActionEnergyBmobStop *action = new ActionEnergyBmobStop(owner, desc);
		return action;
	}

	ActionDesc*	ActionFactoryEnergyBmobStop::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActionDescEnergyBmobStop* actionDesc = new ActionDescEnergyBmobStop;

		_loadBaseActionDesc( actionDesc, xmlNode, filename );

		nodeAttr = xmlNode->first_attribute( "waitTime" );
		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "coin actor. Stop action. need body label. filename: " << filename );
		}
		actionDesc->waitTime = StringConverter::parseReal(nodeAttr->value());
	
		return actionDesc;
	}
}