#ifndef _CAMERA_H
#define _CAMERA_H

#include<_Common.h>

class _Camera
{
    public:
        _Camera();
        virtual ~_Camera();

        vec3 eye;
        vec3 dir;
        vec3 upVec;

        float thetaX=180;
        float thetaY=0;

        float zoom;

        void camInit();
        void setUpCam();

        void rotateXYP(vec3);
        void rotateUDP(vec3);

    protected:

    private:
};

#endif // _CAMERA_H
