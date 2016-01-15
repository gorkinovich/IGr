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
#ifndef _ANUBIS_SHADERS_H_
#define _ANUBIS_SHADERS_H_
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
#include <string>
//------------------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------------------
#include "error.h"
#include "extensions.h"
//******************************************************************************************
// Errores.
//******************************************************************************************
#define SHAERR_SHAOBJ_FOPENFILE           4101
#define SHAERR_SHAOBJ_EMPTYFILE           4102
#define SHAERR_SHAOBJ_CREATESHADEROBJECT  4103
#define SHAERR_SHAOBJ_COMPILESHADER       4104
//------------------------------------------------------------------------------------------
#define SHAERR_SHAOBJ_CREATEPROGRAMOBJECT 4201
#define SHAERR_SHAOBJ_LINKPROGRAM         4202
//------------------------------------------------------------------------------------------
#define SHAERR_SHAOBJ_NOSHADERSAVAILABLE  4301
//******************************************************************************************
// Clase para cargar un shader y compilarlo.
//******************************************************************************************
class CShaderObject
{
//------------------------------------------------------------------------------------------
// Parte protegida.
//------------------------------------------------------------------------------------------
protected:
	GLhandleARB shader;

//------------------------------------------------------------------------------------------
// Parte publica.
//------------------------------------------------------------------------------------------
public:
	//--------------------------------------------------------------------------------------
	// Constructores y funciones de copia.
	//--------------------------------------------------------------------------------------
	CShaderObject ();
	CShaderObject (const CShaderObject & obj);
	virtual ~CShaderObject ();

	virtual CShaderObject & operator = (const CShaderObject & obj);
	virtual void CopyFrom (const CShaderObject & obj);
	
	//--------------------------------------------------------------------------------------
	// Lógica.
	//--------------------------------------------------------------------------------------
	bool LoadVS (const char * path) { return this->Load(path, GL_VERTEX_SHADER_ARB);   }
	bool LoadFS (const char * path) { return this->Load(path, GL_FRAGMENT_SHADER_ARB); }

	bool Load (const char * path, GLenum type);
	void Release (void);

	//--------------------------------------------------------------------------------------
	// Gets.
	//--------------------------------------------------------------------------------------
	inline GLhandleARB GetHandle (void) { return this->shader; }
};
//******************************************************************************************
// Clase para cargar un programa de shaders.
//******************************************************************************************
class CShaderProgram
{
//------------------------------------------------------------------------------------------
// Parte protegida.
//------------------------------------------------------------------------------------------
protected:
	GLhandleARB program;

	CShaderObject vertex;
	CShaderObject fragment;

//------------------------------------------------------------------------------------------
// Parte publica.
//------------------------------------------------------------------------------------------
public:
	//--------------------------------------------------------------------------------------
	// Constructores y funciones de copia.
	//--------------------------------------------------------------------------------------
	CShaderProgram ();
	CShaderProgram (const CShaderProgram & obj);
	virtual ~CShaderProgram ();

	virtual CShaderProgram & operator = (const CShaderProgram & obj);
	virtual void CopyFrom (const CShaderProgram & obj);
	
	//--------------------------------------------------------------------------------------
	// Lógica.
	//--------------------------------------------------------------------------------------
	bool Load (const char * vspath, const char * fspath);
	void Release (void);
	void Use (void);
	
	//--------------------------------------------------------------------------------------
	// Gets.
	//--------------------------------------------------------------------------------------
	inline GLhandleARB GetVertexHandle (void)   { return this->vertex.GetHandle();   }
	inline GLhandleARB GetFragmentHandle (void) { return this->fragment.GetHandle(); }

	inline GLhandleARB GetHandle (void) { return this->program; }
};
//******************************************************************************************
// Clase para controlar los shaders y gestionarlos.
//******************************************************************************************
enum ShaderProgramType
{
	FixedPipelineSPT = -1,
	PerPixelLightingSPT = 0,
	NormalMappingSPT = 1,
	ParallaxMappingSPT = 2
};
//------------------------------------------------------------------------------------------
class CShadersManager
{
//------------------------------------------------------------------------------------------
// Parte protegida.
//------------------------------------------------------------------------------------------
protected:
	static CShadersManager * Instance;

	CShadersManager();

	CShaderProgram Programs[3];

	ShaderProgramType Limit;
	ShaderProgramType Program;

//------------------------------------------------------------------------------------------
// Parte publica.
//------------------------------------------------------------------------------------------
public:
	//--------------------------------------------------------------------------------------
	// Destructor.
	//--------------------------------------------------------------------------------------
	~CShadersManager ();
	
	//--------------------------------------------------------------------------------------
	// Lógica.
	//--------------------------------------------------------------------------------------
	bool Load (void);
	void Release (void);

	void UseProgram (ShaderProgramType program = FixedPipelineSPT);
	
	//--------------------------------------------------------------------------------------
	// Gets.
	//--------------------------------------------------------------------------------------
	bool IsShadersAvailable (void);

	ShaderProgramType GetLimit (void) { return this->Limit; }

	static CShadersManager * GetInstance (void);

	//--------------------------------------------------------------------------------------
	// Sets.
	//--------------------------------------------------------------------------------------
	void SetLimit (ShaderProgramType limit);

	void SetSampler2D (const char * name, GLint value);

	void SetScaleBiasFactor (GLfloat * factor);
	void EnableTangents (GLfloat * tangents);
	void DisableTangents (void);
};
//******************************************************************************************
#endif
//******************************************************************************************
// shaders.h
//******************************************************************************************