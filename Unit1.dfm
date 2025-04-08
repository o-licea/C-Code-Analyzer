object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'C++ Code Analyzer'
  ClientHeight = 572
  ClientWidth = 984
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  TextHeight = 13
  object Label1: TLabel
    Left = 336
    Top = 21
    Width = 364
    Height = 45
    Caption = 'C++ Code Analyzer'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -37
    Font.Name = 'Verdana'
    Font.Style = [fsItalic]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 232
    Top = 85
    Width = 544
    Height = 13
    Caption = 
      'This program is designed to check for the correct usage of vario' +
      'us symbols used in a C++ file.'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 232
    Top = 112
    Width = 555
    Height = 13
    Caption = 
      'To begin analysis, simply press the button below to select a  .c' +
      'pp or .h file from your documents.'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 208
    Top = 164
    Width = 64
    Height = 13
    Caption = 'Your Code:'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 712
    Top = 164
    Width = 78
    Height = 13
    Caption = 'Errors Found:'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = []
    ParentFont = False
  end
  object Button1: TButton
    Left = 464
    Top = 152
    Width = 75
    Height = 25
    Caption = 'Open File'
    TabOrder = 0
    OnClick = Button1Click
  end
  object CodeBox: TMemo
    Left = 40
    Top = 183
    Width = 441
    Height = 369
    Lines.Strings = (
      'CodeBox')
    TabOrder = 1
  end
  object ErrorBox: TMemo
    Left = 520
    Top = 183
    Width = 441
    Height = 369
    Lines.Strings = (
      'ErrorBox')
    TabOrder = 2
  end
  object OpenCodeFile: TOpenDialog
    FileName = 
      'C:\Users\oraci\Documents\Schoolwork\Semester 4 (CTC)\COSC 2336\L' +
      'esson 4\Programming Project II\Unit1.cpp'
    Options = [ofReadOnly, ofEnableSizing]
    Left = 24
    Top = 16
  end
end
