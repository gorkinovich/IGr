object MainForm: TMainForm
  Left = 221
  Top = 107
  Width = 634
  Height = 566
  Caption = 'Prueba con OpenGL - Práctica 1, Apartado 2'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object OpenGL: TOpenGLPanel
    Left = 0
    Top = 0
    Width = 626
    Height = 539
    Align = alClient
    TabOrder = 0
    PFDFlags = [f_PFD_DRAW_TO_WINDOW, f_PFD_SUPPORT_OPENGL, f_PFD_DOUBLEBUFFER]
    GLSwapBuffers = Manual
    Font3D_Type.Charset = ANSI_CHARSET
    Font3D_Type.Color = clWindowText
    Font3D_Type.Height = -9
    Font3D_Type.Name = 'Arial'
    Font3D_Type.Style = []
    Font3D_Extrustion = 0.100000001490116
    Font2D_Type.Charset = ANSI_CHARSET
    Font2D_Type.Color = clWindowText
    Font2D_Type.Height = -9
    Font2D_Type.Name = 'Arial'
    Font2D_Type.Style = []
    OnResize = OpenGLResize
    OnPaint = OpenGLPaint
  end
end
