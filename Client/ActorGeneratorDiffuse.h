#ifndef ACTORGENERATORDIFFUSE_H
#define ACTORGENERATORDIFFUSE_H

#include "ActorGenerator.h"
namespace Ogre
{
	struct DiffuseNode;

	typedef std::list< DiffuseNode > ListDiffuseNode;
	class ActorGeneratorDiffuse: public ActorGenerator
	{
	public:
		ActorGeneratorDiffuse(IScene* scene, ActorGeneratorDesc* desc, Vector2 vPos = Vector2::ZERO );
		~ActorGeneratorDiffuse();
		
		virtual void update( Real timeLapse );

	private:
		Vector2		mCenterPos;
		Real		mSpeed;
		Real		mLoopTime;
		int			mCount;
		int			mFishCount;
		String		mActorName;
		Real		mCurLoopTime;
		int			mCurCount;
		Real		mCurSpeed;
		String		mNavigName;		//	导航名
		Real		mLifeTime;		//	生命周期
		Real		mTimes;			//	用于生命周期叠加时间
		Real		mFishTime;
		ListDiffuseNode	listDiffuseNode;
	};

	class ActorGeneratorFactoryDiffuse : public ActorGeneratorFactory
	{
	public:
		ActorGeneratorFactoryDiffuse();
		virtual ~ActorGeneratorFactoryDiffuse();

		virtual const String&			type() const;

		virtual ActorGenerator*			createInstance( ActorGeneratorDesc* desc, IScene* scene, Vector2 vPos = Vector2::ZERO );

		virtual  ActorGeneratorDesc*	load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const String		TypeName;
	};
}
#endif