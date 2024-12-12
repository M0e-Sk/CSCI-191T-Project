#include "_Runner.h"

_Runner::_Runner()
{
	//ctor
	health = 5;
	model->scale = 0.03f;
	behavior = PASSIVE;
	width = depth = 0.3f;
	height = 0.7f;
}

_Runner::~_Runner()
{
	//dtor
}

void _Runner::init(char* modelFile, char* texFile, vec3 pos)
{
	model->initModel(modelFile, texFile, pos);
	behavior = PASSIVE;
	myTime->startTime = clock();
}

void _Runner::Actions(int* plHealth)
{
	if(clock() - myTime->startTime > 60)
	{
	//model->actions();
	//dir = (des - model->pos).norm();
	switch(behavior)
	{
	case PASSIVE:
		model->StartFrame = 40;
		model->EndFrame = 46;
		speed = 0.1f;
		if(((dir.x >0.0f) ? model->pos.x >= des.x : model->pos.x <= des.x) && ((dir.z > 0.0f) ? model->pos.z >= des.z : model->pos.z <= des.z))
		{
			float angle = rand() % 360;
			vec3 d{cos(angle) * (PI/180.0f), 0.0f, sin(angle) * (PI/180.0f)};
			des = model->pos + (d.norm() * (rand() % 10));
			dir = (des - model->pos).norm();
			model->dirAngleZ = acos(dir.dot(vec3{1.0f,0.0f,0.0f})) * (180.0f/PI);
			if(dir.z > 0.0f) model->dirAngleZ = 360 - model->dirAngleZ;
		}
		break;
	case CAUTIOUS:
		model->StartFrame = 40;
		model->EndFrame = 46;
		speed = 1.0f;
		if(((dir.x >0.0f) ? model->pos.x >= des.x : model->pos.x <= des.x) && ((dir.z > 0.0f) ? model->pos.z >= des.z : model->pos.z <= des.z))
		{
			behavior = PASSIVE;
			float angle = rand() % 360;
			vec3 d{cos(angle) * (PI/180.0f), 0.0f, sin(angle) * (PI/180.0f)};
			des = model->pos + (d.norm() * (rand() % 10));
			dir = (des - model->pos).norm();
			model->dirAngleZ = acos(dir.dot(vec3{1.0f,0.0f,0.0f})) * (180.0f/PI);
			if(dir.z > 0.0f) model->dirAngleZ = 360 - model->dirAngleZ;
		}
		break;
	case HURT:
		model->StartFrame = 54;
		model->EndFrame = 60;
		speed = 0.3f;
		if(model->currFrame == 59)
		{
			behavior = CAUTIOUS;
			vec3 add = dir * 20.0f;
			des = plPos + (dir * 20.0f);
			model->dirAngleZ = acos(dir.dot(vec3{1.0f,0.0f,0.0f})) * (180.0f/PI);
			if(dir.z > 0.0f) model->dirAngleZ = 360 - model->dirAngleZ;
		}
		break;
	case DYING:
		speed = 0.0f;
		model->StartFrame = 178;
		model->EndFrame = 184;
		live = model->currFrame != 183;
		break;
	}
	model->pos = model->pos + (dir.norm()*speed);
	myTime->startTime = clock();
	}
}
