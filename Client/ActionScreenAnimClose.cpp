#include "SystemPrerequisites.h"
#include "ActionScreenAnimClose.h"
#include "IAnimation2D.h"
#include "ISceneNode2D.h"
#include "ISprite2D.h"
#include "ISprite2DManager.h"
#include "IAnimation2DManager.h"
#include "ActorBackground.h"

namespace Ogre
{
	struct ActionDescScreenAnimClose:public ActionDesc
	{
		String		id;
		int			layer;
	};

	ActionScreenAnimClose::ActionScreenAnimClose(Actor* owner, ActionDesc* desc)
		:Action(desc, owner)
		, mActorBackground(NULL)
		, mId("")
		, mLayer(0)
		, mBackMapSprite2D(NULL)
		, mScreenCloseBody(NULL)
	{
		mActorBackground = static_cast<ActorBackground*>(owner);
		ActionDescScreenAnimClose *actionDesc = static_cast<ActionDescScreenAnimClose*>(desc);
		mId = actionDesc->id;
		mLayer = actionDesc->layer;
	}

	ActionScreenAnimClose::~ActionScreenAnimClose()
	{
		mScreenCloseBody->destroy();
		mScreenCloseBody = NULL;
	}

	void ActionScreenAnimClose::initailze()
	{

	}

	const String& ActionScreenAnimClose::type() const
	{
		return ActionFactoryScreenAnimClose::TypeName;
	}

	void ActionScreenAnimClose::begin()
	{
		Action::begin();
		mOwner->getSceneNode()->detachObject(mScreenCloseBody);
		mScreenCloseBody = gEnv->mAnimationMgr->create(mId);
		mScreenCloseBody->setRenderQueue(mLayer);
		mOwner->getSceneNode()->setPositionRelative(0.5f, 0.5f);
		mOwner->getSceneNode()->attachObject(mScreenCloseBody);
	}

	void ActionScreenAnimClose::end()
	{
		mOwner->getSceneNode()->detachObject(mScreenCloseBody);
		Action::end();
	}

	void ActionScreenAnimClose::update(Real timeLapse)
	{
		// ÇÐ»»µ½µÈ´ý
		if ((mScreenCloseBody->getCurFrameIndex()+1) >= mScreenCloseBody->getFrameCount())
		{
			mOwner->changeActionTo("ScreenAnimWait");
		}
	}

	IAnimation2D* ActionScreenAnimClose::getBody()
	{
		return mScreenCloseBody;
	}

	const String ActionFactoryScreenAnimClose::TypeName = "ScreenAnimClose";
	ActionFactoryScreenAnimClose::ActionFactoryScreenAnimClose()
	{

	}

	ActionFactoryScreenAnimClose::~ActionFactoryScreenAnimClose()
	{

	}

	const String& ActionFactoryScreenAnimClose::type() const
	{
		return TypeName;
	}

	Action* ActionFactoryScreenAnimClose::createInstance( Actor* owner, ActionDesc* desc )
	{
		ActionScreenAnimClose* action = new ActionScreenAnimClose(owner, desc);
		return action;
	}

	ActionDesc* ActionFactoryScreenAnimClose::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActionDescScreenAnimClose* actionDesc = new ActionDescScreenAnimClose;

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