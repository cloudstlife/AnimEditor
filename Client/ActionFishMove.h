#ifndef ACTIONFISHMOVE_H
#define ACTIONFISHMOVE_H
#include "Action.h"

namespace Ogre
{
	class NormalActorFish; 

	struct IAnimation2D;

	class ActionFishMove : public Action
	{
	public:
		ActionFishMove( Actor* owner, ActionDesc* desc );
		~ActionFishMove();

		virtual	void			initailze();
		virtual const String&	type() const;
		virtual	void			begin();
		virtual	void			end();
		virtual	void			update( Real timelapse );

		IAnimation2D*			getBody();

	private:
		NormalActorFish*			mActorFish;
		IAnimation2D*		mFishBody;
	};


	class ActionFactoryFishMove : public ActionFactory
	{
	public:
		ActionFactoryFishMove();
		virtual ~ActionFactoryFishMove();

		virtual const String&	type() const;

		virtual Action*			createInstance( Actor* owner, ActionDesc* desc );

		virtual  ActionDesc*	load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const	String	TypeName;
	};
}

#endif