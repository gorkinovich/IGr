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
#include "lighting.h"
#include <stdio.h>
//******************************************************************************************
// Funciones auxiliares.
//******************************************************************************************
GLenum GetLightID (unsigned int light)
{
	switch(light)
	{
		case 0:  return GL_LIGHT0;
		case 1:  return GL_LIGHT1;
		case 2:  return GL_LIGHT2;
		case 3:  return GL_LIGHT3;
		case 4:  return GL_LIGHT4;
		case 5:  return GL_LIGHT5;
		case 6:  return GL_LIGHT6;
		case 7:  return GL_LIGHT7;
		default: return GL_LIGHT0;
	}
}
//******************************************************************************************
// Miembros de la clase CLighting.
//******************************************************************************************

	//**************************************************************************************
	// Constructores y funciones de copia.
	//**************************************************************************************

	//--------------------------------------------------------------------------------------
	// Constructor de la clase CLighting.
	//--------------------------------------------------------------------------------------
	CLighting::CLighting ()
	{
		Lighting::tLight aux;

		aux.Ambient[0] = 0.0f;
		aux.Ambient[1] = 0.0f;
		aux.Ambient[2] = 0.0f;
		aux.Ambient[3] = 1.0f;

		aux.Diffuse[0] = 1.0f;
		aux.Diffuse[1] = 1.0f;
		aux.Diffuse[2] = 1.0f;
		aux.Diffuse[3] = 1.0f;

		aux.Specular[0] = 1.0f;
		aux.Specular[1] = 1.0f;
		aux.Specular[2] = 1.0f;
		aux.Specular[3] = 1.0f;

		aux.Position[0] = 0.0f;
		aux.Position[1] = 0.0f;
		aux.Position[2] = 1.0f;
		aux.Position[3] = 0.0f;

		aux.SpotDirection[0] =  0.0f;
		aux.SpotDirection[1] =  0.0f;
		aux.SpotDirection[2] = -1.0f;

		aux.SpotExponent =   0.0f;
		aux.SpotCutoff   = 180.0f;

		aux.Attenuation[CONSTANT_ATTENUATION]  = 1.0f;
		aux.Attenuation[LINEAR_ATTENUATION]    = 0.0f;
		aux.Attenuation[QUADRATIC_ATTENUATION] = 0.0f;

		aux.Enable = false;

		for(int i = 0; i < ANUBIS_MAX_LIGHTS; ++i)
		{
			this->Lights[i] = aux;
		}

		this->Ambient[0] = 0.2f;
		this->Ambient[1] = 0.2f;
		this->Ambient[2] = 0.2f;
		this->Ambient[3] = 1.0f;

		this->Enable = false;
	}

	//--------------------------------------------------------------------------------------
	// Constructor copia de la clase CLighting.
	//--------------------------------------------------------------------------------------
	CLighting::CLighting (const CLighting & obj)
	{
		this->CopyFrom(obj);
	}

	//--------------------------------------------------------------------------------------
	// Destructor de la clase CLighting.
	//--------------------------------------------------------------------------------------
	CLighting::~CLighting ()
	{
	}

	//--------------------------------------------------------------------------------------
	// Sobrecarga del operador igual.
	//--------------------------------------------------------------------------------------
	CLighting & CLighting::operator = (const CLighting & obj)
	{
		this->CopyFrom(obj);
		return (*this);
	}

	//--------------------------------------------------------------------------------------
	// Método para copiar un objeto a otro.
	//--------------------------------------------------------------------------------------
	void CLighting::CopyFrom (const CLighting & obj)
	{
		int i;

		for(i = 0; i < ANUBIS_MAX_LIGHTS; ++i)
		{
			this->Lights[i] = obj.Lights[i];
		}

		memcpy(this->Ambient, obj.Ambient, sizeof(GLfloat) * 4);

		this->Enable = obj.Enable;
	}

	//**************************************************************************************
	// Lógica.
	//**************************************************************************************

	//--------------------------------------------------------------------------------------
	// Metodo para activar la iluminación en OpenGL.
	//--------------------------------------------------------------------------------------
	void CLighting::Update (void)
	{
		if(this->Enable)
			glEnable(GL_LIGHTING);
		else
			glDisable(GL_LIGHTING);
		     
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, this->Ambient);

		GLenum light;
		for(int i = 0; i < ANUBIS_MAX_LIGHTS; ++i)
		{
			light = GetLightID(i);

			if(this->Lights[i].Enable)
            {
				glEnable(light);

       			glLightfv(light, GL_AMBIENT,  this->Lights[i].Ambient);
	    		glLightfv(light, GL_DIFFUSE,  this->Lights[i].Diffuse);
		    	glLightfv(light, GL_SPECULAR, this->Lights[i].Specular);

			    glLightfv(light, GL_POSITION, this->Lights[i].Position);

    			glLightfv(light, GL_SPOT_DIRECTION, this->Lights[i].SpotDirection);
	    		glLightf(light, GL_SPOT_EXPONENT, this->Lights[i].SpotExponent);
		    	glLightf(light, GL_SPOT_CUTOFF, this->Lights[i].SpotCutoff);

			    glLightf(light, GL_CONSTANT_ATTENUATION,
                         this->Lights[i].Attenuation[CONSTANT_ATTENUATION]);
    			glLightf(light, GL_LINEAR_ATTENUATION,
                         this->Lights[i].Attenuation[LINEAR_ATTENUATION]);
	    		glLightf(light, GL_QUADRATIC_ATTENUATION,
                         this->Lights[i].Attenuation[QUADRATIC_ATTENUATION]);
            }
			else
            {
				glDisable(light);
            }
		}
	}

	//--------------------------------------------------------------------------------------
	// Metodo para configurar la iluminación en OpenGL para GLSL.
	//--------------------------------------------------------------------------------------
	void CLighting::ConfigActiveLight (GLint value)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, this->Ambient);

       	glLightfv(GL_LIGHT0, GL_AMBIENT,  this->Lights[value].Ambient);
	    glLightfv(GL_LIGHT0, GL_DIFFUSE,  this->Lights[value].Diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, this->Lights[value].Specular);

		glLightfv(GL_LIGHT0, GL_POSITION, this->Lights[value].Position);

    	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, this->Lights[value].SpotDirection);
	    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, this->Lights[value].SpotExponent);
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, this->Lights[value].SpotCutoff);

		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,
                 this->Lights[value].Attenuation[CONSTANT_ATTENUATION]);
    	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION,
                 this->Lights[value].Attenuation[LINEAR_ATTENUATION]);
	    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION,
                 this->Lights[value].Attenuation[QUADRATIC_ATTENUATION]);
	}

	//--------------------------------------------------------------------------------------
	// Metodo para cargar un fichero con la iluminación.
	//--------------------------------------------------------------------------------------
	void CLighting::Load (const char * path)
	{
		FILE * file = fopen(path, "rb");
		if(file == NULL) return;

		fread(&(this->Enable), sizeof(bool), 1, file);
		fread(this->Ambient, sizeof(GLfloat), 4, file);
		fread(this->Lights, sizeof(Lighting::tLight), ANUBIS_MAX_LIGHTS, file);

		fclose(file);
	}

	//--------------------------------------------------------------------------------------
	// Metodo para salvar un fichero con la iluminación.
	//--------------------------------------------------------------------------------------
	void CLighting::Save (const char * path)
	{
		FILE * file = fopen(path, "wb");
		if(file == NULL) return;

		fwrite(&(this->Enable), sizeof(bool), 1, file);
		fwrite(this->Ambient, sizeof(GLfloat), 4, file);
		fwrite(this->Lights, sizeof(Lighting::tLight), ANUBIS_MAX_LIGHTS, file);

		fclose(file);
	}
            
	//--------------------------------------------------------------------------------------
	// Metodo para salvar un fichero con la iluminación.
	//--------------------------------------------------------------------------------------
    void CLighting::SaveText (const char * path)
	{
		FILE * file = fopen(path, "wt");
		if(file == NULL) return;

		fprintf(file , "Enable = %d\n", this->Enable);
		fprintf(file , "Ambient = %f %f %f %f\n", this->Ambient[0],
                this->Ambient[1], this->Ambient[2], this->Ambient[3]);

        for(int i = 0; i < ANUBIS_MAX_LIGHTS; ++i)
        {
            fprintf(file, "\n\nLight %d\n", i);
    		fprintf(file , "Ambient = %f %f %f %f\n", this->Lights[i].Ambient[0],
                    this->Lights[i].Ambient[1], this->Lights[i].Ambient[2],
                    this->Lights[i].Ambient[3]);
    		fprintf(file , "Diffuse = %f %f %f %f\n", this->Lights[i].Diffuse[0],
                    this->Lights[i].Diffuse[1], this->Lights[i].Diffuse[2],
                    this->Lights[i].Diffuse[3]);
    		fprintf(file , "Specular = %f %f %f %f\n", this->Lights[i].Specular[0],
                    this->Lights[i].Specular[1], this->Lights[i].Specular[2],
                    this->Lights[i].Specular[3]);
    		fprintf(file , "Position = %f %f %f %f\n", this->Lights[i].Position[0],
                    this->Lights[i].Position[1], this->Lights[i].Position[2],
                    this->Lights[i].Position[3]);
                    
    		fprintf(file , "Spot Direction = %f %f %f\n", this->Lights[i].SpotDirection[0],
                    this->Lights[i].SpotDirection[1], this->Lights[i].SpotDirection[2]);
    		fprintf(file , "Spot Exponent = %f\n", this->Lights[i].SpotExponent);
    		fprintf(file , "Spot Cut-off = %f\n", this->Lights[i].SpotCutoff);

    		fprintf(file , "Constant Attenuation = %f\n", this->Lights[i].Attenuation[CONSTANT_ATTENUATION]);
    		fprintf(file , "Linear Attenuation = %f\n", this->Lights[i].Attenuation[LINEAR_ATTENUATION]);
    		fprintf(file , "Quadratic Attenuation = %f\n", this->Lights[i].Attenuation[QUADRATIC_ATTENUATION]);
            
    		fprintf(file , "Enable = %d\n", this->Lights[i].Enable);
        }
        
		fclose(file);
	}

	//**************************************************************************************
	// Sets.
	//**************************************************************************************

	void CLighting::SetEnable (bool enable)
	{
		this->Enable = enable;
	}

	//--------------------------------------------------------------------------------------

	void CLighting::SetAmbient (GLfloat * ambient)
	{
		memcpy(this->Ambient, ambient, sizeof(GLfloat) * 4);

		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, this->Ambient);
	}

	void CLighting::SetAmbient (GLfloat r, GLfloat g, GLfloat b, GLfloat a)
	{
		this->Ambient[0] = r;
		this->Ambient[1] = g;
		this->Ambient[2] = b;
		this->Ambient[3] = a;

		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, this->Ambient);
	}

	//--------------------------------------------------------------------------------------

	void CLighting::SetLight (int index, const Lighting::tLight & light)
	{
		this->Lights[index] = light;

		GLenum lid = GetLightID(index);
		
		glLightfv(lid, GL_AMBIENT,  this->Lights[index].Ambient);
		glLightfv(lid, GL_DIFFUSE,  this->Lights[index].Diffuse);
		glLightfv(lid, GL_SPECULAR, this->Lights[index].Specular);
		
		glLightfv(lid, GL_POSITION, this->Lights[index].Position);
		
		glLightfv(lid, GL_SPOT_DIRECTION, this->Lights[index].SpotDirection);
		glLightf(lid, GL_SPOT_EXPONENT, this->Lights[index].SpotExponent);
		glLightf(lid, GL_SPOT_CUTOFF, this->Lights[index].SpotCutoff);
		
		glLightf(lid, GL_CONSTANT_ATTENUATION, this->Lights[index].Attenuation[CONSTANT_ATTENUATION]);
		glLightf(lid, GL_LINEAR_ATTENUATION, this->Lights[index].Attenuation[LINEAR_ATTENUATION]);
		glLightf(lid, GL_QUADRATIC_ATTENUATION, this->Lights[index].Attenuation[QUADRATIC_ATTENUATION]);
	}

	//--------------------------------------------------------------------------------------

	void CLighting::SetLightAmbient (int index, GLfloat * ambient)
	{
		this->Lights[index].Ambient[0] = ambient[0];
		this->Lights[index].Ambient[1] = ambient[1];
		this->Lights[index].Ambient[2] = ambient[2];
		this->Lights[index].Ambient[3] = ambient[3];

		glLightfv(GetLightID(index), GL_AMBIENT,  this->Lights[index].Ambient);
	}

	void CLighting::SetLightAmbient (int index, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
	{
		this->Lights[index].Ambient[0] = r;
		this->Lights[index].Ambient[1] = g;
		this->Lights[index].Ambient[2] = b;
		this->Lights[index].Ambient[3] = a;
		
		glLightfv(GetLightID(index), GL_AMBIENT,  this->Lights[index].Ambient);
	}

	//--------------------------------------------------------------------------------------

	void CLighting::SetLightDiffuse (int index, GLfloat * diffuse)
	{
		this->Lights[index].Diffuse[0] = diffuse[0];
		this->Lights[index].Diffuse[1] = diffuse[1];
		this->Lights[index].Diffuse[2] = diffuse[2];
		this->Lights[index].Diffuse[3] = diffuse[3];

		glLightfv(GetLightID(index), GL_DIFFUSE,  this->Lights[index].Diffuse);
	}

	void CLighting::SetLightDiffuse (int index, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
	{
		this->Lights[index].Diffuse[0] = r;
		this->Lights[index].Diffuse[1] = g;
		this->Lights[index].Diffuse[2] = b;
		this->Lights[index].Diffuse[3] = a;
		
		glLightfv(GetLightID(index), GL_DIFFUSE,  this->Lights[index].Diffuse);
	}

	//--------------------------------------------------------------------------------------

	void CLighting::SetLightSpecular (int index, GLfloat * specular)
	{
		this->Lights[index].Specular[0] = specular[0];
		this->Lights[index].Specular[1] = specular[1];
		this->Lights[index].Specular[2] = specular[2];
		this->Lights[index].Specular[3] = specular[3];
		
		glLightfv(GetLightID(index), GL_SPECULAR, this->Lights[index].Specular);
	}

	void CLighting::SetLightSpecular (int index, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
	{
		this->Lights[index].Specular[0] = r;
		this->Lights[index].Specular[1] = g;
		this->Lights[index].Specular[2] = b;
		this->Lights[index].Specular[3] = a;
		
		glLightfv(GetLightID(index), GL_SPECULAR, this->Lights[index].Specular);
	}

	//--------------------------------------------------------------------------------------

	void CLighting::SetLightPosition (int index, GLfloat * position)
	{
		this->Lights[index].Position[0] = position[0];
		this->Lights[index].Position[1] = position[1];
		this->Lights[index].Position[2] = position[2];
		this->Lights[index].Position[3] = position[3];

		glLightfv(GetLightID(index), GL_POSITION, this->Lights[index].Position);
	}

	void CLighting::SetLightPosition (int index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
	{
		this->Lights[index].Position[0] = x;
		this->Lights[index].Position[1] = y;
		this->Lights[index].Position[2] = z;
		this->Lights[index].Position[3] = w;
		
		glLightfv(GetLightID(index), GL_POSITION, this->Lights[index].Position);
	}

	//--------------------------------------------------------------------------------------

	void CLighting::SetLightSpotDirection (int index, GLfloat * direction)
	{
		this->Lights[index].SpotDirection[0] = direction[0];
		this->Lights[index].SpotDirection[1] = direction[1];
		this->Lights[index].SpotDirection[2] = direction[2];

		glLightfv(GetLightID(index), GL_SPOT_DIRECTION, this->Lights[index].SpotDirection);
	}

	void CLighting::SetLightSpotDirection (int index, GLfloat x, GLfloat y, GLfloat z)
	{
		this->Lights[index].SpotDirection[0] = x;
		this->Lights[index].SpotDirection[1] = y;
		this->Lights[index].SpotDirection[2] = z;

		glLightfv(GetLightID(index), GL_SPOT_DIRECTION, this->Lights[index].SpotDirection);
	}

	//--------------------------------------------------------------------------------------

	void CLighting::SetLightSpotExponent (int index, GLfloat exponent)
	{
		this->Lights[index].SpotExponent = exponent;

		glLightf(GetLightID(index), GL_SPOT_EXPONENT, this->Lights[index].SpotExponent);
	}

	//--------------------------------------------------------------------------------------

	void CLighting::SetLightSpotCutoff (int index, GLfloat cutoff)
	{
		this->Lights[index].SpotCutoff = cutoff;

		glLightf(GetLightID(index), GL_SPOT_CUTOFF, this->Lights[index].SpotCutoff);
	}

	//--------------------------------------------------------------------------------------

	void CLighting::SetLightConstantAttenuation (int index, GLfloat value)
	{
		this->Lights[index].Attenuation[CONSTANT_ATTENUATION] = value;

		glLightf(GetLightID(index), GL_CONSTANT_ATTENUATION,
				 this->Lights[index].Attenuation[CONSTANT_ATTENUATION]);
	}

	//--------------------------------------------------------------------------------------

	void CLighting::SetLightLinearAttenuation (int index, GLfloat value)
	{
		this->Lights[index].Attenuation[LINEAR_ATTENUATION] = value;

		glLightf(GetLightID(index), GL_LINEAR_ATTENUATION,
				 this->Lights[index].Attenuation[LINEAR_ATTENUATION]);
	}

	//--------------------------------------------------------------------------------------

	void CLighting::SetLightQuadraticAttenuation (int index, GLfloat value)
	{
		this->Lights[index].Attenuation[QUADRATIC_ATTENUATION] = value;

		glLightf(GetLightID(index), GL_QUADRATIC_ATTENUATION,
				 this->Lights[index].Attenuation[QUADRATIC_ATTENUATION]);
	}

	//--------------------------------------------------------------------------------------

	void CLighting::SetLightEnable (int index, bool enable)
	{
		this->Lights[index].Enable = enable;
	}

//******************************************************************************************
// lighting.cpp
//******************************************************************************************