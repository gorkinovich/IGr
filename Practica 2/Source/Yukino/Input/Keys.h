//******************************************************************************************
// Yukino 2.0 - A 3D game library.
// Copyright (C) 2006  Gorka Suárez García
// 
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//******************************************************************************************
#ifndef _YUKINO_INPUT_KEYS_H_
#define _YUKINO_INPUT_KEYS_H_
//******************************************************************************************
// Constantes para el teclado inglés/estado unidense.
//******************************************************************************************
#define KEY_ESCAPE          0x01
#define KEY_1               0x02
#define KEY_2               0x03
#define KEY_3               0x04
#define KEY_4               0x05
#define KEY_5               0x06
#define KEY_6               0x07
#define KEY_7               0x08
#define KEY_8               0x09
#define KEY_9               0x0A
#define KEY_0               0x0B
#define KEY_MINUS           0x0C    // - on main keyboard
#define KEY_EQUALS          0x0D
#define KEY_BACK            0x0E    // backspace
#define KEY_TAB             0x0F
#define KEY_Q               0x10
#define KEY_W               0x11
#define KEY_E               0x12
#define KEY_R               0x13
#define KEY_T               0x14
#define KEY_Y               0x15
#define KEY_U               0x16
#define KEY_I               0x17
#define KEY_O               0x18
#define KEY_P               0x19
#define KEY_LBRACKET        0x1A
#define KEY_RBRACKET        0x1B
#define KEY_RETURN          0x1C    // Enter on main keyboard
#define KEY_LCONTROL        0x1D
#define KEY_A               0x1E
#define KEY_S               0x1F
#define KEY_D               0x20
#define KEY_F               0x21
#define KEY_G               0x22
#define KEY_H               0x23
#define KEY_J               0x24
#define KEY_K               0x25
#define KEY_L               0x26
#define KEY_SEMICOLON       0x27
#define KEY_APOSTROPHE      0x28
#define KEY_GRAVE           0x29    // accent grave
#define KEY_LSHIFT          0x2A
#define KEY_BACKSLASH       0x2B
#define KEY_Z               0x2C
#define KEY_X               0x2D
#define KEY_C               0x2E
#define KEY_V               0x2F
#define KEY_B               0x30
#define KEY_N               0x31
#define KEY_M               0x32
#define KEY_COMMA           0x33
#define KEY_PERIOD          0x34    // . on main keyboard
#define KEY_SLASH           0x35    // / on main keyboard
#define KEY_RSHIFT          0x36
#define KEY_MULTIPLY        0x37    // * on numeric keypad
#define KEY_LMENU           0x38    // left Alt
#define KEY_SPACE           0x39
#define KEY_CAPITAL         0x3A
#define KEY_F1              0x3B
#define KEY_F2              0x3C
#define KEY_F3              0x3D
#define KEY_F4              0x3E
#define KEY_F5              0x3F
#define KEY_F6              0x40
#define KEY_F7              0x41
#define KEY_F8              0x42
#define KEY_F9              0x43
#define KEY_F10             0x44
#define KEY_NUMLOCK         0x45
#define KEY_SCROLL          0x46    // Scroll Lock
#define KEY_NUMPAD7         0x47
#define KEY_NUMPAD8         0x48
#define KEY_NUMPAD9         0x49
#define KEY_SUBTRACT        0x4A    // - on numeric keypad
#define KEY_NUMPAD4         0x4B
#define KEY_NUMPAD5         0x4C
#define KEY_NUMPAD6         0x4D
#define KEY_ADD             0x4E    // + on numeric keypad
#define KEY_NUMPAD1         0x4F
#define KEY_NUMPAD2         0x50
#define KEY_NUMPAD3         0x51
#define KEY_NUMPAD0         0x52
#define KEY_DECIMAL         0x53    // . on numeric keypad
#define KEY_OEM_102         0x56    // <> or \| on RT 102-key keyboard (Non-U.S.)
#define KEY_F11             0x57
#define KEY_F12             0x58
#define KEY_F13             0x64    //                     (NEC PC98)
#define KEY_F14             0x65    //                     (NEC PC98)
#define KEY_F15             0x66    //                     (NEC PC98)
#define KEY_KANA            0x70    // (Japanese keyboard)           
#define KEY_ABNT_C1         0x73    // /? on Brazilian keyboard
#define KEY_CONVERT         0x79    // (Japanese keyboard)           
#define KEY_NOCONVERT       0x7B    // (Japanese keyboard)           
#define KEY_YEN             0x7D    // (Japanese keyboard)           
#define KEY_ABNT_C2         0x7E    // Numpad . on Brazilian keyboard
#define KEY_NUMPADEQUALS    0x8D    // = on numeric keypad (NEC PC98)
#define KEY_PREVTRACK       0x90    // Previous Track (DIK_CIRCUMFLEX on Japanese keyboard)
#define KEY_AT              0x91    //                     (NEC PC98)
#define KEY_COLON           0x92    //                     (NEC PC98)
#define KEY_UNDERLINE       0x93    //                     (NEC PC98)
#define KEY_KANJI           0x94    // (Japanese keyboard)           
#define KEY_STOP            0x95    //                     (NEC PC98)
#define KEY_AX              0x96    //                     (Japan AX)
#define KEY_UNLABELED       0x97    //                        (J3100)
#define KEY_NEXTTRACK       0x99    // Next Track
#define KEY_NUMPADENTER     0x9C    // Enter on numeric keypad
#define KEY_RCONTROL        0x9D
#define KEY_MUTE            0xA0    // Mute
#define KEY_CALCULATOR      0xA1    // Calculator
#define KEY_PLAYPAUSE       0xA2    // Play / Pause
#define KEY_MEDIASTOP       0xA4    // Media Stop
#define KEY_VOLUMEDOWN      0xAE    // Volume -
#define KEY_VOLUMEUP        0xB0    // Volume +
#define KEY_WEBHOME         0xB2    // Web home
#define KEY_NUMPADCOMMA     0xB3    // , on numeric keypad (NEC PC98)
#define KEY_DIVIDE          0xB5    // / on numeric keypad
#define KEY_SYSRQ           0xB7
#define KEY_RMENU           0xB8    // right Alt
#define KEY_PAUSE           0xC5    // Pause
#define KEY_HOME            0xC7    // Home on arrow keypad
#define KEY_UP              0xC8    // UpArrow on arrow keypad
#define KEY_PRIOR           0xC9    // PgUp on arrow keypad
#define KEY_LEFT            0xCB    // LeftArrow on arrow keypad
#define KEY_RIGHT           0xCD    // RightArrow on arrow keypad
#define KEY_END             0xCF    // End on arrow keypad
#define KEY_DOWN            0xD0    // DownArrow on arrow keypad
#define KEY_NEXT            0xD1    // PgDn on arrow keypad
#define KEY_INSERT          0xD2    // Insert on arrow keypad
#define KEY_DELETE          0xD3    // Delete on arrow keypad
#define KEY_LWIN            0xDB    // Left Windows key
#define KEY_RWIN            0xDC    // Right Windows key
#define KEY_APPS            0xDD    // AppMenu key
#define KEY_POWER           0xDE    // System Power
#define KEY_SLEEP           0xDF    // System Sleep
#define KEY_WAKE            0xE3    // System Wake
#define KEY_WEBSEARCH       0xE5    // Web Search
#define KEY_WEBFAVORITES    0xE6    // Web Favorites
#define KEY_WEBREFRESH      0xE7    // Web Refresh
#define KEY_WEBSTOP         0xE8    // Web Stop
#define KEY_WEBFORWARD      0xE9    // Web Forward
#define KEY_WEBBACK         0xEA    // Web Back
#define KEY_MYCOMPUTER      0xEB    // My Computer
#define KEY_MAIL            0xEC    // Mail
#define KEY_MEDIASELECT     0xED    // Media Select
//******************************************************************************************
// Constantes para el teclado español.
//******************************************************************************************
#define TECLA_ESC				  1
#define TECLA_F1				 59
#define TECLA_F2				 60
#define TECLA_F3				 61
#define TECLA_F4				 62
#define TECLA_F5				 63
#define TECLA_F6				 64
#define TECLA_F7				 65
#define TECLA_F8				 66
#define TECLA_F9				 67
#define TECLA_F10				 68
#define TECLA_F11				 87
#define TECLA_F12				 88
#define TECLA_IMPRPANT			183
#define TECLA_BLOQDESPL			 70
#define TECLA_PAUSA				197
#define TECLA_BARRAINV			 41
#define TECLA_1					  2
#define TECLA_2					  3
#define TECLA_3					  4
#define TECLA_4					  5
#define TECLA_5					  6
#define TECLA_6					  7
#define TECLA_7					  8
#define TECLA_8					  9
#define TECLA_9					 10
#define TECLA_0					 11
#define TECLA_APOSTROFE			 12
#define TECLA_EXCLAMACION		 13
#define TECLA_RETROCESO			 14
#define TECLA_TABULADOR			 15
#define TECLA_Q					 16
#define TECLA_W					 17
#define TECLA_E					 18
#define TECLA_R					 19
#define TECLA_T					 20
#define TECLA_Y					 21
#define TECLA_U					 22
#define TECLA_I					 23
#define TECLA_O					 24
#define TECLA_P					 25
#define TECLA_ABRE_CORCHETE		 26
#define TECLA_CIERRA_CORCHETE	 27
#define TECLA_BLOQMAYUS			 58
#define TECLA_A					 30
#define TECLA_S					 31
#define TECLA_D					 32
#define TECLA_F					 33
#define TECLA_G					 34
#define TECLA_H					 35
#define TECLA_J					 36
#define TECLA_K					 37
#define TECLA_L					 38
#define TECLA_NY				 39
#define TECLA_ABRE_LLAVE		 40
#define TECLA_CIERRA_LLAVE		 43
#define TECLA_ENTER				 28
#define TECLA_SHIFT_IZUIERDO	 42
#define TECLA_MENOR				 86
#define TECLA_Z					 44
#define TECLA_X					 45
#define TECLA_C					 46
#define TECLA_V					 47
#define TECLA_B					 48
#define TECLA_N					 49
#define TECLA_M					 50
#define TECLA_COMA				 51
#define TECLA_PUNTO				 52
#define TECLA_MENOS				 53
#define TECLA_SHIFT_DERECHO		 54
#define TECLA_CONTROL_IZQUIERDO	 29
#define TECLA_ALT_IZQUIERDO		 56
#define TECLA_ESPACIO			 57
#define TECLA_ALT_DERECHO		184
#define TECLA_CONTROL_DERECHO	157
#define TECLA_INSERTAR			210
#define TECLA_INICIO			199
#define TECLA_REPAG				201
#define TECLA_SUPRIMIR			211
#define TECLA_FIN				207
#define TECLA_AVPAG				209
#define TECLA_ARRIBA			200
#define TECLA_IZQUIERDA			203
#define TECLA_ABAJO				208
#define TECLA_DERECHA			205
#define TECLA_BLOQNUM			 69
#define TECLA_NUM_BARRA			181
#define TECLA_NUM_ASTERISCO		 55
#define TECLA_NUM_MENOS			 74
#define TECLA_NUM_7				 71
#define TECLA_NUM_8				 72
#define TECLA_NUM_9				 73
#define TECLA_NUM_4				 75
#define TECLA_NUM_5				 76
#define TECLA_NUM_6				 77
#define TECLA_NUM_MAS			 78
#define TECLA_NUM_1				 79
#define TECLA_NUM_2				 80
#define TECLA_NUM_3				 81
#define TECLA_NUM_0				 82
#define TECLA_NUM_PUNTO			 83
#define TECLA_NUM_ENTER			156
//******************************************************************************************
#endif
//******************************************************************************************
// Keys.h
//******************************************************************************************