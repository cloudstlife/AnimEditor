#ifndef ACTIONPLAYERFIRELV1_H
#define ACTIONPLAYERFIRELV1_H
#include "Action.h"
#include "ISceneNode2D.h"

namespace Ogre
{
  class ActorPlayer;
  struct IAnimation2D;

  struct BulletInfoLV1
  {
	  String				bulletId;
  };

  struct BmobInfoLV1
  {
	  String				bmobId;
  };

  class ActionPlayerFireLV1:public Action
  {
  public:
    ActionPlayerFireLV1(Actor* owner, ActionDesc* desc);
    ~ActionPlayerFireLV1();

    virtual void  initailze();
    virtual const String& type() const;
    virtual void  begin();
    virtual void  end();
    virtual void  update(Real timeLapse);
	virtual void  setProperty( const String& name, const Any& val );
    IAnimation2D* getBody();

  private:
    ActorPlayer*		mActorPlayer;
    IAnimation2D*		mActorPlayerBody;
	IAnimation2D*		mActorBmobBody;
    ISceneNode2D*		mSceneNodePaoGuan;

	Vector3				mBulletPosOffset;
	Vector3				mBulletPosOffsetOrignal;
	Vector3				mDir;
	Vector3				mDirOrignal;
	BulletInfoLV1		mBulletInfo;
	BmobInfoLV1			mBmobInfo;
  };

  class ActionFactoryPlayerFireLV1:public ActionFactory
  {
  public:
    ActionFactoryPlayerFireLV1();
    virtual ~ActionFactoryPlayerFireLV1();

    virtual const String& type() const;
    virtual Action* createInstance( Actor* owner, ActionDesc* desc );
    virtual ActionDesc* load( rapidxml::xml_node<>* xmlNode, const String& filename );
    static const String TypeName;
  };
}
#endif