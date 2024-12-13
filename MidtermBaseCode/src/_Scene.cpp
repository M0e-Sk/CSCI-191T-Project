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
#include<_models.h>
#include<_Enemy.h>
#include<_Runner.h>
#include<_Blitzer.h>
#include<_Boss.h>
#include<_Menu.h>
#include<_Sounds.h>

_lightSetup *myLight = new _lightSetup();
_KbMs *KbMs = new _KbMs();
_parallax *aplx;
_parallax *plx = new _parallax();
_parallax *plx2 = new _parallax();
_parallax *plx3 = new _parallax();
_Skybox2 *asky;
_Skybox2 *sky = new _Skybox2();
_Skybox2 *sky2 = new _Skybox2();
_Skybox2 *sky3 = new _Skybox2();
_Camera *cam = new _Camera();
_Bullets b[20];
_ModelLoaderMD2 *gun = new _ModelLoaderMD2();
_Collision *col = new _Collision();
_Enemy* e[5];
_Menu *mainMenu = new _Menu();
_Menu *pauseMenu = new _Menu();
_Menu *helpMenu = new _Menu();
_Sounds *snds = new _Sounds();

int maxEnemies;
int playerHealth = 10;

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

     plx->parallaxInit("images/forestfloor.jpg");
     plx2->parallaxInit("images/mansionfloor.jpg");
     plx3->parallaxInit("images/cellarfloor.jpg");
     sky->skyBoxinit("images/forest.png");
     sky2->skyBoxinit("images/mansion.png");
     sky3->skyBoxinit("images/cellar.png");
     cam->camInit();
     for(int i = 0; i < 20; i++)
		b[i].initBullet("file");

	gun->initModel("models/GIJOE/weapon.md2", "models/GIJOE/weapon.jpg", cam->eye);
	gun->pos.y -= 1.0f;
	gun->dirAngleZ = 75.0f;
	gun->dirAngleY = 35.0f;
	gun->scale = 0.08f;
	gun->actionTrigger = gun->IDLE;
    mainMenu->initMenu("images/startMenu.png");

    pauseMenu->initMenu("images/pauseMenu.jpg");
    helpMenu->initMenu("images/Controls2.png");


    snds->initSounds();
	snds->playMusic("sounds/Luigi Theme.mp3");
    return true;
}

GLint _Scene::loadLevel1()
{
	asky = sky;
	aplx = plx;
	maxEnemies = 3;
	cam->camInit();
	for(int i = 0; i < maxEnemies; i++)
	{
	e[i] = new _Runner();
	float x = (rand() % 40) - 20;
	float z = (rand() % 40) - 20;
	if(x <= 10.0f && x >= -10.0f) x > 0.0f ? x = 10.0f : x = -10.0f;
	if(z <= 10.0f && z >= -10.0f) z > 0.0f ? z = 10.0f : z = -10.0f;
	e[i]->init("models/corpse/tris.md2", "models/corpse/base.jpg", vec3{x, 0.0f, z});
	e[i]->des = e[i]->model->pos;
	e[i]->dir = vec3{-0.5f,0.0f,-0.5f};
	e[i]->model->dirAngleZ = acos(e[i]->dir.dot(vec3{1.0f,0.0f,0.0f})) * (180.0f/PI);
	if(e[i]->dir.z > 0.0f) e[i]->model->dirAngleZ = 360 - e[i]->model->dirAngleZ;
	e[i]->plPos = cam->eye;
	e[i]->snds = snds;
	}
	gun->pos.y = cam->eye.y - 1.0f;
	gun->dirAngleZ = 75.0f;
	gun->dirAngleY = 35.0f;
	gun->actionTrigger = gun->IDLE;
	currLevel =1;
	return true;
}

GLint _Scene::loadLevel2()
{
	snds->stopSounds();
	asky = sky2;
	aplx = plx2;
	cam->camInit();
	for(int i = 0; i < maxEnemies; i++)
	{
		delete e[i];
	}
	maxEnemies =5;
	for(int i = 0; i < 4; i++)
	{
		e[i] = new _Runner();
		float x = (rand() % 40) - 20;
		float z = (rand() % 40) - 20;
		if(x <= 10.0f && x >= -10.0f) x > 0.0f ? x = 10.0f : x = -10.0f;
		if(z <= 10.0f && z >= -10.0f) z > 0.0f ? z = 10.0f : z = -10.0f;
		e[i]->init("models/corpse/tris.md2", "models/corpse/base.jpg", vec3{x, 0.0f, z});
		e[i]->des = vec3{0.0f, 0.0f, 5.0f};
		e[i]->dir = vec3{-0.5f,0.0f,-0.5f};
		e[i]->model->dirAngleZ = acos(e[i]->dir.dot(vec3{1.0f,0.0f,0.0f})) * (180.0f/PI);
		if(e[i]->dir.z > 0.0f) e[i]->model->dirAngleZ = 360 - e[i]->model->dirAngleZ;
		e[i]->plPos = cam->eye;
		e[i]->snds = snds;
	}
	for(int i = 4; i < maxEnemies; i++)
	{
		e[i] = new _Blitzer();
		float x = (rand() % 40) - 20;
		float z = (rand() % 40) - 20;
		if(x <= 10.0f && x >= -10.0f) x > 0.0f ? x = 10.0f : x = -10.0f;
		if(z <= 10.0f && z >= -10.0f) z > 0.0f ? z = 10.0f : z = -10.0f;
		e[i]->init("models/wraith/tris.md2", "models/wraith/WRAITH.jpg", vec3{x, 0.0f, z});
		e[i]->plPos = cam->eye;
		e[i]->dir = (cam->eye - e[i]->model->pos).norm();
		e[i]->des = cam->eye - e[i]->dir;
		e[i]->model->dirAngleZ = acos(e[i]->dir.dot(vec3{1.0f,0.0f,0.0f})) * (180.0f/PI);
		if(e[i]->dir.z > 0.0f) e[i]->model->dirAngleZ = 360 - e[i]->model->dirAngleZ;
		e[i]->snds = snds;
	}
	gun->pos.y = cam->eye.y - 1.0f;
	gun->dirAngleZ = 75.0f;
	gun->dirAngleY = 35.0f;
	gun->actionTrigger = gun->IDLE;
	currLevel = 2;
	snds->playMusic("sounds/Theme2.mp3");
	return true;
}

GLint _Scene::loadLevel3()
{
	snds->stopSounds();
	asky = sky3;
	aplx = plx3;
	for(int i = 0; i < maxEnemies; i++)
	{
		delete e[i];
	}
	maxEnemies = 1;
	cam->camInit();
	e[0] = new _Boss();
	e[0]->init("models/doomunls/tris.md2", "models/doomunls/red.jpg", vec3{0.0f, 3.0f, -30.0f});
	e[0]->snds = snds;
	gun->pos.y = cam->eye.y - 1.0f;
	gun->dirAngleZ = 75.0f;
	gun->dirAngleY = 35.0f;
	gun->actionTrigger = gun->IDLE;
	currLevel = 3;
	snds->playMusic("sounds/Theme3.mp3");
	return true;
}

GLint _Scene::drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();   // clearing matrices


    wireFrame?glPolygonMode(GL_FRONT_AND_BACK, GL_LINE):glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	static double curent_time = 0;
	static double last_time = 0;

	last_time = curent_time;
	curent_time = (double)glutGet (GLUT_ELAPSED_TIME) / 1000.0;

	if(status!=HELP){
        previousStatus=status;
	}
	switch(status){
	    case MAIN:
    //menu draw
        ShowCursor(TRUE);
        mainMenu->drawMenu(screenWidth, screenHeight, cam);
        break;
        case HELP:
            ShowCursor(TRUE);
            helpMenu->drawMenu(screenWidth,screenHeight,cam);
            break;
        case PAUSE:
			    \
				ShowCursor(TRUE);
				pauseMenu->drawMenu(screenWidth, screenHeight, cam);
				break;
        case PLAY:
    cam->setUpCam();
    if(playerHealth <= 0)
	{
		cam->eye = cam->eye - vec3{0.0f,0.1f,0.0f};
		if(cam->eye.y < -1.0f) cam->eye.y = -1.0f;
	}
    ShowCursor(FALSE);
    glPushMatrix();
    glPopMatrix();

      glPushMatrix();
      glTranslatef(0,-10,1);
      glRotatef(90,1,0,0);

      glScalef(200,200,1.0);
      aplx->parallaxDraw(1,1);

      glPopMatrix();

      for(int i = 0; i < 20; i++)
      {
		b[i].drawBullet();
		for(int j = 0; j < maxEnemies; j++){
			if(col->isCubicCollision(e[j]->model->pos, b[i].pos, e[j]->width, 0.1f,e[j]->height, 0.1f, e[j]->depth, 0.1f) && b[i].live)
			{
				if(e[j]->live) {
				e[j]->health -= 1;
				if(e[j]->health <= 0)
				{
					e[j]->behavior = e[j]->DYING;
					snds->playSound("sounds/DeathVoice.wav");
				}
				else {
					if(e[j]->behavior == e[j]->TAUNT)
					{
						e[j]->stunCnt++;
					}else if(currLevel !=3){
					e[j]->behavior = e[j]->HURT;
					e[j]->dir = (e[j]->model->pos - e[j]->plPos).norm();
					}
					snds->playSound("sounds/GruntVoice01.wav");
				}
				b[i].actionTrigger = b[i].DEAD;
				}
			}
		}
		b[i].bulletAction();
      }

      glPushMatrix();
      gun->pos = cam->eye;
      gun->actions();
      gun->Draw(curent_time, last_time);
      glPopMatrix();

      for(int i = 0; i < maxEnemies; i++) {
      glPushMatrix();
      e[i]->plPos = cam->eye;
      if(playerHealth > 0)
		e[i]->Actions(&playerHealth);
      e[i]->Draw(curent_time, last_time);
      glPopMatrix();
      }

      glPushMatrix();
		asky->skyBoxDraw();
      glPopMatrix();

	  int enemiesLeft = maxEnemies;
	  for(int i = 0; i < maxEnemies; i++)
	  {
	  	e[i]->live ? NULL : enemiesLeft--;
	  }
	  if(enemiesLeft <= 0)
	  {
	  	switch(currLevel)
	  	{
		case 1:
			loadLevel2();
			break;
		case 2:
			loadLevel3();
			break;
		case 3:
			delete e[0];
			status=0;
			ShowCursor(TRUE);
			cam->camInit();
			glDisable(GL_LIGHTING);
			snds->stopSounds();
			snds->playMusic("sounds/Luigi Theme.mp3");
	  	}
	  }
	  break;

	}//switch statement
    return true;
}

GLvoid _Scene::resizeScene(GLsizei width, GLsizei height)
{
    GLfloat aspectRatio = (GLfloat)width/height;

    KbMs->screenWidth = width;
    KbMs->screenHeight = height;

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
         if(playerHealth > 0) {
         KbMs->keyPress(cam);
         if(gun->actionTrigger == gun->ATTACK)
		 {
			gun->dirAngleY += 25;
			gun->dirAngleZ -= 25;
		 }
         gun->actionTrigger = gun->RUN;
         }
         else {
			status=MAIN;
			ShowCursor(TRUE);
			snds->stopSounds();
			snds->playMusic("sounds/Luigi Theme.mp3");
			playerHealth = 10;
         }
         if(KbMs->pausePress()&&status==3)
		 {
		 	status=2;
		 }
         break;

    case WM_KEYUP:
         KbMs->wParam = wParam;
         KbMs->keyUp();
        KbMs->keyUp(cam);
         if(gun->actionTrigger == gun->ATTACK)
		 {
			gun->dirAngleY += 25;
			gun->dirAngleZ -= 25;
		 }
        gun->actionTrigger = gun->IDLE;
         break;

    case WM_LBUTTONDOWN:
         KbMs->wParam = wParam;

         if(playerHealth > 0)
		 {
         if(gun->actionTrigger != gun->ATTACK)
		 {
         gun->actionTrigger = gun->ATTACK;
         gun->dirAngleY -= 25;
         gun->dirAngleZ += 25;
		 }
		 if(status == PLAY)
		 {
		 snds->playSound("sounds/Shot.wav");
		 b[curBullet].actionTrigger = b[curBullet].SHOOT;
		 b[curBullet].live = true;
		 b[curBullet].pos = cam->eye;
		 b[curBullet].des = cam->dir;
		 curBullet = (curBullet + 1) % 20;
		 }
		 }
		 else{
			status=0;
			ShowCursor(TRUE);
			snds->stopSounds();
			snds->playMusic("sounds/Luigi Theme.mp3");
			playerHealth = 10;
		 }

         mouseMapping(LOWORD(lParam),HIWORD(lParam));
         //cout << screenWidth << " " << screenHeight << endl;
         if(status==MAIN){
          KbMs->mouseEventDown(status,(double) LOWORD(lParam), (double) HIWORD(lParam));
          if(status==PLAY) loadLevel1();
         }
         if(status==PAUSE) {
			KbMs->mouseEventDownPause(status, (double) LOWORD(lParam), (double) HIWORD(lParam));
         }
         if(KbMs->mouseEventDownHelp(status, (double) LOWORD(lParam), (double) HIWORD(lParam))){
         status=previousStatus;
         }

         KbMs->mouseEventDown(mouseX,mouseY);


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
         //cout << (double) LOWORD(lParam) << " " << (double) HIWORD(lParam) << endl;
         if(!status==MAIN){//only move camera if menu isn't active
         if(KbMs->firstMouse)
		 {
		 	KbMs->prev_MouseX = (double) LOWORD(lParam);
		 	KbMs->prev_MouseY = (double) HIWORD(lParam);
		 	KbMs->prev_MouseX_Cam = (double) LOWORD(lParam);
		 	KbMs->prev_MouseY_Cam = (double) HIWORD(lParam);
		 	KbMs->firstMouse = false;
		 }
		 else
		 {
		 	if(status==PLAY && playerHealth > 0){
			KbMs->mouseMove(cam, (double) LOWORD(lParam), (double) HIWORD(lParam));
			KbMs->mouseMove(gun, (double) LOWORD(lParam), (double) HIWORD(lParam));
			}
		 	KbMs->prev_MouseX = (double) LOWORD(lParam);
		 	KbMs->prev_MouseY = (double) HIWORD(lParam);
		 	KbMs->prev_MouseX_Cam = (double) LOWORD(lParam);
		 	KbMs->prev_MouseY_Cam = (double) HIWORD(lParam);
		 }
		 }
         break;
    case WM_MOUSEWHEEL:

       break;
    }
}

