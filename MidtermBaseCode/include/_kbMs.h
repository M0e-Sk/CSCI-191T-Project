#ifndef _KBMS_H
#define _KBMS_H

#include<_Common.h>
#include<_Models.h>
#include<_parallax.h>
#include<_SkyBox.h>
#include<_Skybox2.h>
#include<_Camera.h>
#include<_2DPlayer.h>
#include<_ModelLoaderMD2.h>
#include<_Timer.h>
#include<_Menu.h>

class _KbMs
{
    public:
        _KbMs();
        virtual ~_KbMs();

        WPARAM wParam;

        void keyPress(_Models *);
        void keyPress(_SkyBox*);
        void keyPress(_Skybox2*);
        void keyPress(_Camera*);
        void keyPress(_2DPlayer*);
        void keyPress(_ModelLoaderMD2*);
        bool pausePress();
        void moveBck(_parallax*,float);
        void keyUp();
        void keyUp(_2DPlayer*);
        void keyUp(_ModelLoaderMD2*);
        void keyUp(_Camera*);

        void mouseEventDown(double, double);
        void mouseEventDown(_Menu*,double, double);
        bool mouseEventDownPause(_Menu*,double,double);
        void mouseEventUp();

        void mouseWheel(_Models*,double);
        void mouseMove(_Models*, double, double);
        void mouseMove(_SkyBox*, double, double);
        void mouseMove(_Skybox2*, double, double);

        void mouseMove(_Camera*,double,double);
        void mouseMove(_ModelLoaderMD2*, double, double);

        double prev_MouseX;
        double prev_MouseY;

        double prev_MouseX_Cam;
        double prev_MouseY_Cam;

        bool mouseTranslation;
        bool mouseRotation;
        bool firstMouse = true;

        _Timer *myTime = new _Timer();

    protected:

    private:
};

#endif // _KBMS_H
