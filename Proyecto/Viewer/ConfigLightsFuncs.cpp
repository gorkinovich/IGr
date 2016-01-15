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
#pragma hdrstop    
//---------------------------------------------------------------------------
#include "MainForm.h"
#include "ConfigLightsForm.h"
#include "strconv.h"
//***************************************************************************
// Métodos de la clase TConfigLightsWnd.
//***************************************************************************  
int __fastcall TConfigLightsWnd::GetLightIndex (void)
{
    if(this->Light->Text == "GL_LIGHT0")      return 0;
    else if(this->Light->Text == "GL_LIGHT1") return 1;
    else if(this->Light->Text == "GL_LIGHT2") return 2;
    else if(this->Light->Text == "GL_LIGHT3") return 3;
    else if(this->Light->Text == "GL_LIGHT4") return 4;
    else if(this->Light->Text == "GL_LIGHT5") return 5;
    else if(this->Light->Text == "GL_LIGHT6") return 6;
    else if(this->Light->Text == "GL_LIGHT7") return 7;

    return 0;
}
//---------------------------------------------------------------------------  
void __fastcall TConfigLightsWnd::SendUpdateRender (void)
{
    MainWnd->OpenGL->Repaint();
    MainWnd->Repaint();
}        
//---------------------------------------------------------------------------
void  __fastcall TConfigLightsWnd::Update (void)
{
    this->EnableLighting->Text = (MainWnd->Lighting.GetEnable() ? "true" : "false");

    GLfloat value;
    GLfloat * vector = MainWnd->Lighting.GetAmbient();
    char auxstr[200];

    sprintf(auxstr, "%d, %d, %d, %d", ColorFloatToInt(vector[0]),
            ColorFloatToInt(vector[1]), ColorFloatToInt(vector[2]),
            ColorFloatToInt(vector[3]));

    this->Ambient->Text = auxstr;

    Lighting::tLight & light = MainWnd->Lighting.GetLight(this->GetLightIndex());

    vector = light.Ambient;
    sprintf(auxstr, "%d, %d, %d, %d", ColorFloatToInt(vector[0]),
            ColorFloatToInt(vector[1]), ColorFloatToInt(vector[2]),
            ColorFloatToInt(vector[3]));
    this->LightAmbient->Text = auxstr;

    vector = light.Diffuse;
    sprintf(auxstr, "%d, %d, %d, %d", ColorFloatToInt(vector[0]),
            ColorFloatToInt(vector[1]), ColorFloatToInt(vector[2]),
            ColorFloatToInt(vector[3]));
    this->LightDiffuse->Text = auxstr;

    vector = light.Specular;
    sprintf(auxstr, "%d, %d, %d, %d", ColorFloatToInt(vector[0]),
            ColorFloatToInt(vector[1]), ColorFloatToInt(vector[2]),
            ColorFloatToInt(vector[3]));
    this->LightSpecular->Text = auxstr;

    vector = light.Position;
    sprintf(auxstr, "%f, %f, %f, %f", vector[0], vector[1], vector[2], vector[3]);
    this->LightPosition->Text = auxstr;

    vector = light.SpotDirection;
    sprintf(auxstr, "%f, %f, %f", vector[0], vector[1], vector[2]);
    this->LightSpotDirection->Text = auxstr;

    value = light.SpotExponent;
    sprintf(auxstr, "%f", value);
    this->LightSpotExponent->Text = auxstr;

    value = light.SpotCutoff;
    sprintf(auxstr, "%f", value);
    this->LightSpotCutoff->Text = auxstr;

    vector = light.Attenuation;
    sprintf(auxstr, "%f", vector[0]);
    this->LightConstant->Text = auxstr;
    sprintf(auxstr, "%f", vector[1]);
    this->LightLinear->Text = auxstr;
    sprintf(auxstr, "%f", vector[2]);
    this->LightQuadratic->Text = auxstr;

    this->LightEnable->Text = (light.Enable ? "true" : "false");
} 
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::SaveLightingConfig (void)
{    
    this->LightingEnable = MainWnd->Lighting.GetEnable();

    GLfloat * vector = MainWnd->Lighting.GetAmbient();
    this->LightingAmbient[0] = vector[0];
    this->LightingAmbient[1] = vector[1];
    this->LightingAmbient[2] = vector[2];
    this->LightingAmbient[3] = vector[3];

    for(int i = 0; i < ANUBIS_MAX_LIGHTS; ++i)
    {
        this->Lights[i] = MainWnd->Lighting.GetLight(i);
    }
}
//***************************************************************************
// Funciones para cambir las propiedades de la luz.
//***************************************************************************
void __fastcall TConfigLightsWnd::AmbientChange (void)
{          
    GLfloat vector[4];

    if(GetRGBAFromString(this->Ambient->Text.c_str(), vector))
    {
        MainWnd->Lighting.SetAmbient(vector);
        this->SendUpdateRender();
        this->UndoString = this->Ambient->Text;
    }
    else
    {     
        this->Ambient->Text = this->UndoString;
    }
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightAmbientChange(void)
{       
    GLfloat vector[4];

    if(GetRGBAFromString(this->LightAmbient->Text.c_str(), vector))
    {
        MainWnd->Lighting.SetLightAmbient(this->GetLightIndex(), vector);
        this->SendUpdateRender();
        this->UndoString = this->LightAmbient->Text;
    }
    else
    {     
        this->LightAmbient->Text = this->UndoString;
    }
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightDiffuseChange(void)
{      
    GLfloat vector[4];

    if(GetRGBAFromString(this->LightDiffuse->Text.c_str(), vector))
    {
        MainWnd->Lighting.SetLightDiffuse(this->GetLightIndex(), vector);
        this->SendUpdateRender();
        this->UndoString = this->LightDiffuse->Text;
    }
    else
    {
        this->LightDiffuse->Text = this->UndoString;
    }
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightSpecularChange(void)
{    
    GLfloat vector[4];

    if(GetRGBAFromString(this->LightSpecular->Text.c_str(), vector))
    {
        MainWnd->Lighting.SetLightSpecular(this->GetLightIndex(), vector);
        this->SendUpdateRender();
        this->UndoString = this->LightSpecular->Text;
    }
    else
    {     
        this->LightSpecular->Text = this->UndoString;
    }
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightPositionChange(void)
{     
    GLfloat vector[4];

    if(GetVec4FromString(this->LightPosition->Text.c_str(), vector))
    {
        MainWnd->Lighting.SetLightPosition(this->GetLightIndex(), vector);
        this->SendUpdateRender();
        this->UndoString = this->LightPosition->Text;
    }
    else
    {     
        this->LightPosition->Text = this->UndoString;
    }
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightSpotDirectionChange(void)
{     
    GLfloat vector[3];

    if(GetVec3FromString(this->LightSpotDirection->Text.c_str(), vector))
    {
        MainWnd->Lighting.SetLightSpotDirection(this->GetLightIndex(), vector);
        this->SendUpdateRender();
        this->UndoString = this->LightSpotDirection->Text;
    }
    else
    {     
        this->LightSpotDirection->Text = this->UndoString;
    }
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightSpotExponentChange(void)
{  
    GLfloat value;

    if(GetFloatFromString(this->LightSpotExponent->Text.c_str(), &value))
    {
        MainWnd->Lighting.SetLightSpotExponent(this->GetLightIndex(), value);
        this->SendUpdateRender();
        this->UndoString = this->LightSpotExponent->Text;
    }
    else
    {     
        this->LightSpotExponent->Text = this->UndoString;
    }
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightSpotCutoffChange(void)
{     
    GLfloat value;

    if(GetFloatFromString(this->LightSpotCutoff->Text.c_str(), &value))
    {
        MainWnd->Lighting.SetLightSpotCutoff(this->GetLightIndex(), value);
        this->SendUpdateRender();
        this->UndoString = this->LightSpotCutoff->Text;
    }
    else
    {     
        this->LightSpotCutoff->Text = this->UndoString;
    }
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightConstantChange(void)
{          
    GLfloat value;

    if(GetFloatFromString(this->LightConstant->Text.c_str(), &value))
    {
        MainWnd->Lighting.SetLightConstantAttenuation(this->GetLightIndex(), value);
        this->SendUpdateRender();
        this->UndoString = this->LightConstant->Text;
    }
    else
    {     
        this->LightConstant->Text = this->UndoString;
    }
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightLinearChange(void)
{       
    GLfloat value;

    if(GetFloatFromString(this->LightLinear->Text.c_str(), &value))
    {
        MainWnd->Lighting.SetLightLinearAttenuation(this->GetLightIndex(), value);
        this->SendUpdateRender();
        this->UndoString = this->LightLinear->Text;
    }
    else
    {     
        this->LightLinear->Text = this->UndoString;
    }
}
//---------------------------------------------------------------------------
void __fastcall TConfigLightsWnd::LightQuadraticChange(void)
{   
    GLfloat value;

    if(GetFloatFromString(this->LightQuadratic->Text.c_str(), &value))
    {
        MainWnd->Lighting.SetLightQuadraticAttenuation(this->GetLightIndex(), value);
        this->SendUpdateRender();
        this->UndoString = this->LightQuadratic->Text;
    }
    else
    {     
        this->LightQuadratic->Text = this->UndoString;
    }
}
//***************************************************************************
// Fin ConfigLightsFuncs.cpp
//***************************************************************************