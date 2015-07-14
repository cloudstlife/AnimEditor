#ifndef ACTIONSTATICSTAND_H
#define ACTIONSTATICSTAND_H
#include "Action.h"

namespace Ogre
{
	struct ISprite2D;
	struct IAnimation2D;

	class ActorStatic;
	

	class ActionStaticStand : public Action
	{
		typedef std::list< IAnimation2D* >		ListAnim;
		typedef std::list< ISprite2D* >			ListSprite;

	public:
		ActionStaticStand( Actor* owner, ActionDesc* desc );
		~ActionStaticStand();

		virtual	void			initailze();
		virtual const String&	type() const;
		virtual	void			begin();
		virtual	void			end();
		virtual	void			update( Real timelapse );

	private:
		ActorStatic*		mActorStatic;
		ListAnim			mAnims;
		ListSprite			mSprites;
	};


	class ActionFactoryStaticStand : public ActionFactory
	{
	public:
		ActionFactoryStaticStand();
		virtual ~ActionFactoryStaticStand();

		virtual const String&	type() const;

		virtual Action*			createInstance( Actor* owner, ActionDesc* desc );

		virtual  ActionDesc*	load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const	String	TypeName;
	};
}

#endif