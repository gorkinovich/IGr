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
#ifndef _YUKINO_APPLICATION_H_
#define _YUKINO_APPLICATION_H_
//******************************************************************************************
// Librer�as con las que hay que enlazar.
//******************************************************************************************
#ifdef WIN32
	#pragma comment (lib, "opengl32.lib")
	#pragma comment (lib, "glu32.lib")
	#pragma comment (lib, "kernel32.lib")
	#pragma comment (lib, "user32.lib")
	#pragma comment (lib, "gdi32.lib")
#endif
//******************************************************************************************
// Includes
//******************************************************************************************
#include "Base.h"
#include "Graphics/Graphics.h"
#include "Input/Input.h"
//------------------------------------------------------------------------------------------
#include <gl/gl.h>
//******************************************************************************************
// Constantes
//******************************************************************************************
#define WNDPROC_PASS 0
#define WNDPROC_FAIL 1
//******************************************************************************************
// Clase Application
//******************************************************************************************
namespace Yukino
{
	class DLLAPI Application
	{
	//--------------------------------------------------------------------------------------
	// Miembros privados.
	//--------------------------------------------------------------------------------------
	private:
		Application ();
		
		static Application * Instance;

	//--------------------------------------------------------------------------------------
	// Miembros protegidos.
	//--------------------------------------------------------------------------------------
	protected:
		//----------------------------------------------------------------------------------
		// Propiedades de la ventana.
		//----------------------------------------------------------------------------------
		HINSTANCE  hInstance; // Manejador de la instancia de la aplicaci�n.
		HWND       hWnd;      // Manejador de la ventana de la aplicaci�n.
		WNDCLASSEX WndClass;  // Datos de la clase de ventana de la aplicaci�n.
		WNDPROC    WndProc;   // Manejador de eventos definido por el usuario.
		
		//----------------------------------------------------------------------------------
		// Propiedades del contexto.
		//----------------------------------------------------------------------------------
		HDC   hDC; // Manejador del dispositivo de contexto de la aplicaci�n.
		HGLRC hRC; // Manejador del dispositivo de contexto de OpenGL.
		
		PIXELFORMATDESCRIPTOR PixelFormat; // Formato del pixel para OpenGL.

		//----------------------------------------------------------------------------------
		// Propiedades de la applicaci�n.
		//----------------------------------------------------------------------------------
		bool FullScreen; // Indicador de si la aplicaci�n es en pantalla completa.
		bool Resizable;  // Indicador de si la ventana puede ser redimensionada.

		string Name; // Nombre de la aplicaci�n.

		int Width;  // Ancho de la ventana de la aplicaci�n.
		int Height; // Alto de la ventana de la aplicaci�n.

		bool ExitApp; // Indicador de si ha llegado ya un evento de fin de la aplicaci�n.

	//--------------------------------------------------------------------------------------
	// Miembros p�blicos.
	//--------------------------------------------------------------------------------------
	public:
		~Application ();

		GraphicsManager * Graphics;
		InputManager      Input;

		//----------------------------------------------------------------------------------
		// Funciones para controlar la l�gica.
		//----------------------------------------------------------------------------------
		bool CreateAppWnd    (HINSTANCE instance, LPCTSTR name, int width, int height,
							  bool fullscreen = false, bool resizable = false);
		void DestroyAppWnd   (void);
		void CheckAndSaveLog (bool append = true);
		
		bool InitInput (void);

		bool CallWndProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		bool ResizeWnd   (int width, int height);
		bool UpdateWnd   (void);

		// M�todo para enviar un mensaje de cierre a la ventana.
		inline void CloseWnd (void)
		{
			PostMessage(this->hWnd, WM_QUIT, 0L, 0L);
		}

		// M�todo para actualizar los buffers de la aplicaci�n.
		inline void UpdateBuffers (void)
		{
			glFlush();
			SwapBuffers(this->hDC);
		}

		// M�todo para mostrar el cursor del rat�n.
		inline void ShowCursor (void)
		{
			::ShowCursor(TRUE);
		}

		// M�todo para esconder el cursor del rat�n.
		inline void HideCursor (void)
		{
			::ShowCursor(FALSE);
		}

		// M�todo para obtener el tiempo transcurrido de ejecuci�n.
		inline DWORD GetTime (void)
		{
			return GetTickCount();
		}

		//----------------------------------------------------------------------------------
		// Gets.
		//----------------------------------------------------------------------------------
		HINSTANCE    GetHInstance (void);
		HWND         GetHWND      (void);
		WNDCLASSEX & GetWndClass  (void);
		WNDPROC      GetWndProc   (void);
		HDC          GetHDC       (void);
		HGLRC        GetHRC       (void);

		PIXELFORMATDESCRIPTOR & GetPixelFormatDescriptor (void);

		bool IsFullScreen (void);
		bool IsResizable  (void);

		const char * GetName (void);

		int GetWidth  (void);
		int GetHeight (void);

		bool ExitApplication (void);

		//----------------------------------------------------------------------------------
		// Sets.
		//----------------------------------------------------------------------------------
		void SetWndProc (WNDPROC wndproc);

		void SetPixelFormatDescriptor (const PIXELFORMATDESCRIPTOR & pfd);

		void SetPFDPixelType     (BYTE pixeltype);
		void SetPFDFlags         (DWORD flags);		
		void SetPFDBuffersBits   (BYTE color, BYTE depth, BYTE stencil, BYTE accum);
		void SetPFDRGBABits      (BYTE red, BYTE green, BYTE blue, BYTE alpha);
		void SetPFDRGBAShift     (BYTE red, BYTE green, BYTE blue, BYTE alpha);
		void SetPFDAccumRGBABits (BYTE red, BYTE green, BYTE blue, BYTE alpha);
		void SetPFDAuxBuffers    (BYTE auxbuffers);
		void SetPFDLayerType     (BYTE layertype);
		void SetPFDReserved      (BYTE reserved);
		void SetPFDMask          (DWORD layer, DWORD visible, DWORD damage);
		
		void SetWidth  (int w);
		void SetHeight (int h);

		//----------------------------------------------------------------------------------
		// Funciones est�ticas.
		//----------------------------------------------------------------------------------
		static Application * GetInstance (void);
	};
}
//******************************************************************************************
#endif
//******************************************************************************************
// Application.h
//******************************************************************************************
