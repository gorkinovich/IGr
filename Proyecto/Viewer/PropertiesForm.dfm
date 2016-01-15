object PropertiesWnd: TPropertiesWnd
  Left = 724
  Top = 205
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Model Properties'
  ClientHeight = 537
  ClientWidth = 425
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
  object LblName: TLabel
    Left = 8
    Top = 16
    Width = 34
    Height = 13
    Caption = 'Name: '
  end
  object Name: TEdit
    Left = 56
    Top = 8
    Width = 361
    Height = 21
    TabOrder = 0
  end
  object GBTransformation: TGroupBox
    Left = 8
    Top = 40
    Width = 409
    Height = 97
    Caption = ' Transformation '
    TabOrder = 1
    object LblPosition: TLabel
      Left = 16
      Top = 24
      Width = 43
      Height = 13
      Caption = 'Position: '
    end
    object LblRotation: TLabel
      Left = 16
      Top = 48
      Width = 46
      Height = 13
      Caption = 'Rotation: '
    end
    object LblScale: TLabel
      Left = 16
      Top = 72
      Width = 33
      Height = 13
      Caption = 'Scale: '
    end
    object Position: TEdit
      Left = 72
      Top = 16
      Width = 321
      Height = 21
      TabOrder = 0
      OnEnter = PositionEnter
      OnExit = PositionExit
      OnKeyDown = PositionKeyDown
    end
    object Rotation: TEdit
      Left = 72
      Top = 40
      Width = 321
      Height = 21
      TabOrder = 1
      OnEnter = RotationEnter
      OnExit = RotationExit
      OnKeyDown = RotationKeyDown
    end
    object Scale: TEdit
      Left = 72
      Top = 64
      Width = 321
      Height = 21
      TabOrder = 2
      OnEnter = ScaleEnter
      OnExit = ScaleExit
      OnKeyDown = ScaleKeyDown
    end
  end
  object ModelProperties: TPageControl
    Left = 8
    Top = 144
    Width = 409
    Height = 353
    ActivePage = TabObjects
    TabOrder = 2
    object TabObjects: TTabSheet
      Caption = 'Objects'
      object ObjList: TStringGrid
        Left = 8
        Top = 8
        Width = 385
        Height = 105
        ColCount = 14
        DefaultColWidth = 32
        DefaultRowHeight = 16
        RowCount = 2
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
        TabOrder = 0
        OnSelectCell = ObjListSelectCell
      end
      object ObjVertexes: TStringGrid
        Left = 8
        Top = 120
        Width = 385
        Height = 105
        DefaultColWidth = 32
        DefaultRowHeight = 16
        RowCount = 2
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
        TabOrder = 1
      end
      object ObjFaces: TStringGrid
        Left = 8
        Top = 232
        Width = 385
        Height = 81
        DefaultColWidth = 32
        DefaultRowHeight = 16
        RowCount = 2
        TabOrder = 2
      end
    end
    object TabMaterials: TTabSheet
      Caption = 'Materials'
      ImageIndex = 1
      object Material: TComboBox
        Left = 8
        Top = 8
        Width = 385
        Height = 21
        Style = csDropDownList
        ItemHeight = 0
        TabOrder = 0
        OnChange = MaterialChange
      end
      object MatProperties: TStringGrid
        Left = 8
        Top = 40
        Width = 385
        Height = 249
        DefaultColWidth = 75
        DefaultRowHeight = 16
        RowCount = 12
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goEditing]
        TabOrder = 1
      end
      object MatEffect: TComboBox
        Left = 8
        Top = 296
        Width = 385
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 2
        Items.Strings = (
          'None effect'
          'Normal mapping'
          'Parallax mapping')
      end
    end
  end
  object CmdCancel: TButton
    Left = 8
    Top = 504
    Width = 75
    Height = 25
    Caption = '&Cancel'
    TabOrder = 3
    OnClick = CmdCancelClick
  end
  object CmdRestore: TButton
    Left = 96
    Top = 504
    Width = 75
    Height = 25
    Caption = '&Restore'
    TabOrder = 4
    OnClick = CmdRestoreClick
  end
  object CmdApply: TButton
    Left = 256
    Top = 504
    Width = 75
    Height = 25
    Caption = 'A&pply'
    TabOrder = 5
    OnClick = CmdApplyClick
  end
  object CmdAccept: TButton
    Left = 344
    Top = 504
    Width = 75
    Height = 25
    Caption = '&Accept'
    TabOrder = 6
    OnClick = CmdAcceptClick
  end
end
