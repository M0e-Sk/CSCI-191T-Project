#include "_Models.h"

_Models::_Models()
{
    //ctor

    rotateX =0.0;
    rotateY =0.0;
    rotateZ =0.0;

    pos.x    =0.0;
    pos.y    =30.0;
    pos.z    =-80.0;

    color.r = 1;color.g = color.b =0.0;

    myTime->startTime = clock();
}

_Models::~_Models()
{
    //dtor
}
GLvoid _Models::initModel(char* fileName)
{
    myTex->loadTexture(fileName);
}


GLvoid _Models::drawModel()
{
    glColor3f(color.r,color.g,color.b);
    glTranslatef(pos.x,pos.y,pos.z);

    glRotatef(rotateX,1,0,0);
    glRotatef(rotateY,0,1,0);
    glRotatef(rotateZ,0,0,1);

    myTex->bindTexture();
    glutSolidTeapot(1.5);
}

GLvoid _Models::moveModel()
{
      if(clock()-myTime->startTime >30){
    pos.x <-40?dir=1:(pos.x>40?dir=-1:NULL);
    pos.x +=dir*0.2;
    myTime->startTime = clock();
      }
}
