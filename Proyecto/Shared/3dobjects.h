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
#ifndef _ANUBIS_3DOBJECTS_H_
#define _ANUBIS_3DOBJECTS_H_
//******************************************************************************************
// Includes.
//******************************************************************************************
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
//------------------------------------------------------------------------------------------
#include <gl/gl.h>
#include <gl/glu.h>
//------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//------------------------------------------------------------------------------------------
#include "3ds/Model_3DS.h"
#include "error.h"
#include "extensions.h"
#include "content.h"
#include "color.h"
#include "3dmath.h"
//******************************************************************************************
// Errores.
//******************************************************************************************
#define OBJ3DERR_COPYSTR_NULL      3001
#define OBJ3DERR_COPYFLT_NULL      3002
#define OBJ3DERR_COPYUINT_NULL     3003
#define OBJ3DERR_OBJCPYF_NEVAT     3004
#define OBJ3DERR_OBJCPYF_FACESNULL 3005
#define OBJ3DERR_OBJCPYF_VECSNULL  3006
#define OBJ3DERR_OBJLOAD_FACESNULL 3007
#define OBJ3DERR_OBJLOAD_VECSNULL  3008
#define OBJ3DERR_FCSLOAD_INDXSNULL 3009
//******************************************************************************************
// Constantes de tamaños.
//******************************************************************************************
namespace Geometry
{
	const unsigned int MAX_VEC2 = 2;
	const unsigned int MAX_VEC3 = 3;
	const unsigned int MAX_VEC4 = 4;

//******************************************************************************************
// Funciones auxiliares.
//******************************************************************************************

	char * ReadStringFromFile (FILE * file);

	char         * CopyString   (const char * src);
	GLfloat      * CopyFloatVec (const GLfloat * src, unsigned int len);
	unsigned int * CopyUIntVec  (const unsigned int * src, unsigned int len);
	unsigned int * CopyUIntVec  (const unsigned short * src, unsigned int len);

//******************************************************************************************
// Clase para almacenar una transformación.
//******************************************************************************************

	class CTransformation
	{
	//--------------------------------------------------------------------------------------
	// Parte publica.
	//--------------------------------------------------------------------------------------
	public:
		//----------------------------------------------------------------------------------
		// Datos.
		//----------------------------------------------------------------------------------
		GLfloat Rotation[3];
		GLfloat Position[3];
		GLfloat Scale[3];

		//----------------------------------------------------------------------------------
		// Constructores y funciones de copia.
		//----------------------------------------------------------------------------------
		CTransformation ();
		CTransformation (const CTransformation & obj);
		virtual ~CTransformation ();

		virtual CTransformation & operator = (const CTransformation & obj);
		virtual void CopyFrom (const CTransformation & obj);
		
		//----------------------------------------------------------------------------------
		// Lógica.
		//----------------------------------------------------------------------------------
		void Reset (void);
		void Load (FILE * file);
		void Save (FILE * file);

		//----------------------------------------------------------------------------------
		// Gets.
		//----------------------------------------------------------------------------------
		void GetMatrix (GLfloat * matrix);
	};

//******************************************************************************************
// Clase para almacenar un material.
//******************************************************************************************

	//--------------------------------------------------------------------------------------
	// Enumerado TextureEffect.
	//--------------------------------------------------------------------------------------
	typedef enum
	{
		NoneEffect = 0,
		NormalMapping = 1,
		ParallaxMapping = 2
	} TextureEffect;

	//--------------------------------------------------------------------------------------
	// Clase CMaterial.
	//--------------------------------------------------------------------------------------
	class CMaterial
	{
	//--------------------------------------------------------------------------------------
	// Parte protegida.
	//--------------------------------------------------------------------------------------
	protected:
		void Reset (void);

	//--------------------------------------------------------------------------------------
	// Parte publica.
	//--------------------------------------------------------------------------------------
	public:
		//----------------------------------------------------------------------------------
		// Datos.
		//----------------------------------------------------------------------------------
		char * Name;

		GLfloat Ambient[4];  // 0.2f, 0.2f, 0.2f, 1.0f ( 51,  51,  51, 255)
		GLfloat Diffuse[4];  // 0.8f, 0.8f, 0.8f, 1.0f (204, 204, 204, 255)
		GLfloat Specular[4]; // 0.0f, 0.0f, 0.0f, 1.0f
		GLfloat Shininess;   // 0.0f
		GLfloat Emission[4]; // 0.0f, 0.0f, 0.0f, 1.0f

		GLfloat Color[4];    // 1.0f, 1.0f, 1.0f, 1.0f

		bool Textured;

		CTexture * Texture;
		CTexture * NormalMap;
		CTexture * HeightMap;
		TextureEffect Effect;

		GLfloat ScaleBiasFactor[2]; // 0.02f, 0.015f

		//----------------------------------------------------------------------------------
		// Constructores y funciones de copia.
		//----------------------------------------------------------------------------------
		CMaterial ();
		CMaterial (const CMaterial & obj);
		virtual ~CMaterial ();

		virtual CMaterial & operator = (const CMaterial & obj);
		virtual void CopyFrom (const CMaterial & obj);
		virtual void CopyFrom (const Model_3DS::Material & obj);
		
		//----------------------------------------------------------------------------------
		// Lógica.
		//----------------------------------------------------------------------------------
		void UpdateBegin (void);
		void UpdateEnd (void);		
		void Update (void);
		
		void Load (FILE * file);
		void Save (FILE * file);
	};

//******************************************************************************************
// Clase para almacenar las caras de un objeto.
//******************************************************************************************

	class CFaces
	{
	//--------------------------------------------------------------------------------------
	// Parte protegida.
	//--------------------------------------------------------------------------------------
	protected:
		void Reset (void);

	//--------------------------------------------------------------------------------------
	// Parte publica.
	//--------------------------------------------------------------------------------------
	public:
		//----------------------------------------------------------------------------------
		// Datos.
		//----------------------------------------------------------------------------------
		unsigned int Material;
		unsigned int NumIndexes;
		unsigned int * Indexes;

		//----------------------------------------------------------------------------------
		// Constructores y funciones de copia.
		//----------------------------------------------------------------------------------
		CFaces ();
		CFaces (const CFaces & obj);
		virtual ~CFaces ();

		virtual CFaces & operator = (const CFaces & obj);
		virtual void CopyFrom (const CFaces & obj);
		virtual void CopyFrom (const Model_3DS::MaterialFaces & obj);
		
		//----------------------------------------------------------------------------------
		// Lógica.
		//----------------------------------------------------------------------------------
		void Load (FILE * file);
		void Save (FILE * file);
	};

//******************************************************************************************
// Clase para almacenar un objeto tridimensional.
//******************************************************************************************

	class CObject
	{
	//--------------------------------------------------------------------------------------
	// Parte protegida.
	//--------------------------------------------------------------------------------------
	protected:
		void CalculateTangent (GLfloat * p1, GLfloat * p2, GLfloat * p3, GLfloat * uv1,
							   GLfloat * uv2, GLfloat * uv3, GLfloat * normal,
							   GLfloat * tangent);

	//--------------------------------------------------------------------------------------
	// Parte publica.
	//--------------------------------------------------------------------------------------
	public:
		//----------------------------------------------------------------------------------
		// Datos.
		//----------------------------------------------------------------------------------
		char * Name;
		GLfloat Matrix[16];

		CTransformation Transformation;

		bool Textured;

		unsigned int NumVertexes;

		GLfloat * Vertexes;
		GLfloat * Normals;
		GLfloat * Tangents;
		GLfloat * TexCoords;

		unsigned int NumFaces;

		CFaces * Faces;

		//----------------------------------------------------------------------------------
		// Constructores y funciones de copia.
		//----------------------------------------------------------------------------------
		CObject ();
		CObject (const CObject & obj);
		virtual ~CObject ();

		virtual CObject & operator = (const CObject & obj);
		virtual void CopyFrom (const CObject & obj);
		virtual void CopyFrom (const Model_3DS::Object & obj);
		
		//----------------------------------------------------------------------------------
		// Lógica.
		//----------------------------------------------------------------------------------
		void CalculateTangents (void);
		void Draw (CMaterial * Materials);
		void Release (void);
		
		void Load (FILE * file);
		void Save (FILE * file);
	};
}
//******************************************************************************************
#endif
//******************************************************************************************
// 3dobjects.h
//******************************************************************************************