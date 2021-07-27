// Includes
#include "pch.h"
#include "EventWriter.hpp"
#include <cmath>

// These methods are good for single input sends:
// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-sendinput
// MS DOCS on how to use SendInput and also how to do Batch Inputs

namespace EventWriter {
    UINT InputEvent(DWORD type, DWORD flag)
    {
        INPUT Input = { 0 };
        Input.type = type;
        Input.mi.dwFlags = flag;
        return ::SendInput(1, &Input, sizeof(INPUT));
    }

    UINT InputEvent(DWORD type, WORD VK, DWORD flag)
    {
        INPUT Input = { 0 };
        Input.type = type;
        Input.ki.wVk = VK;
        Input.ki.dwFlags = flag;
        return ::SendInput(1, &Input, sizeof(INPUT));
    }

    UINT InputEvent(DWORD type, WORD VK)
    {
        INPUT Input = { 0 };
        Input.type = type;
        Input.ki.wVk = VK;
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
        UINT MouseEvent(DWORD flag) { return InputEvent(INPUT_MOUSE, flag); }

        BOOL MoveCursorLinear(DOUBLE x, DOUBLE y, DWORD steps, DWORD milliseconds) {
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

        BOOL MoveCursorPolar(DOUBLE r, DOUBLE t, DWORD steps, DWORD milliseconds, PolarParams const& origin) {
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
        BOOL MoveCursor(DOUBLE x, DOUBLE y, DWORD steps, MoveType type, const MoveParams* params, DWORD milliseconds)
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

        UINT LeftDown() { return MouseEvent(MOUSEEVENTF_LEFTDOWN); }

        UINT LeftUp() { return MouseEvent(MOUSEEVENTF_LEFTUP); }

        UINT RightDown() { return MouseEvent(MOUSEEVENTF_RIGHTDOWN); }

        UINT RightUp() { return MouseEvent(MOUSEEVENTF_RIGHTUP); }

        UINT leftClick(DWORD milliseconds)
        {
            UINT down = LeftDown();
            if (milliseconds != 0)
            {
                Sleep(milliseconds);
            }
            return down & LeftUp();
        }

        UINT RightClick(DWORD milliseconds)
        {
            UINT down = RightDown();
            if (milliseconds != 0)
            {
                Sleep(milliseconds);
            }
            return down & RightUp();
        }

        UINT LeftDrag(DOUBLE x, DOUBLE y, DWORD steps, MoveType type, const MoveParams* params, DWORD milliseconds)
        {
            UINT down = LeftDown();
            MoveCursor(x, y, steps, type, params, milliseconds);
            return down & LeftUp();
        }

        UINT RightDrag(DOUBLE x, DOUBLE y, DWORD steps, MoveType type, const MoveParams* params, DWORD milliseconds)
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
        // Private Members
        UINT KeyboardEvent(WORD VK, DWORD flag) { return InputEvent(INPUT_KEYBOARD, VK, flag); }

        UINT KeyboardEvent(WORD VK) { return InputEvent(INPUT_KEYBOARD, VK); }

        // Public Members
        UINT KeyDownVK(WORD VK) {
            return KeyboardEvent(VK);
        }

        UINT KeyUpVK(WORD VK) {
            return KeyboardEvent(VK, KEYEVENTF_KEYUP);
        }

        UINT KeyDown(char key) {
            key = (char)toupper(key);
            return KeyDown((WORD)key);
        }

        UINT KeyUp(char key) {
            key = (char)toupper(key);
            return KeyUp((WORD)key);
        }

        UINT KeyDown(const char* keys, DWORD milliseconds) {
            UINT down = KeyDown(keys[0]);
            for (UINT i = 1; keys[i]; ++i) {
                if (milliseconds) { Sleep(milliseconds); }
                down &= KeyDown(keys[i]);
            }
            return down;
        }

        UINT KeyUp(const char* keys, DWORD milliseconds) {
            UINT up = KeyUp(keys[0]);
            for (UINT i = 1; keys[i]; ++i) {
                if (milliseconds) { Sleep(milliseconds); }
                up &= KeyUp(keys[i]);
            }
            return up;
        }

        UINT KeyTypeVK(WORD VK, DWORD milliseconds) {
            UINT down = KeyDown(VK);
            if (milliseconds) { Sleep(milliseconds); }
            return down & KeyUp(VK);
        }

        UINT KeyType(char key, DWORD milliseconds) {
            UINT down = KeyDown(key);
            if (milliseconds) { Sleep(milliseconds); }
            return down & KeyUp(key);
        }

        UINT KeyType(const char* word, DWORD milliseconds) {
            UINT typed = KeyType(word[0], milliseconds);
            for (UINT i = 1; word[i]; ++i) {
                if (milliseconds) { Sleep(milliseconds); }
                typed &= KeyType(word[i], milliseconds);
            }
            return typed;
        }
    }
}