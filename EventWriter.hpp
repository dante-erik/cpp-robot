#pragma once
// Includes
#include <Windows.h>

// These methods are good for single input sends:
// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-sendinput
// MS DOCS on how to use SendInput and also how to do Batch Inputs

namespace EventWriter {

    /**********************************************
     ***              MOUSE Events              ***
     **********************************************/

    namespace Mouse
    {
        enum class MoveType
        {
            INSTANT, LINEAR, POLAR
        };

        struct MoveParams {};

        struct PolarParams : MoveParams
        {
            POINT origin;
        };

        BOOL MoveCursor(DOUBLE x, DOUBLE y, DWORD steps, MoveType type = MoveType::INSTANT, const MoveParams* params = NULL, DWORD milliseconds = 0);

        UINT LeftDown();

        UINT LeftUp();

        UINT RightDown();

        UINT RightUp();

        UINT leftClick(DWORD milliseconds = 0);

        UINT RightClick(DWORD milliseconds = 0);

        UINT LeftDrag(DOUBLE x, DOUBLE y, DWORD steps, MoveType type, const MoveParams* params = NULL, DWORD milliseconds = 0);

        UINT RightDrag(DOUBLE x, DOUBLE y, DWORD steps, MoveType type, const MoveParams* params = NULL, DWORD milliseconds = 0);
    }

    /***********************************************
     ***             KEYBOARD Events             ***
     ***********************************************/

    namespace Keyboard
    {
        UINT KeyDownVK(WORD VK);

        UINT KeyUpVK(WORD VK);

        UINT KeyDown(char key);

        UINT KeyUp(char key);

        UINT KeyDown(const char* keys, DWORD milliseconds = 0);

        UINT KeyUp(const char* keys, DWORD milliseconds = 0);

        UINT KeyTypeVK(WORD VK, DWORD milliseconds = 0);

        UINT KeyType(char key, DWORD milliseconds = 0);

        UINT KeyType(const char* word, DWORD milliseconds = 0);
    }
}