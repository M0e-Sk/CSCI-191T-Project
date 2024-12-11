#include "_Boss.h"

_Boss::_Boss()
{
	//ctor
	health = 100;
	model->scale = 0.2f;
	w->scale = 0.2f;
	width = depth = 2.2f;
	height = 4.5f;
}

_Boss::~_Boss()
{
	//dtor
	delete w;
}

void _Boss::init(char* modelfile, char* texfile, vec3 pos)
{
	model->initModel(modelfile, texfile, pos);
	w->initModel("models/doomunls/weapon.md2", "models/GIJOE/weapon.jpg", pos);
	behavior = TAUNT;
	speed = 0.0f;
	for(int i = 0; i< 30; i++)
	{
		b[i].initBullet("");
	}
}

void _Boss::Draw(double currTime, double lastTime)
{
	w->pos = model->pos;
	w->dirAngleZ = model->dirAngleZ;
	if(live)
	{
		glPushMatrix();
		model->Draw(currTime,lastTime);
		glPopMatrix();
		w->Draw(currTime,lastTime);
	}
}

void _Boss::Actions(int* plHealth)
{
	for(int i = 0; i < 30; i++)
	{
		b[i].drawBullet();
		if(col->isCubicCollision(plPos, b[i].pos, 0.5f, 0.1f, 1.0f, 0.1f, 0.5f, 0.1f) && b[i].live)
		{
			plHealth--;
		}
		b[i].bulletAction();
	}
	if(clock() - myTime->startTime > 60) {
	dir = (plPos - model->pos).norm();
	model->dirAngleZ = acos(dir.dot(vec3{1.0f,0.0f,0.0f})) * (180.0f/PI);
	if(dir.z > 0.0f) model->dirAngleZ = 360 - model->dirAngleZ;
	dir = (plPos - vec3{model->pos.x, 0, model->pos.z}).norm();
	//model->pos = model->pos + (dir * speed);
	switch(behavior)
	{
	case AGGRESSIVE:
		model->StartFrame = 40;
		model->EndFrame = 45;
		w->StartFrame = 40;
		w->EndFrame = 45;
		if(model->currFrame == 44)
		{
			behavior = ATTACK;
		}
		speed = 0.2f;
		break;
	case HURT:
		model->StartFrame = 190;
		model->EndFrame = 197;
		w->StartFrame = 190;
		w->StartFrame = 197;
		speed = 0.0f;
		if(model->currFrame == 196)
			behavior = AGGRESSIVE;
		break;
	case ATTACK:
		model->StartFrame = 46;
		model->EndFrame = 53;
		w->StartFrame = 46;
		w->EndFrame = 53;
		if(model->currFrame == 48 || model->currFrame == 50)
		{
			b[bullCnt].actionTrigger = b[bullCnt].SHOOT;
			b[bullCnt].live = true;
			b[bullCnt].pos = model->pos;
			b[bullCnt].des = (plPos - model->pos).norm();
			bullCnt = (bullCnt + 1) % 30;
		}
		if(model->currFrame == 52)
		{
			attackCnt--;
			attackCnt <= 0 ? behavior = TAUNT : behavior = AGGRESSIVE;
		}
		speed = 0.1f;
		break;
	case TAUNT:
		model->StartFrame = 95;
		model->EndFrame = 111;
		w->StartFrame = 95;
		w->EndFrame = 111;
		health > 50 ? attackCnt = 3 : health > 20 ? attackCnt = 4 : attackCnt = 5;
		cout << stunCnt << endl;
		if(model->currFrame == 110)
		{
			behavior = AGGRESSIVE;
			stunCnt = 0;
		}
		else if(stunCnt >= 3)
		{
			behavior = HURT;
			health -= 7;
			stunCnt = 0;
		}
		speed = 0.0f;
		break;
	case DYING:
		model->StartFrame = 178;
		model->EndFrame = 183;
		w->StartFrame = 178;
		w->EndFrame = 183;
		speed = 0.0f;
		live = model->currFrame != 182;
		break;
	}
	}
}
