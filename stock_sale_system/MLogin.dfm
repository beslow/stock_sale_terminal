object Login: TLogin
  Left = 500
  Top = 300
  Caption = '591'#24211#23384'20151201'
  ClientHeight = 266
  ClientWidth = 275
  Color = clSkyBlue
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 48
    Width = 72
    Height = 13
    Caption = #29992#25143#21517#25110#37038#31665
  end
  object Label2: TLabel
    Left = 55
    Top = 88
    Width = 24
    Height = 13
    Caption = #23494#30721
  end
  object message: TLabel
    Left = 136
    Top = 128
    Width = 113
    Height = 89
    AutoSize = False
    WordWrap = True
  end
  object user_name_or_email: TEdit
    Left = 85
    Top = 45
    Width = 179
    Height = 21
    ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 0
  end
  object terminal_password: TEdit
    Left = 85
    Top = 85
    Width = 179
    Height = 21
    ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    PasswordChar = '*'
    TabOrder = 1
    OnKeyPress = terminal_passwordKeyPress
  end
  object BitBtn1: TBitBtn
    Left = 32
    Top = 152
    Width = 73
    Height = 25
    Caption = #30331#24405
    TabOrder = 2
    OnClick = BitBtn1Click
  end
  object my_con: TMyConnection
    Options.UseUnicode = True
    Left = 24
    Top = 112
  end
  object my_qry: TMyQuery
    Connection = my_con
    Left = 56
    Top = 208
  end
end
