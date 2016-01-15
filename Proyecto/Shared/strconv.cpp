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
#include "strconv.h"
//******************************************************************************************
// Funciones para convertir cadenas en datos.
//******************************************************************************************
bool GetRGBAFromString (const char * str, GLfloat * vector)
{
    int r, g, b, a;

    if(sscanf(str, "%d, %d, %d, %d", &r, &g, &b, &a) == 4)
	{
		vector[0] = ((float) r) / 255.0f;
		vector[1] = ((float) g) / 255.0f;
		vector[2] = ((float) b) / 255.0f;
		vector[3] = ((float) a) / 255.0f;
		return true;
	}
	else
	{
		return false;
	}
}
//------------------------------------------------------------------------------------------
bool GetVec4FromString (const char * str, GLfloat * vector)
{
    GLfloat x, y, z, w;

    if(sscanf(str, "%f, %f, %f, %f", &x, &y, &z, &w) == 4)
	{
		vector[0] = x;
		vector[1] = y;
		vector[2] = z;
		vector[3] = w;
		return true;
	}
	else
	{
		return false;
	}
}
//------------------------------------------------------------------------------------------
bool GetVec3FromString (const char * str, GLfloat * vector)
{
    GLfloat x, y, z;

    if(sscanf(str, "%f, %f, %f", &x, &y, &z) == 3)
	{
		vector[0] = x;
		vector[1] = y;
		vector[2] = z;
		return true;
	}
	else
	{
		return false;
	}
}
//------------------------------------------------------------------------------------------
bool GetFloatFromString (const char * str, GLfloat * vector)
{
    GLfloat value;

    if(sscanf(str, "%f", &value) == 0)
	{
		return false;
	}
	else
	{
		vector[0] = value;
		return true;
	}
}        
//------------------------------------------------------------------------------------------
bool GetColorFromString (const char * str, GLfloat * vector)
{  
    int value;

    if(sscanf(str, "%d", &value) == 0)
	{
		return false;
	}
	else
	{
		vector[0] = ((float) value) / 255.0f;
		return true;
	}
}
//******************************************************************************************
// strconv.cpp
//******************************************************************************************