#include "_Bullets.h"

_Bullets::_Bullets()
{
    //ctor
}

_Bullets::~_Bullets()
{
    //dtor
}
void _Bullets::initBullet(char* fileName)
{
   pos.x =0;
   pos.y =0;
   pos.z =0;
   t=0;
   lifetime = 100.0f;

   des.x =0;
   des.y = 20;
   des.z =-50;

   src.x =0;
   src.y =0;
   src.z =0;

   actionTrigger = READY;

   speed = 0.5f;

   live =false;
}

void _Bullets::drawBullet()
{
     glDisable(GL_TEXTURE_2D);
     glPushMatrix();
     if(live)
     {
     glTranslatef(pos.x,pos.y,pos.z);
     glutSolidSphere(0.1,20,20);
     }
     glPopMatrix();
     glEnable(GL_TEXTURE_2D);
}
void _Bullets::bulletAction()
{
    switch(actionTrigger)
    {
        case READY:
            pos.x =0;
            pos.y=0;
            pos.z=0;

            src.x =0;
            src.y= 0;
            src.z =0;

            live = false;
            t=0;
            break;

        case DEAD:
                  live = false;
                  t=0;
                  actionTrigger = 0;
            break;
        case SHOOT:
              if(live)
              {
              if(clock()-myTime->startTime>10)
              {
              if(t>=lifetime) {actionTrigger = DEAD;}
              else
			  {
				pos = pos + (des.norm() * speed);
				t+=0.1f;
              }
              myTime->startTime = clock();
              }
              }
            break;
        case HIT:
            // use this to show explosion any other action
            break;
    }
}
