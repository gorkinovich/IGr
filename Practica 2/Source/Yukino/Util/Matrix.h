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
#ifndef _YUKINO_UTIL_MATRIX_H_
#define _YUKINO_UTIL_MATRIX_H_
//******************************************************************************************
// Includes
//******************************************************************************************
#include "../Base.h"
//------------------------------------------------------------------------------------------
#include <gl/gl.h>
//******************************************************************************************
// Constantes
//******************************************************************************************
#define MAX_MATRIX_RANGE 16
//******************************************************************************************
// Clase Matrix
//******************************************************************************************
namespace Yukino
{
	class DLLAPI Matrix
	{
	//--------------------------------------------------------------------------------------
	// Miembros protegidos.
	//--------------------------------------------------------------------------------------
	protected:
		GLfloat Data[MAX_MATRIX_RANGE];

	//--------------------------------------------------------------------------------------
	// Miembros públicos.
	//--------------------------------------------------------------------------------------
	public:
		Matrix ();
		Matrix (const Matrix & obj);
		~Matrix ();

		void SetIdentity (void);
		void SetZero (void);
		
		Matrix Add (const Matrix & obj) const;
		Matrix Subtract (const Matrix & obj) const;
		Matrix Product (const Matrix & obj) const;

		void SetVal (GLuint row, GLuint col, GLfloat val);
		void SetVal (GLuint index, GLfloat val);

		GLfloat GetVal (GLuint row, GLuint col);
		GLfloat GetVal (GLuint index);

		// Metodo para obtener los valores de la matriz.
		inline void SetData (GLfloat * matrix)
		{
			for(int i = 0; i < MAX_MATRIX_RANGE; ++i)
				this->Data[i] = matrix[i];
		}

		// Metodo para obtener los valores de la matriz.
		inline GLfloat * GetData (void)
		{
			return this->Data;
		}

		//----------------------------------------------------------------------------------
		// Metodos para obtener la matriz actual de OpenGL.
		//----------------------------------------------------------------------------------
		inline void GetMatrix (GLenum matrix = GL_MODELVIEW_MATRIX)
		{
			glGetFloatv(matrix, this->Data);
		}
		
		inline void GetModelViewMatrix (void)
		{
			glGetFloatv(GL_MODELVIEW_MATRIX, this->Data);
		}
		
		inline void GetProjectionMatrix (void)
		{
			glGetFloatv(GL_PROJECTION_MATRIX, this->Data);
		}
		
		inline void GetTextureMatrix (void)
		{
			glGetFloatv(GL_TEXTURE_MATRIX, this->Data);
		}

		//----------------------------------------------------------------------------------
		// Metodo para multiplicar la matriz actual de OpenGL.
		//----------------------------------------------------------------------------------
		inline void MultMatrix (void)
		{
			glMultMatrixf(this->Data);
		}

		//----------------------------------------------------------------------------------
		// Metodo para cargar esta matriz como la actual de OpenGL.
		//----------------------------------------------------------------------------------
		inline void LoadMatrix (void)
		{
			glLoadMatrixf(this->Data);
		}
	};
}
//******************************************************************************************
#endif
//******************************************************************************************
// Matrix.h
//******************************************************************************************