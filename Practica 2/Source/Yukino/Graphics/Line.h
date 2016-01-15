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
#ifndef _YUKINO_GRAPHICS_LINE_H_
#define _YUKINO_GRAPHICS_LINE_H_
//******************************************************************************************
// Includes
//******************************************************************************************
#include "../Base.h"
//------------------------------------------------------------------------------------------
#include <gl/gl.h>
#include <gl/glu.h>
//******************************************************************************************
// Clase LineManager
//******************************************************************************************
namespace Yukino
{
	class DLLAPI LineManager
	{
	//--------------------------------------------------------------------------------------
	// Miembros privados.
	//--------------------------------------------------------------------------------------
	private:
		LineManager ();

	//--------------------------------------------------------------------------------------
	// Miembros públicos.
	//--------------------------------------------------------------------------------------
	public:
		~LineManager ();

		//----------------------------------------------------------------------------------
		// Gets.
		//----------------------------------------------------------------------------------
		GLfloat GetWidthGranularity (void);
		void    GetWidthRange       (GLfloat & minsize, GLfloat & maxsize);		

		GLint    GetStippleRepeat  (void);
		GLushort GetStipplePattern (void);

		//----------------------------------------------------------------------------------
		// Sets.
		//----------------------------------------------------------------------------------
		inline void SetWidth (GLfloat width) { glLineWidth(width); }

		inline void SetStipple (GLint factor, GLushort pattern) { glLineStipple(factor, pattern); }

		friend class GraphicsManager;
	};
}
//******************************************************************************************
#endif
//******************************************************************************************
// Line.h
//******************************************************************************************