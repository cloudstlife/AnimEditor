#ifndef ACTIONFISHDIED_H
#define ACTIONFISHDIED_H
#include "Action.h"

namespace Ogre
{
	class NormalActorFish; 
	struct IAnimation2D;
	struct ILabelNumber2D;
	struct ISceneNode2D;

	struct ShowScore
	{
		String		id;
		int			layer;
		Vector2		offsetPos;
		//Real		showTime;
	};

	class ActionFishDied : public Action
	{
	public:
		ActionFishDied( Actor* owner, ActionDesc* desc );
		~ActionFishDied();

		virtual	void			initailze();
		virtual const String&	type() const;
		virtual	void			begin();
		virtual	void			end();
		virtual	void			update( Real timelapse );

	private:
		NormalActorFish*			mActorFish;
		IAnimation2D*		mFishBody;
		ISceneNode2D*		mShowScore2DNode;
		ISceneNode2D*		mFireScoreNode;
		ILabelNumber2D*		mShowScore2D;
		ShowScore			mShowScore;
	};


	class ActionFactoryFishDied : public ActionFactory
	{
	public:
		ActionFactoryFishDied();
		virtual ~ActionFactoryFishDied();

		virtual const String&	type() const;

		virtual Action*			createInstance( Actor* owner, ActionDesc* desc );

		virtual  ActionDesc*	load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const	String	TypeName;
	};
}

#endif