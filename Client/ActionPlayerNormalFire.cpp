#include "SystemPrerequisites.h"
#include "ActionPlayerNormalFire.h"
#include "ActorPlayer.h"

namespace Ogre
{
	struct ActionDescPlayerNormalFire: public ActionDesc
	{

	};

	ActionPlayerNormalFire::ActionPlayerNormalFire(Actor* owner, ActionDesc* desc)
		: Action(desc, owner)
		, mActorPlayer(0)
		, mTimes(0.0f)
		, mIsFired(false)
	{
		mActorPlayer = static_cast<ActorPlayer*>(owner);
	}

	ActionPlayerNormalFire::~ActionPlayerNormalFire()
	{

	}

	void ActionPlayerNormalFire::initailze()
	{

	}

	const String& ActionPlayerNormalFire::type() const
	{
		return ActionFactoryPlayerNormalFire::TypeName;
	}

	void ActionPlayerNormalFire::begin()
	{
		Action::begin();
		if (!mIsFired)
		{
			if (mActorPlayer->checkFire())
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

	void ActionPlayerNormalFire::end()
	{
		Action::end();
	}

	void ActionPlayerNormalFire::update(Real timeLapse)
	{
		// 发炮（获取player的发炮action）
		mTimes += timeLapse;
		if (mTimes> mActorPlayer->getFireInternalTime())
		{
			//mOwner->changeActionToDefault();
			mIsFired = false;
			mTimes = 0;
		}
	}

	const String ActionFactoryPlayerNormalFire::TypeName = "Gun_NormalFire";
	ActionFactoryPlayerNormalFire::ActionFactoryPlayerNormalFire()
	{

	}

	ActionFactoryPlayerNormalFire::~ActionFactoryPlayerNormalFire()
	{

	}

	const String& ActionFactoryPlayerNormalFire::type() const
	{
		return TypeName;
	}

	Action* ActionFactoryPlayerNormalFire::createInstance( Actor* owner, ActionDesc* desc )
	{
		ActionPlayerNormalFire* action = new ActionPlayerNormalFire(owner, desc);
		return action;
	}

	ActionDesc* ActionFactoryPlayerNormalFire::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActionDescPlayerNormalFire* actionDesc = new ActionDescPlayerNormalFire;

		_loadBaseActionDesc( actionDesc, xmlNode, filename );

		return actionDesc;
	}
}