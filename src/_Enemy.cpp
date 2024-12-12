#include "_Enemy.h"

_Enemy::_Enemy()
{
	//ctor
}

_Enemy::~_Enemy()
{
	//dtor
}

void _Enemy::Draw(double currTime, double lastTime)
{
	if(live)
		model->Draw(currTime, lastTime);
}
