#include "SystemPrerequisites.h"
#include "ActionFishDied.h"
#include "ISprite2D.h"
#include "IAnimation2D.h"
#include "ISprite2DManager.h"
#include "IAnimation2DManager.h"
#include "ISceneNode2D.h"
#include "IScene.h"
#include "NormalActorFish.h"
#include "ActorGoldCoin.h"
#include "ActorPlayer.h"
#include "ILabelNumber2D.h"
#include "ILabelNumber2DManager.h"
#include "Navigation2D.h"

namespace Ogre
{	
	struct ActionDescFishDied : public ActionDesc
	{
		ActionDescFishDied()
			: bombId( -1 )
		{

		}
		AnimElement		body;
		int				bombId;

		ShowScore		showScore;
	};

	//---
	ActionFishDied::ActionFishDied( Actor* owner, ActionDesc* desc )
	: Action( desc, owner )
	, mShowScore2DNode(NULL)
	, mShowScore2D(NULL)
	{
		mActorFish = static_cast< NormalActorFish* >( owner );

		ActionDescFishDied* actionDesc = static_cast< ActionDescFishDied* >( desc );

		mFishBody = gEnv->mAnimationMgr->create( actionDesc->body.id );
		mFishBody->setRenderQueue( actionDesc->body.layer );

		mShowScore.id = actionDesc->showScore.id;
		mShowScore.layer = actionDesc->showScore.layer;
		mShowScore.offsetPos = actionDesc->showScore.offsetPos;
		mShowScore2D = gEnv->mLabelNumberMgr->create( mShowScore.id );
	}

	ActionFishDied::~ActionFishDied()
	{
		mFishBody->destroy();
		mFishBody = 0;
	}

	void	ActionFishDied::initailze()
	{

	}

	const String&	ActionFishDied::type() const
	{
		return ActionFactoryFishDied::TypeName;
	}

	void	ActionFishDied::begin()
	{
		Action::begin();
		mOwner->getSceneNode()->attachObject( mFishBody );
		mActorFish->enabelPhysics( false );

		// 创建金币
		ISceneNode2D* nodeGoldCoins = mScene->getRootSceneNode()->createChild();
		nodeGoldCoins->setPosition(mActorFish->getSceneNode()->getDerivedPosition().z, 
		  mActorFish->getSceneNode()->getDerivedPosition().y);
		ActorGoldCoin* pGoldCoin = static_cast<ActorGoldCoin*>(mScene->createActor("GoldCoin", nodeGoldCoins));
		pGoldCoin->setActorPlayer(mActorFish->getActorPlayer());
		pGoldCoin->setFishOdds(mActorFish->getOdds());
		pGoldCoin->setEnergy(mActorFish->getEnergy());

		// 创建打中后押注(当前减少，有时分数不足押分则直接用完)分数
		ActorPlayer* pActorPlayer = static_cast<ActorPlayer*>(mActorFish->getActorPlayer());
		// 分数显示方向
		mShowScore2D->setNumber(pActorPlayer->getCurrentDecPoint()*mActorFish->getOdds());
		mShowScore2D->setRenderQueue(mShowScore.layer);
		mShowScore2DNode = mScene->getRootSceneNode()->createChild();
		mShowScore2DNode->setRotateX(pActorPlayer->getSceneNode()->getDerivedRotateX());
		mShowScore2DNode->setPosition(nodeGoldCoins->getDerivedPosition().z + mShowScore.offsetPos.x,
			nodeGoldCoins->getDerivedPosition().y + mShowScore.offsetPos.y);
		mShowScore2DNode->attachObject(mShowScore2D);

		// 获取导航并关闭
		Navigation2D *nav = mOwner->getSceneNode()->getNavigation();
		if (nav)
		{
			nav->stop();
		}
	}

	void	ActionFishDied::end()
	{
		mOwner->getSceneNode()->detachObject( mFishBody );
		if (mShowScore2DNode)
		{
			mShowScore2DNode->detachAllObject();
		}
		Action::end();
	}

	void	ActionFishDied::update( Real timelapse )
	{
		if ( mLifeTimeLapse >= mLifeTime )
		{
			mOwner->valid();
		}
		mLifeTimeLapse += timelapse;
	}

	const String ActionFactoryFishDied::TypeName = "Died";
	ActionFactoryFishDied::ActionFactoryFishDied()
	{

	}

	ActionFactoryFishDied::~ActionFactoryFishDied()
	{

	}

	const String&	ActionFactoryFishDied::type() const
	{

		return TypeName;
	}

	Action*	ActionFactoryFishDied::createInstance( Actor* owner, ActionDesc* desc )
	{
		ActionFishDied* action = new ActionFishDied( owner, desc );
		
		return action;
	}

	ActionDesc*	ActionFactoryFishDied::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActionDescFishDied* actionDesc = new ActionDescFishDied;

		_loadBaseActionDesc( actionDesc, xmlNode, filename );

		xml_node<>* xmlNodeBody = xmlNode->first_node( "body" );
		if ( xmlNodeBody == 0 )
		{
			EXCEPTEX( "fish actor. move action. need body label. filename: " << filename );
		}

		nodeAttr = xmlNodeBody->first_attribute( "animId" );
		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "fish actor. move action. body need animId label. filename: " << filename );
		}

		actionDesc->body.id = nodeAttr->value();

		nodeAttr = xmlNodeBody->first_attribute( "layer" );
		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "fish actor. move action. body need layer label. filename: " << filename );
		}
		actionDesc->body.layer = StringConverter::parseInt( nodeAttr->value() );

		//showScore
		xml_node<>* xmlNodeShowScore = xmlNode->first_node("ShowScore");
		if (!xmlNodeShowScore)
		{
			EXCEPTEX( "fish actor. ShowScore. filename: " << filename );
		}
		nodeAttr = xmlNodeShowScore->first_attribute("id");
		if (!nodeAttr)
		{
			EXCEPTEX( "fish actor. id. filename: " << filename );
		}
		actionDesc->showScore.id = nodeAttr->value();
		nodeAttr = xmlNodeShowScore->first_attribute("layer");
		if (!nodeAttr)
		{
			EXCEPTEX( "fish actor. layer. filename: " << filename );
		}
		actionDesc->showScore.layer = StringConverter::parseInt(nodeAttr->value());
		nodeAttr = xmlNodeShowScore->first_attribute("offsetPos");
		if (!nodeAttr)
		{
			EXCEPTEX( "fish actor. layer. filename: " << filename );
		}
		actionDesc->showScore.offsetPos = StringConverter::parseVector2(nodeAttr->value());
		//nodeAttr = xmlNodeShowScore->first_attribute("showTime")
		
		return actionDesc;
	}

}