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
#ifndef _ANUBIS_LIGHTING_H_
#define _ANUBIS_LIGHTING_H_
//******************************************************************************************
// Includes.
//******************************************************************************************
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl/gl.h>
//------------------------------------------------------------------------------------------
#include "color.h"
//******************************************************************************************
// Constantes.
//******************************************************************************************
#define ANUBIS_MAX_LIGHTS 8
//------------------------------------------------------------------------------------------
#define CONSTANT_ATTENUATION  0
#define LINEAR_ATTENUATION    1
#define QUADRATIC_ATTENUATION 2
//******************************************************************************************
// Tipos estructurados.
//******************************************************************************************
namespace Lighting
{
	typedef struct
	{
		GLfloat Ambient[4];  // 0.0f, 0.0f, 0.0f, 1.0f
		GLfloat Diffuse[4];  // 1.0f, 1.0f, 1.0f, 1.0f
		GLfloat Specular[4]; // 1.0f, 1.0f, 1.0f, 1.0f

		GLfloat Position[4]; // 0.0f, 0.0f, 1.0f, 0.0f
		
		GLfloat SpotDirection[3]; // 0.0f, 0.0f, -1.0f
		GLfloat SpotExponent;     // 0.0f
		GLfloat SpotCutoff;       // 180.0f (0.0f..90.0f)
		
		GLfloat Attenuation[3]; // 1.0f, 0.0f, 0.0f

		bool Enable;
	} tLight;
}
//******************************************************************************************
// Clase para gestionar las luces en OpenGL.
//******************************************************************************************
class CLighting
{
//------------------------------------------------------------------------------------------
// Parte protegida.
//------------------------------------------------------------------------------------------
protected:
	bool Enable;

	GLfloat Ambient[4]; // 0.2f, 0.2f, 0.2f, 1.0f

	Lighting::tLight Lights[ANUBIS_MAX_LIGHTS];

//------------------------------------------------------------------------------------------
// Parte publica.
//------------------------------------------------------------------------------------------
public:
	//--------------------------------------------------------------------------------------
	// Constructores y funciones de copia.
	//--------------------------------------------------------------------------------------
	CLighting ();
	CLighting (const CLighting & obj);
	virtual ~CLighting ();

	virtual CLighting & operator = (const CLighting & obj);
	virtual void CopyFrom (const CLighting & obj);
	
	//--------------------------------------------------------------------------------------
	// Lógica.
	//--------------------------------------------------------------------------------------
	void Update (void);
	void ConfigActiveLight (GLint value);

	void Load (const char * path);
	void Save (const char * path);

    void SaveText (const char * path);

	//--------------------------------------------------------------------------------------
	// Gets.
	//--------------------------------------------------------------------------------------
	inline bool      GetEnable  (void) { return this->Enable;  }
	inline GLfloat * GetAmbient (void) { return this->Ambient; }
	
	inline Lighting::tLight & GetLight (int index) { return this->Lights[index]; }
	
	//--------------------------------------------------------------------------------------
	// Sets.
	//--------------------------------------------------------------------------------------
	void SetEnable (bool enable);

	void SetAmbient (GLfloat * ambient);
	void SetAmbient (GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);

	void SetLight (int index, const Lighting::tLight & light);

	void SetLightAmbient  (int index, GLfloat * ambient);
	void SetLightAmbient  (int index, GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);
	void SetLightDiffuse  (int index, GLfloat * diffuse);
	void SetLightDiffuse  (int index, GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);
	void SetLightSpecular (int index, GLfloat * specular);
	void SetLightSpecular (int index, GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);
	void SetLightPosition (int index, GLfloat * position);
	void SetLightPosition (int index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	void SetLightSpotDirection (int index, GLfloat * direction);
	void SetLightSpotDirection (int index, GLfloat x, GLfloat y, GLfloat z);
	void SetLightSpotExponent  (int index, GLfloat exponent);
	void SetLightSpotCutoff    (int index, GLfloat cutoff);

	void SetLightConstantAttenuation  (int index, GLfloat value);
	void SetLightLinearAttenuation    (int index, GLfloat value);
	void SetLightQuadraticAttenuation (int index, GLfloat value);

	void SetLightEnable (int index, bool enable);
};
//******************************************************************************************
#endif
//******************************************************************************************
// lighting.h
//******************************************************************************************