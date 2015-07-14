#ifndef ACTIONBOUNDARY_H
#define ACTIONBOUNDARY_H
#include "Action.h"

namespace Ogre
{
	class ActorBoundaryScreen; 

	struct IAnimation2D;

	class ActionBoundary : public Action
	{
	public:
		ActionBoundary( Actor* owner, ActionDesc* desc );
		~ActionBoundary();

		virtual	void			initailze();
		virtual const String&	type() const;
		virtual	void			begin();
		virtual	void			end();
		virtual	void			update( Real timelapse );

		virtual	void			beginContact( Actor* other );
		virtual	void			endContact( Actor* other );

	private:
		ActorBoundaryScreen*			mActorBoundary;
		IAnimation2D*					mBoundaryBody;
		Real							mSpeed;
		int								mScreenHeight;
		int								mScreenWidth;
	};


	class ActionFactoryBoundaryScreen : public ActionFactory
	{
	public:
		ActionFactoryBoundaryScreen();
		virtual ~ActionFactoryBoundaryScreen();

		virtual const String&	type() const;

		virtual Action*			createInstance( Actor* owner, ActionDesc* desc );

		virtual  ActionDesc*	load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const	String	TypeName;
	};
}

#endif