#ifndef ACTORGOLDCOIN_H
#define ACTORGOLDCOIN_H

#include "Actor.h"

namespace Ogre
{
  class ActorGoldCoin:public Actor
  {
  public:
    ActorGoldCoin(ActorDesc* desc, ISceneNode2D* node, IScene* scene);
    virtual ~ActorGoldCoin();

    virtual void			initailze();
    virtual void			updateLogic( Real timeLapse );
    virtual const String&	type() const;
    virtual void			setProperty(const String& name, const Any& val );
	void					setActorPlayer(Actor* actor);
	Actor*					getActorPlayer();
	void					setFishOdds(int val);
	int						getFishOdds();
	void					setEnergy(int val);
	int						getEnergy();

  public:
    DYNAMIC_DECLARE( ActorGoldCoin );
  private:
	  Actor*		mPlayer;
	  int			mOdds;
	  int			mEnergy;
  };

  class ActorFactoryGoldCoin : public ActorFactory
  {
  public:
    ActorFactoryGoldCoin();
    virtual ~ActorFactoryGoldCoin();
    virtual const String& type() const;
    virtual Actor* createInstance( ActorDesc* actorDesc, ISceneNode2D* node, IScene* scene, const String& name = "" );
    virtual ActorDesc* load( rapidxml::xml_node<>* xmlNode, const String& filename );
    static const String TypeName;
  };
}
#endif