#include "SystemPrerequisites.h"
#include "ActionEnergyBmobFly.h"
#include "IAnimation2D.h"
#include "IAnimation2DManager.h"
#include "ISceneNode2D.h"
#include "ActorEnergyBmob.h"
#include "ActionEnergyBmobStop.h"
#include "ActorPlayer.h"

namespace Ogre
{
	struct ActionDescEnergyBmobFly: public ActionDesc
	{
		AnimElement	body;
	};

	ActionEnergyBmobFly::ActionEnergyBmobFly(Actor* owner, ActionDesc* desc)
		: Action(desc, owner)
		, mActorEnergyBmob( 0 )
		, mEnergyBmobBody( 0 )
		, mSpeed(0.0f)
	{
		mActorEnergyBmob = static_cast<ActorEnergyBmob*>(owner);
		ActionDescEnergyBmobFly* actionDesc = static_cast<ActionDescEnergyBmobFly*>(desc);

		mEnergyBmobBody = gEnv->mAnimationMgr->create(actionDesc->body.id);
		mEnergyBmobBody->setRenderQueue(actionDesc->body.layer);
		mSpeed = actionDesc->body.speed;
	}

	ActionEnergyBmobFly::~ActionEnergyBmobFly()
	{
		mEnergyBmobBody->destroy();
		mEnergyBmobBody = 0;
	}

	void ActionEnergyBmobFly::initailze()
	{
		
	}

	const String& ActionEnergyBmobFly::type() const
	{
		return ActionFactoryEnergyBmobFly::TypeName;
	}

	void ActionEnergyBmobFly::begin()
	{
		Action::begin();
		mOwner->getSceneNode()->attachObject(mEnergyBmobBody);
	}

	void ActionEnergyBmobFly::end()
	{
		mOwner->getSceneNode()->detachObject(mEnergyBmobBody);
		Action::end();
	}

	void ActionEnergyBmobFly::update(Real timelapse)
	{
		// 如果到达屏幕正中就立即切换状态
		const Vector2& dir = mActorEnergyBmob->getDir();
		Vector2 step = dir * (timelapse/1.0f*mSpeed);
		mOwner->getSceneNode()->translate( step );

		ActorPlayer* pPlayer = static_cast<ActorPlayer*>(mActorEnergyBmob->getActorPlayer());
		Vector3 v3Player = pPlayer->getSceneNode()->getPosition();
		Vector3 v3Pos = mOwner->getSceneNode()->getPosition();
		Real fDistance = mActorEnergyBmob->getDistance();
		Real rLength = sqrt((v3Pos.z-v3Player.z)*(v3Pos.z-v3Player.z) + (v3Pos.y-v3Player.y)*(v3Pos.y-v3Player.y));
		if (rLength>= fDistance)
		{
			mOwner->changeActionTo( ActionFactoryEnergyBmobStop::TypeName );
		}
	}

	IAnimation2D* ActionEnergyBmobFly::getBody()
	{
		return mEnergyBmobBody;
	}

	const String ActionFactoryEnergyBmobFly::TypeName = "BmobFly";
	ActionFactoryEnergyBmobFly::ActionFactoryEnergyBmobFly()
	{

	}

	ActionFactoryEnergyBmobFly::~ActionFactoryEnergyBmobFly()
	{
	}

	const String& ActionFactoryEnergyBmobFly::type() const
	{
		return TypeName;
	}

	Action* ActionFactoryEnergyBmobFly::createInstance( Actor* owner, ActionDesc* desc )
	{
		ActionEnergyBmobFly *action = new ActionEnergyBmobFly(owner, desc);
		return action;
	}

	ActionDesc*	ActionFactoryEnergyBmobFly::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActionDescEnergyBmobFly* actionDesc = new ActionDescEnergyBmobFly;

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
		actionDesc->body.layer = StringConverter::parseInt( nodeAttr->value() );

		// speed移动速度
		xml_node<>* xmlNodeSpeed = xmlNode->first_node("speed");
		if (!xmlNodeSpeed)
		{
			EXCEPTEX( "bmob actor. move action. need body label. filename: " << filename );
		}
		nodeAttr = xmlNodeSpeed->first_attribute("val");
		if (!nodeAttr)
		{
			EXCEPTEX( "bmob actor. move action. body need speed label. filename: " << filename );
		}
		actionDesc->body.speed = StringConverter::parseReal(nodeAttr->value());

		return actionDesc;
	}
}