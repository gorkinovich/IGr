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
#ifndef _YUKINO_GRAPHICS_MATERIAL_H_
#define _YUKINO_GRAPHICS_MATERIAL_H_
//******************************************************************************************
// Includes
//******************************************************************************************
#include "../Base.h"
//------------------------------------------------------------------------------------------
#include <gl/gl.h>
#include <gl/glu.h>
//******************************************************************************************
// Constantes
//******************************************************************************************
//#define CAMERAMODE_RPYPOS 0
//#define CAMERAMODE_LOOKAT 1
//******************************************************************************************
// Clase Material
//******************************************************************************************
namespace Yukino
{
	class DLLAPI Material
	{
	//--------------------------------------------------------------------------------------
	// Miembros protegidos.
	//--------------------------------------------------------------------------------------
	protected:
		GLenum Face; // GL_FRONT, GL_BACK, GL_FRONT_AND_BACK

		GLfloat Ambient[4];  // 0.2f, 0.2f, 0.2f, 1.0f
		GLfloat Diffuse[4];  // 0.8f, 0.8f, 0.8f, 1.0f
		GLfloat Specular[4]; // 0.0f, 0.0f, 0.0f, 1.0f
		GLfloat Emission[4]; // 0.0f, 0.0f, 0.0f, 1.0f

		GLfloat Shininess; // 0.0f (Rangos aceptados: 0..128)

	//--------------------------------------------------------------------------------------
	// Miembros públicos.
	//--------------------------------------------------------------------------------------
	public:
		Material ();
		~Material ();

		//----------------------------------------------------------------------------------
		// Funciones para controlar la lógica.
		//----------------------------------------------------------------------------------
		void Update (void);

		//----------------------------------------------------------------------------------
		// Gets.
		//----------------------------------------------------------------------------------
		inline GLenum GetFace (void) { return this->Face; }

		inline GLfloat * GetAmbient  (void) { return this->Ambient;  }
		inline GLfloat * GetDiffuse  (void) { return this->Diffuse;  }
		inline GLfloat * GetSpecular (void) { return this->Specular; }
		inline GLfloat * GetEmission (void) { return this->Emission; }

		inline GLfloat GetShininess (void) { return this->Shininess; }

		//----------------------------------------------------------------------------------
		// Sets.
		//----------------------------------------------------------------------------------
		inline void SetFace (GLenum val = GL_FRONT) { this->Face = val; }

		inline void SetAmbient (GLfloat r = 0.2f, GLfloat g = 0.2f, GLfloat b = 0.2f, GLfloat a = 1.0f)
		{
			this->Ambient[0] = r;
			this->Ambient[1] = g;
			this->Ambient[2] = b;
			this->Ambient[3] = a;
		}

		inline void SetDiffuse (GLfloat r = 0.8f, GLfloat g = 0.8f, GLfloat b = 0.8f, GLfloat a = 1.0f)
		{
			this->Diffuse[0] = r;
			this->Diffuse[1] = g;
			this->Diffuse[2] = b;
			this->Diffuse[3] = a;
		}

		inline void SetSpecular (GLfloat r = 0.0f, GLfloat g = 0.0f, GLfloat b = 0.0f, GLfloat a = 1.0f)
		{
			this->Specular[0] = r;
			this->Specular[1] = g;
			this->Specular[2] = b;
			this->Specular[3] = a;
		}

		inline void SetEmission (GLfloat r = 0.0f, GLfloat g = 0.0f, GLfloat b = 0.0f, GLfloat a = 1.0f)
		{
			this->Emission[0] = r;
			this->Emission[1] = g;
			this->Emission[2] = b;
			this->Emission[3] = a;
		}
		
		inline void SetShininess (GLfloat val = 0.0f) { this->Shininess = val; }
	};
}
//******************************************************************************************
#endif
//******************************************************************************************
// Material.h
//******************************************************************************************