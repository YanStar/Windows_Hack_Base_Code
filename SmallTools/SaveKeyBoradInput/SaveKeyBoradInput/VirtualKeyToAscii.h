#ifndef _VIRTUAL_KEY_TO_ASCII_
#define _VIRTUAL_KEY_TO_ASCII_

#include <windows.h>

struct VKeyInfo{
	USHORT VKey;
	LPCSTR VKname;
};

#define AddVKey(VK, VKName)   {(VK), (VKName)}

// 辛辛苦苦从MSDN上摘录下来，VK的值从0x01 - 0xFE,如果编译器发现未定义的项目，直接换成对应的值就可以了.
static VKeyInfo vkis[] = {
	AddVKey(VK_LBUTTON, "Left mouse button"),
	AddVKey(VK_RBUTTON, "Right mouse button"),
	AddVKey(VK_CANCEL, "Control-break processing"),
	AddVKey(0x04, "Middle mouse button (three-button mouse)"),
	AddVKey(0x05, "Windows 2000/XP: X1 mouse button"),
	AddVKey(0x06, "Windows 2000/XP: X2 mouse button"),
	AddVKey(0x07, "Undefined"),
	AddVKey(VK_BACK, "BACKSPACE key"),
	AddVKey(VK_TAB, "TAB key"),
	AddVKey(0x0A, "Reserved"),
	AddVKey(0x0B, "Reserved"),
	AddVKey(VK_CLEAR, "CLEAR key"),
	AddVKey(VK_RETURN, "ENTER key"),
	AddVKey(0x0E, "Undefined"),
	AddVKey(0x0F, "Undefined"),
	AddVKey(VK_SHIFT, "SHIFT key"),
	AddVKey(VK_CONTROL, "CTRL key"),
	AddVKey(VK_MENU, "ALT key"),
	AddVKey(VK_PAUSE, "PAUSE key"),
	AddVKey(VK_CAPITAL, "CAPS LOCK key"),
	AddVKey(VK_KANA, "Input Method Editor (IME) Kana mode"),
	AddVKey(VK_HANGUL, "IME Hangul mode"),
	AddVKey(0x16, "Undefined"),
	AddVKey(VK_JUNJA, "IME Junja mode"),
	AddVKey(VK_FINAL, "IME final mode"),
	AddVKey(VK_HANJA, "IME Hanja mode"),
	AddVKey(VK_KANJI, "IME Kanji mode"),
	AddVKey(0x1A, "Undefined"),
	AddVKey(VK_ESCAPE, "ESC key"),
	AddVKey(VK_CONVERT, "IME convert"),
	AddVKey(VK_NONCONVERT, "IME nonconvert"),
	AddVKey(VK_ACCEPT, "IME accept"),
	AddVKey(VK_MODECHANGE, "IME mode change request"),
	AddVKey(VK_SPACE, "SPACEBAR"),
	AddVKey(VK_PRIOR, "PAGE UP key"),
	AddVKey(VK_NEXT, "PAGE DOWN key"),
	AddVKey(VK_END, "END key"),
	AddVKey(VK_HOME, "HOME key"),
	AddVKey(VK_LEFT, "LEFT ARROW key"),
	AddVKey(VK_UP, "UP ARROW key"),
	AddVKey(VK_RIGHT, "RIGHT ARROW key"),
	AddVKey(VK_DOWN, "DOWN ARROW key"),
	AddVKey(VK_SELECT, "SELECT key"),
	AddVKey(VK_PRINT, "PRINT key"),
	AddVKey(VK_EXECUTE, "EXECUTE key"),
	AddVKey(VK_SNAPSHOT, "PRINT SCREEN key"),
	AddVKey(VK_INSERT, "INSERT key"),
	AddVKey(VK_DELETE, "DEL key"),
	AddVKey(VK_HELP, "HELP key"),
	AddVKey(0x30, "0"),
	AddVKey(0x31, "1"),
	AddVKey(0x32, "2"),
	AddVKey(0x33, "3"),
	AddVKey(0x34, "4"),
	AddVKey(0x35, "5"),
	AddVKey(0x36, "6"),
	AddVKey(0x37, "7"),
	AddVKey(0x38, "8"),
	AddVKey(0x39, "9"),
	AddVKey(0x3A, "Undefined"),
	AddVKey(0x3B, "Undefined"),
	AddVKey(0x3C, "Undefined"),
	AddVKey(0x3D, "Undefined"),
	AddVKey(0x3E, "Undefined"),
	AddVKey(0x3F, "Undefined"),
	AddVKey(0x40, "Undefined"),
	AddVKey(0x41, "A"),
	AddVKey(0x42, "B"),
	AddVKey(0x43, "C"),
	AddVKey(0x44, "D"),
	AddVKey(0x45, "E"),
	AddVKey(0x46, "F"),
	AddVKey(0x47, "G"),
	AddVKey(0x48, "H"),
	AddVKey(0x49, "I"),
	AddVKey(0x4A, "J"),
	AddVKey(0x4B, "K"),
	AddVKey(0x4C, "L"),
	AddVKey(0x4D, "M"),
	AddVKey(0x4E, "N"),
	AddVKey(0x4F, "O"),
	AddVKey(0x50, "P"),
	AddVKey(0x51, "Q"),
	AddVKey(0x52, "R"),
	AddVKey(0x53, "S"),
	AddVKey(0x54, "T"),
	AddVKey(0x55, "U"),
	AddVKey(0x56, "V"),
	AddVKey(0x57, "W"),
	AddVKey(0x58, "X"),
	AddVKey(0x59, "Y"),
	AddVKey(0x5A, "Z"),

	AddVKey(VK_LWIN, "Left Windows key (Microsoft Natural keyboard)"),
	AddVKey(VK_RWIN, "Right Windows key (Natural keyboard)"),
	AddVKey(VK_APPS, "Applications key (Natural keyboard)"),
	AddVKey(0x5E, "Reserved"),
	AddVKey(VK_SLEEP, "Computer Sleep key"),
	AddVKey(VK_NUMPAD0, "Numeric keypad 0 key"),
	AddVKey(VK_NUMPAD1, "Numeric keypad 1 key"),
	AddVKey(VK_NUMPAD2, "Numeric keypad 2 key"),
	AddVKey(VK_NUMPAD3, "Numeric keypad 3 key"),
	AddVKey(VK_NUMPAD4, "Numeric keypad 4 key"),
	AddVKey(VK_NUMPAD5, "Numeric keypad 5 key"),
	AddVKey(VK_NUMPAD6, "Numeric keypad 6 key"),
	AddVKey(VK_NUMPAD7, "Numeric keypad 7 key"),
	AddVKey(VK_NUMPAD8, "Numeric keypad 8 key"),
	AddVKey(VK_NUMPAD9, "Numeric keypad 9 key"),
	AddVKey(VK_MULTIPLY, "Multiply key"),
	AddVKey(VK_ADD, "Add key"),
	AddVKey(VK_SEPARATOR, "Separator key"),
	AddVKey(VK_SUBTRACT, "Subtract key"),
	AddVKey(VK_DECIMAL, "Decimal key"),
	AddVKey(VK_DIVIDE, "Divide key"),
	AddVKey(VK_F1, "F1 key"),
	AddVKey(VK_F2, "F2 key"),
	AddVKey(VK_F3, "F3 key"),
	AddVKey(VK_F4, "F4 key"),
	AddVKey(VK_F5, "F5 key"),
	AddVKey(VK_F6, "F6 key"),
	AddVKey(VK_F7, "F7 key"),
	AddVKey(VK_F8, "F8 key"),
	AddVKey(VK_F9, "F9 key"),
	AddVKey(VK_F10, "F10 key"),
	AddVKey(VK_F11, "F11 key"),
	AddVKey(VK_F12, "F12 key"),
	AddVKey(VK_F13, "F13 key"),
	AddVKey(VK_F14, "F14 key"),
	AddVKey(VK_F15, "F15 key"),
	AddVKey(VK_F16, "F16 key"),
	AddVKey(VK_F17, "F17 key"),
	AddVKey(VK_F18, "F18 key"),
	AddVKey(VK_F19, "F19 key"),
	AddVKey(VK_F20, "F20 key"),
	AddVKey(VK_F21, "F21 key"),
	AddVKey(VK_F22, "F22 key"),
	AddVKey(VK_F23, "F23 key"),
	AddVKey(VK_F24, "F24 key"),
	AddVKey(0x88, "Unassigned"),
	AddVKey(0x89, "Unassigned"),
	AddVKey(0x8A, "Unassigned"),
	AddVKey(0x8B, "Unassigned"),
	AddVKey(0x8C, "Unassigned"),
	AddVKey(0x8D, "Unassigned"),
	AddVKey(0x8E, "Unassigned"),
	AddVKey(0x8F, "Unassigned"),
	AddVKey(VK_NUMLOCK, "NUM LOCK key"),
	AddVKey(VK_SCROLL, "SCROLL LOCK key"),
	AddVKey(0x92, "OEM specific"),
	AddVKey(0x93, "OEM specific"),
	AddVKey(0x94, "OEM specific"),
	AddVKey(0x95, "OEM specific"),
	AddVKey(0x96, "OEM specific"),
	AddVKey(0x97, "Unassigned"),
	AddVKey(0x98, "Unassigned"),
	AddVKey(0x99, "Unassigned"),
	AddVKey(0x9A, "Unassigned"),
	AddVKey(0x9B, "Unassigned"),
	AddVKey(0x9C, "Unassigned"),
	AddVKey(0x9D, "Unassigned"),
	AddVKey(0x9E, "Unassigned"),
	AddVKey(0x9F, "Unassigned"),
	AddVKey(VK_LSHIFT, "Left SHIFT key"),
	AddVKey(VK_RSHIFT, "Right SHIFT key"),
	AddVKey(VK_LCONTROL, "Left CONTROL key"),
	AddVKey(VK_RCONTROL, "Right CONTROL key"),
	AddVKey(VK_LMENU, "Left MENU key"),
	AddVKey(VK_RMENU, "Right MENU key"),
	AddVKey(0xA6, "Windows 2000/XP: Browser Back key"),
	AddVKey(0xA7, "Windows 2000/XP: Browser Forward key"),
	AddVKey(0xA8, "Windows 2000/XP: Browser Refresh key"),
	AddVKey(0xA9, "Windows 2000/XP: Browser Stop key"),
	AddVKey(0xAA, "Windows 2000/XP: Browser Search key"),
	AddVKey(0xAB, "Windows 2000/XP: Browser Favorites key"),
	AddVKey(0xAC, "Windows 2000/XP: Browser Start and Home key"),
	AddVKey(0xAD, "Windows 2000/XP: Volume Mute key"),
	AddVKey(0xAE, "Windows 2000/XP: Volume Down key"),
	AddVKey(0xAF, "Windows 2000/XP: Volume Up key"),
	AddVKey(0xB0, "Windows 2000/XP: Next Track key"),
	AddVKey(0xB1, "Windows 2000/XP: Previous Track key"),
	AddVKey(0xB2, "Windows 2000/XP: Stop Media key"),
	AddVKey(0xB3, "Windows 2000/XP: Play/Pause Media key"),
	AddVKey(0xB4, "Windows 2000/XP: Start Mail key"),
	AddVKey(0xB5, "Windows 2000/XP: Select Media key"),
	AddVKey(0xB6, "Windows 2000/XP: Start Application 1 key"),
	AddVKey(0xB7, "Windows 2000/XP: Start Application 2 key"),
	AddVKey(0xB8, "Reserved"),
	AddVKey(0xB9, "Reserved"),
	AddVKey(VK_OEM_1, "Used for miscellaneous characters; it can vary by keyboard."
	"Windows 2000/XP: For the US standard keyboard, the \';:\' key"),
	AddVKey(VK_OEM_PLUS, "Windows 2000/XP: For any country/region, the \'+\' key"),
	AddVKey(VK_OEM_COMMA, "Windows 2000/XP: For any country/region, the \',\' key"),
	AddVKey(VK_OEM_MINUS, "Windows 2000/XP: For any country/region, the \'-\' key"),
	AddVKey(VK_OEM_PERIOD, "Windows 2000/XP: For any country/region, the \'.\' key"),
	AddVKey(VK_OEM_2, "Used for miscellaneous characters; it can vary by keyboard."
	"Windows 2000/XP: For the US standard keyboard, the \'/?\' key"),
	AddVKey(VK_OEM_3, "Used for miscellaneous characters; it can vary by keyboard."
	"Windows 2000/XP: For the US standard keyboard, the \'`~\' key"),
	AddVKey(0xC1, "Reserved"),
	AddVKey(0xC2, "Reserved"),
	AddVKey(0xC3, "Reserved"),
	AddVKey(0xC4, "Reserved"),
	AddVKey(0xC5, "Reserved"),
	AddVKey(0xC6, "Reserved"),
	AddVKey(0xC7, "Reserved"),
	AddVKey(0xC8, "Reserved"),
	AddVKey(0xC9, "Reserved"),
	AddVKey(0xCA, "Reserved"),
	AddVKey(0xCB, "Reserved"),
	AddVKey(0xCC, "Reserved"),
	AddVKey(0xCD, "Reserved"),
	AddVKey(0xCE, "Reserved"),
	AddVKey(0xCF, "Reserved"),
	AddVKey(0xD0, "Reserved"),
	AddVKey(0xD1, "Reserved"),
	AddVKey(0xD2, "Reserved"),
	AddVKey(0xD3, "Reserved"),
	AddVKey(0xD4, "Reserved"),
	AddVKey(0xD5, "Reserved"),
	AddVKey(0xD6, "Reserved"),
	AddVKey(0xD7, "Reserved"),
	AddVKey(0xD8, "Unassigned"),
	AddVKey(0xD9, "Unassigned"),
	AddVKey(0xDA, "Unassigned"),
	AddVKey(VK_OEM_4, "Used for miscellaneous characters; it can vary by keyboard."
	"Windows 2000/XP: For the US standard keyboard, the \'[{\' key"),
	AddVKey(VK_OEM_5, "Used for miscellaneous characters; it can vary by keyboard."
	"Windows 2000/XP: For the US standard keyboard, the \'\\|\' key"),
	AddVKey(VK_OEM_6, "Used for miscellaneous characters; it can vary by keyboard."
	"Windows 2000/XP: For the US standard keyboard, the \']}\' key"),
	AddVKey(VK_OEM_7, "Used for miscellaneous characters; it can vary by keyboard."
	"Windows 2000/XP: For the US standard keyboard, the \'single-quote/double-quote\' key"),

	AddVKey(VK_OEM_8, "Used for miscellaneous characters; it can vary by keyboard."),
	AddVKey(0xE0, "Reserved"),
	AddVKey(0xE1, "OEM specific"),
	AddVKey(VK_OEM_102, "Windows 2000/XP: Either the angle bracket key or the backslash key on the RT 102-key keyboard"),
	AddVKey(0xE3, "OEM specific"),
	AddVKey(0xE4, "OEM specific"),
	AddVKey(VK_PROCESSKEY, "Windows 95/98/Me, Windows NT 4.0, Windows 2000/XP: IME PROCESS key"),
	AddVKey(0xE6, "OEM specific"),
	AddVKey(0xE7, "Windows 2000/XP: Used to pass Unicode characters as if they were keystrokes. The VK_PACKET key is the low word of a 32-bit Virtual Key value used for non-keyboard input methods. For more information, see Remark in KEYBDINPUT, SendInput, WM_KEYDOWN, and WM_KEYUP"),
	AddVKey(0xE8, "Unassigned"),
	AddVKey(0xE9, "OEM specific"),
	AddVKey(0xEA, "OEM specific"),
	AddVKey(0xEB, "OEM specific"),
	AddVKey(0xEC, "OEM specific"),
	AddVKey(0xED, "OEM specific"),
	AddVKey(0xEF, "OEM specific"),
	AddVKey(0xF0, "OEM specific"),
	AddVKey(0xF1, "OEM specific"),
	AddVKey(0xF2, "OEM specific"),
	AddVKey(0xF3, "OEM specific"),
	AddVKey(0xF4, "OEM specific"),
	AddVKey(0xF5, "OEM specific"),
	AddVKey(VK_ATTN, "Attn key"),
	AddVKey(VK_CRSEL, "CrSel key"),
	AddVKey(VK_EXSEL, "ExSel key"),
	AddVKey(VK_EREOF, "Erase EOF key"),
	AddVKey(VK_PLAY, "Play key"),
	AddVKey(VK_ZOOM, "Zoom key"),
	AddVKey(VK_NONAME, "Reserved"),
	AddVKey(VK_PA1, "PA1 key"),
	AddVKey(VK_OEM_CLEAR, "Clear key"),
	AddVKey(0xFF, "Unknown Virtual-Key Code")
};


LPCSTR GetKeyName(USHORT VKey)
{
	int i = 0;
	for (i = 0; i < sizeof(vkis); i++)
	{
		if (VKey == vkis[i].VKey)
			return vkis[i].VKname;
	}
	return vkis[--i].VKname;
}


#endif