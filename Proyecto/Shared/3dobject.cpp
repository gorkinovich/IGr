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
#include "shaders.h"
//******************************************************************************************
// Miembros de la clase CObject.
//******************************************************************************************
namespace Geometry
{
	//**************************************************************************************
	// Constructores y funciones de copia.
	//**************************************************************************************

	//--------------------------------------------------------------------------------------
	// Constructor de la clase CObject.
	//--------------------------------------------------------------------------------------
	CObject::CObject () : Transformation()
	{
		this->Name = NULL;
		this->Transformation.GetMatrix(this->Matrix);

		this->Textured = false;

		this->NumVertexes = 0;
		this->Vertexes    = NULL;
		this->Normals     = NULL;
		this->Tangents    = NULL;
		this->TexCoords   = NULL;

		this->NumFaces = 0;
		this->Faces    = NULL;
	}

	//--------------------------------------------------------------------------------------
	// Constructor copia de la clase CObject.
	//--------------------------------------------------------------------------------------
	CObject::CObject (const CObject & obj)
	{
		this->CopyFrom(obj);
	}

	//--------------------------------------------------------------------------------------
	// Destructor de la clase CObject.
	//--------------------------------------------------------------------------------------
	CObject::~CObject ()
	{
		this->Release();
	}

	//--------------------------------------------------------------------------------------
	// Sobrecarga del operador igual.
	//--------------------------------------------------------------------------------------
	CObject & CObject::operator = (const CObject & obj)
	{
		this->CopyFrom(obj);
		return (*this);
	}
	
	//--------------------------------------------------------------------------------------
	// Método para copiar un objeto a otro.
	//--------------------------------------------------------------------------------------
	void CObject::CopyFrom (const CObject & obj)
	{
		//----------------------------------------------------------------------------------
		// Eliminamos el contenido del objeto.
		//----------------------------------------------------------------------------------
		appResetLastError();
		this->Release();
		
		//----------------------------------------------------------------------------------
		// Copiamos sus propiedades básicas.
		//----------------------------------------------------------------------------------
		this->Name = CopyString(obj.Name);

		this->Transformation = obj.Transformation;
		this->Textured       = obj.Textured;
		this->NumVertexes    = obj.NumVertexes;
		this->NumFaces       = obj.NumFaces;
		
		this->Transformation.GetMatrix(this->Matrix);

		//----------------------------------------------------------------------------------
		// Y luego copiamos los arrays de valores. Por cierto, muy importante es recordar
		// que el número de vértices no es el número de floats en los arrays, por ello
		// hay que multiplicarlo por 3 para obtener el tamaño total.
		//----------------------------------------------------------------------------------
		this->Vertexes  = CopyFloatVec(obj.Vertexes,  this->NumVertexes * MAX_VEC3);
		this->Normals   = CopyFloatVec(obj.Normals,   this->NumVertexes * MAX_VEC3);
		this->Tangents  = CopyFloatVec(obj.Tangents,  this->NumVertexes * MAX_VEC3);
		this->TexCoords = CopyFloatVec(obj.TexCoords, this->NumVertexes * MAX_VEC2);

		if((this->Vertexes == NULL) || (this->Normals == NULL) ||
		   (this->Tangents == NULL) || (this->TexCoords == NULL))
		{
			appSetLastError(OBJ3DERR_OBJCPYF_VECSNULL);
			return;
		}

		//----------------------------------------------------------------------------------
		// Por último copiaremos los conjuntos de caras del modelo.
		//----------------------------------------------------------------------------------
		this->Faces = new CFaces[this->NumFaces];
		if(this->Faces != NULL)
		{
			for(unsigned int i = 0; i < this->NumFaces; ++i)
				this->Faces[i] = obj.Faces[i];
		}
		else
		{
			appSetLastError(OBJ3DERR_OBJCPYF_FACESNULL);
		}
	}

	//--------------------------------------------------------------------------------------
	// Método para copiar un objeto del 3DS en el objeto.
	//--------------------------------------------------------------------------------------
	void CObject::CopyFrom (const Model_3DS::Object & obj)
	{
		//----------------------------------------------------------------------------------
		// Eliminamos el contenido del objeto.
		//----------------------------------------------------------------------------------
		appResetLastError();
		this->Release();

		//----------------------------------------------------------------------------------
		// Copiamos el nombre y la transformación.
		//----------------------------------------------------------------------------------
		this->Name = CopyString(obj.name);
		
		this->Transformation.Rotation[0] = obj.rot.x;
		this->Transformation.Rotation[1] = obj.rot.y;
		this->Transformation.Rotation[2] = obj.rot.z;
		
		this->Transformation.Position[0] = obj.pos.x;
		this->Transformation.Position[1] = obj.pos.y;
		this->Transformation.Position[2] = obj.pos.z;
		
		this->Transformation.Scale[0] = 1.0f;
		this->Transformation.Scale[1] = 1.0f;
		this->Transformation.Scale[2] = 1.0f;
		
		this->Transformation.GetMatrix(this->Matrix);

		//----------------------------------------------------------------------------------
		// Copiamos el resto de propiedades, comprobando que el array de coordenadas de
		// textura sea igual en número de elementos al de vértices. Por cierto, muy
		// importante es recordar que el número de vértices no es el número de floats en
		// los arrays, por ello hay que multiplicarlo por 3 para obtener el tamaño total.
		//----------------------------------------------------------------------------------
		if(obj.numVerts != obj.numTexCoords)
		{
			appSetLastError(OBJ3DERR_OBJCPYF_NEVAT);
			return;
		}
		
		this->Textured    = obj.textured;
		this->NumVertexes = ((obj.numVerts    > 0) ? obj.numVerts    : 0);
		this->NumFaces    = ((obj.numMatFaces > 0) ? obj.numMatFaces : 0);

		this->Vertexes  = CopyFloatVec(obj.Vertexes,  this->NumVertexes * MAX_VEC3);
		this->Normals   = CopyFloatVec(obj.Normals,   this->NumVertexes * MAX_VEC3);
		this->TexCoords = CopyFloatVec(obj.TexCoords, this->NumVertexes * MAX_VEC2);
		
		unsigned int size = sizeof(GLfloat) * this->NumVertexes * MAX_VEC3;
		this->Tangents = (GLfloat *) malloc(size);

		if((this->Vertexes == NULL) || (this->Normals == NULL) ||
		   (this->Tangents == NULL) || (this->TexCoords == NULL))
		{
			appSetLastError(OBJ3DERR_OBJCPYF_VECSNULL);
			return;
		}

		//----------------------------------------------------------------------------------
		// Por último copiaremos los conjuntos de caras del modelo.
		//----------------------------------------------------------------------------------
		this->Faces = new CFaces[this->NumFaces];
		if(this->Faces != NULL)
		{
			for(unsigned int i = 0; i < this->NumFaces; ++i)
			{
				this->Faces[i].CopyFrom(obj.MatFaces[i]);
				if(appGetLastError()) return;
			}

			this->CalculateTangents();
		}
		else
		{
			appSetLastError(OBJ3DERR_OBJCPYF_FACESNULL);
		}
	}

	//**************************************************************************************
	// Lógica.
	//**************************************************************************************

	//--------------------------------------------------------------------------------------
	// Método para calcular la tangente del punto que querramos en relación a la normal.
	//--------------------------------------------------------------------------------------
	void CObject::CalculateTangent (GLfloat * p1, GLfloat * p2, GLfloat * p3,
									GLfloat * uv1, GLfloat * uv2, GLfloat * uv3,
									GLfloat * normal, GLfloat * tangent)
	{
		//----------------------------------------------------------------------------------
		// Lo primero es calcular el vector que se forma de p1 a p2, y de p1 a p3, para
		// poder hacer los pertinentes calculos. También para las coordenadas de textura
		// es necesario calcular los 2 vectores de las aristas.
		//----------------------------------------------------------------------------------
		GLfloat e1[3];   Vec3Sub(e1, p2, p1);
		GLfloat e2[3];   Vec3Sub(e2, p3, p1);
		GLfloat e1uv[2]; Vec2Sub(e1uv, uv2, uv1);
		GLfloat e2uv[2]; Vec2Sub(e2uv, uv3, uv1);

		//----------------------------------------------------------------------------------
		// Luego calculamos un valor que necesitaremos para el cálculo de la tangente:
		//    cp = e1uv.y * e2uv.x - e1uv.x * e2uv.y;
		//----------------------------------------------------------------------------------
		float cp = e1uv[1] * e2uv[0] - e1uv[0] * e2uv[1];

		//----------------------------------------------------------------------------------
		// Si el valor no es cero podemos calcular la tangente con lo siguiente:
		//    e2   = e2 * e1uv.y;
		//    e1   = e1 * e2uv.y;
		//    auxt = e2 - e1;
		//    auxt = auxt * (1.0f /cp);
		//    aux2 = normal * dot(normal, auxt);
		//    auxt = auxt - aux2;
		//    tang = normalize(auxt);
		//----------------------------------------------------------------------------------
		if(cp != 0.0f)
		{
			GLfloat auxt[3];
			GLfloat aux2[3];

			Vec3Mul(e2, e2, e1uv[1]);
			Vec3Mul(e1, e1, e2uv[1]);
			Vec3Sub(auxt, e2, e1);
			Vec3Mul(auxt, auxt, 1.0f / cp);

			Vec3Mul(aux2, normal, Vec3Dot(normal, auxt));
			Vec3Sub(auxt, auxt, aux2);

			Vec3Normalize(tangent, auxt);
		}
		//----------------------------------------------------------------------------------
		// Si es cero no podremos calcular la tangente, así que nos la inventamos. Esto no
		// está bien, pero bueno, para salir del paso no está mal.
		//----------------------------------------------------------------------------------
		else
		{
			GLfloat auxt[3] = {1.0f, 1.0f, 1.0f};
			GLfloat aux2[3];

			Vec3Mul(aux2, normal, Vec3Dot(normal, auxt));
			Vec3Sub(auxt, auxt, aux2);

			Vec3Normalize(tangent, auxt);
		}
	}

	//--------------------------------------------------------------------------------------
	// Método para calcular las tangentes del objeto.
	//--------------------------------------------------------------------------------------
	void CObject::CalculateTangents (void)
	{
		//----------------------------------------------------------------------------------
		// Comprobamos que el array con las tangentes existe.
		//----------------------------------------------------------------------------------
		if(this->Tangents == NULL) return;

		//----------------------------------------------------------------------------------
		// Luego comprobamos que los demás también existen, en caso de no existir alguno
		// de ellos simplemente inicializamos.
		//----------------------------------------------------------------------------------
		if((this->Vertexes == NULL) || (this->Normals == NULL) ||
		   (this->TexCoords == NULL) || (this->Faces == NULL))
		{
			unsigned int size = (this->NumVertexes * 3);

			for(unsigned int i = 0; i < size; ++i)
				this->Tangents[i] = 1.0f;
		}
		//----------------------------------------------------------------------------------
		// Si todo está en su sitio nos disponemos a recorrer los arrays, triángulo a
		// triángulo, a fin de calcular la tangente para cada vértice.
		//----------------------------------------------------------------------------------
		else
		{
			unsigned int i, j, k, m;
			GLfloat * p0, * p1, * p2, * uv0, * uv1, * uv2;
			GLfloat * n0, * n1, * n2, * t0, * t1, * t2;

			//------------------------------------------------------------------------------
			// Así que por cada conjunto de caras del objeto, recorreremos todos los
			// indices de esta, tomando 3 puntos en cada iteración. y luego llamaremos
			// a la función que calcula la tangente para un punto determinado.
			//------------------------------------------------------------------------------
			for(i = 0; i < this->NumFaces; ++i)
			{
				for(j = 0; j < this->Faces[i].NumIndexes; ++j)
				{
					cout<<j<<endl;
					k = this->Faces[i].Indexes[j] * 3;
					m = this->Faces[i].Indexes[j] * 2;

					p0  = &(this->Vertexes[k]);
					n0  = &(this->Normals[k]);
					t0  = &(this->Tangents[k]);
					uv0 = &(this->TexCoords[m]);

					++j;
					k = this->Faces[i].Indexes[j] * 3;
					m = this->Faces[i].Indexes[j] * 2;

					p1  = &(this->Vertexes[k]);
					n1  = &(this->Normals[k]);
					t1  = &(this->Tangents[k]);
					uv1 = &(this->TexCoords[m]);
					
					++j;
					k = this->Faces[i].Indexes[j] * 3;
					m = this->Faces[i].Indexes[j] * 2;

					p2  = &(this->Vertexes[k]);
					n2  = &(this->Normals[k]);
					t2  = &(this->Tangents[k]);
					uv2 = &(this->TexCoords[m]);

					this->CalculateTangent(p0, p1, p2, uv0, uv1, uv2, n0, t0);
					this->CalculateTangent(p1, p2, p0, uv1, uv2, uv0, n1, t1);
					this->CalculateTangent(p2, p0, p1, uv2, uv0, uv1, n2, t2);
				}
			}
		}
	}

	//--------------------------------------------------------------------------------------
	// Método para dibujar en pantalla el objeto.
	//--------------------------------------------------------------------------------------
	void CObject::Draw (CMaterial * Materials)
	{
		//----------------------------------------------------------------------------------
		// Para poder pintar usaremos vertex arrays, primero hay que indicarle a OpenGL,
		// que vamos a usar arrays de vértices y de normales. Una vez lo hemos activado,
		// le hemos de pasar los punteros a dichos arrays.
		//----------------------------------------------------------------------------------
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, this->Vertexes);
		glNormalPointer(GL_FLOAT, 0, this->Normals);

		//----------------------------------------------------------------------------------
		// Luego hemos de comprobar si vamos a pintar un objeto con textura o no.
		//----------------------------------------------------------------------------------
		if(this->Textured)
		{
			//------------------------------------------------------------------------------
			// Ya que usaremos texturas, hemos de activar el array de coordenadas de
			// texturas, indicándole que la vamos a almacenar para la unidad de textura 0.
			//------------------------------------------------------------------------------
			glClientActiveTextureARB(GL_TEXTURE0_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, 0, this->TexCoords);

			//------------------------------------------------------------------------------
			// También tendremos que pasarle un array de atributos, que tendrá almacenadas,
			// la tangente de cada vértice del objeto.
			//------------------------------------------------------------------------------
			CShadersManager * manager = CShadersManager::GetInstance();
			manager->EnableTangents(this->Tangents);
			
			//------------------------------------------------------------------------------
			// Así que vamos por cada conjunto de caras, activando el material de dicho
			// conjunto, y dibujando los triángulos que lo forman. Al estar usando texturas
			// necesitamos al final de pintar el conjunto, desactivar algunas cosas del
			// material, relativas a las texturas.
			//------------------------------------------------------------------------------
			for(unsigned int i = 0; i < this->NumFaces; ++i)
			{
				Materials[this->Faces[i].Material].UpdateBegin();
				
				glPushMatrix();
					glMultMatrixf(this->Matrix);

					glDrawElements(GL_TRIANGLES, this->Faces[i].NumIndexes,
								   GL_UNSIGNED_INT, this->Faces[i].Indexes);
				glPopMatrix();
				
				Materials[this->Faces[i].Material].UpdateEnd();
			}
			
			//------------------------------------------------------------------------------
			// También hemos de desactivar el array de atributos de las tangentes.
			//------------------------------------------------------------------------------
			manager->DisableTangents();
		}
		else
		{
			//------------------------------------------------------------------------------
			// Si no vamos a usar texturas, desactivamos el array de coordenadas de
			// texturas, por si acaso estaba ya activado anteriormente.
			//------------------------------------------------------------------------------
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			
			//------------------------------------------------------------------------------
			// Así que vamos por cada conjunto de caras, activando el material de dicho
			// conjunto, y dibujando los triángulos que lo forman.
			//------------------------------------------------------------------------------
			for(unsigned int i = 0; i < this->NumFaces; ++i)
			{
				Materials[this->Faces[i].Material].Update();
				
				glPushMatrix();
					glMultMatrixf(this->Matrix);

					glDrawElements(GL_TRIANGLES, this->Faces[i].NumIndexes,
								   GL_UNSIGNED_INT, this->Faces[i].Indexes);
				glPopMatrix();
			}
		}
	}

	//--------------------------------------------------------------------------------------
	// Método para inicializar o borrar un objeto.
	//--------------------------------------------------------------------------------------
	void CObject::Release (void)
	{
		//----------------------------------------------------------------------------------
		// Eliminamos el nombre y borramos las transformaciones.
		//----------------------------------------------------------------------------------
		if(this->Name != NULL)
		{
			free(this->Name);
			this->Name = NULL;
		}

		this->Transformation.Reset();
		this->Transformation.GetMatrix(this->Matrix);

		this->Textured = false;


		//----------------------------------------------------------------------------------
		// Eliminamos los arrays de datos de vértices.
		//----------------------------------------------------------------------------------
		this->NumVertexes = 0;
		
		if(this->Vertexes != NULL)
		{
			free(this->Vertexes);
			this->Vertexes = NULL;
		}

		if(this->Normals != NULL)
		{
			free(this->Normals);
			this->Normals = NULL;
		}

		if(this->Tangents != NULL)
		{
			free(this->Tangents);
			this->Tangents = NULL;
		}

		if(this->TexCoords != NULL)
		{
			free(this->TexCoords);
			this->TexCoords = NULL;
		}


		//----------------------------------------------------------------------------------
		// Y eliminamos los conjuntos de caras.
		//----------------------------------------------------------------------------------
		this->NumFaces = 0;
		
		if(this->Faces != NULL)
		{
			delete [] this->Faces;
			this->Faces = NULL;
		}
	}

	//--------------------------------------------------------------------------------------
	// Método para cargar de un fichero el objeto.
	//--------------------------------------------------------------------------------------
	void CObject::Load (FILE * file)
	{
		if(file != NULL)
		{
			this->Release();
			this->Name = ReadStringFromFile(file);
			fread(this->Matrix, sizeof(GLfloat), 16, file);

			this->Transformation.Load(file);

			fread(&(this->Textured), sizeof(bool), 1, file);


			fread(&(this->NumVertexes), sizeof(unsigned int), 1, file);

			unsigned int size = sizeof(GLfloat) * this->NumVertexes;
			this->Vertexes  = (GLfloat *) malloc(size * MAX_VEC3);
			this->Normals   = (GLfloat *) malloc(size * MAX_VEC3);
			this->Tangents  = (GLfloat *) malloc(size * MAX_VEC3);
			this->TexCoords = (GLfloat *) malloc(size * MAX_VEC2);

			if((this->Vertexes == NULL) || (this->Normals == NULL) ||
			   (this->Tangents == NULL) || (this->TexCoords == NULL))
			{
				appSetLastError(OBJ3DERR_OBJLOAD_FACESNULL);
				return;
			}

			fread(this->Vertexes,  sizeof(GLfloat), this->NumVertexes * MAX_VEC3, file);
			fread(this->Normals,   sizeof(GLfloat), this->NumVertexes * MAX_VEC3, file);
			fread(this->Tangents,  sizeof(GLfloat), this->NumVertexes * MAX_VEC3, file);
			fread(this->TexCoords, sizeof(GLfloat), this->NumVertexes * MAX_VEC2, file);
			

			fread(&(this->NumFaces), sizeof(unsigned int), 1, file);

			this->Faces = new CFaces[this->NumFaces];
			if(this->Faces != NULL)
			{
				for(unsigned int i = 0; i < this->NumFaces; ++i)
				{
					this->Faces[i].Load(file);
					if(appGetLastError()) return;
				}
			}
			else
			{
				appSetLastError(OBJ3DERR_OBJLOAD_FACESNULL);
			}
		}
	}
	
	//--------------------------------------------------------------------------------------
	// Método para salvar a un fichero el objeto.
	//--------------------------------------------------------------------------------------
	void CObject::Save (FILE * file)
	{
		if(file != NULL)
		{
            if(this->Name != NULL)
            {
		        fwrite(this->Name, sizeof(char), strlen(this->Name) + 1, file);
            }
            else
            {
                char zero = '\0';
	    	    fwrite(&zero, sizeof(char), 1, file);
            }

			fwrite(this->Matrix, sizeof(GLfloat), 16, file);

			this->Transformation.Save(file);

			fwrite(&(this->Textured), sizeof(bool), 1, file);

			fwrite(&(this->NumVertexes), sizeof(unsigned int), 1, file);

			fwrite(this->Vertexes,  sizeof(GLfloat), this->NumVertexes * MAX_VEC3, file);
			fwrite(this->Normals,   sizeof(GLfloat), this->NumVertexes * MAX_VEC3, file);
			fwrite(this->Tangents,  sizeof(GLfloat), this->NumVertexes * MAX_VEC3, file);
			fwrite(this->TexCoords, sizeof(GLfloat), this->NumVertexes * MAX_VEC2, file);

			fwrite(&(this->NumFaces), sizeof(unsigned int), 1, file);

			for(unsigned int i = 0; i < this->NumFaces; ++i)
				this->Faces[i].Save(file);
		}
	}
}
//******************************************************************************************
// 3dobject.cpp
//******************************************************************************************