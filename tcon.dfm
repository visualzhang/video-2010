object tcon_form: Ttcon_form
  Left = 0
  Top = 0
  Width = 1024
  Height = 674
  Caption = 'tcon_form'
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl5: TPageControl
    Left = -1
    Top = 16
    Width = 986
    Height = 609
    ActivePage = Para
    TabIndex = 0
    TabOrder = 0
    object Para: TTabSheet
      Caption = 'Gamma       '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clDefault
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      object Label17: TLabel
        Left = 152
        Top = 12
        Width = 56
        Height = 13
        Caption = 'CA-210 CH:'
      end
      object Image1: TImage
        Left = 376
        Top = 8
        Width = 537
        Height = 569
      end
      object Panel2: TPanel
        Left = 0
        Top = 120
        Width = 289
        Height = 105
        TabOrder = 0
        object Label1: TLabel
          Left = 8
          Top = 68
          Width = 85
          Height = 13
          Caption = 'Interpolation over:'
        end
        object Label2: TLabel
          Left = 430
          Top = 68
          Width = 51
          Height = 13
          Caption = 'Saturation:'
        end
        object Label3: TLabel
          Left = 8
          Top = 36
          Width = 91
          Height = 13
          Caption = 'Interpolation under:'
        end
        object Edit2: TEdit
          Left = 136
          Top = 64
          Width = 129
          Height = 21
          TabOrder = 0
        end
        object Edit3: TEdit
          Left = 528
          Top = 64
          Width = 33
          Height = 21
          TabOrder = 1
        end
        object RadioGroup7: TRadioGroup
          Left = 488
          Top = 48
          Width = 36
          Height = 54
          ItemIndex = 0
          Items.Strings = (
            '+'
            '-')
          TabOrder = 2
        end
        object Edit1: TEdit
          Left = 136
          Top = 24
          Width = 129
          Height = 21
          TabOrder = 3
        end
      end
      object Button7: TButton
        Left = 0
        Top = 8
        Width = 129
        Height = 25
        Caption = 'connect to CA210'
        TabOrder = 1
      end
      object ComboBox1: TComboBox
        Left = 200
        Top = 52
        Width = 81
        Height = 21
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 2
        Text = 'Red'
        Items.Strings = (
          'Red'
          'Green'
          'Blue'
          'Cyan'
          'Magenta'
          'Yellow'
          'Flesh')
      end
      object ComboBox2: TComboBox
        Left = 216
        Top = 12
        Width = 81
        Height = 21
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 3
        Text = 'Red'
        Items.Strings = (
          'Red'
          'Green'
          'Blue'
          'Cyan'
          'Magenta'
          'Yellow'
          'Flesh')
      end
      object StringGrid7: TStringGrid
        Left = 8
        Top = 264
        Width = 369
        Height = 161
        Color = clWhite
        ColCount = 6
        DefaultColWidth = 30
        DefaultRowHeight = 22
        FixedColor = 16572634
        RowCount = 8
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
        TabOrder = 4
        OnSelectCell = StringGrid1SelectCell
        ColWidths = (
          30
          30
          30
          30
          30
          30)
        RowHeights = (
          22
          22
          22
          22
          22
          22
          22
          22)
      end
      object Button1: TButton
        Left = 0
        Top = 48
        Width = 129
        Height = 25
        Caption = 'Pattern'
        TabOrder = 5
      end
      object Button4: TButton
        Left = 0
        Top = 88
        Width = 129
        Height = 25
        Caption = 'Color temperature'
        TabOrder = 6
      end
      object Button5: TButton
        Left = 8
        Top = 232
        Width = 129
        Height = 25
        Caption = 'calibration'
        TabOrder = 7
      end
      object Button6: TButton
        Left = 928
        Top = 24
        Width = 51
        Height = 25
        Caption = 'get data'
        TabOrder = 8
        OnClick = get_data
      end
      object Button9: TButton
        Left = 928
        Top = 128
        Width = 49
        Height = 25
        Caption = 'Button9'
        TabOrder = 9
        Visible = False
        OnClick = draw_axis_frame
      end
      object BitBtn1: TBitBtn
        Left = 928
        Top = 160
        Width = 49
        Height = 25
        Caption = 'Curve'
        TabOrder = 10
        OnClick = gamma_curve
      end
      object Edit4: TEdit
        Left = 928
        Top = 216
        Width = 41
        Height = 21
        TabOrder = 11
        Text = '1'
      end
      object Edit5: TEdit
        Left = 928
        Top = 256
        Width = 41
        Height = 21
        TabOrder = 12
        Text = '2'
      end
      object Edit6: TEdit
        Left = 928
        Top = 296
        Width = 41
        Height = 21
        TabOrder = 13
        Text = '3'
      end
    end
    object Page_R: TTabSheet
      Caption = 'Timing     '
      ImageIndex = 1
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 969
        Height = 561
        Color = clWhite
        TabOrder = 0
        object GroupBox2: TGroupBox
          Left = 328
          Top = 16
          Width = 625
          Height = 457
          TabOrder = 3
          object StringGrid1: TStringGrid
            Left = 16
            Top = 24
            Width = 273
            Height = 81
            Color = clWhite
            ColCount = 6
            DefaultColWidth = 30
            DefaultRowHeight = 22
            FixedColor = 16572634
            RowCount = 8
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
            TabOrder = 0
            OnSelectCell = StringGrid1SelectCell
            ColWidths = (
              30
              30
              30
              30
              30
              30)
            RowHeights = (
              22
              22
              22
              22
              22
              22
              22
              22)
          end
          object StringGrid2: TStringGrid
            Left = 264
            Top = 24
            Width = 265
            Height = 137
            Color = clWhite
            ColCount = 6
            DefaultColWidth = 30
            DefaultRowHeight = 22
            FixedColor = 16572634
            RowCount = 8
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
            TabOrder = 1
            OnSelectCell = StringGrid1SelectCell
            ColWidths = (
              30
              30
              30
              30
              30
              30)
            RowHeights = (
              22
              22
              22
              22
              22
              22
              22
              22)
          end
        end
        object GroupBox1: TGroupBox
          Left = 8
          Top = 16
          Width = 313
          Height = 305
          TabOrder = 2
          object Label5: TLabel
            Left = 32
            Top = 32
            Width = 32
            Height = 13
            Caption = 'Label5'
          end
          object Label4: TLabel
            Left = 40
            Top = 40
            Width = 32
            Height = 13
            Caption = 'Label5'
          end
          object Label6: TLabel
            Left = 48
            Top = 48
            Width = 32
            Height = 13
            Caption = 'Label5'
          end
          object Label7: TLabel
            Left = 56
            Top = 56
            Width = 32
            Height = 13
            Caption = 'Label5'
          end
          object Label8: TLabel
            Left = 64
            Top = 64
            Width = 32
            Height = 13
            Caption = 'Label5'
          end
          object Label9: TLabel
            Left = 72
            Top = 72
            Width = 32
            Height = 13
            Caption = 'Label5'
          end
          object Label10: TLabel
            Left = 80
            Top = 80
            Width = 32
            Height = 13
            Caption = 'Label5'
          end
          object Label11: TLabel
            Left = 88
            Top = 88
            Width = 32
            Height = 13
            Caption = 'Label5'
          end
          object Label12: TLabel
            Left = 96
            Top = 96
            Width = 32
            Height = 13
            Caption = 'Label5'
          end
          object Label13: TLabel
            Left = 104
            Top = 104
            Width = 32
            Height = 13
            Caption = 'Label5'
          end
          object Label14: TLabel
            Left = 112
            Top = 112
            Width = 32
            Height = 13
            Caption = 'Label5'
          end
          object Label15: TLabel
            Left = 120
            Top = 120
            Width = 32
            Height = 13
            Caption = 'Label5'
          end
          object Label16: TLabel
            Left = 128
            Top = 128
            Width = 32
            Height = 13
            Caption = 'Label5'
          end
          object CheckBox3: TCheckBox
            Left = 160
            Top = 80
            Width = 25
            Height = 17
            TabOrder = 0
            OnClick = timing_para
          end
          object CheckBox9: TCheckBox
            Left = 192
            Top = 144
            Width = 25
            Height = 17
            TabOrder = 1
            OnClick = timing_para
          end
          object CheckBox8: TCheckBox
            Left = 184
            Top = 128
            Width = 25
            Height = 17
            TabOrder = 2
            OnClick = timing_para
          end
          object CheckBox7: TCheckBox
            Left = 176
            Top = 112
            Width = 25
            Height = 17
            TabOrder = 3
            OnClick = timing_para
          end
          object CheckBox6: TCheckBox
            Left = 168
            Top = 96
            Width = 25
            Height = 17
            TabOrder = 4
            OnClick = timing_para
          end
          object CheckBox2: TCheckBox
            Left = 160
            Top = 56
            Width = 25
            Height = 17
            TabOrder = 5
            OnClick = timing_para
          end
          object CheckBox14: TCheckBox
            Left = 184
            Top = 272
            Width = 25
            Height = 17
            TabOrder = 6
            OnClick = timing_para
          end
          object CheckBox13: TCheckBox
            Left = 184
            Top = 248
            Width = 25
            Height = 17
            TabOrder = 7
            OnClick = timing_para
          end
          object CheckBox12: TCheckBox
            Left = 184
            Top = 224
            Width = 25
            Height = 17
            TabOrder = 8
            OnClick = timing_para
          end
          object CheckBox11: TCheckBox
            Left = 184
            Top = 192
            Width = 25
            Height = 17
            TabOrder = 9
            OnClick = timing_para
          end
          object CheckBox10: TCheckBox
            Left = 192
            Top = 168
            Width = 25
            Height = 17
            TabOrder = 10
            OnClick = timing_para
          end
          object CheckBox1: TCheckBox
            Left = 160
            Top = 40
            Width = 25
            Height = 17
            TabOrder = 11
            OnClick = timing_para
          end
        end
        object Button2: TButton
          Left = 886
          Top = 528
          Width = 83
          Height = 25
          Caption = 'send'
          TabOrder = 0
          OnClick = timing_send
        end
        object Button3: TButton
          Left = 792
          Top = 528
          Width = 75
          Height = 25
          Caption = 'Get'
          TabOrder = 1
          OnClick = timing_get
        end
        object Panel3: TPanel
          Left = 368
          Top = 56
          Width = 593
          Height = 297
          Caption = 'Panel3'
          Color = clWhite
          TabOrder = 4
          object StringGrid4: TStringGrid
            Left = 368
            Top = 176
            Width = 265
            Height = 137
            Color = clWhite
            ColCount = 6
            DefaultColWidth = 30
            DefaultRowHeight = 22
            FixedColor = 16572634
            RowCount = 8
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
            TabOrder = 2
            OnSelectCell = StringGrid1SelectCell
            ColWidths = (
              30
              30
              30
              30
              30
              30)
            RowHeights = (
              22
              22
              22
              22
              22
              22
              22
              22)
          end
          object StringGrid6: TStringGrid
            Left = 24
            Top = 168
            Width = 265
            Height = 137
            Color = clWhite
            ColCount = 6
            DefaultColWidth = 30
            DefaultRowHeight = 22
            FixedColor = 16572634
            RowCount = 8
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
            TabOrder = 0
            OnSelectCell = StringGrid1SelectCell
            ColWidths = (
              30
              30
              30
              30
              30
              30)
            RowHeights = (
              22
              22
              22
              22
              22
              22
              22
              22)
          end
          object StringGrid3: TStringGrid
            Left = -40
            Top = 24
            Width = 265
            Height = 137
            Color = clWhite
            ColCount = 6
            DefaultColWidth = 30
            DefaultRowHeight = 22
            FixedColor = 16572634
            RowCount = 8
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
            TabOrder = 3
            OnSelectCell = StringGrid1SelectCell
            ColWidths = (
              30
              30
              30
              30
              30
              30)
            RowHeights = (
              22
              22
              22
              22
              22
              22
              22
              22)
          end
          object StringGrid5: TStringGrid
            Left = 224
            Top = 16
            Width = 265
            Height = 137
            Color = clWhite
            ColCount = 6
            DefaultColWidth = 30
            DefaultRowHeight = 22
            FixedColor = 16572634
            RowCount = 8
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
            TabOrder = 1
            OnSelectCell = StringGrid1SelectCell
            ColWidths = (
              30
              30
              30
              30
              30
              30)
            RowHeights = (
              22
              22
              22
              22
              22
              22
              22
              22)
          end
        end
      end
    end
  end
end
