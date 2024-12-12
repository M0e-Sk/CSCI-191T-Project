#include "_lightSetup.h"

_lightSetup::_lightSetup()
{
    //ctor
}

_lightSetup::~_lightSetup()
{
    //dtor
}

GLvoid _lightSetup::setLight(GLenum light)
{

   glEnable(light);
   glEnable(GL_LIGHTING);

   light_ambient[0]=0;  // Environment
   light_ambient[1]=0;  // Environment
   light_ambient[2]=0;  // Environment
   light_ambient[3]=1;  // Environment


   light_diffuse[0]=1;  // For shade
   light_diffuse[1]=1;  // For shade
   light_diffuse[2]=1;  // For shade
   light_diffuse[3]=1;  // For shade

   light_specular[0]=1; // To shine
   light_specular[1]=1; // To shine
   light_specular[2]=1; // To shine
   light_specular[3]=1; // To shine

   light_position[0]=2; // Light Possition
   light_position[1]=5; // Light Possition
   light_position[2]=5; // Light Possition
   light_position[3]=1; // Light Possition

    mat_ambient[0]= 0.7;    // material values
    mat_ambient[1]= 0.7;    // material values
    mat_ambient[2]= 0.7;    // material values
    mat_ambient[3]= 1.0;    // material values

    mat_diffuse[0]= 0.8;
    mat_diffuse[1]= 0.8;
    mat_diffuse[2]= 0.8;
    mat_diffuse[3]= 1.0;

    mat_specular[0]=1;
    mat_specular[1]=1;
    mat_specular[2]=1;
    mat_specular[3]=1;

    high_shininess[1]=100.0;
}

GLvoid _lightSetup::movingLight(GLenum light)
{
        spin+=0.5;         // spining my lioght
   	    glPushMatrix(); // start groupinhg
		  glRotated(spin,0,1,0); // rotate around y axis
		  glLightfv(light, GL_POSITION, light_position);// change light position
		glPopMatrix();  // end of grouping
}
