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
#include "Light.h"
using namespace Yukino;
//******************************************************************************************
// Constructores, destructores y funciones de copia.
//******************************************************************************************

	//--------------------------------------------------------------------------------------
	// Constructor de la clase.
	//--------------------------------------------------------------------------------------
	Light::Light ()
	{
		int i;

		this->LightID = GL_LIGHT0;

		for(i = 0; i < 4; ++i)
		{
			this->Ambient[i]  = 1.0f;
			this->Diffuse[i]  = 1.0f;
			this->Specular[i] = 1.0f;
		}

		this->Position[0] = 0.0f;
		this->Position[1] = 0.0f;
		this->Position[2] = 1.0f;
		this->Position[3] = 0.0f;

		this->SpotDirection[0] =  0.0f;
		this->SpotDirection[1] =  0.0f;
		this->SpotDirection[2] = -1.0f;

		this->SpotExponent =   1.0f;
		this->SpotCutOff   = 180.0f;

		this->ConstantAttenuation  = 1.0f;
		this->LinearAttenuation    = 0.0f;
		this->QuadraticAttenuation = 0.0f;
	}

	//--------------------------------------------------------------------------------------
	// Destructor de la clase.
	//--------------------------------------------------------------------------------------
	Light::~Light ()
	{
	}

//******************************************************************************************
// Funciones miembro de la clase.
//******************************************************************************************

	void Light::Update (void)
	{
		glLightfv(this->LightID, GL_AMBIENT,  this->Ambient);
		glLightfv(this->LightID, GL_DIFFUSE,  this->Diffuse);
		glLightfv(this->LightID, GL_SPECULAR, this->Specular);

		glLightfv(this->LightID, GL_POSITION, this->Position);


		glLightfv(this->LightID, GL_SPOT_DIRECTION, this->SpotDirection);

		glLightf(this->LightID, GL_SPOT_EXPONENT, this->SpotExponent);
		glLightf(this->LightID, GL_SPOT_CUTOFF,   this->SpotCutOff);

		
		glLightf(this->LightID, GL_CONSTANT_ATTENUATION,  this->ConstantAttenuation);
		glLightf(this->LightID, GL_LINEAR_ATTENUATION,    this->LinearAttenuation);
		glLightf(this->LightID, GL_QUADRATIC_ATTENUATION, this->QuadraticAttenuation);
	}

//******************************************************************************************
// Light.cpp
//******************************************************************************************