//******************************************************************************************
// Anubis Editor 1.0 - A 3D Adventure Game Engine.
// Copyright (C) 2006-2007  Gorka Su�rez Garc�a
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
#ifndef _ANUBIS_COLOR_H_
#define _ANUBIS_COLOR_H_
//******************************************************************************************
// Includes.
//******************************************************************************************
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl/gl.h>
//******************************************************************************************
// Funciones auxiliares para la conversi�n de los colores.
//******************************************************************************************
inline GLfloat ColorIntToFloat (int value)
{
	return ((float) value) / 255.0f;
}
//------------------------------------------------------------------------------------------
inline int ColorFloatToInt (GLfloat value)
{
	return (int) (value * 255.0f);
}
//******************************************************************************************
#endif
//******************************************************************************************
// color.h
//******************************************************************************************