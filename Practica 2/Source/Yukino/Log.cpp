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
#ifdef _DEBUG
	#pragma warning (disable: 4786)
#endif
//******************************************************************************************
#include "Log.h"
using namespace Yukino;
//******************************************************************************************
// Propiedades estáticas de la clase.
//******************************************************************************************

	Log * Log::Instance = NULL;

//******************************************************************************************
// Constructores, destructores y funciones de copia.
//******************************************************************************************

	//--------------------------------------------------------------------------------------
	// Constructor de la clase.
	//--------------------------------------------------------------------------------------
	Log::Log ()
	{
		this->Info.clear();
		this->Error    = 0;
		this->ErrMsg   = "";
		this->FilePath = "Yukino.log";
	}

	//--------------------------------------------------------------------------------------
	// Destructor de la clase.
	//--------------------------------------------------------------------------------------
	Log::~Log ()
	{
		this->Clear();
	}

//******************************************************************************************
// Funciones miembro de la clase.
//******************************************************************************************

	//--------------------------------------------------------------------------------------
	// Método para salvar la información anotada.
	//--------------------------------------------------------------------------------------
	void Log::Save (bool append)
	{
		FILE * f = NULL;

		if(append)
			f = fopen(this->FilePath.c_str(), "at");
		else
			f = fopen(this->FilePath.c_str(), "wt");

		if(f != NULL)
		{
			list<string>::iterator i;

			for(i = this->Info.begin(); i != this->Info.end(); ++i)
			{
				fprintf(f, "%s\n", (*i).c_str());
			}
		}

		fclose(f);
	}

	//--------------------------------------------------------------------------------------
	// Método para eliminar la información anotada.
	//--------------------------------------------------------------------------------------
	void Log::Clear (void)
	{
		this->Info.clear();
		this->Error  = 0;
		this->ErrMsg = "";
	}

	//--------------------------------------------------------------------------------------
	// Método para añadir un error o un mensaje al listado de notificaciones.
	//--------------------------------------------------------------------------------------
	void Log::Add (const string & msg, int error)
	{
		this->Error  = error;
		this->ErrMsg = msg;
		this->Info.push_back(msg);
	}

	//--------------------------------------------------------------------------------------
	// Método para lanzar un mensaje al usuario avisándole de que hay un error.
	//--------------------------------------------------------------------------------------
	void Log::Warning (HWND hWnd)
	{
		if(this->Error != 0)
		{
			MessageBox(hWnd, this->ErrMsg.c_str(), "Warning", MB_ICONEXCLAMATION);
		}
	}

	//--------------------------------------------------------------------------------------
	// Método para eliminar el último error lanzado, aunque no será borrado del listado.
	//--------------------------------------------------------------------------------------
	void Log::ClearError (void)
	{
		this->Error  = 0;
		this->ErrMsg = "";
	}

	//--------------------------------------------------------------------------------------
	// Método para obtener la instancia de la clase.
	//--------------------------------------------------------------------------------------
	Log * Log::GetInstance (void)
	{
		if(Log::Instance == NULL)
			Log::Instance = new Log();

		return Log::Instance;
	}

//******************************************************************************************
// Funciones gets de la clase.
//******************************************************************************************

	//--------------------------------------------------------------------------------------
	// Método para obtener el valor del último error almacenado.
	//--------------------------------------------------------------------------------------
	int Log::GetError (void)
	{
		return this->Error;
	}

	//--------------------------------------------------------------------------------------
	// Método para obtener el mensaje del último error almacenado.
	//--------------------------------------------------------------------------------------
	string & Log::GetString (void)
	{
		return this->ErrMsg;
	}

//******************************************************************************************
// Funciones sets de la clase.
//******************************************************************************************

	//--------------------------------------------------------------------------------------
	// Método para modificar el último error almacenado.
	//--------------------------------------------------------------------------------------
	void Log::SetError (const string & msg, int error)
	{
		this->Error  = error;
		this->ErrMsg = msg;
	}

	//--------------------------------------------------------------------------------------
	// Método para modificar la ruta del fichero donde se guardarán las anotaciones.
	//--------------------------------------------------------------------------------------
	void Log::SetFilePath (const string & path)
	{
		this->FilePath = path;
	}

//******************************************************************************************
// Log.cpp
//******************************************************************************************