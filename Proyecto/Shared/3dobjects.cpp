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
// Funciones auxiliares.
//******************************************************************************************
namespace Geometry
{
	//--------------------------------------------------------------------------------------
	// Función para leer una cadena de un fichero.
	//--------------------------------------------------------------------------------------
	char * ReadStringFromFile (FILE * file)
	{
		int i = 0;
		char straux[201];
		char caux;

		memset(straux, 0, 201);

		do{
			fread(&caux, sizeof(char), 1, file);
			straux[i] = caux; ++i;
		}while((feof(file) == 0) && (caux != '\0') && (i < 200));

		return strdup(straux);
	}

	//--------------------------------------------------------------------------------------
	// Función para copiar una cadena reservando memoria para esta.
	//--------------------------------------------------------------------------------------
	char * CopyString (const char * src)
	{
		if(src == NULL) return NULL;
		char * dst = strdup(src);
		if(dst == NULL) appSetLastError(OBJ3DERR_COPYSTR_NULL);
		return dst;
	}
	
	//--------------------------------------------------------------------------------------
	// Función para copiar un array de floats.
	//--------------------------------------------------------------------------------------
	GLfloat * CopyFloatVec (const GLfloat * src, unsigned int len)
	{
		if(src == NULL) return NULL;

		GLfloat * dst = (GLfloat *) malloc(sizeof(GLfloat) * len);
		if(dst == NULL) appSetLastError(OBJ3DERR_COPYFLT_NULL);

		for(unsigned int i = 0; i < len; ++i)
		{
			dst[i] = src[i];
		}

		return dst;
	}
	
	//--------------------------------------------------------------------------------------
	// Función para copiar un array de enteros.
	//--------------------------------------------------------------------------------------
	unsigned int * CopyUIntVec (const unsigned int * src, unsigned int len)
	{
		if(src == NULL) return NULL;

		unsigned int * dst = (unsigned int *) malloc(sizeof(unsigned int) * len);
		if(dst == NULL) appSetLastError(OBJ3DERR_COPYUINT_NULL);

		for(unsigned int i = 0; i < len; ++i)
		{
			dst[i] = src[i];
		}

		return dst;
	}
	
	//--------------------------------------------------------------------------------------
	// Función para copiar un array de enteros.
	//--------------------------------------------------------------------------------------
	unsigned int * CopyUIntVec (const unsigned short * src, unsigned int len)
	{
		if(src == NULL) return NULL;

		unsigned int * dst = (unsigned int *) malloc(sizeof(unsigned int) * len);
		if(dst == NULL) appSetLastError(OBJ3DERR_COPYUINT_NULL);

		for(unsigned int i = 0; i < len; ++i)
		{
			dst[i] = src[i];
		}

		return dst;
	}
}
//******************************************************************************************
// 3dobjects.cpp
//******************************************************************************************