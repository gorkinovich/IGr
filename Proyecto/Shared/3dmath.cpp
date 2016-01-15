//******************************************************************************************
// Anubis Editor 1.0 - A 3D Adventure Game Engine.
// Copyright (C) 2006-2007  Gorka Suárez García
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//******************************************************************************************
#include "3dmath.h"
//******************************************************************************************
// Funciones para vectores 2D.
//******************************************************************************************
float Vec2Magnitude (const GLfloat * v)
{
	return (float) sqrt(v[0] * v[0] + v[1] * v[1]);
}
//------------------------------------------------------------------------------------------
void Vec2Normalize (GLfloat * n, const GLfloat * v)
{
	float mag = Vec2Magnitude(v);
	    
    if(mag != 0.0f)
    {
    	n[0] = v[0] / mag;
	    n[1] = v[1] / mag;
    }
}
//------------------------------------------------------------------------------------------
float Vec2Dot (const GLfloat * a, const GLfloat * b)
{
	return a[0] * b[0] + a[1] * b[1];
}
//------------------------------------------------------------------------------------------
void Vec2Cross (GLfloat * r, const GLfloat * a, const GLfloat * b)
{
	r[0] = 0;
	r[1] = 0;
	r[2] = a[0] * b[1] - a[1] * b[0];
}
//------------------------------------------------------------------------------------------
void Vec2Mul (GLfloat * r, const GLfloat * a, const GLfloat s)
{
	r[0] = a[0] * s;
	r[1] = a[1] * s;
}
//------------------------------------------------------------------------------------------
void Vec2Mul (GLfloat * r, const GLfloat * a, const GLfloat * b)
{
	r[0] = a[0] * b[0];
	r[1] = a[1] * b[1];
}
//------------------------------------------------------------------------------------------
void Vec2Add (GLfloat * r, const GLfloat * a, const GLfloat * b)
{
	r[0] = a[0] + b[0];
	r[1] = a[1] + b[1];
}
//------------------------------------------------------------------------------------------
void Vec2Sub (GLfloat * r, const GLfloat * a, const GLfloat * b)
{
	r[0] = a[0] - b[0];
	r[1] = a[1] - b[1];
}
//------------------------------------------------------------------------------------------
bool Vec2Equal (const GLfloat * a, const GLfloat * b)
{
	return (a[0] == b[0]) && (a[1] == b[1]);
}
//******************************************************************************************
// Funciones para vectores 3D.
//******************************************************************************************
float Vec3Magnitude (const GLfloat * v)
{
	return (float) sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}
//------------------------------------------------------------------------------------------
void Vec3Normalize (GLfloat * n, const GLfloat * v)
{
	float mag = Vec3Magnitude(v);

    if(mag != 0.0f)
    {
	    n[0] = v[0] / mag;
    	n[1] = v[1] / mag;
	    n[2] = v[2] / mag;
    }
}
//------------------------------------------------------------------------------------------
float Vec3Dot (const GLfloat * a, const GLfloat * b)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}
//------------------------------------------------------------------------------------------
void Vec3Cross (GLfloat * r, const GLfloat * a, const GLfloat * b)
{
	r[0] = a[1] * b[2] - a[2] * b[1];
	r[1] = a[2] * b[0] - a[0] * b[2];
	r[2] = a[0] * b[1] - a[1] * b[0];
}
//------------------------------------------------------------------------------------------
void Vec3Mul (GLfloat * r, const GLfloat * a, const GLfloat s)
{
	r[0] = a[0] * s;
	r[1] = a[1] * s;
	r[2] = a[2] * s;
}
//------------------------------------------------------------------------------------------
void Vec3Mul (GLfloat * r, const GLfloat * a, const GLfloat * b)
{
	r[0] = a[0] * b[0];
	r[1] = a[1] * b[1];
	r[2] = a[2] * b[2];
}
//------------------------------------------------------------------------------------------
void Vec3Add (GLfloat * r, const GLfloat * a, const GLfloat * b)
{
	r[0] = a[0] + b[0];
	r[1] = a[1] + b[1];
	r[2] = a[2] + b[2];
}
//------------------------------------------------------------------------------------------
void Vec3Sub (GLfloat * r, const GLfloat * a, const GLfloat * b)
{
	r[0] = a[0] - b[0];
	r[1] = a[1] - b[1];
	r[2] = a[2] - b[2];
}
//------------------------------------------------------------------------------------------
bool Vec3Equal (const GLfloat * a, const GLfloat * b)
{
	return (a[0] == b[0]) && (a[1] == b[1]) && (a[2] == b[2]);
}
//******************************************************************************************
// 3dmath.cpp
//******************************************************************************************