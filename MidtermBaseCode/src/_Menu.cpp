#include "_Menu.h"

_Menu::_Menu()
{
    //ctor
}

_Menu::~_Menu()
{
    //dtor
}

void _Menu::initMenu(char* fileName)
{
    mainMenu->loadTexture(fileName);

}

void _Menu::drawMenu(float width, float height,_Camera* cam)
{
    gluLookAt(cam->eye.x,cam->eye.y,cam->eye.z,cam->eye.x,cam->eye.y,cam->eye.z-1,cam->upVec.x,cam->upVec.y,cam->upVec.z);
    mainMenu->bindTexture();
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
     glTexCoord2f(0,0);glVertex3f((-width/height)+cam->eye.x,cam->eye.y+1,cam->eye.z-2);
     glTexCoord2f(1,0);glVertex3f(width/height+cam->eye.x,cam->eye.y+1,cam->eye.z-2);
     glTexCoord2f(1,1);glVertex3f(width/height+cam->eye.x,cam->eye.y-1,cam->eye.z-2);
     glTexCoord2f(0,1);glVertex3f(-width/height+cam->eye.x,cam->eye.y-1.0,cam->eye.z-2);
    glEnd();
    glEnable(GL_LIGHTING);
}
