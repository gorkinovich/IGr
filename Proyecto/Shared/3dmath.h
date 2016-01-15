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
#ifndef _ANUBIS_3DMATH_H_
#define _ANUBIS_3DMATH_H_
//******************************************************************************************
// Includes.
//******************************************************************************************
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl/gl.h>
#include <math.h>
//******************************************************************************************
// Constantes.
//******************************************************************************************
#define PI 3.1415926535897932f
//******************************************************************************************
// Funciones varias.
//******************************************************************************************
inline GLfloat RadToGra (GLfloat rad)
{
	return rad * 180.0f / PI;
}
//------------------------------------------------------------------------------------------
inline GLfloat GraToRad (GLfloat gra)
{
	return gra * PI / 180.0f;
}
//******************************************************************************************
// Funciones para vectores 2D.
//******************************************************************************************
float Vec2Magnitude (const GLfloat * v);
void  Vec2Normalize (GLfloat * n, const GLfloat * v);
float Vec2Dot       (const GLfloat * a, const GLfloat * b);
void  Vec2Cross     (GLfloat * r, const GLfloat * a, const GLfloat * b);
void  Vec2Mul       (GLfloat * r, const GLfloat * a, const GLfloat s);
void  Vec2Mul       (GLfloat * r, const GLfloat * a, const GLfloat * b);
void  Vec2Add       (GLfloat * r, const GLfloat * a, const GLfloat * b);
void  Vec2Sub       (GLfloat * r, const GLfloat * a, const GLfloat * b);
bool  Vec2Equal     (const GLfloat * a, const GLfloat * b);
//******************************************************************************************
// Funciones para vectores 3D.
//******************************************************************************************
float Vec3Magnitude (const GLfloat * v);
void  Vec3Normalize (GLfloat * n, const GLfloat * v);
float Vec3Dot       (const GLfloat * a, const GLfloat * b);
void  Vec3Cross     (GLfloat * r, const GLfloat * a, const GLfloat * b);
void  Vec3Mul       (GLfloat * r, const GLfloat * a, const GLfloat s);
void  Vec3Mul       (GLfloat * r, const GLfloat * a, const GLfloat * b);
void  Vec3Add       (GLfloat * r, const GLfloat * a, const GLfloat * b);
void  Vec3Sub       (GLfloat * r, const GLfloat * a, const GLfloat * b);
bool  Vec3Equal     (const GLfloat * a, const GLfloat * b);
//******************************************************************************************
#endif
//******************************************************************************************
// 3dmath.h
//******************************************************************************************