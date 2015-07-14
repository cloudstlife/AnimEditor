#include "SystemPrerequisites.h"
#include "ActionBoundary.h"
#include "ISprite2D.h"
#include "IAnimation2D.h"
#include "ISprite2DManager.h"
#include "IAnimation2DManager.h"
#include "ISceneNode2D.h"
#include "ActorBoundaryScreen.h"
#include "ActorFish.h"

namespace Ogre
{	
	struct ActionDescBoundary : public ActionDesc
	{
		String		id;
		int			layer;
	};

	//---
	ActionBoundary::ActionBoundary( Actor* owner, ActionDesc* desc )
		: Action( desc, owner )
	{
		mActorBoundary = static_cast< ActorBoundaryScreen* >( owner );
	}

	ActionBoundary::~ActionBoundary()
	{
	}

	void	ActionBoundary::initailze()
	{
		
	}

	const String&	ActionBoundary::type() const
	{
		return ActionFactoryBoundaryScreen::TypeName;
	}

	void	ActionBoundary::begin()
	{
		Action::begin();
		
	}

	void	ActionBoundary::end()
	{
		Action::end();
	}

	void	ActionBoundary::update( Real timelapse )
	{
	}

	void	ActionBoundary::beginContact( Actor* other )
	{
		if ( RTTI::IsKindOf( other->getRTTI(), GETRTTI( ActorFish ) ) )
		{
			ActorFish* fish = static_cast< ActorFish* >( other );
			// É¾³ý¸ÃÓã
			fish->valid();
			printf("delete Fish name: %0x\n", fish);
		}
	}

	void	ActionBoundary::endContact( Actor* other )
	{
	}

	//---
	const String ActionFactoryBoundaryScreen::TypeName = "boundary";
	ActionFactoryBoundaryScreen::ActionFactoryBoundaryScreen()
	{

	}

	ActionFactoryBoundaryScreen::~ActionFactoryBoundaryScreen()
	{

	}

	const String&	ActionFactoryBoundaryScreen::type() const
	{

		return TypeName;
	}

	Action*	ActionFactoryBoundaryScreen::createInstance( Actor* owner, ActionDesc* desc )
	{
		ActionBoundary* action = new ActionBoundary( owner, desc );

		return action;
	}

	ActionDesc*	ActionFactoryBoundaryScreen::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActionDescBoundary* actionDesc = new ActionDescBoundary;

		_loadBaseActionDesc( actionDesc, xmlNode, filename );

		return actionDesc;
	}

}