#ifndef ACTIONPLAYERFIRELV2_H
#define ACTIONPLAYERFIRELV2_H
#include "Action.h"
#include "ISceneNode2D.h"

namespace Ogre
{
  class ActorPlayer;
  struct IAnimation2D;

  struct BulletInfoLV2
  {
	  String				bulletId;
  };

  struct BmobInfoLV2
  {
	  String				bmobId;
  };

  class ActionPlayerFireLV2:public Action
  {
  public:
    ActionPlayerFireLV2(Actor* owner, ActionDesc* desc);
    ~ActionPlayerFireLV2();

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
	IAnimation2D*	mActorBmobBody;
    ISceneNode2D*	mSceneNodePaoGuan;

	Vector3				mBulletPosOffset;
	Vector3 			mBulletPosOffsetOrignal;
	Vector3 			mDir;
	Vector3 			mDirOrignal;
	BulletInfoLV2		mBulletInfo;
	BmobInfoLV2			mBmobInfo;
  };

  class ActionFactoryPlayerFireLV2:public ActionFactory
  {
  public:
    ActionFactoryPlayerFireLV2();
    virtual ~ActionFactoryPlayerFireLV2();

    virtual const String& type() const;
    virtual Action* createInstance( Actor* owner, ActionDesc* desc );
    virtual ActionDesc* load( rapidxml::xml_node<>* xmlNode, const String& filename );
    static const String TypeName;
  };
}
#endif