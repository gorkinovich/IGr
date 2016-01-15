object AboutWnd: TAboutWnd
  Left = 329
  Top = 251
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'About Anubis Viewer'
  ClientHeight = 266
  ClientWidth = 427
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object AboutText: TMemo
    Left = 16
    Top = 16
    Width = 393
    Height = 201
    Color = clBtnFace
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 1
  end
  object CmdOk: TButton
    Left = 176
    Top = 232
    Width = 75
    Height = 25
    Caption = '&Ok'
    TabOrder = 0
    OnClick = CmdOkClick
  end
end
