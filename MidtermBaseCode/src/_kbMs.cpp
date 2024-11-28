#include "_KbMs.h"

_KbMs::_KbMs()
{
    //ctor

    prev_MouseX=0;
    prev_MouseY=0;

    prev_MouseX_Cam=0;
    prev_MouseY_Cam=0;

    mouseTranslation= false;
    mouseRotation = false;

    firstMouse = true;
}

_KbMs::~_KbMs()
{
    //dtor
}
void _KbMs::keyPress(_Models* model)
{
    switch(wParam)
    {
    case VK_LEFT:
          model->rotateY +=1.0;
          break;

     case VK_RIGHT:
          model->rotateY -=1.0;
          break;

          //todo

          //VK_DOWN
          //VK_UP

          // do z rotations
    }
}

void _KbMs::keyUp()
{
    switch(wParam)
    {
        default: break;
    }

}



void _KbMs::moveBck(_parallax* prlx, float speed)
{
     switch(wParam)
    {
    case VK_LEFT:
          prlx->xMax -= speed;
          prlx->xMin -=speed;
         break;

     case VK_RIGHT:
          prlx->xMin +=speed;
           prlx->xMax += speed;
          break;
    }
}

void _KbMs::keyPress(_SkyBox* sky)
{
     switch(wParam)
    {
    case VK_LEFT:
          sky->yRotation +=0.2;
          break;

     case VK_RIGHT:
          sky->yRotation-=0.2;
          break;

          //todo

     case VK_DOWN:
          sky->xRotation +=0.2;
          break;

     case VK_UP:
          sky->xRotation -=0.2;
          break;

          // do z rotations
    }
}
void _KbMs::keyPress(_2DPlayer* pls)
{
    switch(wParam)
    {
    case VK_LEFT:
           pls->actionTrigger= pls->WALKLEFT;
          break;

     case VK_RIGHT:
             pls->actionTrigger= pls->WALKRIGHT;
          break;

          //todo

     case VK_DOWN:

          break;

     case VK_UP:

          break;

}
}
void _KbMs::keyUp(_2DPlayer* pl)
{
    pl->actionTrigger = pl->STAND;
}




void _KbMs::keyPress(_Skybox2* sky)
{
       switch(wParam)
    {
    case VK_LEFT:
          sky->rot.y +=1.0;
          break;

     case VK_RIGHT:
          sky->rot.y-=1.0;
          break;

          //todo

     case VK_DOWN:
          sky->rot.x +=1.0;
          break;

     case VK_UP:
          sky->rot.x -=1.0;
          break;
    }
}


void _KbMs::keyPress(_Camera* cam)
{
       switch(wParam)
    {
    case 	0x41:  // pressed key 'A'
          cam->actionTrigger = cam->LEFT;
          break;

     case 0x44: // press key 'D'
          cam->actionTrigger = cam->RIGHT;
          break;

          //todo

     case 0x53: // press key 'S'
        cam->actionTrigger = cam->BACK;
        break;

     case 0x57:  // press key 'W'

         cam->actionTrigger = cam->FORWARD;
         break;
	 case VK_LEFT:
		cam->thetaX += 0.5f;
		break;
	 case VK_RIGHT:
		cam->thetaX -= 0.5f;
		break;
    }

}

void _KbMs::keyPress(_ModelLoaderMD2* MD2)
{
     switch(wParam)
    {
    case VK_LEFT:
           MD2->actionTrigger= MD2->RUN;
           MD2->dirAngleZ = 180;
          break;

     case VK_RIGHT:
            MD2->actionTrigger= MD2->RUN;
            MD2->dirAngleZ = 0;
          break;

          //todo

     case VK_DOWN:
           MD2->actionTrigger= MD2->CRSTAND;
          break;

     case VK_UP:
            MD2->actionTrigger= MD2->JUMP;
          break;

     case VK_SPACE:
           MD2->actionTrigger= MD2->ATTACK;
           break;

}
}
void _KbMs::keyUp(_ModelLoaderMD2* MD2)
{
    MD2->actionTrigger = MD2->STAND;
}

void _KbMs::keyUp(_Camera* cam)
{
	cam->actionTrigger = cam->IDLE;
}



/******************************************************************/

void _KbMs::mouseMove(_SkyBox* sky, double x, double y)
{

}


void _KbMs::mouseMove(_Skybox2*, double, double)
{

}

void _KbMs::mouseEventDown(double x, double y)
{
    prev_MouseX =x;
    prev_MouseY =y;

    switch(wParam)
    {
   case MK_LBUTTON:  // set translation flag
         mouseTranslation = true;
        break;
   case MK_RBUTTON:   // set rotation flag
         mouseRotation =true;
         break;

   case MK_MBUTTON:
         break;
    }
}

void _KbMs::mouseEventUp()
{
     mouseRotation = false;
     mouseTranslation =false;
}

void _KbMs::mouseWheel(_Models* mdl, double delta)
{
   mdl->pos.z +=delta/100;
}

void _KbMs::mouseMove(_Models*mdl, double x, double y)
{
  if(mouseTranslation)
  {
      mdl->pos.x += (x-prev_MouseX)/100.0;
      mdl->pos.y -=  (y-prev_MouseY)/100.0;
  }
   // To do
   // apply for rotation

      prev_MouseX = x;
      prev_MouseY =y;
}

void _KbMs::mouseMove(_Camera* cam, double x, double y)
{

	if(firstMouse)
	{
		prev_MouseX_Cam = x;
		prev_MouseY_Cam = y;
		firstMouse = false;
	} else {
     cam->thetaX -=  ( x-prev_MouseX_Cam)/3.0;
     cam->thetaY -=  ( y-prev_MouseY_Cam)/3.0;

   // To do
   // apply for rotation

      prev_MouseX_Cam = x;
      prev_MouseY_Cam =y;
	}
}

