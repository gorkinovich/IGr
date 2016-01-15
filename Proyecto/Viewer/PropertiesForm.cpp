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
#include "PropertiesForm.h"
#include "strconv.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPropertiesWnd *PropertiesWnd;    
//***************************************************************************
// Métodos de la clase TPropertiesWnd.
//***************************************************************************
__fastcall TPropertiesWnd::TPropertiesWnd(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesWnd::FormShow(TObject *Sender)
{
    this->ObjIndex = 0;
    this->MatIndex = 0;
    this->CmdRestoreClick(Sender);    
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesWnd::PositionEnter(TObject *Sender)
{
    this->UndoString = this->Position->Text;
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesWnd::PositionExit(TObject *Sender)
{
    this->PositionChange();
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesWnd::PositionKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key == 13) this->PositionChange();
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesWnd::RotationEnter(TObject *Sender)
{
    this->UndoString = this->Rotation->Text;
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesWnd::RotationExit(TObject *Sender)
{
    this->PositionChange();
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesWnd::RotationKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key == 13) this->PositionChange();
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesWnd::ScaleEnter(TObject *Sender)
{
    this->UndoString = this->Scale->Text;
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesWnd::ScaleExit(TObject *Sender)
{
    this->ScaleChange();
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesWnd::ScaleKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key == 13) this->ScaleChange();
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesWnd::ObjListSelectCell(TObject *Sender,
      int ACol, int ARow, bool &CanSelect)
{
    this->ObjIndex = ARow - 1;
    this->UpdateObjectInfo(this->ObjIndex);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesWnd::MaterialChange(TObject *Sender)
{
    if(this->Material->ItemIndex > -1)
    {
        this->MatIndex = this->Material->ItemIndex;
    }
    else
    {
        this->MatIndex = 0;
    }

    this->UpdateMaterialInfo(this->MatIndex);
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesWnd::CmdCancelClick(TObject *Sender)
{
    this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesWnd::CmdRestoreClick(TObject *Sender)
{
    //-----------------------------------------------------------------------
    // Cargamos las propiedades globales del modelo.
    //-----------------------------------------------------------------------
    this->Name->Text = MainWnd->Model.GetName();

    char auxstr[200];
    sprintf(auxstr, "%f, %f, %f", MainWnd->Model.GetTransformation().Position[0],
            MainWnd->Model.GetTransformation().Position[1],
            MainWnd->Model.GetTransformation().Position[2]);
    this->Position->Text = auxstr;
    
    sprintf(auxstr, "%f, %f, %f", MainWnd->Model.GetTransformation().Rotation[0],
            MainWnd->Model.GetTransformation().Rotation[1],
            MainWnd->Model.GetTransformation().Rotation[2]);
    this->Rotation->Text = auxstr;
    
    sprintf(auxstr, "%f, %f, %f", MainWnd->Model.GetTransformation().Scale[0],
            MainWnd->Model.GetTransformation().Scale[1],
            MainWnd->Model.GetTransformation().Scale[2]);
    this->Scale->Text = auxstr;

       
    //-----------------------------------------------------------------------
    // Configuramos las tablas de datos de los objetos.
    //-----------------------------------------------------------------------
    this->ObjList->ColCount  = 14;
    this->ObjList->RowCount  =  2;
    this->ObjList->FixedCols =  1;
    this->ObjList->FixedRows =  1;

    this->ObjList->Cols[1]->SetText("Name");
    this->ObjList->Cols[2]->SetText("Position X");
    this->ObjList->Cols[3]->SetText("Position Y");
    this->ObjList->Cols[4]->SetText("Position Z");
    this->ObjList->Cols[5]->SetText("Rotation X");
    this->ObjList->Cols[6]->SetText("Rotation Y");
    this->ObjList->Cols[7]->SetText("Rotation Z");
    this->ObjList->Cols[8]->SetText("Scale X");
    this->ObjList->Cols[9]->SetText("Scale Y");
    this->ObjList->Cols[10]->SetText("Scale Z");
    this->ObjList->Cols[11]->SetText("Textured");
    this->ObjList->Cols[12]->SetText("Num. Vertexes");
    this->ObjList->Cols[13]->SetText("Num. Faces");
         
    this->ObjList->ColWidths[1]  = 100;
    this->ObjList->ColWidths[2]  = 80;
    this->ObjList->ColWidths[3]  = 80;
    this->ObjList->ColWidths[4]  = 80;
    this->ObjList->ColWidths[5]  = 80;
    this->ObjList->ColWidths[6]  = 80;
    this->ObjList->ColWidths[7]  = 80;
    this->ObjList->ColWidths[8]  = 80;
    this->ObjList->ColWidths[9]  = 80;
    this->ObjList->ColWidths[10] = 80;
    this->ObjList->ColWidths[11] = 80;
    this->ObjList->ColWidths[12] = 80;
    this->ObjList->ColWidths[13] = 80;


    this->ObjVertexes->ColCount  = 12;
    this->ObjVertexes->RowCount  =  2;
    this->ObjVertexes->FixedCols =  1;
    this->ObjVertexes->FixedRows =  1;

    this->ObjVertexes->Cols[1]->SetText("Vertex X");
    this->ObjVertexes->Cols[2]->SetText("Vertex Y");
    this->ObjVertexes->Cols[3]->SetText("Vertex Z");
    this->ObjVertexes->Cols[4]->SetText("Normal X");
    this->ObjVertexes->Cols[5]->SetText("Normal Y");
    this->ObjVertexes->Cols[6]->SetText("Normal Z");
    this->ObjVertexes->Cols[7]->SetText("Tangent X");
    this->ObjVertexes->Cols[8]->SetText("Tangent Y");
    this->ObjVertexes->Cols[9]->SetText("Tangent Z");
    this->ObjVertexes->Cols[10]->SetText("Tex. Coord. U");
    this->ObjVertexes->Cols[11]->SetText("Tex. Coord. V");

    this->ObjVertexes->ColWidths[1]  = 80;
    this->ObjVertexes->ColWidths[2]  = 80;
    this->ObjVertexes->ColWidths[3]  = 80;
    this->ObjVertexes->ColWidths[4]  = 80;
    this->ObjVertexes->ColWidths[5]  = 80;
    this->ObjVertexes->ColWidths[6]  = 80;
    this->ObjVertexes->ColWidths[7]  = 80;
    this->ObjVertexes->ColWidths[8]  = 80;
    this->ObjVertexes->ColWidths[9]  = 80;
    this->ObjVertexes->ColWidths[10] = 80;
    this->ObjVertexes->ColWidths[11] = 80;


    this->ObjFaces->ColCount  = 4;
    this->ObjFaces->RowCount  = 2;
    this->ObjFaces->FixedCols = 1;
    this->ObjFaces->FixedRows = 1;

    this->ObjFaces->Cols[1]->SetText("Material");
    this->ObjFaces->Cols[2]->SetText("Num. Indexes");
    this->ObjFaces->Cols[3]->SetText("Indexes");

    this->ObjFaces->ColWidths[1]  = 80;
    this->ObjFaces->ColWidths[2]  = 80;
    this->ObjFaces->ColWidths[3]  = 64;

       
    //-----------------------------------------------------------------------
    // Cargamos los datos de los objetos.
    //-----------------------------------------------------------------------
    unsigned int i;
	Geometry::CObject   * objects   = MainWnd->Model.GetObjects();
	Geometry::CMaterial * materials = MainWnd->Model.GetMaterials();

    if(objects != NULL)
    {
        this->ObjList->RowCount = MainWnd->Model.GetNumObjects() + 1;
        for(i = 0; i < MainWnd->Model.GetNumObjects(); ++i)
        {
            sprintf(auxstr, "%d", i);
            this->ObjList->Cells[0][i + 1] = auxstr;
            this->ObjList->Cells[1][i + 1] = objects[i].Name;

            sprintf(auxstr, "%f", objects[i].Transformation.Position[0]);
            this->ObjList->Cells[2][i + 1] = auxstr;
            sprintf(auxstr, "%f", objects[i].Transformation.Position[1]);
            this->ObjList->Cells[3][i + 1] = auxstr;
            sprintf(auxstr, "%f", objects[i].Transformation.Position[2]);
            this->ObjList->Cells[4][i + 1] = auxstr;
            
            sprintf(auxstr, "%f", objects[i].Transformation.Rotation[0]);
            this->ObjList->Cells[5][i + 1] = auxstr;
            sprintf(auxstr, "%f", objects[i].Transformation.Rotation[1]);
            this->ObjList->Cells[6][i + 1] = auxstr;
            sprintf(auxstr, "%f", objects[i].Transformation.Rotation[2]);
            this->ObjList->Cells[7][i + 1] = auxstr;

            sprintf(auxstr, "%f", objects[i].Transformation.Scale[0]);
            this->ObjList->Cells[8][i + 1] = auxstr;
            sprintf(auxstr, "%f", objects[i].Transformation.Scale[1]);
            this->ObjList->Cells[9][i + 1] = auxstr;
            sprintf(auxstr, "%f", objects[i].Transformation.Scale[2]);
            this->ObjList->Cells[10][i + 1] = auxstr;

            if(objects[i].Textured)
            {
                this->ObjList->Cells[11][i + 1] = "true";
            }
            else
            {
                this->ObjList->Cells[11][i + 1] = "false";
            }

            sprintf(auxstr, "%d", objects[i].NumVertexes);
            this->ObjList->Cells[12][i + 1] = auxstr;
            sprintf(auxstr, "%d", objects[i].NumFaces);
            this->ObjList->Cells[13][i + 1] = auxstr;
        }

        this->UpdateObjectInfo(this->ObjIndex);
    }

       
    //-----------------------------------------------------------------------
    // Configuramos las tablas de datos de los materiales.
    //-----------------------------------------------------------------------
    this->MatProperties->ColCount  =  5;
    this->MatProperties->RowCount  = 12;
    this->MatProperties->FixedCols =  1;
    this->MatProperties->FixedRows =  1;

    this->MatProperties->Cols[1]->SetText("R / Value");
    this->MatProperties->Cols[2]->SetText("G");
    this->MatProperties->Cols[3]->SetText("B");
    this->MatProperties->Cols[4]->SetText("A");
                                               
    this->MatProperties->Rows[1]->SetText("Ambient");
    this->MatProperties->Rows[2]->SetText("Diffuse");
    this->MatProperties->Rows[3]->SetText("Specular");
    this->MatProperties->Rows[4]->SetText("Shininess");
    this->MatProperties->Rows[5]->SetText("Emission");
    this->MatProperties->Rows[6]->SetText("Color");
    this->MatProperties->Rows[7]->SetText("Textured");
    this->MatProperties->Rows[8]->SetText("Texture");
    this->MatProperties->Rows[9]->SetText("Normal Map");
    this->MatProperties->Rows[10]->SetText("Height Map");
    this->MatProperties->Rows[11]->SetText("Scale/Bias");
    
              
    //-----------------------------------------------------------------------
    // Cargamos los datos de los materiales.
    //-----------------------------------------------------------------------
    if(materials != NULL)
    {
        this->Material->Items->Clear();

        for(i = 0; i < MainWnd->Model.GetNumMaterials(); ++i)
        {      
            this->Material->Items->Add(materials[i].Name);
        }

        this->Material->ItemIndex = 0;
        this->MatIndex = 0;
               
        this->UpdateMaterialInfo(this->MatIndex);
    }
    else
    {
        this->Material->Items->Clear();
    }
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesWnd::CmdApplyClick(TObject *Sender)
{        
    //-----------------------------------------------------------------------
    // Salvamos las propiedades globales del modelo.
    //-----------------------------------------------------------------------
    MainWnd->OpenGL->MakeOpenGLPanelCurrent();

    MainWnd->Model.SetName(this->Name->Text.c_str());
    
    GLfloat vector[3];
    Geometry::CTransformation transformation;

    if(GetVec3FromString(this->Position->Text.c_str(), vector))
    {
        transformation.Position[0] = vector[0];
        transformation.Position[1] = vector[1];
        transformation.Position[2] = vector[2];
    }
    
    if(GetVec3FromString(this->Rotation->Text.c_str(), vector))
    {
        transformation.Rotation[0] = vector[0];
        transformation.Rotation[1] = vector[1];
        transformation.Rotation[2] = vector[2];
    }
    
    if(GetVec3FromString(this->Scale->Text.c_str(), vector))
    {
        transformation.Scale[0] = vector[0];
        transformation.Scale[1] = vector[1];
        transformation.Scale[2] = vector[2];
    }

    MainWnd->Model.SetMatrix(transformation);

        
    //-----------------------------------------------------------------------
    // Salvamos el material actual seleccionado.
    //-----------------------------------------------------------------------  
    GLfloat value;
	Geometry::CMaterial & material = MainWnd->Model.GetMaterials()[this->MatIndex];


    if(GetColorFromString(this->MatProperties->Cells[1][1].c_str(), &value))
        material.Ambient[0] = value;
    if(GetColorFromString(this->MatProperties->Cells[2][1].c_str(), &value))
        material.Ambient[1] = value;
    if(GetColorFromString(this->MatProperties->Cells[3][1].c_str(), &value))
        material.Ambient[2] = value;
    if(GetColorFromString(this->MatProperties->Cells[4][1].c_str(), &value))
        material.Ambient[3] = value;


    if(GetColorFromString(this->MatProperties->Cells[1][2].c_str(), &value))
        material.Diffuse[0] = value;
    if(GetColorFromString(this->MatProperties->Cells[2][2].c_str(), &value))
        material.Diffuse[1] = value;
    if(GetColorFromString(this->MatProperties->Cells[3][2].c_str(), &value))
        material.Diffuse[2] = value;
    if(GetColorFromString(this->MatProperties->Cells[4][2].c_str(), &value))
        material.Diffuse[3] = value;


    if(GetColorFromString(this->MatProperties->Cells[1][3].c_str(), &value))
        material.Specular[0] = value;
    if(GetColorFromString(this->MatProperties->Cells[2][3].c_str(), &value))
        material.Specular[1] = value;
    if(GetColorFromString(this->MatProperties->Cells[3][3].c_str(), &value))
        material.Specular[2] = value;
    if(GetColorFromString(this->MatProperties->Cells[4][3].c_str(), &value))
        material.Specular[3] = value;


    if(GetFloatFromString(this->MatProperties->Cells[1][4].c_str(), &value))
        material.Shininess = value;


    if(GetColorFromString(this->MatProperties->Cells[1][5].c_str(), &value))
        material.Emission[0] = value;
    if(GetColorFromString(this->MatProperties->Cells[2][5].c_str(), &value))
        material.Emission[1] = value;
    if(GetColorFromString(this->MatProperties->Cells[3][5].c_str(), &value))
        material.Emission[2] = value;
    if(GetColorFromString(this->MatProperties->Cells[4][5].c_str(), &value))
        material.Emission[3] = value;


    if(GetColorFromString(this->MatProperties->Cells[1][6].c_str(), &value))
        material.Color[0] = value;
    if(GetColorFromString(this->MatProperties->Cells[2][6].c_str(), &value))
        material.Color[1] = value;
    if(GetColorFromString(this->MatProperties->Cells[3][6].c_str(), &value))
        material.Color[2] = value;
    if(GetColorFromString(this->MatProperties->Cells[4][6].c_str(), &value))
        material.Color[3] = value;


    material.Textured = (this->MatProperties->Cells[1][7] == "true");
    if(!material.Textured) this->MatProperties->Cells[1][7] = "false";


    CContentManager * content = CContentManager::GetInstance();
    if(this->MatProperties->Cells[1][8] != "")
    {
        material.Texture = content->GetTexture(this->MatProperties->Cells[1][8].c_str());
        if(material.Texture == NULL)
        {
            this->MatProperties->Cells[1][8] = "";
        }
    }

    if(this->MatProperties->Cells[1][9] != "")
    {
        material.NormalMap = content->GetTexture(this->MatProperties->Cells[1][9].c_str());
        if(material.NormalMap == NULL)
        {
            this->MatProperties->Cells[1][9] = "";
        }
    }

    if(this->MatProperties->Cells[1][10] != "")
    {
        material.HeightMap = content->GetTexture(this->MatProperties->Cells[1][10].c_str());
        if(material.HeightMap == NULL)
        {
            this->MatProperties->Cells[1][10] = "";
        }
    }


    if(GetFloatFromString(this->MatProperties->Cells[1][11].c_str(), &value))
        material.ScaleBiasFactor[0] = value;
    if(GetFloatFromString(this->MatProperties->Cells[2][11].c_str(), &value))
        material.ScaleBiasFactor[1] = value;


    switch(this->MatEffect->ItemIndex)
    {
    case 2:
        material.Effect = Geometry::ParallaxMapping;
        break;

    case 1:
        material.Effect = Geometry::NormalMapping;
        break;

    default:        
        material.Effect = Geometry::NoneEffect;
    }
    

    MainWnd->OpenGL->Repaint();
    MainWnd->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesWnd::CmdAcceptClick(TObject *Sender)
{
    this->CmdApplyClick(Sender);
    this->Close();
}
//***************************************************************************
// Fin PropertiesForm.cpp
//***************************************************************************
