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
#include "Application.h"
#include "Log.h"
using namespace Yukino;
//------------------------------------------------------------------------------------------
#include <gl/gl.h>
//******************************************************************************************
// Propiedades est�ticas de la clase.
//******************************************************************************************

	Application * Application::Instance = NULL;

//******************************************************************************************
// Funciones que utiliza la clase.
//******************************************************************************************

	//--------------------------------------------------------------------------------------
	// Funci�n por defecto para manejar los mensajes de Windows.
	//--------------------------------------------------------------------------------------
	LRESULT CALLBACK WndMsgHandler (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		Application * App = Application::GetInstance();

		if(App->CallWndProc(hWnd, uMsg, wParam, lParam))
		{
			return 0;
		}
		else
		{
			switch(uMsg)
			{
			case WM_CREATE:
				return 0;

			case WM_CLOSE:
				PostMessage(hWnd, WM_QUIT, 0L, 0L);
				return 0;
				
			case WM_SIZE:
				App->SetWidth(LOWORD(lParam));
				App->SetHeight(HIWORD(lParam));
				return 0;

			default:
				return DefWindowProc(hWnd, uMsg, wParam, lParam);
			}
		}
	}

//******************************************************************************************
// Constructores, destructores y funciones de copia.
//******************************************************************************************

	//--------------------------------------------------------------------------------------
	// Constructor de la clase Application.
	//--------------------------------------------------------------------------------------
	Application::Application ()
	{
		//----------------------------------------------------------------------------------
		// Inicializaci�n de las propiedades de la clase.
		//----------------------------------------------------------------------------------
		this->hInstance = NULL;
		this->hWnd      = NULL;
		this->WndProc   = NULL;
		
		this->hDC = NULL;
		this->hRC = NULL;

		this->FullScreen = false;
		this->Resizable  = false;
		this->Name       = "";
		this->Width      = 0;
		this->Height     = 0;
		this->ExitApp    = false;
		
		this->Graphics = NULL;
		//this->Sound = NULL;

		//----------------------------------------------------------------------------------
		// Inicializaci�n de la clase ventana.
		//----------------------------------------------------------------------------------
		this->WndClass.cbSize        = sizeof(WNDCLASSEX);
		this->WndClass.style         = CS_HREDRAW | CS_VREDRAW;
		this->WndClass.lpfnWndProc   = (WNDPROC) WndMsgHandler;
		this->WndClass.cbClsExtra    = 0L;
		this->WndClass.cbWndExtra    = 0L;
		this->WndClass.hInstance     = NULL;
		this->WndClass.hIcon         = LoadIcon(NULL, IDI_WINLOGO);
		this->WndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
		this->WndClass.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
		this->WndClass.lpszMenuName  = NULL;
		this->WndClass.lpszClassName = NULL;
		this->WndClass.hIconSm       = NULL;
		
		//----------------------------------------------------------------------------------
		// Inicializaci�n del formato de pixel.
		//----------------------------------------------------------------------------------		
		this->PixelFormat.nSize           = sizeof(PIXELFORMATDESCRIPTOR);
		this->PixelFormat.nVersion        = 1;
		this->PixelFormat.dwFlags         = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
											PFD_DOUBLEBUFFER;
		this->PixelFormat.iPixelType      = PFD_TYPE_RGBA;
		this->PixelFormat.cColorBits      = 32;
		this->PixelFormat.cRedBits        = 0;
		this->PixelFormat.cRedShift       = 0;
		this->PixelFormat.cGreenBits      = 0;
		this->PixelFormat.cGreenShift     = 0;
		this->PixelFormat.cBlueBits       = 0;
		this->PixelFormat.cBlueShift      = 0;
		this->PixelFormat.cAlphaBits      = 0;
		this->PixelFormat.cAlphaShift     = 0;
		this->PixelFormat.cAccumBits      = 32;
		this->PixelFormat.cAccumRedBits   = 0;
		this->PixelFormat.cAccumGreenBits = 0;
		this->PixelFormat.cAccumBlueBits  = 0;
		this->PixelFormat.cAccumAlphaBits = 0;
		this->PixelFormat.cDepthBits      = 16;
		this->PixelFormat.cStencilBits    = 16;
		this->PixelFormat.cAuxBuffers     = 0;
		this->PixelFormat.iLayerType      = PFD_MAIN_PLANE;
		this->PixelFormat.bReserved       = 0;
		this->PixelFormat.dwLayerMask     = 0;
		this->PixelFormat.dwVisibleMask   = 0;
		this->PixelFormat.dwDamageMask    = 0;
	}

	//--------------------------------------------------------------------------------------
	// Destructor de la clase Application.
	//--------------------------------------------------------------------------------------
	Application::~Application ()
	{
	}

//******************************************************************************************
// Funciones miembro de la clase.
//******************************************************************************************

	//--------------------------------------------------------------------------------------
	// M�todo para crear la ventana de la aplicaci�n.
	//--------------------------------------------------------------------------------------	
	bool Application::CreateAppWnd (HINSTANCE instance, LPCTSTR name, int width, int height,
									bool fullscreen, bool resizable)
	{
		//----------------------------------------------------------------------------------
		// Informaci�n de entrada en el fichero de log.
		//----------------------------------------------------------------------------------
		Log * AppLog = Log::GetInstance();

		AppLog->Add("//------------------------------------------------------------");
		AppLog->Add("// Yukino 2.0 log.");
		AppLog->Add("//------------------------------------------------------------\n");

		AppLog->Add("Creando la ventana de la aplicaci�n.");

		//----------------------------------------------------------------------------------
		// Modificamos los �ltimos puntos que no se pod�an configurara en el constructor,
		// de la clase ventana que vamos a registrar para nuestra aplicaci�n. Estos son el
		// identificador de instancia y el nombre de la clase a registrar.
		//----------------------------------------------------------------------------------
		this->WndClass.hInstance     = instance;
		this->WndClass.lpszClassName = name;

		//----------------------------------------------------------------------------------
		// Mandamos a registrar la clase, una vez est� totalmente configurada.
		//----------------------------------------------------------------------------------
		if(!RegisterClassEx(&this->WndClass))
		{
			AppLog->Add("(-) �Error al registrar la clase ventana!", APPERR_REGWNDCLS);
			return false;
		}

		AppLog->Add("(+) Clase ventana registrada correctamente.");

		//----------------------------------------------------------------------------------
		// Si la clase es registrada correctamente, el siguiente paso es modificar el modo
		// de visualizaci�n de la pantalla, siempre y cuando la aplicaci�n sea a pantalla
		// completa. Para ello hace falta tener el ancho, el alto, y la profundidad de
		// color. Si no se lograra poder cambiar el modo de pantalla, ejecutamos la
		// aplicaci�n en modo ventana, avisando en el log del problema.
		//----------------------------------------------------------------------------------
		if(fullscreen)
		{
			DEVMODE devModeScreen;
			memset(&devModeScreen, 0, sizeof(devModeScreen));          // Limpiamos la estructura
			devModeScreen.dmSize       = sizeof(devModeScreen);        // Tama�o de la estructura
			devModeScreen.dmPelsWidth  = width;                        // Ancho de la pantalla
			devModeScreen.dmPelsHeight = height;                       // Alto de la pantalla
			devModeScreen.dmBitsPerPel = this->PixelFormat.cColorBits; // Bpp de la pantalla
			devModeScreen.dmFields     = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

			// Cambiamos el modo de la pantalla, de no lograrlo ponemos fullscreen a falso.
			if(ChangeDisplaySettings(&devModeScreen, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
			{
				AppLog->Add("(-) �Error al intentar pasar a modo pantalla completa!");
				fullscreen = false;
			}
		}

		//----------------------------------------------------------------------------------
		// Configuramos las propiedades internas de la clase, justo en este momento, en el
		// que no van a padecer ning�n cambio que querramos ver reflejado en el futuro.
		//----------------------------------------------------------------------------------
		this->hInstance  = instance;
		this->Name       = name;
		this->Width      = width;
		this->Height     = height;
		this->FullScreen = fullscreen;
		this->Resizable  = resizable;

		//----------------------------------------------------------------------------------
		// Y ahora pasamos a configurar algunas propiedades del estilo y las dimensiones
		// que tendr� la ventana. En modo pantalla completa solo es necesario cambiar el
		// estilo. Pero en modo ventana, dependiendo de de si queremos que sea
		// redimensionable o no, tendremos que manipular las dimensiones de la ventana,
		// para que el area de pintado sea el que hemos indicado.
		//----------------------------------------------------------------------------------
		DWORD WndStyle;
		DWORD WndStyleEx;

		if(fullscreen)
		{
			WndStyleEx = WS_EX_APPWINDOW;
			WndStyle   = WS_POPUP;
			::ShowCursor(FALSE);
		}
		else
		{
			WndStyleEx = NULL;

			if(resizable)
			{
				width  += WINMODE_INCW;
				height += WINMODE_INCH;

				WndStyle = WS_OVERLAPPEDWINDOW;
			}
			else
			{
				width  += (WINMODE_INCW - WINMODE_FIXED);
				height += (WINMODE_INCH - WINMODE_FIXED);

				WndStyle = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE;
			}

			::ShowCursor(TRUE);
		}

		//----------------------------------------------------------------------------------
		// Ajustamos la ventana al tama�o indicado.
		//----------------------------------------------------------------------------------
		RECT WindowRect;
		WindowRect.top    = 0;
		WindowRect.left   = 0;
		WindowRect.bottom = height;
		WindowRect.right  = width;

		AdjustWindowRectEx(&WindowRect, WndStyle, FALSE, WndStyleEx);

		//----------------------------------------------------------------------------------
		// Creamos la ventana con todas las propiedades bien configuradas.
		//----------------------------------------------------------------------------------
		this->hWnd = CreateWindow(name,          // Nombre de la Clase
								  name,          // El titulo de la ventana
								  WndStyle,      // Estilo de la ventana
								  CW_USEDEFAULT, // X
								  CW_USEDEFAULT, // Y
								  width,         // Ancho
								  height,        // Alto
								  NULL,          // Ventana padre
								  NULL,          // Menu de la ventana
								  instance,      // La instancia
								  NULL);
		
		//----------------------------------------------------------------------------------
		// Tras mandar a crear la ventana, comprobamos que todo ha ido bien.
		//----------------------------------------------------------------------------------
		if(this->hWnd == NULL)
		{
			AppLog->Add("(-) �La ventana no ha podido ser creada!", APPERR_CREATEWND);
			return false;
		}

		AppLog->Add("(+) Ventana creada correctamente.");

		//----------------------------------------------------------------------------------
		// Mandamos mostrar la ventana y que sea actualizado su contenido.
		//----------------------------------------------------------------------------------
		ShowWindow(this->hWnd, SW_SHOW);
		UpdateWindow(this->hWnd);

		//----------------------------------------------------------------------------------
		// Obtenemos el dispositivo de contexto de la aplicaci�n, para escoger un formato
		// de pixel lo m�s cercano al que queremos. Y lo mandamos seleccionar para que sea
		// usado en nuestra aplicaci�n.
		//----------------------------------------------------------------------------------
		this->hDC = GetDC(this->hWnd);

		int nPixelFormat; // Indice del formato de pixel escogido

		nPixelFormat = ChoosePixelFormat(this->hDC, &this->PixelFormat);

		SetPixelFormat(this->hDC, nPixelFormat, &this->PixelFormat);

		//----------------------------------------------------------------------------------
		// Tras seleccionar el formato creamos el contexto para OpenGL y lo activamos.
		//----------------------------------------------------------------------------------
		this->hRC = wglCreateContext(this->hDC);
		wglMakeCurrent(this->hDC, this->hRC);

		//----------------------------------------------------------------------------------
		// Indicamos que no se tiene que salir de la aplicaci�n y ya est�.
		//----------------------------------------------------------------------------------
		this->ExitApp = false;

		//----------------------------------------------------------------------------------
		// Obtenemos los gestores de gr�ficos, entrada, sonidos, etc�tera.
		//----------------------------------------------------------------------------------
		this->Graphics = GraphicsManager::GetInstance();
		//this->Sound = SoundManager::GetInstance();

		return true;
	}
		
	//--------------------------------------------------------------------------------------
	// M�todo para destruir la ventana de la aplicaci�n.
	//--------------------------------------------------------------------------------------
	void Application::DestroyAppWnd (void)
	{
		//----------------------------------------------------------------------------------
		// Desactivamos el contexto OpenGL y lo borramos.
		//----------------------------------------------------------------------------------
		wglMakeCurrent(this->hDC, NULL);
		wglDeleteContext(this->hRC);

		//----------------------------------------------------------------------------------
		// Si estamos en modo pantalla completa cambiamos el modo de pantalla.
		//----------------------------------------------------------------------------------
		if(this->FullScreen)
		{
			ChangeDisplaySettings(NULL, 0);
			::ShowCursor(TRUE);
		}

		//----------------------------------------------------------------------------------
		// Y luego borramos del registro la clase de ventana de la aplicaci�n.
		//----------------------------------------------------------------------------------
		UnregisterClass(this->WndClass.lpszClassName, this->WndClass.hInstance);		
	}

	//--------------------------------------------------------------------------------------
	// M�todo para principalmente salvar el log de la aplicaci�n.
	//--------------------------------------------------------------------------------------
	void Application::CheckAndSaveLog (bool append)
	{
		Log * AppLog = Log::GetInstance();

		AppLog->Warning();
		AppLog->Save(append);
		AppLog->Clear();
	}

	//--------------------------------------------------------------------------------------
	// M�todo para inicializar la entrada de la aplicaci�n.
	//--------------------------------------------------------------------------------------
	bool Application::InitInput (void)
	{
		return this->Input.Init(this->hWnd, this->Width, this->Height, this->FullScreen,
								this->Resizable);
	}

	//--------------------------------------------------------------------------------------
	// M�todo para llamar a la funci�n de manejo de eventos del usuario.
	//--------------------------------------------------------------------------------------
	bool Application::CallWndProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		//----------------------------------------------------------------------------------
		// Comprobamos que tenemos una funci�n asignada, y echamos un vistazo a lo que
		// devuelve. Siempre que devuelva 0 ser� que ha sido interceptada por la funci�n
		// que el usuario ha definido. Sino hemos de suponer que no ha sido interceptada,
		// con lo que hemos de devolver false, para que la de la librer�a haga algo.
		//----------------------------------------------------------------------------------
		if(this->WndProc != NULL)
		{
			if(this->WndProc(hWnd, uMsg, wParam, lParam) == WNDPROC_PASS)
				return true;
			else
				return false;
		}
		//----------------------------------------------------------------------------------
		// En caso de no haber asignado ninguna funci�n para manejar eventos, simplemente
		// devolv�remos false para que la funci�n de la librer�a tome el control.
		//----------------------------------------------------------------------------------
		else
		{
			return false;
		}
	}
	
	//--------------------------------------------------------------------------------------
	// M�todo para redimensionar la ventana de forma manual.
	//--------------------------------------------------------------------------------------
	bool Application::ResizeWnd (int width, int height)
	{
		//----------------------------------------------------------------------------------
		// Llamamos a la funci�n MoveWindow para que redimensione la ventana, y en caso de
		// lograrlo, actualizaremos las variables almacenadas en la clase.
		//----------------------------------------------------------------------------------
		if(MoveWindow(this->hWnd, CW_USEDEFAULT, CW_USEDEFAULT, width, height, TRUE))
		{
			this->Width  = width;
			this->Height = height;

			return true;
		}
		//----------------------------------------------------------------------------------
		// Si no lo logra informaremos al log lanzando un error.
		//----------------------------------------------------------------------------------
		else
		{
			Log::GetInstance()->Add("(-) �No se ha podido redimensionar la ventana!",
									APPERR_RESIZEWND);
			return false;
		}
	}

	//--------------------------------------------------------------------------------------
	// M�todo para actualizar la cola de eventos de la ventana.
	//--------------------------------------------------------------------------------------
	bool Application::UpdateWnd (void)
	{
		MSG msg;

		//----------------------------------------------------------------------------------
		// Procesamos el �ltimo mensaje de la cola de eventos de windows. Y si fuera ese
		// mensaje uno de salida de la aplicaci�n (WM_QUIT), actualizamos el valor de la
		// propiedad ExitApp, para indicar que tenemos que terminar la ejecuci�n.
		//----------------------------------------------------------------------------------
		if(PeekMessage(&msg, this->hWnd, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			this->ExitApp = (msg.message == WM_QUIT);

			return true;
		}
		//----------------------------------------------------------------------------------
		// Si no hay eventos indicamos que no hemos actualizado nada.
		//----------------------------------------------------------------------------------
		else
		{
			return false;
		}
	}

	//--------------------------------------------------------------------------------------
	// M�todo para obtener la instancia de la aplicaci�n.
	//--------------------------------------------------------------------------------------
	Application * Application::GetInstance (void)
	{
		if(Application::Instance == NULL)
			Application::Instance = new Application();

		return Application::Instance;
	}

//******************************************************************************************
// Funciones gets de la clase.
//******************************************************************************************
	
	//--------------------------------------------------------------------------------------
	// M�todo para obtener la instancia de la aplicaci�n.
	//--------------------------------------------------------------------------------------
	HINSTANCE Application::GetHInstance (void)
	{
		return this->hInstance;
	}

	//--------------------------------------------------------------------------------------
	// M�todo para obtener el identificador de ventana.
	//--------------------------------------------------------------------------------------
	HWND Application::GetHWND (void)
	{
		return this->hWnd;
	}

	//--------------------------------------------------------------------------------------
	// M�todo para obtener los datos de la clase de la ventana.
	//--------------------------------------------------------------------------------------
	WNDCLASSEX & Application::GetWndClass (void)
	{
		return this->WndClass;
	}

	//--------------------------------------------------------------------------------------
	// M�todo para obtener el puntero a la funci�n de manejo de eventos del usuario.
	//--------------------------------------------------------------------------------------
	WNDPROC Application::GetWndProc (void)
	{
		return this->WndProc;
	}

	//--------------------------------------------------------------------------------------
	// M�todo para obtener el manejador del dispositivo de contexto.
	//--------------------------------------------------------------------------------------
	HDC Application::GetHDC (void)
	{
		return this->hDC;
	}

	//--------------------------------------------------------------------------------------
	// M�todo para obtener el manejador del contexto de OpenGL.
	//--------------------------------------------------------------------------------------
	HGLRC Application::GetHRC (void)
	{
		return this->hRC;
	}

	//--------------------------------------------------------------------------------------
	// M�todo para obtener el descriptor de formato de pixel.
	//--------------------------------------------------------------------------------------
	PIXELFORMATDESCRIPTOR & Application::GetPixelFormatDescriptor (void)
	{
		return this->PixelFormat;
	}

	//--------------------------------------------------------------------------------------
	// M�todo para obtener si se est� ejecutando la aplicaci�n en pantalla completa.
	//--------------------------------------------------------------------------------------
	bool Application::IsFullScreen (void)
	{
		return this->FullScreen;
	}

	//--------------------------------------------------------------------------------------
	// M�todo para obtener si la aplicaci�n se puede redimensionar.
	//--------------------------------------------------------------------------------------
	bool Application::IsResizable (void)
	{
		return this->Resizable;
	}

	//--------------------------------------------------------------------------------------
	// M�todo para obtener el nombre de la aplicaci�n.
	//--------------------------------------------------------------------------------------
	const char * Application::GetName (void)
	{
		return this->Name.c_str();
	}

	//--------------------------------------------------------------------------------------
	// M�todo para obtener el ancho de la aplicaci�n.
	//--------------------------------------------------------------------------------------
	int Application::GetWidth (void)
	{
		return this->Width;
	}

	//--------------------------------------------------------------------------------------
	// M�todo para obtener el alto de la aplicaci�n.
	//--------------------------------------------------------------------------------------
	int Application::GetHeight (void)
	{
		return this->Height;
	}

	//--------------------------------------------------------------------------------------
	// M�todo para obtener si la aplicaci�n a recibido la orden de finalizar.
	//--------------------------------------------------------------------------------------
	bool Application::ExitApplication (void)
	{
		return this->ExitApp;
	}

//******************************************************************************************
// Funciones sets de la clase.
//******************************************************************************************
	
	//--------------------------------------------------------------------------------------
	// M�todo para modificar la funci�n de manejo de eventos de la aplicaci�n.
	//--------------------------------------------------------------------------------------
	void Application::SetWndProc (WNDPROC wndproc)
	{
		this->WndProc = wndproc;
	}

	//--------------------------------------------------------------------------------------
	// M�todo para modificar el formato de pixel de la aplicaci�n.
	//--------------------------------------------------------------------------------------
	void Application::SetPixelFormatDescriptor (const PIXELFORMATDESCRIPTOR & pfd)
	{
		this->PixelFormat = pfd;
	}

	//--------------------------------------------------------------------------------------
	// M�todo para modificar el tipo de pixel del formato de pixel.
	//--------------------------------------------------------------------------------------
	void Application::SetPFDPixelType (BYTE pixeltype)
	{
		this->PixelFormat.iPixelType = pixeltype;
	}

	//--------------------------------------------------------------------------------------
	// M�todo para modificar los flags del formato de pixel.
	//--------------------------------------------------------------------------------------
	void Application::SetPFDFlags (DWORD flags)
	{
		this->PixelFormat.dwFlags = flags;
	}

	//--------------------------------------------------------------------------------------
	// M�todo para modificar el tama�o de los buffers del formato de pixel.
	//--------------------------------------------------------------------------------------		
	void Application::SetPFDBuffersBits (BYTE color, BYTE depth, BYTE stencil, BYTE accum)
	{
		this->PixelFormat.cColorBits   = color;
		this->PixelFormat.cDepthBits   = depth;
		this->PixelFormat.cStencilBits = stencil;
		this->PixelFormat.cAccumBits   = accum;
	}

	//--------------------------------------------------------------------------------------
	// M�todo para modificar el tama�o de los colores del formato de pixel.
	//--------------------------------------------------------------------------------------
	void Application::SetPFDRGBABits (BYTE red, BYTE green, BYTE blue, BYTE alpha)
	{
		this->PixelFormat.cRedBits   = red;
		this->PixelFormat.cGreenBits = green;
		this->PixelFormat.cBlueBits  = blue;
		this->PixelFormat.cAlphaBits = alpha;
	}

	//--------------------------------------------------------------------------------------
	// M�todo para modificar el desplazamiento de los colores del formato de pixel.
	//--------------------------------------------------------------------------------------
	void Application::SetPFDRGBAShift (BYTE red, BYTE green, BYTE blue, BYTE alpha)
	{
		this->PixelFormat.cRedShift   = red;
		this->PixelFormat.cGreenShift = green;
		this->PixelFormat.cBlueShift  = blue;
		this->PixelFormat.cAlphaShift = alpha;
	}

	//--------------------------------------------------------------------------------------
	// M�todo para modificar el tama�o de los colores de acumulaci�n del formato de pixel.
	//--------------------------------------------------------------------------------------
	void Application::SetPFDAccumRGBABits (BYTE red, BYTE green, BYTE blue, BYTE alpha)
	{
		this->PixelFormat.cAccumRedBits   = red;
		this->PixelFormat.cAccumGreenBits = green;
		this->PixelFormat.cAccumBlueBits  = blue;
		this->PixelFormat.cAccumAlphaBits = alpha;
	}

	//--------------------------------------------------------------------------------------
	// M�todo para modificar el n�mero de buffers auxiliares del formato de pixel.
	//--------------------------------------------------------------------------------------		
	void Application::SetPFDAuxBuffers (BYTE auxbuffers)
	{
		this->PixelFormat.cAuxBuffers = auxbuffers;
	}

	//--------------------------------------------------------------------------------------
	// M�todo para modificar el tipo de capa del formato de pixel.
	//--------------------------------------------------------------------------------------
	void Application::SetPFDLayerType (BYTE layertype)
	{
		this->PixelFormat.iLayerType = layertype;
	}

	//--------------------------------------------------------------------------------------
	// M�todo para modificar el n�mero de planos del formato de pixel.
	//--------------------------------------------------------------------------------------
	void Application::SetPFDReserved (BYTE reserved)
	{
		this->PixelFormat.bReserved = reserved;
	}

	//--------------------------------------------------------------------------------------
	// M�todo para modificar las m�scaras del formato de pixel.
	//--------------------------------------------------------------------------------------
	void Application::SetPFDMask (DWORD layer, DWORD visible, DWORD damage)
	{
		this->PixelFormat.dwLayerMask   = layer;
		this->PixelFormat.dwVisibleMask = visible;
		this->PixelFormat.dwDamageMask  = damage;
	}

	//--------------------------------------------------------------------------------------
	// M�todo para modificar el ancho de la aplicaci�n.
	//--------------------------------------------------------------------------------------
	void Application::SetWidth (int w)
	{
		this->Width = w;
	}

	//--------------------------------------------------------------------------------------
	// M�todo para modificar el alto de la aplicaci�n.
	//--------------------------------------------------------------------------------------
	void Application::SetHeight (int h)
	{
		this->Height = h;
	}

//******************************************************************************************
// Application.cpp
//******************************************************************************************