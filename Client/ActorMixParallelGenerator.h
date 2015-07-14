#ifndef ACTORMIXPARALLELGENERATOR_H
#define ACTORMIXPARALLELGENERATOR_H
#include "ActorGenerator.h"

namespace Ogre
{
	struct MixParallelNode;

	struct ActorGeneratorDescMixParallel;

	class ActorMixParallelGenerator: public ActorGenerator
	{
	public:
		ActorMixParallelGenerator(IScene* scene, ActorGeneratorDesc* desc, Vector2 vPos = Vector2::ZERO);
		~ActorMixParallelGenerator();

		virtual void	update(Real timeLapse);

	private:
		Vector2				mPos;
		Real				mSpeed;
		Real				mLoopTime;
		int					mCount;
		String				mNavigName;

		Real				mCurLoopTime;
		int					mCurCount;
		Real				mCurSpeed;
		Real				mLifeTime;
		ActorGeneratorDescMixParallel* mDesc;
	};

	class ActorGeneratorFactoryMixParallel : public ActorGeneratorFactory
	{
	public:
		ActorGeneratorFactoryMixParallel();
		virtual ~ActorGeneratorFactoryMixParallel();

		virtual const String&			type() const;

		virtual ActorGenerator*			createInstance( ActorGeneratorDesc* desc, IScene* scene, Vector2 vPos = Vector2::ZERO );

		virtual  ActorGeneratorDesc*	load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const String		TypeName;
	};
}

#endif