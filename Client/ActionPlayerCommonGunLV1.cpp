#include "SystemPrerequisites.h"
#include "ActionPlayerCommonGunLV1.h"
#include "ISprite2D.h"
#include "IAnimation2D.h"
#include "ISprite2DManager.h"
#include "IAnimation2DManager.h"
#include "ISceneNode2D.h"
#include "ActorPlayer.h"

namespace Ogre
{
  struct ActionDescPlayerCommonGun: public ActionDesc 
  {
    AnimElement body;
    
  };

  ActionPlayerCommonGunLV1::ActionPlayerCommonGunLV1(Actor* owner, ActionDesc* desc)
    :Action(desc, owner)
	, mRot(0)
	, mSceneNodePaoGuan( 0 )
  {
    mActorPlayer = static_cast<ActorPlayer*>(owner);
    ActionDescPlayerCommonGun *actionDesc = static_cast<ActionDescPlayerCommonGun*>(desc);
    mActorPlayerBody = gEnv->mAnimationMgr->create(actionDesc->body.id);
    mActorPlayerBody->setRenderQueue(actionDesc->body.layer);
    
  }

  ActionPlayerCommonGunLV1::~ActionPlayerCommonGunLV1()
  {
    mActorPlayerBody->destroy();
    mActorPlayerBody = 0;
  }

  void ActionPlayerCommonGunLV1::initailze()
  {

  }

  const String& ActionPlayerCommonGunLV1::type() const
  {
    return ActionFactoryPlayerCommonGunLV1::TypeName;
  }

  void ActionPlayerCommonGunLV1::begin()
  {
    Action::begin();
	if (mSceneNodePaoGuan)
	{
		mSceneNodePaoGuan->attachObject(mActorPlayerBody);
	}
  }

  void ActionPlayerCommonGunLV1::end()
  {
	if (mSceneNodePaoGuan)
	{
		mSceneNodePaoGuan->detachObject(mActorPlayerBody);
	}
    Action::end();
  }

  void ActionPlayerCommonGunLV1::update(Real timeLapse)
  {
	//mSceneNodePaoGuan->setRotateX(mRot);
  }

  void ActionPlayerCommonGunLV1::setProperty( const String& name, const Any& val )
  {
	  if ( name == "SceneNodePaoGuan" )
	  {
			mSceneNodePaoGuan = val.get<ISceneNode2D*>();
	  }
  }

  IAnimation2D* ActionPlayerCommonGunLV1::getBody()
  {
    return mActorPlayerBody;
  }

  const String ActionFactoryPlayerCommonGunLV1::TypeName = "Gun_CommonLV1";
  ActionFactoryPlayerCommonGunLV1::ActionFactoryPlayerCommonGunLV1()
  {

  }

  ActionFactoryPlayerCommonGunLV1::~ActionFactoryPlayerCommonGunLV1()
  {

  }

  const String& ActionFactoryPlayerCommonGunLV1::type() const
  {
    return TypeName;
  }

  Action* ActionFactoryPlayerCommonGunLV1::createInstance( Actor* owner, ActionDesc* desc )
  {
    ActionPlayerCommonGunLV1* action = new ActionPlayerCommonGunLV1(owner, desc);
    return action;
  }

  ActionDesc* ActionFactoryPlayerCommonGunLV1::load( rapidxml::xml_node<>* xmlNode, const String& filename )
  {
    using namespace rapidxml;

    xml_attribute<>* nodeAttr = 0;

    ActionDescPlayerCommonGun* actionDesc = new ActionDescPlayerCommonGun;

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
    actionDesc->body.layer = StringConverter::parseInt( nodeAttr->value() );

    
    return actionDesc;
  }
}