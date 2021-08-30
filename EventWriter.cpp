// Includes
#include "pch.h"
#include "EventWriter.hpp"
#include <cmath>

// These methods are good for single input sends:
// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-sendinput
// MS DOCS on how to use SendInput and also how to do Batch Inputs

#ifndef KEYEVENTF_SCANCODE
#define KEYEVENTF_SCANCODE 0x0008
#endif

namespace EventWriter {
    UINT InputEvent(DWORD type, DWORD flag)
    {
        INPUT Input = { 0 };
        Input.type = type;
        Input.mi.dwFlags = flag;
        return ::SendInput(1, &Input, sizeof(INPUT));
    }

    UINT InputEvent(DWORD type, WORD scan, DWORD flag)
    {
        INPUT Input = { 0 };
        Input.type = type;
        Input.ki.wScan = scan;
        Input.ki.dwFlags = flag | KEYEVENTF_SCANCODE;
        return ::SendInput(1, &Input, sizeof(INPUT));
    }

    UINT InputEvent(DWORD type, WORD scan)
    {
        INPUT Input = { 0 };
        Input.type = type;
        Input.ki.wScan = scan | KEYEVENTF_SCANCODE;
        return ::SendInput(1, &Input, sizeof(INPUT));
    }

    inline LONG roundl(DOUBLE value) {
        return (LONG)value + ((LONG)value <= (LONG)(value - 0.5));
    }

    /**********************************************
     ***              MOUSE Events              ***
     **********************************************/

    namespace Mouse
    {
        // Private Members
        inline UINT MouseEvent(DWORD flag) { return InputEvent(INPUT_MOUSE, flag); }

        inline BOOL MoveCursorLinear(DOUBLE x, DOUBLE y, DWORD steps, DWORD milliseconds) {
            BOOL success = true;
            POINT cursor_pos;
            GetCursorPos(&cursor_pos);
            DOUBLE delta_x = x - cursor_pos.x, delta_y = y - cursor_pos.y;
            for (DWORD i = 0; i < steps; ++i) {
                if (milliseconds) { Sleep(milliseconds); }
                success = SetCursorPos(cursor_pos.x + roundl(i * delta_x / steps), cursor_pos.y + roundl(i * delta_y / steps)) && success;
            }
            return success;
        }

        inline BOOL MoveCursorPolar(DOUBLE r, DOUBLE t, DWORD steps, DWORD milliseconds, PolarParams const& origin) {
            t *= -1;
            BOOL success = true;
            POINT cursor_pos;
            GetCursorPos(&cursor_pos);
            cursor_pos.x -= origin.origin.x;
            cursor_pos.y -= origin.origin.y;
            DOUBLE radius = std::sqrt(cursor_pos.x * cursor_pos.x + cursor_pos.y * cursor_pos.y);
            DOUBLE theta = cursor_pos.x == 0 && cursor_pos.y == 0 ? t : std::atan2(cursor_pos.y, cursor_pos.x);
            DOUBLE delta_r = r - radius, delta_t = t - theta;
            for (DWORD i = 0; i < steps; ++i) {
                if (milliseconds) { Sleep(milliseconds); }
                success = SetCursorPos(origin.origin.x + roundl((radius + i * delta_r / steps) * std::cos(theta + i * delta_t / steps)), origin.origin.y + roundl((radius + i * delta_r / steps) * std::sin(theta + i * delta_t / steps))) && success;
            }
            GetCursorPos(&cursor_pos);
            cursor_pos.x -= origin.origin.x;
            cursor_pos.y -= origin.origin.y;
            radius = std::sqrt(cursor_pos.x * cursor_pos.x + cursor_pos.y * cursor_pos.y);
            theta = cursor_pos.x == 0 && cursor_pos.y == 0 ? t : std::atan2(cursor_pos.y, cursor_pos.x);
            return success;
        }

        // Public Members
        inline BOOL MoveCursor(DOUBLE x, DOUBLE y, DWORD steps, MoveType type, const MoveParams* params, DWORD milliseconds)
        {
            if (steps == 0 || type == MoveType::INSTANT) {
                return SetCursorPos(roundl(x), roundl(y));
            }
            switch (type) {
            case MoveType::LINEAR: return MoveCursorLinear(x, y, steps, milliseconds);
            case MoveType::POLAR: return MoveCursorPolar(x, y, steps, milliseconds, *((PolarParams*)params));
            case MoveType::INSTANT:
            default: return false;
            }
        }

        inline UINT LeftDown() { return MouseEvent(MOUSEEVENTF_LEFTDOWN); }

        inline UINT LeftUp() { return MouseEvent(MOUSEEVENTF_LEFTUP); }

        inline UINT RightDown() { return MouseEvent(MOUSEEVENTF_RIGHTDOWN); }

        inline UINT RightUp() { return MouseEvent(MOUSEEVENTF_RIGHTUP); }

        inline UINT LeftClick(DWORD milliseconds)
        {
            UINT down = LeftDown();
            if (milliseconds != 0)
            {
                Sleep(milliseconds);
            }
            return down & LeftUp();
        }

        inline UINT RightClick(DWORD milliseconds)
        {
            UINT down = RightDown();
            if (milliseconds != 0)
            {
                Sleep(milliseconds);
            }
            return down & RightUp();
        }

        inline UINT LeftDrag(DOUBLE x, DOUBLE y, DWORD steps, MoveType type, const MoveParams* params, DWORD milliseconds)
        {
            UINT down = LeftDown();
            MoveCursor(x, y, steps, type, params, milliseconds);
            return down & LeftUp();
        }

        inline UINT RightDrag(DOUBLE x, DOUBLE y, DWORD steps, MoveType type, const MoveParams* params, DWORD milliseconds)
        {
            UINT down = RightDown();
            MoveCursor(x, y, steps, type, params, milliseconds);
            return down & RightUp();
        }
    }

    /***********************************************
     ***             KEYBOARD Events             ***
     ***********************************************/

    namespace Keyboard
    {
        /****************************************************************************
        *
        * DirectInput keyboard scan codes
        *
        ****************************************************************************/
        namespace DirectInputScancodes
        {
            constexpr WORD DIK_ESCAPE = 0x01;
            constexpr WORD DIK_1 = 0x02;
            constexpr WORD DIK_2 = 0x03;
            constexpr WORD DIK_3 = 0x04;
            constexpr WORD DIK_4 = 0x05;
            constexpr WORD DIK_5 = 0x06;
            constexpr WORD DIK_6 = 0x07;
            constexpr WORD DIK_7 = 0x08;
            constexpr WORD DIK_8 = 0x09;
            constexpr WORD DIK_9 = 0x0A;
            constexpr WORD DIK_0 = 0x0B;
            constexpr WORD DIK_MINUS = 0x0C /* - on main keyboard */;
            constexpr WORD DIK_EQUALS = 0x0D;
            constexpr WORD DIK_BACK = 0x0E /* backspace */;
            constexpr WORD DIK_TAB = 0x0F;
            constexpr WORD DIK_Q = 0x10;
            constexpr WORD DIK_W = 0x11;
            constexpr WORD DIK_E = 0x12;
            constexpr WORD DIK_R = 0x13;
            constexpr WORD DIK_T = 0x14;
            constexpr WORD DIK_Y = 0x15;
            constexpr WORD DIK_U = 0x16;
            constexpr WORD DIK_I = 0x17;
            constexpr WORD DIK_O = 0x18;
            constexpr WORD DIK_P = 0x19;
            constexpr WORD DIK_LBRACKET = 0x1A;
            constexpr WORD DIK_RBRACKET = 0x1B;
            constexpr WORD DIK_RETURN = 0x1C /* Enter on main keyboard */;
            constexpr WORD DIK_LCONTROL = 0x1D;
            constexpr WORD DIK_A = 0x1E;
            constexpr WORD DIK_S = 0x1F;
            constexpr WORD DIK_D = 0x20;
            constexpr WORD DIK_F = 0x21;
            constexpr WORD DIK_G = 0x22;
            constexpr WORD DIK_H = 0x23;
            constexpr WORD DIK_J = 0x24;
            constexpr WORD DIK_K = 0x25;
            constexpr WORD DIK_L = 0x26;
            constexpr WORD DIK_SEMICOLON = 0x27;
            constexpr WORD DIK_APOSTROPHE = 0x28;
            constexpr WORD DIK_GRAVE = 0x29 /* accent grave */;
            constexpr WORD DIK_LSHIFT = 0x2A;
            constexpr WORD DIK_BACKSLASH = 0x2B;
            constexpr WORD DIK_Z = 0x2C;
            constexpr WORD DIK_X = 0x2D;
            constexpr WORD DIK_C = 0x2E;
            constexpr WORD DIK_V = 0x2F;
            constexpr WORD DIK_B = 0x30;
            constexpr WORD DIK_N = 0x31;
            constexpr WORD DIK_M = 0x32;
            constexpr WORD DIK_COMMA = 0x33;
            constexpr WORD DIK_PERIOD = 0x34 /* . on main keyboard */;
            constexpr WORD DIK_SLASH = 0x35 /* / on main keyboard */;
            constexpr WORD DIK_RSHIFT = 0x36;
            constexpr WORD DIK_MULTIPLY = 0x37 /* * on numeric keypad */;
            constexpr WORD DIK_LMENU = 0x38 /* left Alt */;
            constexpr WORD DIK_SPACE = 0x39;
            constexpr WORD DIK_CAPITAL = 0x3A;
            constexpr WORD DIK_F1 = 0x3B;
            constexpr WORD DIK_F2 = 0x3C;
            constexpr WORD DIK_F3 = 0x3D;
            constexpr WORD DIK_F4 = 0x3E;
            constexpr WORD DIK_F5 = 0x3F;
            constexpr WORD DIK_F6 = 0x40;
            constexpr WORD DIK_F7 = 0x41;
            constexpr WORD DIK_F8 = 0x42;
            constexpr WORD DIK_F9 = 0x43;
            constexpr WORD DIK_F10 = 0x44;
            constexpr WORD DIK_NUMLOCK = 0x45;
            constexpr WORD DIK_SCROLL = 0x46 /* Scroll Lock */;
            constexpr WORD DIK_NUMPAD7 = 0x47;
            constexpr WORD DIK_NUMPAD8 = 0x48;
            constexpr WORD DIK_NUMPAD9 = 0x49;
            constexpr WORD DIK_SUBTRACT = 0x4A /* - on numeric keypad */;
            constexpr WORD DIK_NUMPAD4 = 0x4B;
            constexpr WORD DIK_NUMPAD5 = 0x4C;
            constexpr WORD DIK_NUMPAD6 = 0x4D;
            constexpr WORD DIK_ADD = 0x4E /* + on numeric keypad */;
            constexpr WORD DIK_NUMPAD1 = 0x4F;
            constexpr WORD DIK_NUMPAD2 = 0x50;
            constexpr WORD DIK_NUMPAD3 = 0x51;
            constexpr WORD DIK_NUMPAD0 = 0x52;
            constexpr WORD DIK_DECIMAL = 0x53 /* . on numeric keypad */;
            constexpr WORD DIK_OEM_102 = 0x56 /* < > | on UK/Germany keyboards */;
            constexpr WORD DIK_F11 = 0x57;
            constexpr WORD DIK_F12 = 0x58;
            constexpr WORD DIK_F13 = 0x64 /* (NEC PC98) */;
            constexpr WORD DIK_F14 = 0x65 /* (NEC PC98) */;
            constexpr WORD DIK_F15 = 0x66 /* (NEC PC98) */;
            constexpr WORD DIK_KANA = 0x70 /* (Japanese keyboard) */;
            constexpr WORD DIK_ABNT_C1 = 0x73 /* / ? on Portugese (Brazilian) keyboards */;
            constexpr WORD DIK_CONVERT = 0x79 /* (Japanese keyboard) */;
            constexpr WORD DIK_NOCONVERT = 0x7B /* (Japanese keyboard) */;
            constexpr WORD DIK_YEN = 0x7D /* (Japanese keyboard) */;
            constexpr WORD DIK_ABNT_C2 = 0x7E /* Numpad . on Portugese (Brazilian) keyboards */;
            constexpr WORD DIK_NUMPADEQUALS = 0x8D /* = on numeric keypad (NEC PC98) */;
            constexpr WORD DIK_PREVTRACK = 0x90 /* Previous Track (DIK_CIRCUMFLEX on Japanese keyboard) */;
            constexpr WORD DIK_AT = 0x91 /* (NEC PC98) */;
            constexpr WORD DIK_COLON = 0x92 /* (NEC PC98) */;
            constexpr WORD DIK_UNDERLINE = 0x93 /* (NEC PC98) */;
            constexpr WORD DIK_KANJI = 0x94 /* (Japanese keyboard) */;
            constexpr WORD DIK_STOP = 0x95 /* (NEC PC98) */;
            constexpr WORD DIK_AX = 0x96 /* (Japan AX) */;
            constexpr WORD DIK_UNLABELED = 0x97 /* (J3100) */;
            constexpr WORD DIK_NEXTTRACK = 0x99 /* Next Track */;
            constexpr WORD DIK_NUMPADENTER = 0x9C /* Enter on numeric keypad */;
            constexpr WORD DIK_RCONTROL = 0x9D;
            constexpr WORD DIK_MUTE = 0xA0 /* Mute */;
            constexpr WORD DIK_CALCULATOR = 0xA1 /* Calculator */;
            constexpr WORD DIK_PLAYPAUSE = 0xA2 /* Play / Pause */;
            constexpr WORD DIK_MEDIASTOP = 0xA4 /* Media Stop */;
            constexpr WORD DIK_VOLUMEDOWN = 0xAE /* Volume - */;
            constexpr WORD DIK_VOLUMEUP = 0xB0 /* Volume + */;
            constexpr WORD DIK_WEBHOME = 0xB2 /* Web home */;
            constexpr WORD DIK_NUMPADCOMMA = 0xB3 /* , on numeric keypad (NEC PC98) */;
            constexpr WORD DIK_DIVIDE = 0xB5 /* / on numeric keypad */;
            constexpr WORD DIK_SYSRQ = 0xB7;
            constexpr WORD DIK_RMENU = 0xB8 /* right Alt */;
            constexpr WORD DIK_PAUSE = 0xC5 /* Pause */;
            constexpr WORD DIK_HOME = 0xC7 /* Home on arrow keypad */;
            constexpr WORD DIK_UP = 0xC8 /* UpArrow on arrow keypad */;
            constexpr WORD DIK_PRIOR = 0xC9 /* PgUp on arrow keypad */;
            constexpr WORD DIK_LEFT = 0xCB /* LeftArrow on arrow keypad */;
            constexpr WORD DIK_RIGHT = 0xCD /* RightArrow on arrow keypad */;
            constexpr WORD DIK_END = 0xCF /* End on arrow keypad */;
            constexpr WORD DIK_DOWN = 0xD0 /* DownArrow on arrow keypad */;
            constexpr WORD DIK_NEXT = 0xD1 /* PgDn on arrow keypad */;
            constexpr WORD DIK_INSERT = 0xD2 /* Insert on arrow keypad */;
            constexpr WORD DIK_DELETE = 0xD3 /* Delete on arrow keypad */;
            constexpr WORD DIK_LWIN = 0xDB /* Left Windows key */;
            constexpr WORD DIK_RWIN = 0xDC /* Right Windows key */;
            constexpr WORD DIK_APPS = 0xDD /* AppMenu key */;
            constexpr WORD DIK_POWER = 0xDE /* System Power */;
            constexpr WORD DIK_SLEEP = 0xDF /* System Sleep */;
            constexpr WORD DIK_WAKE = 0xE3 /* System Wake */;
            constexpr WORD DIK_WEBSEARCH = 0xE5 /* Web Search */;
            constexpr WORD DIK_WEBFAVORITES = 0xE6 /* Web Favorites */;
            constexpr WORD DIK_WEBREFRESH = 0xE7 /* Web Refresh */;
            constexpr WORD DIK_WEBSTOP = 0xE8 /* Web Stop */;
            constexpr WORD DIK_WEBFORWARD = 0xE9 /* Web Forward */;
            constexpr WORD DIK_WEBBACK = 0xEA /* Web Back */;
            constexpr WORD DIK_MYCOMPUTER = 0xEB /* My Computer */;
            constexpr WORD DIK_MAIL = 0xEC /* Mail */;
            constexpr WORD DIK_MEDIASELECT = 0xED /* Media Select */;
            /*
            * Alternate names for keys, to facilitate transition from DOS.
            */
            constexpr WORD DIK_BACKSPACE = DIK_BACK /* backspace */;
            constexpr WORD DIK_NUMPADSTAR = DIK_MULTIPLY /* * on numeric keypad */;
            constexpr WORD DIK_LALT = DIK_LMENU /* left Alt */;
            constexpr WORD DIK_CAPSLOCK = DIK_CAPITAL /* CapsLock */;
            constexpr WORD DIK_NUMPADMINUS = DIK_SUBTRACT /* - on numeric keypad */;
            constexpr WORD DIK_NUMPADPLUS = DIK_ADD /* + on numeric keypad */;
            constexpr WORD DIK_NUMPADPERIOD = DIK_DECIMAL /* . on numeric keypad */;
            constexpr WORD DIK_NUMPADSLASH = DIK_DIVIDE /* / on numeric keypad */;
            constexpr WORD DIK_RALT = DIK_RMENU /* right Alt */;
            constexpr WORD DIK_UPARROW = DIK_UP /* UpArrow on arrow keypad */;
            constexpr WORD DIK_PGUP = DIK_PRIOR /* PgUp on arrow keypad */;
            constexpr WORD DIK_LEFTARROW = DIK_LEFT /* LeftArrow on arrow keypad */;
            constexpr WORD DIK_RIGHTARROW = DIK_RIGHT /* RightArrow on arrow keypad */;
            constexpr WORD DIK_DOWNARROW = DIK_DOWN /* DownArrow on arrow keypad */;
            constexpr WORD DIK_PGDN = DIK_NEXT /* PgDn on arrow keypad */;
            /*
            * Alternate names for keys originally not used on US keyboards.
            */
            constexpr WORD DIK_CIRCUMFLEX = DIK_PREVTRACK /* Japanese keyboard */;
        }

        // Private Members
        inline UINT KeyboardEvent(WORD scan, DWORD flag) { return InputEvent(INPUT_KEYBOARD, scan, flag); }

        inline UINT KeyboardEvent(WORD scan) { return InputEvent(INPUT_KEYBOARD, scan); }

        // Public Members
        inline UINT KeyDown(WORD scan) {
            return KeyboardEvent(scan);
        }

        inline UINT KeyUp(WORD scan) {
            return KeyboardEvent(scan, KEYEVENTF_KEYUP);
        }

        /**
         * @brief Fetches the scancode for non-control chars whenever possible. Prefers codes in the keyboard, avoiding numpad.
         * 
         * Exceptions: '+', '*' use numpad
         * 
         * @param key - Char to generate scancode
         * @return WORD the scancode of the matching keyboard key regardless of letter case, 0 if none exist
         */
        inline WORD CharToScancode(char key) {
            switch(key) {
                case '0':
                return DirectInputScancodes::DIK_0;
                case '1':
                return DirectInputScancodes::DIK_1;
                case '2':
                return DirectInputScancodes::DIK_2;
                case '3':
                return DirectInputScancodes::DIK_3;
                case '4':
                return DirectInputScancodes::DIK_4;
                case '5':
                return DirectInputScancodes::DIK_5;
                case '6':
                return DirectInputScancodes::DIK_6;
                case '7':
                return DirectInputScancodes::DIK_7;
                case '8':
                return DirectInputScancodes::DIK_8;
                case '9':
                return DirectInputScancodes::DIK_9;
                case 'A':
                case 'a':
                return DirectInputScancodes::DIK_A;
                case 'B':
                case 'b':
                return DirectInputScancodes::DIK_B;
                case 'C':
                case 'c':
                return DirectInputScancodes::DIK_C;
                case 'D':
                case 'd':
                return DirectInputScancodes::DIK_D;
                case 'E':
                case 'e':
                return DirectInputScancodes::DIK_E;
                case 'F':
                case 'f':
                return DirectInputScancodes::DIK_F;
                case 'G':
                case 'g':
                return DirectInputScancodes::DIK_G;
                case 'H':
                case 'h':
                return DirectInputScancodes::DIK_H;
                case 'I':
                case 'i':
                return DirectInputScancodes::DIK_I;
                case 'J':
                case 'j':
                return DirectInputScancodes::DIK_J;
                case 'K':
                case 'k':
                return DirectInputScancodes::DIK_K;
                case 'L':
                case 'l':
                return DirectInputScancodes::DIK_L;
                case 'M':
                case 'm':
                return DirectInputScancodes::DIK_M;
                case 'N':
                case 'n':
                return DirectInputScancodes::DIK_N;
                case 'O':
                case 'o':
                return DirectInputScancodes::DIK_O;
                case 'P':
                case 'p':
                return DirectInputScancodes::DIK_P;
                case 'Q':
                case 'q':
                return DirectInputScancodes::DIK_Q;
                case 'R':
                case 'r':
                return DirectInputScancodes::DIK_R;
                case 'S':
                case 's':
                return DirectInputScancodes::DIK_S;
                case 'T':
                case 't':
                return DirectInputScancodes::DIK_T;
                case 'U':
                case 'u':
                return DirectInputScancodes::DIK_U;
                case 'V':
                case 'v':
                return DirectInputScancodes::DIK_V;
                case 'W':
                case 'w':
                return DirectInputScancodes::DIK_W;
                case 'X':
                case 'x':
                return DirectInputScancodes::DIK_X;
                case 'Y':
                case 'y':
                return DirectInputScancodes::DIK_Y;
                case 'Z':
                case 'z':
                return DirectInputScancodes::DIK_Z;
                case '-':
                return DirectInputScancodes::DIK_MINUS;
                case '=':
                return DirectInputScancodes::DIK_EQUALS;
                case '\t':
                return DirectInputScancodes::DIK_TAB;
                case '[':
                return DirectInputScancodes::DIK_LBRACKET;
                case ']':
                return DirectInputScancodes::DIK_RBRACKET;
                case '\n':
                return DirectInputScancodes::DIK_RETURN;
                case ';':
                return DirectInputScancodes::DIK_SEMICOLON;
                case '"':
                return DirectInputScancodes::DIK_APOSTROPHE;
                case '~':
                return DirectInputScancodes::DIK_GRAVE;
                case '\\':
                return DirectInputScancodes::DIK_BACKSLASH;
                case ',':
                return DirectInputScancodes::DIK_COMMA;
                case '.':
                return DirectInputScancodes::DIK_PERIOD;
                case '/':
                return DirectInputScancodes::DIK_SLASH;
                case '*':
                return DirectInputScancodes::DIK_MULTIPLY;
                case ' ':
                return DirectInputScancodes::DIK_SPACE;
                case '+':
                return DirectInputScancodes::DIK_ADD;
            }
            return static_cast<WORD>(0x0);
        }

        inline UINT KeyDown(char key) {
            return KeyDown(CharToScancode(key));
        }

        inline UINT KeyUp(char key) {
            return KeyUp(CharToScancode(key));
        }

        inline UINT KeyDown(const char* keys, DWORD milliseconds) {
            UINT down = KeyDown(keys[0]);
            for (UINT i = 1; keys[i]; ++i) {
                if (milliseconds) { Sleep(milliseconds); }
                down &= KeyDown(keys[i]);
            }
            return down;
        }

        inline UINT KeyUp(const char* keys, DWORD milliseconds) {
            UINT up = KeyUp(keys[0]);
            for (UINT i = 1; keys[i]; ++i) {
                if (milliseconds) { Sleep(milliseconds); }
                up &= KeyUp(keys[i]);
            }
            return up;
        }

        inline UINT KeyType(char key, DWORD milliseconds) {
            UINT down = KeyDown(key);
            if (milliseconds) { Sleep(milliseconds); }
            return down & KeyUp(key);
        }

        inline UINT KeyType(const char* word, DWORD milliseconds) {
            UINT typed = KeyType(word[0], milliseconds);
            for (UINT i = 1; word[i]; ++i) {
                if (milliseconds) { Sleep(milliseconds); }
                typed &= KeyType(word[i], milliseconds);
            }
            return typed;
        }
    }
}