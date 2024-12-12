#ifndef _ENEMY_H
#define _ENEMY_H

#include "_Common.h"
#include "_ModelLoaderMD2.h"
#include "_Timer.h"
#include "_Collision.h"
#include "_Sounds.h"

class _Enemy
{
	public:
		_Enemy();
		virtual ~_Enemy();

		virtual void init(char*, char*, vec3) = 0;
		virtual void Draw(double, double);
		virtual void Actions(int*) = 0;

		_ModelLoaderMD2 *model = new _ModelLoaderMD2();
		_Timer *myTime = new _Timer();

		enum {PASSIVE, CAUTIOUS, AGGRESSIVE, ATTACK, HURT, DYING, TAUNT, STUN};
		float health;
		float speed;
		int stunCnt = 0;

		float width, height, depth;

		int behavior;
		bool live = true;

		vec3 des;
		vec3 dir;
		vec3 plPos;

		_Collision *col = new _Collision();

		_Sounds *snds;


	protected:

	private:
};

#endif // _ENEMY_H
