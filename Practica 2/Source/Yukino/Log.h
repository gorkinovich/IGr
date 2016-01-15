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
#ifndef _YUKINO_LOG_H_
#define _YUKINO_LOG_H_
//******************************************************************************************
// Includes
//******************************************************************************************
#include "Base.h"
//******************************************************************************************
// Macros
//******************************************************************************************
#ifdef _DEBUG
	#pragma warning (disable: 4786)
#endif
//******************************************************************************************
// Constantes
//******************************************************************************************
#define EVERYTHING_ALL_RIGHT 0
//------------------------------------------------------------------------------------------
#define UNKNOWN_ERROR    1
#define APPERR_REGWNDCLS 2
#define APPERR_CREATEWND 3
#define APPERR_RESIZEWND 4
//------------------------------------------------------------------------------------------
#define INPERR_DIRECTINPUT8CREATE           200
#define INPERR_CREATEDEVICE_KEYBOARD        201
#define INPERR_SETDATAFORMAT_KEYBOARD       202
#define INPERR_SETCOOPERATIVELEVEL_KEYBOARD 203
#define INPERR_ACQUIRE_KEYBOARD             204
#define INPERR_CREATEDEVICE_MOUSE           205
#define INPERR_SETDATAFORMAT_MOUSE          206
#define INPERR_SETCOOPERATIVELEVEL_MOUSE    207
#define INPERR_ACQUIRE_MOUSE                208
#define INPERR_GETDEVICESTATE_KEYBOARD      209
#define INPERR_GETDEVICESTATE_MOUSE         210
//******************************************************************************************
// Clase Log
//******************************************************************************************
namespace Yukino
{
	class DLLAPI Log
	{
	//--------------------------------------------------------------------------------------
	// Miembros privados.
	//--------------------------------------------------------------------------------------
	private:
		Log ();
		
		static Log * Instance;

	//--------------------------------------------------------------------------------------
	// Miembros protegidos.
	//--------------------------------------------------------------------------------------
	protected:
		list<string> Info; // Listado de notificaciones en el anotador de errores.

		int Error;     // Valor del último error lanzado.
		string ErrMsg; // Mensaje asociado al último error lanzado.

		string FilePath; // Ruta del fichero donde se guardarán las anotaciones.
		
	//--------------------------------------------------------------------------------------
	// Miembros públicos.
	//--------------------------------------------------------------------------------------
	public:
		~Log ();

		//----------------------------------------------------------------------------------
		// Funciones para controlar la lógica.
		//----------------------------------------------------------------------------------
		void Save  (bool append = true);
		void Clear (void);

		void Add (const string & msg, int error = 0);

		void Warning (HWND hWnd = NULL);

		void ClearError (void);

		//----------------------------------------------------------------------------------
		// Gets.
		//----------------------------------------------------------------------------------
		int      GetError  (void);
		string & GetString (void);
		
		//----------------------------------------------------------------------------------
		// Sets.
		//----------------------------------------------------------------------------------
		void SetError    (const string & msg, int error);
		void SetFilePath (const string & path);

		//----------------------------------------------------------------------------------
		// Funciones estáticas.
		//----------------------------------------------------------------------------------
		static Log * GetInstance (void);
	};
}
//******************************************************************************************
#endif
//******************************************************************************************
// Log.h
//******************************************************************************************