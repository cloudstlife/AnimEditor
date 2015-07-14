#ifndef ACTIONAUTOLOCKTARGET_H
#define ACTIONAUTOLOCKTARGET_H	

#include "Action.h"

namespace Ogre
{
	class ActorAutoLockTarget;
	struct IAnimation2D;

	class ActionAutoLockTarget: public Action
	{
	public:
		ActionAutoLockTarget(Actor* owner, ActionDesc* desc);
		~ActionAutoLockTarget();

		virtual void initailze();
		virtual const String& type() const;
		virtual void begin();
		virtual void end();
		virtual void update(Real timelapse);
		IAnimation2D* getBody();

	private:
		ActorAutoLockTarget* mActorLockTarget;
		IAnimation2D* mLockTargetAnim;
	};

	class ActionFactoryAutoLockTarget: public ActionFactory
	{
	public:
		ActionFactoryAutoLockTarget();
		virtual ~ActionFactoryAutoLockTarget();
		virtual const String& type() const;
		virtual Action*  createInstance( Actor* owner, ActionDesc* desc );
		virtual  ActionDesc*	load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const	String	TypeName;
	};
}
#endif