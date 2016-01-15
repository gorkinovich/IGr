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
//---------------------------------------------------------------------------
#pragma hdrstop    
#include "MainForm.h"
#include "ConfigLightsForm.h"
#include "strconv.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TConfigLightsWnd *ConfigLightsWnd;
//***************************************************************************
// Métodos de la clase TConfigLightsWnd.
//***************************************************************************
__fastcall TConfigLightsWnd::TConfigLightsWnd(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::FormShow(TObject *Sender)
{           
    this->Update();
    this->SaveLightingConfig();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::CmdLoadClick(TObject *Sender)
{
    if(this->OpenDialog->Execute())
    {
        MainWnd->Lighting.Load(this->OpenDialog->FileName.c_str());  
        this->Update();        
        this->SendUpdateRender();
    }
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::CmdSaveClick(TObject *Sender)
{
    if(this->SaveDialog->Execute())
    {
        MainWnd->Lighting.Save(this->SaveDialog->FileName.c_str());
    }
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::CmdCancelClick(TObject *Sender)
{     
    MainWnd->Lighting.SetEnable(this->LightingEnable);

    MainWnd->Lighting.SetAmbient(this->LightingAmbient);

    for(int i = 0; i < 8; ++i)
        MainWnd->Lighting.SetLight(i, this->Lights[i]);
                
    this->SendUpdateRender();
    this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::CmdAcceptClick(TObject *Sender)
{
    this->SendUpdateRender();
    this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::EnableLightingChange(TObject *Sender)
{
    if(this->EnableLighting->Text.LowerCase() == "true")
        MainWnd->Lighting.SetEnable(true);
    else if(this->EnableLighting->Text.LowerCase() == "false")
        MainWnd->Lighting.SetEnable(false);

    this->SendUpdateRender();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::AmbientKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
    if(Key == 13) this->AmbientChange();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightChange(TObject *Sender)
{
    this->Update();

    if(this->GetLightIndex() == 0)
        this->Light->Text = "GL_LIGHT0";
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightAmbientKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
    if(Key == 13) this->LightAmbientChange();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightDiffuseKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
    if(Key == 13) this->LightDiffuseChange();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightSpecularKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
    if(Key == 13) this->LightSpecularChange();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightPositionKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
    if(Key == 13) this->LightPositionChange();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightSpotDirectionKeyDown(
      TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == 13) this->LightSpotDirectionChange();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightSpotExponentKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
    if(Key == 13) this->LightSpotExponentChange();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightSpotCutoffKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
    if(Key == 13) this->LightSpotCutoffChange();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightConstantKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
    if(Key == 13) this->LightConstantChange();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightLinearKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
    if(Key == 13) this->LightLinearChange();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightQuadraticKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
    if(Key == 13) this->LightQuadraticChange();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::AmbientExit(TObject *Sender)
{
    this->AmbientChange();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightAmbientExit(TObject *Sender)
{
    this->LightAmbientChange();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightDiffuseExit(TObject *Sender)
{
    this->LightDiffuseChange();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightSpecularExit(TObject *Sender)
{
    this->LightSpecularChange();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightPositionExit(TObject *Sender)
{
    this->LightPositionChange();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightSpotDirectionExit(TObject *Sender)
{
    this->LightSpotDirectionChange();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightSpotExponentExit(TObject *Sender)
{
    this->LightSpotExponentChange();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightSpotCutoffExit(TObject *Sender)
{
    this->LightSpotCutoffChange();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightConstantExit(TObject *Sender)
{
    this->LightConstantChange();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightLinearExit(TObject *Sender)
{
    this->LightLinearChange();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightQuadraticExit(TObject *Sender)
{
    this->LightQuadraticChange();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightEnableChange(TObject *Sender)
{
    if(this->LightEnable->Text.LowerCase() == "true")
        MainWnd->Lighting.SetLightEnable(this->GetLightIndex(), true);
    else if(this->LightEnable->Text.LowerCase() == "false")
        MainWnd->Lighting.SetLightEnable(this->GetLightIndex(), false);

    this->SendUpdateRender();
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::FormCreate(TObject *Sender)
{
    this->OpenDialog->InitialDir = ".";
    this->SaveDialog->InitialDir = ".";
}                               
//--------------------------------------------------------------------------- 
void __fastcall TConfigLightsWnd::AmbientEnter(TObject *Sender)
{
    UndoString = this->Ambient->Text;
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightAmbientEnter(TObject *Sender)
{
    UndoString = this->LightAmbient->Text;
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightDiffuseEnter(TObject *Sender)
{
    UndoString = this->LightDiffuse->Text;
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightSpecularEnter(TObject *Sender)
{
    UndoString = this->LightSpecular->Text;
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightPositionEnter(TObject *Sender)
{
    UndoString = this->LightPosition->Text;
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightSpotDirectionEnter(TObject *Sender)
{
    UndoString = this->LightSpotDirection->Text;
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightSpotExponentEnter(TObject *Sender)
{
    UndoString = this->LightSpotExponent->Text;
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightSpotCutoffEnter(TObject *Sender)
{
    UndoString = this->LightSpotCutoff->Text;
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightConstantEnter(TObject *Sender)
{
    UndoString = this->LightConstant->Text;
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightLinearEnter(TObject *Sender)
{
    UndoString = this->LightLinear->Text;
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightQuadraticEnter(TObject *Sender)
{
    UndoString = this->LightQuadratic->Text;
}
//***************************************************************************
// ConfigLightsForm.cpp
//***************************************************************************
