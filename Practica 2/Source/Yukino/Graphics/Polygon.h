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
#ifndef _YUKINO_GRAPHICS_POLYGON_H_
#define _YUKINO_GRAPHICS_POLYGON_H_
//******************************************************************************************
// Includes
//******************************************************************************************
#include "../Base.h"
//------------------------------------------------------------------------------------------
#include <gl/gl.h>
#include <gl/glu.h>
//******************************************************************************************
// Clase Polygon
//******************************************************************************************
namespace Yukino
{
	class DLLAPI PolygonManager
	{
	//--------------------------------------------------------------------------------------
	// Miembros privados.
	//--------------------------------------------------------------------------------------
	private:
		PolygonManager ();

	//--------------------------------------------------------------------------------------
	// Miembros públicos.
	//--------------------------------------------------------------------------------------
	public:
		~PolygonManager ();

		//----------------------------------------------------------------------------------
		// Funciones para configurar u obtener las propiedades del pintado de poligonos.
		//----------------------------------------------------------------------------------
		inline void FrontPointMode (void) { glPolygonMode(GL_FRONT, GL_POINT); }
		inline void FrontLineMode  (void) { glPolygonMode(GL_FRONT, GL_LINE);  }
		inline void FrontFillMode  (void) { glPolygonMode(GL_FRONT, GL_FILL);  }
		inline void BackPointMode  (void) { glPolygonMode(GL_BACK, GL_POINT);  }
		inline void BackLineMode   (void) { glPolygonMode(GL_BACK, GL_LINE);   }
		inline void BackFillMode   (void) { glPolygonMode(GL_BACK, GL_FILL);   }
		
		inline void PolygonMode (GLenum face, GLenum mode) { glPolygonMode(face, mode); }

		inline void CullFront (void) { glCullFace(GL_FRONT); }
		inline void CullBack  (void) { glCullFace(GL_BACK);  }

		inline void FrontFaceCCW (void) { glFrontFace(GL_CCW); }
		inline void FrontFaceCW  (void) { glFrontFace(GL_CW);  }

		inline void ShowEdges (void) { glEdgeFlag(GL_TRUE);  }
		inline void HideEdges (void) { glEdgeFlag(GL_FALSE); }

		friend class GraphicsManager;
	};
}
//******************************************************************************************
#endif
//******************************************************************************************
// Polygon.h
//******************************************************************************************