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
// Miembros de la clase CMaterial.
//******************************************************************************************
namespace Geometry
{
	//**************************************************************************************
	// Constructores y funciones de copia.
	//**************************************************************************************

	//--------------------------------------------------------------------------------------
	// Constructor de la clase CMaterial.
	//--------------------------------------------------------------------------------------
	CMaterial::CMaterial ()
	{
		this->Name = NULL;
		this->Reset();
	}

	//--------------------------------------------------------------------------------------
	// Constructor copia de la clase CMaterial.
	//--------------------------------------------------------------------------------------
	CMaterial::CMaterial (const CMaterial & obj)
	{
		this->CopyFrom(obj);
	}

	//--------------------------------------------------------------------------------------
	// Destructor de la clase CMaterial.
	//--------------------------------------------------------------------------------------
	CMaterial::~CMaterial ()
	{
		this->Reset();
	}

	//--------------------------------------------------------------------------------------
	// Sobrecarga del operador igual.
	//--------------------------------------------------------------------------------------
	CMaterial & CMaterial::operator = (const CMaterial & obj)
	{
		this->CopyFrom(obj);
		return (*this);
	}

	//--------------------------------------------------------------------------------------
	// Método para copiar un objeto a otro.
	//--------------------------------------------------------------------------------------
	void CMaterial::CopyFrom (const CMaterial & obj)
	{
		appResetLastError();
		this->Reset();

		this->Name = CopyString(obj.Name);

		for(unsigned int i = 0; i < MAX_VEC4; ++i)
		{
			this->Ambient[i]  = obj.Ambient[i];
			this->Diffuse[i]  = obj.Diffuse[i];
			this->Specular[i] = obj.Specular[i];
			this->Emission[i] = obj.Emission[i];
			this->Color[i]    = obj.Color[i];
		}

		this->Shininess = obj.Shininess;
		this->Textured  = obj.Textured;

		this->Texture   = obj.Texture;
		this->NormalMap = obj.NormalMap;
		this->HeightMap = obj.HeightMap;
		this->Effect    = obj.Effect;

		this->ScaleBiasFactor[0] = obj.ScaleBiasFactor[0];
		this->ScaleBiasFactor[1] = obj.ScaleBiasFactor[1];
	}

	//--------------------------------------------------------------------------------------
	// Método para copiar un material del 3DS en el objeto.
	//--------------------------------------------------------------------------------------
	void CMaterial::CopyFrom (const Model_3DS::Material & obj)
	{
		appResetLastError();
		this->Reset();
		
		this->Name = CopyString(obj.name);
		
		this->Color[0] = ((float) obj.color.r) / 255.0f;
		this->Color[1] = ((float) obj.color.g) / 255.0f;
		this->Color[2] = ((float) obj.color.b) / 255.0f;
		this->Color[3] = ((float) obj.color.a) / 255.0f;
		
		if(obj.tex.texturename != NULL)
		{
			CContentManager * content = CContentManager::GetInstance();

			this->Textured = obj.textured;
			this->Texture  = content->GetTexture(obj.tex.texturename);
		}
	}

	//**************************************************************************************
	// Lógica.
	//**************************************************************************************

	//--------------------------------------------------------------------------------------
	// Método para indicar a OpenGL que use este material.
	//--------------------------------------------------------------------------------------
	void CMaterial::UpdateBegin (void)
	{
		//----------------------------------------------------------------------------------
		// Activamos las propiedades del material.
		//----------------------------------------------------------------------------------
		glMaterialfv(GL_FRONT, GL_AMBIENT,  this->Ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,  this->Diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, this->Specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, this->Emission);

		glMaterialf(GL_FRONT, GL_SHININESS, this->Shininess);

		glColor4fv(this->Color);

		//----------------------------------------------------------------------------------
		// Si el material contiene una textura, comprobamos que clase de efecto queremos
		// applicarle al objeto con este material.
		//----------------------------------------------------------------------------------
		if(this->Textured)
		{
			CShadersManager * manager = CShadersManager::GetInstance();

			switch(this->Effect)
			{
			//------------------------------------------------------------------------------
			// Para el normal mapping requeriremos dos texturas, la normal y la que
			// contenga el mapa de normales. Además de indicar al shader el efecto.
			//------------------------------------------------------------------------------
			case NormalMapping:
				manager->UseProgram(NormalMappingSPT);

				if(this->Texture != NULL)
				{
					glActiveTextureARB(GL_TEXTURE0_ARB);
					this->Texture->Use();
				}

				if(!manager->IsShadersAvailable()) return;
				if(manager->GetLimit() != NormalMappingSPT) return;

				if(this->NormalMap != NULL)
				{
					glActiveTextureARB(GL_TEXTURE1_ARB);
					this->NormalMap->Use();
					manager->SetSampler2D("normalMap", 1);
				}

				break;

			//------------------------------------------------------------------------------
			// Para el parallax mapping requeriremos tres texturas, la normal, la que
			// contenga el mapa de normales y la del mapa de alturas. Además tendremos que
			// indicar al shader el efecto que deseamos usar.
			//------------------------------------------------------------------------------
			case ParallaxMapping:
				manager->UseProgram(ParallaxMappingSPT);

				if(this->Texture != NULL)
				{
					glActiveTextureARB(GL_TEXTURE0_ARB);
					this->Texture->Use();
				}

				if(!manager->IsShadersAvailable()) return;
				if((manager->GetLimit() != NormalMappingSPT) &&
				   (manager->GetLimit() != ParallaxMappingSPT)) return;

				if(this->NormalMap != NULL)
				{
					glActiveTextureARB(GL_TEXTURE1_ARB);
					this->NormalMap->Use();
					manager->SetSampler2D("normalMap", 1);
				}

				if(manager->GetLimit() != ParallaxMappingSPT) return;

				if(this->HeightMap != NULL)
				{
					glActiveTextureARB(GL_TEXTURE2_ARB);
					this->HeightMap->Use();
					manager->SetSampler2D("heightMap", 2);
					manager->SetScaleBiasFactor(this->ScaleBiasFactor);
				}

				break;

			//------------------------------------------------------------------------------
			// Para todo lo demás solo usaremos la textura normal.
			//------------------------------------------------------------------------------
			default:
				manager->UseProgram(PerPixelLightingSPT);

				if(this->Texture != NULL)
				{
					glActiveTextureARB(GL_TEXTURE0_ARB);
					this->Texture->Use();
				}
			}
		}
	}

	//--------------------------------------------------------------------------------------
	// Método para indicar a OpenGL que deje de usar este material.
	//--------------------------------------------------------------------------------------
	void CMaterial::UpdateEnd (void)
	{
		//----------------------------------------------------------------------------------
		// En caso de que el material contenga una textura, tendremos que desactivar los
		// diferentes niveles de multitexturizado, para evitar problemas.
		//----------------------------------------------------------------------------------
		if(this->Textured)
		{
			switch(this->Effect)
			{
			case ParallaxMapping:
				glActiveTextureARB(GL_TEXTURE2_ARB);
				glDisable(GL_TEXTURE_2D);

			case NormalMapping:
				glActiveTextureARB(GL_TEXTURE1_ARB);
				glDisable(GL_TEXTURE_2D);

			default:
				glActiveTextureARB(GL_TEXTURE0_ARB);
				glDisable(GL_TEXTURE_2D);
			}
		}
	}

	//--------------------------------------------------------------------------------------
	// Método para indicar a OpenGL que use este material sin textura.
	//--------------------------------------------------------------------------------------
	void CMaterial::Update (void)
	{
		//----------------------------------------------------------------------------------
		// Activamos las propiedades del material.
		//----------------------------------------------------------------------------------
		glMaterialfv(GL_FRONT, GL_AMBIENT,  this->Ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,  this->Diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, this->Specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, this->Emission);

		glMaterialf(GL_FRONT, GL_SHININESS, this->Shininess);

		glColor4fv(this->Color);
	}

	//--------------------------------------------------------------------------------------
	// Método para inicializar o borrar un material.
	//--------------------------------------------------------------------------------------
	void CMaterial::Reset (void)
	{
		//----------------------------------------------------------------------------------
		// Liberamos el nombre del material.
		//----------------------------------------------------------------------------------
		if(this->Name != NULL)
		{
			free(this->Name);
			this->Name = NULL;
		}

		//----------------------------------------------------------------------------------
		// Borramos las propiedades de color e iluminación.
		//----------------------------------------------------------------------------------
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

		this->Shininess = 0.0f;

		this->Emission[0] = 0.0f;
		this->Emission[1] = 0.0f;
		this->Emission[2] = 0.0f;
		this->Emission[3] = 1.0f;

		this->Color[0] = 1.0f;
		this->Color[1] = 1.0f;
		this->Color[2] = 1.0f;
		this->Color[3] = 1.0f;

		//----------------------------------------------------------------------------------
		// Borramos las propiedades relativas a las texturas.
		//----------------------------------------------------------------------------------
		this->Textured = false;

		this->Texture   = NULL;
		this->NormalMap = NULL;
		this->HeightMap = NULL;
		this->Effect    = NoneEffect;

		this->ScaleBiasFactor[0] = 0.02f;
		this->ScaleBiasFactor[1] = 0.015f;
	}

	//--------------------------------------------------------------------------------------
	// Método para cargar de un fichero el objeto.
	//--------------------------------------------------------------------------------------
	void CMaterial::Load (FILE * file)
	{
		if(file != NULL)
		{
			//------------------------------------------------------------------------------
			// Eliminamos el contenido y leemos el nombre del material.
			//------------------------------------------------------------------------------
			this->Reset();
			this->Name = ReadStringFromFile(file);
			
			//------------------------------------------------------------------------------
			// Luego leemos los colores y propiedades implicadas en OpenGL.
			//------------------------------------------------------------------------------
			fread(this->Ambient,  sizeof(GLfloat), 4, file);
			fread(this->Diffuse,  sizeof(GLfloat), 4, file);
			fread(this->Specular, sizeof(GLfloat), 4, file);
			fread(this->Emission, sizeof(GLfloat), 4, file);

			fread(&(this->Shininess), sizeof(GLfloat), 1, file);

			fread(this->Color, sizeof(GLfloat), 4, file);

			//------------------------------------------------------------------------------
			// Comprobamos si el material está usando texturas.
			//------------------------------------------------------------------------------
			fread(&(this->Textured), sizeof(bool), 1, file);

			bool texaux;
			char * straux;
			CContentManager * content = CContentManager::GetInstance();

			//------------------------------------------------------------------------------
			// Luego comprobamos si tiene una textura para el color.
			//------------------------------------------------------------------------------
			fread(&texaux, sizeof(bool), 1, file);
			
			if(texaux)
			{
				straux = ReadStringFromFile(file);
				this->Texture = content->GetTexture(straux);
				free(straux);
			}
			
			//------------------------------------------------------------------------------
			// Luego comprobamos si tiene una textura para las normales.
			//------------------------------------------------------------------------------
			fread(&texaux, sizeof(bool), 1, file);
			
			if(texaux)
			{
				straux = ReadStringFromFile(file);
				this->NormalMap = content->GetTexture(straux);
				free(straux);
			}

			//------------------------------------------------------------------------------
			// Luego comprobamos si tiene una textura para las alturas.
			//------------------------------------------------------------------------------
			fread(&texaux, sizeof(bool), 1, file);
			
			if(texaux)
			{
				straux = ReadStringFromFile(file);
				this->HeightMap = content->GetTexture(straux);
				free(straux);
			}

			//------------------------------------------------------------------------------
			// Finalmente leemos el efecto que usa y el factor de escala.
			//------------------------------------------------------------------------------
			fread(&(this->Effect), sizeof(TextureEffect), 1, file);

			fread(this->ScaleBiasFactor, sizeof(GLfloat), 2, file);
		}
	}
	
	//--------------------------------------------------------------------------------------
	// Método para salvar a un fichero el objeto.
	//--------------------------------------------------------------------------------------
	void CMaterial::Save (FILE * file)
	{
		if(file != NULL)
		{
			//------------------------------------------------------------------------------
			// Escribimos el nombre del material.
			//------------------------------------------------------------------------------ 
			if(this->Name != NULL)
			{
				fwrite(this->Name, sizeof(char), strlen(this->Name) + 1, file);
			}
			else
			{
				char zero = '\0';
				fwrite(&zero, sizeof(char), 1, file);
			}

			//------------------------------------------------------------------------------
			// Escribimos los colores y propiedades implicadas en OpenGL.
			//------------------------------------------------------------------------------
			fwrite(this->Ambient,  sizeof(GLfloat), 4, file);
			fwrite(this->Diffuse,  sizeof(GLfloat), 4, file);
			fwrite(this->Specular, sizeof(GLfloat), 4, file);
			fwrite(this->Emission, sizeof(GLfloat), 4, file);

			fwrite(&(this->Shininess), sizeof(GLfloat), 1, file);

			fwrite(this->Color, sizeof(GLfloat), 4, file);

			//------------------------------------------------------------------------------
			// Escribimos si el material está usando texturas.
			//------------------------------------------------------------------------------
			fwrite(&(this->Textured), sizeof(bool), 1, file);

			bool texaux;
			
			//------------------------------------------------------------------------------
			// Escribimos si tiene una textura para el color.
			//------------------------------------------------------------------------------
			if(this->Texture != NULL)
			{
				texaux = true;
				fwrite(&texaux, sizeof(bool), 1, file);

				fwrite(this->Texture->GetImage()->GetName().c_str(), sizeof(char),
					   this->Texture->GetImage()->GetName().size() + 1, file);
			}
			else
			{
				texaux = false;
				fwrite(&texaux, sizeof(bool), 1, file);
			}
			
			//------------------------------------------------------------------------------
			// Escribimos si tiene una textura para las normales.
			//------------------------------------------------------------------------------
			if(this->NormalMap != NULL)
			{
				texaux = true;
				fwrite(&texaux, sizeof(bool), 1, file);

				fwrite(this->NormalMap->GetImage()->GetName().c_str(), sizeof(char),
					   this->NormalMap->GetImage()->GetName().size() + 1, file);
			}
			else
			{
				texaux = false;
				fwrite(&texaux, sizeof(bool), 1, file);
			}
			
			//------------------------------------------------------------------------------
			// Escribimos si tiene una textura para las alturas.
			//------------------------------------------------------------------------------
			if(this->HeightMap != NULL)
			{
				texaux = true;
				fwrite(&texaux, sizeof(bool), 1, file);

				fwrite(this->HeightMap->GetImage()->GetName().c_str(), sizeof(char),
					   this->HeightMap->GetImage()->GetName().size() + 1, file);
			}
			else
			{
				texaux = false;
				fwrite(&texaux, sizeof(bool), 1, file);
			}

			//------------------------------------------------------------------------------
			// Escribimos el efecto que usa y el factor de escala.
			//------------------------------------------------------------------------------
			fwrite(&(this->Effect), sizeof(TextureEffect), 1, file);

			fwrite(this->ScaleBiasFactor, sizeof(GLfloat), 2, file);
		}
	}
}
//******************************************************************************************
// 3dmaterial.cpp
//******************************************************************************************