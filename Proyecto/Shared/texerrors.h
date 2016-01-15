//******************************************************************************************
// Anubis Editor 1.0 - A 3D Adventure Game Engine.
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
//******************************************************************************************
#ifndef _ANUBIS_TEXERRORS_H_
#define _ANUBIS_TEXERRORS_H_
//******************************************************************************************
// Constantes.
//******************************************************************************************
#define TEXERR_UNSUPPORTED_FORMAT     2001
//------------------------------------------------------------------------------------------
#define TEXERR_LOADBMP_FOPEN          2101
#define TEXERR_LOADBMP_BADFORMAT      2102
#define TEXERR_LOADBMP_BADCOMPRESSION 2103
#define TEXERR_LOADBMP_NULLMALLOC     2104
//------------------------------------------------------------------------------------------
#define TEXERR_SAVEBMP_NULLMALLOC     2201
#define TEXERR_SAVEBMP_FOPEN          2202
//------------------------------------------------------------------------------------------
#define TEXERR_LOADTGA_FOPEN          2301
#define TEXERR_LOADTGA_BADFORMAT      2302
#define TEXERR_LOADTGA_NULLMALLOC     2303
//------------------------------------------------------------------------------------------
#define TEXERR_SAVETGA_NULLMALLOC     2401
#define TEXERR_SAVETGA_FOPEN          2402
//------------------------------------------------------------------------------------------
#define TEXERR_TEXTURE_LOAD_NULLIMAGE 2501
#define TEXERR_TEXTURE_LOAD_BADDEPTH  2502
#define TEXERR_TEXTURE_RELOAD_NULLIMG 2503
//------------------------------------------------------------------------------------------
#define TEXERR_CNTMNG_GETIMG_NULLNEW  2601
#define TEXERR_CNTMNG_GETTEX_NULLNEW  2602
//******************************************************************************************
#endif
//******************************************************************************************
// texerrors.h
//******************************************************************************************