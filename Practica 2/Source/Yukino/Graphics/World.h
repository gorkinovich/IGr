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
#ifndef _YUKINO_GRAPHICS_WORLD_H_
#define _YUKINO_GRAPHICS_WORLD_H_
//******************************************************************************************
// Includes
//******************************************************************************************
#include "../Base.h"
//------------------------------------------------------------------------------------------
#include <gl/gl.h>
#include <gl/glu.h>
//******************************************************************************************
// Clase World
//******************************************************************************************
namespace Yukino
{
	class DLLAPI WorldManager
	{
	//--------------------------------------------------------------------------------------
	// Miembros privados.
	//--------------------------------------------------------------------------------------
	private:
		WorldManager ();

	//--------------------------------------------------------------------------------------
	// Miembros públicos.
	//--------------------------------------------------------------------------------------
	public:
		~WorldManager ();

		//----------------------------------------------------------------------------------
		// Funciones para manipular las matrices.
		//----------------------------------------------------------------------------------
		inline void LoadIdentity (void) { glLoadIdentity(); }

		inline void ModelViewMode  (void) { glMatrixMode(GL_MODELVIEW);  }
		inline void ProjectionMode (void) { glMatrixMode(GL_PROJECTION); }
		inline void TextureMode    (void) { glMatrixMode(GL_TEXTURE);    }

		inline void MatrixMode (GLenum mode) { glMatrixMode(mode); }

		inline void PushMatrix (void) { glPushMatrix(); }
		inline void PopMatrix  (void) { glPopMatrix();  }

		inline void Translate (GLfloat x, GLfloat y, GLfloat z)
		{
			glTranslatef(x, y, z);
		}

		inline void Rotate (GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
		{
			glRotatef(angle, x, y, z);
		}

		inline void Scale (GLfloat x, GLfloat y, GLfloat z)
		{
			glScalef(x, y, z);
		}

		//----------------------------------------------------------------------------------
		// Funciones para manipular las proyecciones.
		//----------------------------------------------------------------------------------
		inline void Ortho (GLdouble left, GLdouble right, GLdouble bottom,
						   GLdouble top, GLdouble nearz, GLdouble farz)
		{
			glOrtho(left, right, bottom, top, nearz, farz);
		}

		inline void Frustum (GLdouble left, GLdouble right, GLdouble bottom,
							 GLdouble top, GLdouble nearz, GLdouble farz)
		{
			glFrustum(left, right, bottom, top, nearz, farz);
		}

		inline void Perspective (GLdouble fov, GLint width, GLint height,
								 GLdouble nearz, GLdouble farz)
		{
			if(height == 0) height = 1;
			gluPerspective(fov, (GLfloat) width / (GLfloat) height, nearz, farz);
		}

		inline void Viewport (GLint x, GLint y, GLint width, GLint height)
		{
			glViewport(x, y, width, height);
		}

		friend class GraphicsManager;
	};
}
//******************************************************************************************
#endif
//******************************************************************************************
// World.h
//******************************************************************************************