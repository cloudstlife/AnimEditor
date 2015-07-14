#ifndef ACTIONGOLDCOINGET_H
#define ACTIONGOLDCOINGET_H
#include "Action.h"

namespace Ogre
{
  class ActorGoldCoin;
  struct IAnimation2D;
  class	 ActorPlayer;
  class  NormalActorFish;

  class ActionGoldCoinGet:public Action
  {
  public:
    ActionGoldCoinGet(Actor* owner, ActionDesc* desc);
    ~ActionGoldCoinGet();

    virtual void initailze();
    virtual const String& type() const;
    virtual void begin();
    virtual void end();
    virtual void update(Real timelapse);
    IAnimation2D* getBody();
	void		 setActorPlayer(Actor* val);
	void		 setNormalActorFish(Actor* val);

  private:
    ActorGoldCoin*		mActorGoldCoin;
    IAnimation2D*		mGoldCoinBody;
    Real				mTimes;
	Real				mSpeed;
	Real				mWaitTimes;
	Vector2				mOffsetPos;
	Vector3				mDestPos;
	Vector3				mDirOrignal;
	bool				mbUpdatePlayerPoint;
	ActorPlayer*		mActorPlayer;
	NormalActorFish*	mNormalActorFish;
  };

  class ActionFactoryGoldCoin:public ActionFactory
  {
  public:
    ActionFactoryGoldCoin();
    virtual ~ActionFactoryGoldCoin();
    virtual const String& type() const;
    virtual Action*  createInstance( Actor* owner, ActionDesc* desc );
    virtual  ActionDesc*	load( rapidxml::xml_node<>* xmlNode, const String& filename );

    static const	String	TypeName;
  };
}
#endif