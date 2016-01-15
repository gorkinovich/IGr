//******************************************************************************************
// Yukino 2.0 - A 3D game library.
// Copyright (C) 2006  Gorka Su�rez Garc�a
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
// Propiedades est�ticas de la clase.
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
	// M�todo para salvar la informaci�n anotada.
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
	// M�todo para eliminar la informaci�n anotada.
	//--------------------------------------------------------------------------------------
	void Log::Clear (void)
	{
		this->Info.clear();
		this->Error  = 0;
		this->ErrMsg = "";
	}

	//--------------------------------------------------------------------------------------
	// M�todo para a�adir un error o un mensaje al listado de notificaciones.
	//--------------------------------------------------------------------------------------
	void Log::Add (const string & msg, int error)
	{
		this->Error  = error;
		this->ErrMsg = msg;
		this->Info.push_back(msg);
	}

	//--------------------------------------------------------------------------------------
	// M�todo para lanzar un mensaje al usuario avis�ndole de que hay un error.
	//--------------------------------------------------------------------------------------
	void Log::Warning (HWND hWnd)
	{
		if(this->Error != 0)
		{
			MessageBox(hWnd, this->ErrMsg.c_str(), "Warning", MB_ICONEXCLAMATION);
		}
	}

	//--------------------------------------------------------------------------------------
	// M�todo para eliminar el �ltimo error lanzado, aunque no ser� borrado del listado.
	//--------------------------------------------------------------------------------------
	void Log::ClearError (void)
	{
		this->Error  = 0;
		this->ErrMsg = "";
	}

	//--------------------------------------------------------------------------------------
	// M�todo para obtener la instancia de la clase.
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
	// M�todo para obtener el valor del �ltimo error almacenado.
	//--------------------------------------------------------------------------------------
	int Log::GetError (void)
	{
		return this->Error;
	}

	//--------------------------------------------------------------------------------------
	// M�todo para obtener el mensaje del �ltimo error almacenado.
	//--------------------------------------------------------------------------------------
	string & Log::GetString (void)
	{
		return this->ErrMsg;
	}

//******************************************************************************************
// Funciones sets de la clase.
//******************************************************************************************

	//--------------------------------------------------------------------------------------
	// M�todo para modificar el �ltimo error almacenado.
	//--------------------------------------------------------------------------------------
	void Log::SetError (const string & msg, int error)
	{
		this->Error  = error;
		this->ErrMsg = msg;
	}

	//--------------------------------------------------------------------------------------
	// M�todo para modificar la ruta del fichero donde se guardar�n las anotaciones.
	//--------------------------------------------------------------------------------------
	void Log::SetFilePath (const string & path)
	{
		this->FilePath = path;
	}

//******************************************************************************************
// Log.cpp
//******************************************************************************************