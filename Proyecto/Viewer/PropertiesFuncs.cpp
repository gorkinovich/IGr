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
//***************************************************************************
// Funciones auxiliares para lo eventos.
//***************************************************************************
void __fastcall TPropertiesWnd::PositionChange(void)
{
    GLfloat vector[3];

    if(GetVec3FromString(this->Position->Text.c_str(), vector))
    {
        this->UndoString = this->Position->Text;
    }
    else
    {
        this->Position->Text = this->UndoString;
    }
}  
//---------------------------------------------------------------------------
void __fastcall TPropertiesWnd::RotationChange(void)
{
    GLfloat vector[3];

    if(GetVec3FromString(this->Rotation->Text.c_str(), vector))
    {
        this->UndoString = this->Rotation->Text;
    }
    else
    {
        this->Rotation->Text = this->UndoString;
    }
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesWnd::ScaleChange(void)
{
    GLfloat vector[3];

    if(GetVec3FromString(this->Scale->Text.c_str(), vector))
    {
        this->UndoString = this->Scale->Text;
    }
    else
    {
        this->Scale->Text = this->UndoString;
    }
}     
//--------------------------------------------------------------------------- 
void __fastcall TPropertiesWnd::UpdateObjectInfo (int index)
{
    if(MainWnd->Model.GetObjects() == NULL) return;

    char auxstr[200];
    unsigned int i, j;
	Geometry::CObject & object = MainWnd->Model.GetObjects()[index];

    this->ObjVertexes->RowCount = object.NumVertexes + 1;

    for(i = 0; i < object.NumVertexes; ++i)
    {
        sprintf(auxstr, "%d", i);
        this->ObjVertexes->Cells[0][i + 1] = auxstr;

        sprintf(auxstr, "%f", object.Vertexes[3 * i]);
        this->ObjVertexes->Cells[1][i + 1] = auxstr;
        sprintf(auxstr, "%f", object.Vertexes[3 * i + 1]);
        this->ObjVertexes->Cells[2][i + 1] = auxstr;
        sprintf(auxstr, "%f", object.Vertexes[3 * i + 2]);
        this->ObjVertexes->Cells[3][i + 1] = auxstr;
        
        sprintf(auxstr, "%f", object.Normals[3 * i]);
        this->ObjVertexes->Cells[4][i + 1] = auxstr;
        sprintf(auxstr, "%f", object.Normals[3 * i + 1]);
        this->ObjVertexes->Cells[5][i + 1] = auxstr;
        sprintf(auxstr, "%f", object.Normals[3 * i + 2]);
        this->ObjVertexes->Cells[6][i + 1] = auxstr;

        sprintf(auxstr, "%f", object.Tangents[3 * i]);
        this->ObjVertexes->Cells[7][i + 1] = auxstr;
        sprintf(auxstr, "%f", object.Tangents[3 * i + 1]);
        this->ObjVertexes->Cells[8][i + 1] = auxstr;
        sprintf(auxstr, "%f", object.Tangents[3 * i + 2]);
        this->ObjVertexes->Cells[9][i + 1] = auxstr;

        sprintf(auxstr, "%f", object.TexCoords[2 * i]);
        this->ObjVertexes->Cells[10][i + 1] = auxstr;
        sprintf(auxstr, "%f", object.TexCoords[2 * i + 1]);
        this->ObjVertexes->Cells[11][i + 1] = auxstr;
    }
                           
    this->ObjFaces->ColCount  = 4;
    this->ObjFaces->FixedCols = 1;
    this->ObjFaces->FixedRows = 1;

    this->ObjFaces->RowCount = object.NumFaces + 1;

    for(i = 0; i < object.NumFaces; ++i)
    {        
        sprintf(auxstr, "%d", i);
        this->ObjFaces->Cells[0][i + 1] = auxstr;

        sprintf(auxstr, "%d", object.Faces[i].Material);
        this->ObjFaces->Cells[1][i + 1] = auxstr;
        sprintf(auxstr, "%d", object.Faces[i].NumIndexes);
        this->ObjFaces->Cells[2][i + 1] = auxstr;

        if(this->ObjFaces->ColCount < (int) (object.Faces[i].NumIndexes + 3))
        {
            this->ObjFaces->ColCount = object.Faces[i].NumIndexes + 3;
        }

        for(j = 0; j < object.Faces[i].NumIndexes; ++j)
        {  
            sprintf(auxstr, "%d", object.Faces[i].Indexes[j]);
            this->ObjFaces->Cells[j + 3][i + 1] = auxstr;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TPropertiesWnd::UpdateMaterialInfo (int index)
{        
    if(MainWnd->Model.GetMaterials() == NULL) return;
           
    char auxstr[200];
    unsigned int i, j;
	Geometry::CMaterial & material = MainWnd->Model.GetMaterials()[index];

    sprintf(auxstr, "%d", ColorFloatToInt(material.Ambient[0]));
    this->MatProperties->Cells[1][1] = auxstr;
    sprintf(auxstr, "%d", ColorFloatToInt(material.Ambient[1]));
    this->MatProperties->Cells[2][1] = auxstr;
    sprintf(auxstr, "%d", ColorFloatToInt(material.Ambient[2]));
    this->MatProperties->Cells[3][1] = auxstr;
    sprintf(auxstr, "%d", ColorFloatToInt(material.Ambient[3]));
    this->MatProperties->Cells[4][1] = auxstr;

                                               
    sprintf(auxstr, "%d", ColorFloatToInt(material.Diffuse[0]));
    this->MatProperties->Cells[1][2] = auxstr;
    sprintf(auxstr, "%d", ColorFloatToInt(material.Diffuse[1]));
    this->MatProperties->Cells[2][2] = auxstr;
    sprintf(auxstr, "%d", ColorFloatToInt(material.Diffuse[2]));
    this->MatProperties->Cells[3][2] = auxstr;
    sprintf(auxstr, "%d", ColorFloatToInt(material.Diffuse[3]));
    this->MatProperties->Cells[4][2] = auxstr;


    sprintf(auxstr, "%d", ColorFloatToInt(material.Specular[0]));
    this->MatProperties->Cells[1][3] = auxstr;
    sprintf(auxstr, "%d", ColorFloatToInt(material.Specular[1]));
    this->MatProperties->Cells[2][3] = auxstr;
    sprintf(auxstr, "%d", ColorFloatToInt(material.Specular[2]));
    this->MatProperties->Cells[3][3] = auxstr;
    sprintf(auxstr, "%d", ColorFloatToInt(material.Specular[3]));
    this->MatProperties->Cells[4][3] = auxstr;


    sprintf(auxstr, "%f", material.Shininess);
    this->MatProperties->Cells[1][4] = auxstr;


    sprintf(auxstr, "%d", ColorFloatToInt(material.Emission[0]));
    this->MatProperties->Cells[1][5] = auxstr;
    sprintf(auxstr, "%d", ColorFloatToInt(material.Emission[1]));
    this->MatProperties->Cells[2][5] = auxstr;
    sprintf(auxstr, "%d", ColorFloatToInt(material.Emission[2]));
    this->MatProperties->Cells[3][5] = auxstr;
    sprintf(auxstr, "%d", ColorFloatToInt(material.Emission[3]));
    this->MatProperties->Cells[4][5] = auxstr;


    sprintf(auxstr, "%d", ColorFloatToInt(material.Color[0]));
    this->MatProperties->Cells[1][6] = auxstr;
    sprintf(auxstr, "%d", ColorFloatToInt(material.Color[1]));
    this->MatProperties->Cells[2][6] = auxstr;
    sprintf(auxstr, "%d", ColorFloatToInt(material.Color[2]));
    this->MatProperties->Cells[3][6] = auxstr;
    sprintf(auxstr, "%d", ColorFloatToInt(material.Color[3]));
    this->MatProperties->Cells[4][6] = auxstr;

    
    if(material.Textured)
        this->MatProperties->Cells[1][7] = "true";
    else
        this->MatProperties->Cells[1][7] = "false";


    if(material.Texture != NULL)
        this->MatProperties->Cells[1][8] = material.Texture->GetImage()->GetName().c_str();
    else
        this->MatProperties->Cells[1][8] = "";
                                              
    if(material.NormalMap != NULL)
        this->MatProperties->Cells[1][9] = material.NormalMap->GetImage()->GetName().c_str();
    else
        this->MatProperties->Cells[1][9] = "";

    if(material.HeightMap != NULL)
        this->MatProperties->Cells[1][10] = material.HeightMap->GetImage()->GetName().c_str();
    else
        this->MatProperties->Cells[1][10] = "";

            
    sprintf(auxstr, "%f", material.ScaleBiasFactor[0]);
    this->MatProperties->Cells[1][11] = auxstr;
    sprintf(auxstr, "%f", material.ScaleBiasFactor[1]);
    this->MatProperties->Cells[2][11] = auxstr;


    switch(material.Effect)
    {
    case Geometry::ParallaxMapping:
        this->MatEffect->ItemIndex = 2;
        break;
        
    case Geometry::NormalMapping:
        this->MatEffect->ItemIndex = 1;
        break;

    default:
        this->MatEffect->ItemIndex = 0;
    }
}
//***************************************************************************
// Fin PropertiesFuncs.cpp
//***************************************************************************