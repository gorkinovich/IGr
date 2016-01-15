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
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
//------------------------------------------------------------------------------------------
#include <gl/gl.h>
#include <gl/glu.h>
//------------------------------------------------------------------------------------------
#include "gl/glext.h"
#include "error.h"
#include "exterrors.h"
//******************************************************************************************
// Funciones para saber si está activa una extensión.
//******************************************************************************************
bool extMultitexture;
bool extVertexShaders;
bool extFragmentShaders;
//------------------------------------------------------------------------------------------
bool extIsMultitexture (void)
{
	return extMultitexture;
}
//------------------------------------------------------------------------------------------
bool extIsVertexShaders (void)
{
	return extVertexShaders;
}
//------------------------------------------------------------------------------------------
bool extIsFragmentShaders (void)
{
	return extFragmentShaders;
}
//******************************************************************************************
// Funciones para la multitextura (GL_ARB_multitexture).
//******************************************************************************************
PFNGLACTIVETEXTUREARBPROC       glActiveTextureARB       = NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB = NULL;

PFNGLMULTITEXCOORD1DARBPROC     glMultiTexCoord1dARB  = NULL;
PFNGLMULTITEXCOORD1FARBPROC     glMultiTexCoord1fARB  = NULL;
PFNGLMULTITEXCOORD1IARBPROC     glMultiTexCoord1iARB  = NULL;
PFNGLMULTITEXCOORD1SARBPROC     glMultiTexCoord1sARB  = NULL;
PFNGLMULTITEXCOORD1DVARBPROC    glMultiTexCoord1dvARB = NULL;
PFNGLMULTITEXCOORD1FVARBPROC    glMultiTexCoord1fvARB = NULL;
PFNGLMULTITEXCOORD1IVARBPROC    glMultiTexCoord1ivARB = NULL;
PFNGLMULTITEXCOORD1SVARBPROC    glMultiTexCoord1svARB = NULL;

PFNGLMULTITEXCOORD2DARBPROC     glMultiTexCoord2dARB  = NULL;
PFNGLMULTITEXCOORD2FARBPROC     glMultiTexCoord2fARB  = NULL;
PFNGLMULTITEXCOORD2IARBPROC     glMultiTexCoord2iARB  = NULL;
PFNGLMULTITEXCOORD2SARBPROC     glMultiTexCoord2sARB  = NULL;
PFNGLMULTITEXCOORD2DVARBPROC    glMultiTexCoord2dvARB = NULL;
PFNGLMULTITEXCOORD2FVARBPROC    glMultiTexCoord2fvARB = NULL;
PFNGLMULTITEXCOORD2IVARBPROC    glMultiTexCoord2ivARB = NULL;
PFNGLMULTITEXCOORD2SVARBPROC    glMultiTexCoord2svARB = NULL;

PFNGLMULTITEXCOORD3DARBPROC     glMultiTexCoord3dARB  = NULL;
PFNGLMULTITEXCOORD3FARBPROC     glMultiTexCoord3fARB  = NULL;
PFNGLMULTITEXCOORD3IARBPROC     glMultiTexCoord3iARB  = NULL;
PFNGLMULTITEXCOORD3SARBPROC     glMultiTexCoord3sARB  = NULL;
PFNGLMULTITEXCOORD3DVARBPROC    glMultiTexCoord3dvARB = NULL;
PFNGLMULTITEXCOORD3FVARBPROC    glMultiTexCoord3fvARB = NULL;
PFNGLMULTITEXCOORD3IVARBPROC    glMultiTexCoord3ivARB = NULL;
PFNGLMULTITEXCOORD3SVARBPROC    glMultiTexCoord3svARB = NULL;

PFNGLMULTITEXCOORD4DARBPROC     glMultiTexCoord4dARB  = NULL;
PFNGLMULTITEXCOORD4FARBPROC     glMultiTexCoord4fARB  = NULL;
PFNGLMULTITEXCOORD4IARBPROC     glMultiTexCoord4iARB  = NULL;
PFNGLMULTITEXCOORD4SARBPROC     glMultiTexCoord4sARB  = NULL;
PFNGLMULTITEXCOORD4DVARBPROC    glMultiTexCoord4dvARB = NULL;
PFNGLMULTITEXCOORD4FVARBPROC    glMultiTexCoord4fvARB = NULL;
PFNGLMULTITEXCOORD4IVARBPROC    glMultiTexCoord4ivARB = NULL;
PFNGLMULTITEXCOORD4SVARBPROC    glMultiTexCoord4svARB = NULL;
//------------------------------------------------------------------------------------------
bool extLoadMultitexture (char * extensions)
{
	//--------------------------------------------------------------------------------------
	// Comprobamos que esté la extensión para el multitexturizado.
	//--------------------------------------------------------------------------------------
	if(strstr(extensions, "GL_ARB_multitexture") == NULL)
	{
		extMultitexture = false;
		return appSetLastError(EXTERR_MULTITEXTURE);
	}
	else
	{
		extMultitexture = true;
	}

	//--------------------------------------------------------------------------------------
	// void glActiveTextureARB (GLenum texture);
	//--------------------------------------------------------------------------------------
	glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)
						 wglGetProcAddress("glActiveTextureARB");

    if(glActiveTextureARB == NULL)
		return appSetLastError(EXTERR_GLACTIVETEXTUREARB);

	//--------------------------------------------------------------------------------------
	// void glClientActiveTextureARB (GLenum texture);
	//--------------------------------------------------------------------------------------
	glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)
							   wglGetProcAddress("glClientActiveTextureARB");
	
	if(glClientActiveTextureARB == NULL)
		return appSetLastError(EXTERR_GLCLIENTACTIVETEXTUREARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord1dARB (GLenum target, GLdouble s);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord1dARB = (PFNGLMULTITEXCOORD1DARBPROC)
						   wglGetProcAddress("glMultiTexCoord1dARB");
	
	if(glMultiTexCoord1dARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD1DARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord1fARB (GLenum target, GLfloat s);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord1fARB = (PFNGLMULTITEXCOORD1FARBPROC)
						   wglGetProcAddress("glMultiTexCoord1fARB");
	
	if(glMultiTexCoord1fARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD1FARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord1iARB (GLenum target, GLint s);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord1iARB = (PFNGLMULTITEXCOORD1IARBPROC)
						   wglGetProcAddress("glMultiTexCoord1iARB");
	
	if(glMultiTexCoord1iARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD1IARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord1sARB (GLenum target, GLshort s);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord1sARB = (PFNGLMULTITEXCOORD1SARBPROC)
						   wglGetProcAddress("glMultiTexCoord1sARB");
	
	if(glMultiTexCoord1sARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD1SARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord1dvARB (GLenum target, const GLdouble * v);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord1dvARB = (PFNGLMULTITEXCOORD1DVARBPROC)
							wglGetProcAddress("glMultiTexCoord1dvARB");
	
	if(glMultiTexCoord1dvARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD1DVARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord1fvARB (GLenum target, const GLfloat * v);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord1fvARB = (PFNGLMULTITEXCOORD1FVARBPROC)
							wglGetProcAddress("glMultiTexCoord1fvARB");
	
	if(glMultiTexCoord1fvARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD1FVARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord1ivARB (GLenum target, const GLint * v);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord1ivARB = (PFNGLMULTITEXCOORD1IVARBPROC)
							wglGetProcAddress("glMultiTexCoord1ivARB");
	
	if(glMultiTexCoord1ivARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD1IVARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord1svARB (GLenum target, const GLshort * v);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord1svARB = (PFNGLMULTITEXCOORD1SVARBPROC)
							wglGetProcAddress("glMultiTexCoord1svARB");
	
	if(glMultiTexCoord1svARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD1SVARB);
	
	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord2dARB (GLenum target, GLdouble s, GLdouble t);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord2dARB = (PFNGLMULTITEXCOORD2DARBPROC)
						   wglGetProcAddress("glMultiTexCoord2dARB");
	
	if(glMultiTexCoord2dARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD2DARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord2fARB (GLenum target, GLfloat s, GLfloat t);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)
						   wglGetProcAddress("glMultiTexCoord2fARB");
	
	if(glMultiTexCoord2fARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD2FARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord2iARB (GLenum target, GLint s, GLint t);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord2iARB = (PFNGLMULTITEXCOORD2IARBPROC)
						   wglGetProcAddress("glMultiTexCoord2iARB");
	
	if(glMultiTexCoord2iARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD2IARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord2sARB (GLenum target, GLshort s, GLshort t);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord2sARB = (PFNGLMULTITEXCOORD2SARBPROC)
						   wglGetProcAddress("glMultiTexCoord2sARB");
	
	if(glMultiTexCoord2sARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD2SARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord2dvARB (GLenum target, const GLdouble * v);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord2dvARB = (PFNGLMULTITEXCOORD2DVARBPROC)
							wglGetProcAddress("glMultiTexCoord2dvARB");
	
	if(glMultiTexCoord2dvARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD2DVARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord2fvARB (GLenum target, const GLfloat * v);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord2fvARB = (PFNGLMULTITEXCOORD2FVARBPROC)
							wglGetProcAddress("glMultiTexCoord2fvARB");
	
	if(glMultiTexCoord2fvARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD2FVARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord2ivARB (GLenum target, const GLint * v);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord2ivARB = (PFNGLMULTITEXCOORD2IVARBPROC)
							wglGetProcAddress("glMultiTexCoord2ivARB");
	
	if(glMultiTexCoord2ivARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD2IVARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord2svARB (GLenum target, const GLshort * v);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord2svARB = (PFNGLMULTITEXCOORD2SVARBPROC)
							wglGetProcAddress("glMultiTexCoord2svARB");
	
	if(glMultiTexCoord2svARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD2SVARB);
	
	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord3dARB (GLenum target, GLdouble s, GLdouble t, GLdouble r);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord3dARB = (PFNGLMULTITEXCOORD3DARBPROC)
						   wglGetProcAddress("glMultiTexCoord3dARB");
	
	if(glMultiTexCoord3dARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD3DARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord3fARB (GLenum target, GLfloat s, GLfloat t, GLfloat r);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord3fARB = (PFNGLMULTITEXCOORD3FARBPROC)
						   wglGetProcAddress("glMultiTexCoord3fARB");
	
	if(glMultiTexCoord3fARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD3FARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord3iARB (GLenum target, GLint s, GLint t, GLint r);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord3iARB = (PFNGLMULTITEXCOORD3IARBPROC)
						   wglGetProcAddress("glMultiTexCoord3iARB");
	
	if(glMultiTexCoord3iARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD3IARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord3sARB (GLenum target, GLshort s, GLshort t, GLshort r);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord3sARB = (PFNGLMULTITEXCOORD3SARBPROC)
						   wglGetProcAddress("glMultiTexCoord3sARB");
	
	if(glMultiTexCoord3sARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD3SARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord3dvARB (GLenum target, const GLdouble * v);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord3dvARB = (PFNGLMULTITEXCOORD3DVARBPROC)
							wglGetProcAddress("glMultiTexCoord3dvARB");
	
	if(glMultiTexCoord3dvARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD3DVARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord3fvARB (GLenum target, const GLfloat * v);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord3fvARB = (PFNGLMULTITEXCOORD3FVARBPROC)
							wglGetProcAddress("glMultiTexCoord3fvARB");
	
	if(glMultiTexCoord3fvARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD3FVARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord3ivARB (GLenum target, const GLint * v);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord3ivARB = (PFNGLMULTITEXCOORD3IVARBPROC)
							wglGetProcAddress("glMultiTexCoord3ivARB");
	
	if(glMultiTexCoord3ivARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD3IVARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord3svARB (GLenum target, const GLshort * v);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord3svARB = (PFNGLMULTITEXCOORD3SVARBPROC)
							wglGetProcAddress("glMultiTexCoord3svARB");
	
	if(glMultiTexCoord3svARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD3SVARB);
	
	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord4dARB (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord4dARB = (PFNGLMULTITEXCOORD4DARBPROC)
						   wglGetProcAddress("glMultiTexCoord4dARB");
	
	if(glMultiTexCoord4dARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD4DARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord4fARB (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord4fARB = (PFNGLMULTITEXCOORD4FARBPROC)
						   wglGetProcAddress("glMultiTexCoord4fARB");
	
	if(glMultiTexCoord4fARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD4FARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord4iARB (GLenum target, GLint s, GLint t, GLint r, GLint q);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord4iARB = (PFNGLMULTITEXCOORD4IARBPROC)
						   wglGetProcAddress("glMultiTexCoord4iARB");
	
	if(glMultiTexCoord4iARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD4IARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord4sARB (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord4sARB = (PFNGLMULTITEXCOORD4SARBPROC)
						   wglGetProcAddress("glMultiTexCoord4sARB");
	
	if(glMultiTexCoord4sARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD4SARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord4dvARB (GLenum target, const GLdouble * v);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord4dvARB = (PFNGLMULTITEXCOORD4DVARBPROC)
							wglGetProcAddress("glMultiTexCoord4dvARB");
	
	if(glMultiTexCoord4dvARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD4DVARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord4fvARB (GLenum target, const GLfloat * v);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord4fvARB = (PFNGLMULTITEXCOORD4FVARBPROC)
							wglGetProcAddress("glMultiTexCoord4fvARB");
	
	if(glMultiTexCoord4fvARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD4FVARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord4ivARB (GLenum target, const GLint * v);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord4ivARB = (PFNGLMULTITEXCOORD4IVARBPROC)
							wglGetProcAddress("glMultiTexCoord4ivARB");
	
	if(glMultiTexCoord4ivARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD4IVARB);

	//--------------------------------------------------------------------------------------
	// void glMultiTexCoord4svARB (GLenum target, const GLshort * v);
	//--------------------------------------------------------------------------------------
	glMultiTexCoord4svARB = (PFNGLMULTITEXCOORD4SVARBPROC)
							wglGetProcAddress("glMultiTexCoord4svARB");
	
	if(glMultiTexCoord4svARB == NULL)
		return appSetLastError(EXTERR_GLMULTITEXCOORD4SVARB);

	//--------------------------------------------------------------------------------------
	// Si se han cargado todas las funciones devolvemos true.
	//--------------------------------------------------------------------------------------
	return true;
}
//------------------------------------------------------------------------------------------
int extMultitextureGetMaxTexUnits (void)
{
	int maxTexUnits;
	glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB, &maxTexUnits);

	return maxTexUnits;
}
//******************************************************************************************
// Funciones para los vertex shaders ().
// Funciones para los fragment shaders (GL_ARB_fragment_shader).
//******************************************************************************************
PFNGLCREATEPROGRAMOBJECTARBPROC  glCreateProgramObjectARB = NULL;

PFNGLCREATESHADEROBJECTARBPROC   glCreateShaderObjectARB = NULL;
PFNGLSHADERSOURCEARBPROC         glShaderSourceARB       = NULL;
PFNGLCOMPILESHADERARBPROC        glCompileShaderARB      = NULL;

PFNGLATTACHOBJECTARBPROC         glAttachObjectARB     = NULL;
PFNGLLINKPROGRAMARBPROC          glLinkProgramARB      = NULL;
PFNGLUSEPROGRAMOBJECTARBPROC     glUseProgramObjectARB = NULL;

PFNGLGETOBJECTPARAMETERFVARBPROC glGetObjectParameterfvARB = NULL;
PFNGLGETOBJECTPARAMETERIVARBPROC glGetObjectParameterivARB = NULL;
PFNGLGETINFOLOGARBPROC           glGetInfoLogARB           = NULL;

PFNGLDETACHOBJECTARBPROC         glDetachObjectARB = NULL;
PFNGLDELETEOBJECTARBPROC         glDeleteObjectARB = NULL;

PFNGLGETHANDLEARBPROC            glGetHandleARB          = NULL;
PFNGLVALIDATEPROGRAMARBPROC      glValidateProgramARB    = NULL;
PFNGLGETATTACHEDOBJECTSARBPROC   glGetAttachedObjectsARB = NULL;
PFNGLGETSHADERSOURCEARBPROC      glGetShaderSourceARB    = NULL;
//------------------------------------------------------------------------------------------
PFNGLGETUNIFORMLOCATIONARBPROC   glGetUniformLocationARB = NULL;
PFNGLGETACTIVEUNIFORMARBPROC     glGetActiveUniformARB   = NULL;
PFNGLGETUNIFORMFVARBPROC         glGetUniformfvARB       = NULL;
PFNGLGETUNIFORMIVARBPROC         glGetUniformivARB       = NULL;

PFNGLUNIFORM1FARBPROC            glUniform1fARB  = NULL;
PFNGLUNIFORM1IARBPROC            glUniform1iARB  = NULL;
PFNGLUNIFORM1FVARBPROC           glUniform1fvARB = NULL;
PFNGLUNIFORM1IVARBPROC           glUniform1ivARB = NULL;

PFNGLUNIFORM2FARBPROC            glUniform2fARB  = NULL;
PFNGLUNIFORM2IARBPROC            glUniform2iARB  = NULL;
PFNGLUNIFORM2FVARBPROC           glUniform2fvARB = NULL;
PFNGLUNIFORM2IVARBPROC           glUniform2ivARB = NULL;

PFNGLUNIFORM3FARBPROC            glUniform3fARB  = NULL;
PFNGLUNIFORM3IARBPROC            glUniform3iARB  = NULL;
PFNGLUNIFORM3FVARBPROC           glUniform3fvARB = NULL;
PFNGLUNIFORM3IVARBPROC           glUniform3ivARB = NULL;

PFNGLUNIFORM4FARBPROC            glUniform4fARB  = NULL;
PFNGLUNIFORM4IARBPROC            glUniform4iARB  = NULL;
PFNGLUNIFORM4FVARBPROC           glUniform4fvARB = NULL;
PFNGLUNIFORM4IVARBPROC           glUniform4ivARB = NULL;

PFNGLUNIFORMMATRIX2FVARBPROC     glUniformMatrix2fvARB = NULL;
PFNGLUNIFORMMATRIX3FVARBPROC     glUniformMatrix3fvARB = NULL;
PFNGLUNIFORMMATRIX4FVARBPROC     glUniformMatrix4fvARB = NULL;
//------------------------------------------------------------------------------------------
PFNGLGETATTRIBLOCATIONARBPROC          glGetAttribLocationARB  = NULL;
PFNGLBINDATTRIBLOCATIONARBPROC         glBindAttribLocationARB = NULL;
PFNGLGETACTIVEATTRIBARBPROC            glGetActiveAttribARB    = NULL;

PFNGLENABLEVERTEXATTRIBARRAYARBPROC    glEnableVertexAttribArrayARB  = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYARBPROC   glDisableVertexAttribArrayARB = NULL;
PFNGLVERTEXATTRIBPOINTERARBPROC        glVertexAttribPointerARB      = NULL;

PFNGLVERTEXATTRIB1DARBPROC             glVertexAttrib1dARB  = NULL;
PFNGLVERTEXATTRIB1FARBPROC             glVertexAttrib1fARB  = NULL;
PFNGLVERTEXATTRIB1SARBPROC             glVertexAttrib1sARB  = NULL;
PFNGLVERTEXATTRIB1DVARBPROC            glVertexAttrib1dvARB = NULL;
PFNGLVERTEXATTRIB1FVARBPROC            glVertexAttrib1fvARB = NULL;
PFNGLVERTEXATTRIB1SVARBPROC            glVertexAttrib1svARB = NULL;

PFNGLVERTEXATTRIB2DARBPROC             glVertexAttrib2dARB  = NULL;
PFNGLVERTEXATTRIB2FARBPROC             glVertexAttrib2fARB  = NULL;
PFNGLVERTEXATTRIB2SARBPROC             glVertexAttrib2sARB  = NULL;
PFNGLVERTEXATTRIB2DVARBPROC            glVertexAttrib2dvARB = NULL;
PFNGLVERTEXATTRIB2FVARBPROC            glVertexAttrib2fvARB = NULL;
PFNGLVERTEXATTRIB2SVARBPROC            glVertexAttrib2svARB = NULL;

PFNGLVERTEXATTRIB3DARBPROC             glVertexAttrib3dARB  = NULL;
PFNGLVERTEXATTRIB3FARBPROC             glVertexAttrib3fARB  = NULL;
PFNGLVERTEXATTRIB3SARBPROC             glVertexAttrib3sARB  = NULL;
PFNGLVERTEXATTRIB3DVARBPROC            glVertexAttrib3dvARB = NULL;
PFNGLVERTEXATTRIB3FVARBPROC            glVertexAttrib3fvARB = NULL;
PFNGLVERTEXATTRIB3SVARBPROC            glVertexAttrib3svARB = NULL;

PFNGLVERTEXATTRIB4DARBPROC             glVertexAttrib4dARB  = NULL;
PFNGLVERTEXATTRIB4FARBPROC             glVertexAttrib4fARB  = NULL;
PFNGLVERTEXATTRIB4SARBPROC             glVertexAttrib4sARB  = NULL;
PFNGLVERTEXATTRIB4DVARBPROC            glVertexAttrib4dvARB = NULL;
PFNGLVERTEXATTRIB4FVARBPROC            glVertexAttrib4fvARB = NULL;
PFNGLVERTEXATTRIB4SVARBPROC            glVertexAttrib4svARB = NULL;

PFNGLVERTEXATTRIB4BVARBPROC            glVertexAttrib4bvARB  = NULL;
PFNGLVERTEXATTRIB4UBVARBPROC           glVertexAttrib4ubvARB = NULL;
PFNGLVERTEXATTRIB4USVARBPROC           glVertexAttrib4usvARB = NULL;
PFNGLVERTEXATTRIB4IVARBPROC            glVertexAttrib4ivARB  = NULL;
PFNGLVERTEXATTRIB4UIVARBPROC           glVertexAttrib4uivARB = NULL;

PFNGLVERTEXATTRIB4NUBARBPROC           glVertexAttrib4NubARB  = NULL;
PFNGLVERTEXATTRIB4NBVARBPROC           glVertexAttrib4NbvARB  = NULL;
PFNGLVERTEXATTRIB4NUBVARBPROC          glVertexAttrib4NubvARB = NULL;
PFNGLVERTEXATTRIB4NSVARBPROC           glVertexAttrib4NsvARB  = NULL;
PFNGLVERTEXATTRIB4NUSVARBPROC          glVertexAttrib4NusvARB = NULL;
PFNGLVERTEXATTRIB4NIVARBPROC           glVertexAttrib4NivARB  = NULL;
PFNGLVERTEXATTRIB4NUIVARBPROC          glVertexAttrib4NuivARB = NULL;
//------------------------------------------------------------------------------------------
bool extLoadVertexAndFragmentShaders (char * extensions)
{
	//--------------------------------------------------------------------------------------
	// Comprobamos que esté la extensión para los vertex shaders.
	//--------------------------------------------------------------------------------------
	if(strstr(extensions, "GL_ARB_vertex_shader") == NULL)
	{
		extVertexShaders = false;
		return appSetLastError(EXTERR_VERTEX_SHADERS);
	}
	else
	{
		extVertexShaders = true;
	}

	//--------------------------------------------------------------------------------------
	// Comprobamos que esté la extensión para los fragment shaders.
	//--------------------------------------------------------------------------------------
	if(strstr(extensions, "GL_ARB_fragment_shader") == NULL)
	{
		extFragmentShaders = false;
		return appSetLastError(EXTERR_FRAGMENT_SHADERS);
	}
	else
	{
		extFragmentShaders = true;
	}



	//--------------------------------------------------------------------------------------
	// GLhandleARB glCreateProgramObjectARB (void);
	//--------------------------------------------------------------------------------------
	glCreateProgramObjectARB = (PFNGLCREATEPROGRAMOBJECTARBPROC)
							   wglGetProcAddress("glCreateProgramObjectARB");

    if(glCreateProgramObjectARB == NULL)
		return appSetLastError(EXTERR_GLCREATEPROGRAMOBJECTARB);

	//--------------------------------------------------------------------------------------
	// GLhandleARB glCreateShaderObjectARB (GLenum shaderType);
	//--------------------------------------------------------------------------------------
	glCreateShaderObjectARB = (PFNGLCREATESHADEROBJECTARBPROC)
							  wglGetProcAddress("glCreateShaderObjectARB");

    if(glCreateShaderObjectARB == NULL)
		return appSetLastError(EXTERR_GLCREATESHADEROBJECTARB);

	//--------------------------------------------------------------------------------------
	// void glShaderSourceARB (GLhandleARB shaderObj, GLsizei count,
	//                         const GLcharARB ** string, const GLint * length);
	//--------------------------------------------------------------------------------------
	glShaderSourceARB = (PFNGLSHADERSOURCEARBPROC)
						wglGetProcAddress("glShaderSourceARB");

    if(glShaderSourceARB == NULL)
		return appSetLastError(EXTERR_GLSHADERSOURCEARB);

	//--------------------------------------------------------------------------------------
	// void glCompileShaderARB (GLhandleARB shaderObj);
	//--------------------------------------------------------------------------------------
	glCompileShaderARB = (PFNGLCOMPILESHADERARBPROC)
						 wglGetProcAddress("glCompileShaderARB");

    if(glCompileShaderARB == NULL)
		return appSetLastError(EXTERR_GLCOMPILESHADERARB);

	//--------------------------------------------------------------------------------------
	// void glAttachObjectARB (GLhandleARB containerObj, GLhandleARB obj);
	//--------------------------------------------------------------------------------------
	glAttachObjectARB = (PFNGLATTACHOBJECTARBPROC)
						wglGetProcAddress("glAttachObjectARB");

    if(glAttachObjectARB == NULL)
		return appSetLastError(EXTERR_GLATTACHOBJECTARB);

	//--------------------------------------------------------------------------------------
	// void glLinkProgramARB (GLhandleARB programObj);
	//--------------------------------------------------------------------------------------
	glLinkProgramARB = (PFNGLLINKPROGRAMARBPROC)
					   wglGetProcAddress("glLinkProgramARB");

    if(glLinkProgramARB == NULL)
		return appSetLastError(EXTERR_GLLINKPROGRAMARB);

	//--------------------------------------------------------------------------------------
	// void glUseProgramObjectARB (GLhandleARB programObj);
	//--------------------------------------------------------------------------------------
	glUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC)
							wglGetProcAddress("glUseProgramObjectARB");

    if(glUseProgramObjectARB == NULL)
		return appSetLastError(EXTERR_GLUSEPROGRAMOBJECTARB);

	//--------------------------------------------------------------------------------------
	// void glGetObjectParameterfvARB (GLhandleARB obj, GLenum pname, GLfloat * params);
	//--------------------------------------------------------------------------------------
	glGetObjectParameterfvARB = (PFNGLGETOBJECTPARAMETERFVARBPROC)
								wglGetProcAddress("glGetObjectParameterfvARB");

    if(glGetObjectParameterfvARB == NULL)
		return appSetLastError(EXTERR_GLGETOBJECTPARAMETERFVARB);

	//--------------------------------------------------------------------------------------
	// void glGetObjectParameterivARB (GLhandleARB obj, GLenum pname, GLint * params);
	//--------------------------------------------------------------------------------------
	glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC)
								wglGetProcAddress("glGetObjectParameterivARB");

    if(glGetObjectParameterivARB == NULL)
		return appSetLastError(EXTERR_GLGETOBJECTPARAMETERIVARB);

	//--------------------------------------------------------------------------------------
	// void glGetInfoLogARB (GLhandleARB obj, GLsizei maxLength,
	//                       GLsizei * length, GLcharARB * infoLog);
	//--------------------------------------------------------------------------------------
	glGetInfoLogARB = (PFNGLGETINFOLOGARBPROC)
					  wglGetProcAddress("glGetInfoLogARB");

    if(glGetInfoLogARB == NULL)
		return appSetLastError(EXTERR_GLGETINFOLOGARB);

	//--------------------------------------------------------------------------------------
	// void glDetachObjectARB (GLhandleARB containerObj, GLhandleARB attachedObj);
	//--------------------------------------------------------------------------------------
	glDetachObjectARB = (PFNGLDETACHOBJECTARBPROC)
						wglGetProcAddress("glDetachObjectARB");

    if(glDetachObjectARB == NULL)
		return appSetLastError(EXTERR_GLDETACHOBJECTARB);

	//--------------------------------------------------------------------------------------
	// void glDeleteObjectARB (GLhandleARB obj);
	//--------------------------------------------------------------------------------------
	glDeleteObjectARB = (PFNGLDELETEOBJECTARBPROC)
						wglGetProcAddress("glDeleteObjectARB");

    if(glDeleteObjectARB == NULL)
		return appSetLastError(EXTERR_GLDELETEOBJECTARB);

	//--------------------------------------------------------------------------------------
	// GLhandleARB glGetHandleARB (GLenum pname);
	//--------------------------------------------------------------------------------------
	glGetHandleARB = (PFNGLGETHANDLEARBPROC)
					 wglGetProcAddress("glGetHandleARB");

    if(glGetHandleARB == NULL)
		return appSetLastError(EXTERR_GLGETHANDLEARB);

	//--------------------------------------------------------------------------------------
	// void glValidateProgramARB (GLhandleARB programObj);
	//--------------------------------------------------------------------------------------
	glValidateProgramARB = (PFNGLVALIDATEPROGRAMARBPROC)
						   wglGetProcAddress("glValidateProgramARB");

    if(glValidateProgramARB == NULL)
		return appSetLastError(EXTERR_GLVALIDATEPROGRAMARB);

	//--------------------------------------------------------------------------------------
	// void glGetAttachedObjectsARB (GLhandleARB containerObj, GLsizei maxCount,
	//                               GLsizei * count, GLhandleARB * obj);
	//--------------------------------------------------------------------------------------
	glGetAttachedObjectsARB = (PFNGLGETATTACHEDOBJECTSARBPROC)
							  wglGetProcAddress("glGetAttachedObjectsARB");

    if(glGetAttachedObjectsARB == NULL)
		return appSetLastError(EXTERR_GLGETATTACHEDOBJECTSARB);

	//--------------------------------------------------------------------------------------
	// void glGetShaderSourceARB (GLhandleARB obj, GLsizei maxLength,
	//                            GLsizei * length, GLcharARB * source);
	//--------------------------------------------------------------------------------------
	glGetShaderSourceARB = (PFNGLGETSHADERSOURCEARBPROC)
						   wglGetProcAddress("glGetShaderSourceARB");

    if(glGetShaderSourceARB == NULL)
		return appSetLastError(EXTERR_GLGETSHADERSOURCEARB);



	//--------------------------------------------------------------------------------------
	// GLint glGetUniformLocationARB (GLhandleARB programObj, const GLcharARB * name);
	//--------------------------------------------------------------------------------------
	glGetUniformLocationARB = (PFNGLGETUNIFORMLOCATIONARBPROC)
							  wglGetProcAddress("glGetUniformLocationARB");

    if(glGetUniformLocationARB == NULL)
		return appSetLastError(EXTERR_GLGETUNIFORMLOCATIONARB);

	//--------------------------------------------------------------------------------------
	// void glGetActiveUniformARB (GLhandleARB programObj, GLuint index,
	//                             GLsizei maxLength, GLsizei * length,
	//                             GLint * size, GLenum * type, GLcharARB * name);
	//--------------------------------------------------------------------------------------
	glGetActiveUniformARB = (PFNGLGETACTIVEUNIFORMARBPROC)
							wglGetProcAddress("glGetActiveUniformARB");

    if(glGetActiveUniformARB == NULL)
		return appSetLastError(EXTERR_GLGETACTIVEUNIFORMARB);

	//--------------------------------------------------------------------------------------
	// void glGetUniformfvARB (GLhandleARB programObj, GLint location, GLfloat * params);
	//--------------------------------------------------------------------------------------
	glGetUniformfvARB = (PFNGLGETUNIFORMFVARBPROC)
						wglGetProcAddress("glGetUniformfvARB");

    if(glGetUniformfvARB == NULL)
		return appSetLastError(EXTERR_GLGETUNIFORMFVARB);

	//--------------------------------------------------------------------------------------
	// void glGetUniformivARB (GLhandleARB programObj, GLint location, GLint * params);
	//--------------------------------------------------------------------------------------
	glGetUniformivARB = (PFNGLGETUNIFORMIVARBPROC)
						wglGetProcAddress("glGetUniformivARB");

    if(glGetUniformivARB == NULL)
		return appSetLastError(EXTERR_GLGETUNIFORMIVARB);

	//--------------------------------------------------------------------------------------
	// void glUniform1fARB (GLint location, GLfloat v0);
	//--------------------------------------------------------------------------------------
	glUniform1fARB = (PFNGLUNIFORM1FARBPROC)
					 wglGetProcAddress("glUniform1fARB");

    if(glUniform1fARB == NULL)
		return appSetLastError(EXTERR_GLUNIFORM1FARB);

	//--------------------------------------------------------------------------------------
	// void glUniform1iARB (GLint location, GLint v0);
	//--------------------------------------------------------------------------------------
	glUniform1iARB = (PFNGLUNIFORM1IARBPROC)
					 wglGetProcAddress("glUniform1iARB");

    if(glUniform1iARB == NULL)
		return appSetLastError(EXTERR_GLUNIFORM1IARB);

	//--------------------------------------------------------------------------------------
	// void glUniform1fvARB (GLint location, GLsizei count, const GLfloat * value);
	//--------------------------------------------------------------------------------------
	glUniform1fvARB = (PFNGLUNIFORM1FVARBPROC)
					  wglGetProcAddress("glUniform1fvARB");

    if(glUniform1fvARB == NULL)
		return appSetLastError(EXTERR_GLUNIFORM1FVARB);

	//--------------------------------------------------------------------------------------
	// void glUniform1ivARB (GLint location, GLsizei count, const GLint * value);
	//--------------------------------------------------------------------------------------
	glUniform1ivARB = (PFNGLUNIFORM1IVARBPROC)
					  wglGetProcAddress("glUniform1ivARB");

    if(glUniform1ivARB == NULL)
		return appSetLastError(EXTERR_GLUNIFORM1IVARB);

	//--------------------------------------------------------------------------------------
	// void glUniform2fARB (GLint location, GLfloat v0, GLfloat v1);
	//--------------------------------------------------------------------------------------
	glUniform2fARB = (PFNGLUNIFORM2FARBPROC)
					 wglGetProcAddress("glUniform2fARB");

    if(glUniform2fARB == NULL)
		return appSetLastError(EXTERR_GLUNIFORM2FARB);

	//--------------------------------------------------------------------------------------
	// void glUniform2iARB (GLint location, GLint v0, GLint v1);
	//--------------------------------------------------------------------------------------
	glUniform2iARB = (PFNGLUNIFORM2IARBPROC)
					 wglGetProcAddress("glUniform2iARB");

    if(glUniform2iARB == NULL)
		return appSetLastError(EXTERR_GLUNIFORM2IARB);

	//--------------------------------------------------------------------------------------
	// void glUniform2fvARB (GLint location, GLsizei count, const GLfloat * value);
	//--------------------------------------------------------------------------------------
	glUniform2fvARB = (PFNGLUNIFORM2FVARBPROC)
					  wglGetProcAddress("glUniform2fvARB");

    if(glUniform2fvARB == NULL)
		return appSetLastError(EXTERR_GLUNIFORM2FVARB);

	//--------------------------------------------------------------------------------------
	// void glUniform2ivARB (GLint location, GLsizei count, const GLint * value);
	//--------------------------------------------------------------------------------------
	glUniform2ivARB = (PFNGLUNIFORM2IVARBPROC)
					  wglGetProcAddress("glUniform2ivARB");

    if(glUniform2ivARB == NULL)
		return appSetLastError(EXTERR_GLUNIFORM2IVARB);

	//--------------------------------------------------------------------------------------
	// void glUniform3fARB (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
	//--------------------------------------------------------------------------------------
	glUniform3fARB = (PFNGLUNIFORM3FARBPROC)
					 wglGetProcAddress("glUniform3fARB");

    if(glUniform3fARB == NULL)
		return appSetLastError(EXTERR_GLUNIFORM3FARB);

	//--------------------------------------------------------------------------------------
	// void glUniform3iARB (GLint location, GLint v0, GLint v1, GLint v2);
	//--------------------------------------------------------------------------------------
	glUniform3iARB = (PFNGLUNIFORM3IARBPROC)
					 wglGetProcAddress("glUniform3iARB");

    if(glUniform3iARB == NULL)
		return appSetLastError(EXTERR_GLUNIFORM3IARB);

	//--------------------------------------------------------------------------------------
	// void glUniform3fvARB (GLint location, GLsizei count, const GLfloat * value);
	//--------------------------------------------------------------------------------------
	glUniform3fvARB = (PFNGLUNIFORM3FVARBPROC)
					  wglGetProcAddress("glUniform3fvARB");

    if(glUniform3fvARB == NULL)
		return appSetLastError(EXTERR_GLUNIFORM3FVARB);

	//--------------------------------------------------------------------------------------
	// void glUniform3ivARB (GLint location, GLsizei count, const GLint * value);
	//--------------------------------------------------------------------------------------
	glUniform3ivARB = (PFNGLUNIFORM3IVARBPROC)
					  wglGetProcAddress("glUniform3ivARB");

    if(glUniform3ivARB == NULL)
		return appSetLastError(EXTERR_GLUNIFORM3IVARB);

	//--------------------------------------------------------------------------------------
	// void glUniform4fARB (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
	//--------------------------------------------------------------------------------------
	glUniform4fARB = (PFNGLUNIFORM4FARBPROC)
					 wglGetProcAddress("glUniform4fARB");

    if(glUniform4fARB == NULL)
		return appSetLastError(EXTERR_GLUNIFORM4FARB);

	//--------------------------------------------------------------------------------------
	// void glUniform4iARB (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
	//--------------------------------------------------------------------------------------
	glUniform4iARB = (PFNGLUNIFORM4IARBPROC)
					 wglGetProcAddress("glUniform4iARB");

    if(glUniform4iARB == NULL)
		return appSetLastError(EXTERR_GLUNIFORM4IARB);

	//--------------------------------------------------------------------------------------
	// void glUniform4fvARB (GLint location, GLsizei count, const GLfloat * value);
	//--------------------------------------------------------------------------------------
	glUniform4fvARB = (PFNGLUNIFORM4FVARBPROC)
					  wglGetProcAddress("glUniform4fvARB");

    if(glUniform4fvARB == NULL)
		return appSetLastError(EXTERR_GLUNIFORM4FVARB);

	//--------------------------------------------------------------------------------------
	// void glUniform4ivARB (GLint location, GLsizei count, const GLint * value);
	//--------------------------------------------------------------------------------------
	glUniform4ivARB = (PFNGLUNIFORM4IVARBPROC)
					  wglGetProcAddress("glUniform4ivARB");

    if(glUniform4ivARB == NULL)
		return appSetLastError(EXTERR_GLUNIFORM4IVARB);

	//--------------------------------------------------------------------------------------
	// void glUniformMatrix2fvARB (GLint location, GLsizei count,
	//                             GLboolean transpose, const GLfloat * value);
	//--------------------------------------------------------------------------------------
	glUniformMatrix2fvARB = (PFNGLUNIFORMMATRIX2FVARBPROC)
							wglGetProcAddress("glUniformMatrix2fvARB");

    if(glUniformMatrix2fvARB == NULL)
		return appSetLastError(EXTERR_GLUNIFORMMATRIX2FVARB);

	//--------------------------------------------------------------------------------------
	// void glUniformMatrix3fvARB (GLint location, GLsizei count,
	//                             GLboolean transpose, const GLfloat * value);
	//--------------------------------------------------------------------------------------
	glUniformMatrix3fvARB = (PFNGLUNIFORMMATRIX3FVARBPROC)
							wglGetProcAddress("glUniformMatrix3fvARB");

    if(glUniformMatrix3fvARB == NULL)
		return appSetLastError(EXTERR_GLUNIFORMMATRIX3FVARB);

	//--------------------------------------------------------------------------------------
	// void glUniformMatrix4fvARB (GLint location, GLsizei count,
	//                             GLboolean transpose, const GLfloat * value);
	//--------------------------------------------------------------------------------------
	glUniformMatrix4fvARB = (PFNGLUNIFORMMATRIX4FVARBPROC)
							wglGetProcAddress("glUniformMatrix4fvARB");

    if(glUniformMatrix4fvARB == NULL)
		return appSetLastError(EXTERR_GLUNIFORMMATRIX4FVARB);



	//--------------------------------------------------------------------------------------
	// GLint glGetAttribLocationARB (GLhandleARB programObj, const GLcharARB * name);
	//--------------------------------------------------------------------------------------
	glGetAttribLocationARB = (PFNGLGETATTRIBLOCATIONARBPROC)
							 wglGetProcAddress("glGetAttribLocationARB");

    if(glGetAttribLocationARB == NULL)
		return appSetLastError(EXTERR_GLGETATTRIBLOCATIONARB);

	//--------------------------------------------------------------------------------------
	// void glBindAttribLocationARB (GLhandleARB programObj, GLuint index, const GLcharARB * name);
	//--------------------------------------------------------------------------------------
	glBindAttribLocationARB = (PFNGLBINDATTRIBLOCATIONARBPROC)
							  wglGetProcAddress("glBindAttribLocationARB");

    if(glBindAttribLocationARB == NULL)
		return appSetLastError(EXTERR_GLBINDATTRIBLOCATIONARB);
		
	//--------------------------------------------------------------------------------------
	// void glGetActiveAttribARB (GLhandleARB programObj, GLuint index, GLsizei maxLength,
	//                            GLsizei * length, GLint * size, GLenum * type, GLcharARB * name);
	//--------------------------------------------------------------------------------------
	glGetActiveAttribARB = (PFNGLGETACTIVEATTRIBARBPROC)
						   wglGetProcAddress("glGetActiveAttribARB");

    if(glGetActiveAttribARB == NULL)
		return appSetLastError(EXTERR_GLGETACTIVEATTRIBARB);

	//--------------------------------------------------------------------------------------
	// void glEnableVertexAttribArrayARB (GLuint index);
	//--------------------------------------------------------------------------------------
	glEnableVertexAttribArrayARB = (PFNGLENABLEVERTEXATTRIBARRAYARBPROC)
								   wglGetProcAddress("glEnableVertexAttribArrayARB");

    if(glEnableVertexAttribArrayARB == NULL)
		return appSetLastError(EXTERR_GLENABLEVERTEXATTRIBARRAYARB);

	//--------------------------------------------------------------------------------------
	// void glDisableVertexAttribArrayARB (GLuint index);
	//--------------------------------------------------------------------------------------
	glDisableVertexAttribArrayARB = (PFNGLDISABLEVERTEXATTRIBARRAYARBPROC)
									wglGetProcAddress("glDisableVertexAttribArrayARB");

    if(glDisableVertexAttribArrayARB == NULL)
		return appSetLastError(EXTERR_GLDISABLEVERTEXATTRIBARRAYARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttribPointerARB (GLuint index, GLint size, GLenum type,
	//                                GLboolean normalized, GLsizei stride,
	//                                const GLvoid * pointer);
	//--------------------------------------------------------------------------------------
	glVertexAttribPointerARB = (PFNGLVERTEXATTRIBPOINTERARBPROC)
							   wglGetProcAddress("glVertexAttribPointerARB");

    if(glVertexAttribPointerARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIBPOINTERARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib1dARB (GLuint index, GLdouble x);
	//--------------------------------------------------------------------------------------
	glVertexAttrib1dARB = (PFNGLVERTEXATTRIB1DARBPROC)
						  wglGetProcAddress("glVertexAttrib1dARB");

    if(glVertexAttrib1dARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB1DARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib1fARB (GLuint index, GLfloat x);
	//--------------------------------------------------------------------------------------
	glVertexAttrib1fARB = (PFNGLVERTEXATTRIB1FARBPROC)
						  wglGetProcAddress("glVertexAttrib1fARB");

    if(glVertexAttrib1fARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB1FARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib1sARB (GLuint index, GLshort x);
	//--------------------------------------------------------------------------------------
	glVertexAttrib1sARB = (PFNGLVERTEXATTRIB1SARBPROC)
						  wglGetProcAddress("glVertexAttrib1sARB");

    if(glVertexAttrib1sARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB1SARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib1dvARB (GLuint index, const GLdouble * v);
	//--------------------------------------------------------------------------------------
	glVertexAttrib1dvARB = (PFNGLVERTEXATTRIB1DVARBPROC)
						   wglGetProcAddress("glVertexAttrib1dvARB");

    if(glVertexAttrib1dvARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB1DVARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib1fvARB (GLuint index, const GLfloat * v);
	//--------------------------------------------------------------------------------------
	glVertexAttrib1fvARB = (PFNGLVERTEXATTRIB1FVARBPROC)
						   wglGetProcAddress("glVertexAttrib1fvARB");

    if(glVertexAttrib1fvARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB1FVARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib1svARB (GLuint index, const GLshort * v);
	//--------------------------------------------------------------------------------------
	glVertexAttrib1svARB = (PFNGLVERTEXATTRIB1SVARBPROC)
						   wglGetProcAddress("glVertexAttrib1svARB");

    if(glVertexAttrib1svARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB1SVARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib2dARB (GLuint index, GLdouble x, GLdouble y);
	//--------------------------------------------------------------------------------------
	glVertexAttrib2dARB = (PFNGLVERTEXATTRIB2DARBPROC)
						  wglGetProcAddress("glVertexAttrib2dARB");

    if(glVertexAttrib2dARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB2DARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib2fARB (GLuint index, GLfloat x, GLfloat y);
	//--------------------------------------------------------------------------------------
	glVertexAttrib2fARB = (PFNGLVERTEXATTRIB2FARBPROC)
						  wglGetProcAddress("glVertexAttrib2fARB");

    if(glVertexAttrib2fARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB2FARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib2sARB (GLuint index, GLshort x, GLshort y);
	//--------------------------------------------------------------------------------------
	glVertexAttrib2sARB = (PFNGLVERTEXATTRIB2SARBPROC)
						  wglGetProcAddress("glVertexAttrib2sARB");

    if(glVertexAttrib2sARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB2SARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib2dvARB (GLuint index, const GLdouble * v);
	//--------------------------------------------------------------------------------------
	glVertexAttrib2dvARB = (PFNGLVERTEXATTRIB2DVARBPROC)
						   wglGetProcAddress("glVertexAttrib2dvARB");

    if(glVertexAttrib2dvARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB2DVARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib2fvARB (GLuint index, const GLfloat * v);
	//--------------------------------------------------------------------------------------
	glVertexAttrib2fvARB = (PFNGLVERTEXATTRIB2FVARBPROC)
						   wglGetProcAddress("glVertexAttrib2fvARB");

    if(glVertexAttrib2fvARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB2FVARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib2svARB (GLuint index, const GLshort * v);
	//--------------------------------------------------------------------------------------
	glVertexAttrib2svARB = (PFNGLVERTEXATTRIB2SVARBPROC)
						   wglGetProcAddress("glVertexAttrib2svARB");

    if(glVertexAttrib2svARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB2SVARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib3dARB (GLuint index, GLdouble x, GLdouble y, GLdouble w);
	//--------------------------------------------------------------------------------------
	glVertexAttrib3dARB = (PFNGLVERTEXATTRIB3DARBPROC)
						  wglGetProcAddress("glVertexAttrib3dARB");

    if(glVertexAttrib3dARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB3DARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib3fARB (GLuint index, GLfloat x, GLfloat y, GLfloat w);
	//--------------------------------------------------------------------------------------
	glVertexAttrib3fARB = (PFNGLVERTEXATTRIB3FARBPROC)
						  wglGetProcAddress("glVertexAttrib3fARB");

    if(glVertexAttrib3fARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB3FARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib3sARB (GLuint index, GLshort x, GLshort y, GLshort w);
	//--------------------------------------------------------------------------------------
	glVertexAttrib3sARB = (PFNGLVERTEXATTRIB3SARBPROC)
						  wglGetProcAddress("glVertexAttrib3sARB");

    if(glVertexAttrib3sARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB3SARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib3dvARB (GLuint index, const GLdouble * v);
	//--------------------------------------------------------------------------------------
	glVertexAttrib3dvARB = (PFNGLVERTEXATTRIB3DVARBPROC)
						   wglGetProcAddress("glVertexAttrib3dvARB");

    if(glVertexAttrib3dvARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB3DVARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib3fvARB (GLuint index, const GLfloat * v);
	//--------------------------------------------------------------------------------------
	glVertexAttrib3fvARB = (PFNGLVERTEXATTRIB3FVARBPROC)
						   wglGetProcAddress("glVertexAttrib3fvARB");

    if(glVertexAttrib3fvARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB3FVARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib3svARB (GLuint index, const GLshort * v);
	//--------------------------------------------------------------------------------------
	glVertexAttrib3svARB = (PFNGLVERTEXATTRIB3SVARBPROC)
						   wglGetProcAddress("glVertexAttrib3svARB");

    if(glVertexAttrib3svARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB3SVARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib4dARB (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
	//--------------------------------------------------------------------------------------
	glVertexAttrib4dARB = (PFNGLVERTEXATTRIB4DARBPROC)
						  wglGetProcAddress("glVertexAttrib4dARB");

    if(glVertexAttrib4dARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB4DARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib4fARB (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	//--------------------------------------------------------------------------------------
	glVertexAttrib4fARB = (PFNGLVERTEXATTRIB4FARBPROC)
						  wglGetProcAddress("glVertexAttrib4fARB");

    if(glVertexAttrib4fARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB4FARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib4sARB (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
	//--------------------------------------------------------------------------------------
	glVertexAttrib4sARB = (PFNGLVERTEXATTRIB4SARBPROC)
						  wglGetProcAddress("glVertexAttrib4sARB");

    if(glVertexAttrib4sARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB4SARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib4dvARB (GLuint index, const GLdouble * v);
	//--------------------------------------------------------------------------------------
	glVertexAttrib4dvARB = (PFNGLVERTEXATTRIB4DVARBPROC)
						   wglGetProcAddress("glVertexAttrib4dvARB");

    if(glVertexAttrib4dvARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB4DVARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib4fvARB (GLuint index, const GLfloat * v);
	//--------------------------------------------------------------------------------------
	glVertexAttrib4fvARB = (PFNGLVERTEXATTRIB4FVARBPROC)
						   wglGetProcAddress("glVertexAttrib4fvARB");

    if(glVertexAttrib4fvARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB4FVARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib4svARB (GLuint index, const GLshort * v);
	//--------------------------------------------------------------------------------------
	glVertexAttrib4svARB = (PFNGLVERTEXATTRIB4SVARBPROC)
						   wglGetProcAddress("glVertexAttrib4svARB");

    if(glVertexAttrib4svARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB4SVARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib4bvARB (GLuint index, const GLbyte * v);
	//--------------------------------------------------------------------------------------
	glVertexAttrib4bvARB = (PFNGLVERTEXATTRIB4BVARBPROC)
						   wglGetProcAddress("glVertexAttrib4bvARB");

    if(glVertexAttrib4bvARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB4BVARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib4ubvARB (GLuint index, const GLubyte * v);
	//--------------------------------------------------------------------------------------
	glVertexAttrib4ubvARB = (PFNGLVERTEXATTRIB4UBVARBPROC)
							wglGetProcAddress("glVertexAttrib4ubvARB");

    if(glVertexAttrib4ubvARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB4UBVARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib4usvARB (GLuint index, const GLushort * v);
	//--------------------------------------------------------------------------------------
	glVertexAttrib4usvARB = (PFNGLVERTEXATTRIB4USVARBPROC)
							wglGetProcAddress("glVertexAttrib4usvARB");

    if(glVertexAttrib4usvARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB4USVARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib4ivARB (GLuint index, const GLint * v);
	//--------------------------------------------------------------------------------------
	glVertexAttrib4ivARB = (PFNGLVERTEXATTRIB4IVARBPROC)
						   wglGetProcAddress("glVertexAttrib4ivARB");

    if(glVertexAttrib4ivARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB4IVARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib4uivARB (GLuint index, const GLuint * v);
	//--------------------------------------------------------------------------------------
	glVertexAttrib4uivARB = (PFNGLVERTEXATTRIB4UIVARBPROC)
							wglGetProcAddress("glVertexAttrib4uivARB");

    if(glVertexAttrib4uivARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB4UIVARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib4NubARB (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
	//--------------------------------------------------------------------------------------
	glVertexAttrib4NubARB = (PFNGLVERTEXATTRIB4NUBARBPROC)
							wglGetProcAddress("glVertexAttrib4NubARB");

    if(glVertexAttrib4NubARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB4NUBARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib4NbvARB (GLuint index, const GLbyte * v);
	//--------------------------------------------------------------------------------------
	glVertexAttrib4NbvARB = (PFNGLVERTEXATTRIB4NBVARBPROC)
							wglGetProcAddress("glVertexAttrib4NbvARB");

    if(glVertexAttrib4NbvARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB4NBVARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib4NubvARB (GLuint index, const GLubyte * v);
	//--------------------------------------------------------------------------------------
	glVertexAttrib4NubvARB = (PFNGLVERTEXATTRIB4NUBVARBPROC)
							 wglGetProcAddress("glVertexAttrib4NubvARB");

    if(glVertexAttrib4NubvARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB4NUBVARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib4NsvARB (GLuint index, const GLshort * v);
	//--------------------------------------------------------------------------------------
	glVertexAttrib4NsvARB = (PFNGLVERTEXATTRIB4NSVARBPROC)
							wglGetProcAddress("glVertexAttrib4NsvARB");

    if(glVertexAttrib4NsvARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB4NSVARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib4NusvARB (GLuint index, const GLushort * v);
	//--------------------------------------------------------------------------------------
	glVertexAttrib4NusvARB = (PFNGLVERTEXATTRIB4NUSVARBPROC)
							 wglGetProcAddress("glVertexAttrib4NusvARB");

    if(glVertexAttrib4NusvARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB4NUSVARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib4NivARB (GLuint index, const GLint * v);
	//--------------------------------------------------------------------------------------
	glVertexAttrib4NivARB = (PFNGLVERTEXATTRIB4NIVARBPROC)
							wglGetProcAddress("glVertexAttrib4NivARB");

    if(glVertexAttrib4NivARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB4NIVARB);

	//--------------------------------------------------------------------------------------
	// void glVertexAttrib4NuivARB (GLuint index, const GLuint * v);
	//--------------------------------------------------------------------------------------
	glVertexAttrib4NuivARB = (PFNGLVERTEXATTRIB4NUIVARBPROC)
							 wglGetProcAddress("glVertexAttrib4NuivARB");

    if(glVertexAttrib4NuivARB == NULL)
		return appSetLastError(EXTERR_GLVERTEXATTRIB4NUIVARB);



	//--------------------------------------------------------------------------------------
	// Si se han cargado todas las funciones devolvemos true.
	//--------------------------------------------------------------------------------------
	return true;
}
//******************************************************************************************
// Funciones para cargar las extensiones.
//******************************************************************************************
bool extLoadExtensions (void)
{
	//--------------------------------------------------------------------------------------
	// Obtenemos la lista de extensiones soportadas en el programa.
	//--------------------------------------------------------------------------------------
    char * extensions = (char *) glGetString(GL_EXTENSIONS);

	//--------------------------------------------------------------------------------------
	// Borramos la variable que registra el último error.
	//--------------------------------------------------------------------------------------
	appResetLastError();

	//--------------------------------------------------------------------------------------
	// Cargamos la extensión para el multitexturizado.
	//--------------------------------------------------------------------------------------
	if(extLoadMultitexture(extensions) == false)
	{
		return false;
	}

	//--------------------------------------------------------------------------------------
	// Cargamos la extensión para manejar vertex y fragment shaders.
	//--------------------------------------------------------------------------------------
	if(extLoadVertexAndFragmentShaders(extensions) == false)
	{
		return false;
	}
	
	//--------------------------------------------------------------------------------------
	// Si todo ha ido bien devolvemos true.
	//--------------------------------------------------------------------------------------
	return true;
}
//******************************************************************************************
// extensions.cpp
//******************************************************************************************