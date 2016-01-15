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
#ifndef _YUKINO_GRAPHICS_LIGHTMODEL_H_
#define _YUKINO_GRAPHICS_LIGHTMODEL_H_
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
#ifndef GL_LIGHT_MODEL_COLOR_CONTROL
	#define GL_LIGHT_MODEL_COLOR_CONTROL 0x81F8
#endif

#ifndef GL_SINGLE_COLOR
	#define GL_SINGLE_COLOR 0x81F9
#endif

#ifndef GL_SEPARATE_SPECULAR_COLOR
	#define GL_SEPARATE_SPECULAR_COLOR 0x81FA
#endif
//******************************************************************************************
// Clase LightModel
//******************************************************************************************
namespace Yukino
{
	class DLLAPI LightModelManager
	{
	//--------------------------------------------------------------------------------------
	// Miembros privados.
	//--------------------------------------------------------------------------------------
	private:
		LightModelManager ();

	//--------------------------------------------------------------------------------------
	// Miembros públicos.
	//--------------------------------------------------------------------------------------
	public:
		~LightModelManager ();

		//----------------------------------------------------------------------------------
		// Funciones para manipular la iluminación general.
		//----------------------------------------------------------------------------------
		inline void Ambient (GLfloat * param)
		{
			//0.2f, 0.2f, 0.2f, 1.0f
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, param);
		}

		void Ambient (GLfloat r = 0.2f, GLfloat g = 0.2f, GLfloat b = 0.2f, GLfloat a = 1.0f);

		inline void LocalViewer (GLint param = GL_FALSE)
		{
			glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, param);
		}

		inline void TwoSide (GLint param = GL_FALSE)
		{
			glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, param);
		}

		inline void ColorControl (GLint param = GL_SINGLE_COLOR)
		{
			glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, param);
		}

		friend class GraphicsManager;
	};
}
//******************************************************************************************
#endif
//******************************************************************************************
// LightModel.h
//******************************************************************************************