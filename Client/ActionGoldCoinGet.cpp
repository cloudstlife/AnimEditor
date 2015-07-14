#include "SystemPrerequisites.h"
#include "ActionGoldCoinGet.h"
#include "ISprite2D.h"
#include "IAnimation2D.h"
#include "ISprite2DManager.h"
#include "IAnimation2DManager.h"
#include "ISceneNode2D.h"
#include "ActorGoldCoin.h"
#include "ActorPlayer.h"
#include "NormalActorFish.h"


namespace Ogre
{
	struct ActionDescGoldCoin: public ActionDesc
	{
		AnimElement  body;
		Real		 waitTime;
	};

	ActionGoldCoinGet::ActionGoldCoinGet(Actor* owner, ActionDesc* desc)
	:Action(desc, owner)
	, mActorGoldCoin(NULL)
	, mGoldCoinBody(NULL)
	, mTimes(0.0f)
	, mSpeed(0.0f)
	, mOffsetPos(Vector2::ZERO)
	, mWaitTimes(0.0f)
	, mDestPos(Vector3::ZERO)
	, mDirOrignal(Vector3::ZERO)
	, mbUpdatePlayerPoint(false)
	, mActorPlayer(NULL)
	, mNormalActorFish(NULL)
	{
		mActorGoldCoin = static_cast<ActorGoldCoin*>(owner);
		ActionDescGoldCoin* actionDesc = static_cast<ActionDescGoldCoin*>(desc);
		mGoldCoinBody = gEnv->mAnimationMgr->create(actionDesc->body.id);
		mGoldCoinBody->setRenderQueue(actionDesc->body.layer);
		mSpeed = actionDesc->body.speed;
		mOffsetPos = actionDesc->body.pos;
		mWaitTimes = actionDesc->waitTime;
	}

	ActionGoldCoinGet::~ActionGoldCoinGet()
	{
		mGoldCoinBody->destroy();
		mGoldCoinBody = 0;
	}

	void ActionGoldCoinGet::initailze()
	{
	}

	const String& ActionGoldCoinGet::type() const
	{
		return ActionFactoryGoldCoin::TypeName;
	}

	void ActionGoldCoinGet::begin()
	{
		Action::begin();
		mOwner->getSceneNode()->attachObject( mGoldCoinBody );
		// 根据偏移位置显示
		mDirOrignal = mOwner->getSceneNode()->getPosition();
		mDirOrignal.y += mOffsetPos.y;
		mOwner->getSceneNode()->setPosition(mDirOrignal.z, mDirOrignal.y);
		mActorPlayer = static_cast<ActorPlayer*>(mActorGoldCoin->getActorPlayer());
		ActorGoldCoin* pGoldCoin = static_cast<ActorGoldCoin*>(mOwner);

		mbUpdatePlayerPoint = true;
	}

	void ActionGoldCoinGet::end()
	{
		mOwner->getSceneNode()->detachObject(mGoldCoinBody);
		Action::end();
	}

	void ActionGoldCoinGet::update(Real timelapse)
	{
		if(mDestPos == Vector3::ZERO)
		{
			if (mActorGoldCoin->getActorPlayer())
			{
				// 目标点
				mDestPos = mActorGoldCoin->getActorPlayer()->getSceneNode()->getDerivedPosition();
			}
		}

		Vector3 v3Dir = Vector3::ZERO;
		if (mDestPos != Vector3::ZERO)
		{
			// 计算向量
			v3Dir = mDestPos - mDirOrignal;
		}
		mTimes += timelapse;

		ActorPlayer* pActorPlayer = static_cast<ActorPlayer*>(mActorGoldCoin->getActorPlayer());
		int iOdds = mActorGoldCoin->getFishOdds();
		int	iEnergy = mActorGoldCoin->getEnergy();
		if (mWaitTimes< mTimes)
		{
			//  金币停留一段时间再移动
			Vector2 tran;
			// 单位化
			tran.x = v3Dir.z/(sqrt(v3Dir.z*v3Dir.z+v3Dir.y*v3Dir.y));
			tran.y = v3Dir.y/(sqrt(v3Dir.z*v3Dir.z+v3Dir.y*v3Dir.y));
			tran = tran * (timelapse/1.0f*mSpeed);
			mOwner->getSceneNode()->translate( tran );
			if (mOwner->getSceneNode()->getPosition().z< mDestPos.z
				|| mOwner->getSceneNode()->getPosition().y< mDestPos.y)
			{
				// player剩余分数加分
				if (mbUpdatePlayerPoint)
				{
					mActorPlayer = static_cast<ActorPlayer*>(mActorGoldCoin->getActorPlayer());
					if (pActorPlayer)
					{
						pActorPlayer->addCurrentPointByFish(iOdds, iEnergy);
						// 根据营业模式执行后续操作
						pActorPlayer->businessDecFen();
					}
					mbUpdatePlayerPoint = false;
				}
				mOwner->getSceneNode()->detachObject(mGoldCoinBody);
			}
			mWaitTimes = 0;
		}
	}

	IAnimation2D* ActionGoldCoinGet::getBody()
	{
		return mGoldCoinBody;
	}

	const String ActionFactoryGoldCoin::TypeName = "Get";
	ActionFactoryGoldCoin::ActionFactoryGoldCoin()
	{

	}

	ActionFactoryGoldCoin::~ActionFactoryGoldCoin()
	{
	}

	const String& ActionFactoryGoldCoin::type() const
	{
		return TypeName;
	}

	Action* ActionFactoryGoldCoin::createInstance( Actor* owner, ActionDesc* desc )
	{
		ActionGoldCoinGet *action = new ActionGoldCoinGet(owner, desc);
		return action;
	}

	ActionDesc*	ActionFactoryGoldCoin::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActionDescGoldCoin* actionDesc = new ActionDescGoldCoin;

		_loadBaseActionDesc( actionDesc, xmlNode, filename );

		xml_node<>* xmlNodeBody = xmlNode->first_node( "body" );
		if ( xmlNodeBody == 0 )
		{
			EXCEPTEX( "coin actor. move action. need body label. filename: " << filename );
		}
		nodeAttr = xmlNodeBody->first_attribute( "animId" );
		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "coin actor. move action. body need animId label. filename: " << filename );
		}
		actionDesc->body.id = nodeAttr->value();
		nodeAttr = xmlNodeBody->first_attribute( "layer" );
		if ( nodeAttr == 0 )
		{
			EXCEPTEX( "coin actor. move action. body need layer label. filename: " << filename );
		}
		actionDesc->body.layer = StringConverter::parseInt( nodeAttr->value() );

		// speed移动速度
		xml_node<>* xmlNodeSpeed = xmlNode->first_node("speed");
		if (!xmlNodeSpeed)
		{
			EXCEPTEX( "coin actor. move action. need body label. filename: " << filename );
		}
		nodeAttr = xmlNodeSpeed->first_attribute("val");
		if (!nodeAttr)
		{
			EXCEPTEX( "coin actor. move action. body need speed label. filename: " << filename );
		}
		actionDesc->body.speed = StringConverter::parseReal(nodeAttr->value());

		// offset 出现初始位移
		xml_node<>* xmlNodeOffset = xmlNode->first_node("default");
		if (!xmlNodeOffset)
		{
			EXCEPTEX( "coin actor. fire action. body need default label. filename: " << filename );
		}
		nodeAttr = xmlNodeOffset->first_attribute("offset");
		if (!nodeAttr)
		{
			EXCEPTEX( "coin actor. fire action. body need offset label. filename: " << filename );
		}
		actionDesc->body.pos = StringConverter::parseVector2(nodeAttr->value());
		
		// time 金币弹出后的停留时间
		xml_node<>* xmlNodeWait = xmlNode->first_node("Wait");
		if (!xmlNodeWait)
		{
			EXCEPTEX( "coin actor. fire action. body need default label. filename: " << filename );
		}
		nodeAttr = xmlNodeWait->first_attribute("time");
		if (!nodeAttr)
		{
			EXCEPTEX( "coin actor. fire action. body need offset label. filename: " << filename );
		}
		actionDesc->waitTime = StringConverter::parseReal(nodeAttr->value());
		return actionDesc;
	}
}