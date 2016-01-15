//---------------------------------------------------------------------------
// Gorka Suárez García - Ing. Tec. Inf. de Gestión 2º B.
// Práctica 01 - Apartado 01.
//---------------------------------------------------------------------------
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>
//---------------------------------------------------------------------------
#include <iostream>
#include <conio.h>
using namespace std;
//---------------------------------------------------------------------------
// Directivas del compilador.
//---------------------------------------------------------------------------
#pragma hdrstop
#pragma link "glaux.lib"
//---------------------------------------------------------------------------
// Variables globales del programa.
//---------------------------------------------------------------------------
int Apartado;
GLsizei Width;
GLsizei Height;
//---------------------------------------------------------------------------
// Funciones del programa de prueba.
//---------------------------------------------------------------------------
void CALLBACK Renderizado (void)
{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    if(Apartado == 1)
    {
        glColor3f(1.0f, 0.0f, 0.0f);

        auxWireTeapot(50.0f);
    }
    else
    {      
        glColor3f(1.0f, 1.0f, 1.0f);

        auxWireTeapot(50.0f);

        glColor3f(0.0f, 1.0f, 0.0f);

        glEnable(GL_LINE_STIPPLE);
        glLineStipple(4, 0x7272);

        glBegin(GL_LINES);
            glVertex3f(-100.0f, 0.0f, 0.0f);
            glVertex3f(100.0f, 0.0f, 0.0f);

            glVertex3f(0.0f, -100.0f, 0.0f);
            glVertex3f(0.0f, 100.0f, 0.0f);
        glEnd();
        
        glDisable(GL_LINE_STIPPLE);
    }

    glFlush();
    
    auxSwapBuffers();
}
//---------------------------------------------------------------------------
void CALLBACK Redimensionado (GLsizei w, GLsizei h)
{
    if(h == 0) h = 1;

    Width  = w;
    Height = h;

    switch(Apartado)
    {
    case 1:  
    case 2:
        glViewport(0, 0, w, h);

        glLoadIdentity();

        glOrtho(-125.0f, 125.0f, -125.0f, 125.0f, 125.0f, -125.0f);
        break;

    case 3:   
        glViewport(w/2, h/2, w/2, h/2);

        glLoadIdentity();

        glOrtho(-125.0f, 125.0f, -125.0f, 125.0f, 125.0f, -125.0f);
        break;

    case 4:  
        glViewport(w/2, h/2, w/2, h/2);

        glLoadIdentity();

        glOrtho(-50.0f, 50.0f, 25.0f, 125.0f, 125.0f, -125.0f);
        break;
    }

    glFlush();
}
//---------------------------------------------------------------------------
void CALLBACK Tecla1 (void)
{
    cout << "Pasando al modo Apartados 1 y 2..." << endl;
    Apartado = 1;
    
    Redimensionado(Width, Height);
}
//---------------------------------------------------------------------------
void CALLBACK Tecla2 (void)
{
    cout << "Pasando al modo Apartados 3..." << endl;
    Apartado = 2;

    Redimensionado(Width, Height);
}
//---------------------------------------------------------------------------
void CALLBACK Tecla3 (void)
{
    cout << "Pasando al modo Apartados 4a..." << endl;
    Apartado = 3;

    Redimensionado(Width, Height);
}
//---------------------------------------------------------------------------
void CALLBACK Tecla4 (void)
{
    cout << "Pasando al modo Apartados 4b..." << endl;
    Apartado = 4;

    Redimensionado(Width, Height);
}
//---------------------------------------------------------------------------
// Función principal del programa.
//---------------------------------------------------------------------------
#pragma argsused
int main (int argc, char ** argv)
{
    auxInitDisplayMode(AUX_DOUBLE | AUX_RGBA | AUX_DEPTH16);
    auxInitPosition(100, 100, 500, 500);
    auxInitWindow("Prueba con OpenGL - Práctica 1, Apartado 1");

    Apartado = 1;

    auxKeyFunc(AUX_1, Tecla1);
    auxKeyFunc(AUX_2, Tecla2);
    auxKeyFunc(AUX_3, Tecla3);
    auxKeyFunc(AUX_4, Tecla4);

    auxReshapeFunc(Redimensionado);
    auxMainLoop(Renderizado);

    cout << "Pulse una tecla para continuar...";
    getch(); cout << endl;
    return 0;
}
//---------------------------------------------------------------------------
// Fin PruebaOGL.cpp
//---------------------------------------------------------------------------
