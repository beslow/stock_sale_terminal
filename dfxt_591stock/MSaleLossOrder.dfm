object SaleLossOrder: TSaleLossOrder
  Left = 350
  Top = 20
  Caption = #36865#36135#25439#32791
  ClientHeight = 453
  ClientWidth = 681
  Color = clSkyBlue
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDesigned
  Visible = True
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object SaleLossStringGrid: TStringGrid
    Left = 24
    Top = 32
    Width = 481
    Height = 715
    ColCount = 7
    RowCount = 100
    TabOrder = 0
  end
  object Qry: TMyQuery
    Connection = MainForm.Connection
    Left = 544
    Top = 16
  end
  object Cmd: TMyCommand
    Connection = MainForm.Connection
    Left = 592
    Top = 16
  end
  object Timer1: TTimer
    Interval = 500
    OnTimer = Timer1Timer
    Left = 632
    Top = 16
  end
end
