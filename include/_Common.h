#ifndef _COMMON_H
#define _COMMON_H

#include<string.h>

#include <stdlib.h>
#include <iostream>
#include <windows.h>	// Header File For Windows
#include <gl/gl.h>
#include <GL/glut.h>
#include <time.h>
#include <math.h>

#define PI 3.1415926

typedef struct{

    float x;
    float y;

}vec2;

struct vec3
{
	float x;
	float y;
	float z;

	vec3 operator +(vec3 a)
	{
		return {a.x + x, a.y + y, a.z + z};
	}

	vec3 operator -(vec3 a)
	{
		return {x - a.x, y - a.y, z - a.z};
	}

	float dot(vec3 a)
	{
		return (a.x * x) + (a.y * y) + (a.z * z);
	}

	vec3 operator *(float a)
	{
		return {x*a, y*a, z*a};
	}

	vec3 operator =(float a)
	{
		return {a,a,a};
	}

	vec3 cross(vec3 a)
	{
		float upX = (y*a.z) - (a.y*z);
		float upY = (z*a.x) - (a.z*x);
		float upZ = (x*a.y) - (a.x*y);
		return {upX, upY, upZ};
	}

	float length()
	{
		return sqrt((x*x) + (y*y) + (z*z));
	}

	vec3 norm()
	{
		if(length() == 0) return {0,0,0};
		return {x/length(), y/length(), z/length()};
	}
};

typedef struct{

    float r;
    float g;
    float b;
}col3;


typedef struct{

    float x;
    float y;
    float z;
    float w;
}vec4;


using namespace std;

#endif // _COMMON_H
