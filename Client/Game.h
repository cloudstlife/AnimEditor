#ifndef GAME_H
#define GAME_H

namespace Ogre
{
	struct ICompnt;

	class Game
	{
	public:
		Game();
		~Game();

		void	initialize();
		void	registerActor();
		void	registerActorGenerator();
		void	registerNavigation();
		void	go();

	private:
		ICompnt*	mCompntSystem;
	};
}


#endif