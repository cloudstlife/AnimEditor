#include "SystemPrerequisites.h"
#include "ActorBoundaryScreen.h"
#include "IScene.h"
#include "ISceneNode2D.h"
#include "ISprite2D.h"
#include "ISprite2DManager.h"
#include "ActionBoundary.h"
#include "ICollision2DManager.h"
#include "ICollision2DDesc.h"

#include "ogre_src_v1-8-1/OgreSceneManager.h"
#include "ogre_src_v1-8-1/OgreManualObject.h"
#include "ogre_src_v1-8-1/OgreMath.h"

namespace Ogre
{
	struct ActorDescBoundary:public ActorDesc
	{
		Vector2			mViewBound;
	};

	DYNAMIC_IMPLEMENT( ActorBoundaryScreen, GETRTTI( Actor ) )
		ActorBoundaryScreen::ActorBoundaryScreen( ActorDesc* desc, ISceneNode2D* node, IScene* scene, const String& name )
		: Actor( desc, node, scene, "" )
		, mTimes(0.0f)
		, mDrawLine(NULL)
	{
		mDesc = static_cast< ActorDescBoundary* >( desc );
	}

	ActorBoundaryScreen::~ActorBoundaryScreen()
	{

	}

	void ActorBoundaryScreen::initailze()
	{
		// 画出电网，取坐标
		Vector3 vPos3 = this->getSceneNode()->getDerivedPosition();

		Vector2 vLeftBottomPos = Vector2(vPos3.z-(mDesc->mViewBound.x/2), vPos3.y-(mDesc->mViewBound.y));
		Vector2 vLeftUpPos = Vector2(vPos3.z-(mDesc->mViewBound.x/2), vPos3.y+(mDesc->mViewBound.y));
		Vector2 vRightBottomPos = Vector2(vPos3.z+(mDesc->mViewBound.x/2), vPos3.y-(mDesc->mViewBound.y));
		Vector2 vRightUpPos = Vector2(vPos3.z+(mDesc->mViewBound.x/2), vPos3.y+(mDesc->mViewBound.y));
		static int i = 0;
		String strName = "Boundary_";
		strName = strName + StringConverter::toString(i);
		i++;
		// 画线
		mDrawLine = gEnv->mSceneMgr->createManualObject( strName );
	
		mDrawLine->begin( "HelpLine", RenderOperation::OT_LINE_LIST );
		mDrawLine->position( 0, vLeftBottomPos.y, vLeftBottomPos.x );
		mDrawLine->colour( 1.f, 0.f, 0.f );

		mDrawLine->position( 0, vLeftUpPos.y, vLeftUpPos.x );
		mDrawLine->colour( 1.f, 0.f, 0.f );

		mDrawLine->position( 0, vRightUpPos.y, vRightUpPos.x );
		mDrawLine->colour( 1.f, 0.f, 0.f );

		mDrawLine->position( 0, vRightBottomPos.y, vRightBottomPos.x );
		mDrawLine->colour( 1.f, 0.f, 0.f );

		mDrawLine->end();
		mDrawLine->setRenderQueueGroup( RENDER_QUEUE_SKIES_LATE );
		mDrawLine->setCastShadows( false );
		gEnv->mSceneMgr->getRootSceneNode()->attachObject(mDrawLine);

		initailzeActions();
	}

	void ActorBoundaryScreen::updateLogic(Real timeLapse)
	{
		Actor::updateLogic( timeLapse );
		mTimes += timeLapse;
	}

	const String&	ActorBoundaryScreen::type() const
	{
		return ActorFactoryBoundaryScreen::TypeName;
	}

	void	ActorBoundaryScreen::setProperty( const String& name, const Any& val )
	{
		Actor::setProperty( name, val );
	}

	void ActorBoundaryScreen::injectWinMsg( uint uMsg, int wParam, int lParam )
	{

	}

	const String ActorFactoryBoundaryScreen::TypeName = "BounadryScreen";

	ActorFactoryBoundaryScreen::ActorFactoryBoundaryScreen()
	{
		registActionFactory( new ActionFactoryBoundaryScreen );
	}

	ActorFactoryBoundaryScreen::~ActorFactoryBoundaryScreen()
	{

	}

	const String&	ActorFactoryBoundaryScreen::type() const
	{
		return ActorFactoryBoundaryScreen::TypeName;
	}


	Actor*	ActorFactoryBoundaryScreen::createInstance( ActorDesc* actorDesc, ISceneNode2D* node, IScene* scene, const String& name )
	{
		ActorBoundaryScreen* actor = new ActorBoundaryScreen( actorDesc, node, scene );
		//	create actions
		_createActions( actor, actorDesc );
		actor->initailze();
		return actor;
	}

	ActorDesc*	ActorFactoryBoundaryScreen::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActorDescBoundary* actionDesc = new ActorDescBoundary;

		_loadBaseActorDesc( actionDesc, xmlNode, filename );

		_loadActionDesc( actionDesc, xmlNode, filename );
		nodeAttr = xmlNode->first_attribute("viewBound");
		if (!nodeAttr)
		{
			EXCEPTEX( "ActorBoundaryScreen actor. No viewBound. filename: " << filename );
		}
		actionDesc->mViewBound = StringConverter::parseVector2(nodeAttr->value());

		return actionDesc;
	}
}