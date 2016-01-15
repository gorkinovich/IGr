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
#include "geometry.h"
//******************************************************************************************
// Constantes relevantes.
//******************************************************************************************
const char * FILE_TYPE    = "ANUBIS STATIC MESH";
const char * FILE_VERSION = "1.0";
//******************************************************************************************
// Miembros de la clase CStaticMesh.
//******************************************************************************************

	//**************************************************************************************
	// Constructores y funciones de copia.
	//**************************************************************************************

	//--------------------------------------------------------------------------------------
	// Constructor de la clase CStaticMesh.
	//--------------------------------------------------------------------------------------
	CStaticMesh::CStaticMesh () : Transformation()
	{
		this->Name = NULL;

		this->Transformation.GetMatrix(this->Matrix);

		this->NumObjects   = 0;
		this->NumMaterials = 0;
		
		this->Objects   = NULL;
		this->Materials = NULL;
	}

	//--------------------------------------------------------------------------------------
	// Constructor de la clase CStaticMesh.
	//--------------------------------------------------------------------------------------
	CStaticMesh::CStaticMesh (const CStaticMesh & obj)
	{
		this->CopyFrom(obj);
	}

	//--------------------------------------------------------------------------------------
	// Constructor de la clase CStaticMesh.
	//--------------------------------------------------------------------------------------
	CStaticMesh::~CStaticMesh ()
	{
		this->Release();
	}

	//--------------------------------------------------------------------------------------
	// Sobrecarga del operador igual.
	//--------------------------------------------------------------------------------------
	CStaticMesh & CStaticMesh::operator = (const CStaticMesh & obj)
	{
		this->CopyFrom(obj);
		return (*this);
	}

	//--------------------------------------------------------------------------------------
	// Método para copiar un objeto a otro.
	//--------------------------------------------------------------------------------------
	void CStaticMesh::CopyFrom (const CStaticMesh & obj)
	{
		//----------------------------------------------------------------------------------
		// Eliminamos el contenido del objeto.
		//----------------------------------------------------------------------------------
		appResetLastError();
		this->Release();

		//----------------------------------------------------------------------------------
		// Copiamos sus propiedades básicas.
		//----------------------------------------------------------------------------------
		this->Name           = Geometry::CopyString(obj.Name);
		this->Transformation = obj.Transformation;
		this->Transformation.GetMatrix(this->Matrix);

		this->NumObjects   = obj.NumObjects;
		this->NumMaterials = obj.NumMaterials;

		//----------------------------------------------------------------------------------
		// Y luego copiamos los arrays de objetos y materiales, pidiendo memoria para
		// cada uno de ellos, y comprobando que se ha logrado.
		//----------------------------------------------------------------------------------
		unsigned int i;
		
		this->Objects = new Geometry::CObject[this->NumObjects];
		if(this->Objects != NULL)
		{
			for(i = 0; i < this->NumObjects; ++i)
				this->Objects[i] = obj.Objects[i];
		}
		else
		{
			this->NumObjects = 0;
			appSetLastError(GEOERR_SMCPY_OBJSNULL);
		}

		this->Materials = new Geometry::CMaterial[this->NumMaterials];
		if(this->Materials != NULL)
		{
			for(i = 0; i < this->NumMaterials; ++i)
				this->Materials[i] = obj.Materials[i];
		}
		else
		{
			this->NumMaterials = 0;
			appSetLastError(GEOERR_SMCPY_MATSNULL);
		}
	}

	//**************************************************************************************
	// Lógica.
	//**************************************************************************************

	//--------------------------------------------------------------------------------------
	// Metodo para cargar un modelo desde un fichero.
	//--------------------------------------------------------------------------------------
	bool CStaticMesh::Load (const char * name)
	{
		//----------------------------------------------------------------------------------
		// Borramos el contenido del modelo.
		//----------------------------------------------------------------------------------
		appResetLastError();
		this->Release();

		//----------------------------------------------------------------------------------
		// Abrimos el fichero para ser leido.
		//----------------------------------------------------------------------------------
		FILE * file = fopen(name, "rb");

		if(file == NULL)
		{
			return appSetLastError(GEOERR_SMLOAD_FOPEN);
		}

		//----------------------------------------------------------------------------------
		// Comprobamos el tipo y la versión del fichero.
		//----------------------------------------------------------------------------------
		char * straux;

		straux = Geometry::ReadStringFromFile(file);
		if(strcmp(straux, FILE_TYPE) != 0)
		{
			free(straux);
			fclose(file);
			return appSetLastError(GEOERR_SMLOAD_BADTYPE);
		}
		
		free(straux);

		straux = Geometry::ReadStringFromFile(file);
		if(strcmp(straux, FILE_VERSION) != 0)
		{
			free(straux);
			fclose(file);
			return appSetLastError(GEOERR_SMLOAD_BADVER);
		}
		
		free(straux);

		//----------------------------------------------------------------------------------
		// Leemos el nombre y las transformaciones.
		//----------------------------------------------------------------------------------
		this->Name = Geometry::ReadStringFromFile(file);
		fread(this->Matrix, sizeof(GLfloat), 16, file);

		this->Transformation.Load(file);

		unsigned int i;

		//----------------------------------------------------------------------------------
		// Leemos todos los objetos del modelo.
		//----------------------------------------------------------------------------------
		fread(&(this->NumObjects), sizeof(unsigned int), 1, file);

    	this->Objects = new Geometry::CObject[this->NumObjects];
		if(this->Objects != NULL)
		{
    		for(i = 0; i < this->NumObjects; ++i)
	    	{
		    	this->Objects[i].Load(file);
			    if(appGetLastError())
    			{
	    			fclose(file);
		    		return false;
			    }
    		}
        }
		else
		{
            this->NumObjects = 0;
			appSetLastError(GEOERR_SMLOAD_OBJNULL);
		}

		//----------------------------------------------------------------------------------
		// Leemos todos los materiales del modelo.
		//----------------------------------------------------------------------------------
		fread(&(this->NumMaterials), sizeof(unsigned int), 1, file);
               
    	this->Materials = new Geometry::CMaterial[this->NumMaterials];
		if(this->Materials != NULL)
		{
    		for(i = 0; i < this->NumMaterials; ++i)
	    	{
		    	this->Materials[i].Load(file);
			    if(appGetLastError())
    			{
	    			fclose(file);
		    		return false;
			    }
    		}  
        }
		else
		{
            this->NumMaterials = 0;
			appSetLastError(GEOERR_SMLOAD_MATNULL);
		}
		
		//----------------------------------------------------------------------------------
		// Y finalmente cerramos el fichero.
		//----------------------------------------------------------------------------------
		fclose(file);

		return true;
	}

	//--------------------------------------------------------------------------------------
	// Metodo para salvar un modelo en un fichero.
	//--------------------------------------------------------------------------------------
	bool CStaticMesh::Save (const char * name)
	{
		//----------------------------------------------------------------------------------
		// Abrimos el fichero para ser escrito.
		//----------------------------------------------------------------------------------
		appResetLastError();
		FILE * file = fopen(name, "wb");

		if(file == NULL)
		{
			return appSetLastError(GEOERR_SMSAVE_FOPEN);
		}

		//----------------------------------------------------------------------------------
		// Escribimos el tipo y la versión del fichero.
		//----------------------------------------------------------------------------------
		fwrite(FILE_TYPE,    sizeof(char), strlen(FILE_TYPE)    + 1, file);
		fwrite(FILE_VERSION, sizeof(char), strlen(FILE_VERSION) + 1, file);

		//----------------------------------------------------------------------------------
		// Escribimos el nombre.
		//----------------------------------------------------------------------------------
        if(this->Name != NULL)
        {
		    fwrite(this->Name, sizeof(char), strlen(this->Name) + 1, file);
        }
        else
        {
            char zero = '\0';     
		    fwrite(&zero, sizeof(char), 1, file);
        }

		//----------------------------------------------------------------------------------
		// Escribimos las transformaciones.
		//----------------------------------------------------------------------------------
		fwrite(this->Matrix, sizeof(GLfloat), 16, file);

		this->Transformation.Save(file);

		unsigned int i;

		//----------------------------------------------------------------------------------
		// Escribimos todos los objetos del modelo.
		//----------------------------------------------------------------------------------
		fwrite(&(this->NumObjects), sizeof(unsigned int), 1, file);

		for(i = 0; i < this->NumObjects; ++i)
			this->Objects[i].Save(file);

		//----------------------------------------------------------------------------------
		// Escribimos todos los materiales del modelo.
		//----------------------------------------------------------------------------------
		fwrite(&(this->NumMaterials), sizeof(unsigned int), 1, file);

		for(i = 0; i < this->NumMaterials; ++i)
			this->Materials[i].Save(file);
		
		//----------------------------------------------------------------------------------
		// Y finalmente cerramos el fichero.
		//----------------------------------------------------------------------------------
		fclose(file);

		return true;
	}

	//--------------------------------------------------------------------------------------
	// Metodo para dibujar un modelo con OpenGL.
	//--------------------------------------------------------------------------------------
	void CStaticMesh::Draw (void)
	{
		glPushMatrix();
			glMultMatrixf(this->Matrix);

			for(unsigned int i = 0; i < this->NumObjects; ++i)
				this->Objects[i].Draw(this->Materials);

		glPopMatrix();
	}

	//--------------------------------------------------------------------------------------
	// Metodo para importar un modelo desde un fichero 3DS.
	//--------------------------------------------------------------------------------------
	bool CStaticMesh::Import (const char * name)
	{
		//----------------------------------------------------------------------------------
		// Primero eliminamos el contenido del objeto.
		//----------------------------------------------------------------------------------
		appResetLastError();
		this->Release();

		//----------------------------------------------------------------------------------
		// Luego cargamos en la clase para ficheros 3DS el modelo.
		//----------------------------------------------------------------------------------
		Model_3DS model;
		model.Load((char *) name);

		this->NumObjects   = model.numObjects;
		this->NumMaterials = model.numMaterials;

		//----------------------------------------------------------------------------------
		// Vamos leyendo objeto por objeto del modelo.
		//----------------------------------------------------------------------------------
		this->Objects = new Geometry::CObject[this->NumObjects];
		if(this->Objects != NULL)
		{
			for(unsigned int i = 0; i < this->NumObjects; ++i)
			{
				this->Objects[i].CopyFrom(model.Objects[i]);
			}
		}
		else
		{
			return appSetLastError(GEOERR_SMIMP_OBJSNULL);
		}

		//----------------------------------------------------------------------------------
		// Y por último leemos cada material del modelo.
		//----------------------------------------------------------------------------------
		this->Materials = new Geometry::CMaterial[this->NumMaterials];
		if(this->Materials != NULL)
		{
			for(unsigned int i = 0; i < this->NumMaterials; ++i)
			{
				this->Materials[i].CopyFrom(model.Materials[i]);
			}
		}
		else
		{
			return appSetLastError(GEOERR_SMIMP_MATSNULL);
		}

        return (appGetLastError() == EVERYTHING_ALL_RIGHT);
	}

	//--------------------------------------------------------------------------------------
	// Metodo para liberar el modelo cargado de la memoria.
	//--------------------------------------------------------------------------------------
	void CStaticMesh::Release (void)
	{
		//----------------------------------------------------------------------------------
		// Eliminamos el nombre y las transformaciones.
		//----------------------------------------------------------------------------------
		if(this->Name != NULL)
		{
			free(this->Name);
			this->Name = NULL;
		}

		this->Transformation.Reset();
		this->Transformation.GetMatrix(this->Matrix);

		//----------------------------------------------------------------------------------
		// Y luego eliminamos los objetos y los materiales.
		//----------------------------------------------------------------------------------
		this->NumObjects   = 0;
		this->NumMaterials = 0;

		if(this->Objects != NULL)
		{
			delete [] this->Objects;
			this->Objects = NULL;
		}
		
		if(this->Materials != NULL)
		{
			delete [] this->Materials;
			this->Materials = NULL;
		}
	}

	//**************************************************************************************
	// Gets.
	//**************************************************************************************

	Geometry::CObject & CStaticMesh::GetObject (unsigned int index)
	{
		if(index < this->NumObjects)
			return this->Objects[index];
		else
			return this->Objects[0];
	}

	//--------------------------------------------------------------------------------------

	Geometry::CMaterial & CStaticMesh::GetMaterial (unsigned int index)
	{
		if(index < this->NumMaterials)
			return this->Materials[index];
		else
			return this->Materials[0];
	}

	//**************************************************************************************
	// Sets.
	//**************************************************************************************
        
	void CStaticMesh::SetName (const char * name)
	{        
		if(this->Name != NULL)
		{
			free(this->Name);
			this->Name = NULL;
		}

        this->Name = strdup(name);
    }

	//--------------------------------------------------------------------------------------

	void CStaticMesh::SetMatrix (const GLfloat * matrix)
	{
		if(matrix != NULL)
		{
			for(int i = 0; i < 16; ++i)
				this->Matrix[i] = matrix[i];
		}
	}
	
	//--------------------------------------------------------------------------------------

	void CStaticMesh::SetMatrix (const Geometry::CTransformation & transformation)
	{
		this->Transformation = transformation;
		this->Transformation.GetMatrix(this->Matrix);
	}

	//--------------------------------------------------------------------------------------

	void CStaticMesh::SetObject (unsigned int index, const Geometry::CObject & object)
	{
		if(index < this->NumObjects)
		{
			this->Objects[index] = object;
		}
	}

	//--------------------------------------------------------------------------------------

	void CStaticMesh::SetMaterial (unsigned int index, const Geometry::CMaterial & material)
	{
		if(index < this->NumMaterials)
		{
			this->Materials[index] = material;
		}
	}

//******************************************************************************************
// Miembros de la clase xxx.
//******************************************************************************************

	//**************************************************************************************
	// Constructores y funciones de copia.
	//**************************************************************************************

	//--------------------------------------------------------------------------------------
	// Constructor de la clase xxx.
	//--------------------------------------------------------------------------------------

	//**************************************************************************************
	// Lógica.
	//**************************************************************************************

	//**************************************************************************************
	// Gets.
	//**************************************************************************************

	//**************************************************************************************
	// Sets.
	//**************************************************************************************

//******************************************************************************************
// geometry.cpp
//******************************************************************************************