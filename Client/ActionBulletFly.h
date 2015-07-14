#ifndef ACTIONBULLETFLY_H
#define ACTIONBULLETFLY_H
#include "Action.h"

namespace Ogre
{
	class ActorBullet; 
	
	struct IAnimation2D;
		
	class ActionBulletFly : public Action
	{
	public:
		ActionBulletFly( Actor* owner, ActionDesc* desc );
		~ActionBulletFly();

		virtual	void			initailze();
		virtual const String&	type() const;
		virtual	void			begin();
		virtual	void			end();
		virtual	void			update( Real timelapse );

		virtual	void			beginContact( Actor* other );
		virtual	void			endContact( Actor* other );

	private:
		bool					_calcBulletToBound();

	private:
		ActorBullet*		mActorBullet;
		IAnimation2D*		mBulletBody;
		Real				mSpeed;
		int					mScreenHeight;
		int					mScreenWidth;
	};


	class ActionFactoryBulletFly : public ActionFactory
	{
	public:
		ActionFactoryBulletFly();
		virtual ~ActionFactoryBulletFly();

		virtual const String&	type() const;

		virtual Action*			createInstance( Actor* owner, ActionDesc* desc );

		virtual  ActionDesc*	load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const	String	TypeName;
	};
}

#endif