#ifndef ACTORGENERATORROUNDDIFFUSE_H
#define ACTORGENERATORROUNDDIFFUSE_H
#include "ActorGenerator.h"
namespace Ogre
{
	struct RoundDiffuseNode;
	typedef std::vector<Real> VectFishNode;
	class ActorGeneratorRoundDiffuse: public ActorGenerator
	{
	public:
		ActorGeneratorRoundDiffuse(IScene* scene, ActorGeneratorDesc* desc, Vector2 vPos = Vector2::ZERO );
		~ActorGeneratorRoundDiffuse();

		virtual void update(Real timeLapse);

	private:
		int			mFishCount;
		String		mActorName;
		Real		mCurSpeed;
		String		mNavigName;		//	导航名
		Real		mLifeTime;		//	生命周期
		Real		mDiffuseTime;	//	散开时间
		Vector2		mCenterPos;
		Real		mRadius;
		Real		mTimes;			//	用于生命周期叠加时间
		bool		mBStart;
		int			mRotateDir;
		VectFishNode	vectFishNode;
	};

	class ActorGeneratorFactoryRoundDiffuse : public ActorGeneratorFactory
	{
	public:
		ActorGeneratorFactoryRoundDiffuse();
		virtual ~ActorGeneratorFactoryRoundDiffuse();

		virtual const String&			type() const;

		virtual ActorGenerator*			createInstance( ActorGeneratorDesc* desc, IScene* scene, Vector2 vPos = Vector2::ZERO );

		virtual  ActorGeneratorDesc*	load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const String		TypeName;
	};
}

#endif