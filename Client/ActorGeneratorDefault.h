/*
	在固定位置按照一定的频率投放指定鱼
*/

#ifndef ACTORGENERATORDEFAULT_H
#define ACTORGENERATORDEFAULT_H
#include "ActorGenerator.h"

namespace Ogre
{
	class ActorGeneratorDefault : public ActorGenerator
	{
	public:
		ActorGeneratorDefault( IScene* scene, ActorGeneratorDesc* desc, Vector2 vPos = Vector2::ZERO );
		~ActorGeneratorDefault();
		
		virtual void	update( Real timeLapse );

	private:
		Vector2		mPos;
		Real		mSpeed;
		Real		mLoopTime;
		int			mCount;
		String		mActorName;
		String		mNavigName;

		Real		mCurLoopTime;
		int			mCurCount;
		Real		mCurSpeed;
		Real		mLifeTime;
	};

	class ActorGeneratorFactoryDefault : public ActorGeneratorFactory
	{
	public:
		ActorGeneratorFactoryDefault();
		virtual ~ActorGeneratorFactoryDefault();

		virtual const String&			type() const;

		virtual ActorGenerator*			createInstance( ActorGeneratorDesc* desc, IScene* scene, Vector2 vPos = Vector2::ZERO );

		virtual  ActorGeneratorDesc*	load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const String		TypeName;
	};
}


#endif