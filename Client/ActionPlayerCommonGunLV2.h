#ifndef ACTIONPLAYERCOMMONGUNLV2_H
#define ACTIONPLAYERCOMMONGUNLV2_H
#include "Action.h"
#include "ISceneNode2D.h"

namespace Ogre
{
  
  struct IAnimation2D;
  class ActorPlayer;

  class ActionPlayerCommonGunLV2 : public Action
  {
  public:
    ActionPlayerCommonGunLV2(Actor* owner, ActionDesc* desc);
    ~ActionPlayerCommonGunLV2();

    virtual void  initailze();
    virtual const String& type() const;
    virtual void  begin();
    virtual void  end();
    virtual void  update(Real timeLapse);
	virtual void setProperty( const String& name, const Any& val );
    IAnimation2D* getBody();
  private:
    ActorPlayer* mActorPlayer;
    IAnimation2D* mActorPlayerBody;
	ISceneNode2D* mSceneNodePaoGuan;
    Real mRot;
  };

  class ActionFactoryPlayerCommonGunLV2:public ActionFactory
  {
  public:
    ActionFactoryPlayerCommonGunLV2();
    virtual ~ActionFactoryPlayerCommonGunLV2();

    virtual const String& type() const;
    virtual Action* createInstance( Actor* owner, ActionDesc* desc );
    virtual ActionDesc* load( rapidxml::xml_node<>* xmlNode, const String& filename );
    static const String TypeName;
  };
}
#endif