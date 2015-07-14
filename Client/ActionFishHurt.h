#ifndef ACTIONFISHHURT_H
#define ACTIONFISHHURT_H
#include "Action.h"

namespace Ogre
{
	class NormalActorFish; 
	struct IAnimation2D;

	class ActionFishHurt : public Action
	{
	public:
		ActionFishHurt( Actor* owner, ActionDesc* desc );
		~ActionFishHurt();

		virtual	void			initailze();
		virtual const String&	type() const;
		virtual	void			begin();
		virtual	void			end();
		virtual	void			update( Real timelapse );

	private:
		NormalActorFish*			mActorFish;
		bool				mCanChangleColor;
		IAnimation2D*		mFishBody;
		Vector3				mHurtColorNormal;
	};


	class ActionFactoryFishHurt : public ActionFactory
	{
	public:
		ActionFactoryFishHurt();
		virtual ~ActionFactoryFishHurt();

		virtual const String&	type() const;

		virtual Action*			createInstance( Actor* owner, ActionDesc* desc );

		virtual  ActionDesc*	load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const	String	TypeName;
	};
}

#endif