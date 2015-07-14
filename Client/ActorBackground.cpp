#include "SystemPrerequisites.h"
#include "ActorBackground.h"
#include "IScene.h"
#include "ISceneNode2D.h"
#include "ISprite2D.h"
#include "ISprite2DManager.h"
#include "ActionScreenAnimOpen.h"
#include "ActionScreenAnimClose.h"
#include "ActionScreenAnimIdle.h"
#include "ActionScreenAnimWait.h"


namespace Ogre
{
	struct BackMapNode
	{
		int		lv;
		bool	isAminOpen;
		String	backGround;
		int		layer;
		Real	duration;
		String	generatorGroupId;
	};

	typedef std::vector< BackMapNode >VecBackMapNode;

	struct ActionDescBackground:public ActorDesc
	{
		VecBackMapNode		vecBackMapNode;
	};

	DYNAMIC_IMPLEMENT( ActorBackground, GETRTTI( Actor ) )
		ActorBackground::ActorBackground( ActorDesc* desc, ISceneNode2D* node, IScene* scene, const String& name )
		: Actor( desc, node, scene, "" )
		, mTimes(0.0f)
		, mCurBackMapLv(0)
		, mCurBackMapLvTimes(0.0f)
		, mBackMapScreen(NULL)
		, mBackMapSprite2D(NULL)
		, mNextMap("")
		, mLayer(0)
		, mGeneratorGroupId("")
		, mCurBackMapIter(0)
	{
		mDesc = static_cast< ActionDescBackground* >( desc );
		
		VecBackMapNode::iterator iter = mDesc->vecBackMapNode.begin();
		VecBackMapNode::iterator iterEnd = mDesc->vecBackMapNode.end();
		for (; iter!= iterEnd; ++iter)
		{
			// 第一级背景
			mBackMapSprite2D = gEnv->mSpriteMgr->create(iter->backGround);
			mBackMapSprite2D->setRenderQueue(iter->layer);
			this->getSceneNode()->attachObject(mBackMapSprite2D);
			mLayer = iter->layer;
			break;
		}
	}

	ActorBackground::~ActorBackground()
	{

	}

	void ActorBackground::initailze()
	{
		VecBackMapNode::iterator iter = mDesc->vecBackMapNode.begin();
		VecBackMapNode::iterator iterEnd = mDesc->vecBackMapNode.end();
		for (; iter!= iterEnd; ++iter)
		{
			mCurBackMapLv = iter->lv;
			mCurBackMapLvTimes = iter->duration;
			mCurBackMapIter = 0;
			mGeneratorGroupId = iter->generatorGroupId;
			break;
		}
		mBackMapScreen = static_cast<Action*>(this->getAction("ScreenAnimClose"));
		mScene->createGeneratorGroup(mGeneratorGroupId);
		initailzeActions();
	}

	void ActorBackground::updateLogic(Real timeLapse)
	{
		Actor::updateLogic( timeLapse );
		mTimes += timeLapse;
		if (mTimes >= mCurBackMapLvTimes)
		{
			// 查找下地图
			BackMapNode mapNode = _getNextBackMapInfo();
			mCurBackMapLv = mapNode.lv;
			mCurBackMapLvTimes = mapNode.duration;
			mGeneratorGroupId = mapNode.generatorGroupId;
			mNextMap = mapNode.backGround;
			if (mapNode.isAminOpen)
			{
				changeActionTo( mBackMapScreen->type() );
			}
			else
			{
				// 设置当前地图中的生成器组
				mScene->createGeneratorGroup(mGeneratorGroupId);
			}
			mTimes = 0;
		}
	}

	const String&	ActorBackground::type() const
	{
		return ActorFactoryBackground::TypeName;
	}

	void	ActorBackground::setProperty( const String& name, const Any& val )
	{
		Actor::setProperty( name, val );
	}

	void ActorBackground::injectWinMsg( uint uMsg, int wParam, int lParam )
	{

	}

	String ActorBackground::getNextBackground()
	{
		return mNextMap;
	}

	void ActorBackground::setBackgroundImage()
	{
		// 干掉之前的
		this->getSceneNode()->detachObject(mBackMapSprite2D);
		mBackMapSprite2D = gEnv->mSpriteMgr->create(mNextMap);
		mBackMapSprite2D->setRenderQueue(mLayer);
		this->getSceneNode()->attachObject(mBackMapSprite2D);
		// 设置当前地图中的生成器组
		mScene->createGeneratorGroup(mGeneratorGroupId);
	}

	BackMapNode ActorBackground::_getNextBackMapInfo()
	{
		int nextMapLv = 0;
		String backMap = "";
		mCurBackMapIter++;
		if (mCurBackMapIter> mDesc->vecBackMapNode.size()-1)
		{
			mCurBackMapIter= 0;
		}
		return mDesc->vecBackMapNode[mCurBackMapIter];
	}

	const String ActorFactoryBackground::TypeName = "Background";

	ActorFactoryBackground::ActorFactoryBackground()
	{
		registActionFactory(new ActionFactoryScreenAnimIdle);
		registActionFactory(new ActionFactoryScreenAnimOpen);
		registActionFactory(new ActionFactoryScreenAnimClose);
		registActionFactory(new ActionFactoryScreenAnimWait);
	}

	ActorFactoryBackground::~ActorFactoryBackground()
	{

	}

	const String&	ActorFactoryBackground::type() const
	{
		return ActorFactoryBackground::TypeName;
	}


	Actor*	ActorFactoryBackground::createInstance( ActorDesc* actorDesc, ISceneNode2D* node, IScene* scene, const String& name )
	{
		ActorBackground* actor = new ActorBackground( actorDesc, node, scene );
		//	create actions
		_createActions( actor, actorDesc );
		actor->initailze();
		return actor;
	}

	ActorDesc*	ActorFactoryBackground::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActionDescBackground* actionDesc = new ActionDescBackground;

		_loadBaseActorDesc( actionDesc, xmlNode, filename );

		_loadActionDesc( actionDesc, xmlNode, filename );

		xml_node<>* backMapLVNode = xmlNode->first_node( "BackMapLV" );
		while ( backMapLVNode )
		{
			BackMapNode backMapEle;
			nodeAttr = backMapLVNode->first_attribute("lv");
			backMapEle.lv = StringConverter::parseInt(nodeAttr->value());
			nodeAttr = backMapLVNode->first_attribute("isAminOpen");
			backMapEle.isAminOpen = StringConverter::parseBool(nodeAttr->value());
			nodeAttr = backMapLVNode->first_attribute("background");
			backMapEle.backGround = nodeAttr->value();
			nodeAttr = backMapLVNode->first_attribute("layer");
			backMapEle.layer = StringConverter::parseInt(nodeAttr->value());
			nodeAttr = backMapLVNode->first_attribute("duration");
			backMapEle.duration = StringConverter::parseReal( nodeAttr->value() );
			nodeAttr = backMapLVNode->first_attribute("generatorGroupId");
			backMapEle.generatorGroupId = nodeAttr->value();
			actionDesc->vecBackMapNode.push_back(backMapEle);

			backMapLVNode = backMapLVNode->next_sibling( "BackMapLV" );
		}
		return actionDesc;
	}
}