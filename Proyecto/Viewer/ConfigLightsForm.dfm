object ConfigLightsWnd: TConfigLightsWnd
  Left = 783
  Top = 185
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Configure Lights'
  ClientHeight = 498
  ClientWidth = 402
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object LblEnable: TLabel
    Left = 16
    Top = 24
    Width = 75
    Height = 13
    Caption = 'Enable lighting: '
  end
  object LblAmbient: TLabel
    Left = 16
    Top = 56
    Width = 70
    Height = 13
    Caption = 'Ambient color: '
  end
  object EnableLighting: TComboBox
    Left = 104
    Top = 16
    Width = 281
    Height = 21
    ItemHeight = 13
    TabOrder = 0
    OnChange = EnableLightingChange
    Items.Strings = (
      'true'
      'false')
  end
  object Ambient: TEdit
    Left = 104
    Top = 48
    Width = 281
    Height = 21
    MaxLength = 20
    TabOrder = 1
    OnEnter = AmbientEnter
    OnExit = AmbientExit
    OnKeyDown = AmbientKeyDown
  end
  object GBLights: TGroupBox
    Left = 16
    Top = 88
    Width = 369
    Height = 361
    Caption = ' Lights Properties '
    TabOrder = 2
    object LblLightAmbient: TLabel
      Left = 16
      Top = 56
      Width = 44
      Height = 13
      Caption = 'Ambient: '
    end
    object LblLightDiffuse: TLabel
      Left = 16
      Top = 80
      Width = 39
      Height = 13
      Caption = 'Diffuse: '
    end
    object LblLightSpecular: TLabel
      Left = 16
      Top = 104
      Width = 48
      Height = 13
      Caption = 'Specular: '
    end
    object LblLightPosition: TLabel
      Left = 16
      Top = 128
      Width = 43
      Height = 13
      Caption = 'Position: '
    end
    object LblLight: TLabel
      Left = 16
      Top = 24
      Width = 26
      Height = 13
      Caption = 'Light:'
    end
    object LblLightSpotDirection: TLabel
      Left = 16
      Top = 160
      Width = 71
      Height = 13
      Caption = 'Spot direction: '
    end
    object LblLightSpotExponent: TLabel
      Left = 16
      Top = 184
      Width = 75
      Height = 13
      Caption = 'Spot exponent: '
    end
    object LblLightSpotCutoff: TLabel
      Left = 16
      Top = 208
      Width = 64
      Height = 13
      Caption = 'Spot Cut-Off: '
    end
    object LblLightConstant: TLabel
      Left = 16
      Top = 248
      Width = 104
      Height = 13
      Caption = 'Constant attenuation: '
    end
    object LblLightLinear: TLabel
      Left = 16
      Top = 272
      Width = 91
      Height = 13
      Caption = 'Linear attenuation: '
    end
    object LblLightQuadratic: TLabel
      Left = 16
      Top = 296
      Width = 108
      Height = 13
      Caption = 'Quadratic attenuation: '
    end
    object LblLightEnable: TLabel
      Left = 16
      Top = 328
      Width = 58
      Height = 13
      Caption = 'Enable light:'
    end
    object LightAmbient: TEdit
      Left = 136
      Top = 56
      Width = 217
      Height = 21
      MaxLength = 20
      TabOrder = 1
      OnEnter = LightAmbientEnter
      OnExit = LightAmbientExit
      OnKeyDown = LightAmbientKeyDown
    end
    object LightDiffuse: TEdit
      Left = 136
      Top = 80
      Width = 217
      Height = 21
      MaxLength = 20
      TabOrder = 2
      OnEnter = LightDiffuseEnter
      OnExit = LightDiffuseExit
      OnKeyDown = LightDiffuseKeyDown
    end
    object LightSpecular: TEdit
      Left = 136
      Top = 104
      Width = 217
      Height = 21
      MaxLength = 20
      TabOrder = 3
      OnEnter = LightSpecularEnter
      OnExit = LightSpecularExit
      OnKeyDown = LightSpecularKeyDown
    end
    object LightPosition: TEdit
      Left = 136
      Top = 128
      Width = 217
      Height = 21
      MaxLength = 80
      TabOrder = 4
      OnEnter = LightPositionEnter
      OnExit = LightPositionExit
      OnKeyDown = LightPositionKeyDown
    end
    object Light: TComboBox
      Left = 136
      Top = 24
      Width = 217
      Height = 21
      ItemHeight = 13
      TabOrder = 0
      Text = 'GL_LIGHT0'
      OnChange = LightChange
      Items.Strings = (
        'GL_LIGHT0'
        'GL_LIGHT1'
        'GL_LIGHT2'
        'GL_LIGHT3'
        'GL_LIGHT4'
        'GL_LIGHT5'
        'GL_LIGHT6'
        'GL_LIGHT7')
    end
    object LightSpotDirection: TEdit
      Left = 136
      Top = 160
      Width = 217
      Height = 21
      MaxLength = 80
      TabOrder = 5
      OnEnter = LightSpotDirectionEnter
      OnExit = LightSpotDirectionExit
      OnKeyDown = LightSpotDirectionKeyDown
    end
    object LightSpotExponent: TEdit
      Left = 136
      Top = 184
      Width = 217
      Height = 21
      MaxLength = 20
      TabOrder = 6
      OnEnter = LightSpotExponentEnter
      OnExit = LightSpotExponentExit
      OnKeyDown = LightSpotExponentKeyDown
    end
    object LightSpotCutoff: TEdit
      Left = 136
      Top = 208
      Width = 217
      Height = 21
      MaxLength = 20
      TabOrder = 7
      OnEnter = LightSpotCutoffEnter
      OnExit = LightSpotCutoffExit
      OnKeyDown = LightSpotCutoffKeyDown
    end
    object LightConstant: TEdit
      Left = 136
      Top = 240
      Width = 217
      Height = 21
      MaxLength = 20
      TabOrder = 8
      OnEnter = LightConstantEnter
      OnExit = LightConstantExit
      OnKeyDown = LightConstantKeyDown
    end
    object LightLinear: TEdit
      Left = 136
      Top = 264
      Width = 217
      Height = 21
      MaxLength = 20
      TabOrder = 9
      OnEnter = LightLinearEnter
      OnExit = LightLinearExit
      OnKeyDown = LightLinearKeyDown
    end
    object LightQuadratic: TEdit
      Left = 136
      Top = 288
      Width = 217
      Height = 21
      MaxLength = 20
      TabOrder = 10
      OnEnter = LightQuadraticEnter
      OnExit = LightQuadraticExit
      OnKeyDown = LightQuadraticKeyDown
    end
    object LightEnable: TComboBox
      Left = 136
      Top = 320
      Width = 217
      Height = 21
      ItemHeight = 13
      TabOrder = 11
      OnChange = LightEnableChange
      Items.Strings = (
        'true'
        'false')
    end
  end
  object CmdLoad: TButton
    Left = 16
    Top = 456
    Width = 75
    Height = 25
    Caption = '&Load'
    TabOrder = 3
    OnClick = CmdLoadClick
  end
  object CmdSave: TButton
    Left = 104
    Top = 456
    Width = 75
    Height = 25
    Caption = '&Save'
    TabOrder = 4
    OnClick = CmdSaveClick
  end
  object CmdCancel: TButton
    Left = 224
    Top = 456
    Width = 75
    Height = 25
    Caption = '&Cancel'
    TabOrder = 5
    OnClick = CmdCancelClick
  end
  object CmdAccept: TButton
    Left = 312
    Top = 456
    Width = 75
    Height = 25
    Caption = '&Accept'
    TabOrder = 6
    OnClick = CmdAcceptClick
  end
  object OpenDialog: TOpenDialog
    Filter = 'Config File (*.cfg)|*.cfg|All Files (*.*)|*.*'
    Left = 312
    Top = 72
  end
  object SaveDialog: TSaveDialog
    Filter = 'Config File (*.cfg)|*.cfg|All Files (*.*)|*.*'
    Left = 352
    Top = 72
  end
end
