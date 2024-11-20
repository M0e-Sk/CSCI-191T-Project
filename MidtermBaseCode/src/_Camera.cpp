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
        eye.x= eye.y=0; eye.z =10.0;
        dir.x=0;dir.y =0; dir.z =-1;
        upVec.x =upVec.z=0; upVec.y = 1.0;

        zoom = sqrt(pow(dir.x-eye.x,2)+pow(dir.y-eye.y,2)+pow(dir.z-eye.z,2));

}

void _Camera::setUpCam()
{

    dir.x = cos(thetaY *PI/180.0) * sin(thetaX*PI/180.0);
    dir.y = sin(thetaY*PI/180.0);
    dir.z = cos(thetaY*PI/180.0) * cos(thetaX*PI/180.0);


   // setup camera with values
   vec3 des;
   des = eye + dir;
   gluLookAt(eye.x,eye.y,eye.z,des.x,des.y,des.z,upVec.x,upVec.y,upVec.z);
 // gluLookAt(0,0,10,0,0,0,0,1,0);
}
