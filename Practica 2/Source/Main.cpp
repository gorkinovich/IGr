//******************************************************************************************
// Gorka Suárez García - Ing. Tec. Inf. de Gestión 2º B.
// Práctica 02 - Apartado 03.
//******************************************************************************************
#include "Yukino/Yukino.h"
using namespace Yukino;
//------------------------------------------------------------------------------------------
#include "Logic.h"
#include "Data.h"
//******************************************************************************************
// Variables del programa.
//******************************************************************************************
Application * App = NULL;
GameData * Data   = NULL;
//******************************************************************************************
// Función WinMain.
//******************************************************************************************
WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                LPSTR lpCmdLine, int nShowCmd)
{
	Log::GetInstance()->Save(false);

	App = Application::GetInstance();
	Data = GameData::GetInstance();

    if(App->CreateAppWnd(hInstance, "Anubis", 800, 600, false, true) &&
	   App->InitInput())
	{
		Data->Init();

		DWORD start;
		do{
			start = App->GetTime();

			App->UpdateWnd();

			Render();

			Logic(App->GetTime() - start);

		}while(App->ExitApplication() == false);
		
		Data->Release();
	}

	App->DestroyAppWnd();
	App->CheckAndSaveLog();

    return 0;
}
//******************************************************************************************
// Main.cpp
//******************************************************************************************