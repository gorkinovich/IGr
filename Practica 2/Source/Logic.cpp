//******************************************************************************************
// Gorka Suárez García - Ing. Tec. Inf. de Gestión 2º B.
// Práctica 02 - Apartado 03.
//******************************************************************************************
#ifdef WIN32
	#pragma comment (lib, "glaux.lib")
#endif
//******************************************************************************************
// Includes
//******************************************************************************************
#include "Yukino/Yukino.h"
using namespace Yukino;
//------------------------------------------------------------------------------------------
#include "Logic.h"
#include "Data.h"
//------------------------------------------------------------------------------------------
#include <gl/glaux.h>
//******************************************************************************************
// Cosntantes
//******************************************************************************************
#define MAX_INTERVAL 50
//******************************************************************************************
// Variables externas.
//******************************************************************************************
extern Application * App;
extern GameData    * Data;

bool ActiveFog = false;
//******************************************************************************************
void RenderClear (int w, int h)
{
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glViewport(0, 0, w, h);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
//******************************************************************************************
void DrawCircle (void)
{
	int i;

	glPushMatrix();	
		for(i = 0; i < 360; ++i)
		{
			glRotatef(1.0f, 0.0f, 0.0f, 1.0f);
			glBegin(GL_LINES);
				glVertex3f( 0.1f, 1.0f, 0.0f);
				glVertex3f(-0.1f, 1.0f, 0.0f);
			glEnd();
		}
	glPopMatrix();
}
//------------------------------------------------------------------------------------------
void DrawCircles (void)
{
	int i;

	for(i = 1; i < 8; i += 2)
	{
		glPushMatrix();
			glScalef(i, i, i);
			DrawCircle();
		glPopMatrix();
	}
}
//------------------------------------------------------------------------------------------
void DrawFillCircle (void)
{	
	int i;

	glPushMatrix();
		glScalef(7.0f, 7.0f, 7.0f);
		for(i = 0; i < 360; ++i)
		{
			glRotatef(1.0f, 0.0f, 0.0f, 1.0f);
			glBegin(GL_TRIANGLES);
				glVertex3f( 0.0f, 0.0f, 0.0f);
				glVertex3f( 0.1f, 1.0f, 0.0f);
				glVertex3f(-0.1f, 1.0f, 0.0f);
			glEnd();
		}
	glPopMatrix();
}
//------------------------------------------------------------------------------------------
void DrawRadarLine (void)
{
	glPushMatrix();
		glRotatef(Data->GetRadarAngle(), 0.0f, 0.0f, 1.0f);

		glBegin(GL_LINES);
			glVertex3f(0.0f, 7.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
		glEnd();
	glPopMatrix();
}
//------------------------------------------------------------------------------------------
void DrawRadarEnemy (void)
{	
	int i;

	glPushMatrix();
		glRotatef(Data->GetYaw() - 90.0f, 0.0f, 0.0f, 1.0f);
		glTranslatef(-Data->TankPosition.GetZ() / 5,
					 -Data->TankPosition.GetX() / 5,
					 0.0f);
		
		glTranslatef(Data->EnemyPosition.GetZ() / 5,
					 Data->EnemyPosition.GetX() / 5,
					 0.0f);
		
		for(i = 0; i < 360; ++i)
		{
			glRotatef(1.0f, 0.0f, 0.0f, 1.0f);
			glBegin(GL_TRIANGLES);
				glVertex3f( 0.0f, 0.0f, 0.0f);
				glVertex3f( 0.1f, 1.0f, 0.0f);
				glVertex3f(-0.1f, 1.0f, 0.0f);
			glEnd();
		}
	glPopMatrix();
}
//------------------------------------------------------------------------------------------
void RenderRadar (int x, int y, int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0f, 10.0f, -10.0f, 10.0f, 10.0f, -10.0f);
	glViewport(x, y, w, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	DrawFillCircle();

	glLineWidth(2.0f);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	DrawCircles();

	DrawRadarLine();
	glLineWidth(1.0f);

	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	DrawRadarEnemy();
}
//******************************************************************************************
void DrawCompassMarks (void)
{
	int i;

	glPushMatrix();	
		for(i = 0; i < 36; ++i)
		{
			if((i == 0) || (i == 9) || (i == 18) || (i == 27))
			{
				glBegin(GL_LINES);
					glVertex3f(0.0f, 7.0f, 0.0f);
					glVertex3f(0.0f, 5.5f, 0.0f);
				glEnd();
			}
			else
			{
				glBegin(GL_LINES);
					glVertex3f(0.0f, 7.0f, 0.0f);
					glVertex3f(0.0f, 6.0f, 0.0f);
				glEnd();
			}
			glRotatef(10.0f, 0.0f, 0.0f, 1.0f);
		}
	glPopMatrix();
}
//------------------------------------------------------------------------------------------
void DrawCompassText (void)
{
	Data->PrintString3D(-0.5f,  7.5f, "N");
	Data->PrintString3D(-0.5f, -8.5f, "S");
	Data->PrintString3D( 7.5f, -0.5f, "E");
	Data->PrintString3D(-8.5f, -0.5f, "O");
}
//------------------------------------------------------------------------------------------
void DrawCompassArrow (void)
{
	glBegin(GL_LINE_LOOP);
		glVertex3f( 0.0f,  6.0f, 0.0f);		
		glVertex3f( 1.0f, -1.5f, 0.0f);
		glVertex3f( 0.0f, -4.0f, 0.0f);		
		glVertex3f(-1.0f, -1.5f, 0.0f);
	glEnd();
}
//------------------------------------------------------------------------------------------
void RenderCompass (int x, int y, int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0f, 10.0f, -10.0f, 10.0f, 10.0f, -10.0f);
	glViewport(x, y, w, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
		glRotatef(Data->GetYaw(), 0.0f, 0.0f, 1.0f);
		glColor4f(0.0f, 0.5f, 0.0f, 1.0f);

		DrawCompassMarks();
		DrawCompassText();
	glPopMatrix();

	DrawCompassArrow();
}
//******************************************************************************************
void RenderInfo (int x, int y, int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0f, 10.0f, -10.0f, 10.0f, 10.0f, -10.0f);
	glViewport(x, y, w, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);

	char msg[256];
	sprintf(msg, "Yaw: %f", Data->GetYaw());
	Data->PrintString(-5, 5, msg);
	sprintf(msg, "X:   %f", Data->TankPosition.GetX());
	Data->PrintString(-5, 0, msg);
	sprintf(msg, "Z:   %f", Data->TankPosition.GetZ());
	Data->PrintString(-5, -5, msg);
}
//******************************************************************************************
void DrawFloor (int x, int z)
{
	int i;

	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glPushMatrix();

		i = x - 100;
		i /= 10;
		i *= 10;

		for(; i <= (x + 100); i += 10)
		{
			glBegin(GL_LINES);
				glVertex3f((float) i, -5.0f, z - 100.0f);
				glVertex3f((float) i, -5.0f, z + 100.0f);
			glEnd();
		}
		
		i = z - 100;
		i /= 10;
		i *= 10;

		for(; i <= (z + 100); i += 10)
		{
			glBegin(GL_LINES);
				glVertex3f(x - 100.0f, -5.0f, (float) i);
				glVertex3f(x + 100.0f, -5.0f, (float) i);
			glEnd();
		}

	glPopMatrix();
}
//------------------------------------------------------------------------------------------
void DrawObjects (void)
{
	vector<tAuxObject>::iterator i;

	for(i = Data->Objects.begin(); i != Data->Objects.end(); ++i)
	{
		tAuxObject * obj = i;
		
		glPushMatrix();
		glTranslatef(obj->X, obj->Y, obj->Z);
		glRotatef(obj->Yaw, 0.0f, 1.0f, 0.0f);
		glColor4f(obj->R, obj->G, obj->B, 1.0f);

		switch(obj->Type)
		{
		case TYPE_CUBE:
			auxSolidCube(obj->Param1);
			break;

		case TYPE_SPHERE:
			auxSolidSphere(obj->Param1);
			break;

		case TYPE_BOX:
			auxSolidBox(obj->Param1, obj->Param2, obj->Param3);
			break;

		case TYPE_TORUS:
			auxSolidTorus(obj->Param1, obj->Param2);
			break;

		case TYPE_CYLINDER:
			auxSolidCylinder(obj->Param1, obj->Param2);
			break;

		case TYPE_ICOSAHEDRON:
			auxSolidIcosahedron(obj->Param1);
			break;

		case TYPE_OCTAHEDRON:
			auxSolidOctahedron(obj->Param1);
			break;

		case TYPE_TETRAHEDRON:
			auxSolidTetrahedron(obj->Param1);
			break;

		case TYPE_DODECAHEDRON:
			auxSolidDodecahedron(obj->Param1);
			break;

		case TYPE_CONE:
			auxSolidCone(obj->Param1, obj->Param2);
			break;

		case TYPE_TEAPOT:			
			glFrontFace(GL_CW);
			auxSolidTeapot(obj->Param1);
			glFrontFace(GL_CCW);
			break;
		}

		glPopMatrix();
	}
}
//------------------------------------------------------------------------------------------
void RenderWorld (int x, int y, int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(h == 0) h = 1;
	gluPerspective(45.0f, (GLfloat) w / (GLfloat) h, 0.1f, 200.0f);

	glViewport(x, y, w, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glEnable(GL_BLEND);

	if(ActiveFog)
	{
		glEnable(GL_FOG);

		GLfloat FogColor[4] = {0.8f, 0.8f, 0.4f, 0.8f};

		glFogi(GL_FOG_MODE, GL_LINEAR);
		glFogf(GL_FOG_DENSITY, 0.1f);
		glFogf(GL_FOG_START, 10.0f);
		glFogf(GL_FOG_END, 15.0f);
		glFogfv(GL_FOG_COLOR, FogColor);
		glHint(GL_FOG_HINT, GL_NICEST);
	}


	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glPushMatrix();
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
		
		glFrontFace(GL_CW);
		auxSolidTeapot(1.0f);
		glFrontFace(GL_CCW);
	glPopMatrix();


	Data->GotoCamera();

	DrawFloor(Data->TankPosition.GetX(), Data->TankPosition.GetZ());

	glPushMatrix();
		glTranslatef(Data->EnemyPosition.GetX(), Data->EnemyPosition.GetY(),
					 Data->EnemyPosition.GetZ());
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glScalef(4.0f, 4.0f, 4.0f);

		glFrontFace(GL_CW);
		auxSolidTeapot(1.0f);
		glFrontFace(GL_CCW);
	glPopMatrix();

	DrawObjects();
	
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_FOG);
	//glDisable(GL_BLEND);
}
//******************************************************************************************
void Render (void)
{
	int AppWidth  = App->GetWidth();
	int AppHeight = App->GetHeight();

	int PanelW = 200;
	int PanelH = 200;
	
	int WorldH = AppHeight - PanelH;

	int RadarX = 0;
	int RadarY = AppHeight - PanelH;
	
	int CompassX = AppWidth - PanelW;
	int CompassY = AppHeight - PanelH;

	RenderClear(AppWidth, AppHeight);
	RenderRadar(RadarX, RadarY, PanelW, PanelH);
	RenderCompass(CompassX, CompassY, PanelW, PanelH);

	RenderInfo(RadarX + PanelW, RadarY, (AppWidth - PanelW * 2), PanelH);

	RenderWorld(0, 0, AppWidth, WorldH);

	App->UpdateBuffers();
}
//******************************************************************************************
void Logic (DWORD interval)
{
	static DWORD AccumInterval = 0;
	static bool Pressed = false;

	//--------------------------------------------------------------------------------------
	// Comprobación del teclado.
	//--------------------------------------------------------------------------------------
	App->Input.Update();

	if(App->Input.KeyState(TECLA_ESC))
	{
		App->CloseWnd();
	}

	if(App->Input.KeyState(TECLA_F))
	{
		if(Pressed == false)
		{
			ActiveFog = !ActiveFog;
			Pressed = true;
		}
	}
	else
	{
		Pressed = false;
	}


	if(App->Input.KeyState(TECLA_ARRIBA))
	{
		Data->DecPitch();
	}
	
	if(App->Input.KeyState(TECLA_ABAJO))
	{
		Data->IncPitch();
	}

	if(App->Input.KeyState(TECLA_IZQUIERDA))
	{
		Data->DecYaw();
	}
	
	if(App->Input.KeyState(TECLA_DERECHA))
	{
		Data->IncYaw();
	}
	
	
	if(App->Input.KeyState(TECLA_W))
	{
		Data->MoveForward();
	}

	if(App->Input.KeyState(TECLA_S))
	{
		Data->MoveBackward();
	}

	if(App->Input.KeyState(TECLA_A))
	{
		Data->StrafeLeft();
	}

	if(App->Input.KeyState(TECLA_D))
	{
		Data->StrafeRight();
	}

	//--------------------------------------------------------------------------------------
	// Ejecución de la lógica.
	//--------------------------------------------------------------------------------------
	AccumInterval += interval;

	while(AccumInterval > MAX_INTERVAL)
	{
		Data->IncRadarAngle();

		AccumInterval -= MAX_INTERVAL;
	}
}
//******************************************************************************************
// Logic.cpp
//******************************************************************************************