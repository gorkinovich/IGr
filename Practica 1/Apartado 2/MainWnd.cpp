//---------------------------------------------------------------------------
// Gorka Suárez García - Ing. Tec. Inf. de Gestión 2º B.
// Práctica 01 - Apartado 02.
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop   
//---------------------------------------------------------------------------
#include "MainWnd.h"
#include <gl/glaux.h> 
#pragma link "glaux.lib"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "OpenGLPanel"
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{
    Apartado = 1;
} 
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
    this->OpenGL->MakeOpenGLPanelCurrent();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenGLPaint(TObject *Sender)
{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    if(Apartado == 1)
    {
        glColor3f(1.0f, 0.0f, 0.0f);

        auxWireTeapot(50.0f);
    }
    else
    {      
        glColor3f(1.0f, 1.0f, 1.0f);

        auxWireTeapot(50.0f);

        glColor3f(0.0f, 1.0f, 0.0f);

        glEnable(GL_LINE_STIPPLE);
        glLineStipple(4, 0x7272);

        glBegin(GL_LINES);
            glVertex3f(-100.0f, 0.0f, 0.0f);
            glVertex3f(100.0f, 0.0f, 0.0f);

            glVertex3f(0.0f, -100.0f, 0.0f);
            glVertex3f(0.0f, 100.0f, 0.0f);
        glEnd();
        
        glDisable(GL_LINE_STIPPLE);
    }

    glFlush();
    
    this->OpenGL->SwapBuffers();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenGLResize(TObject *Sender)
{
    if(this->Height == 0) this->Height = 1;

    switch(Apartado)
    {
    case 1:  
    case 2:
        glViewport(0, 0, this->Width, this->Height);

        glLoadIdentity();

        glOrtho(-125.0f, 125.0f, -125.0f, 125.0f, 125.0f, -125.0f);
        break;

    case 3:   
        glViewport(this->Width/2, this->Height/2, this->Width/2, this->Height/2);

        glLoadIdentity();

        glOrtho(-125.0f, 125.0f, -125.0f, 125.0f, 125.0f, -125.0f);
        break;

    case 4:  
        glViewport(this->Width/2, this->Height/2, this->Width/2, this->Height/2);

        glLoadIdentity();

        glOrtho(-50.0f, 50.0f, 25.0f, 125.0f, 125.0f, -125.0f);
        break;
    }

    this->OpenGL->SwapBuffers();
}
//---------------------------------------------------------------------------
void TMainForm::ChangeProjection (void)
{
    this->OpenGL->Perform(WM_SIZE, 0, 0);
    this->OpenGL->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key == 27)
    {
        this->Close();
    }
    else if(Key == '1')
    {
        Apartado = 1;
        ChangeProjection();
    }
    else if(Key == '2')
    {
        Apartado = 2;
        ChangeProjection();
    }
    else if(Key == '3')
    {     
        Apartado = 3;
        ChangeProjection();
    }
    else if(Key == '4')
    {
        Apartado = 4;
        ChangeProjection();
    }
}
//---------------------------------------------------------------------------
