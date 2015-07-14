#ifndef ACTORGENERATORRANDOMCHASE_H
#define ACTORGENERATORRANDOMCHASE_H

#include "ActorGenerator.h"

namespace Ogre
{
	class ActorGeneratorRandomChase: public ActorGenerator
	{
		typedef std::vector<Vector3>		VecPos;
	public:
		ActorGeneratorRandomChase(IScene* scene, ActorGeneratorDesc* desc, Vector2 vPos = Vector2::ZERO );
		~ActorGeneratorRandomChase();

		virtual void update( Real timeLapse );
		Vector3		 getDestPos();
		int			 getRefreshFishCount();
		void		 updateDestPos();

	private:
		String			mActorName;
		Vector2			mCenterPos;
		Vector3			DestPost;
		int				mWidth;
		int				mHeight;
		int				mFishCount;
		int				mDestCount;
		Real			mRefreshDestTime;
		Real			mRefreshFishTime;
		Real			mTimes;
		Real			mLocalDestTime;
		String			mNavigName;
		VecPos			mVecPos;
		int				mLocalDestCount;
		bool			mPutFished;
		int				mScreenHeight;
		int				mScreenWidth;
	};

	class ActorGeneratorFactoryRandomChase : public ActorGeneratorFactory
	{
	public:
		ActorGeneratorFactoryRandomChase();
		virtual ~ActorGeneratorFactoryRandomChase();

		virtual const String&			type() const;

		virtual ActorGenerator*			createInstance( ActorGeneratorDesc* desc, IScene* scene, Vector2 vPos = Vector2::ZERO );

		virtual  ActorGeneratorDesc*	load( rapidxml::xml_node<>* xmlNode, const String& filename );

		static const String		TypeName;
	};
}
#endif