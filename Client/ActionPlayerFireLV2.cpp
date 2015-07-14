#include "SystemPrerequisites.h"
#include "ActionPlayerFireLV2.h"
#include "ISprite2D.h"
#include "IAnimation2D.h"
#include "ISprite2DManager.h"
#include "IAnimation2DManager.h"
#include "IScene.h"
#include "ISceneNode2D.h"
#include "ActorPlayer.h"
#include "ActionPlayerCommonGunLV2.h"
#include "ActorBullet.h"
#include "ActorEnergyBmob.h"

namespace Ogre
{
  struct ActionDescPlayerFire:public ActionDesc
  {
    AnimElement			body;
	BulletInfoLV2		bulletInfo;
	BmobInfoLV2			bmobInfo;
  };

  ActionPlayerFireLV2::ActionPlayerFireLV2(Actor* owner, ActionDesc* desc)
    :Action(desc, owner)
	, mSceneNodePaoGuan( 0 )
	, mBulletPosOffset( 0.f, 57.5f, 0.f )
	, mBulletPosOffsetOrignal( 0.f, 57.5f, 0.f )
	, mDir( Vector3::UNIT_Y )
	, mDirOrignal( Vector3::UNIT_Y )
	, mActorBmobBody(0)
  {
    mActorPlayer = static_cast<ActorPlayer*>(owner);
    ActionDescPlayerFire *actionDesc = static_cast<ActionDescPlayerFire*>(desc);
    mActorPlayerBody = gEnv->mAnimationMgr->create(actionDesc->body.id);
    mActorPlayerBody->setRenderQueue(actionDesc->body.layer);
    mLifeTime = actionDesc->lifeTime;

	mActorBmobBody = gEnv->mAnimationMgr->create(actionDesc->body.id);
	mActorBmobBody->setRenderQueue(actionDesc->body.layer);
	// 子弹信息
	mBulletInfo.bulletId = actionDesc->bulletInfo.bulletId;
	// 炸弹信息
	mBmobInfo.bmobId = actionDesc->bmobInfo.bmobId;
  }

  ActionPlayerFireLV2::~ActionPlayerFireLV2()
  {
    mActorPlayerBody->destroy();
    mActorPlayerBody = 0;

	mActorBmobBody->destroy();
	mActorBmobBody = 0;
  }

  void ActionPlayerFireLV2::initailze()
  {

  }

  const String& ActionPlayerFireLV2::type() const
  {
    return ActionFactoryPlayerFireLV2::TypeName;
  }


	void ActionPlayerFireLV2::begin()
	{
		Action::begin();
		int iFireState = mActorPlayer->getFireState();
		if (mActorPlayer->isBmobFire() && ActorPlayer::ENormalState == iFireState)
		{
			// 发射炮弹
			mSceneNodePaoGuan->attachObject(mActorBmobBody);
			const Quaternion& quat = mSceneNodePaoGuan->getDerivedOrientation();
			mBulletPosOffset = quat * mBulletPosOffsetOrignal;
			mDir = quat * mDirOrignal;
			ISceneNode2D* nodeBmob = mScene->getRootSceneNode()->createChild();
			Vector3 pos = mSceneNodePaoGuan->getDerivedPosition() + mBulletPosOffset;
			nodeBmob->setPosition( pos.z, pos.y );
			ActorEnergyBmob* actBmob = static_cast< ActorEnergyBmob* >( mScene->createActor( mBmobInfo.bmobId, nodeBmob ) );
			actBmob->setDir( mDir.z, mDir.y );
			actBmob->setActorPlayer(mOwner);
			actBmob->fireBmob();
		}
		else
		{
			// 发射子弹
			mSceneNodePaoGuan->attachObject(mActorPlayerBody);
			const Quaternion& quat = mSceneNodePaoGuan->getDerivedOrientation();
			mBulletPosOffset = quat * mBulletPosOffsetOrignal;
			mDir = quat * mDirOrignal;
			ISceneNode2D* nodeBullet = mScene->getRootSceneNode()->createChild();
			Vector3 pos = mSceneNodePaoGuan->getDerivedPosition() + mBulletPosOffset;
			nodeBullet->setPosition( pos.z, pos.y );
			ActorBullet* actBullet = static_cast< ActorBullet* >( mScene->createActor( mBulletInfo.bulletId, nodeBullet ) );
			actBullet->setDir( mDir.z, mDir.y );
			actBullet->setActorPlayer(mOwner);
		}
	}

	void ActionPlayerFireLV2::end()
	{
		if(mSceneNodePaoGuan)
		{
			mSceneNodePaoGuan->detachObject(mActorPlayerBody);
			mSceneNodePaoGuan->detachObject(mActorBmobBody);
		}
		Action::end();
	}

  void ActionPlayerFireLV2::update(Real timeLapse)
  {
	  mLifeTimeLapse += timeLapse;
	  if ( mLifeTimeLapse > mLifeTime )
	  {
		  mOwner->changeActionToDefault();
		  mLifeTimeLapse = 0.f;
	  }
  }

  void ActionPlayerFireLV2::setProperty( const String& name, const Any& val )
  {
		if ( name == "SceneNodePaoGuan" )
		{
			mSceneNodePaoGuan = val.get<ISceneNode2D*>();
		}
  }

  IAnimation2D* ActionPlayerFireLV2::getBody()
  {
    return mActorPlayerBody;
  }

  const String ActionFactoryPlayerFireLV2::TypeName = "Gun_FireLV2";
  ActionFactoryPlayerFireLV2::ActionFactoryPlayerFireLV2()
  {

  }

  ActionFactoryPlayerFireLV2::~ActionFactoryPlayerFireLV2()
  {

  }

  const String& ActionFactoryPlayerFireLV2::type() const
  {
    return TypeName;
  }

  Action* ActionFactoryPlayerFireLV2::createInstance( Actor* owner, ActionDesc* desc )
  {
    ActionPlayerFireLV2* action = new ActionPlayerFireLV2(owner, desc);
    return action;
  }

  ActionDesc* ActionFactoryPlayerFireLV2::load( rapidxml::xml_node<>* xmlNode, const String& filename )
  {
    using namespace rapidxml;
    xml_attribute<>* nodeAttr = 0;
    ActionDescPlayerFire* actionDesc = new ActionDescPlayerFire;
    _loadBaseActionDesc( actionDesc, xmlNode, filename );

    xml_node<>* xmlNodeBody = xmlNode->first_node("body");
    if (xmlNodeBody == 0)
    {
      EXCEPTEX( "player actor. move action. need body label. filename: " << filename );
    }
    nodeAttr = xmlNodeBody->first_attribute("animId");
    if (nodeAttr == 0)
    {
      EXCEPTEX( "player actor. move action. body need animId label. filename: " << filename );
    }
    actionDesc->body.id = nodeAttr->value();
    nodeAttr = xmlNodeBody->first_attribute("layer");
    if (nodeAttr == 0)
    {
      EXCEPTEX( "player actor. move action. body need layer label. filename: " << filename );
    }
    actionDesc->body.layer =  StringConverter::parseInt( nodeAttr->value() );

	// bullet
	xml_node<>* xmlBulletBody = xmlNode->first_node("Bullet");
	if (!xmlBulletBody)
	{
		EXCEPTEX( "player actor. bullet body. need bullet label. filename: " << filename );
	}
	nodeAttr = xmlBulletBody->first_attribute("actorId");
	if (!nodeAttr)
	{
		EXCEPTEX( "player actor. bullet id. need bullet label. filename: " << filename );
	}
	actionDesc->bulletInfo.bulletId = nodeAttr->value();

	// bmob
	xml_node<>* xmlBmobBody = xmlNode->first_node("Bmob");
	if (!xmlBmobBody)
	{
		EXCEPTEX( "player actor. bmob body. need bullet label. filename: " << filename );
	}
	nodeAttr = xmlBmobBody->first_attribute("actorId");
	if (!nodeAttr)
	{
		EXCEPTEX( "player actor. Bmob id. need bullet label. filename: " << filename );
	}
	actionDesc->bmobInfo.bmobId = nodeAttr->value();
    return actionDesc;
  }
}