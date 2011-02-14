object panel_adjust_form: Tpanel_adjust_form
  Left = 0
  Top = 0
  Width = 1024
  Height = 674
  Caption = 'Panel Adjust'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox2: TGroupBox
    Left = 24
    Top = 16
    Width = 633
    Height = 249
    Caption = 'Color'
    TabOrder = 23
    object Label8: TLabel
      Left = 16
      Top = 32
      Width = 47
      Height = 13
      Caption = 'Brightnes:'
    end
    object Label9: TLabel
      Left = 16
      Top = 64
      Width = 42
      Height = 13
      Caption = 'Contrast:'
    end
    object Label14: TLabel
      Left = 16
      Top = 104
      Width = 23
      Height = 13
      Caption = 'Hue:'
    end
    object Label15: TLabel
      Left = 16
      Top = 144
      Width = 51
      Height = 13
      Caption = 'Saturation:'
    end
    object Label16: TLabel
      Left = 16
      Top = 184
      Width = 53
      Height = 13
      Caption = 'Sharpness:'
    end
    object Label1: TLabel
      Left = 120
      Top = 216
      Width = 6
      Height = 13
      Caption = '0'
    end
    object Label2: TLabel
      Left = 464
      Top = 216
      Width = 18
      Height = 13
      Caption = '100'
    end
  end
  object GroupBox1: TGroupBox
    Left = 32
    Top = 304
    Width = 449
    Height = 113
    Caption = 'OverScan'
    TabOrder = 21
    object Label10: TLabel
      Left = 56
      Top = 32
      Width = 33
      Height = 13
      Caption = 'H-Start'
    end
    object Label11: TLabel
      Left = 112
      Top = 32
      Width = 32
      Height = 13
      Caption = 'V-Start'
    end
    object Label12: TLabel
      Left = 176
      Top = 32
      Width = 30
      Height = 13
      Caption = 'H-End'
    end
    object Label13: TLabel
      Left = 240
      Top = 32
      Width = 29
      Height = 13
      Caption = 'V-End'
    end
    object Button4: TButton
      Left = 328
      Top = 64
      Width = 75
      Height = 25
      Caption = 'Write'
      TabOrder = 0
      OnClick = Button4Click
    end
    object Button5: TButton
      Left = 328
      Top = 32
      Width = 75
      Height = 25
      Caption = 'Read'
      TabOrder = 1
      OnClick = Button5Click
    end
  end
  object ScrollBar9: TScrollBar
    Left = 144
    Top = 48
    Width = 361
    Height = 17
    PageSize = 0
    Position = 10
    SmallChange = 10
    TabOrder = 0
    OnChange = ScrollBar9Change
  end
  object ScrollBar10: TScrollBar
    Left = 144
    Top = 80
    Width = 361
    Height = 17
    LargeChange = 10
    Max = 360
    Min = 1
    PageSize = 0
    Position = 1
    SmallChange = 10
    TabOrder = 1
    OnChange = ScrollBar9Change
  end
  object Edit4: TEdit
    Left = 104
    Top = 44
    Width = 33
    Height = 21
    TabOrder = 2
    Text = '1'
  end
  object Edit5: TEdit
    Left = 104
    Top = 76
    Width = 33
    Height = 21
    TabOrder = 3
    Text = '1'
  end
  object Button1: TButton
    Left = 424
    Top = 624
    Width = 75
    Height = 25
    Caption = 'set'
    TabOrder = 4
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 192
    Top = 584
    Width = 75
    Height = 25
    Caption = 'Open comm'
    TabOrder = 5
    Visible = False
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 8
    Top = 656
    Width = 75
    Height = 25
    Caption = 'Button3'
    TabOrder = 6
    Visible = False
    OnClick = Button3Click
  end
  object Edit1: TEdit
    Left = 48
    Top = 624
    Width = 345
    Height = 21
    TabOrder = 7
    Text = 'echo 99 > /sys/class/video/brightness'
  end
  object m_get_data: TMemo
    Left = 664
    Top = 24
    Width = 457
    Height = 609
    TabOrder = 8
  end
  object Edit2: TEdit
    Left = 48
    Top = 592
    Width = 121
    Height = 21
    TabOrder = 9
    Text = 'Edit2'
  end
  object Edit3: TEdit
    Left = 96
    Top = 656
    Width = 121
    Height = 21
    TabOrder = 10
    Text = 'Edit3'
    Visible = False
  end
  object Edit6: TEdit
    Left = 104
    Top = 124
    Width = 33
    Height = 21
    TabOrder = 11
    Text = '1'
  end
  object ScrollBar1: TScrollBar
    Left = 144
    Top = 128
    Width = 361
    Height = 17
    LargeChange = 10
    Max = 360
    Min = 1
    PageSize = 0
    Position = 1
    SmallChange = 10
    TabOrder = 12
    OnChange = ScrollBar9Change
  end
  object Edit7: TEdit
    Left = 104
    Top = 156
    Width = 33
    Height = 21
    TabOrder = 13
    Text = '1'
  end
  object ScrollBar2: TScrollBar
    Left = 144
    Top = 160
    Width = 361
    Height = 17
    LargeChange = 10
    Max = 360
    Min = 1
    PageSize = 0
    Position = 1
    SmallChange = 10
    TabOrder = 14
    OnChange = ScrollBar9Change
  end
  object Edit8: TEdit
    Left = 81
    Top = 360
    Width = 31
    Height = 21
    TabOrder = 15
  end
  object Edit9: TEdit
    Left = 136
    Top = 360
    Width = 41
    Height = 21
    TabOrder = 16
  end
  object Edit10: TEdit
    Left = 104
    Top = 204
    Width = 33
    Height = 21
    TabOrder = 17
    Text = '1'
  end
  object ScrollBar3: TScrollBar
    Left = 144
    Top = 208
    Width = 361
    Height = 17
    LargeChange = 10
    Max = 360
    Min = 1
    PageSize = 0
    Position = 1
    SmallChange = 10
    TabOrder = 18
    OnChange = ScrollBar9Change
  end
  object Edit11: TEdit
    Left = 208
    Top = 360
    Width = 41
    Height = 21
    TabOrder = 19
  end
  object Edit12: TEdit
    Left = 273
    Top = 360
    Width = 31
    Height = 21
    TabOrder = 20
  end
  object Button6: TButton
    Left = 544
    Top = 216
    Width = 57
    Height = 25
    Caption = 'Read'
    TabOrder = 22
    OnClick = Button6Click
  end
end
