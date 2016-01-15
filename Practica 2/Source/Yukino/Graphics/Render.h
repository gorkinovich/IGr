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
#ifndef _YUKINO_GRAPHICS_RENDER_H_
#define _YUKINO_GRAPHICS_RENDER_H_
//******************************************************************************************
// Includes
//******************************************************************************************
#include "../Base.h"
//------------------------------------------------------------------------------------------
#include "../Util/Matrix.h"
#include "../Util/Point2D.h"
#include "../Util/Point3D.h"
#include "../Util/Vector2D.h"
#include "../Util/Vector3D.h"
//------------------------------------------------------------------------------------------
#include <gl/gl.h>
#include <gl/glu.h>
//******************************************************************************************
// Clase Render
//******************************************************************************************
namespace Yukino
{
	class DLLAPI RenderManager
	{
	//--------------------------------------------------------------------------------------
	// Miembros privados.
	//--------------------------------------------------------------------------------------
	private:
		RenderManager ();

	//--------------------------------------------------------------------------------------
	// Miembros públicos.
	//--------------------------------------------------------------------------------------
	public:
		~RenderManager ();

		//----------------------------------------------------------------------------------
		// Funciones para iniciar el pintado de geometría.
		//----------------------------------------------------------------------------------
		inline void Begin (GLenum mode) { glBegin(mode); }
		inline void End   (void)        { glEnd();       }

		inline void BeginPoints        (void) { glBegin(GL_POINTS);         }
		inline void BeginLines         (void) { glBegin(GL_LINES);          }
		inline void BeginLineStrip     (void) { glBegin(GL_LINE_STRIP);     }
		inline void BeginLineLoop      (void) { glBegin(GL_LINE_LOOP);      }
		inline void BeginTriangles     (void) { glBegin(GL_TRIANGLES);      }
		inline void BeginTriangleStrip (void) { glBegin(GL_TRIANGLE_STRIP); }
		inline void BeginTriangleFan   (void) { glBegin(GL_TRIANGLE_FAN);   }
		inline void BeginQuads         (void) { glBegin(GL_QUADS);          }
		inline void BeginQuadStrip     (void) { glBegin(GL_QUAD_STRIP);     }
		inline void BeginPolygon       (void) { glBegin(GL_POLYGON);        }

		//----------------------------------------------------------------------------------
		// Funciones para pintar vértices.
		//----------------------------------------------------------------------------------
		inline void Vertex (GLfloat x, GLfloat y)            { glVertex2f(x, y);    }
		inline void Vertex (GLfloat x, GLfloat y, GLfloat z) { glVertex3f(x, y, z); }

		inline void Vertex (Point2D & p)  { glVertex2fv(p.GetData()); }
		inline void Vertex (Point3D & p)  { glVertex3fv(p.GetData()); }
		inline void Vertex (Vector2D & v) { glVertex2fv(v.GetData()); }
		inline void Vertex (Vector3D & v) { glVertex3fv(v.GetData()); }
		
		inline void Vertex2v (GLfloat * p)  { glVertex2fv(p); }
		inline void Vertex3v (GLfloat * p)  { glVertex3fv(p); }

		//----------------------------------------------------------------------------------
		// Funciones para manipular los colores de los vértices.
		//----------------------------------------------------------------------------------
		inline void Color (GLfloat r, GLfloat g, GLfloat b)
		{
			glColor3f(r, g, b);
		}

		inline void Color (GLfloat r, GLfloat g, GLfloat b, GLfloat a)
		{
			glColor4f(r, g, b, a);
		}

		inline void Color3v (GLfloat * p)  { glColor3fv(p); }
		inline void Color4v (GLfloat * p)  { glColor4fv(p); }

		inline void ShadeModel (GLenum mode) { glShadeModel(mode); }
		
		inline void FlatShadeModel   (void) { glShadeModel(GL_FLAT);   }
		inline void SmoothShadeModel (void) { glShadeModel(GL_SMOOTH); }

		inline void ColorMaterial (GLenum face, GLenum pname) { glColorMaterial(face, pname); }

		//----------------------------------------------------------------------------------
		// Funciones para manipular las normales de los vértices.
		//----------------------------------------------------------------------------------
		inline void Normal (GLfloat nx, GLfloat ny, GLfloat nz) { glNormal3f(nx, ny, nz); }
		inline void Normal (const GLfloat * normal)             { glNormal3fv(normal);    }

		friend class GraphicsManager;
	};
}
//******************************************************************************************
#endif
//******************************************************************************************
// Render.h
//******************************************************************************************