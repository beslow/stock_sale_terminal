object PrintOrder: TPrintOrder
  Left = 350
  Top = 20
  Caption = #25171#21360#21333#25454
  ClientHeight = 774
  ClientWidth = 975
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
  OnKeyDown = CompanyNameKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 24
    Width = 24
    Height = 13
    Caption = #21333#20301
  end
  object Label2: TLabel
    Left = 24
    Top = 48
    Width = 24
    Height = 13
    Caption = #38376#24215
    OnDblClick = StoreDblClick
  end
  object Label3: TLabel
    Left = 200
    Top = 24
    Width = 48
    Height = 13
    Caption = #21333#25454#31867#22411
    OnDblClick = OrderTypeDblClick
  end
  object Label4: TLabel
    Left = 200
    Top = 48
    Width = 48
    Height = 13
    Caption = #35746#36135#26085#26399
  end
  object Label5: TLabel
    Left = 376
    Top = 48
    Width = 48
    Height = 13
    Caption = #21040#36135#26085#26399
  end
  object Label6: TLabel
    Left = 381
    Top = 25
    Width = 36
    Height = 13
    Caption = #25805#20316#21592
  end
  object Label9: TLabel
    Left = 24
    Top = 100
    Width = 73
    Height = 53
    AutoSize = False
    WordWrap = True
  end
  object Label10: TLabel
    Left = 511
    Top = 180
    Width = 81
    Height = 26
    AutoSize = False
    WordWrap = True
  end
  object Label15: TLabel
    Left = 11
    Top = 8
    Width = 3
    Height = 13
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label16: TLabel
    Left = 536
    Top = 368
    Width = 48
    Height = 13
    Caption = #27492#21333#22791#27880
  end
  object CompanyName: TEdit
    Left = 54
    Top = 21
    Width = 121
    Height = 21
    ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ReadOnly = True
    TabOrder = 0
    OnChange = CompanyNameChange
    OnClick = CompanyNameClick
    OnKeyDown = CompanyNameKeyDown
  end
  object Store: TEdit
    Left = 54
    Top = 45
    Width = 121
    Height = 21
    ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ReadOnly = True
    TabOrder = 1
    OnChange = CompanyNameChange
    OnClick = StoreClick
    OnDblClick = StoreDblClick
    OnEnter = StoreClick
    OnKeyDown = CompanyNameKeyDown
  end
  object OrderType: TEdit
    Left = 254
    Top = 21
    Width = 121
    Height = 21
    ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ReadOnly = True
    TabOrder = 2
    OnChange = CompanyNameChange
    OnClick = OrderTypeClick
    OnDblClick = OrderTypeDblClick
    OnEnter = OrderTypeClick
    OnKeyDown = CompanyNameKeyDown
  end
  object SendOrderTime: TDateTimePicker
    Left = 254
    Top = 43
    Width = 121
    Height = 21
    Date = 41979.690449027780000000
    Time = 41979.690449027780000000
    ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 3
    TabStop = False
    OnKeyDown = CompanyNameKeyDown
  end
  object ReachOrderTime: TDateTimePicker
    Left = 430
    Top = 45
    Width = 121
    Height = 21
    Date = 41979.690449027780000000
    Time = 41979.690449027780000000
    ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 4
    TabStop = False
    OnChange = ReachOrderTimeChange
    OnKeyDown = CompanyNameKeyDown
  end
  object InputGrid: TStringGrid
    Left = 24
    Top = 70
    Width = 481
    Height = 715
    Color = clSkyBlue
    ColCount = 7
    Enabled = False
    RowCount = 100
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goDrawFocusSelected, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goTabs]
    TabOrder = 5
    OnKeyDown = CompanyNameKeyDown
    OnKeyPress = InputGridKeyPress
    OnSelectCell = InputGridSelectCell
    RowHeights = (
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24)
  end
  object OperatorName: TEdit
    Left = 430
    Top = 21
    Width = 121
    Height = 21
    Enabled = False
    ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 6
    OnClick = CompanyNameClick
    OnKeyDown = CompanyNameKeyDown
  end
  object BtnPrint: TBitBtn
    Left = 511
    Top = 503
    Width = 81
    Height = 41
    Caption = #25171#21360'(C+R)'
    Enabled = False
    TabOrder = 7
    Visible = False
    OnClick = BtnPrintClick
    OnKeyDown = CompanyNameKeyDown
  end
  object BitBtn1: TBitBtn
    Left = 511
    Top = 455
    Width = 81
    Height = 42
    Caption = #39044#35272'(C+P)'
    Enabled = False
    TabOrder = 8
    Visible = False
    OnClick = BitBtn1Click
    OnKeyDown = CompanyNameKeyDown
  end
  object chk_default_printer: TCheckBox
    Left = 511
    Top = 88
    Width = 106
    Height = 17
    Caption = #20351#29992#40664#35748#25171#21360#26426
    Checked = True
    Color = clBlue
    ParentColor = False
    State = cbChecked
    TabOrder = 9
    OnKeyDown = CompanyNameKeyDown
  end
  object BitBtn2: TBitBtn
    Left = 511
    Top = 407
    Width = 81
    Height = 42
    Caption = #33719#21462#24050#25171#21360
    Enabled = False
    TabOrder = 10
    Visible = False
    OnClick = BitBtn2Click
    OnKeyDown = CompanyNameKeyDown
  end
  object BitBtn3: TBitBtn
    Left = 511
    Top = 312
    Width = 81
    Height = 42
    Caption = #28165#31354'(C+O)'
    Enabled = False
    TabOrder = 11
    OnClick = BitBtn3Click
    OnKeyDown = CompanyNameKeyDown
  end
  object Panel1: TPanel
    Left = 511
    Top = 551
    Width = 106
    Height = 147
    TabOrder = 12
    Visible = False
    object Label7: TLabel
      Left = 14
      Top = 15
      Width = 60
      Height = 13
      Caption = #26032#22686#21697#39033#21517
    end
    object message: TLabel
      Left = 8
      Top = 92
      Width = 73
      Height = 53
      AutoSize = False
      WordWrap = True
    end
    object will_add: TEdit
      Left = 9
      Top = 34
      Width = 81
      Height = 21
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 0
      OnKeyDown = CompanyNameKeyDown
      OnKeyPress = will_addKeyPress
    end
    object BitBtn4: TBitBtn
      Left = 8
      Top = 61
      Width = 81
      Height = 25
      Caption = #28155#21152
      TabOrder = 1
      OnClick = BitBtn4Click
      OnKeyDown = CompanyNameKeyDown
    end
  end
  object Panel2: TPanel
    Left = 623
    Top = 551
    Width = 216
    Height = 500
    TabOrder = 13
    Visible = False
    object Label8: TLabel
      Left = 0
      Top = 16
      Width = 96
      Height = 13
      Caption = #35831#36755#20837#23383#27597#32553#20889#8595
      Visible = False
    end
    object Label13: TLabel
      Left = 166
      Top = 16
      Width = 36
      Height = 13
      Caption = #20215#26684#8595
    end
    object Label14: TLabel
      Left = 118
      Top = 16
      Width = 36
      Height = 13
      Caption = #35268#26684#8595
    end
    object edit: TEdit
      Left = 16
      Top = 35
      Width = 73
      Height = 21
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 0
      Visible = False
      OnKeyDown = CompanyNameKeyDown
    end
    object BitBtn5: TBitBtn
      Left = 16
      Top = 62
      Width = 75
      Height = 25
      Caption = #28155#21152
      TabOrder = 3
      Visible = False
      OnClick = BitBtn5Click
      OnKeyDown = CompanyNameKeyDown
    end
    object Edit2: TEdit
      Left = 111
      Top = 35
      Width = 42
      Height = 21
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 1
      OnKeyDown = CompanyNameKeyDown
    end
    object Edit3: TEdit
      Left = 159
      Top = 35
      Width = 49
      Height = 21
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 2
      OnKeyDown = CompanyNameKeyDown
    end
    object Panel4: TPanel
      Left = 97
      Top = 0
      Width = 8
      Height = 265
      Color = clBtnText
      ParentBackground = False
      TabOrder = 4
    end
  end
  object BitBtn6: TBitBtn
    Left = 511
    Top = 216
    Width = 81
    Height = 42
    Caption = #20445#23384'(C+S)'
    Enabled = False
    TabOrder = 14
    OnClick = BitBtn6Click
    OnKeyDown = CompanyNameKeyDown
  end
  object BitBtn7: TBitBtn
    Left = 511
    Top = 264
    Width = 81
    Height = 42
    Caption = #33719#21462#24050#20445#23384
    Enabled = False
    TabOrder = 15
    Visible = False
    OnClick = BitBtn2Click
    OnKeyDown = CompanyNameKeyDown
  end
  object Panel3: TPanel
    Left = 631
    Top = 131
    Width = 314
    Height = 402
    TabOrder = 16
    object Label11: TLabel
      Left = 48
      Top = 13
      Width = 82
      Height = 13
      Caption = '1.'#20808#36755#20837#21697#39033#21517
    end
    object Label12: TLabel
      Left = 48
      Top = 58
      Width = 118
      Height = 13
      Caption = '1.'#20877#28857#20987#21442#32771#20197#24448#20215#26684
    end
    object BitBtn8: TBitBtn
      Left = 56
      Top = 77
      Width = 81
      Height = 42
      Caption = #21442#32771#20197#24448#20215#26684
      TabOrder = 0
      OnClick = BitBtn8Click
      OnKeyDown = CompanyNameKeyDown
    end
    object Edit1: TEdit
      Left = 56
      Top = 32
      Width = 73
      Height = 21
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 1
      OnKeyDown = CompanyNameKeyDown
      OnKeyPress = Edit1KeyPress
    end
    object StringGrid1: TStringGrid
      Left = 8
      Top = 125
      Width = 305
      Height = 31
      FixedCols = 0
      RowCount = 1
      FixedRows = 0
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goRowSelect]
      TabOrder = 2
      OnKeyDown = CompanyNameKeyDown
      RowHeights = (
        24)
    end
  end
  object auto_next: TCheckBox
    Left = 511
    Top = 157
    Width = 106
    Height = 17
    Caption = #28857#36873#21518#33258#21160#25442#34892
    Checked = True
    State = cbChecked
    TabOrder = 17
    OnKeyDown = CompanyNameKeyDown
  end
  object BitBtn9: TBitBtn
    Left = 511
    Top = 360
    Width = 81
    Height = 41
    Caption = #20316#24223
    Enabled = False
    TabOrder = 18
    Visible = False
    OnClick = BitBtn9Click
    OnKeyDown = CompanyNameKeyDown
  end
  object Memo1: TMemo
    Left = 623
    Top = 69
    Width = 137
    Height = 25
    ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 19
    OnKeyDown = CompanyNameKeyDown
  end
  object Button3: TButton
    Left = 766
    Top = 66
    Width = 75
    Height = 27
    Caption = #25172#36827#34920#21333
    TabOrder = 20
    OnClick = Button3Click
    OnKeyDown = CompanyNameKeyDown
  end
  object Button4: TButton
    Left = 840
    Top = 67
    Width = 58
    Height = 25
    Caption = #35299#26512
    TabOrder = 21
    OnClick = Button4Click
    OnKeyDown = CompanyNameKeyDown
  end
  object Button5: TButton
    Left = 623
    Top = 100
    Width = 166
    Height = 25
    Caption = #23454#38469#37327'='#35746#36135#37327
    TabOrder = 22
    OnClick = Button5Click
    OnKeyDown = CompanyNameKeyDown
  end
  object auto_fill: TCheckBox
    Left = 511
    Top = 111
    Width = 97
    Height = 17
    Caption = #33258#21160#22635#20889#21697#21517
    TabOrder = 23
    OnKeyDown = CompanyNameKeyDown
  end
  object strong_insert: TCheckBox
    Left = 511
    Top = 134
    Width = 114
    Height = 17
    Caption = #26597#21040#22810#20010#36873#31532#19968#20010
    TabOrder = 24
    OnKeyDown = CompanyNameKeyDown
  end
  object Button2: TButton
    Left = 1100
    Top = 224
    Width = 93
    Height = 25
    Caption = #20108#12289#22635#20837#34920#21333
    TabOrder = 25
  end
  object Memo2: TMemo
    Left = 511
    Top = 392
    Width = 114
    Height = 153
    ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 26
  end
  object Qry: TMyQuery
    Connection = MainForm.Connection
    SQL.Strings = (
      'select * from products')
    Active = True
    Left = 608
    Top = 24
  end
  object Timer1: TTimer
    Interval = 500
    OnTimer = Timer1Timer
    Left = 576
    Top = 24
  end
  object frxReport: TfrxReport
    Version = '5.1.5'
    DataSet = frxTitleData
    DataSetName = 'frxTitleData'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = 'Default'
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 41982.921686550900000000
    ReportOptions.LastChange = 42288.861436863420000000
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      ''
      'begin'
      ''
      'end.')
    OnGetValue = frxReportGetValue
    Left = 696
    Top = 24
    Datasets = <
      item
        DataSet = frxDetailData
        DataSetName = 'frxDetailData'
      end
      item
        DataSet = frxTitleData
        DataSetName = 'frxTitleData'
      end>
    Variables = <
      item
        Name = ' my_variables'
        Value = Null
      end
      item
        Name = 'company_name'
        Value = '<company_name>'
      end
      item
        Name = 'store_name'
        Value = '<store_name>'
      end
      item
        Name = 'reach_date'
        Value = Null
      end>
    Style = <>
    object Data: TfrxDataPage
      Height = 1000.000000000000000000
      Width = 1000.000000000000000000
    end
    object Page1: TfrxReportPage
      PaperWidth = 120.000000000000000000
      PaperHeight = 400.000000000000000000
      PaperSize = 256
      LeftMargin = 10.000000000000000000
      RightMargin = 10.000000000000000000
      TopMargin = 10.000000000000000000
      BottomMargin = 10.000000000000000000
      object ReportTitle1: TfrxReportTitle
        FillType = ftBrush
        Height = 117.165354330709000000
        Top = 18.897650000000000000
        Width = 377.953000000000000000
        object frxTitleDatacompany_name: TfrxMemoView
          Top = 18.897637800000000000
          Width = 226.771653540000000000
          Height = 26.456692910000000000
          DataSet = frxTitleData
          DataSetName = 'frxTitleData'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -19
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftBottom]
          Memo.UTF8W = (
            '[frxTitleData."company_name"]')
          ParentFont = False
        end
        object frxTitleDatastore_name: TfrxMemoView
          Top = 45.354330710000000000
          Width = 226.771800000000000000
          Height = 26.456692910000000000
          DataSet = frxTitleData
          DataSetName = 'frxTitleData'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -19
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftBottom]
          Memo.UTF8W = (
            '[frxTitleData."store_name"]')
          ParentFont = False
        end
        object frxTitleDatareach_date: TfrxMemoView
          Left = 226.771653540000000000
          Top = 18.897637800000000000
          Width = 132.283464570000000000
          Height = 26.456692910000000000
          DataSet = frxTitleData
          DataSetName = 'frxTitleData'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -19
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            '[frxTitleData."reach_date"]')
          ParentFont = False
        end
        object frxTitleDataorder_type: TfrxMemoView
          Left = 226.771653540000000000
          Top = 45.354330710000000000
          Width = 132.283464570000000000
          Height = 26.456692910000000000
          DataSet = frxTitleData
          DataSetName = 'frxTitleData'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -19
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            '[frxTitleData."order_type"]')
          ParentFont = False
        end
        object frxTitleDataorder_id: TfrxMemoView
          Left = 45.354330710000000000
          Top = 71.811023620000000000
          Width = 68.031496060000000000
          Height = 18.897650000000000000
          DataSet = frxTitleData
          DataSetName = 'frxTitleData'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            '[frxTitleData."order_id"]')
          ParentFont = False
        end
        object frxTitleDatacompany_id: TfrxMemoView
          Left = 158.740157480000000000
          Top = 71.811023620000000000
          Width = 68.031496060000000000
          Height = 18.897650000000000000
          DataSet = frxTitleData
          DataSetName = 'frxTitleData'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftRight, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            '[frxTitleData."company_id"]')
          ParentFont = False
        end
        object frxTitleDataprinter: TfrxMemoView
          Left = 272.125984250000000000
          Top = 71.811023620000000000
          Width = 86.929133860000000000
          Height = 18.897650000000000000
          DataSet = frxTitleData
          DataSetName = 'frxTitleData'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftRight, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            '[frxTitleData."printer"]')
          ParentFont = False
        end
        object Memo2: TfrxMemoView
          Width = 359.055118110000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            '[frxTitleData."supplier_name"]')
          ParentFont = False
        end
        object Memo1: TfrxMemoView
          Top = 71.811023620000000000
          Width = 45.354360000000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            #21333#25454'ID')
          ParentFont = False
          VAlign = vaBottom
        end
        object Memo3: TfrxMemoView
          Left = 113.385826770000000000
          Top = 71.811023620000000000
          Width = 45.354330710000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            #23458#25143'ID')
          ParentFont = False
          VAlign = vaBottom
        end
        object Memo4: TfrxMemoView
          Left = 226.771800000000000000
          Top = 71.811023620000000000
          Width = 45.354330710000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            #25805#20316#32773)
          ParentFont = False
          VAlign = vaBottom
        end
        object Memo21: TfrxMemoView
          Top = 98.267780000000000000
          Width = 98.267728740000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = -2147483640
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop]
          HAlign = haCenter
          Memo.UTF8W = (
            #20135#21697#21517#31216)
          ParentFont = False
        end
        object Memo22: TfrxMemoView
          Left = 98.267716540000000000
          Top = 98.267780000000000000
          Width = 56.692913390000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = -2147483640
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop]
          HAlign = haCenter
          Memo.UTF8W = (
            #35268#26684)
          ParentFont = False
        end
        object Memo23: TfrxMemoView
          Left = 154.960629920000000000
          Top = 98.267780000000000000
          Width = 56.692925590000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = -2147483640
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop]
          HAlign = haCenter
          Memo.UTF8W = (
            #35746#37327)
          ParentFont = False
        end
        object Memo24: TfrxMemoView
          Left = 211.653543310000000000
          Top = 98.267780000000000000
          Width = 45.354330710000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = -2147483640
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop]
          HAlign = haCenter
          Memo.UTF8W = (
            #21040#36135#37327)
          ParentFont = False
        end
        object Memo25: TfrxMemoView
          Left = 257.007874020000000000
          Top = 98.267780000000000000
          Width = 37.795275590000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = -2147483640
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop]
          HAlign = haCenter
          Memo.UTF8W = (
            #21333#20215)
          ParentFont = False
        end
        object Memo26: TfrxMemoView
          Left = 294.803149610000000000
          Top = 98.267780000000000000
          Width = 64.251980710000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = -2147483640
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop]
          HAlign = haCenter
          Memo.UTF8W = (
            #37329#39069)
          ParentFont = False
        end
      end
      object MasterData1: TfrxMasterData
        FillType = ftBrush
        Height = 163.622140000000000000
        Top = 196.535560000000000000
        Width = 377.953000000000000000
        DataSet = frxDetailData
        DataSetName = 'frxDetailData'
        RowCount = 0
        Stretched = True
        object frxDetailDataname: TfrxMemoView
          Width = 98.267780000000000000
          Height = 18.897650000000000000
          DataField = 'name'
          DataSet = frxDetailData
          DataSetName = 'frxDetailData'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftTop]
          Frame.LeftLine.Style = fsDot
          Frame.TopLine.Style = fsDot
          Frame.RightLine.Style = fsDot
          Frame.BottomLine.Style = fsDot
          Memo.UTF8W = (
            '[frxDetailData."name"]')
          ParentFont = False
        end
        object frxDetailDataspeci: TfrxMemoView
          Left = 98.267780000000000000
          Width = 56.692950000000000000
          Height = 18.897650000000000000
          DataField = 'speci'
          DataSet = frxDetailData
          DataSetName = 'frxDetailData'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftTop]
          Frame.LeftLine.Style = fsDot
          Frame.TopLine.Style = fsDot
          Frame.RightLine.Style = fsDot
          Frame.BottomLine.Style = fsDot
          Memo.UTF8W = (
            '[frxDetailData."speci"]')
          ParentFont = False
        end
        object frxDetailDataorder_weight: TfrxMemoView
          Left = 154.960730000000000000
          Width = 56.692950000000000000
          Height = 18.897650000000000000
          DataField = 'order_weight'
          DataSet = frxDetailData
          DataSetName = 'frxDetailData'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftTop]
          Frame.LeftLine.Style = fsDot
          Frame.TopLine.Style = fsDot
          Frame.RightLine.Style = fsDot
          Frame.BottomLine.Style = fsDot
          HAlign = haCenter
          Memo.UTF8W = (
            '[frxDetailData."order_weight"]')
          ParentFont = False
        end
        object frxDetailDatareal_weight: TfrxMemoView
          Left = 211.653680000000000000
          Width = 45.354360000000000000
          Height = 18.897650000000000000
          DataField = 'real_weight'
          DataSet = frxDetailData
          DataSetName = 'frxDetailData'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftTop]
          Frame.LeftLine.Style = fsDot
          Frame.TopLine.Style = fsDot
          Frame.RightLine.Style = fsDot
          Frame.BottomLine.Style = fsDot
          HAlign = haCenter
          Memo.UTF8W = (
            '[frxDetailData."real_weight"]')
          ParentFont = False
        end
        object frxDetailDataprice: TfrxMemoView
          Left = 257.008040000000000000
          Width = 37.795300000000000000
          Height = 18.897650000000000000
          DataField = 'price'
          DataSet = frxDetailData
          DataSetName = 'frxDetailData'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftTop]
          Frame.LeftLine.Style = fsDot
          Frame.TopLine.Style = fsDot
          Frame.RightLine.Style = fsDot
          Frame.BottomLine.Style = fsDot
          HAlign = haCenter
          Memo.UTF8W = (
            '[frxDetailData."price"]')
          ParentFont = False
        end
        object frxDetailDatamoney: TfrxMemoView
          Left = 294.803340000000000000
          Width = 64.252010000000000000
          Height = 18.897650000000000000
          DataField = 'money'
          DataSet = frxDetailData
          DataSetName = 'frxDetailData'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop]
          Frame.LeftLine.Style = fsDot
          Frame.TopLine.Style = fsDot
          Frame.RightLine.Style = fsDot
          Frame.BottomLine.Style = fsDot
          HAlign = haCenter
          Memo.UTF8W = (
            '[frxDetailData."money"]')
          ParentFont = False
        end
      end
      object ReportSummary1: TfrxReportSummary
        FillType = ftBrush
        Height = 317.480520000000000000
        Top = 419.527830000000000000
        Width = 377.953000000000000000
        object Memo16: TfrxMemoView
          Width = 56.692913390000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = -2147483640
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            #21512#35745)
          ParentFont = False
        end
        object Memo17: TfrxMemoView
          Left = 56.692913390000000000
          Width = 302.362204720000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = -2147483640
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            '[frxTitleData."total_money"]')
          ParentFont = False
        end
        object Memo18: TfrxMemoView
          Top = 18.897637800000000000
          Width = 359.055118110000000000
          Height = 37.795300000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = -2147483640
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          Memo.UTF8W = (
            #25910#36135#20154#31614#23383)
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo19: TfrxMemoView
          Top = 71.811070000000000000
          Width = 192.755798110000000000
          Height = 181.417440000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = -2147483640
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Memo.UTF8W = (
            #30422#31456#65306)
          ParentFont = False
        end
        object Memo29: TfrxMemoView
          Left = 192.756030000000000000
          Top = 71.811070000000000000
          Width = 166.299320000000000000
          Height = 185.196970000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = -2147483640
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            ''
            #32852#31995#20154#65306#38472#20808#29983'    '
            #25163#26426':13501783676   '
            #24231#26426':021-52353295'
            #37038#31665':1015742224@qq.com            ('#21487#25509#25910#35746#21333')')
          ParentFont = False
        end
      end
    end
  end
  object frxTitleData: TfrxDBDataset
    UserName = 'frxTitleData'
    CloseDataSource = False
    FieldAliases.Strings = (
      'supplier_name=supplier_name'
      'company_name=company_name'
      'store_name=store_name'
      'order_type=order_type'
      'reach_date=reach_date'
      'printer=printer'
      'order_id=order_id'
      'company_id=company_id'
      'total_money=total_money')
    DataSet = MyQuery1
    BCDToCurrency = False
    Left = 624
    Top = 1
  end
  object frxDetailData: TfrxDBDataset
    UserName = 'frxDetailData'
    CloseDataSource = False
    DataSet = MyQuery2
    BCDToCurrency = False
    Left = 768
    Top = 8
  end
  object Cmd: TMyCommand
    Connection = MainForm.Connection
    Left = 672
    Top = 8
  end
  object MyQuery1: TMyQuery
    Connection = MainForm.Connection
    SQL.Strings = (
      
        'SELECT '#39'shengxing'#39' AS supplier_name, '#39#33426#26524'SIX'#39' AS company_name, '#39#37329 +
        #27719#21335#36335#39' AS store_name, '
      #39#27491#21333#39' AS order_type, '#39'2014-12-12'#39' AS reach_date, '
      
        #39#23567#26379#39' AS printer, '#39'1'#39' AS order_id, '#39'2'#39' AS company_id,'#39'1000'#39' AS to' +
        'tal_money')
    Active = True
    Left = 752
    Top = 24
  end
  object MyQuery2: TMyQuery
    Connection = MainForm.Connection
    SQL.Strings = (
      
        'select '#39#22823#30058#33540#39' as name, '#39'1.5'#26020#39' as order_weight, '#39'2'#39' as real_weight' +
        ', '#39#26020#39' as speci, '#39'4.5'#39' as price, '#39'9'#39' as money')
    Active = True
    Left = 720
    Top = 8
  end
  object QryDetail: TMyQuery
    Connection = MainForm.Connection
    Left = 648
    Top = 24
  end
end
