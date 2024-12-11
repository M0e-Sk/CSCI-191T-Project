#include "_Camera.h"

_Camera::_Camera()
{
    //ctor

}

_Camera::~_Camera()
{
    //dtor
}
void _Camera::camInit()
{
      // initialize camera values
        eye.x=0.0f; eye.y=0; eye.z =10.0;
        dir.x=0;dir.y =0; dir.z =-1;
        upVec.x =upVec.z=0; upVec.y = 1.0;

        thetaX = 180.0f;
        thetaY = 0.0f;

        zoom = sqrt(pow(dir.x-eye.x,2)+pow(dir.y-eye.y,2)+pow(dir.z-eye.z,2));

        myTime->startTime = clock();
}

void _Camera::setUpCam()
{

    dir.x = cos(thetaY *PI/180.0) * sin(thetaX*PI/180.0);
    dir.y = sin(thetaY*PI/180.0);
    dir.z = cos(thetaY*PI/180.0) * cos(thetaX*PI/180.0);

    right = dir.cross(upVec);
    right.y = 0;

    vec3 fwd = dir;
    fwd.y = 0;

    //cout << mov.x << " " << mov.y << " " << mov.z << endl;
    if(clock() - myTime->startTime > 60)
	{
    switch(actionTrigger)
    {
	case FORWARD:
		eye = eye + fwd.norm();
		break;
	case BACK:
		eye = eye - fwd.norm();
		break;
	case LEFT:
		eye = eye - right.norm();
		//dir = dir-right;
		break;
	case RIGHT:
		eye = eye + right.norm();
		//dir = dir + right;
		break;
    }
    myTime->startTime = clock();
    //cout << eye.x << " " << eye.y << " " << eye.z << endl;
	}
	if(eye.x > 200.0f) eye.x = 198.0f;
	if(eye.x < -200.0f) eye.x = -198.0f;
	if(eye.z > 200.0f) eye.z = 198.0f;
	if(eye.z < -200.0f) eye.z = -198.0f;


   // setup camera with values
   vec3 des;
   des = eye + dir;
   gluLookAt(eye.x,eye.y,eye.z,des.x,des.y,des.z,upVec.x,upVec.y,upVec.z);
 // gluLookAt(0,0,10,0,0,0,0,1,0);
}
