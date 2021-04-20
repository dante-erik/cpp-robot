#pragma once

#include "EventWriter.hpp"
#include "ScreenReader.hpp"

class Robot : public ScreenReader
{
    typedef struct tagPOINTD
    {
        DOUBLE  x;
        DOUBLE  y;
    } POINTD, *PPOINTD, NEAR *NPPOINTD, FAR *LPPOINTD;

    POINTD translateLocation(DOUBLE x, DOUBLE y) const;
    POINT translateLocation(LONG  x, LONG y) const;
    POINT translateLocation(POINT p) const;

public:
    Robot();
    Robot(const char *windowClass, const char *windowDesc);
    ~Robot();
    void focusApplication();
    // Writer
    BOOL moveCursor(DOUBLE x, DOUBLE y, DWORD steps, mouse::MoveType type, const mouse::MoveParams* params = NULL, DWORD milliseconds = 0, bool absolute = false);
    // BOOL moveCursor(POINT p, DWORD steps, mouse::MoveType type, const mouse::MoveParams* params = NULL, DWORD milliseconds = 0, bool absolute = false);
    BOOL setCursorPos(LONG x, LONG y, bool absolute = false);
    // BOOL setCursorPos(POINT p, bool absolute = false);
    UINT leftDown(LONG x, LONG y, bool absolute = false);
    // UINT leftDown(POINT p, bool absolute = false);
    UINT leftDown();
    UINT leftUp(LONG x, LONG y, bool absolute = false);
    // UINT leftUp(POINT p, bool absolute = false);
    UINT leftUp();
    UINT rightDown(LONG x, LONG y, bool absolute = false);
    // UINT rightDown(POINT p, bool absolute = false);
    UINT rightDown();
    UINT rightUp(LONG x, LONG y, bool absolute = false);
    // UINT rightUp(POINT p, bool absolute = false);
    UINT rightUp();
    UINT leftClick(LONG x, LONG y, DWORD milliseconds = 0, bool absolute = false);
    // UINT leftClick(POINT p, DWORD milliseconds = 0, bool absolute = false);
    UINT leftClick(DWORD milliseconds = 0);
    UINT rightClick(LONG x, LONG y, DWORD milliseconds = 0, bool absolute = false);
    // UINT rightClick(POINT p, DWORD milliseconds = 0, bool absolute = false);
    UINT rightClick(DWORD milliseconds = 0);
    UINT leftDrag(DOUBLE x, DOUBLE y, DWORD steps, mouse::MoveType type, const mouse::MoveParams* params = NULL, DWORD milliseconds = 0, bool absolute = false);
    // UINT leftDrag(POINT p, DWORD steps, mouse::MoveType type, const mouse::MoveParams* params = NULL, DWORD milliseconds = 0, bool absolute = false);
    UINT rightDrag(DOUBLE x, DOUBLE y, DWORD steps, mouse::MoveType type, const mouse::MoveParams* params = NULL, DWORD milliseconds = 0, bool absolute = false);
    // UINT rightDrag(POINT p, DWORD steps, mouse::MoveType type, const mouse::MoveParams* params = NULL, DWORD milliseconds = 0, bool absolute = false);

    // Reader
    [[nodiscard]] RGBQUAD getPixel(LONG x, LONG y, BOOL absolute = false) const;
    [[nodiscard]] BYTE getRed(LONG x, LONG y, BOOL absolute = false) const;
    [[nodiscard]] BYTE getGreen(LONG x, LONG y, BOOL absolute = false) const;
    [[nodiscard]] BYTE getBlue(LONG x, LONG y, BOOL absolute = false) const;
    [[nodiscard]] DOUBLE getPixelDiff(LONG x, LONG y, RGBQUAD color, BOOL absolute = false) const;
    [[nodiscard]] BOOL getPixelDiff(LONG x, LONG y, RGBQUAD color, DOUBLE tolerance, BOOL absolute = false) const;
    [[nodiscard]] UINT getPixelsDiff(LONG x, LONG y, LONG width, LONG height, RGBQUAD color, DOUBLE tolerance, BOOL absolute = false) const;
    [[nodiscard]] DOUBLE getPixelsDiffPercent(LONG x, LONG y, LONG width, LONG height, RGBQUAD color, DOUBLE tolerance, BOOL absolute = false) const;
};

Robot::POINTD Robot::translateLocation(DOUBLE x, DOUBLE y) const
{
    POINTD pos;
    if (x < 0)
    {
        pos.x = rect.right + x;
    }
    else
    {
        pos.x = rect.left + x;
    }
    if (y < 0)
    {
        pos.y = rect.bottom + y;
    }
    else
    {
        pos.y = rect.top + y;
    }
    return pos;
}

POINT Robot::translateLocation(LONG x, LONG y) const
{
    POINT pos;
    if (x < 0)
    {
        pos.x = rect.right + x;
    }
    else
    {
        pos.x = rect.left + x;
    }
    if (y < 0)
    {
        pos.y = rect.bottom + y;
    }
    else
    {
        pos.y = rect.top + y;
    }
    return pos;
}

POINT Robot::translateLocation(POINT p) const
{
    return translateLocation(p.x, p.y);
}

Robot::Robot() : ScreenReader()
{
    if (getWindow())
    {
        focusApplication();
    }
}

Robot::Robot(const char *windowClass, const char *windowDesc) : ScreenReader(windowClass, windowDesc)
{
    if (getWindow())
    {
        focusApplication();
    }
}

Robot::~Robot() = default;

void Robot::focusApplication()
{
    SetForegroundWindow(window);
    SetActiveWindow(window);
    SetFocus(window);
}

BOOL Robot::moveCursor(DOUBLE x, DOUBLE y, DWORD steps, mouse::MoveType type, const mouse::MoveParams* params, DWORD milliseconds, bool absolute)
{
    POINTD tp;
    if(absolute){
        tp.x = x;
        tp.y = y;
    } else {
        tp = translateLocation(x, y);
    }
    return mouse::MoveCursor(tp.x, tp.y, steps, type, params, milliseconds);
}

// BOOL Robot::moveCursor(POINT p, DWORD steps, mouse::MoveType type, const mouse::MoveParams* params, DWORD milliseconds, bool absolute)
// {
//     return moveCursor(p.x, p.y, steps, type, params, milliseconds, absolute);
// }

BOOL Robot::setCursorPos(LONG x, LONG y, bool absolute)
{
    POINT tp;
    if(absolute){
        tp.x = x;
        tp.y = y;
    } else {
        tp = translateLocation(x, y);
    }
    return mouse::MoveCursor(tp.x, tp.y, 0);
}

// BOOL Robot::setCursorPos(POINT p, bool absolute)
// {
//     return setCursorPos(p.x, p.y, absolute);
// }

UINT Robot::leftDown(LONG x, LONG y, bool absolute)
{
    setCursorPos(x, y, absolute);
    return leftDown();
}

// UINT Robot::leftDown(POINT p, bool absolute)
// {
//     setCursorPos(p, absolute);
//     return leftDown();
// }

UINT Robot::leftDown()
{
    return mouse::LeftDown();
}

UINT Robot::leftUp(LONG x, LONG y, bool absolute)
{
    setCursorPos(x, y, absolute);
    return leftUp();
}

// UINT Robot::leftUp(POINT p, bool absolute)
// {
//     setCursorPos(p, absolute);
//     return leftUp();
// }

UINT Robot::leftUp()
{
    return mouse::LeftUp();
}

UINT Robot::rightDown(LONG x, LONG y, bool absolute)
{
    setCursorPos(x, y, absolute);
    return rightDown();
}

// UINT Robot::rightDown(POINT p, bool absolute)
// {
//     setCursorPos(p, absolute);
//     return rightDown();
// }

UINT Robot::rightDown()
{
    return mouse::RightDown();
}

UINT Robot::rightUp(LONG x, LONG y, bool absolute)
{
    setCursorPos(x, y, absolute);
    return rightUp();
}

// UINT Robot::rightUp(POINT p, bool absolute)
// {
//     setCursorPos(p, absolute);
//     return rightUp();
// }

UINT Robot::rightUp()
{
    return mouse::RightUp();
}

UINT Robot::leftClick(LONG x, LONG y, DWORD milliseconds, bool absolute)
{
    setCursorPos(x, y, absolute);
    return leftClick(milliseconds);
}

// UINT Robot::leftClick(POINT p, DWORD milliseconds, bool absolute)
// {
//     setCursorPos(p, absolute);
//     return leftClick(milliseconds, absolute);
// }

UINT Robot::leftClick(DWORD milliseconds)
{
    return mouse::LeftClick(milliseconds);
}

UINT Robot::rightClick(LONG x, LONG y, DWORD milliseconds, bool absolute)
{
    setCursorPos(x, y, absolute);
    return rightClick(milliseconds);
}

// UINT Robot::rightClick(POINT p, DWORD milliseconds, bool absolute)
// {
//     setCursorPos(p, absolute);
//     return rightClick(milliseconds);
// }

UINT Robot::rightClick(DWORD milliseconds)
{
    return mouse::RightClick(milliseconds);
}

UINT Robot::leftDrag(DOUBLE x, DOUBLE y, DWORD steps, mouse::MoveType type, const mouse::MoveParams* params, DWORD milliseconds, bool absolute)
{
    POINTD tp;
    if(absolute){
        tp.x = x;
        tp.y = y;
    } else {
        tp = translateLocation(x, y);
    }
    return mouse::LeftDrag(tp.x, tp.y, steps, type, params, milliseconds);
}

// UINT Robot::leftDrag(POINT p, DWORD steps, mouse::MoveType type, const mouse::MoveParams* params, DWORD milliseconds, bool absolute)
// {
//     return leftDrag(p.x, p.y, steps, type, params, milliseconds, absolute);
// }

UINT Robot::rightDrag(DOUBLE x, DOUBLE y, DWORD steps, mouse::MoveType type, const mouse::MoveParams* params, DWORD milliseconds, bool absolute)
{
    POINTD tp;
    if(absolute){
        tp.x = x;
        tp.y = y;
    } else {
        tp = translateLocation(x, y);
    }
    return mouse::RightDrag(tp.x, tp.y, steps, type, params, milliseconds);
}

// UINT Robot::rightDrag(POINT p, DWORD steps, mouse::MoveType type, const mouse::MoveParams* params, DWORD milliseconds, bool absolute)
// {
//     return rightDrag(p.x, p.y, steps, type, params, milliseconds, absolute);
// }

RGBQUAD Robot::getPixel(LONG x, LONG y, BOOL absolute) const {
    POINT tp;
    if(absolute){
        tp.x = x;
        tp.y = y;
    } else {
        tp = translateLocation(x, y);
    }
    return ScreenReader::getPixel(tp.x, tp.y);
}

BYTE Robot::getRed(LONG x, LONG y, BOOL absolute) const {
    POINT tp;
    if(absolute){
        tp.x = x;
        tp.y = y;
    } else {
        tp = translateLocation(x, y);
    }
    return ScreenReader::getRed(tp.x, tp.y);
}

BYTE Robot::getGreen(LONG x, LONG y, BOOL absolute) const {
    POINT tp;
    if(absolute){
        tp.x = x;
        tp.y = y;
    } else {
        tp = translateLocation(x, y);
    }
    return ScreenReader::getGreen(tp.x, tp.y);
}

BYTE Robot::getBlue(LONG x, LONG y, BOOL absolute) const {
    POINT tp;
    if(absolute){
        tp.x = x;
        tp.y = y;
    } else {
        tp = translateLocation(x, y);
    }
    return ScreenReader::getBlue(tp.x, tp.y);
}

DOUBLE Robot::getPixelDiff(LONG x, LONG y, RGBQUAD color, BOOL absolute) const {
    POINT tp;
    if(absolute){
        tp.x = x;
        tp.y = y;
    } else {
        tp = translateLocation(x, y);
    }
    return ScreenReader::getPixelDiff(tp.x, tp.y, color);
}

BOOL Robot::getPixelDiff(LONG x, LONG y, RGBQUAD color, DOUBLE tolerance, BOOL absolute) const {
    POINT tp;
    if(absolute){
        tp.x = x;
        tp.y = y;
    } else {
        tp = translateLocation(x, y);
    }
    return ScreenReader::getPixelDiff(tp.x, tp.y, color, tolerance);
}

UINT Robot::getPixelsDiff(LONG x, LONG y, LONG width, LONG height, RGBQUAD color, DOUBLE tolerance, BOOL absolute) const {
    POINT tp;
    if(absolute){
        tp.x = x;
        tp.y = y;
    } else {
        tp = translateLocation(x, y);
    }
    return ScreenReader::getPixelsDiff(tp.x, tp.y, width, height, color, tolerance);
}

DOUBLE Robot::getPixelsDiffPercent(LONG x, LONG y, LONG width, LONG height, RGBQUAD color, DOUBLE tolerance, BOOL absolute) const {
    POINT tp;
    if(absolute){
        tp.x = x;
        tp.y = y;
    } else {
        tp = translateLocation(x, y);
    }
    return ScreenReader::getPixelsDiffPercent(tp.x, tp.y, width, height, color, tolerance);
}

