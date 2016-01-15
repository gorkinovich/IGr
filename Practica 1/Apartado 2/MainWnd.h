//---------------------------------------------------------------------------
// Gorka Suárez García - Ing. Tec. Inf. de Gestión 2º B.
// Práctica 01 - Apartado 02.
//---------------------------------------------------------------------------
#ifndef MainWndH
#define MainWndH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "OpenGLPanel.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
    TOpenGLPanel *OpenGL;
    void __fastcall OpenGLPaint(TObject *Sender);
    void __fastcall OpenGLResize(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
    int Apartado;

    void ChangeProjection (void);

public:		// User declarations
    __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
