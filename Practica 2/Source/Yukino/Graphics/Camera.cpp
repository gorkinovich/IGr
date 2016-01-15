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
#include "Camera.h"
using namespace Yukino;
//******************************************************************************************
// Constructores, destructores y funciones de copia.
//******************************************************************************************

	//--------------------------------------------------------------------------------------
	// Constructor de la clase.
	//--------------------------------------------------------------------------------------
	CameraManager::CameraManager ()
	{
		this->Roll  = 0.0f;
		this->Pitch = 0.0f;
		this->Yaw   = 0.0f;

		this->EyeX = 0.0f;
		this->EyeY = 0.0f;
		this->EyeZ = 1.0f;

		this->CenterX =  0.0f;
		this->CenterY =  0.0f;
		this->CenterZ = -1.0f;

		this->UpX = 0.0f;
		this->UpY = 1.0f;
		this->UpZ = 0.0f;

		this->Mode = CAMERAMODE_RPYPOS;
	}

	//--------------------------------------------------------------------------------------
	// Destructor de la clase.
	//--------------------------------------------------------------------------------------
	CameraManager::~CameraManager ()
	{
	}

//******************************************************************************************
// Funciones miembro de la clase.
//******************************************************************************************

	void CameraManager::Update (void)
	{
		switch(this->Mode)
		{
		case CAMERAMODE_RPYPOS:
			// pitch indica el giro en el eje X
			glRotatef(this->Pitch, 1.0f, 0.0f, 0.0f);

			// yaw indica el giro en el eje Y
			glRotatef(this->Yaw, 0.0f, 1.0f, 0.0f);

			// roll indica el giro en el eje Z
			glRotatef(this->Roll, 0.0f, 0.0f, 1.0f);

			// y movemos la camara a unas coordenadas
			glTranslatef(-this->EyeX, -this->EyeY, -this->EyeZ);
			break;
			
		case CAMERAMODE_LOOKAT:
			gluLookAt(this->EyeX, this->EyeY, this->EyeZ, this->CenterX, this->CenterY,
					  this->CenterZ, this->UpX, this->UpY, this->UpZ);
			break;
		}
	}

//******************************************************************************************
// Camera.cpp
//******************************************************************************************