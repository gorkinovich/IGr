//******************************************************************************************
// Yukino 2.0 - A 3D game library.
// Copyright (C) 2006  Gorka Suárez García
// 
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//******************************************************************************************
#ifndef _YUKINO_BASE_H_
#define _YUKINO_BASE_H_
//******************************************************************************************
// Includes
//******************************************************************************************
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
//------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <vector>
#include <list>
//------------------------------------------------------------------------------------------
using namespace std;
//******************************************************************************************
// Macros
//******************************************************************************************
/*#ifndef YUKINO_STATIC
	#ifndef YUKINO_EXPORTS // The VC++ defines this constant in the proyect settings.
		#define DLLAPI __declspec (dllimport) // Import the functions from the dll.
	#else
		#define DLLAPI __declspec (dllexport) // Export the functions to the dll.
	#endif
#else*/
	#define DLLAPI
/*#endif*/
//******************************************************************************************
// Constantes
//******************************************************************************************
#define WINMODE_INCW   8
#define WINMODE_INCH  27
#define WINMODE_FIXED  2
//------------------------------------------------------------------------------------------
#define PI 3.14159265f
//******************************************************************************************
#endif
//******************************************************************************************
// Base.h
//******************************************************************************************
