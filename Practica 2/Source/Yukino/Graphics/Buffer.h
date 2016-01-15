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
#ifndef _YUKINO_GRAPHICS_BUFFER_H_
#define _YUKINO_GRAPHICS_BUFFER_H_
//******************************************************************************************
// Includes
//******************************************************************************************
#include "../Base.h"
//------------------------------------------------------------------------------------------
#include <gl/gl.h>
#include <gl/glu.h>
//******************************************************************************************
// Clase Buffer
//******************************************************************************************
namespace Yukino
{
	class DLLAPI BufferManager
	{
	//--------------------------------------------------------------------------------------
	// Miembros privados.
	//--------------------------------------------------------------------------------------
	private:
		BufferManager ();

	//--------------------------------------------------------------------------------------
	// Miembros públicos.
	//--------------------------------------------------------------------------------------
	public:
		~BufferManager ();

		//----------------------------------------------------------------------------------
		// Funciones para manipular los buffers.
		//----------------------------------------------------------------------------------
		inline void ClearColor (GLclampf r, GLclampf g, GLclampf b, GLclampf a)
		{
			glClearColor(r, g, b, a);
		}
		
		inline void ClearDepth (GLclampf depth)
		{
			glClearDepth(depth);
		}
		
		inline void ClearStencil (GLint s)
		{
			glClearStencil(s);
		}
		
		inline void ClearAccum (GLclampf r, GLclampf g, GLclampf b, GLclampf a)
		{
			glClearAccum(r, g, b, a);
		}

		inline void Clear (GLbitfield mask) { glClear(mask); }
		
		inline void ClearAll (void)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |
					GL_STENCIL_BUFFER_BIT | GL_ACCUM_BUFFER_BIT);
		}

		inline void ClearColorBuffer   (void) { glClear(GL_COLOR_BUFFER_BIT);   }
		inline void ClearDepthBuffer   (void) { glClear(GL_DEPTH_BUFFER_BIT);   }
		inline void ClearStencilBuffer (void) { glClear(GL_STENCIL_BUFFER_BIT); }
		inline void ClearAccumBuffer   (void) { glClear(GL_ACCUM_BUFFER_BIT);   }

		inline void DepthMask (GLboolean flag) { glDepthMask(flag); }

		// GL_FRONT, GL_BACK, GL_FRONT_AND_BACK, GL_NONE
		inline void DrawBuffer (GLenum mode = GL_BACK) { glDrawBuffer(mode); }
		inline void ReadBuffer (GLenum mode = GL_BACK) { glReadBuffer(mode); }

		inline void ColorMask (GLboolean r, GLboolean g, GLboolean b, GLboolean a)
		{
			glColorMask(r, g, b, a);
		}

		inline void Accum (GLenum op, GLfloat value) { glAccum (op, value); }
		
		inline void AccumAccum  (GLfloat value) { glAccum (GL_ACCUM, value);  }
		inline void AccumLoad   (GLfloat value) { glAccum (GL_LOAD, value);   }
		inline void AccumAdd    (GLfloat value) { glAccum (GL_ADD, value);    }
		inline void AccumMult   (GLfloat value) { glAccum (GL_MULT, value);   }
		inline void AccumReturn (GLfloat value) { glAccum (GL_RETURN, value); }

		//----------------------------------------------------------------------------------
		// Funciones para configurar las funciones de manipulación de los buffers.
		//----------------------------------------------------------------------------------
		
		inline void BlendFunc (GLenum source = GL_ONE, GLenum destination = GL_ZERO)
		{
			glBlendFunc(source, destination);
		}
		

		// GL_NEVER, GL_ALWAYS, GL_LESS, GL_LEQUAL, GL_GREATER, GL_GEQUAL, GL_EQUAL, GL_NOTEQUAL
		inline void DepthFunc (GLenum func = GL_LESS) { glDepthFunc(func); }

		// GL_NEVER, GL_ALWAYS, GL_LESS, GL_LEQUAL, GL_GREATER, GL_GEQUAL, GL_EQUAL, GL_NOTEQUAL
		inline void StencilFunc (GLenum func, GLint ref, GLuint mask)
		{
			glStencilFunc(func, ref, mask);
		}

		// GL_KEEP, GL_ZERO, GL_REPLACE, GL_INCR, GL_DECR, GL_INVERT
		inline void StencilOp (GLenum fail, GLenum zfail, GLenum zpass)
		{
			glStencilOp(fail, zfail, zpass);
		}

		inline void StencilMask (GLuint mask) { glStencilMask(mask); }

		// GL_NEVER, GL_ALWAYS, GL_LESS, GL_LEQUAL, GL_GREATER, GL_GEQUAL, GL_EQUAL, GL_NOTEQUAL
		inline void AlphaFunc (GLenum func, GLclampf ref) { glAlphaFunc(func, ref); }

		friend class GraphicsManager;
	};
}
//******************************************************************************************
#endif
//******************************************************************************************
// Buffer.h
//******************************************************************************************