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
#pragma link "opengl32.lib"
#pragma link "glu32.lib"
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("AnubisViewer.res");
USEFORM("Viewer\MainForm.cpp", MainWnd);
USEUNIT("Shared\extensions.cpp");
USEUNIT("Shared\textures.cpp");
USEUNIT("Shared\error.cpp");
USEUNIT("Shared\3dmath.cpp");
USEUNIT("Shared\content.cpp");
USEUNIT("Shared\3ds\Model_3DS.cpp");
USEFORM("Viewer\PropertiesForm.cpp", PropertiesWnd);
USEFORM("Viewer\ConfigLightsForm.cpp", ConfigLightsWnd);
USEFORM("Viewer\OptionsForm.cpp", OptionsWnd);
USEFORM("Viewer\AboutForm.cpp", AboutWnd);
USEUNIT("Shared\geometry.cpp");
USEUNIT("Shared\shaders.cpp");
USEUNIT("Shared\lighting.cpp");
USEUNIT("Shared\strconv.cpp");
USEUNIT("Viewer\ConfigLightsFuncs.cpp");
USEUNIT("Shared\3dobjects.cpp");
USEUNIT("Shared\3dtransf.cpp");
USEUNIT("Shared\3dfaces.cpp");
USEUNIT("Shared\3dmaterial.cpp");
USEUNIT("Shared\3dobject.cpp");
USEUNIT("Viewer\PropertiesFuncs.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->CreateForm(__classid(TMainWnd), &MainWnd);
         Application->CreateForm(__classid(TPropertiesWnd), &PropertiesWnd);
         Application->CreateForm(__classid(TConfigLightsWnd), &ConfigLightsWnd);
         Application->CreateForm(__classid(TOptionsWnd), &OptionsWnd);
         Application->CreateForm(__classid(TAboutWnd), &AboutWnd);
         Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    return 0;
}
//***************************************************************************
// AnubisViewer.cpp   
//***************************************************************************
