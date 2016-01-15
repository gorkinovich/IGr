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
#ifndef _ANUBIS_CONTENT_H_
#define _ANUBIS_CONTENT_H_
//******************************************************************************************
// Includes.
//******************************************************************************************
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
//------------------------------------------------------------------------------------------
#include <gl/gl.h>
#include <gl/glu.h>
//------------------------------------------------------------------------------------------
#include <iostream>
#include <list>
#include <string>
//------------------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------------------
#include "error.h"
#include "extensions.h"
#include "textures.h"
//******************************************************************************************
// Clase para almacenar y gestionar multiples contenidos.
//******************************************************************************************
class CContentManager
{
//------------------------------------------------------------------------------------------
// Parte privada.
//------------------------------------------------------------------------------------------
private:
	CContentManager ();

	static CContentManager * Instance;

//------------------------------------------------------------------------------------------
// Parte protegida.
//------------------------------------------------------------------------------------------
protected:
	list<CImage *>   Images;
	list<CTexture *> Textures;

	CImage   * SearchImage   (const char * name);
	CTexture * SearchTexture (const char * name);

//------------------------------------------------------------------------------------------
// Parte publica.
//------------------------------------------------------------------------------------------
public:
	//--------------------------------------------------------------------------------------
	// Constructores y funciones de copia.
	//--------------------------------------------------------------------------------------
	~CContentManager ();
	
	//--------------------------------------------------------------------------------------
	// Lógica.
	//--------------------------------------------------------------------------------------
	void ReleaseImage   (const char * name);
	void ReleaseTexture (const char * name);

	void ReleaseAllImages   (void);
	void ReleaseAllTextures (void);

	void ReleaseAll (void);
	
	//--------------------------------------------------------------------------------------
	// Gets.
	//--------------------------------------------------------------------------------------
	bool IsImageLoaded   (const char * name);
	bool IsTextureLoaded (const char * name);

	CImage * GetImage (const char * name);
	CImage * GetImage (unsigned int index);

	CTexture * GetTexture (const char * name);
	CTexture * GetTexture (unsigned int index);

	int GetNumImages   (void);
	int GetNumTextures (void);

	static CContentManager * GetInstance (void);
};
//******************************************************************************************
#endif
//******************************************************************************************
// content.h
//******************************************************************************************