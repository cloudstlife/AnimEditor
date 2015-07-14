#include "SystemPrerequisites.h"
#include "ActionPlayerCommonGunLV2.h"
#include "ISprite2D.h"
#include "IAnimation2D.h"
#include "ISprite2DManager.h"
#include "IAnimation2DManager.h"
#include "ISceneNode2D.h"
#include "ActorPlayer.h"

namespace Ogre
{
  struct ActionDescPlayerCommonGunLV2: public ActionDesc 
  {
    AnimElement body;
    
  };

  ActionPlayerCommonGunLV2::ActionPlayerCommonGunLV2(Actor* owner, ActionDesc* desc)
    :Action(desc, owner)
	, mRot(0)
	, mSceneNodePaoGuan( 0 )
  {
    mActorPlayer = static_cast<ActorPlayer*>(owner);
    ActionDescPlayerCommonGunLV2 *actionDesc = static_cast<ActionDescPlayerCommonGunLV2*>(desc);
    mActorPlayerBody = gEnv->mAnimationMgr->create(actionDesc->body.id);
    mActorPlayerBody->setRenderQueue(actionDesc->body.layer);
    
  }

  ActionPlayerCommonGunLV2::~ActionPlayerCommonGunLV2()
  {
    mActorPlayerBody->destroy();
    mActorPlayerBody = 0;
  }

  void ActionPlayerCommonGunLV2::initailze()
  {

  }

  const String& ActionPlayerCommonGunLV2::type() const
  {
    return ActionFactoryPlayerCommonGunLV2::TypeName;
  }

  void ActionPlayerCommonGunLV2::begin()
  {
    Action::begin();
	if (mSceneNodePaoGuan)
	{
		mSceneNodePaoGuan->attachObject(mActorPlayerBody);
	}
  }

  void ActionPlayerCommonGunLV2::end()
  {
	if (mSceneNodePaoGuan)
	{
		mSceneNodePaoGuan->detachObject(mActorPlayerBody);
	}
    Action::end();
  }

  void ActionPlayerCommonGunLV2::update(Real timeLapse)
  {
	//mSceneNodePaoGuan->setRotateX(mRot);
  }

  void ActionPlayerCommonGunLV2::setProperty( const String& name, const Any& val )
  {
	  if ( name == "SceneNodePaoGuan" )
	  {
			mSceneNodePaoGuan = val.get<ISceneNode2D*>();
	  }
	  
  }

  IAnimation2D* ActionPlayerCommonGunLV2::getBody()
  {
    return mActorPlayerBody;
  }

  const String ActionFactoryPlayerCommonGunLV2::TypeName = "Gun_CommonLV2";
  ActionFactoryPlayerCommonGunLV2::ActionFactoryPlayerCommonGunLV2()
  {

  }

  ActionFactoryPlayerCommonGunLV2::~ActionFactoryPlayerCommonGunLV2()
  {

  }

  const String& ActionFactoryPlayerCommonGunLV2::type() const
  {
    return TypeName;
  }

  Action* ActionFactoryPlayerCommonGunLV2::createInstance( Actor* owner, ActionDesc* desc )
  {
    ActionPlayerCommonGunLV2* action = new ActionPlayerCommonGunLV2(owner, desc);
    return action;
  }

  ActionDesc* ActionFactoryPlayerCommonGunLV2::load( rapidxml::xml_node<>* xmlNode, const String& filename )
  {
    using namespace rapidxml;

    xml_attribute<>* nodeAttr = 0;

    ActionDescPlayerCommonGunLV2* actionDesc = new ActionDescPlayerCommonGunLV2;

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