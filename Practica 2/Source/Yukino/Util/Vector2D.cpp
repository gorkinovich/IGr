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
#include "Vector2D.h"
using namespace Yukino;
//------------------------------------------------------------------------------------------
#include <math.h>
//******************************************************************************************
// Constructores, destructores y funciones de copia.
//******************************************************************************************

	//--------------------------------------------------------------------------------------
	// Constructores de la clase.
	//--------------------------------------------------------------------------------------
	Vector2D::Vector2D ()
	{
		this->Data[0] = 0;
		this->Data[1] = 0;
		this->Data[2] = 0;
		this->Data[3] = 0;
	}

	Vector2D::Vector2D (GLfloat x, GLfloat y)
	{
		this->Data[0] = x;
		this->Data[1] = y;
		this->Data[2] = 0;
		this->Data[3] = 0;
	}

	Vector2D::Vector2D (const Vector2D & obj)
	{
		this->Data[0] = obj.Data[0];
		this->Data[1] = obj.Data[1];
		this->Data[2] = 0;
		this->Data[3] = 0;
	}

	//--------------------------------------------------------------------------------------
	// Destructor de la clase.
	//--------------------------------------------------------------------------------------
	Vector2D::~Vector2D ()
	{
	}

//******************************************************************************************
// Funciones miembro de la clase.
//******************************************************************************************

	//--------------------------------------------------------------------------------------
	// Metodo para calcular la magnitud del vector.
	//--------------------------------------------------------------------------------------
	GLfloat Vector2D::Magnitude (void) const
	{
		return (GLfloat) sqrt(this->Data[0] * this->Data[0] +
							  this->Data[1] * this->Data[1]);
	}

	//--------------------------------------------------------------------------------------
	// Metodo para calcular el vector normalizado.
	//--------------------------------------------------------------------------------------
	Vector2D Vector2D::Normalize (void) const
	{
		GLfloat magnitude = this->Magnitude();

		return Vector2D(this->Data[0] / magnitude,
						this->Data[1] / magnitude);
	}
	
	//--------------------------------------------------------------------------------------
	// Metodo para calcular la suma de dos vectores.
	//--------------------------------------------------------------------------------------
	Vector2D Vector2D::Add (const Vector2D & obj) const
	{
		return Vector2D(this->Data[0] + obj.Data[0],
						this->Data[1] + obj.Data[1]);
	}

	//--------------------------------------------------------------------------------------
	// Metodo para calcular la resta entre dos vectores.
	//--------------------------------------------------------------------------------------
	Vector2D Vector2D::Subtract (const Vector2D & obj) const
	{
		return Vector2D(this->Data[0] - obj.Data[0],
						this->Data[1] - obj.Data[1]);
	}

	//--------------------------------------------------------------------------------------
	// Metodo para calcular el producto de un escalar con el vector.
	//--------------------------------------------------------------------------------------
	Vector2D Vector2D::ScalarProduct (GLfloat s) const
	{
		return Vector2D(this->Data[0] * s,
						this->Data[1] * s);
	}

	//--------------------------------------------------------------------------------------
	// Metodo para calcular el producto escalar entre dos vectores.
	//--------------------------------------------------------------------------------------
	GLfloat Vector2D::DotProduct (const Vector2D & obj) const
	{
		return (this->Data[0] * obj.Data[0] + this->Data[1] * obj.Data[1]);
	}

	//--------------------------------------------------------------------------------------
	// Metodo para calcular el producto vectorial entre dos vectores.
	//--------------------------------------------------------------------------------------
	Vector2D Vector2D::CrossProduct (const Vector2D & obj) const
	{
		//A x B = (A.y * B.z - A.z * B.y,  A.z * B.x - A.x * B.z,  A.x * B.y - A.y * B.x)
		Vector2D result;

		result.Data[0] = this->Data[1] * obj.Data[2] - this->Data[2] * obj.Data[1];
		result.Data[1] = this->Data[2] * obj.Data[0] - this->Data[0] * obj.Data[2];
		result.Data[2] = this->Data[0] * obj.Data[1] - this->Data[1] * obj.Data[0];

		return result;
	}

	//--------------------------------------------------------------------------------------
	// Metodo para calcular el angulo entre dos vectores.
	//--------------------------------------------------------------------------------------
	GLfloat Vector2D::GetAngle (const Vector2D & obj) const
	{
		//alpha = arccos((A * B) / (|A| * |B|))
		GLfloat dotp = this->DotProduct(obj);
		GLfloat magp = this->Magnitude() * obj.Magnitude();

		//  gra     180            rad * 180
		// ----- = ----- -> gra = -----------
		//  rad     PI                 PI
		return ((GLfloat) acos(dotp / magp)) * 180.0f / PI;
	}

//******************************************************************************************
// Vector2D.cpp
//******************************************************************************************