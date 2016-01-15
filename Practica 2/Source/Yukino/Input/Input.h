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
#ifndef _YUKINO_INPUT_INPUT_H_
#define _YUKINO_INPUT_INPUT_H_
//******************************************************************************************
// Librerías con las que hay que enlazar.
//******************************************************************************************
#ifdef WIN32
	#pragma comment (lib, "dxguid.lib")
	#pragma comment (lib, "dinput8.lib")
#endif
//******************************************************************************************
// Includes
//******************************************************************************************
#include "../Base.h"
//------------------------------------------------------------------------------------------
#define DIRECTINPUT_VERSION  0x0800 // Indicamos la version de la libreria DirectInput
#include <dinput.h>
//------------------------------------------------------------------------------------------
#include "Keys.h"
//******************************************************************************************
// Constantes
//******************************************************************************************
const unsigned char PRESSED = 0x80;
//------------------------------------------------------------------------------------------
#define MOUSE_BUTTON_LEFT  0
#define MOUSE_BUTTON_MIDLE 2
#define MOUSE_BUTTON_RIGHT 1
//******************************************************************************************
// Tipos estructurados
//******************************************************************************************
namespace Yukino
{
	typedef struct
	{
		int x, y;
		int w, h;
	} tRect;

	//    typedef struct DIMOUSESTATE { 
	//      LONG lX;
	//      LONG lY;
	//      LONG lZ; 
	//      BYTE rgbButtons[4]; 
	//    } DIMOUSESTATE, *LPDIMOUSESTATE;

//******************************************************************************************
// Clase InputManager
//******************************************************************************************
	class InputManager
	{
	private:
		//----------------------------------------------------------------------------------
		// Interfaces.
		//----------------------------------------------------------------------------------
		LPDIRECTINPUT8       lpDInput;  // Interfaz principal
		LPDIRECTINPUTDEVICE8 lpKeyb;	// Interfaz del teclado
		LPDIRECTINPUTDEVICE8 lpMouse;   // Interfaz del raton

		//----------------------------------------------------------------------------------
		// Informacion sobre el estado de las teclas del teclado.
		//----------------------------------------------------------------------------------
		unsigned char KeybState[256];

		//----------------------------------------------------------------------------------
		// Informacion sobre el estado del raton.
		//----------------------------------------------------------------------------------
		DIMOUSESTATE MouseState;

		//----------------------------------------------------------------------------------
		// Coordenadas absolutas del ratón.
		//----------------------------------------------------------------------------------
		LONG MouseX;
		LONG MouseY;
		LONG MouseZ;
		
		LONG Width;
		LONG Height;

		HWND hWindow;
		bool FullScreen;

		int WndDecX;
		int WndDecY;

	public:
		InputManager ();

		//----------------------------------------------------------------------------------
		// Funciones para la inicialización, finalización y actualización.
		//----------------------------------------------------------------------------------
		bool Init    (HWND hwnd, LONG width, LONG height, bool fullscreen, bool resizable);
		void Release (void);
		bool Update  (void);

		//----------------------------------------------------------------------------------
		// Funciones para saber si una tecla o botón del ratón, están pulsados.
		//----------------------------------------------------------------------------------
		BOOL KeyState    (int key);
		BOOL ButtonState (int button);
		BOOL IsMouseIn   (tRect rect);
		BOOL IsMouseIn   (int x, int y, int w, int h);
		
		void UpdateMouse (void);

		//----------------------------------------------------------------------------------
		// Funciones para obtener las coordenadas absolutas y relativas del ratón.
		//----------------------------------------------------------------------------------
		LONG GetX (void) { return this->MouseX; }
		LONG GetY (void) { return this->MouseY; }
		LONG GetZ (void) { return this->MouseZ; }

		LONG GetRelX (void) { return this->MouseState.lX; }
		LONG GetRelY (void) { return this->MouseState.lY; }
		LONG GetRelZ (void) { return this->MouseState.lZ; }

		LONG GetWidth  (void) { return this->Width;  }
		LONG GetHeight (void) { return this->Height; }

		//----------------------------------------------------------------------------------
		// Funciones para cambiar las coordenadas absolutas del ratón, y para establecer el
		// máximo valor de estos ejes.
		//----------------------------------------------------------------------------------
		inline BOOL SetX (LONG x)
		{
			this->MouseX = x;
			this->UpdateMouse();
		}

		inline BOOL SetY (LONG y)
		{
			this->MouseY = y;
			this->UpdateMouse();
		}

		inline void SetZ (LONG z)
		{
			this->MouseZ = z;
		}

		inline void SetXY (LONG x, LONG y)
		{
			this->MouseX = x;
			this->MouseY = y;
			this->UpdateMouse();
		}

		inline void SetXYZ (LONG x, LONG y, LONG z)
		{
			this->MouseX = x;
			this->MouseY = y;
			this->MouseZ = z;
			this->UpdateMouse();
		}

		inline void SetWidth  (LONG w) { this->Width = w;  }
		inline void SetHeight (LONG h) { this->Height = h; }

		inline void SetMaxXY (LONG w, LONG h) { this->Width = w; this->Height = h; }
	};
}
//******************************************************************************************
#endif
//******************************************************************************************
// Input.h
//******************************************************************************************
