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
#include "Input.h"
#include "../Log.h"
using namespace Yukino;
//******************************************************************************************
// Constructores, destructores y funciones de copia.
//******************************************************************************************

	//--------------------------------------------------------------------------------------
	// Constructor de la clase Application.
	//--------------------------------------------------------------------------------------
	InputManager::InputManager (void)
	{
		// Interfaces
		this->lpDInput = NULL;
		this->lpKeyb   = NULL;
		this->lpMouse  = NULL;

		// Inicializamos las coordenadas del raton
		this->MouseX = 0;
		this->MouseY = 0;
		this->MouseZ = 0;

		this->Width  = 0;
		this->Height = 0;

		this->hWindow    = 0;
		this->FullScreen = 0;

		this->WndDecX = 0;
		this->WndDecY = 0;
	}

//******************************************************************************************
// Funciones miembro de la clase.
//******************************************************************************************

	//--------------------------------------------------------------------------------------
	// Método para inicializar el dispositivo de entrada.
	//--------------------------------------------------------------------------------------
	bool InputManager::Init (HWND hwnd, LONG width, LONG height, bool fullscreen,
							 bool resizable)
	{
		//----------------------------------------------------------------------------------
		// Configuramos los flags en base al modo de visualización.
		//----------------------------------------------------------------------------------
		DWORD flags;

		if(fullscreen)
		{
			flags = DISCL_BACKGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY;
		}
		else
		{
			flags = DISCL_BACKGROUND | DISCL_NONEXCLUSIVE;
		}

		Log * InpLog = Log::GetInstance();

		//----------------------------------------------------------------------------------
		// Creamos la interfaz principal DInput.
		//----------------------------------------------------------------------------------
		if(FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION,
									 IID_IDirectInput8, (void**) &lpDInput, NULL)))
		{
			InpLog->Add("(-) ¡Fallo al crear la clase DirectInput8!",
						INPERR_DIRECTINPUT8CREATE);
			return false;
		}


		//----------------------------------------------------------------------------------
		// Creación del dispositivo del teclado.
		//----------------------------------------------------------------------------------
		if(FAILED(lpDInput->CreateDevice(GUID_SysKeyboard, &lpKeyb, NULL)))
		{
			InpLog->Add("(-) ¡Fallo al crear el dispositivo del teclado!",
						INPERR_CREATEDEVICE_KEYBOARD);
			return false;
		}
		
		//----------------------------------------------------------------------------------
		// Le indicamos la forma de guardar los datos
		//----------------------------------------------------------------------------------
		if(FAILED(lpKeyb->SetDataFormat(&c_dfDIKeyboard)))
		{
			InpLog->Add("(-) ¡Fallo al configurar el formato de datos del teclado!",
						INPERR_SETDATAFORMAT_KEYBOARD);
			return false;
		}

		//----------------------------------------------------------------------------------
		// Establecemos el nivel coperativo:
		//   DISCL_FOREGROUND   -> El dispositivo solo funciona con la aplicacion activa.
		//   DISCL_BACKGROUND   -> El dispositivo funciona aun sin estar la aplicacion activa.
		//   DISCL_EXCLUSIVE    -> El dispositivo es exclusivo a la aplicacion.
		//   DISCL_NONEXCLUSIVE -> El dispositivo no es exclusivo a la aplicacion.
		//----------------------------------------------------------------------------------
		if(FAILED(lpKeyb->SetCooperativeLevel(hwnd, flags)))
		{
			InpLog->Add("(-) ¡Fallo al indicar el nivel de cooperación del teclado!",
						INPERR_SETCOOPERATIVELEVEL_KEYBOARD);
			return false;
		}
		
		//----------------------------------------------------------------------------------
		// Activamos el teclado.
		//----------------------------------------------------------------------------------
		if(FAILED(lpKeyb->Acquire()))
		{
			InpLog->Add("(-) ¡Fallo al adquirir el teclado!", INPERR_ACQUIRE_KEYBOARD);
			return false;
		}


		//----------------------------------------------------------------------------------
		// Creación del dispositivo del ratón.
		//----------------------------------------------------------------------------------
		if(FAILED(lpDInput->CreateDevice(GUID_SysMouse, &lpMouse, NULL)))
		{
			InpLog->Add("(-) ¡Fallo al crear el dispositivo del ratón!",
						INPERR_CREATEDEVICE_MOUSE);
			return false;
		}
		
		//----------------------------------------------------------------------------------
		// Le indicamos la forma de guardar los datos.
		//----------------------------------------------------------------------------------
		if(FAILED(lpMouse->SetDataFormat(&c_dfDIMouse)))
		{
			InpLog->Add("(-) ¡Fallo al configurar el formato de datos del ratón!",
						INPERR_SETDATAFORMAT_MOUSE);
			return false;
		}
		
		//----------------------------------------------------------------------------------
		// Establecemos el nivel coperativo:
		//   DISCL_FOREGROUND   -> El dispositivo solo funciona con la aplicacion activa.
		//   DISCL_BACKGROUND   -> El dispositivo funciona aun sin estar la aplicacion activa.
		//   DISCL_EXCLUSIVE    -> El dispositivo es exclusivo a la aplicacion.
		//   DISCL_NONEXCLUSIVE -> El dispositivo no es exclusivo a la aplicacion.
		//----------------------------------------------------------------------------------
		if(FAILED(lpMouse->SetCooperativeLevel(hwnd, flags)))
		{
			InpLog->Add("(-) ¡Fallo al indicar el nivel de cooperación del ratón!",
						INPERR_SETCOOPERATIVELEVEL_MOUSE);
			return false;
		}
		
		//----------------------------------------------------------------------------------
		// Activamos el ratón.
		//----------------------------------------------------------------------------------
		if(FAILED(lpMouse->Acquire()))			
		{
			InpLog->Add("(-) ¡Fallo al adquirir el ratón!", INPERR_ACQUIRE_MOUSE);
			return false;
		}

		//----------------------------------------------------------------------------------
		// Guardamos el manejador de la ventana.
		//----------------------------------------------------------------------------------
		this->hWindow    = hwnd;
		this->FullScreen = fullscreen;
		
		this->Width  = 0;
		this->Height = 0;
		
		if(resizable)
		{
			this->WndDecX = WINMODE_INCW;
			this->WndDecY = WINMODE_INCH;
		}
		else
		{
			this->WndDecX = (WINMODE_INCW - WINMODE_FIXED);
			this->WndDecY = (WINMODE_INCH - WINMODE_FIXED);
		}

		//----------------------------------------------------------------------------------
		// Finalente devolvemos que todo ha ido bien.
		//----------------------------------------------------------------------------------
		InpLog->Add("(+) Entrada inicializada correctamente.", EVERYTHING_ALL_RIGHT);

		return true;
	}
	
	//--------------------------------------------------------------------------------------
	// Método para liberar el dispositivo de entrada.
	//--------------------------------------------------------------------------------------
	void InputManager::Release (void)
	{
		//----------------------------------------------------------------------------------
		// Destruimos el raton.
		//----------------------------------------------------------------------------------
		if(this->lpMouse)
		{
			this->lpMouse->Unacquire();
			this->lpMouse->Release();
			this->lpMouse = NULL;
		}

		//----------------------------------------------------------------------------------
		// Destruimos el teclado.
		//----------------------------------------------------------------------------------
		if(this->lpKeyb)
		{
			this->lpKeyb->Unacquire();
			this->lpKeyb->Release();
			this->lpKeyb = NULL;
		}

		//----------------------------------------------------------------------------------
		// Y acabamos con la interfaz primaria DInput.
		//----------------------------------------------------------------------------------
		if(this->lpDInput)
		{
			this->lpDInput->Release();
			this->lpDInput = NULL;
		}
	}
	
	//--------------------------------------------------------------------------------------
	// Método para actualizar la entrada.
	//--------------------------------------------------------------------------------------
	bool InputManager::Update (void)
	{
		//----------------------------------------------------------------------------------
		// Actualizamos el estado de las teclas.
		//----------------------------------------------------------------------------------
		if (FAILED(lpKeyb->GetDeviceState(sizeof(UCHAR[256]), (LPVOID) KeybState)))
		{
			return false;
		}

		//----------------------------------------------------------------------------------
		// Actualizamos el estado del raton.
		//----------------------------------------------------------------------------------
		if (FAILED(lpMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID) &MouseState)))
		{
			return false;
		}
		
		//----------------------------------------------------------------------------------
		// Calculamos las coordenadas absolutas a partir de la API del windows.
		//----------------------------------------------------------------------------------
		POINT point;
		RECT WndRect;

		GetWindowRect(this->hWindow, &WndRect);
		GetCursorPos(&point);

		if(this->FullScreen)
		{
			this->MouseX = point.x - WndRect.left;
			this->MouseY = point.y - WndRect.top;
		}
		else
		{
			this->MouseX = point.x - WndRect.left - this->WndDecX;
			this->MouseY = point.y - WndRect.top - this->WndDecY;
		}

		//----------------------------------------------------------------------------------
		// Calculamos las coordenadas absolutas a partir de las relativas.
		//----------------------------------------------------------------------------------
		this->MouseZ += MouseState.lZ;

		//----------------------------------------------------------------------------------
		// Aplicamos los limites a dichas coordenadas.
		//----------------------------------------------------------------------------------
		if(this->MouseX < 0) this->MouseX = 0;
		if(this->MouseY < 0) this->MouseY = 0;

		if((this->Width  != 0) && (this->MouseX > this->Width))  this->MouseX = this->Width;
		if((this->Height != 0) && (this->MouseY > this->Height)) this->MouseY = this->Height;

		return true;
	}
	
	//--------------------------------------------------------------------------------------
	// Método para comprobar el estado de una tecla.
	//--------------------------------------------------------------------------------------
	BOOL InputManager::KeyState (int key)
	{
		return (this->KeybState[key] & PRESSED);
	}

	//--------------------------------------------------------------------------------------
	// Método para comprobar el estado de un botón del ratón.
	//--------------------------------------------------------------------------------------
	BOOL InputManager::ButtonState (int button)
	{
		return (this->MouseState.rgbButtons[button] & PRESSED);
	}

	//--------------------------------------------------------------------------------------
	// Método para comprobar si el ratón está en una región.
	//--------------------------------------------------------------------------------------
	BOOL InputManager::IsMouseIn (tRect rect)
	{
		return (rect.x <= this->MouseX) && (this->MouseX < rect.x + rect.w) &&
			   (rect.y <= this->MouseY) && (this->MouseY < rect.y + rect.h);
	}

	//--------------------------------------------------------------------------------------
	// Método para actualizar la posición del ratón.
	//--------------------------------------------------------------------------------------
	void InputManager::UpdateMouse (void)
	{
		POINT point;
		RECT WndRect;

		GetWindowRect(this->hWindow, &WndRect);

		if(this->FullScreen)
		{
			point.x = this->MouseX + WndRect.left;
			point.y = this->MouseY + WndRect.left;
		}
		else
		{
			point.x = this->MouseX + WndRect.left + this->WndDecX;
			point.y = this->MouseY + WndRect.left + this->WndDecX;
		}

		SetCursorPos(point.x, point.y);
	}

//******************************************************************************************
// Input.cpp
//******************************************************************************************