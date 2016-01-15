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
#ifndef _YUKINO_UTIL_VECTOR3D_H_
#define _YUKINO_UTIL_VECTOR3D_H_
//******************************************************************************************
// Includes
//******************************************************************************************
#include "../Base.h"
//------------------------------------------------------------------------------------------
#include <gl/gl.h>
//******************************************************************************************
// Clase Vector3D
//******************************************************************************************
namespace Yukino
{
	class DLLAPI Vector3D
	{
	//--------------------------------------------------------------------------------------
	// Miembros protegidos.
	//--------------------------------------------------------------------------------------
	protected:
		GLfloat Data[4];

	//--------------------------------------------------------------------------------------
	// Miembros públicos.
	//--------------------------------------------------------------------------------------
	public:
		Vector3D ();
		Vector3D (GLfloat x, GLfloat y, GLfloat z);
		Vector3D (const Vector3D & obj);
		~Vector3D ();

		GLfloat  Magnitude (void) const;
		Vector3D Normalize (void) const;

		Vector3D Add           (const Vector3D & obj) const;
		Vector3D Subtract      (const Vector3D & obj) const;
		Vector3D ScalarProduct (GLfloat s) const;
		GLfloat  DotProduct    (const Vector3D & obj) const;
		Vector3D CrossProduct  (const Vector3D & obj) const;

		GLfloat GetAngle (const Vector3D & obj) const;

		//----------------------------------------------------------------------------------
		// Metodo para modificar la coordenada x del vector.
		//----------------------------------------------------------------------------------
		inline void SetX (GLfloat x)
		{
			this->Data[0] = x;
		}

		//----------------------------------------------------------------------------------
		// Metodo para modificar la coordenada y del vector.
		//----------------------------------------------------------------------------------
		inline void SetY (GLfloat y)
		{
			this->Data[1] = y;
		}

		//----------------------------------------------------------------------------------
		// Metodo para modificar la coordenada z del vector.
		//----------------------------------------------------------------------------------
		inline void SetZ (GLfloat z)
		{
			this->Data[2] = z;
		}

		//----------------------------------------------------------------------------------
		// Metodo para modificar las coordenadas del vector.
		//----------------------------------------------------------------------------------
		inline void SetData (GLfloat * data)
		{
			this->Data[0] = data[0];
			this->Data[1] = data[1];
		}

		//----------------------------------------------------------------------------------
		// Metodo para obtener la coordenada x del vector.
		//----------------------------------------------------------------------------------
		inline GLfloat GetX (void)
		{
			return this->Data[0];
		}

		//----------------------------------------------------------------------------------
		// Metodo para obtener la coordenada y del vector.
		//----------------------------------------------------------------------------------
		inline GLfloat GetY (void)
		{
			return this->Data[1];
		}

		//----------------------------------------------------------------------------------
		// Metodo para obtener la coordenada z del vector.
		//----------------------------------------------------------------------------------
		inline GLfloat GetZ (void)
		{
			return this->Data[2];
		}
		
		//----------------------------------------------------------------------------------
		// Metodo para obtener las coordenadas del vector.
		//----------------------------------------------------------------------------------
		inline GLfloat * GetData (void)
		{
			return this->Data;
		}
	};
}
//******************************************************************************************
#endif
//******************************************************************************************
// Vector3D.h
//******************************************************************************************