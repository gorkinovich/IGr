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
#include "shaders.h"
//******************************************************************************************
// Miembros de la clase CShaderObject.
//******************************************************************************************

	//**************************************************************************************
	// Constructores y funciones de copia.
	//**************************************************************************************

	//--------------------------------------------------------------------------------------
	// Constructor de la clase CShaderObject.
	//--------------------------------------------------------------------------------------
	CShaderObject::CShaderObject ()
	{
		this->shader = 0;
	}

	//--------------------------------------------------------------------------------------
	// Constructor copia de la clase CShaderObject.
	//--------------------------------------------------------------------------------------
	CShaderObject::CShaderObject (const CShaderObject & obj)
	{
		this->shader = obj.shader;
	}

	//--------------------------------------------------------------------------------------
	// Destructor de la clase CShaderObject.
	//--------------------------------------------------------------------------------------
	CShaderObject::~CShaderObject ()
	{
		this->Release();
	}

	//--------------------------------------------------------------------------------------
	// Sobrecarga del operador igual.
	//--------------------------------------------------------------------------------------
	CShaderObject & CShaderObject::operator = (const CShaderObject & obj)
	{
		this->CopyFrom(obj);
		return (*this);
	}

	//--------------------------------------------------------------------------------------
	// Método para copiar un objeto a otro.
	//--------------------------------------------------------------------------------------
	void CShaderObject::CopyFrom (const CShaderObject & obj)
	{
		this->shader = obj.shader;
	}
	
	//**************************************************************************************
	// Lógica.
	//**************************************************************************************

	//--------------------------------------------------------------------------------------
	// Método para cargar un shader en la memoria de la tarjeta.
	//--------------------------------------------------------------------------------------
	bool CShaderObject::Load (const char * path, GLenum type)
	{
		appResetLastError();
		FILE * file = fopen(path, "r");
		if(file == NULL) return appSetLastError(SHAERR_SHAOBJ_FOPENFILE);


		string source = "";
		char aux;

		fread(&aux, sizeof(char), 1, file);
		while(!feof(file))
		{
			source += aux;
			fread(&aux, sizeof(char), 1, file);
		}

		fclose(file);

		if(!source.length()) return appSetLastError(SHAERR_SHAOBJ_EMPTYFILE);


		this->shader = glCreateShaderObjectARB(type);
		if(!this->shader) return appSetLastError(SHAERR_SHAOBJ_CREATESHADEROBJECT);


		const char * srcstr = source.c_str();
		int len = source.length();

		glShaderSourceARB(this->shader, 1, &srcstr, &len);
		glCompileShaderARB(this->shader);

		int cmperr;
		glGetObjectParameterivARB(this->shader, GL_OBJECT_COMPILE_STATUS_ARB, &cmperr);

		if(cmperr == 0) return appSetLastError(SHAERR_SHAOBJ_COMPILESHADER);


		return true;
	}
	
	//--------------------------------------------------------------------------------------
	// Método para liberar un shader de la memoria de la tarjeta.
	//--------------------------------------------------------------------------------------
	void CShaderObject::Release (void)
	{
		if(this->shader)
		{
			glDeleteObjectARB(this->shader);
			this->shader = 0;
		}
	}

//******************************************************************************************
// Miembros de la clase CShaderProgram.
//******************************************************************************************

	//**************************************************************************************
	// Constructores y funciones de copia.
	//**************************************************************************************

	//--------------------------------------------------------------------------------------
	// Constructor de la clase CShaderProgram.
	//--------------------------------------------------------------------------------------
	CShaderProgram::CShaderProgram ()
	{
		this->program = 0;
	}

	//--------------------------------------------------------------------------------------
	// Constructor copia de la clase CShaderProgram.
	//--------------------------------------------------------------------------------------
	CShaderProgram::CShaderProgram (const CShaderProgram & obj)
	{
		this->program = obj.program;
	}

	//--------------------------------------------------------------------------------------
	// Destructor de la clase CShaderProgram.
	//--------------------------------------------------------------------------------------
	CShaderProgram::~CShaderProgram ()
	{
		this->Release();
	}

	//--------------------------------------------------------------------------------------
	// Sobrecarga del operador igual.
	//--------------------------------------------------------------------------------------
	CShaderProgram & CShaderProgram::operator = (const CShaderProgram & obj)
	{
		this->CopyFrom(obj);
		return (*this);
	}

	//--------------------------------------------------------------------------------------
	// Método para copiar un objeto a otro.
	//--------------------------------------------------------------------------------------
	void CShaderProgram::CopyFrom (const CShaderProgram & obj)
	{
		this->program = obj.program;
	}

	//**************************************************************************************
	// Lógica.
	//**************************************************************************************
	
	//--------------------------------------------------------------------------------------
	// Método para cargar un programa en la memoria de la tarjeta.
	//--------------------------------------------------------------------------------------
	bool CShaderProgram::Load (const char * vspath, const char * fspath)
	{
		appResetLastError();

		if(!this->vertex.LoadVS(vspath)) return false;
		if(!this->fragment.LoadFS(fspath)) return false;


		this->program = glCreateProgramObjectARB();
		if(!this->program) return appSetLastError(SHAERR_SHAOBJ_CREATEPROGRAMOBJECT);


		glAttachObjectARB(this->program, this->vertex.GetHandle());
		glAttachObjectARB(this->program, this->fragment.GetHandle());

		glLinkProgramARB(this->program);

		int cmperr;
		glGetObjectParameterivARB(this->program, GL_OBJECT_LINK_STATUS_ARB, &cmperr);

		if(cmperr == 0) return appSetLastError(SHAERR_SHAOBJ_LINKPROGRAM);

		return true;
	}

	//--------------------------------------------------------------------------------------
	// Método para liberar un programa de la memoria de la tarjeta.
	//--------------------------------------------------------------------------------------
	void CShaderProgram::Release (void)
	{
		if(this->vertex.GetHandle())
		{
			glDetachObjectARB(this->program, this->vertex.GetHandle());
			this->vertex.Release();
		}

		if(this->fragment.GetHandle())
		{
			glDetachObjectARB(this->program, this->fragment.GetHandle());
			this->fragment.Release();
		}
		
		if(this->program)
		{
			glDeleteObjectARB(this->program);
			this->program = 0;
		}
	}

	//--------------------------------------------------------------------------------------
	// Método para activar el uso de un programa.
	//--------------------------------------------------------------------------------------
	void CShaderProgram::Use (void)
	{
		glUseProgramObjectARB(this->program);
	}

//******************************************************************************************
// Miembros de la clase CShadersManager.
//******************************************************************************************

	//**************************************************************************************
	// Rutas.
	//**************************************************************************************

	const char * PerPixelLightingVSPath = "Shaders\\PerPixel.vert";
	const char * PerPixelLightingFSPath = "Shaders\\PerPixel.frag";
	const char * NormalMappingVSPath    = "Shaders\\Normal.vert";
	const char * NormalMappingFSPath    = "Shaders\\Normal.frag";
	const char * ParallaxMappingVSPath  = "Shaders\\Parallax.vert";
	const char * ParallaxMappingFSPath  = "Shaders\\Parallax.frag";

	//**************************************************************************************
	// Constructores y funciones de copia.
	//**************************************************************************************

	//--------------------------------------------------------------------------------------
	// Constructor de la clase CShadersManager.
	//--------------------------------------------------------------------------------------
	CShadersManager::CShadersManager()
	{
		this->Limit = ParallaxMappingSPT;
	}

	//--------------------------------------------------------------------------------------
	// Destructor de la clase CShadersManager.
	//--------------------------------------------------------------------------------------
	CShadersManager::~CShadersManager()
	{
		this->Release();
	}

	//**************************************************************************************
	// Lógica.
	//**************************************************************************************
	
	//--------------------------------------------------------------------------------------
	// Metodo para cargar los programas shaders que vamos a usar.
	//--------------------------------------------------------------------------------------
	bool CShadersManager::Load (void)
	{
		appResetLastError();
		this->Limit = FixedPipelineSPT;

		if(!this->IsShadersAvailable()) return appSetLastError(SHAERR_SHAOBJ_NOSHADERSAVAILABLE);

		if(!this->Programs[0].Load(PerPixelLightingVSPath, PerPixelLightingFSPath)) return false;
		if(!this->Programs[1].Load(NormalMappingVSPath,    NormalMappingFSPath))    return false;
		if(!this->Programs[2].Load(ParallaxMappingVSPath,  ParallaxMappingFSPath))  return false;

		this->Limit = ParallaxMappingSPT;
		glUseProgramObjectARB(0);

		return true;
	}

	//--------------------------------------------------------------------------------------
	// Metodo para eliminar los programas shaders que estabamos usando.
	//--------------------------------------------------------------------------------------
	void CShadersManager::Release (void)
	{
		if(!this->IsShadersAvailable()) return;

		glUseProgramObjectARB(0);
		this->Programs[0].Release();
		this->Programs[1].Release();
		this->Programs[2].Release();
	}

	//--------------------------------------------------------------------------------------
	// Metodo para activar en uso el programa shader que queremos.
	//--------------------------------------------------------------------------------------
	void CShadersManager::UseProgram (ShaderProgramType program)
	{
		if(!this->IsShadersAvailable())
		{
			this->Program = FixedPipelineSPT;
		}
		else
		{
			switch(this->Limit)
			{
			case PerPixelLightingSPT:
				switch(program)
				{
				case PerPixelLightingSPT:
				case NormalMappingSPT:
				case ParallaxMappingSPT:
					this->Programs[PerPixelLightingSPT].Use();
					this->Program = PerPixelLightingSPT;
					break;

				default:
					glUseProgramObjectARB(0);
					this->Program = FixedPipelineSPT;
				}

				break;

			case NormalMappingSPT:
				switch(program)
				{
				case PerPixelLightingSPT:
					this->Programs[PerPixelLightingSPT].Use();
					this->Program = PerPixelLightingSPT;
					break;

				case NormalMappingSPT:
				case ParallaxMappingSPT:
					this->Programs[NormalMappingSPT].Use();
					this->Program = NormalMappingSPT;
					break;

				default:
					glUseProgramObjectARB(0);
					this->Program = FixedPipelineSPT;
				}
				break;

			case ParallaxMappingSPT:
				switch(program)
				{
				case PerPixelLightingSPT:
				case NormalMappingSPT:
				case ParallaxMappingSPT:
					this->Programs[program].Use();
					this->Program = program;
					break;

				default:
					glUseProgramObjectARB(0);
					this->Program = FixedPipelineSPT;
				}

				break;

			default:
				glUseProgramObjectARB(0);
				this->Program = FixedPipelineSPT;
			}
		}
	}

	//**************************************************************************************
	// Gets.
	//**************************************************************************************

	bool CShadersManager::IsShadersAvailable (void)
	{
		return extIsVertexShaders() && extIsFragmentShaders();
	}

	//**************************************************************************************
	// Sets.
	//**************************************************************************************

	void CShadersManager::SetLimit (ShaderProgramType limit)
	{
		if(!this->IsShadersAvailable())
		{
			this->Limit = FixedPipelineSPT;
		}
		else
		{
			this->Limit = limit;
		}
	}

	//--------------------------------------------------------------------------------------

	void CShadersManager::SetSampler2D (const char * name, GLint value)
	{
		if(this->IsShadersAvailable())
		{
			GLint loc = glGetUniformLocationARB(this->Programs[this->Program].GetHandle(), name);
			glUniform1iARB(loc, value);
		}
	}

	//--------------------------------------------------------------------------------------

	void CShadersManager::SetScaleBiasFactor (GLfloat * factor)
	{
		if(this->Program == ParallaxMappingSPT)
		{
			GLint loc = glGetUniformLocationARB(this->Programs[ParallaxMappingSPT].GetHandle(),
												"ScaleBiasFactor");
			glUniform1fvARB(loc, 2, factor);
		}
	}

	//--------------------------------------------------------------------------------------

	void CShadersManager::EnableTangents (GLfloat * tangents)
	{
		if((this->Program == ParallaxMappingSPT) || (this->Program == NormalMappingSPT))
		{
			int tanloc = glGetAttribLocationARB(this->Programs[this->Program].GetHandle(),
												"Tangent");
			glEnableVertexAttribArrayARB(tanloc);
			glVertexAttribPointerARB(tanloc, 3, GL_FLOAT, 0, 0, tangents);
		}
	}

	//--------------------------------------------------------------------------------------

	void CShadersManager::DisableTangents (void)
	{
		if((this->Program == ParallaxMappingSPT) || (this->Program == NormalMappingSPT))
		{
			int tanloc = glGetAttribLocationARB(this->Programs[this->Program].GetHandle(),
												"Tangent");
			glDisableVertexAttribArrayARB(tanloc);
		}
	}

	//**************************************************************************************
	// Miembros estáticos.
	//**************************************************************************************

	CShadersManager * CShadersManager::Instance = NULL;

	CShadersManager * CShadersManager::GetInstance (void)
	{
		if(CShadersManager::Instance == NULL)
			CShadersManager::Instance = new CShadersManager();

		return CShadersManager::Instance;
	}

//******************************************************************************************
// shaders.cpp
//******************************************************************************************