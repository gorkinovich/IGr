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
#ifndef _ANUBIS_EXTENSIONS_H_
#define _ANUBIS_EXTENSIONS_H_
//******************************************************************************************
// Includes.
//******************************************************************************************
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
//------------------------------------------------------------------------------------------
#include <gl/gl.h>
#include <gl/glu.h>
//------------------------------------------------------------------------------------------
#include "gl/glext.h"
#include "error.h"
//******************************************************************************************
// Constantes.
//******************************************************************************************
#include "exterrors.h"
//******************************************************************************************
// Funciones para manejar las extensiones.
//******************************************************************************************
bool extLoadExtensions (void);
//------------------------------------------------------------------------------------------
int extMultitextureGetMaxTexUnits (void);
//------------------------------------------------------------------------------------------
bool extIsMultitexture    (void);
bool extIsVertexShaders   (void);
bool extIsFragmentShaders (void);
//******************************************************************************************
// Prototipos de las funciones que forman las extensiones.
//******************************************************************************************
/*
void glActiveTextureARB       (GLenum texture);
void glClientActiveTextureARB (GLenum texture);

void glMultiTexCoord1dARB     (GLenum target, GLdouble s);
void glMultiTexCoord1fARB     (GLenum target, GLfloat s);
void glMultiTexCoord1iARB     (GLenum target, GLint s);
void glMultiTexCoord1sARB     (GLenum target, GLshort s);
void glMultiTexCoord1dvARB    (GLenum target, const GLdouble * v);
void glMultiTexCoord1fvARB    (GLenum target, const GLfloat * v);
void glMultiTexCoord1ivARB    (GLenum target, const GLint * v);
void glMultiTexCoord1svARB    (GLenum target, const GLshort * v);

void glMultiTexCoord2dARB     (GLenum target, GLdouble s, GLdouble t);
void glMultiTexCoord2fARB     (GLenum target, GLfloat s, GLfloat t);
void glMultiTexCoord2iARB     (GLenum target, GLint s, GLint t);
void glMultiTexCoord2sARB     (GLenum target, GLshort s, GLshort t);
void glMultiTexCoord2dvARB    (GLenum target, const GLdouble * v);
void glMultiTexCoord2fvARB    (GLenum target, const GLfloat * v);
void glMultiTexCoord2ivARB    (GLenum target, const GLint * v);
void glMultiTexCoord2svARB    (GLenum target, const GLshort * v);

void glMultiTexCoord3dARB     (GLenum target, GLdouble s, GLdouble t, GLdouble r);
void glMultiTexCoord3fARB     (GLenum target, GLfloat s, GLfloat t, GLfloat r);
void glMultiTexCoord3iARB     (GLenum target, GLint s, GLint t, GLint r);
void glMultiTexCoord3sARB     (GLenum target, GLshort s, GLshort t, GLshort r);
void glMultiTexCoord3dvARB    (GLenum target, const GLdouble * v);
void glMultiTexCoord3fvARB    (GLenum target, const GLfloat * v);
void glMultiTexCoord3ivARB    (GLenum target, const GLint * v);
void glMultiTexCoord3svARB    (GLenum target, const GLshort * v);

void glMultiTexCoord4dARB     (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
void glMultiTexCoord4fARB     (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
void glMultiTexCoord4iARB     (GLenum target, GLint s, GLint t, GLint r, GLint q);
void glMultiTexCoord4sARB     (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
void glMultiTexCoord4dvARB    (GLenum target, const GLdouble * v);
void glMultiTexCoord4fvARB    (GLenum target, const GLfloat * v);
void glMultiTexCoord4ivARB    (GLenum target, const GLint * v);
void glMultiTexCoord4svARB    (GLenum target, const GLshort * v);
*/
//------------------------------------------------------------------------------------------
/*
GLhandleARB glCreateProgramObjectARB  (void);

GLhandleARB glCreateShaderObjectARB   (GLenum shaderType);
void        glShaderSourceARB         (GLhandleARB shaderObj, GLsizei count,
                                       const GLcharARB ** string, const GLint * length);
void        glCompileShaderARB        (GLhandleARB shaderObj);

void        glAttachObjectARB         (GLhandleARB containerObj, GLhandleARB obj);
void        glLinkProgramARB          (GLhandleARB programObj);
void        glUseProgramObjectARB     (GLhandleARB programObj);

void        glGetObjectParameterfvARB (GLhandleARB obj, GLenum pname, GLfloat * params);
void        glGetObjectParameterivARB (GLhandleARB obj, GLenum pname, GLint * params);
void        glGetInfoLogARB           (GLhandleARB obj, GLsizei maxLength, GLsizei * length,
                                       GLcharARB * infoLog);

void        glDetachObjectARB         (GLhandleARB containerObj, GLhandleARB attachedObj);
void        glDeleteObjectARB         (GLhandleARB obj);

GLhandleARB glGetHandleARB            (GLenum pname);
void        glValidateProgramARB      (GLhandleARB programObj);
void        glGetAttachedObjectsARB   (GLhandleARB containerObj, GLsizei maxCount,
                                       GLsizei * count, GLhandleARB * obj);
void        glGetShaderSourceARB      (GLhandleARB obj, GLsizei maxLength, GLsizei * length,
                                       GLcharARB * source);
*/
//------------------------------------------------------------------------------------------
/*
GLint       glGetUniformLocationARB   (GLhandleARB programObj, const GLcharARB * name);
void        glGetActiveUniformARB     (GLhandleARB programObj, GLuint index, GLsizei maxLength,
                                       GLsizei * length, GLint * size, GLenum * type, GLcharARB * name);
void        glGetUniformfvARB         (GLhandleARB programObj, GLint location, GLfloat * params);
void        glGetUniformivARB         (GLhandleARB programObj, GLint location, GLint * params);

void        glUniform1fARB            (GLint location, GLfloat v0);
void        glUniform1iARB            (GLint location, GLint v0);
void        glUniform1fvARB           (GLint location, GLsizei count, const GLfloat * value);
void        glUniform1ivARB           (GLint location, GLsizei count, const GLint * value);

void        glUniform2fARB            (GLint location, GLfloat v0, GLfloat v1);
void        glUniform2iARB            (GLint location, GLint v0, GLint v1);
void        glUniform2fvARB           (GLint location, GLsizei count, const GLfloat * value);
void        glUniform2ivARB           (GLint location, GLsizei count, const GLint * value);

void        glUniform3fARB            (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
void        glUniform3iARB            (GLint location, GLint v0, GLint v1, GLint v2);
void        glUniform3fvARB           (GLint location, GLsizei count, const GLfloat * value);
void        glUniform3ivARB           (GLint location, GLsizei count, const GLint * value);

void        glUniform4fARB            (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
void        glUniform4iARB            (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
void        glUniform4fvARB           (GLint location, GLsizei count, const GLfloat * value);
void        glUniform4ivARB           (GLint location, GLsizei count, const GLint * value);

void        glUniformMatrix2fvARB     (GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
void        glUniformMatrix3fvARB     (GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
void        glUniformMatrix4fvARB     (GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
*/
//------------------------------------------------------------------------------------------
/*
GLint glGetAttribLocationARB        (GLhandleARB programObj, const GLcharARB * name);
void  glBindAttribLocationARB       (GLhandleARB programObj, GLuint index, const GLcharARB * name);
void  glGetActiveAttribARB          (GLhandleARB programObj, GLuint index, GLsizei maxLength,
                                     GLsizei * length, GLint * size, GLenum * type, GLcharARB * name);

void  glEnableVertexAttribArrayARB  (GLuint index);
void  glDisableVertexAttribArrayARB (GLuint index);
void  glVertexAttribPointerARB      (GLuint index, GLint size, GLenum type, GLboolean normalized,
                                     GLsizei stride, const GLvoid * pointer);

void  glVertexAttrib1dARB           (GLuint index, GLdouble x);
void  glVertexAttrib1fARB           (GLuint index, GLfloat x);
void  glVertexAttrib1sARB           (GLuint index, GLshort x);
void  glVertexAttrib1dvARB          (GLuint index, const GLdouble * v);
void  glVertexAttrib1fvARB          (GLuint index, const GLfloat * v);
void  glVertexAttrib1svARB          (GLuint index, const GLshort * v);

void  glVertexAttrib2dARB           (GLuint index, GLdouble x, GLdouble y);
void  glVertexAttrib2fARB           (GLuint index, GLfloat x, GLfloat y);
void  glVertexAttrib2sARB           (GLuint index, GLshort x, GLshort y);
void  glVertexAttrib2dvARB          (GLuint index, const GLdouble * v);
void  glVertexAttrib2fvARB          (GLuint index, const GLfloat * v);
void  glVertexAttrib2svARB          (GLuint index, const GLshort * v);

void  glVertexAttrib3dARB           (GLuint index, GLdouble x, GLdouble y, GLdouble w);
void  glVertexAttrib3fARB           (GLuint index, GLfloat x, GLfloat y, GLfloat w);
void  glVertexAttrib3sARB           (GLuint index, GLshort x, GLshort y, GLshort w);
void  glVertexAttrib3dvARB          (GLuint index, const GLdouble * v);
void  glVertexAttrib3fvARB          (GLuint index, const GLfloat * v);
void  glVertexAttrib3svARB          (GLuint index, const GLshort * v);

void  glVertexAttrib4dARB           (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
void  glVertexAttrib4fARB           (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
void  glVertexAttrib4sARB           (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
void  glVertexAttrib4dvARB          (GLuint index, const GLdouble * v);
void  glVertexAttrib4fvARB          (GLuint index, const GLfloat * v);
void  glVertexAttrib4svARB          (GLuint index, const GLshort * v);

void  glVertexAttrib4bvARB          (GLuint index, const GLbyte * v);
void  glVertexAttrib4ubvARB         (GLuint index, const GLubyte * v);
void  glVertexAttrib4usvARB         (GLuint index, const GLushort * v);
void  glVertexAttrib4ivARB          (GLuint index, const GLint * v);
void  glVertexAttrib4uivARB         (GLuint index, const GLuint * v);

void  glVertexAttrib4NubARB         (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
void  glVertexAttrib4NbvARB         (GLuint index, const GLbyte * v);
void  glVertexAttrib4NubvARB        (GLuint index, const GLubyte * v);
void  glVertexAttrib4NsvARB         (GLuint index, const GLshort * v);
void  glVertexAttrib4NusvARB        (GLuint index, const GLushort * v);
void  glVertexAttrib4NivARB         (GLuint index, const GLint * v);
void  glVertexAttrib4NuivARB        (GLuint index, const GLuint * v);
*/
//******************************************************************************************
// Punteros a las extensiones.
//******************************************************************************************
extern PFNGLACTIVETEXTUREARBPROC       glActiveTextureARB;
extern PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB;

extern PFNGLMULTITEXCOORD1DARBPROC     glMultiTexCoord1dARB;
extern PFNGLMULTITEXCOORD1FARBPROC     glMultiTexCoord1fARB;
extern PFNGLMULTITEXCOORD1IARBPROC     glMultiTexCoord1iARB;
extern PFNGLMULTITEXCOORD1SARBPROC     glMultiTexCoord1sARB;
extern PFNGLMULTITEXCOORD1DVARBPROC    glMultiTexCoord1dvARB;
extern PFNGLMULTITEXCOORD1FVARBPROC    glMultiTexCoord1fvARB;
extern PFNGLMULTITEXCOORD1IVARBPROC    glMultiTexCoord1ivARB;
extern PFNGLMULTITEXCOORD1SVARBPROC    glMultiTexCoord1svARB;

extern PFNGLMULTITEXCOORD2DARBPROC     glMultiTexCoord2dARB;
extern PFNGLMULTITEXCOORD2FARBPROC     glMultiTexCoord2fARB;
extern PFNGLMULTITEXCOORD2IARBPROC     glMultiTexCoord2iARB;
extern PFNGLMULTITEXCOORD2SARBPROC     glMultiTexCoord2sARB;
extern PFNGLMULTITEXCOORD2DVARBPROC    glMultiTexCoord2dvARB;
extern PFNGLMULTITEXCOORD2FVARBPROC    glMultiTexCoord2fvARB;
extern PFNGLMULTITEXCOORD2IVARBPROC    glMultiTexCoord2ivARB;
extern PFNGLMULTITEXCOORD2SVARBPROC    glMultiTexCoord2svARB;

extern PFNGLMULTITEXCOORD3DARBPROC     glMultiTexCoord3dARB;
extern PFNGLMULTITEXCOORD3FARBPROC     glMultiTexCoord3fARB;
extern PFNGLMULTITEXCOORD3IARBPROC     glMultiTexCoord3iARB;
extern PFNGLMULTITEXCOORD3SARBPROC     glMultiTexCoord3sARB;
extern PFNGLMULTITEXCOORD3DVARBPROC    glMultiTexCoord3dvARB;
extern PFNGLMULTITEXCOORD3FVARBPROC    glMultiTexCoord3fvARB;
extern PFNGLMULTITEXCOORD3IVARBPROC    glMultiTexCoord3ivARB;
extern PFNGLMULTITEXCOORD3SVARBPROC    glMultiTexCoord3svARB;

extern PFNGLMULTITEXCOORD4DARBPROC     glMultiTexCoord4dARB;
extern PFNGLMULTITEXCOORD4FARBPROC     glMultiTexCoord4fARB;
extern PFNGLMULTITEXCOORD4IARBPROC     glMultiTexCoord4iARB;
extern PFNGLMULTITEXCOORD4SARBPROC     glMultiTexCoord4sARB;
extern PFNGLMULTITEXCOORD4DVARBPROC    glMultiTexCoord4dvARB;
extern PFNGLMULTITEXCOORD4FVARBPROC    glMultiTexCoord4fvARB;
extern PFNGLMULTITEXCOORD4IVARBPROC    glMultiTexCoord4ivARB;
extern PFNGLMULTITEXCOORD4SVARBPROC    glMultiTexCoord4svARB;
//------------------------------------------------------------------------------------------
extern PFNGLCREATEPROGRAMOBJECTARBPROC  glCreateProgramObjectARB;

extern PFNGLCREATESHADEROBJECTARBPROC   glCreateShaderObjectARB;
extern PFNGLSHADERSOURCEARBPROC         glShaderSourceARB;
extern PFNGLCOMPILESHADERARBPROC        glCompileShaderARB;

extern PFNGLATTACHOBJECTARBPROC         glAttachObjectARB;
extern PFNGLLINKPROGRAMARBPROC          glLinkProgramARB;
extern PFNGLUSEPROGRAMOBJECTARBPROC     glUseProgramObjectARB;

extern PFNGLGETOBJECTPARAMETERFVARBPROC glGetObjectParameterfvARB;
extern PFNGLGETOBJECTPARAMETERIVARBPROC glGetObjectParameterivARB;
extern PFNGLGETINFOLOGARBPROC           glGetInfoLogARB;

extern PFNGLDETACHOBJECTARBPROC         glDetachObjectARB;
extern PFNGLDELETEOBJECTARBPROC         glDeleteObjectARB;

extern PFNGLGETHANDLEARBPROC            glGetHandleARB;
extern PFNGLVALIDATEPROGRAMARBPROC      glValidateProgramARB;
extern PFNGLGETATTACHEDOBJECTSARBPROC   glGetAttachedObjectsARB;
extern PFNGLGETSHADERSOURCEARBPROC      glGetShaderSourceARB;
//------------------------------------------------------------------------------------------
extern PFNGLGETUNIFORMLOCATIONARBPROC   glGetUniformLocationARB;
extern PFNGLGETACTIVEUNIFORMARBPROC     glGetActiveUniformARB;
extern PFNGLGETUNIFORMFVARBPROC         glGetUniformfvARB;
extern PFNGLGETUNIFORMIVARBPROC         glGetUniformivARB;

extern PFNGLUNIFORM1FARBPROC            glUniform1fARB;
extern PFNGLUNIFORM2FARBPROC            glUniform2fARB;
extern PFNGLUNIFORM3FARBPROC            glUniform3fARB;
extern PFNGLUNIFORM4FARBPROC            glUniform4fARB;
extern PFNGLUNIFORM1IARBPROC            glUniform1iARB;
extern PFNGLUNIFORM2IARBPROC            glUniform2iARB;
extern PFNGLUNIFORM3IARBPROC            glUniform3iARB;
extern PFNGLUNIFORM4IARBPROC            glUniform4iARB;
extern PFNGLUNIFORM1FVARBPROC           glUniform1fvARB;
extern PFNGLUNIFORM2FVARBPROC           glUniform2fvARB;
extern PFNGLUNIFORM3FVARBPROC           glUniform3fvARB;
extern PFNGLUNIFORM4FVARBPROC           glUniform4fvARB;
extern PFNGLUNIFORM1IVARBPROC           glUniform1ivARB;
extern PFNGLUNIFORM2IVARBPROC           glUniform2ivARB;
extern PFNGLUNIFORM3IVARBPROC           glUniform3ivARB;
extern PFNGLUNIFORM4IVARBPROC           glUniform4ivARB;
extern PFNGLUNIFORMMATRIX2FVARBPROC     glUniformMatrix2fvARB;
extern PFNGLUNIFORMMATRIX3FVARBPROC     glUniformMatrix3fvARB;
extern PFNGLUNIFORMMATRIX4FVARBPROC     glUniformMatrix4fvARB;
//------------------------------------------------------------------------------------------
extern PFNGLGETATTRIBLOCATIONARBPROC        glGetAttribLocationARB;
extern PFNGLBINDATTRIBLOCATIONARBPROC       glBindAttribLocationARB;
extern PFNGLGETACTIVEATTRIBARBPROC          glGetActiveAttribARB;

extern PFNGLENABLEVERTEXATTRIBARRAYARBPROC  glEnableVertexAttribArrayARB;
extern PFNGLDISABLEVERTEXATTRIBARRAYARBPROC glDisableVertexAttribArrayARB;
extern PFNGLVERTEXATTRIBPOINTERARBPROC      glVertexAttribPointerARB;

extern PFNGLVERTEXATTRIB1DARBPROC           glVertexAttrib1dARB;
extern PFNGLVERTEXATTRIB1FARBPROC           glVertexAttrib1fARB;
extern PFNGLVERTEXATTRIB1SARBPROC           glVertexAttrib1sARB;
extern PFNGLVERTEXATTRIB1DVARBPROC          glVertexAttrib1dvARB;
extern PFNGLVERTEXATTRIB1FVARBPROC          glVertexAttrib1fvARB;
extern PFNGLVERTEXATTRIB1SVARBPROC          glVertexAttrib1svARB;

extern PFNGLVERTEXATTRIB2DARBPROC           glVertexAttrib2dARB;
extern PFNGLVERTEXATTRIB2FARBPROC           glVertexAttrib2fARB;
extern PFNGLVERTEXATTRIB2SARBPROC           glVertexAttrib2sARB;
extern PFNGLVERTEXATTRIB2DVARBPROC          glVertexAttrib2dvARB;
extern PFNGLVERTEXATTRIB2FVARBPROC          glVertexAttrib2fvARB;
extern PFNGLVERTEXATTRIB2SVARBPROC          glVertexAttrib2svARB;

extern PFNGLVERTEXATTRIB3DARBPROC           glVertexAttrib3dARB;
extern PFNGLVERTEXATTRIB3FARBPROC           glVertexAttrib3fARB;
extern PFNGLVERTEXATTRIB3SARBPROC           glVertexAttrib3sARB;
extern PFNGLVERTEXATTRIB3DVARBPROC          glVertexAttrib3dvARB;
extern PFNGLVERTEXATTRIB3FVARBPROC          glVertexAttrib3fvARB;
extern PFNGLVERTEXATTRIB3SVARBPROC          glVertexAttrib3svARB;

extern PFNGLVERTEXATTRIB4DARBPROC           glVertexAttrib4dARB;
extern PFNGLVERTEXATTRIB4FARBPROC           glVertexAttrib4fARB;
extern PFNGLVERTEXATTRIB4SARBPROC           glVertexAttrib4sARB;
extern PFNGLVERTEXATTRIB4DVARBPROC          glVertexAttrib4dvARB;
extern PFNGLVERTEXATTRIB4FVARBPROC          glVertexAttrib4fvARB;
extern PFNGLVERTEXATTRIB4SVARBPROC          glVertexAttrib4svARB;

extern PFNGLVERTEXATTRIB4BVARBPROC          glVertexAttrib4bvARB;
extern PFNGLVERTEXATTRIB4UBVARBPROC         glVertexAttrib4ubvARB;
extern PFNGLVERTEXATTRIB4USVARBPROC         glVertexAttrib4usvARB;
extern PFNGLVERTEXATTRIB4IVARBPROC          glVertexAttrib4ivARB;
extern PFNGLVERTEXATTRIB4UIVARBPROC         glVertexAttrib4uivARB;

extern PFNGLVERTEXATTRIB4NUBARBPROC         glVertexAttrib4NubARB;
extern PFNGLVERTEXATTRIB4NBVARBPROC         glVertexAttrib4NbvARB;
extern PFNGLVERTEXATTRIB4NUBVARBPROC        glVertexAttrib4NubvARB;
extern PFNGLVERTEXATTRIB4NSVARBPROC         glVertexAttrib4NsvARB;
extern PFNGLVERTEXATTRIB4NUSVARBPROC        glVertexAttrib4NusvARB;
extern PFNGLVERTEXATTRIB4NIVARBPROC         glVertexAttrib4NivARB;
extern PFNGLVERTEXATTRIB4NUIVARBPROC        glVertexAttrib4NuivARB;
//******************************************************************************************
#endif
//******************************************************************************************
// extensions.h
//******************************************************************************************