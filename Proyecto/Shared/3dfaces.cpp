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
// Miembros de la clase CFaces.
//******************************************************************************************
namespace Geometry
{
	//**************************************************************************************
	// Constructores y funciones de copia.
	//**************************************************************************************

	//--------------------------------------------------------------------------------------
	// Constructor de la clase CFaces.
	//--------------------------------------------------------------------------------------
	CFaces::CFaces ()
	{
		this->Material   = 0;
		this->NumIndexes = 0;
		this->Indexes    = NULL;
	}

	//--------------------------------------------------------------------------------------
	// Constructor copia de la clase CFaces.
	//--------------------------------------------------------------------------------------
	CFaces::CFaces (const CFaces & obj)
	{
		this->CopyFrom(obj);
	}

	//--------------------------------------------------------------------------------------
	// Destructor de la clase CFaces.
	//--------------------------------------------------------------------------------------
	CFaces::~CFaces ()
	{
		this->Reset();
	}

	//--------------------------------------------------------------------------------------
	// Sobrecarga del operador igual.
	//--------------------------------------------------------------------------------------
	CFaces & CFaces::operator = (const CFaces & obj)
	{
		this->CopyFrom(obj);
		return (*this);
	}

	//--------------------------------------------------------------------------------------
	// Método para copiar un objeto a otro.
	//--------------------------------------------------------------------------------------
	void CFaces::CopyFrom (const CFaces & obj)
	{
		appResetLastError();
		this->Reset();

		this->Material   = obj.Material;
		this->NumIndexes = obj.NumIndexes;
		
		this->Indexes = CopyUIntVec(obj.Indexes, obj.NumIndexes);
	}

	//--------------------------------------------------------------------------------------
	// Método para copiar un conjunto de caras del 3DS en el objeto.
	//--------------------------------------------------------------------------------------
	void CFaces::CopyFrom (const Model_3DS::MaterialFaces & obj)
	{
		appResetLastError();
		this->Reset();
		
		this->Material   = ((obj.MatIndex    > 0) ? obj.MatIndex    : 0);
		this->NumIndexes = ((obj.numSubFaces > 0) ? obj.numSubFaces : 0);
		
		this->Indexes = CopyUIntVec(obj.subFaces, this->NumIndexes);
	}

	//**************************************************************************************
	// Lógica.
	//**************************************************************************************

	//--------------------------------------------------------------------------------------
	// Método para inicializar o borrar un conjunto de caras.
	//--------------------------------------------------------------------------------------
	void CFaces::Reset (void)
	{
		if(this->Indexes != NULL)
		{
			free(this->Indexes);
			this->Indexes = NULL;
		}

		this->Material   = 0;
		this->NumIndexes = 0;
	}

	//--------------------------------------------------------------------------------------
	// Método para cargar de un fichero el objeto.
	//--------------------------------------------------------------------------------------
	void CFaces::Load (FILE * file)
	{
		if(file != NULL)
		{
			this->Reset();

			fread(&(this->Material),   sizeof(unsigned int), 1, file);
			fread(&(this->NumIndexes), sizeof(unsigned int), 1, file);

			this->Indexes = (unsigned int *) malloc(sizeof(unsigned int) * this->NumIndexes);
			if(this->Indexes != NULL)
			{
				fread(this->Indexes, sizeof(unsigned int), this->NumIndexes, file);
			}
			else
			{
				appSetLastError(OBJ3DERR_FCSLOAD_INDXSNULL);
			}
		}
	}
	
	//--------------------------------------------------------------------------------------
	// Método para salvar a un fichero el objeto.
	//--------------------------------------------------------------------------------------
	void CFaces::Save (FILE * file)
	{
		if(file != NULL)
		{
			fwrite(&(this->Material),   sizeof(unsigned int), 1, file);
			fwrite(&(this->NumIndexes), sizeof(unsigned int), 1, file);

			fwrite(this->Indexes, sizeof(unsigned int), this->NumIndexes, file);
		}
	}
}
//******************************************************************************************
// 3dfaces.cpp
//******************************************************************************************