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
#include "Matrix.h"
using namespace Yukino;
//******************************************************************************************
// Constructores, destructores y funciones de copia.
//******************************************************************************************

	//--------------------------------------------------------------------------------------
	// Constructores de la clase.
	//--------------------------------------------------------------------------------------
	Matrix::Matrix ()
	{
		this->SetZero();
	}

	Matrix::Matrix (const Matrix & obj)
	{
		for(int i = 0; i < MAX_MATRIX_RANGE; ++i)
			this->Data[i] = obj.Data[i];
	}

	//--------------------------------------------------------------------------------------
	// Destructor de la clase.
	//--------------------------------------------------------------------------------------
	Matrix::~Matrix ()
	{
		this->SetZero();
	}

//******************************************************************************************
// Funciones miembro de la clase.
//******************************************************************************************

	//--------------------------------------------------------------------------------------
	// Metodo para convertir la matriz en una matriz identidad.
	//--------------------------------------------------------------------------------------
	void Matrix::SetIdentity (void)
	{
		this->Data[0] = 1;
		this->Data[1] = 0;
		this->Data[2] = 0;
		this->Data[3] = 0;
		
		this->Data[4] = 0;
		this->Data[5] = 1;
		this->Data[6] = 0;
		this->Data[7] = 0;
		
		this->Data[8]  = 0;
		this->Data[9]  = 0;
		this->Data[10] = 1;
		this->Data[11] = 0;
		
		this->Data[12] = 0;
		this->Data[13] = 0;
		this->Data[14] = 0;
		this->Data[15] = 1;
	}
		
	//--------------------------------------------------------------------------------------
	// Metodo para convertir la matriz en una matriz de ceros.
	//--------------------------------------------------------------------------------------
	void Matrix::SetZero (void)
	{
		for(int i = 0; i < MAX_MATRIX_RANGE; ++i)
			this->Data[i] = 0;
	}
	
	//--------------------------------------------------------------------------------------
	// Metodo para sumar dos matrices.
	//--------------------------------------------------------------------------------------
	Matrix Matrix::Add (const Matrix & obj) const
	{
		Matrix result;
		
		for(int i = 0; i < MAX_MATRIX_RANGE; ++i)
			result.Data[i] = this->Data[i] + obj.Data[i];

		return result;
	}
	
	//--------------------------------------------------------------------------------------
	// Metodo para restar dos matrices.
	//--------------------------------------------------------------------------------------
	Matrix Matrix::Subtract (const Matrix & obj) const
	{
		Matrix result;
		
		for(int i = 0; i < MAX_MATRIX_RANGE; ++i)
			result.Data[i] = this->Data[i] - obj.Data[i];

		return result;
	}
	
	//--------------------------------------------------------------------------------------
	// Metodo para multiplicar dos matrices.
	//--------------------------------------------------------------------------------------
	Matrix Matrix::Product (const Matrix & obj) const
	{
		Matrix result;
		
		result.Data[0] = this->Data[0] * obj.Data[0]  + this->Data[1] * obj.Data[4] +
						 this->Data[2] * obj.Data[8]  + this->Data[3] * obj.Data[12];

		result.Data[1] = this->Data[0] * obj.Data[1]  + this->Data[1] * obj.Data[5] +
						 this->Data[2] * obj.Data[9]  + this->Data[3] * obj.Data[13];

		result.Data[2] = this->Data[0] * obj.Data[2]  + this->Data[1] * obj.Data[6] +
						 this->Data[2] * obj.Data[10] + this->Data[3] * obj.Data[14];

		result.Data[3] = this->Data[0] * obj.Data[3]  + this->Data[1] * obj.Data[7] +
						 this->Data[2] * obj.Data[11] + this->Data[3] * obj.Data[15];
		

		result.Data[4] = this->Data[4] * obj.Data[0]  + this->Data[5] * obj.Data[4] +
						 this->Data[6] * obj.Data[8]  + this->Data[7] * obj.Data[12];

		result.Data[5] = this->Data[4] * obj.Data[1]  + this->Data[5] * obj.Data[5] +
						 this->Data[6] * obj.Data[9]  + this->Data[7] * obj.Data[13];

		result.Data[6] = this->Data[4] * obj.Data[2]  + this->Data[5] * obj.Data[6] +
						 this->Data[6] * obj.Data[10] + this->Data[7] * obj.Data[14];

		result.Data[7] = this->Data[4] * obj.Data[3]  + this->Data[5] * obj.Data[7] +
						 this->Data[6] * obj.Data[11] + this->Data[7] * obj.Data[15];
		

		result.Data[8]  = this->Data[8]  * obj.Data[0]  + this->Data[9]  * obj.Data[4] +
						  this->Data[10] * obj.Data[8]  + this->Data[11] * obj.Data[12];

		result.Data[9]  = this->Data[8]  * obj.Data[1]  + this->Data[9]  * obj.Data[5] +
						  this->Data[10] * obj.Data[9]  + this->Data[11] * obj.Data[13];

		result.Data[10] = this->Data[8]  * obj.Data[2]  + this->Data[9]  * obj.Data[6] +
						  this->Data[10] * obj.Data[10] + this->Data[11] * obj.Data[14];

		result.Data[11] = this->Data[8]  * obj.Data[3]  + this->Data[9]  * obj.Data[7] +
						  this->Data[10] * obj.Data[11] + this->Data[11] * obj.Data[15];
		

		result.Data[12] = this->Data[12] * obj.Data[0]  + this->Data[13] * obj.Data[4] +
						  this->Data[14] * obj.Data[8]  + this->Data[15] * obj.Data[12];

		result.Data[13] = this->Data[12] * obj.Data[1]  + this->Data[13] * obj.Data[5] +
						  this->Data[14] * obj.Data[9]  + this->Data[15] * obj.Data[13];

		result.Data[14] = this->Data[12] * obj.Data[2]  + this->Data[13] * obj.Data[6] +
						  this->Data[14] * obj.Data[10] + this->Data[15] * obj.Data[14];

		result.Data[15] = this->Data[12] * obj.Data[3]  + this->Data[13] * obj.Data[7] +
						  this->Data[14] * obj.Data[11] + this->Data[15] * obj.Data[15];

		return result;
	}

	//--------------------------------------------------------------------------------------
	// Metodo para modificar el valor de una posición.
	//--------------------------------------------------------------------------------------
	void Matrix::SetVal (GLuint row, GLuint col, GLfloat val)
	{
		GLuint index = row * 4 + col;

		if(index < MAX_MATRIX_RANGE)
			this->Data[index] = val;
	}

	//--------------------------------------------------------------------------------------
	// Metodo para modificar el valor de una posición.
	//--------------------------------------------------------------------------------------
	void Matrix::SetVal (GLuint index, GLfloat val)
	{
		if(index < MAX_MATRIX_RANGE)
			this->Data[index] = val;
	}

	//--------------------------------------------------------------------------------------
	// Metodo para obtener el valor de una posición.
	//--------------------------------------------------------------------------------------
	GLfloat Matrix::GetVal (GLuint row, GLuint col)
	{
		GLuint index = row * 4 + col;

		if(index < MAX_MATRIX_RANGE)
			return this->Data[index];
		else
			return 0;
	}

	//--------------------------------------------------------------------------------------
	// Metodo para obtener el valor de una posición.
	//--------------------------------------------------------------------------------------
	GLfloat Matrix::GetVal (GLuint index)
	{
		if(index < MAX_MATRIX_RANGE)
			return this->Data[index];
		else
			return 0;
	}

//******************************************************************************************
// Matrix.cpp
//******************************************************************************************