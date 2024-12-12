#ifndef _BOSS_H
#define _BOSS_H

#include <_Enemy.h>
#include <_Bullets.h>


class _Boss : public _Enemy
{
	public:
		_Boss();
		virtual ~_Boss();

		void init(char*,char*,vec3);
		void Draw(double, double) override;
		void Actions(int* plHealth);

		_ModelLoaderMD2 *w = new _ModelLoaderMD2();
		_Bullets b[30];

		int attackCnt = 3;
		int bullCnt = 0;

	protected:

	private:
};

#endif // _BOSS_H
