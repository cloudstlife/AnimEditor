#include "SystemPrerequisites.h"
#include "ActionScreenAnimIdle.h"
#include "IAnimation2D.h"
#include "ISceneNode2D.h"
#include "ISprite2D.h"
#include "ISprite2DManager.h"
#include "IAnimation2DManager.h"
#include "ActorBackground.h"

namespace Ogre
{
	struct ActionDescScreenAnimIdle:public ActionDesc
	{
		String		id;
		int			layer;
	};

	ActionScreenAnimIdle::ActionScreenAnimIdle(Actor* owner, ActionDesc* desc)
		:Action(desc, owner)
		, mActorBackground(NULL)
		, mId("")
		, mLayer(0)
	{
		mActorBackground = static_cast<ActorBackground*>(owner);
		ActionDescScreenAnimIdle *actionDesc = static_cast<ActionDescScreenAnimIdle*>(desc);
	}

	ActionScreenAnimIdle::~ActionScreenAnimIdle()
	{
		mBackMapSprite2D->destroy();
		mBackMapSprite2D = NULL;
	}

	void ActionScreenAnimIdle::initailze()
	{

	}

	const String& ActionScreenAnimIdle::type() const
	{
		return ActionFactoryScreenAnimIdle::TypeName;
	}

	void ActionScreenAnimIdle::begin()
	{
		Action::begin();
		//mOwner->getSceneNode()->attachObject(mBackMapSprite2D);
	}

	void ActionScreenAnimIdle::end()
	{
		//mOwner->getSceneNode()->detachObject(mBackMapSprite2D);
		Action::end();
	}

	void ActionScreenAnimIdle::update(Real timeLapse)
	{
	}

	const String ActionFactoryScreenAnimIdle::TypeName = "ScreenAnimIdle";
	ActionFactoryScreenAnimIdle::ActionFactoryScreenAnimIdle()
	{

	}

	ActionFactoryScreenAnimIdle::~ActionFactoryScreenAnimIdle()
	{

	}

	const String& ActionFactoryScreenAnimIdle::type() const
	{
		return TypeName;
	}

	Action* ActionFactoryScreenAnimIdle::createInstance( Actor* owner, ActionDesc* desc )
	{
		ActionScreenAnimIdle* action = new ActionScreenAnimIdle(owner, desc);
		return action;
	}

	ActionDesc* ActionFactoryScreenAnimIdle::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActionDescScreenAnimIdle* actionDesc = new ActionDescScreenAnimIdle;

		_loadBaseActionDesc( actionDesc, xmlNode, filename );

		xml_node<>* xmlNodeBody = xmlNode->first_node("sprite");
		if (!xmlNodeBody)
		{
			EXCEPTEX( "background actor. Property action. filename: " << filename );
		}
		nodeAttr = xmlNodeBody->first_attribute("id");
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