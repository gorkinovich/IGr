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
#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "OpenGLPanel.h"
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp> 
//---------------------------------------------------------------------------
#include "lighting.h"
#include "geometry.h"
//---------------------------------------------------------------------------
const int PIPELINEMODE_FIXED_PIPELINE    = 0;
const int PIPELINEMODE_PERPIXEL_LIGHTING = 1;
const int PIPELINEMODE_NORMAL_MAPPING    = 2;
const int PIPELINEMODE_PARALLAX_MAPPING  = 3;
//---------------------------------------------------------------------------
class TMainWnd : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu;
    TMenuItem *MnuFile;
    TMenuItem *MnuFileOpen;
    TMenuItem *MnuFileSave;
    TMenuItem *MnuFileSaveAs;
    TMenuItem *MnuFileClose;
    TMenuItem *MnuFileSep01;
    TMenuItem *MnuFileImport;
    TMenuItem *MnuFileProperties;
    TMenuItem *MnuFileSep02;
    TMenuItem *MnuFileExit;
    TMenuItem *MnuTool;
    TMenuItem *MnuToolUseFixedPipeline;
    TMenuItem *MnuToolUsePerPixelLighting;
    TMenuItem *MnuToolUseNormalMapping;
    TMenuItem *MnuToolUseParallaxMapping;
    TMenuItem *MnuToolSep01;
    TMenuItem *MnuToolConfigureLights;
    TMenuItem *MnuHelp;
    TMenuItem *MnuToolOptions;
    TMenuItem *MnuHelpHelp;
    TMenuItem *MnuHelpAbout;
    TOpenDialog *OpenDialog;
    TSaveDialog *SaveDialog;
    TStatusBar *StatusBar;
    TToolBar *ToolBar;
    TToolButton *ToolButtonOpen;
    TImageList *ImageList;
    TToolButton *ToolButtonSave;
    TPanel *PropertiesPanel;
    TPanel *OpenGLPanel;
    TOpenGLPanel *OpenGL;
    TToolButton *ToolButtonSep01;
    TToolButton *ToolButtonImport;
    TToolButton *ToolButtonProperties;
    TToolButton *ToolButtonSep02;
    TToolButton *ToolButtonConfigLights;
    TToolButton *ToolButtonUseFixedPipeline;
    TToolButton *ToolButtonUsePerPixelLighting;
    TToolButton *ToolButtonSep03;
    TToolButton *ToolButtonUseParallaxMapping;
    TToolButton *ToolButtonSep04;
    TToolButton *ToolButtonOptions;
    TToolButton *ToolButtonHelp;
    TToolButton *ToolButtonUseNormalMapping;
    TLabel *LblEyeX;
    TEdit *TxtEyeX;
    TLabel *LblEyeY;
    TEdit *TxtEyeY;
    TLabel *LblEyeZ;
    TEdit *TxtEyeZ;
    TLabel *LblScale;
    TEdit *TxtScale;
    TButton *CmdResetObject;
    TButton *CmdResetCamera;
    void __fastcall OpenGLPaint(TObject *Sender);
    void __fastcall OpenGLInit(TObject *Sender);
    void __fastcall MnuFileOpenClick(TObject *Sender);
    void __fastcall MnuFileSaveClick(TObject *Sender);
    void __fastcall MnuFileSaveAsClick(TObject *Sender);
    void __fastcall MnuFileCloseClick(TObject *Sender);
    void __fastcall MnuFileImportClick(TObject *Sender);
    void __fastcall MnuFilePropertiesClick(TObject *Sender);
    void __fastcall MnuFileExitClick(TObject *Sender);
    void __fastcall MnuToolUseFixedPipelineClick(TObject *Sender);
    void __fastcall MnuToolUsePerPixelLightingClick(TObject *Sender);
    void __fastcall MnuToolUseNormalMappingClick(TObject *Sender);
    void __fastcall MnuToolUseParallaxMappingClick(TObject *Sender);
    void __fastcall MnuToolConfigureLightsClick(TObject *Sender);
    void __fastcall MnuToolOptionsClick(TObject *Sender);
    void __fastcall MnuHelpHelpClick(TObject *Sender);
    void __fastcall MnuHelpAboutClick(TObject *Sender);
    void __fastcall ToolButtonOpenClick(TObject *Sender);
    void __fastcall ToolButtonSaveClick(TObject *Sender);
    void __fastcall ToolButtonImportClick(TObject *Sender);
    void __fastcall ToolButtonPropertiesClick(TObject *Sender);
    void __fastcall ToolButtonConfigLightsClick(TObject *Sender);
    void __fastcall ToolButtonUseFixedPipelineClick(TObject *Sender);
    void __fastcall ToolButtonUsePerPixelLightingClick(TObject *Sender);
    void __fastcall ToolButtonUseNormalMappingClick(TObject *Sender);
    void __fastcall ToolButtonUseParallaxMappingClick(TObject *Sender);
    void __fastcall ToolButtonOptionsClick(TObject *Sender);
    void __fastcall ToolButtonHelpClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall ToolButtonOpenMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
    void __fastcall ToolButtonSaveMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
    void __fastcall ToolButtonImportMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
    void __fastcall ToolButtonPropertiesMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
    void __fastcall ToolButtonConfigLightsMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
    void __fastcall ToolButtonUseFixedPipelineMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
    void __fastcall ToolButtonUsePerPixelLightingMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
    void __fastcall ToolButtonUseNormalMappingMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
    void __fastcall ToolButtonUseParallaxMappingMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
    void __fastcall ToolButtonOptionsMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
    void __fastcall ToolButtonHelpMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
    void __fastcall ToolBarMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall OpenGLResize(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall OpenGLMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall OpenGLMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall OpenGLMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall OpenGLExit(TObject *Sender);
    void __fastcall TxtEyeXExit(TObject *Sender);
    void __fastcall TxtEyeXKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall TxtEyeYExit(TObject *Sender);
    void __fastcall TxtEyeYKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall TxtEyeZExit(TObject *Sender);
    void __fastcall TxtEyeZKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall TxtScaleExit(TObject *Sender);
    void __fastcall TxtScaleKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall TxtEyeXEnter(TObject *Sender);
    void __fastcall TxtEyeYEnter(TObject *Sender);
    void __fastcall TxtEyeZEnter(TObject *Sender);
    void __fastcall TxtScaleEnter(TObject *Sender);
    void __fastcall CmdResetObjectClick(TObject *Sender);
    void __fastcall CmdResetCameraClick(TObject *Sender);
private:	// User declarations

    int PipelineMode; // 0..3
    AnsiString FileName;

    int  MouseLastX;
    int  MouseLastY;
    bool MouseActive;

    float PosX;
    float PosY;  
    float PosZ;
    float RotX;
    float RotY;

    float EyeX;
    float EyeY;
    float EyeZ;

    float Scale;

    void __fastcall UpdatePipelineButtons (void);
    void __fastcall SendUpdateRender (void);
    void __fastcall UpdatePropertiesPanel (void);

    AnsiString UndoString;

public:		// User declarations
    __fastcall TMainWnd(TComponent* Owner);

    CLighting Lighting;
    CStaticMesh Model;

    void __fastcall SetPipelineMode (int value);
    int __fastcall GetPipelineMode (void);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainWnd *MainWnd;
//---------------------------------------------------------------------------
#endif
//***************************************************************************
// Fin MainForm.h
//***************************************************************************
