//***************************************************************************
// Anubis Viewer 1.0 - A 3D Adventure Game Engine.
// Copyright (C) 2006-2007  Gorka Su�rez Garc�a
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
#ifndef OptionsFormH
#define OptionsFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TOptionsWnd : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
    __fastcall TOptionsWnd(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TOptionsWnd *OptionsWnd;
//---------------------------------------------------------------------------
#endif    
//***************************************************************************
// Fin OptionsForm.h
//***************************************************************************
