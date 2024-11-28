#include "_Scene.h"
#include<_lightSetup.h>
#include<_kbMs.h>
#include <_parallax.h>
#include<_SkyBox.h>
#include<_Skybox2.h>
#include<_Camera.h>
#include<_Bullets.h>
#include<_ModelLoaderMD2.h>
#include<_Collision.h>

_lightSetup *myLight = new _lightSetup();
_KbMs *KbMs = new _KbMs();
_parallax *plx = new _parallax();
_SkyBox *sky = new _SkyBox();
_Skybox2 *sky2 = new _Skybox2();
_Camera *cam = new _Camera();
_Bullets b[20];
_ModelLoaderMD2 ufos[5] ;
_Collision *col = new _Collision();


_Scene::_Scene()
{
    //ctor
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    screenHeight= GetSystemMetrics(SM_CYSCREEN);
}

_Scene::~_Scene()
{
    //dtor
}
GLint _Scene::initGL()
{
    glShadeModel(GL_SMOOTH);  // for smooth render
    glClearColor(1,1,1,0);    // Background Color
    glClearDepth(2.0f);       // test on Depth layer
    glEnable(GL_DEPTH_TEST);  // Activate depth Test
    glDepthFunc(GL_LEQUAL);   // Depth function type
    glEnable(GL_COLOR_MATERIAL);
    myLight->setLight(GL_LIGHT0); // seting my first light

     glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

     glEnable(GL_TEXTURE_2D);  //enable textures

     plx->parallaxInit("images/bck.jpeg");
     sky->skyBoxInit();
     sky2->skyBoxinit("images/bk.png");
     cam->camInit();
     for(int i = 0; i < 20; i++)
		b[i].initBullet("file");

	 for(int i = 0; i < 5; i++)
	 {
		ufos[i].initModel("models/UFO/tris.md2",vec3{100.0f,100.0f,-100.0f});
	 }

	ufos[1].pos.x = -100.0f;
	ufos[2].pos.x = 0;
	ufos[3].pos.z = 0;
	ufos[4].pos.x = -100.0f;
	ufos[4].pos.z = 0;
    return true;
}

GLint _Scene::drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();   // clearing matrices


    wireFrame?glPolygonMode(GL_FRONT_AND_BACK, GL_LINE):glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    cam->setUpCam();

      glPushMatrix();
      glTranslatef(0,-10,1);
      glRotatef(90,1,0,0);

      glScalef(100,50,1.0);
   // plx->parallaxScroll(true,"left",0.005);
      plx->parallaxDraw(screenWidth,screenHeight);

      glPopMatrix();

      glPushMatrix();
      for(int i = 0; i < 20; i++)
      {
		b[i].drawBullet();
		for(int j = 0; j < 5 && b[i].live; j++)
		{
			vec3 pos;
			pos.x = ufos[j].pos.x/10.0f;
			pos.y = ufos[j].pos.y/10.0f;
			pos.z = ufos[j].pos.z/10.0f;
			if(col->isSphereCollision(b[i].pos, pos, 0.5f, 1.5f, 0.2f) && ufos[j].live)
			{
				cout << "HIT!" << endl;
				ufos[j].live = false;
				b[i].actionTrigger = b[i].DEAD;
			}
		}
		b[i].bulletAction();
      }
      glPopMatrix();

      glPushMatrix();
  //    sky->drawSkyBox();
        sky2->skyBoxDraw();
      glPopMatrix();

      for(int i = 0; i < 5; i++)
	  {
	  	if(ufos[i].live)
		{
			glPushMatrix();
			ufos[i].Draw();
			glPopMatrix();
		}
	  }

    return true;
}

GLvoid _Scene::resizeScene(GLsizei width, GLsizei height)
{
    GLfloat aspectRatio = (GLfloat)width/height;

    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,aspectRatio,0.1,3000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}
GLvoid _Scene::mouseMapping(int x, int y)
{
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    screenHeight= GetSystemMetrics(SM_CYSCREEN);

    GLint viewPort[4];
    GLdouble modelViewM[16];
    GLdouble projectionM[16];
    GLfloat winX,winY,winZ;

    float scale = 60*(screenWidth/screenHeight);

    glGetDoublev(GL_MODELVIEW_MATRIX, modelViewM);
    glGetDoublev(GL_PROJECTION_MATRIX,projectionM);
    glGetIntegerv(GL_VIEWPORT,viewPort);

    winX = (GLfloat)x;
    winY = (GLfloat)(viewPort[3]-y);
    glReadPixels(x,int(winY),1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&winZ);

    mouseX = (GLfloat)(x-screenWidth/2.0)/scale;
    mouseY = (GLfloat)(screenHeight/2.0-y)/scale;
    mouseZ = -100;


    gluUnProject(winX,winY,winZ,modelViewM,projectionM,viewPort,&mouseX,&mouseY,&mouseZ);
}


int _Scene::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)   // check for inputs
    {
    case WM_KEYDOWN:
         KbMs->wParam = wParam;
         //KbMs->moveBck(plx,0.0005);
         //KbMs->keyPress(sky);
         //KbMs->keyPress(sky2);
         KbMs->keyPress(cam);
         break;

    case WM_KEYUP:
         KbMs->wParam = wParam;
         KbMs->keyUp();
        KbMs->keyUp(cam);
         break;

    case WM_LBUTTONDOWN:
         KbMs->wParam = wParam;

         mouseMapping(LOWORD(lParam),HIWORD(lParam));
         KbMs->mouseEventDown(mouseX,mouseY);

		b[curBullet].actionTrigger = b[curBullet].SHOOT;
		b[curBullet].live = true;
		b[curBullet].pos = cam->eye;
		b[curBullet].des = cam->dir;
		curBullet = (curBullet + 1) % 20;

         break;

    case WM_RBUTTONDOWN:
         KbMs->wParam = wParam;
         KbMs->mouseEventDown(LOWORD(lParam),HIWORD(lParam));
         break;

    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
        KbMs->mouseEventUp();
        break;

    case WM_MOUSEMOVE:
         KbMs->wParam = wParam;
         KbMs->mouseMove(cam, (double) LOWORD(lParam), (double) HIWORD(lParam));
         break;
    case WM_MOUSEWHEEL:

       break;
    }
}

