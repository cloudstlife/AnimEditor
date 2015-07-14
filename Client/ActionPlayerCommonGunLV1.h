#ifndef ACTIONPLAYERCOMMONGUNLV1_H
#define ACTIONPLAYERCOMMONGUNLV1_H
#include "Action.h"
#include "ISceneNode2D.h"

namespace Ogre
{
  
  struct IAnimation2D;
  class ActorPlayer;

  class ActionPlayerCommonGunLV1 : public Action
  {
  public:
    ActionPlayerCommonGunLV1(Actor* owner, ActionDesc* desc);
    ~ActionPlayerCommonGunLV1();

    virtual void  initailze();
    virtual const String& type() const;
    virtual void  begin();
    virtual void  end();
    virtual void  update(Real timeLapse);
	virtual void setProperty( const String& name, const Any& val );
    IAnimation2D* getBody();
  private:
    ActorPlayer*	mActorPlayer;
    IAnimation2D*	mActorPlayerBody;
	ISceneNode2D*	mSceneNodePaoGuan;
    Real			mRot;
  };

  class ActionFactoryPlayerCommonGunLV1:public ActionFactory
  {
  public:
    ActionFactoryPlayerCommonGunLV1();
    virtual ~ActionFactoryPlayerCommonGunLV1();

    virtual const String& type() const;
    virtual Action* createInstance( Actor* owner, ActionDesc* desc );
    virtual ActionDesc* load( rapidxml::xml_node<>* xmlNode, const String& filename );
    static const String TypeName;
  };
}
#endif