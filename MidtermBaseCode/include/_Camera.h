#ifndef _CAMERA_H
#define _CAMERA_H

#include<_Common.h>

class _Camera
{
    public:
        _Camera();
        virtual ~_Camera();

        enum {IDLE, FORWARD, BACK, LEFT, RIGHT};

        vec3 eye;
        vec3 dir;
        vec3 upVec;
        vec3 right;

        float thetaX=180;
        float thetaY=0;

        float zoom;

        void camInit();
        void setUpCam();

        void rotateXYP(vec3);
        void rotateUDP(vec3);

        int actionTrigger = 0;

    protected:

    private:
};

#endif // _CAMERA_H
