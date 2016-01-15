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
#include "Line.h"
using namespace Yukino;
//******************************************************************************************
// Constructores, destructores y funciones de copia.
//******************************************************************************************

	//--------------------------------------------------------------------------------------
	// Constructor de la clase.
	//--------------------------------------------------------------------------------------
	LineManager::LineManager ()
	{
	}

	//--------------------------------------------------------------------------------------
	// Destructor de la clase.
	//--------------------------------------------------------------------------------------
	LineManager::~LineManager ()
	{
	}

//******************************************************************************************
// Funciones gets de la clase.
//******************************************************************************************

	GLfloat LineManager::GetWidthGranularity (void)
	{
		GLfloat granularity;
		
		glGetFloatv(GL_LINE_WIDTH_GRANULARITY, &granularity);

		return granularity;
	}

	void LineManager::GetWidthRange (GLfloat & minsize, GLfloat & maxsize)
	{
		GLfloat sizes[2];

		glGetFloatv(GL_LINE_WIDTH_RANGE, sizes);

		minsize = sizes[0];
		maxsize = sizes[1];
	}

	GLint LineManager::GetStippleRepeat (void)
	{
		GLint value;

		glGetIntegerv(GL_LINE_STIPPLE_REPEAT, &value);

		return value;
	}

	GLushort LineManager::GetStipplePattern (void)
	{
		GLint value;

		glGetIntegerv(GL_LINE_STIPPLE_PATTERN, &value);

		return (GLushort) value;
	}

//******************************************************************************************
// Line.cpp
//******************************************************************************************