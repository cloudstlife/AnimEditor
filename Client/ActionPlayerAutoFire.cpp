#include "SystemPrerequisites.h"
#include "ActionPlayerAutoFire.h"
#include "ActorPlayer.h"

namespace Ogre
{
	struct ActionDescPlayerAutoFire: public ActionDesc
	{
		
	};

	ActionPlayerAutoFire::ActionPlayerAutoFire(Actor* owner, ActionDesc* desc)
		: Action(desc, owner)
		, mActorPlayer(0)
		, mTimes(0.0f)
		, mIsFired(false)
	{
		mActorPlayer = static_cast<ActorPlayer*>(owner);
	}

	ActionPlayerAutoFire::~ActionPlayerAutoFire()
	{

	}

	void ActionPlayerAutoFire::initailze()
	{

	}

	const String& ActionPlayerAutoFire::type() const
	{
		return ActionFactoryPlayerAutoFire::TypeName;
	}

	void ActionPlayerAutoFire::begin()
	{
		Action::begin();
		if (!mIsFired)
		{
			if(mActorPlayer->checkFire())
			{
				if(mActorPlayer->getActionCommon() && mActorPlayer->getActionFire())
				{
					mOwner->changeActionTo( mActorPlayer->getActionFire()->type() );
					mIsFired = true;
				}
			}
		}
		else
		{
			mOwner->changeActionToDefault();
		}
	}

	void ActionPlayerAutoFire::end()
	{
		Action::end();
	}

	void ActionPlayerAutoFire::update(Real timeLapse)
	{
		// 发炮（获取player的发炮action）
		mTimes += timeLapse;
		if (mTimes> mActorPlayer->getFireInternalTime())
		{
			mOwner->changeActionTo("Gun_AutoFire");
			mIsFired = false;
			mTimes = 0;
		}
	}

	const String ActionFactoryPlayerAutoFire::TypeName = "Gun_AutoFire";
	ActionFactoryPlayerAutoFire::ActionFactoryPlayerAutoFire()
	{

	}

	ActionFactoryPlayerAutoFire::~ActionFactoryPlayerAutoFire()
	{

	}

	const String& ActionFactoryPlayerAutoFire::type() const
	{
		return TypeName;
	}

	Action* ActionFactoryPlayerAutoFire::createInstance( Actor* owner, ActionDesc* desc )
	{
		ActionPlayerAutoFire* action = new ActionPlayerAutoFire(owner, desc);
		return action;
	}

	ActionDesc* ActionFactoryPlayerAutoFire::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActionDescPlayerAutoFire* actionDesc = new ActionDescPlayerAutoFire;

		_loadBaseActionDesc( actionDesc, xmlNode, filename );

		return actionDesc;
	}
}