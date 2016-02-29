object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'BCB Curl'
  ClientHeight = 606
  ClientWidth = 730
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  DesignSize = (
    730
    606)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    AlignWithMargins = True
    Left = 100
    Top = 184
    Width = 624
    Height = 13
    Margins.Left = 100
    Margins.Right = 6
    Align = alTop
    Caption = 'Label1'
    ExplicitLeft = 89
    ExplicitTop = 203
    ExplicitWidth = 31
  end
  object Label2: TLabel
    Left = 8
    Top = 7
    Width = 19
    Height = 13
    Caption = 'URL'
  end
  object Label3: TLabel
    Left = 8
    Top = 34
    Width = 17
    Height = 13
    Caption = 'Ref'
  end
  object Label4: TLabel
    Left = 8
    Top = 61
    Width = 32
    Height = 13
    Caption = 'Outfile'
  end
  object Label5: TLabel
    Left = 8
    Top = 88
    Width = 46
    Height = 13
    Caption = 'Outfolder'
  end
  object Label6: TLabel
    AlignWithMargins = True
    Left = 100
    Top = 165
    Width = 624
    Height = 13
    Margins.Left = 100
    Margins.Right = 6
    Align = alTop
    Caption = 'Label6'
    ExplicitLeft = 89
    ExplicitTop = 184
    ExplicitWidth = 31
  end
  object Label7: TLabel
    Left = 8
    Top = 115
    Width = 32
    Height = 13
    Caption = 'Cookie'
  end
  object Splitter1: TSplitter
    AlignWithMargins = True
    Left = 100
    Top = 405
    Width = 627
    Height = 3
    Cursor = crVSplit
    Margins.Left = 100
    Align = alBottom
    ExplicitLeft = -8
    ExplicitTop = 328
    ExplicitWidth = 639
  end
  object Label8: TLabel
    Left = 8
    Top = 142
    Width = 45
    Height = 13
    Caption = 'Comment'
  end
  object Memo1: TMemo
    AlignWithMargins = True
    Left = 100
    Top = 206
    Width = 624
    Height = 193
    Margins.Left = 100
    Margins.Top = 6
    Margins.Right = 6
    Align = alClient
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Consolas'
    Font.Style = []
    Lines.Strings = (
      'Memo1')
    ParentFont = False
    ScrollBars = ssBoth
    TabOrder = 0
    WordWrap = False
    ExplicitTop = 220
    ExplicitWidth = 533
    ExplicitHeight = 132
  end
  object cbHeader: TCheckBox
    Left = 8
    Top = 229
    Width = 81
    Height = 17
    Caption = 'Headers only'
    TabOrder = 1
  end
  object ComboBox1: TComboBox
    AlignWithMargins = True
    Left = 100
    Top = 3
    Width = 624
    Height = 21
    Margins.Left = 100
    Margins.Right = 6
    Align = alTop
    TabOrder = 2
    Text = 'ComboBox1'
    Items.Strings = (
      
        'http://i0.wp.com/fundersandfounders.com/wp-content/uploads/2013/' +
        '07/how-startup-valuation-works-infographic.png?resize=660%2C2849'
      '2'
      '3'
      '4'
      '5'
      '6'
      '7'
      '8'
      '9'
      '10')
    ExplicitLeft = 89
    ExplicitWidth = 542
  end
  object btDownload: TButton
    Left = 8
    Top = 187
    Width = 75
    Height = 25
    Caption = 'Download'
    TabOrder = 3
    OnClick = btDownloadClick
  end
  object edOutfile: TEdit
    AlignWithMargins = True
    Left = 100
    Top = 57
    Width = 624
    Height = 21
    Margins.Left = 100
    Margins.Right = 6
    Align = alTop
    TabOrder = 4
    ExplicitLeft = 89
    ExplicitWidth = 542
  end
  object edReferer: TEdit
    AlignWithMargins = True
    Left = 100
    Top = 30
    Width = 624
    Height = 21
    Margins.Left = 100
    Margins.Right = 6
    Align = alTop
    TabOrder = 5
    Text = 'edReferer'
    ExplicitLeft = 95
  end
  object Memo2: TMemo
    AlignWithMargins = True
    Left = 100
    Top = 414
    Width = 624
    Height = 189
    Margins.Left = 100
    Margins.Right = 6
    Align = alBottom
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Consolas'
    Font.Style = []
    Lines.Strings = (
      'Memo1')
    ParentFont = False
    ScrollBars = ssBoth
    TabOrder = 6
    WordWrap = False
    ExplicitLeft = 95
    ExplicitTop = 367
    ExplicitWidth = 533
  end
  object cbPause: TCheckBox
    Left = 8
    Top = 252
    Width = 65
    Height = 17
    Hint = 'Pause after current download'
    Caption = 'Pause'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 7
  end
  object edOutFolder: TEdit
    AlignWithMargins = True
    Left = 100
    Top = 84
    Width = 540
    Height = 21
    Margins.Left = 100
    Margins.Right = 90
    Align = alTop
    TabOrder = 8
    ExplicitLeft = 89
    ExplicitWidth = 454
  end
  object btBrowseFolder: TButton
    Left = 642
    Top = 82
    Width = 80
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'Browse'
    TabOrder = 9
    OnClick = btBrowseFolderClick
    ExplicitLeft = 551
  end
  object edCookie: TEdit
    AlignWithMargins = True
    Left = 100
    Top = 111
    Width = 624
    Height = 21
    Margins.Left = 100
    Margins.Right = 6
    Align = alTop
    TabOrder = 10
    ExplicitLeft = 89
    ExplicitTop = 113
    ExplicitWidth = 542
  end
  object edComment: TEdit
    AlignWithMargins = True
    Left = 100
    Top = 138
    Width = 540
    Height = 21
    Margins.Left = 100
    Margins.Right = 90
    Align = alTop
    TabOrder = 11
    ExplicitLeft = 89
    ExplicitTop = 140
    ExplicitWidth = 454
  end
  object CheckBox1: TCheckBox
    Left = 657
    Top = 142
    Width = 65
    Height = 17
    Anchors = [akTop, akRight]
    Caption = 'Use this'
    TabOrder = 12
    OnClick = CheckBox1Click
    ExplicitLeft = 566
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 500
    OnTimer = Timer1Timer
    Left = 48
    Top = 336
  end
  object FileOpenDialog1: TFileOpenDialog
    FavoriteLinks = <>
    FileTypes = <>
    Options = [fdoPickFolders]
    Left = 16
    Top = 336
  end
end
