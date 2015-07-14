#include "SystemPrerequisites.h"
#include "ActionScreenAnimOpen.h"
#include "IAnimation2D.h"
#include "ISceneNode2D.h"
#include "ISprite2D.h"
#include "ISprite2DManager.h"
#include "IAnimation2DManager.h"
#include "ActorBackground.h"

namespace Ogre
{
	struct ActionDescScreenAnimOpen:public ActionDesc
	{
		String		id;
		int			layer;
	};

	ActionScreenAnimOpen::ActionScreenAnimOpen(Actor* owner, ActionDesc* desc)
		:Action(desc, owner)
		, mActorBackground(NULL)
		, mId("")
		, mLayer(0)
		, mBackMapBody(NULL)
	{
		mActorBackground = static_cast<ActorBackground*>(owner);
		ActionDescScreenAnimOpen *actionDesc = static_cast<ActionDescScreenAnimOpen*>(desc);
		mId = actionDesc->id;
		mLayer = actionDesc->layer;
	}

	ActionScreenAnimOpen::~ActionScreenAnimOpen()
	{
		mBackMapBody->destroy();
		mBackMapBody = NULL;
		mScreenOpenBody->destroy();
		mScreenOpenBody = NULL;
	}

	void ActionScreenAnimOpen::initailze()
	{

	}

	const String& ActionScreenAnimOpen::type() const
	{
		return ActionFactoryScreenAnimOpen::TypeName;
	}

	void ActionScreenAnimOpen::begin()
	{
		Action::begin();
		mOwner->getSceneNode()->detachObject(mScreenOpenBody);
		mScreenOpenBody = gEnv->mAnimationMgr->create(mId);
		mScreenOpenBody->setRenderQueue(mLayer);
		mOwner->getSceneNode()->setPositionRelative(0.5f, 0.5f);
		mOwner->getSceneNode()->attachObject(mScreenOpenBody);
	}

	void ActionScreenAnimOpen::end()
	{
		mOwner->getSceneNode()->detachObject(mScreenOpenBody);
		Action::end();
	}

	void ActionScreenAnimOpen::update(Real timeLapse)
	{
		//// ÇÐ»»µ½¹Ø±Õ
		//if (mScreenOpenBody->getCurFrameIndex()>= 6)
		//{
		//	mOwner->changeActionTo("ScreenAnimClose");
		//}

		// ÇÐ»»µ½¿ÕÏÐ
		if ((mScreenOpenBody->getCurFrameIndex()+1)>= mScreenOpenBody->getFrameCount())
		{
			mOwner->changeActionTo("ScreenAnimIdle");
		}
	}

	IAnimation2D* ActionScreenAnimOpen::getBody()
	{
		return mScreenOpenBody;
	}

	const String ActionFactoryScreenAnimOpen::TypeName = "ScreenAnimOpen";
	ActionFactoryScreenAnimOpen::ActionFactoryScreenAnimOpen()
	{

	}

	ActionFactoryScreenAnimOpen::~ActionFactoryScreenAnimOpen()
	{

	}

	const String& ActionFactoryScreenAnimOpen::type() const
	{
		return TypeName;
	}

	Action* ActionFactoryScreenAnimOpen::createInstance( Actor* owner, ActionDesc* desc )
	{
		ActionScreenAnimOpen* action = new ActionScreenAnimOpen(owner, desc);
		return action;
	}

	ActionDesc* ActionFactoryScreenAnimOpen::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActionDescScreenAnimOpen* actionDesc = new ActionDescScreenAnimOpen;

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
		/*nodeAttr = xmlNodeSprite->first_attribute("duration");
		if (!nodeAttr)
		{
			EXCEPTEX( "background actor. Property action. body need duration label. filename: " << filename );
		}
		actionDesc->duration = StringConverter::parseReal( nodeAttr->value() );
		nodeAttr = xmlNodeSprite->first_attribute("generatorGroupId");
		if (!nodeAttr)
		{
			EXCEPTEX( "background actor. Property action. body need generatorGroupId label. filename: " << filename );
		}
		actionDesc->generatorGroupId = nodeAttr->value();*/
		return actionDesc;
	}
}