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
#ifndef PropertiesFormH
#define PropertiesFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TPropertiesWnd : public TForm
{
__published:	// IDE-managed Components
    TLabel *LblName;
    TEdit *Name;
    TGroupBox *GBTransformation;
    TLabel *LblPosition;
    TEdit *Position;
    TLabel *LblRotation;
    TEdit *Rotation;
    TLabel *LblScale;
    TEdit *Scale;
    TPageControl *ModelProperties;
    TTabSheet *TabObjects;
    TTabSheet *TabMaterials;
    TStringGrid *ObjList;
    TStringGrid *ObjVertexes;
    TComboBox *Material;
    TStringGrid *MatProperties;
    TComboBox *MatEffect;
    TButton *CmdCancel;
    TButton *CmdRestore;
    TButton *CmdApply;
    TButton *CmdAccept;
    TStringGrid *ObjFaces;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall PositionEnter(TObject *Sender);
    void __fastcall PositionExit(TObject *Sender);
    void __fastcall PositionKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall RotationEnter(TObject *Sender);
    void __fastcall RotationExit(TObject *Sender);
    void __fastcall RotationKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall ScaleEnter(TObject *Sender);
    void __fastcall ScaleExit(TObject *Sender);
    void __fastcall ScaleKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall ObjListSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
    void __fastcall MaterialChange(TObject *Sender);
    void __fastcall CmdCancelClick(TObject *Sender);
    void __fastcall CmdRestoreClick(TObject *Sender);
    void __fastcall CmdApplyClick(TObject *Sender);
    void __fastcall CmdAcceptClick(TObject *Sender);
private:	// User declarations
    AnsiString UndoString;

    int ObjIndex;
    int MatIndex;

    void __fastcall PositionChange (void);
    void __fastcall RotationChange (void);
    void __fastcall ScaleChange (void);

    void __fastcall UpdateObjectInfo (int index);
    void __fastcall UpdateMaterialInfo (int index);

public:		// User declarations
    __fastcall TPropertiesWnd(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPropertiesWnd *PropertiesWnd;
//---------------------------------------------------------------------------
#endif
//***************************************************************************
// Fin PropertiesForm.h
//***************************************************************************
