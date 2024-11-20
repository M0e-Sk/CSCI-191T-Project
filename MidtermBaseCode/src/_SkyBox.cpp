#include "_SkyBox.h"

_SkyBox::_SkyBox()
{
    //ctor
}

_SkyBox::~_SkyBox()
{
    //dtor
}
void _SkyBox::skyBoxInit()
{
    skyTex[0].loadTexture("images/front.jpg");
    skyTex[1].loadTexture("images/back.jpg");
    skyTex[2].loadTexture("images/top.jpg");
    skyTex[3].loadTexture("images/bottom.jpg");
    skyTex[4].loadTexture("images/left.jpg");
    skyTex[5].loadTexture("images/right.jpg");

    xMin=yMin =0.0;
    xMax=yMax=1.0;
    xRotation=0; yRotation=0;zRotation=0;
    xTranslate=0; yTranslate=0;zTranslate=0;
}

void _SkyBox::drawSkyBox()
{
    glDisable(GL_LIGHTING);
     glTranslatef(xTranslate,yTranslate,zTranslate);
     glRotatef(xRotation,1,0,0);
     glRotatef(yRotation,0,1,0);
     glRotatef(zRotation,0,0,1);

     skyTex[0].bindTexture(); //Front Wall
     glBegin(GL_QUADS);
     glTexCoord2f(xMin,yMin);glVertex3f(-1.0,1.0,1.0);
     glTexCoord2f(xMax,yMin);glVertex3f( 1.0,1.0,1.0);
     glTexCoord2f(xMax,yMax);glVertex3f( 1.0,-1.0,1.0);
     glTexCoord2f(xMin,yMax);glVertex3f(-1.0,-1.0,1.0);
     glEnd();

     skyTex[1].bindTexture(); // Back Wall
     glBegin(GL_QUADS);
     glTexCoord2f(xMin,yMax);glVertex3f(1.0,-1.0,-1.0);
     glTexCoord2f(xMax,yMax);glVertex3f( -1.0,-1.0,-1.0);
     glTexCoord2f(xMax,yMin);glVertex3f( -1.0,1.0,-1.0);
     glTexCoord2f(xMin,yMin);glVertex3f(1.0,1.0,-1.0);
     glEnd();


     skyTex[5].bindTexture();  //left Wall
     glBegin(GL_QUADS);
     glTexCoord2f(xMin,yMin);glVertex3f(-1.0,1.0,-1.0);
     glTexCoord2f(xMax,yMin);glVertex3f(-1.0,1.0,1.0);
     glTexCoord2f(xMax,yMax);glVertex3f(-1.0,-1.0,1.0);
     glTexCoord2f(xMin,yMax);glVertex3f(-1.0,-1.0,-1.0);
     glEnd();

     skyTex[4].bindTexture(); //Right Wall
     glBegin(GL_QUADS);
    glTexCoord2f(xMax,yMin);glVertex3f( 1.0,1.0,-1.0);
     glTexCoord2f(xMax,yMax);glVertex3f( 1.0,-1.0,-1.0);
     glTexCoord2f(xMin,yMax);glVertex3f( 1.0,-1.0,1.0);
     glTexCoord2f(xMin,yMin);glVertex3f( 1.0,1.0,1.0);
     glEnd();

    skyTex[2].bindTexture();  //Top Wall
     glBegin(GL_QUADS);
     glTexCoord2f(xMin,yMax);glVertex3f(1.0,1.0,-1.0);
     glTexCoord2f(xMin,yMin);glVertex3f(1.0,1.0,1.0);
     glTexCoord2f(xMax,yMin);glVertex3f(-1.0,1.0,1.0);
     glTexCoord2f(xMax,yMax);glVertex3f(-1.0,1.0,-1.0);
     glEnd();

     skyTex[3].bindTexture();
     glBegin(GL_QUADS);
     glTexCoord2f(xMax,yMax);glVertex3f( -1.0,-1.0,1.0);
     glTexCoord2f(xMin,yMax);glVertex3f( 1.0,-1.0,1.0);
     glTexCoord2f(xMin,yMin);glVertex3f( 1.0,-1.0,-1.0);
     glTexCoord2f(xMax,yMin);glVertex3f( -1.0,-1.0,- 1.0);
     glEnd();


     glEnable(GL_LIGHTING);
}
