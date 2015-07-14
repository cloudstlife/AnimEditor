#ifndef ACTORPARALLELGENERATOR_H
#define ACTORPARALLELGENERATOR_H
#include "ActorGenerator.h"

namespace Ogre
{
	struct ParallelNode
	{
		int		id;
		Vector2	pos;
	};
	typedef std::list<ParallelNode>		ListParallelNode;
	class ActorParallelGenerator: public ActorGenerator
	{
	public:
		ActorParallelGenerator(IScene* scene, ActorGeneratorDesc* desc, Vector2 vPos = Vector2::ZERO );
		~ActorParallelGenerator();

		virtual void	update( Real timeLapse );

	private:
		Vector2				mPos;
		Real				mSpeed;
		Real				mLoopTime;
		int					mCount;
		String				mActorName;
		String				mNavigName;

		Real				mCurLoopTime;
		int					mCurCount;
		Real				mCurSpeed;
		Real				mLifeTime;
		ListParallelNode	mListParallelNode;
	};

	class ActorGeneratorFactoryParallel : public ActorGeneratorFactory
	{
	public:
		ActorGeneratorFactoryParallel();
		virtual ~ActorGeneratorFactoryParallel();

		virtual const String&			type() const;

		virtual ActorGenerator*			createInstance( ActorGeneratorDesc* desc, IScene* scene, Vector2 vPos = Vector2::ZERO );

		virtual  ActorGeneratorDesc*	load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const String		TypeName;
	};
}
#endif