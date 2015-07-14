#include "SystemPrerequisites.h"
#include "ActionPlayerFireLV1.h"
#include "ISprite2D.h"
#include "IAnimation2D.h"
#include "ISprite2DManager.h"
#include "IAnimation2DManager.h"
#include "IScene.h"
#include "ISceneNode2D.h"
#include "ActorPlayer.h"
#include "ActorBullet.h"
#include "ActorEnergyBmob.h"

namespace Ogre
{
  struct ActionDescPlayerFire:public ActionDesc
  {
    AnimElement			body;
	BulletInfoLV1		bulletInfo;
	BmobInfoLV1			bmobInfo;
  };

  ActionPlayerFireLV1::ActionPlayerFireLV1(Actor* owner, ActionDesc* desc)
    :Action(desc, owner)
	, mSceneNodePaoGuan( 0 )
	, mBulletPosOffset( 0.f, 57.5f, 0.f )
	, mBulletPosOffsetOrignal( 0.f, 57.5f, 0.f )
	, mDir( Vector3::UNIT_Y )
	, mDirOrignal( Vector3::UNIT_Y )
	, mActorPlayer(NULL)
	, mActorPlayerBody(NULL)
	, mActorBmobBody(NULL)
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

  ActionPlayerFireLV1::~ActionPlayerFireLV1()
  {
    mActorPlayerBody->destroy();
    mActorPlayerBody = 0;

	mActorBmobBody->destroy();
	mActorBmobBody = 0;
  }

  void ActionPlayerFireLV1::initailze()
  {

  }

  const String& ActionPlayerFireLV1::type() const
  {
    return ActionFactoryPlayerFireLV1::TypeName;
  }


	void ActionPlayerFireLV1::begin()
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

	void ActionPlayerFireLV1::end()
	{
		if(mSceneNodePaoGuan)
		{
			mSceneNodePaoGuan->detachObject(mActorPlayerBody);
			mSceneNodePaoGuan->detachObject(mActorBmobBody);
		}
		Action::end();
	}

  void ActionPlayerFireLV1::update(Real timeLapse)
  {
	  mLifeTimeLapse += timeLapse;
	  if ( mLifeTimeLapse > mLifeTime )
	  {
		  mOwner->changeActionToDefault();
		  mLifeTimeLapse = 0.f;
	  }
  }

  void ActionPlayerFireLV1::setProperty( const String& name, const Any& val )
  {
		if ( name == "SceneNodePaoGuan" )
		{
			mSceneNodePaoGuan = val.get<ISceneNode2D*>();
		}
  }

  IAnimation2D* ActionPlayerFireLV1::getBody()
  {
    return mActorPlayerBody;
  }

  const String ActionFactoryPlayerFireLV1::TypeName = "Gun_FireLV1";
  ActionFactoryPlayerFireLV1::ActionFactoryPlayerFireLV1()
  {

  }

  ActionFactoryPlayerFireLV1::~ActionFactoryPlayerFireLV1()
  {

  }

  const String& ActionFactoryPlayerFireLV1::type() const
  {
    return TypeName;
  }

  Action* ActionFactoryPlayerFireLV1::createInstance( Actor* owner, ActionDesc* desc )
  {
    ActionPlayerFireLV1* action = new ActionPlayerFireLV1(owner, desc);
    return action;
  }

  ActionDesc* ActionFactoryPlayerFireLV1::load( rapidxml::xml_node<>* xmlNode, const String& filename )
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