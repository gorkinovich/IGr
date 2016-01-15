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
#include "Point2D.h"
using namespace Yukino;
//******************************************************************************************
// Constructores, destructores y funciones de copia.
//******************************************************************************************

	//--------------------------------------------------------------------------------------
	// Constructores de la clase.
	//--------------------------------------------------------------------------------------
	Point2D::Point2D ()
	{
		this->Data[0] = 0;
		this->Data[1] = 0;
		this->Data[2] = 0;
		this->Data[3] = 1;
	}

	Point2D::Point2D (GLfloat x, GLfloat y)
	{
		this->Data[0] = x;
		this->Data[1] = y;
		this->Data[2] = 0;
		this->Data[3] = 1;
	}

	Point2D::Point2D (const Point2D & obj)
	{
		this->Data[0] = obj.Data[0];
		this->Data[1] = obj.Data[1];
		this->Data[2] = 0;
		this->Data[3] = 1;
	}

	//--------------------------------------------------------------------------------------
	// Destructor de la clase.
	//--------------------------------------------------------------------------------------
	Point2D::~Point2D ()
	{
	}

//******************************************************************************************
// Point2D.cpp
//******************************************************************************************