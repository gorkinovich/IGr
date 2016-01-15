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
#ifndef _ANUBIS_TEXTURES_H_
#define _ANUBIS_TEXTURES_H_
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
//******************************************************************************************
// Constantes.
//******************************************************************************************
#define IMAGE_TYPE_RGBA 2
#define IMAGE_TYPE_GRAY 3
//------------------------------------------------------------------------------------------
#include "texerrors.h"
//******************************************************************************************
// Clase para almacenar una imagen en la memoria.
//******************************************************************************************
class CImage
{
//------------------------------------------------------------------------------------------
// Parte protegida.
//------------------------------------------------------------------------------------------
protected:
	string Name;

	unsigned char   Type;
	unsigned int    Width;
	unsigned int    Height;
	unsigned char   Depth;
	unsigned char * Data;

	bool LoadBMPFile (const char * name);
	bool SaveBMPFile (const char * name);

	bool LoadTGAFile (const char * name);
	bool SaveTGAFile (const char * name);

//------------------------------------------------------------------------------------------
// Parte publica.
//------------------------------------------------------------------------------------------
public:
	//--------------------------------------------------------------------------------------
	// Constructores y funciones de copia.
	//--------------------------------------------------------------------------------------
	CImage ();
	CImage (const char * path);
	CImage (const CImage & obj);
	virtual ~CImage ();

	virtual CImage & operator = (const CImage & obj);
	virtual void CopyFrom (const CImage & obj);
	
	//--------------------------------------------------------------------------------------
	// Funciones para cargar, salvar y liberar la imagen.
	//--------------------------------------------------------------------------------------
	bool LoadFile (const char * path);
	bool SaveFile (const char * path);
	void Release  (void);

	//--------------------------------------------------------------------------------------
	// Gets.
	//--------------------------------------------------------------------------------------
	inline string &        GetName   (void) { return this->Name;   }
	inline unsigned char   GetType   (void) { return this->Type;   }
	inline unsigned int    GetWidth  (void) { return this->Width;  }
	inline unsigned int    GetHeight (void) { return this->Height; }
	inline unsigned char   GetDepth  (void) { return this->Depth;  }
	inline unsigned char * GetData   (void) { return this->Data;   }
};
//******************************************************************************************
// Clase para cargar una imagen como textura en la memoria de video.
//******************************************************************************************
class CTexture
{
//------------------------------------------------------------------------------------------
// Parte protegida.
//------------------------------------------------------------------------------------------
protected:
	unsigned int Name;
	CImage * Image;

	GLint MinFilter; // GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_NEAREST,
	                 // GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST_MIPMAP_NEAREST;
	GLint MagFilter; // GL_LINEAR, GL_NEAREST;

	// GL_CLAMP, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER, GL_REPEAT, GL_MIRRORED_REPEAT
	GLint WrapS, WrapT;
	GLint Mode; // GL_BLEND, GL_DECAL, GL_MODULATE, GL_REPLACE;

//------------------------------------------------------------------------------------------
// Parte publica.
//------------------------------------------------------------------------------------------
public:
	//--------------------------------------------------------------------------------------
	// Constructores y funciones de copia.
	//--------------------------------------------------------------------------------------
	CTexture ();
	CTexture (CImage * image, GLint minfilter = GL_LINEAR_MIPMAP_LINEAR,
			  GLint magfilter = GL_LINEAR, GLint wraps = GL_REPEAT,
			   GLint wrapt = GL_REPEAT, GLint mode = GL_MODULATE);
	CTexture (const CTexture & obj);
	virtual ~CTexture ();

	virtual CTexture & operator = (const CTexture & obj);
	virtual void CopyFrom (const CTexture & obj);
	
	//--------------------------------------------------------------------------------------
	// Lógica.
	//--------------------------------------------------------------------------------------
	bool Load    (CImage * image);
	bool Reload  (void);
	void Use     (void);
	void Release (void);
	
	//--------------------------------------------------------------------------------------
	// Gets.
	//--------------------------------------------------------------------------------------
	inline int      GetName      (void) { return this->Name;      }
	inline CImage * GetImage     (void) { return this->Image;     }
	inline GLint    GetMinFilter (void) { return this->MinFilter; }
	inline GLint    GetMagFilter (void) { return this->MagFilter; }
	inline GLint    GetWrapS     (void) { return this->WrapS;     }
	inline GLint    GetWrapT     (void) { return this->WrapT;     }
	inline GLint    GetMode      (void) { return this->Mode;      }
	
	//--------------------------------------------------------------------------------------
	// Sets.
	//--------------------------------------------------------------------------------------
	inline void SetMinFilter (GLint val = GL_LINEAR_MIPMAP_LINEAR) { this->MinFilter = val; }
	inline void SetMagFilter (GLint val = GL_LINEAR)               { this->MagFilter = val; }
	inline void SetWrapS     (GLint val = GL_REPEAT)               { this->WrapS = val;     }
	inline void SetWrapT     (GLint val = GL_REPEAT)               { this->WrapT = val;     }
	inline void SetMode      (GLint val = GL_MODULATE)             { this->Mode = val;      }
};
//******************************************************************************************
#endif
//******************************************************************************************
// textures.h
//******************************************************************************************