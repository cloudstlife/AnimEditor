#ifndef ACTIONEFFECTUPDATE_H
#define ACTIONEFFECTUPDATE_H
#include "Action.h"

namespace Ogre
{
	class ActorEffect;

	struct AffectorReal;
	struct AffectorVector2;
	struct AffectorVector3;

	class ActionEffectUpdate : public Action
	{
	public:
		ActionEffectUpdate( Actor* owner, ActionDesc* desc );
		~ActionEffectUpdate();

		virtual	void			initailze();
		virtual const String&	type() const;
		virtual	void			begin();
		virtual	void			end();
		virtual	void			update( Real timelapse );

	private:
		ActorEffect*			mActorEffect;
		
		AffectorReal*			mAlpha;
		AffectorReal*			mRot;
		AffectorVector2*		mScale;
		AffectorVector2*		mPos;
		AffectorVector3*		mColorAdd;
		AffectorVector3*		mColorMuti;
	};


	class ActionFactoryEffectUpdate : public ActionFactory
	{
	public:
		ActionFactoryEffectUpdate();
		virtual ~ActionFactoryEffectUpdate();

		virtual const String&	type() const;

		virtual Action*			createInstance( Actor* owner, ActionDesc* desc );

		virtual  ActionDesc*	load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const	String	TypeName;
	};
}

#endif