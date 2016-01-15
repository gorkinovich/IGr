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
#ifndef _YUKINO_GRAPHICS_POINT_H_
#define _YUKINO_GRAPHICS_POINT_H_
//******************************************************************************************
// Includes
//******************************************************************************************
#include "../Base.h"
//------------------------------------------------------------------------------------------
#include <gl/gl.h>
#include <gl/glu.h>
//******************************************************************************************
// Clase Point
//******************************************************************************************
namespace Yukino
{
	class DLLAPI PointManager
	{
	//--------------------------------------------------------------------------------------
	// Miembros privados.
	//--------------------------------------------------------------------------------------
	private:
		PointManager ();

	//--------------------------------------------------------------------------------------
	// Miembros públicos.
	//--------------------------------------------------------------------------------------
	public:
		~PointManager ();

		//----------------------------------------------------------------------------------
		// Gets.
		//----------------------------------------------------------------------------------
		GLfloat GetSizeGranularity (void);
		void    GetSizeRange       (GLfloat & minsize, GLfloat & maxsize);

		//----------------------------------------------------------------------------------
		// Sets.
		//----------------------------------------------------------------------------------
		inline void SetSize (GLfloat size) { glPointSize(size); }

		friend class GraphicsManager;
	};
}
//******************************************************************************************
#endif
//******************************************************************************************
// Point.h
//******************************************************************************************