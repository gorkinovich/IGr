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
#include "Material.h"
using namespace Yukino;
//******************************************************************************************
// Constructores, destructores y funciones de copia.
//******************************************************************************************

	//--------------------------------------------------------------------------------------
	// Constructor de la clase.
	//--------------------------------------------------------------------------------------
	Material::Material ()
	{
		this->Face = GL_FRONT;

		this->Ambient[0] = 0.2f;
		this->Ambient[1] = 0.2f;
		this->Ambient[2] = 0.2f;
		this->Ambient[3] = 1.0f;
		
		this->Diffuse[0] = 0.8f;
		this->Diffuse[1] = 0.8f;
		this->Diffuse[2] = 0.8f;
		this->Diffuse[3] = 1.0f;
		
		this->Specular[0] = 0.0f;
		this->Specular[1] = 0.0f;
		this->Specular[2] = 0.0f;
		this->Specular[3] = 1.0f;
		
		this->Emission[0] = 0.0f;
		this->Emission[1] = 0.0f;
		this->Emission[2] = 0.0f;
		this->Emission[3] = 1.0f;

		this->Shininess = 0.0f;
	}

	//--------------------------------------------------------------------------------------
	// Destructor de la clase.
	//--------------------------------------------------------------------------------------
	Material::~Material ()
	{
	}

//******************************************************************************************
// Funciones miembro de la clase.
//******************************************************************************************

	void Material::Update (void)
	{
		glMaterialfv(this->Face, GL_AMBIENT,  this->Ambient);
		glMaterialfv(this->Face, GL_DIFFUSE,  this->Diffuse);
		glMaterialfv(this->Face, GL_SPECULAR, this->Specular);

		glMaterialf(this->Face, GL_SHININESS, this->Shininess);

		glMaterialfv(this->Face, GL_EMISSION, this->Emission);
	}

//******************************************************************************************
// Material.cpp
//******************************************************************************************