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
#ifndef _YUKINO_GRAPHICS_LIGHT_H_
#define _YUKINO_GRAPHICS_LIGHT_H_
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
// Clase Light
//******************************************************************************************
namespace Yukino
{
	class DLLAPI Light
	{
	//--------------------------------------------------------------------------------------
	// Miembros protegidos.
	//--------------------------------------------------------------------------------------
	protected:
		GLenum LightID;

		GLfloat Ambient[4];  // 1.0f, 1.0f, 1.0f, 1.0f
		GLfloat Diffuse[4];  // 1.0f, 1.0f, 1.0f, 1.0f
		GLfloat Specular[4]; // 1.0f, 1.0f, 1.0f, 1.0f

		GLfloat Position[4]; // 0.0f, 0.0f, 1.0f, 0.0f

		GLfloat SpotDirection[3]; // 0.0f, 0.0f, -1.0f
		GLfloat SpotExponent;     //   1.0f (Rangos aceptados: 0..128)
		GLfloat SpotCutOff;       // 180.0f (Rangos aceptados: 0..90, 180)

		GLfloat ConstantAttenuation;  // 1.0f
		GLfloat LinearAttenuation;    // 0.0f
		GLfloat QuadraticAttenuation; // 0.0f

		GLfloat Roll;  // Giro sobre el eje z.
		GLfloat Yaw;   // Giro sobre el eje y (izquierda-derecha).
		GLfloat Pitch; // Giro sobre el eje x (arriba-abajo).

	//--------------------------------------------------------------------------------------
	// Miembros públicos.
	//--------------------------------------------------------------------------------------
	public:
		Light ();
		~Light ();

		//----------------------------------------------------------------------------------
		// Funciones para controlar la lógica.
		//----------------------------------------------------------------------------------
		inline void UpdateWithRotation (void)
		{
			glPushMatrix();
				glRotatef(this->Roll, 0.0f, 0.0f, 1.0f);
				glRotatef(this->Yaw, 0.0f, 1.0f, 0.0f);
				glRotatef(this->Pitch, 1.0f, 0.0f, 0.0f);

				this->Update();
			glPopMatrix();
		}

		void Update (void);

		inline void Enable  (void) { glEnable(this->LightID);  }
		inline void Disable (void) { glDisable(this->LightID); }

		//----------------------------------------------------------------------------------
		// Gets.
		//----------------------------------------------------------------------------------
		inline GLenum GetLight (void) { return this->LightID; }

		inline GLfloat * GetAmbient  (void) { return this->Ambient;  }
		inline GLfloat * GetDiffuse  (void) { return this->Diffuse;  }
		inline GLfloat * GetSpecular (void) { return this->Specular; }
		inline GLfloat * GetPosition (void) { return this->Position; }
		
		inline GLfloat * GetSpotDirection (void) { return this->SpotDirection; }
		inline GLfloat   GetSpotExponent  (void) { return this->SpotExponent; }
		inline GLfloat   GetSpotCutOff    (void) { return this->SpotCutOff; }

		inline GLfloat GetConstantAttenuation  (void) { return this->ConstantAttenuation;  }
		inline GLfloat GetLinearAttenuation    (void) { return this->LinearAttenuation;    }
		inline GLfloat GetQuadraticAttenuation (void) { return this->QuadraticAttenuation; }

		inline GLfloat GetRoll  (void) { return this->Roll;  }
		inline GLfloat GetYaw   (void) { return this->Yaw;   }
		inline GLfloat GetPitch (void) { return this->Pitch; }

		//----------------------------------------------------------------------------------
		// Sets.
		//----------------------------------------------------------------------------------
		inline void SetLight (GLenum val = GL_LIGHT0) { this->LightID = val; }

		inline void SetAmbient (GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f, GLfloat a = 1.0f)
		{
			this->Ambient[0] = r;
			this->Ambient[1] = g;
			this->Ambient[2] = b;
			this->Ambient[3] = a;
		}

		inline void SetDiffuse (GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f, GLfloat a = 1.0f)
		{
			this->Diffuse[0] = r;
			this->Diffuse[1] = g;
			this->Diffuse[2] = b;
			this->Diffuse[3] = a;
		}

		inline void SetSpecular (GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f, GLfloat a = 1.0f)
		{
			this->Specular[0] = r;
			this->Specular[1] = g;
			this->Specular[2] = b;
			this->Specular[3] = a;
		}

		inline void SetPosition (GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = 1.0f, GLfloat w = 0.0f)
		{
			this->Position[0] = x;
			this->Position[1] = y;
			this->Position[2] = z;
			this->Position[3] = w;
		}
		
		inline SetSpotDirection (GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = -1.0f)
		{
			this->SpotDirection[0] = x;
			this->SpotDirection[1] = y;
			this->SpotDirection[2] = z;
		}

		inline void SetSpotExponent (GLfloat val =   1.0f) { this->SpotExponent = val; }
		inline void SetSpotCutOff   (GLfloat val = 180.0f) { this->SpotCutOff = val;   }

		inline void SetConstantAttenuation (GLfloat val = 1.0f)
		{
			this->ConstantAttenuation = val;
		}

		inline void SetLinearAttenuation (GLfloat val = 0.0f)
		{
			this->LinearAttenuation = val;
		}

		inline void SetQuadraticAttenuation (GLfloat val = 0.0f)
		{
			this->QuadraticAttenuation = val;
		}

		inline void SetRoll  (GLfloat val = 0.0f) { this->Roll = val;  }
		inline void SetYaw   (GLfloat val = 0.0f) { this->Yaw = val;   }
		inline void SetPitch (GLfloat val = 0.0f) { this->Pitch = val; }
	};
}
//******************************************************************************************
#endif
//******************************************************************************************
// Light.h
//******************************************************************************************