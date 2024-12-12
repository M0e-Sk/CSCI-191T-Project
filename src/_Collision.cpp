#include "_Collision.h"

_Collision::_Collision()
{
    //ctor
}

_Collision::~_Collision()
{
    //dtor
}
bool _Collision::isLinearCollision(vec2, vec2)
{

}

bool _Collision::isRadialCollision(vec3 p1, vec3 p2, float r1, float r2, float threshold)
{
    return(abs((r1+r2)-sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2)))<threshold);
}

bool _Collision::isHitPlane(vec2, vec2)
{

}

bool _Collision::isCubicCollision(vec3 b1, vec3 b2,float h1,float h2,float w1,float w2,float l1,float l2)//inputs should be half of object length
{
 return((abs(b1.x-b2.x)<l1+l2)&&(abs(b1.y-b2.y)<h1+h2)&&(abs(b1.z-b2.z)<w1+w2));
}

bool _Collision::isSphereCollision(vec3 p1, vec3 p2, float r1, float r2, float threshold)
{
      return(abs((r1+r2)-sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2)+pow(p1.z-p2.z,2)))<threshold);
}

bool _Collision::isHitplanr3D(vec3, vec3)
{

}
