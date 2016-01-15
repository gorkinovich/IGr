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
#include "Graphics.h"
#include "../Log.h"
using namespace Yukino;
//******************************************************************************************
// Propiedades estáticas de la clase.
//******************************************************************************************

	GraphicsManager * GraphicsManager::Instance = NULL;

//******************************************************************************************
// Constructores, destructores y funciones de copia.
//******************************************************************************************

	//--------------------------------------------------------------------------------------
	// Constructor de la clase.
	//--------------------------------------------------------------------------------------
	GraphicsManager::GraphicsManager ()
	{
	}

	//--------------------------------------------------------------------------------------
	// Destructor de la clase.
	//--------------------------------------------------------------------------------------
	GraphicsManager::~GraphicsManager ()
	{
	}

//******************************************************************************************
// Funciones miembro de la clase.
//******************************************************************************************

	//--------------------------------------------------------------------------------------
	// Método para obtener la instancia de la clase.
	//--------------------------------------------------------------------------------------
	GraphicsManager * GraphicsManager::GetInstance (void)
	{
		if(GraphicsManager::Instance == NULL)
			GraphicsManager::Instance = new GraphicsManager();

		return GraphicsManager::Instance;
	}

//******************************************************************************************
// Funciones gets de la clase.
//******************************************************************************************

//******************************************************************************************
// Funciones sets de la clase.
//******************************************************************************************

//******************************************************************************************
// Graphics.cpp
//******************************************************************************************