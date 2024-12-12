#include "_Blitzer.h"

_Blitzer::_Blitzer()
{
	//ctor
	health = 2;
	model->scale = 0.03f;
	width = depth = 0.3f;
	height = 0.7f;
}

_Blitzer::~_Blitzer()
{
	//dtor
}

void _Blitzer::init(char* modelFile, char* texFile, vec3 pos)
{
	model->initModel(modelFile, texFile, pos);
	behavior = AGGRESSIVE;
	myTime->startTime = clock();
}

void _Blitzer::Actions(int* plHealth)
{
	if(clock() - myTime->startTime > 60)
	{
		switch(behavior)
		{
		case AGGRESSIVE:
			model->StartFrame = 40;
			model->EndFrame = 45;
			speed = 1.0f;
			if(((dir.x >0.0f) ? model->pos.x >= des.x : model->pos.x <= des.x) && ((dir.z > 0.0f) ? model->pos.z >= des.z : model->pos.z <= des.z))
			{
				behavior = ATTACK;
			}
			break;
		case ATTACK:
			model->StartFrame = 46;
			model->EndFrame = 53;
			speed = 0.0f;
			if(model->currFrame == 52)
			{
				behavior = AGGRESSIVE;
				dir = (plPos - model->pos).norm();
				des = plPos - dir;
				model->dirAngleZ = acos(dir.dot(vec3{1.0f,0.0f,0.0f})) * (180.0f/PI);
				if(dir.z > 0.0f) model->dirAngleZ = 360 - model->dirAngleZ;
				if(col->isCubicCollision(model->pos + dir, plPos, 0.5f, 0.5, 0.5f, 0.5f, 0.5f, 0.5f))
				{
					(*plHealth)--;
				}
			}
			break;
		case HURT:
			model->StartFrame = 54;
			model->EndFrame = 57;
			speed = 0.2f;
			if(model->currFrame == 56)
			{
				behavior = AGGRESSIVE;
				dir = (plPos - model->pos).norm();
				des = plPos - dir;
				model->dirAngleZ = acos(dir.dot(vec3{1.0f,0.0f,0.0f})) * (180.0f/PI);
				if(dir.z > 0.0f) model->dirAngleZ = 360 - model->dirAngleZ;
			}
			break;
		case DYING:
			model->StartFrame = 178;
			model->EndFrame = 183;
			speed = 0.0f;
			live = model->currFrame != 182;
			break;
		}
		model->pos = model->pos + (dir.norm() * speed);
		myTime->startTime = clock();
	}
}
