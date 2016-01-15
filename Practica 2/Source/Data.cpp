//******************************************************************************************
// Gorka Suárez García - Ing. Tec. Inf. de Gestión 2º B.
// Práctica 02 - Apartado 03.
//******************************************************************************************
#include "Data.h"
#include <math.h>
//******************************************************************************************
// Variables externas.
//******************************************************************************************
extern Application * App;
//******************************************************************************************
// Miembros estáticos de la clase.
//******************************************************************************************
GameData * GameData::Instance = NULL;
//******************************************************************************************
// Funciones auxiliares externas a la clase.
//******************************************************************************************
unsigned int CreateBitmapFont (char * fontname, int fontsize)
{
    HFONT hFont;
    unsigned int base;

    if(stricmp(fontname, "symbol") == 0)
    {
        hFont = CreateFont (fontsize, 0, 0, 0, FW_BOLD, FALSE, FALSE,
                            FALSE, SYMBOL_CHARSET, OUT_TT_PRECIS,
                            CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
                            FF_DONTCARE | DEFAULT_PITCH, fontname);
    }
    else
    {
        hFont = CreateFont (fontsize, 0, 0, 0, FW_BOLD, FALSE, FALSE,
                            FALSE, ANSI_CHARSET, OUT_TT_PRECIS,
                            CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
                            FF_DONTCARE | DEFAULT_PITCH, fontname);
    }

    if(!hFont) return 0;

    base = glGenLists(96);
    SelectObject(Application::GetInstance()->GetHDC(), hFont);
    wglUseFontBitmaps(Application::GetInstance()->GetHDC(), 32, 96, base);

    return base;
}

unsigned int CreateBitmapFont3D (char * fontname, int fontsize)
{
    HFONT hFont;
    unsigned int base;

	GLYPHMETRICSFLOAT * gmf = NULL;

    if(stricmp(fontname, "symbol") == 0)
    {
        hFont = CreateFont (fontsize, 0, 0, 0, FW_BOLD, FALSE, FALSE,
                            FALSE, SYMBOL_CHARSET, OUT_TT_PRECIS,
                            CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
                            FF_DONTCARE | DEFAULT_PITCH, fontname);
    }
    else
    {
        hFont = CreateFont (fontsize, 0, 0, 0, FW_BOLD, FALSE, FALSE,
                            FALSE, ANSI_CHARSET, OUT_TT_PRECIS,
                            CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
                            FF_DONTCARE | DEFAULT_PITCH, fontname);
    }

    if(!hFont) return 0;

    base = glGenLists(256);
    SelectObject(Application::GetInstance()->GetHDC(), hFont);
    wglUseFontOutlines(Application::GetInstance()->GetHDC(), 0, 255, base, 0.0f, 2.0f,
                       WGL_FONT_POLYGONS, gmf);

    return base;
}
//------------------------------------------------------------------------------------------
void PrintString (unsigned int base, char * str)
{
    if((base == 0) || (str == NULL)) return;

    glPushAttrib(GL_LIST_BIT);
        glListBase(base - 32);
        glCallLists(strlen(str), GL_UNSIGNED_BYTE, str);
    glPopAttrib();
}

void PrintString3D (unsigned int base, char * str)
{
    if((base == 0) || (str == NULL)) return;

    glPushAttrib(GL_LIST_BIT);
        glListBase(base);
        glCallLists(strlen(str), GL_UNSIGNED_BYTE, str);
    glPopAttrib();

}
//------------------------------------------------------------------------------------------
void ClearFont (unsigned int base)
{
    if(base != 0)
        glDeleteLists(base, 96);
}
//******************************************************************************************
// Constructor y destructor de la clase.
//******************************************************************************************
GameData::GameData()
{
}
//------------------------------------------------------------------------------------------
GameData::~GameData()
{
}
//******************************************************************************************
// Métodos de la clase.
//******************************************************************************************
void GameData::Init (void)
{
	this->Font = CreateBitmapFont("Courier New", 24);
	this->Font3D = CreateBitmapFont3D("Courier New", 12);

	if(this->Font == 0) MessageBox(NULL, "No se pudo cargar la fuente", "Fallo", 0);

	this->Yaw   = 0.0f;
	this->Pitch = 0.0f;

	this->TankPosition.SetX(0);
	this->TankPosition.SetY(1);
	this->TankPosition.SetZ(0);
	
	this->EnemyPosition.SetX(5);
	this->EnemyPosition.SetY(0);
	this->EnemyPosition.SetZ(-10);

	this->RadarAngle = 0.0f;



	//--------------------------------------------------------------------------------------
	// Cubo
	//--------------------------------------------------------------------------------------
	tAuxObject aux;

	aux.Type = TYPE_CUBE;
	
	aux.Param1 = 5.0f;
	aux.Param2 = 0.0f;
	aux.Param3 = 0.0f;
	
	aux.X = -10.0f;
	aux.Y = 0.0f;
	aux.Z = -10.0f;
	
	aux.R = 1.0f;
	aux.G = 1.0f;
	aux.B = 1.0f;
	
	aux.Yaw = 0.0f;

	this->Objects.push_back(aux);
	
	//--------------------------------------------------------------------------------------
	// Cono
	//--------------------------------------------------------------------------------------
	aux.Type = TYPE_CONE;
	
	aux.Param1 = 5.0f;
	aux.Param2 = 10.0f;
	aux.Param3 = 0.0f;
	
	aux.X = -30.0f;
	aux.Y = 0.0f;
	aux.Z = 10.0f;
	
	aux.R = 0.2f;
	aux.G = 0.3f;
	aux.B = 0.8f;
	
	aux.Yaw = 180.0f;

	this->Objects.push_back(aux);
	
	//--------------------------------------------------------------------------------------
	// Cono
	//--------------------------------------------------------------------------------------
	aux.Type = TYPE_CONE;
	
	aux.Param1 = 5.0f;
	aux.Param2 = 10.0f;
	aux.Param3 = 0.0f;
	
	aux.X = -30.0f;
	aux.Y = 0.0f;
	aux.Z = 10.0f;
	
	aux.R = 0.2f;
	aux.G = 0.3f;
	aux.B = 0.8f;
	
	aux.Yaw = 0.0f;

	this->Objects.push_back(aux);
	
	//--------------------------------------------------------------------------------------
	// Esfera
	//--------------------------------------------------------------------------------------
	aux.Type = TYPE_SPHERE;
	
	aux.Param1 = 5.0f;
	aux.Param2 = 0.0f;
	aux.Param3 = 0.0f;
	
	aux.X = 10.0f;
	aux.Y = 0.0f;
	aux.Z = 10.0f;
	
	aux.R = 0.2f;
	aux.G = 0.8f;
	aux.B = 0.4f;
	
	aux.Yaw = 0.0f;

	this->Objects.push_back(aux);
}
//------------------------------------------------------------------------------------------
void GameData::Release (void)
{
	ClearFont(this->Font);
	ClearFont(this->Font3D);
}
//------------------------------------------------------------------------------------------
void GameData::PrintString (GLfloat x, GLfloat y, char * str)
{
    glRasterPos2f(x, y);
	::PrintString(this->Font, str);
}
//------------------------------------------------------------------------------------------
void GameData::PrintString3D (GLfloat x, GLfloat y, char * str)
{
	glPushMatrix();
		glTranslatef(x, y, 0);
		glScalef(2, 2, 2);
		::PrintString3D(this->Font3D, str);
	glPopMatrix();
}
//------------------------------------------------------------------------------------------
void GameData::IncRadarAngle (void)
{
	RadarAngle -= 1.0f;

	if(RadarAngle <= 0.0f) RadarAngle += 360.0f;
}
//------------------------------------------------------------------------------------------
void GameData::IncYaw (void)
{
	Yaw += 1.0f;

	if(Yaw < 0.0f)
		Yaw += 360.0f;
	else if(Yaw >= 360.0f)
		Yaw -= 360.0f;

	//App->Graphics->Camera.SetYaw(Yaw);
}
//------------------------------------------------------------------------------------------
void GameData::DecYaw (void)
{
	Yaw -= 1.0f;

	if(Yaw < 0.0f)
		Yaw += 360.0f;
	else if(Yaw >= 360.0f)
		Yaw -= 360.0f;

	//App->Graphics->Camera.SetYaw(Yaw);
}
//------------------------------------------------------------------------------------------
void GameData::IncPitch (void)
{
	Pitch += 1.0f;

	if(Pitch > 90.0f) Pitch = 90.0f;
	
	//App->Graphics->Camera.SetPitch(Pitch);
}
//------------------------------------------------------------------------------------------
void GameData::DecPitch (void)
{
	Pitch -= 1.0f;

	if(Pitch < -90.0f) Pitch = -90.0f;
	
	//App->Graphics->Camera.SetPitch(Pitch);
}
//------------------------------------------------------------------------------------------
void GameData::GotoCamera (void)
{
	// pitch indica el giro en el eje X
	glRotatef(Pitch, 1.0f, 0.0f, 0.0f);

	// yaw indica el giro en el eje Y
	glRotatef(Yaw, 0.0f, 1.0f, 0.0f);

	// y movemos la camara a unas coordenadas
	glTranslatef(-TankPosition.GetX(), -TankPosition.GetY(), -TankPosition.GetZ());
}
//------------------------------------------------------------------------------------------
void GameData::MoveForward (void)
{
	float inc = 1.0f;
	float rad = this->Yaw * PI / 180.f;
	
	TankPosition.SetZ(TankPosition.GetZ() - inc * cos(rad));
	TankPosition.SetX(TankPosition.GetX() + inc * sin(rad));
}
//------------------------------------------------------------------------------------------
void GameData::MoveBackward (void)
{
	float inc = 1.0f;
	float rad = this->Yaw * PI / 180.f;

	TankPosition.SetZ(TankPosition.GetZ() + inc * cos(rad));
	TankPosition.SetX(TankPosition.GetX() - inc * sin(rad));
}
//------------------------------------------------------------------------------------------
void GameData::StrafeLeft (void)
{
	float inc = 1.0f;
	float rad = this->Yaw * PI / 180.f;

	TankPosition.SetZ(TankPosition.GetZ() - inc * sin(rad));
	TankPosition.SetX(TankPosition.GetX() - inc * cos(rad));
}
//------------------------------------------------------------------------------------------
void GameData::StrafeRight (void)
{
	float inc = 1.0f;
	float rad = this->Yaw * PI / 180.f;

	TankPosition.SetZ(TankPosition.GetZ() + inc * sin(rad));
	TankPosition.SetX(TankPosition.GetX() + inc * cos(rad));
}
//******************************************************************************************
// Métodos estáticos de la clase.
//******************************************************************************************
GameData * GameData::GetInstance (void)
{
	if(GameData::Instance == NULL)
		GameData::Instance = new GameData();

	return GameData::Instance;
}
//******************************************************************************************
// Data.cpp
//******************************************************************************************