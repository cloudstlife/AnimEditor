#include "SystemPrerequisites.h"
#include "ActionScreenAnimWait.h"
#include "IAnimation2D.h"
#include "ISceneNode2D.h"
#include "ISprite2D.h"
#include "ISprite2DManager.h"
#include "IAnimation2DManager.h"
#include "ActorBackground.h"

namespace Ogre
{
	struct ActionDescScreenAnimWait:public ActionDesc
	{
		String		id;
		int			layer;
	};

	ActionScreenAnimWait::ActionScreenAnimWait(Actor* owner, ActionDesc* desc)
		:Action(desc, owner)
		, mActorBackground(NULL)
		, mId("")
		, mLayer(0)
		, mScreenWaitBody(NULL)
	{
		mActorBackground = static_cast<ActorBackground*>(owner);
		ActionDescScreenAnimWait *actionDesc = static_cast<ActionDescScreenAnimWait*>(desc);
		mId = actionDesc->id;
		mLayer = actionDesc->layer;
	}

	ActionScreenAnimWait::~ActionScreenAnimWait()
	{
		mBackMapSprite2D->destroy();
		mBackMapSprite2D = NULL;
		mScreenWaitBody->destroy();
		mScreenWaitBody = NULL;
	}

	void ActionScreenAnimWait::initailze()
	{

	}

	const String& ActionScreenAnimWait::type() const
	{
		return ActionFactoryScreenAnimWait::TypeName;
	}

	void ActionScreenAnimWait::begin()
	{
		Action::begin();
		mOwner->getSceneNode()->detachObject(mScreenWaitBody);
		mScreenWaitBody = gEnv->mAnimationMgr->create(mId);
		mScreenWaitBody->setRenderQueue(mLayer);
		mOwner->getSceneNode()->setPositionRelative(0.5f, 0.5f);
		mOwner->getSceneNode()->attachObject(mScreenWaitBody);
	}

	void ActionScreenAnimWait::end()
	{
		mOwner->getSceneNode()->detachObject(mScreenWaitBody);
		Action::end();
	}

	void ActionScreenAnimWait::update(Real timeLapse)
	{
		// 设置地图背景(目前是动画一播放完就切换)
		mActorBackground->setBackgroundImage();
		if ((mScreenWaitBody->getCurFrameIndex()+1)>= mScreenWaitBody->getFrameCount())
		{
			// 切换打开
			mOwner->changeActionTo("ScreenAnimOpen");
		}
	}

	const String ActionFactoryScreenAnimWait::TypeName = "ScreenAnimWait";
	ActionFactoryScreenAnimWait::ActionFactoryScreenAnimWait()
	{

	}

	ActionFactoryScreenAnimWait::~ActionFactoryScreenAnimWait()
	{

	}

	const String& ActionFactoryScreenAnimWait::type() const
	{
		return TypeName;
	}

	Action* ActionFactoryScreenAnimWait::createInstance( Actor* owner, ActionDesc* desc )
	{
		ActionScreenAnimWait* action = new ActionScreenAnimWait(owner, desc);
		return action;
	}

	ActionDesc* ActionFactoryScreenAnimWait::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActionDescScreenAnimWait* actionDesc = new ActionDescScreenAnimWait;

		_loadBaseActionDesc( actionDesc, xmlNode, filename );

		xml_node<>* xmlNodeBody = xmlNode->first_node("body");
		if (!xmlNodeBody)
		{
			EXCEPTEX( "background actor. Property action. filename: " << filename );
		}
		nodeAttr = xmlNodeBody->first_attribute("animId");
		if (!nodeAttr)
		{
			EXCEPTEX( "background actor. Property action. body need id label. filename: " << filename );
		}
		actionDesc->id = nodeAttr->value();

		nodeAttr = xmlNodeBody->first_attribute("layer");
		if (!nodeAttr)
		{
			EXCEPTEX( "background actor. Property action. body need layer label. filename: " << filename );
		}
		actionDesc->layer = StringConverter::parseInt(nodeAttr->value());
		return actionDesc;
	}
}