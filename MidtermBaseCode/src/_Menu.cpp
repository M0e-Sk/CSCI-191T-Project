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

void _Menu::drawMenu()
{
	mainMenu->bindTexture();
    glBegin(GL_QUADS);
     glTexCoord2f(0,0);glVertex3f(-5.0,5.0,1.0);
     glTexCoord2f(1,0);glVertex3f( 5.0,5.0,1.0);
     glTexCoord2f(1,1);glVertex3f( 5.0,-5.0,1.0);
     glTexCoord2f(0,1);glVertex3f(-5.0,-5.0,1.0);
    glEnd();
}
