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
#ifndef _YUKINO_GRAPHICS_CAMERA_H_
#define _YUKINO_GRAPHICS_CAMERA_H_
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
#define CAMERAMODE_RPYPOS 0
#define CAMERAMODE_LOOKAT 1
//******************************************************************************************
// Clase CameraManager
//******************************************************************************************
namespace Yukino
{
	class DLLAPI CameraManager
	{
	//--------------------------------------------------------------------------------------
	// Miembros privados.
	//--------------------------------------------------------------------------------------
	private:
		CameraManager ();

	//--------------------------------------------------------------------------------------
	// Miembros protegidos.
	//--------------------------------------------------------------------------------------
	protected:
		GLfloat Roll;  // Giro sobre el eje z.
		GLfloat Yaw;   // Giro sobre el eje y (izquierda-derecha).
		GLfloat Pitch; // Giro sobre el eje x (arriba-abajo).

		GLdouble EyeX;
		GLdouble EyeY;
		GLdouble EyeZ;
		GLdouble CenterX;
		GLdouble CenterY;
		GLdouble CenterZ;
		GLdouble UpX;
		GLdouble UpY;
		GLdouble UpZ;

		GLenum Mode;
		
	//--------------------------------------------------------------------------------------
	// Miembros públicos.
	//--------------------------------------------------------------------------------------
	public:
		~CameraManager ();

		//----------------------------------------------------------------------------------
		// Funciones para controlar la lógica.
		//----------------------------------------------------------------------------------
		void Update (void);

		//----------------------------------------------------------------------------------
		// Gets.
		//----------------------------------------------------------------------------------
		inline GLfloat GetRoll  (void) { return this->Roll;  }
		inline GLfloat GetYaw   (void) { return this->Yaw;   }
		inline GLfloat GetPitch (void) { return this->Pitch; }

		inline GLfloat GetEyeX (void) { return this->EyeX; }
		inline GLfloat GetEyeY (void) { return this->EyeY; }
		inline GLfloat GetEyeZ (void) { return this->EyeZ; }

		inline GLfloat GetCenterX (void) { return this->CenterX; }
		inline GLfloat GetCenterY (void) { return this->CenterY; }
		inline GLfloat GetCenterZ (void) { return this->CenterZ; }
		
		inline GLfloat GetUpX (void) { return this->UpX; }
		inline GLfloat GetUpY (void) { return this->UpY; }
		inline GLfloat GetUpZ (void) { return this->UpZ; }

		inline GLfloat GetMode (void) { return this->Mode; }

		//----------------------------------------------------------------------------------
		// Sets.
		//----------------------------------------------------------------------------------
		inline void SetRoll  (GLfloat val) { this->Roll = val;  }
		inline void SetYaw   (GLfloat val) { this->Yaw = val;   }
		inline void SetPitch (GLfloat val) { this->Pitch = val; }

		inline void SetEyeX (GLfloat val) { this->EyeX = val; }
		inline void SetEyeY (GLfloat val) { this->EyeY = val; }
		inline void SetEyeZ (GLfloat val) { this->EyeZ = val; }

		inline void SetCenterX (GLfloat val) { this->CenterX = val; }
		inline void SetCenterY (GLfloat val) { this->CenterY = val; }
		inline void SetCenterZ (GLfloat val) { this->CenterZ = val; }
		
		inline void SetUpX (GLfloat val) { this->UpX = val; }
		inline void SetUpY (GLfloat val) { this->UpY = val; }
		inline void SetUpZ (GLfloat val) { this->UpZ = val; }
		
		inline void SetEye (GLfloat x, GLfloat y, GLfloat z)
		{
			this->EyeX = x;
			this->EyeY = y;
			this->EyeZ = z;
		}

		inline void SetCenter (GLfloat x, GLfloat y, GLfloat z)
		{
			this->CenterX = x;
			this->CenterY = y;
			this->CenterZ = z;
		}

		inline void SetUp (GLfloat x, GLfloat y, GLfloat z)
		{
			this->UpX = x;
			this->UpY = y;
			this->UpZ = z;
		}

		inline void SetMode (GLfloat val) { this->Mode = val; }

		friend class GraphicsManager;
	};
}
//******************************************************************************************
#endif
//******************************************************************************************
// Camera.h
//******************************************************************************************