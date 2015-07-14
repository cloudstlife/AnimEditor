#include "SystemPrerequisites.h"
#include "ActionBulletFly.h"
#include "ISprite2D.h"
#include "IAnimation2D.h"
#include "ISprite2DManager.h"
#include "IAnimation2DManager.h"
#include "ISceneNode2D.h"
#include "ActorBullet.h"
#include "ActionBulletAttack.h"
#include "ogre_src_v1-8-1/OgreViewport.h"

namespace Ogre
{	
	struct ActionDescBulletFly : public ActionDesc
	{
		AnimElement		body;
		Real			speed;
	};

	//---
	ActionBulletFly::ActionBulletFly( Actor* owner, ActionDesc* desc )
	: Action( desc, owner )
	, mScreenHeight(0)
	, mScreenWidth(0)
	, mSpeed(0.0f)
	{
		mActorBullet = static_cast< ActorBullet* >( owner );
		ActionDescBulletFly* actionDesc = static_cast< ActionDescBulletFly* >( desc );

		mBulletBody = gEnv->mAnimationMgr->create( actionDesc->body.id );
		mBulletBody->setRenderQueue( actionDesc->body.layer );

		mSpeed = actionDesc->speed;
		mScreenHeight = gEnv->mSystem->getMainViewport()->getActualHeight();
		mScreenWidth = gEnv->mSystem->getMainViewport()->getActualWidth();
	}

	ActionBulletFly::~ActionBulletFly()
	{
		mBulletBody->destroy();
		mBulletBody = 0;
	}

	void	ActionBulletFly::initailze()
	{

	}

	const String&	ActionBulletFly::type() const
	{
		return ActionFactoryBulletFly::TypeName;
	}

	void	ActionBulletFly::begin()
	{
		Action::begin();
		mOwner->getSceneNode()->attachObject( mBulletBody );
	}

	void	ActionBulletFly::end()
	{
		mOwner->getSceneNode()->detachObject( mBulletBody ); ;
		Action::end();
	}

	void	ActionBulletFly::update( Real timelapse )
	{
		bool bToBound = _calcBulletToBound();
		if (bToBound)
		{
			// 方向反转取炮台位置
			Actor* pActor = mActorBullet->getActorPlayer();
			Vector3 v3PlayerPos = pActor->getSceneNode()->getPosition();
			Vector3 v3BulletPos = mOwner->getSceneNode()->getPosition();
			Vector3 v3Dir = v3PlayerPos - v3BulletPos;
			Vector2 tran = Vector2::ZERO;
			tran.x = v3Dir.z/(sqrt(v3Dir.z*v3Dir.z+v3Dir.y*v3Dir.y));
			tran.y = v3Dir.y/(sqrt(v3Dir.z*v3Dir.z+v3Dir.y*v3Dir.y));
			mActorBullet->setDir(tran.x, tran.y);
		}

		const Vector2& dir = mActorBullet->getDir();
		Vector2 step = dir * (timelapse/1.0f*mSpeed);
		mOwner->getSceneNode()->translate( step );
	}

	void	ActionBulletFly::beginContact( Actor* other )
	{
		mOwner->changeActionTo( ActionFactoryBulletAttack::TypeName );
	}

	void	ActionBulletFly::endContact( Actor* other )
	{
	}

	bool	ActionBulletFly::_calcBulletToBound()
	{
		bool ret = false;
		if (mOwner && (mOwner->getSceneNode()->getPosition().z<0
			|| mOwner->getSceneNode()->getPosition().z> mScreenWidth
			|| mOwner->getSceneNode()->getPosition().y< 0
			|| mOwner->getSceneNode()->getPosition().y> mScreenHeight))
		{
			ret = true;
		}
		return ret;
	}

	//---
	const String ActionFactoryBulletFly::TypeName = "Fly";
	ActionFactoryBulletFly::ActionFactoryBulletFly()
	{

	}

	ActionFactoryBulletFly::~ActionFactoryBulletFly()
	{

	}

	const String&	ActionFactoryBulletFly::type() const
	{

		return TypeName;
	}

	Action*	ActionFactoryBulletFly::createInstance( Actor* owner, ActionDesc* desc )
	{
		ActionBulletFly* action = new ActionBulletFly( owner, desc );
		
		return action;
	}

	ActionDesc*	ActionFactoryBulletFly::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActionDescBulletFly* actionDesc = new ActionDescBulletFly;

		_loadBaseActionDesc( actionDesc, xmlNode, filename );

		xml_node<>* xmlNodeBody = xmlNode->first_node( "body" );
		if ( xmlNodeBody == 0 )
		{
			EXCEPTEX( "bullet actor. fly action. need body label. filename: " << filename );
		}

		nodeAttr = xmlNodeBody->first_attribute( "animId" );
		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "bullet actor. fly action. body need animId label. filename: " << filename );
		}

		actionDesc->body.id = nodeAttr->value();

		nodeAttr = xmlNodeBody->first_attribute( "layer" );
		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "bullet actor. fly action. body need layer label. filename: " << filename );
		}
		actionDesc->body.layer = StringConverter::parseInt( nodeAttr->value() );

		xml_node<>* xmlNodeSpeed = xmlNode->first_node( "speed" );
		if ( xmlNodeSpeed == 0 )
		{
			EXCEPTEX( "bullet actor. fly action. need speed label. filename: " << filename );
		}

		nodeAttr = xmlNodeSpeed->first_attribute( "val" );
		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "bullet actor. fly action. speed need val label. filename: " << filename );
		}
		actionDesc->speed = StringConverter::parseReal( nodeAttr->value() );

		return actionDesc;
	}

}