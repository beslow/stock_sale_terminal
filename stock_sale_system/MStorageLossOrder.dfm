object StorageLossOrder: TStorageLossOrder
  Left = 350
  Top = 20
  Caption = #20179#24211#25439#32791
  ClientHeight = 557
  ClientWidth = 636
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
  object Label1: TLabel
    Left = 314
    Top = 25
    Width = 72
    Height = 13
    Caption = #20179#24211#25439#32791#26085#26399
  end
  object Label2: TLabel
    Left = 145
    Top = 25
    Width = 36
    Height = 13
    Caption = #37319#36141#33258
  end
  object StorageLossStringGrid: TStringGrid
    Left = 33
    Top = 49
    Width = 376
    Height = 715
    RowCount = 100
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goDrawFocusSelected, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goTabs]
    TabOrder = 0
    OnSelectCell = StorageLossStringGridSelectCell
  end
  object DateTimePicker1: TDateTimePicker
    Left = 392
    Top = 20
    Width = 113
    Height = 21
    Date = 42309.850609618060000000
    Time = 42309.850609618060000000
    ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 1
  end
  object BitBtn1: TBitBtn
    Left = 456
    Top = 128
    Width = 75
    Height = 25
    Caption = #24405#20837#25439#32791
    TabOrder = 2
    OnClick = BitBtn1Click
  end
  object SLSellerName: TEdit
    Left = 187
    Top = 22
    Width = 121
    Height = 21
    ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 3
    OnChange = SLSellerNameChange
    OnClick = SLSellerNameClick
  end
  object auto_next: TCheckBox
    Left = 528
    Top = 24
    Width = 97
    Height = 17
    Caption = #33258#21160#25442#34892
    TabOrder = 4
  end
  object LossType: TComboBox
    Left = 8
    Top = 22
    Width = 131
    Height = 21
    ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 5
    Text = #35831#20808#36873#25321#25439#32791#31867#21035
    OnChange = LossTypeChange
    Items.Strings = (
      #20179#24211#25439#32791
      #38144#21806#25439#32791)
  end
  object Qry: TMyQuery
    Connection = MainForm.Connection
    Left = 400
    Top = 8
  end
  object Cmd: TMyCommand
    Connection = MainForm.Connection
    Left = 496
    Top = 8
  end
  object Timer1: TTimer
    Interval = 500
    OnTimer = Timer1Timer
    Left = 448
    Top = 40
  end
end
