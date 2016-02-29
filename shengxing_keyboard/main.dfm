object Form2: TForm2
  Left = 0
  Top = 0
  ParentCustomHint = False
  BiDiMode = bdLeftToRight
  BorderStyle = bsNone
  Caption = 'ShengXingKeyboard'
  ClientHeight = 653
  ClientWidth = 300
  Color = clSkyBlue
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  ParentBiDiMode = False
  Position = poDesigned
  OnClose = FormClose
  OnCreate = FormCreate
  OnDblClick = FormDblClick
  PixelsPerInch = 96
  TextHeight = 13
  object pnlcontent: TPanel
    Left = 0
    Top = 0
    Width = 300
    Height = 649
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 0
  end
  object con1: TMyConnection
    Left = 344
    Top = 120
  end
  object qry1: TMyQuery
    Connection = con1
    Left = 344
    Top = 184
  end
end
