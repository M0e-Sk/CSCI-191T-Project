#ifndef _RUNNER_H
#define _RUNNER_H

#include <_Enemy.h>

//Runners will wander between random points and will flee from the player when they are hit

class _Runner : public _Enemy
{
	public:
		_Runner();
		virtual ~_Runner();

		void init(char*,char*,vec3);
		void Actions(int*);

	protected:

	private:
};

#endif // _RUNNER_H
