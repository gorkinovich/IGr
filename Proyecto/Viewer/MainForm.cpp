//***************************************************************************
// Anubis Viewer 1.0 - A 3D Adventure Game Engine.
// Copyright (C) 2006-2007  Gorka Suárez García
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//***************************************************************************
#include <vcl.h>
#include <GL/gl.h>
#include <GL/glu.h>
//---------------------------------------------------------------------------
#pragma hdrstop
#include "MainForm.h" 
#include "PropertiesForm.h"
#include "ConfigLightsForm.h"
#include "OptionsForm.h"
#include "AboutForm.h"   
//---------------------------------------------------------------------------
#include "extensions.h"
#include "textures.h"   
#include "content.h" 
#include "shaders.h"
#include "strconv.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "OpenGLPanel"
#pragma resource "*.dfm"
TMainWnd *MainWnd;       
//***************************************************************************
// Constantes.
//***************************************************************************
#define MAINWND_EYEX 0.0f
#define MAINWND_EYEY 0.0f
#define MAINWND_EYEZ 5.0f
#define MAINWND_SCALE 1.0f
//***************************************************************************
// Variables globales.
//***************************************************************************
CContentManager * Content = NULL;
//***************************************************************************
// Métodos de la clase TMainWnd.
//***************************************************************************
__fastcall TMainWnd::TMainWnd(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::UpdatePipelineButtons (void)
{
    switch(this->PipelineMode)
    {
    case PIPELINEMODE_FIXED_PIPELINE:
        this->MnuToolUseFixedPipeline->Checked    = true;
        this->MnuToolUsePerPixelLighting->Checked = false;
        this->MnuToolUseNormalMapping->Checked    = false;
        this->MnuToolUseParallaxMapping->Checked  = false;

        this->ToolButtonUseFixedPipeline->Down    = true;
        this->ToolButtonUsePerPixelLighting->Down = false;
        this->ToolButtonUseNormalMapping->Down    = false;
        this->ToolButtonUseParallaxMapping->Down  = false;
        break;
        
    case PIPELINEMODE_PERPIXEL_LIGHTING: 
        this->MnuToolUseFixedPipeline->Checked    = false;
        this->MnuToolUsePerPixelLighting->Checked = true;
        this->MnuToolUseNormalMapping->Checked    = false;
        this->MnuToolUseParallaxMapping->Checked  = false;

        this->ToolButtonUseFixedPipeline->Down    = false;
        this->ToolButtonUsePerPixelLighting->Down = true;
        this->ToolButtonUseNormalMapping->Down    = false;
        this->ToolButtonUseParallaxMapping->Down  = false;
        break;
        
    case PIPELINEMODE_NORMAL_MAPPING:   
        this->MnuToolUseFixedPipeline->Checked    = false;
        this->MnuToolUsePerPixelLighting->Checked = false;
        this->MnuToolUseNormalMapping->Checked    = true;
        this->MnuToolUseParallaxMapping->Checked  = false;

        this->ToolButtonUseFixedPipeline->Down    = false;
        this->ToolButtonUsePerPixelLighting->Down = false;
        this->ToolButtonUseNormalMapping->Down    = true;
        this->ToolButtonUseParallaxMapping->Down  = false;
        break;
        
    case PIPELINEMODE_PARALLAX_MAPPING:  
        this->MnuToolUseFixedPipeline->Checked    = false;
        this->MnuToolUsePerPixelLighting->Checked = false;
        this->MnuToolUseNormalMapping->Checked    = false;
        this->MnuToolUseParallaxMapping->Checked  = true;

        this->ToolButtonUseFixedPipeline->Down    = false;
        this->ToolButtonUsePerPixelLighting->Down = false;
        this->ToolButtonUseNormalMapping->Down    = false;
        this->ToolButtonUseParallaxMapping->Down  = true;
        break;

    default:
        this->PipelineMode = PIPELINEMODE_FIXED_PIPELINE;
        
        this->MnuToolUseFixedPipeline->Checked    = true;
        this->MnuToolUsePerPixelLighting->Checked = false;
        this->MnuToolUseNormalMapping->Checked    = false;
        this->MnuToolUseParallaxMapping->Checked  = false;

        this->ToolButtonUseFixedPipeline->Down    = true;
        this->ToolButtonUsePerPixelLighting->Down = false;
        this->ToolButtonUseNormalMapping->Down    = false;
        this->ToolButtonUseParallaxMapping->Down  = false;
    }

    CShadersManager * manager = CShadersManager::GetInstance();
    manager->SetLimit((ShaderProgramType) (this->PipelineMode - 1));

    this->SendUpdateRender();
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::SetPipelineMode (int value)
{
    this->PipelineMode = value;  
    this->UpdatePipelineButtons();
}
//---------------------------------------------------------------------------
int __fastcall TMainWnd::GetPipelineMode (void)
{
    return this->PipelineMode;
}    
//---------------------------------------------------------------------------
void __fastcall TMainWnd::SendUpdateRender (void)
{
    MainWnd->OpenGL->Repaint();
    MainWnd->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::UpdatePropertiesPanel (void)
{
    char auxstr[200];

    sprintf(auxstr, "%f", this->EyeX);
    this->TxtEyeX->Text = auxstr;
    
    sprintf(auxstr, "%f", this->EyeY);
    this->TxtEyeY->Text = auxstr;

    sprintf(auxstr, "%f", this->EyeZ);
    this->TxtEyeZ->Text = auxstr;
    
    sprintf(auxstr, "%f", this->Scale);
    this->TxtScale->Text = auxstr;

}
//***************************************************************************
// Eventos de la ventana principal.
//*************************************************************************** 
void __fastcall TMainWnd::FormShow(TObject *Sender)
{
    this->OpenGL->MakeOpenGLPanelCurrent();
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::FormCreate(TObject *Sender)
{              
    this->PipelineMode = PIPELINEMODE_FIXED_PIPELINE; 
    this->UpdatePipelineButtons();

    this->FileName = "";

    this->MouseActive = false;

    this->PosX = 0.0f;
    this->PosY = 0.0f;
    this->PosZ = 0.0f;
    this->RotX = 0.0f;
    this->RotY = 0.0f;

    this->EyeX = MAINWND_EYEX;
    this->EyeY = MAINWND_EYEY;
    this->EyeZ = MAINWND_EYEZ;

    this->Scale = MAINWND_SCALE;

    Content = CContentManager::GetInstance();

    this->OpenDialog->InitialDir = ".";
    this->SaveDialog->InitialDir = ".";

    this->UpdatePropertiesPanel();
}
//***************************************************************************
// Eventos del objeto OpenGL.
//***************************************************************************
void __fastcall TMainWnd::OpenGLPaint(TObject *Sender)
{           
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    gluLookAt(this->EyeX, this->EyeY, this->EyeZ, 0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);
                
    glColor3f(1.0f, 1.0f, 1.0f);
                
    bool firstpass = true;
    glEnable(GL_BLEND);

    for(int i = 0; i < ANUBIS_MAX_LIGHTS; ++i)
    {
        if(this->Lighting.GetLight(i).Enable)
        {
            if(firstpass)
            {
                glDepthFunc(GL_LESS);
                glBlendFunc(GL_ONE, GL_ZERO);
                firstpass = false;
            }
            else
            {
                glDepthFunc(GL_EQUAL);
                glBlendFunc(GL_ONE, GL_ONE);
            }

            this->Lighting.ConfigActiveLight(i);

            glPushMatrix();
                glScalef(this->Scale, this->Scale, this->Scale);
                glTranslatef(this->PosX, this->PosY, this->PosZ);
                glRotatef(this->RotX, 1.0f, 0.0f, 0.0f);
                glRotatef(this->RotY, 0.0f, 1.0f, 0.0f);
                this->Model.Draw();
            glPopMatrix();
        }
    }

    glFlush();
    OpenGL->SwapBuffers();
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::OpenGLResize(TObject *Sender)
{
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(this->OpenGL->Height != 0)
    {
        gluPerspective(45.0f, (GLfloat) this->OpenGL->Width /
                       (GLfloat) this->OpenGL->Height, 0.1f, 200.0f);
    }

	glViewport(0, 0, this->OpenGL->Width, this->OpenGL->Height);    
	glMatrixMode(GL_MODELVIEW);
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::OpenGLInit(TObject *Sender)
{
    if(extLoadExtensions() == false)
    {
        MessageBox(NULL, "The viewer can't load the OpenGL extensions.",
                   "Error", MB_ICONEXCLAMATION);
    }

    this->Lighting.SetEnable(true);
    this->Lighting.SetLightEnable(0, true);
    this->Lighting.Update();

    AboutWnd->Vendor     = (char *) glGetString(GL_VENDOR);
    AboutWnd->Renderer   = (char *) glGetString(GL_RENDERER);
    AboutWnd->Version    = (char *) glGetString(GL_VERSION);
    AboutWnd->Extensions = (char *) glGetString(GL_EXTENSIONS);

    CShadersManager * manager = CShadersManager::GetInstance();
    if(manager->Load() == false)
    {
        AnsiString error;
        error.sprintf("The viewer can't load the shaders.\nError: %d", appGetLastError());
        MessageBox(NULL, error.c_str(), "Error", MB_ICONEXCLAMATION);
    }
    
    manager->SetLimit((ShaderProgramType) (this->PipelineMode - 1));
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::OpenGLMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{    
    this->OpenGL->MakeOpenGLPanelCurrent();

    if(Button == mbLeft)
    {
        POINT point;
        GetCursorPos(&point);
        
        this->MouseLastX  = point.x;
        this->MouseLastY  = point.y;
        this->MouseActive = true;

        this->OpenGL->Cursor = crSizeAll;
    }
}           
//---------------------------------------------------------------------------
void __fastcall TMainWnd::OpenGLExit(TObject *Sender)
{
    this->OpenGL->MakeOpenGLPanelCurrent();
    this->MouseActive = false;
    this->OpenGL->Cursor = crDefault;
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::OpenGLMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    this->OpenGL->MakeOpenGLPanelCurrent();
    this->MouseActive = false;
    this->OpenGL->Cursor = crDefault;
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::OpenGLMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    if(this->MouseActive)
    {
        this->OpenGL->MakeOpenGLPanelCurrent();
                                               
        POINT point;
        GetCursorPos(&point);

        float incx = (point.x - this->MouseLastX);
        float incy = (point.y - this->MouseLastY);

        SetCursorPos(this->MouseLastX, this->MouseLastY);

        const float factor = 10.0f;

        //ssShift, ssAlt, ssCtrl, ssLeft, ssRight, ssMiddle, ssDouble
        if(Shift.Contains(ssLeft))
        {
            if(Shift.Contains(ssShift))
            {
                this->PosX += (incx / factor);
                this->PosY -= (incy / factor);
            }
            else if(Shift.Contains(ssCtrl))
            {
                this->PosX += (incx / factor);
                this->PosZ += (incy / factor);
            }
            else
            {
                this->RotX += incy;
                this->RotY += incx;

                if(this->RotX >= 360.0f) this->RotX -= 360.0f;
                if(this->RotX < 0.0f)    this->RotX += 360.0f;
                
                if(this->RotY >= 360.0f) this->RotY -= 360.0f;
                if(this->RotY < 0.0f)    this->RotY += 360.0f;
            }
        }

        this->SendUpdateRender();
    }
}    
//***************************************************************************
// Eventos de los controles que hay en el panel de propiedades.
//***************************************************************************     
void __fastcall TMainWnd::CmdResetObjectClick(TObject *Sender)
{
    this->PosX = 0.0f;
    this->PosY = 0.0f;
    this->PosZ = 0.0f;
    this->RotX = 0.0f;
    this->RotY = 0.0f;

    this->UpdatePropertiesPanel();
    this->SendUpdateRender();
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::CmdResetCameraClick(TObject *Sender)
{
    this->EyeX = MAINWND_EYEX;
    this->EyeY = MAINWND_EYEY;
    this->EyeZ = MAINWND_EYEZ;

    this->Scale = MAINWND_SCALE;

    this->UpdatePropertiesPanel();
    this->SendUpdateRender();
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::TxtEyeXExit(TObject *Sender)
{
    GLfloat value;

    if(this->TxtEyeX->Text == "") this->TxtEyeX->Text = this->UndoString;

    if(GetFloatFromString(this->TxtEyeX->Text.c_str(), &value))
    {
        this->EyeX = value;
        this->SendUpdateRender();
        this->UndoString = this->TxtEyeX->Text;
    }
    else
    {
        this->TxtEyeX->Text = this->UndoString;
    }
    
    this->UpdatePropertiesPanel();
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::TxtEyeXKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key == 13) this->TxtEyeXExit(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::TxtEyeYExit(TObject *Sender)
{          
    GLfloat value;

    if(this->TxtEyeY->Text == "") this->TxtEyeY->Text = this->UndoString;

    if(GetFloatFromString(this->TxtEyeY->Text.c_str(), &value))
    {
        this->EyeY = value;
        this->SendUpdateRender();
        this->UndoString = this->TxtEyeY->Text;
    }
    else
    {
        this->TxtEyeY->Text = this->UndoString;
    }

    this->UpdatePropertiesPanel();
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::TxtEyeYKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key == 13) this->TxtEyeYExit(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::TxtEyeZExit(TObject *Sender)
{                         
    GLfloat value;

    if(this->TxtEyeZ->Text == "") this->TxtEyeZ->Text = this->UndoString;

    if(GetFloatFromString(this->TxtEyeZ->Text.c_str(), &value))
    {
        this->EyeZ = value;
        this->SendUpdateRender();
        this->UndoString = this->TxtEyeZ->Text;
    }
    else
    {
        this->TxtEyeZ->Text = this->UndoString;
    }

    this->UpdatePropertiesPanel();
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::TxtEyeZKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key == 13) this->TxtEyeZExit(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::TxtScaleExit(TObject *Sender)
{                        
    GLfloat value;

    if(this->TxtScale->Text == "") this->TxtScale->Text = this->UndoString;

    if(GetFloatFromString(this->TxtScale->Text.c_str(), &value))
    {
        this->Scale = value;
        this->SendUpdateRender();
        this->UndoString = this->TxtScale->Text;
    }
    else
    {
        this->TxtScale->Text = this->UndoString;
    }

    this->UpdatePropertiesPanel();
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::TxtScaleKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key == 13) this->TxtScaleExit(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::TxtEyeXEnter(TObject *Sender)
{
    this->UndoString = this->TxtEyeX->Text;
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::TxtEyeYEnter(TObject *Sender)
{
    this->UndoString = this->TxtEyeY->Text;
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::TxtEyeZEnter(TObject *Sender)
{
    this->UndoString = this->TxtEyeZ->Text;
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::TxtScaleEnter(TObject *Sender)
{
    this->UndoString = this->TxtScale->Text;
}
//***************************************************************************
// Eventos del menú Archivo.
//***************************************************************************
void __fastcall TMainWnd::MnuFileOpenClick(TObject *Sender)
{
    this->OpenDialog->Filter = "Anubis Mesh File (*.mesh)|*.mesh|All Files (*.*)|*.*";
    this->OpenDialog->Title = "Open Mesh File";
          
    if(this->OpenDialog->Execute())
    {
        this->OpenGL->MakeOpenGLPanelCurrent();
        this->SetPipelineMode(PIPELINEMODE_FIXED_PIPELINE);
                             
        this->OpenGL->MakeOpenGLPanelCurrent();
        Content->ReleaseAll();
        this->Model.Release();

        if(this->Model.Load(this->OpenDialog->FileName.c_str()) == false)
        {
            MessageBox(NULL, "The viewer can't load the file.",
                       "Error", MB_ICONEXCLAMATION);
        }
        else
        {
            this->FileName = this->OpenDialog->FileName;
        }

        this->SendUpdateRender();
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::MnuFileSaveClick(TObject *Sender)
{
    if(this->FileName == "")
    {
        this->MnuFileSaveAsClick(Sender);
    }
    else
    {
        this->OpenGL->MakeOpenGLPanelCurrent();

        if(this->Model.Save(this->FileName.c_str()) == false)
        {
            MessageBox(NULL, "The viewer can't save the file.",
                       "Error", MB_ICONEXCLAMATION);
        }

        this->SendUpdateRender();
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::MnuFileSaveAsClick(TObject *Sender)
{
    this->SaveDialog->Filter = "Anubis Mesh File (*.mesh)|*.mesh|All Files (*.*)|*.*";
    this->SaveDialog->Title = "Save Mesh File";
          
    if(this->SaveDialog->Execute())
    {          
        this->OpenGL->MakeOpenGLPanelCurrent();

        if(this->Model.Save(this->SaveDialog->FileName.c_str()) == false)
        {
            MessageBox(NULL, "The viewer can't save the file.",
                       "Error", MB_ICONEXCLAMATION);
        }
        else
        {
            this->FileName = this->SaveDialog->FileName;
        }

        this->SendUpdateRender();
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::MnuFileCloseClick(TObject *Sender)
{                        
    this->OpenGL->MakeOpenGLPanelCurrent();
    this->Model.Release();
    this->FileName = "";  
    Content->ReleaseAll();
    this->SendUpdateRender();
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::MnuFileImportClick(TObject *Sender)
{
    this->OpenDialog->Filter = "3D Studio Max File (*.3ds)|*.3ds|All Files (*.*)|*.*";
    this->OpenDialog->Title = "Import";
                                 
    if(this->OpenDialog->Execute())
    {          
        this->OpenGL->MakeOpenGLPanelCurrent();
        this->SetPipelineMode(PIPELINEMODE_FIXED_PIPELINE);
                             
        this->OpenGL->MakeOpenGLPanelCurrent();
        Content->ReleaseAll();
        this->Model.Release();

        if(this->Model.Import(this->OpenDialog->FileName.c_str()) == false)
        {
            MessageBox(NULL, "The viewer can't import the file.",
                       "Error", MB_ICONEXCLAMATION);
        }
                 
        this->FileName = "";
        this->SendUpdateRender();
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::MnuFilePropertiesClick(TObject *Sender)
{                    
    this->OpenGL->MakeOpenGLPanelCurrent();
    PropertiesWnd->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::MnuFileExitClick(TObject *Sender)
{
    Application->Terminate();    
}
//***************************************************************************
// Eventos del menú Herramienta.
//***************************************************************************
void __fastcall TMainWnd::MnuToolUseFixedPipelineClick(TObject *Sender)
{                           
    this->OpenGL->MakeOpenGLPanelCurrent();
    this->SetPipelineMode(PIPELINEMODE_FIXED_PIPELINE);
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::MnuToolUsePerPixelLightingClick(TObject *Sender)
{              
    this->OpenGL->MakeOpenGLPanelCurrent();
    this->SetPipelineMode(PIPELINEMODE_PERPIXEL_LIGHTING);
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::MnuToolUseNormalMappingClick(TObject *Sender)
{        
    this->OpenGL->MakeOpenGLPanelCurrent();
    this->SetPipelineMode(PIPELINEMODE_NORMAL_MAPPING);
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::MnuToolUseParallaxMappingClick(TObject *Sender)
{        
    this->OpenGL->MakeOpenGLPanelCurrent();
    this->SetPipelineMode(PIPELINEMODE_PARALLAX_MAPPING);
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::MnuToolConfigureLightsClick(TObject *Sender)
{      
    this->OpenGL->MakeOpenGLPanelCurrent();
    ConfigLightsWnd->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::MnuToolOptionsClick(TObject *Sender)
{           
    this->OpenGL->MakeOpenGLPanelCurrent();
    OptionsWnd->Show();
}
//***************************************************************************
// Eventos del menú Ayuda.
//***************************************************************************
void __fastcall TMainWnd::MnuHelpHelpClick(TObject *Sender)
{
    this->OpenGL->MakeOpenGLPanelCurrent();
    MessageBox(NULL, "Sorry, no help at the moment...", "Help", 0);
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::MnuHelpAboutClick(TObject *Sender)
{                  
    this->OpenGL->MakeOpenGLPanelCurrent();
    AboutWnd->Show();
}
//***************************************************************************
// Eventos de la barra de botones.
//***************************************************************************
void __fastcall TMainWnd::ToolButtonOpenClick(TObject *Sender)
{
    this->MnuFileOpenClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::ToolButtonSaveClick(TObject *Sender)
{
    this->MnuFileSaveClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::ToolButtonImportClick(TObject *Sender)
{
    this->MnuFileImportClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::ToolButtonPropertiesClick(TObject *Sender)
{                    
    this->OpenGL->MakeOpenGLPanelCurrent();
    PropertiesWnd->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::ToolButtonConfigLightsClick(TObject *Sender)
{                        
    this->OpenGL->MakeOpenGLPanelCurrent();
    ConfigLightsWnd->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::ToolButtonUseFixedPipelineClick(TObject *Sender)
{                       
    this->OpenGL->MakeOpenGLPanelCurrent();
    this->SetPipelineMode(PIPELINEMODE_FIXED_PIPELINE);
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::ToolButtonUsePerPixelLightingClick(
      TObject *Sender)
{                    
    this->OpenGL->MakeOpenGLPanelCurrent();
    this->SetPipelineMode(PIPELINEMODE_PERPIXEL_LIGHTING);
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::ToolButtonUseNormalMappingClick(TObject *Sender)
{                   
    this->OpenGL->MakeOpenGLPanelCurrent();
    this->SetPipelineMode(PIPELINEMODE_NORMAL_MAPPING);
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::ToolButtonUseParallaxMappingClick(
      TObject *Sender)
{                  
    this->OpenGL->MakeOpenGLPanelCurrent();
    this->SetPipelineMode(PIPELINEMODE_PARALLAX_MAPPING);
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::ToolButtonOptionsClick(TObject *Sender)
{
    this->OpenGL->MakeOpenGLPanelCurrent();
    OptionsWnd->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::ToolButtonHelpClick(TObject *Sender)
{
    this->MnuHelpHelpClick(Sender);
}
//---------------------------------------------------------------------------  
void __fastcall TMainWnd::ToolBarMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    this->StatusBar->Panels->Items[0]->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::ToolButtonOpenMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    this->StatusBar->Panels->Items[0]->Text = "Open a new object.";
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::ToolButtonSaveMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    this->StatusBar->Panels->Items[0]->Text = "Save the object.";
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::ToolButtonImportMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    this->StatusBar->Panels->Items[0]->Text = "Import an object.";
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::ToolButtonPropertiesMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    this->StatusBar->Panels->Items[0]->Text = "Set the properties for the object.";
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::ToolButtonConfigLightsMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    this->StatusBar->Panels->Items[0]->Text = "Configure the lights in the scene.";
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::ToolButtonUseFixedPipelineMouseMove(
      TObject *Sender, TShiftState Shift, int X, int Y)
{
    this->StatusBar->Panels->Items[0]->Text = "Set the pipeline to use the fixed pipeline.";
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::ToolButtonUsePerPixelLightingMouseMove(
      TObject *Sender, TShiftState Shift, int X, int Y)
{
    this->StatusBar->Panels->Items[0]->Text = "Set the pipeline to use per-pixel lighting.";
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::ToolButtonUseNormalMappingMouseMove(
      TObject *Sender, TShiftState Shift, int X, int Y)
{
    this->StatusBar->Panels->Items[0]->Text = "Set the pipeline to use normal mapping.";
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::ToolButtonUseParallaxMappingMouseMove(
      TObject *Sender, TShiftState Shift, int X, int Y)
{
    this->StatusBar->Panels->Items[0]->Text = "Set the pipeline to use parallax mapping.";
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::ToolButtonOptionsMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    this->StatusBar->Panels->Items[0]->Text = "Configure the options of the viewer.";
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::ToolButtonHelpMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    this->StatusBar->Panels->Items[0]->Text = "Shows the help of the viewer.";
}
//***************************************************************************
// Fin MainForm.cpp
//***************************************************************************
