// Only include this file 1 time (extra includes are ignored)
#pragma once
#include <Windows.h>

UINT InputEvent(DWORD type, DWORD flag)
{
    INPUT Input = {0};
    Input.type = type;
    Input.mi.dwFlags = flag;
    return ::SendInput(1, &Input, sizeof(INPUT));
}

LONG roundl(DOUBLE value) {
    return (LONG) value + ((LONG) value <= (LONG)(value - 0.5));
}

/***********************************************
 ***              MOUSE Events              ***
 ***********************************************/

namespace mouse
{
    // Private Members
    namespace helpers {
        UINT MouseEvent(DWORD flag) { return InputEvent(INPUT_MOUSE, flag); }

        BOOL MoveCursorLinear(LONG x, LONG y, DWORD steps, DWORD milliseconds) {
            BOOL success = true;
            POINT cursor_pos;
            GetCursorPos(&cursor_pos);
            DOUBLE delta_x = x - cursor_pos.x, delta_y = y - cursor_pos.y;
            for(DWORD i = 0; i < steps; ++i) {
                if(milliseconds) { Sleep(milliseconds); }
                success = SetCursorPos(cursor_pos.x + roundl(i * delta_x / steps), cursor_pos.y + roundl(i * delta_y / steps)) && success;
            }
            return success;
        }
    }

    UINT LeftDown() { return helpers::MouseEvent(MOUSEEVENTF_LEFTDOWN); }

    UINT LeftUp() { return helpers::MouseEvent(MOUSEEVENTF_LEFTUP); }

    UINT RightDown() { return helpers::MouseEvent(MOUSEEVENTF_RIGHTDOWN); }

    UINT RightUp() { return helpers::MouseEvent(MOUSEEVENTF_RIGHTUP); }

    UINT LeftClick(DWORD milliseconds = 0)
    {
        UINT down = LeftDown();
        if (milliseconds != 0)
        {
            Sleep(milliseconds);
        }
        return down & LeftUp();
    }

    UINT RightClick(DWORD milliseconds = 0)
    {
        UINT down = RightDown();
        if (milliseconds != 0)
        {
            Sleep(milliseconds);
        }
        return down & RightUp();
    }

    enum class MoveType
    {
        LINEAR
    };

    BOOL MoveCursor(LONG x, LONG y, DWORD steps, MoveType type, DWORD milliseconds = 0)
    {
        if(steps == 0) {
            return SetCursorPos(x, y);
        }
        switch(type) {
            case MoveType::LINEAR: return helpers::MoveCursorLinear(x, y, steps, milliseconds);
            default: return false;
        }
    }
}