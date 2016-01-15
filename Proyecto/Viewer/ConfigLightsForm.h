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
#ifndef ConfigLightsFormH
#define ConfigLightsFormH
//---------------------------------------------------------------------------
//#include "lighting.h"
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TConfigLightsWnd : public TForm
{
__published:	// IDE-managed Components
    TLabel *LblEnable;
    TComboBox *EnableLighting;
    TLabel *LblAmbient;
    TEdit *Ambient;
    TGroupBox *GBLights;
    TLabel *LblLightAmbient;
    TEdit *LightAmbient;
    TLabel *LblLightDiffuse;
    TEdit *LightDiffuse;
    TLabel *LblLightSpecular;
    TEdit *LightSpecular;
    TLabel *LblLightPosition;
    TEdit *LightPosition;
    TOpenDialog *OpenDialog;
    TSaveDialog *SaveDialog;
    TLabel *LblLight;
    TComboBox *Light;
    TLabel *LblLightSpotDirection;
    TEdit *LightSpotDirection;
    TLabel *LblLightSpotExponent;
    TEdit *LightSpotExponent;
    TLabel *LblLightSpotCutoff;
    TEdit *LightSpotCutoff;
    TLabel *LblLightConstant;
    TEdit *LightConstant;
    TLabel *LblLightLinear;
    TEdit *LightLinear;
    TLabel *LblLightQuadratic;
    TEdit *LightQuadratic;
    TLabel *LblLightEnable;
    TComboBox *LightEnable;
    TButton *CmdLoad;
    TButton *CmdSave;
    TButton *CmdCancel;
    TButton *CmdAccept;
    void __fastcall CmdLoadClick(TObject *Sender);
    void __fastcall CmdSaveClick(TObject *Sender);
    void __fastcall CmdCancelClick(TObject *Sender);
    void __fastcall CmdAcceptClick(TObject *Sender);
    void __fastcall EnableLightingChange(TObject *Sender);
    void __fastcall LightChange(TObject *Sender);
    void __fastcall LightEnableChange(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall AmbientKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall LightAmbientKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall LightDiffuseKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall LightSpecularKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall LightPositionKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall LightSpotDirectionKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall LightSpotExponentKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall LightSpotCutoffKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall LightConstantKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall LightLinearKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall LightQuadraticKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall AmbientExit(TObject *Sender);
    void __fastcall LightAmbientExit(TObject *Sender);
    void __fastcall LightDiffuseExit(TObject *Sender);
    void __fastcall LightSpecularExit(TObject *Sender);
    void __fastcall LightPositionExit(TObject *Sender);
    void __fastcall LightSpotDirectionExit(TObject *Sender);
    void __fastcall LightSpotExponentExit(TObject *Sender);
    void __fastcall LightSpotCutoffExit(TObject *Sender);
    void __fastcall LightConstantExit(TObject *Sender);
    void __fastcall LightLinearExit(TObject *Sender);
    void __fastcall LightQuadraticExit(TObject *Sender);
    void __fastcall AmbientEnter(TObject *Sender);
    void __fastcall LightAmbientEnter(TObject *Sender);
    void __fastcall LightDiffuseEnter(TObject *Sender);
    void __fastcall LightSpecularEnter(TObject *Sender);
    void __fastcall LightPositionEnter(TObject *Sender);
    void __fastcall LightSpotDirectionEnter(TObject *Sender);
    void __fastcall LightSpotExponentEnter(TObject *Sender);
    void __fastcall LightSpotCutoffEnter(TObject *Sender);
    void __fastcall LightConstantEnter(TObject *Sender);
    void __fastcall LightLinearEnter(TObject *Sender);
    void __fastcall LightQuadraticEnter(TObject *Sender);
private:	// User declarations
    bool LightingEnable;
    GLfloat LightingAmbient[4];
    Lighting::tLight Lights[ANUBIS_MAX_LIGHTS];
    
    AnsiString UndoString;
                               
    void __fastcall AmbientChange (void);
    void __fastcall LightAmbientChange (void);
    void __fastcall LightDiffuseChange (void);
    void __fastcall LightSpecularChange (void);
    void __fastcall LightPositionChange (void);
    void __fastcall LightSpotDirectionChange (void);
    void __fastcall LightSpotExponentChange (void);
    void __fastcall LightSpotCutoffChange (void);
    void __fastcall LightConstantChange (void);
    void __fastcall LightLinearChange (void);
    void __fastcall LightQuadraticChange (void);
    void __fastcall LightEnableChange (void);

    int __fastcall GetLightIndex (void);
    void __fastcall SendUpdateRender (void);
    
    void __fastcall SaveLightingConfig (void);
    
public:		// User declarations
    __fastcall TConfigLightsWnd(TComponent* Owner);

    void  __fastcall Update (void);
};
//---------------------------------------------------------------------------
extern PACKAGE TConfigLightsWnd *ConfigLightsWnd;
//---------------------------------------------------------------------------
#endif
//***************************************************************************
// ConfigLightsForm.h
//***************************************************************************
