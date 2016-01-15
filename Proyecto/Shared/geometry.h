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
#ifndef _ANUBIS_GEOMETRY_H_
#define _ANUBIS_GEOMETRY_H_
//******************************************************************************************
// Includes.
//******************************************************************************************
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
//------------------------------------------------------------------------------------------
#include <gl/gl.h>
#include <gl/glu.h>
//------------------------------------------------------------------------------------------
#include "error.h"
#include "extensions.h"
#include "content.h"
#include "3dobjects.h"
//******************************************************************************************
// Errores.
//******************************************************************************************
#define GEOERR_SMIMP_OBJSNULL 3101
#define GEOERR_SMIMP_MATSNULL 3102
#define GEOERR_SMCPY_OBJSNULL 3103
#define GEOERR_SMCPY_MATSNULL 3104
#define GEOERR_SMLOAD_FOPEN   3105
#define GEOERR_SMLOAD_BADTYPE 3106
#define GEOERR_SMLOAD_BADVER  3107
#define GEOERR_SMLOAD_OBJNULL 3108
#define GEOERR_SMLOAD_MATNULL 3109
#define GEOERR_SMSAVE_FOPEN   3110
//******************************************************************************************
// Clase para almacenar una geometría estática.
//******************************************************************************************
class CStaticMesh
{
//------------------------------------------------------------------------------------------
// Parte protegida.
//------------------------------------------------------------------------------------------
protected:
	char * Name;
	GLfloat Matrix[16];

	Geometry::CTransformation Transformation;

	Geometry::CObject   * Objects;
	Geometry::CMaterial * Materials;

	unsigned int NumObjects;
	unsigned int NumMaterials;

//------------------------------------------------------------------------------------------
// Parte publica.
//------------------------------------------------------------------------------------------
public:
	//--------------------------------------------------------------------------------------
	// Constructores y funciones de copia.
	//--------------------------------------------------------------------------------------
	CStaticMesh ();
	CStaticMesh (const CStaticMesh & obj);
	virtual ~CStaticMesh ();

	virtual CStaticMesh & operator = (const CStaticMesh & obj);
	virtual void CopyFrom (const CStaticMesh & obj);
	
	//--------------------------------------------------------------------------------------
	// Lógica.
	//--------------------------------------------------------------------------------------
	bool Load (const char * name);
	bool Save (const char * name);

	void Draw (void);

	bool Import (const char * name);
	void Release (void);
	
	//--------------------------------------------------------------------------------------
	// Gets.
	//--------------------------------------------------------------------------------------
	inline char *    GetName   (void) { return this->Name;   }
	inline GLfloat * GetMatrix (void) { return this->Matrix; }

	inline Geometry::CTransformation & GetTransformation (void)
    {
        return this->Transformation;
    }

	Geometry::CObject &   GetObject   (unsigned int index);
	Geometry::CMaterial & GetMaterial (unsigned int index);

	inline unsigned int GetNumObjects (void)   { return this->NumObjects;   }
	inline unsigned int GetNumMaterials (void) { return this->NumMaterials; }
    
	inline Geometry::CObject *   GetObjects   (void) { return this->Objects;   }
	inline Geometry::CMaterial * GetMaterials (void) { return this->Materials; }
	
	//--------------------------------------------------------------------------------------
	// Sets.
	//--------------------------------------------------------------------------------------
	void SetName     (const char * name);
	void SetMatrix   (const GLfloat * matrix);
	void SetMatrix   (const Geometry::CTransformation & transformation);
	void SetObject   (unsigned int index, const Geometry::CObject & object);
	void SetMaterial (unsigned int index, const Geometry::CMaterial & material);
};
//******************************************************************************************
// Clase para almacenar una geometría animada.
//******************************************************************************************
/*
class xxx
{
//------------------------------------------------------------------------------------------
// Parte protegida.
//------------------------------------------------------------------------------------------
protected:

//------------------------------------------------------------------------------------------
// Parte publica.
//------------------------------------------------------------------------------------------
public:
	//--------------------------------------------------------------------------------------
	// Constructores y funciones de copia.
	//--------------------------------------------------------------------------------------
	xxx ();
	xxx (const xxx & obj);
	virtual ~xxx ();

	virtual xxx & operator = (const xxx & obj);
	virtual void CopyFrom (const xxx & obj);
	
	//--------------------------------------------------------------------------------------
	// Lógica.
	//--------------------------------------------------------------------------------------
	
	//--------------------------------------------------------------------------------------
	// Gets.
	//--------------------------------------------------------------------------------------
	
	//--------------------------------------------------------------------------------------
	// Sets.
	//--------------------------------------------------------------------------------------
};
//*/
//******************************************************************************************
#endif
//******************************************************************************************
// geometry.h
//******************************************************************************************