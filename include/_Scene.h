#ifndef _SCENE_H
#define _SCENE_H

#include<_Common.h>

class _Scene
{
    public:
        _Scene();
        virtual ~_Scene();
        GLint initGL();          // initializing the scene
        GLint loadLevel1();
        GLint loadLevel2();
        GLint loadLevel3();
        GLint drawScene();       //Render scene
        GLvoid resizeScene(GLsizei,GLsizei);// address window resize
        GLvoid mouseMapping(int, int);

        int winMsg(HWND,UINT,WPARAM,LPARAM);
        WPARAM wParam;

        bool wireFrame = false;

      float  screenWidth, screenHeight;

      enum{MAIN,HELP,PAUSE,PLAY};

      GLdouble mouseX;
      GLdouble mouseY;
      GLdouble mouseZ;
      int mouseClicks =0;
      int curBullet = 0;
      int Score;
      int currLevel;
      int status;
      int previousStatus;
      //int* playerHealth;

    protected:

    private:
};

#endif // _SCENE_H
