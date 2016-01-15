//******************************************************************************************
// Anubis Editor 1.0 - A 3D Adventure Game Engine.
// Copyright (C) 2006-2007  Gorka Suárez García
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//******************************************************************************************
#include "3dobjects.h"
//******************************************************************************************
// Miembros de la clase CTransformation.
//******************************************************************************************
namespace Geometry
{
	//**************************************************************************************
	// Constructores y funciones de copia.
	//**************************************************************************************

	//--------------------------------------------------------------------------------------
	// Constructor de la clase CTransformation.
	//--------------------------------------------------------------------------------------
	CTransformation::CTransformation ()
	{
		this->Reset();
	}

	//--------------------------------------------------------------------------------------
	// Constructor copia de la clase CTransformation.
	//--------------------------------------------------------------------------------------
	CTransformation::CTransformation (const CTransformation & obj)
	{
		this->CopyFrom(obj);
	}

	//--------------------------------------------------------------------------------------
	// Destructor de la clase CTransformation.
	//--------------------------------------------------------------------------------------
	CTransformation::~CTransformation ()
	{
		this->Reset();
	}

	//--------------------------------------------------------------------------------------
	// Sobrecarga del operador igual.
	//--------------------------------------------------------------------------------------
	CTransformation & CTransformation::operator = (const CTransformation & obj)
	{
		this->CopyFrom(obj);
		return (*this);
	}

	//--------------------------------------------------------------------------------------
	// Método para copiar un objeto a otro.
	//--------------------------------------------------------------------------------------
	void CTransformation::CopyFrom (const CTransformation & obj)
	{
		for(unsigned int i = 0; i < MAX_VEC3; ++i)
		{
			Rotation[i] = obj.Rotation[i];
			Position[i] = obj.Position[i];
			Scale[i]    = obj.Scale[i];
		}
	}

	//**************************************************************************************
	// Logica.
	//**************************************************************************************

	//--------------------------------------------------------------------------------------
	// Método para inicializar el objeto.
	//--------------------------------------------------------------------------------------
	void CTransformation::Reset (void)
	{
		for(unsigned int i = 0; i < MAX_VEC3; ++i)
		{
			this->Rotation[i] = 0.0f;
			this->Position[i] = 0.0f;
			this->Scale[i]    = 1.0f;
		}
	}

	//--------------------------------------------------------------------------------------
	// Método para cargar de un fichero el objeto.
	//--------------------------------------------------------------------------------------
	void CTransformation::Load (FILE * file)
	{
		if(file != NULL)
		{
			this->Reset();

			fread(this->Rotation, sizeof(GLfloat), MAX_VEC3, file);
			fread(this->Position, sizeof(GLfloat), MAX_VEC3, file);
			fread(this->Scale,    sizeof(GLfloat), MAX_VEC3, file);
		}
	}
	
	//--------------------------------------------------------------------------------------
	// Método para salvar a un fichero el objeto.
	//--------------------------------------------------------------------------------------
	void CTransformation::Save (FILE * file)
	{
		if(file != NULL)
		{
			fwrite(this->Rotation, sizeof(GLfloat), MAX_VEC3, file);
			fwrite(this->Position, sizeof(GLfloat), MAX_VEC3, file);
			fwrite(this->Scale,    sizeof(GLfloat), MAX_VEC3, file);
		}
	}

	//**************************************************************************************
	// Gets.
	//**************************************************************************************

	void CTransformation::GetMatrix (GLfloat * matrix)
	{
		if(matrix != NULL)
		{
			glPushMatrix();
				glLoadIdentity();
                              
				glTranslatef(this->Position[0], this->Position[1], this->Position[2]);
                
				glRotatef(this->Rotation[0], 1.0f, 0.0f, 0.0f);
				glRotatef(this->Rotation[1], 0.0f, 1.0f, 0.0f);
				glRotatef(this->Rotation[2], 0.0f, 0.0f, 1.0f);

				glScalef(this->Scale[0], this->Scale[1], this->Scale[2]);

				glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
			glPopMatrix();
		}
	}
}
//******************************************************************************************
// 3dtransf.cpp
//******************************************************************************************