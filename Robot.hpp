#pragma once

#include "EventWriter.hpp"
#include "ScreenReader.hpp"

class Robot : public ScreenReader
{
    POINT translateLocation(LONG x, LONG y) const;
    POINT translateLocation(POINT p) const;
public:
    Robot();
    Robot(const char *windowClass, const char *windowDesc);
    ~Robot();
    void focusApplication();
    BOOL moveCursor(LONG x, LONG y, DWORD steps, mouse::MoveType type, DWORD milliseconds = 0);
    BOOL moveCursor(POINT p, DWORD steps, mouse::MoveType type, DWORD milliseconds = 0);
    BOOL setCursorPos(LONG x, LONG y);
    BOOL setCursorPos(POINT p);
    UINT leftDown(LONG x, LONG y);
    UINT leftDown(POINT p);
    UINT leftDown();
    UINT leftUp(LONG x, LONG y);
    UINT leftUp(POINT p);
    UINT leftUp();
    UINT rightDown(LONG x, LONG y);
    UINT rightDown(POINT p);
    UINT rightDown();
    UINT rightUp(LONG x, LONG y);
    UINT rightUp(POINT p);
    UINT rightUp();
    UINT leftClick(LONG x, LONG y, DWORD milliseconds = 0);
    UINT leftClick(POINT p, DWORD milliseconds = 0);
    UINT leftClick(DWORD milliseconds = 0);
    UINT rightClick(LONG x, LONG y, DWORD milliseconds = 0);
    UINT rightClick(POINT p, DWORD milliseconds = 0);
    UINT rightClick(DWORD milliseconds = 0);
    UINT leftDrag(LONG x, LONG y, DWORD steps, mouse::MoveType type, DWORD milliseconds = 0);
    UINT leftDrag(POINT p, DWORD steps, mouse::MoveType type, DWORD milliseconds = 0);
    UINT rightDrag(LONG x, LONG y, DWORD steps, mouse::MoveType type, DWORD milliseconds = 0);
    UINT rightDrag(POINT p, DWORD steps, mouse::MoveType type, DWORD milliseconds = 0);
};

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
    focusApplication();
}

Robot::Robot(const char *windowClass, const char *windowDesc) : ScreenReader(windowClass, windowDesc)
{
    focusApplication();
}

Robot::~Robot() = default;

void Robot::focusApplication()
{
    SetForegroundWindow(window);
    SetActiveWindow(window);
    SetFocus(window);
}

BOOL Robot::moveCursor(LONG x, LONG y, DWORD steps, mouse::MoveType type, DWORD milliseconds)
{
    POINT tp = translateLocation(x, y);
    return mouse::MoveCursor(tp.x, tp.y, steps, type, milliseconds);
}

BOOL Robot::moveCursor(POINT p, DWORD steps, mouse::MoveType type, DWORD milliseconds)
{
    return moveCursor(p.x, p.y, steps, type, milliseconds);
}

BOOL Robot::setCursorPos(LONG x, LONG y)
{
    POINT tp = translateLocation(x, y);
    return mouse::MoveCursor(tp.x, tp.y, 0);
}

BOOL Robot::setCursorPos(POINT p)
{
    return setCursorPos(p.x, p.y);
}

UINT Robot::leftDown(LONG x, LONG y) {
    setCursorPos(x, y);
    return leftDown();
}

UINT Robot::leftDown(POINT p) {
    setCursorPos(p);
    return leftDown();
}

UINT Robot::leftDown() {
    return mouse::LeftDown();
}

UINT Robot::leftUp(LONG x, LONG y) {
    setCursorPos(x, y);
    return leftUp();
}

UINT Robot::leftUp(POINT p) {
    setCursorPos(p);
    return leftUp();
}

UINT Robot::leftUp() {
    return mouse::LeftUp();
}

UINT Robot::rightDown(LONG x, LONG y) {
    setCursorPos(x, y);
    return rightDown();
}

UINT Robot::rightDown(POINT p) {
    setCursorPos(p);
    return rightDown();
}

UINT Robot::rightDown() {
    return mouse::RightDown();
}

UINT Robot::rightUp(LONG x, LONG y) {
    setCursorPos(x, y);
    return rightUp();
}

UINT Robot::rightUp(POINT p) {
    setCursorPos(p);
    return rightUp();
}

UINT Robot::rightUp() {
    return mouse::RightUp();
}

UINT Robot::leftClick(LONG x, LONG y, DWORD milliseconds) {
    setCursorPos(x, y);
    return leftClick(milliseconds);
}

UINT Robot::leftClick(POINT p, DWORD milliseconds) {
    setCursorPos(p);
    return leftClick(milliseconds);
}

UINT Robot::leftClick(DWORD milliseconds) {
    return mouse::LeftClick(milliseconds);
}

UINT Robot::rightClick(LONG x, LONG y, DWORD milliseconds) {
    setCursorPos(x, y);
    return rightClick(milliseconds);
}

UINT Robot::rightClick(POINT p, DWORD milliseconds) {
    setCursorPos(p);
    return rightClick(milliseconds);
}

UINT Robot::rightClick(DWORD milliseconds) {
    return mouse::RightClick(milliseconds);
}

UINT Robot::leftDrag(LONG x, LONG y, DWORD steps, mouse::MoveType type, DWORD milliseconds) {
    POINT tp = translateLocation(x, y);
    return mouse::LeftDrag(tp.x, tp.y, steps, type, milliseconds);
}

UINT Robot::leftDrag(POINT p, DWORD steps, mouse::MoveType type, DWORD milliseconds) {
    return leftDrag(p.x, p.y, steps, type, milliseconds);
}

UINT Robot::rightDrag(LONG x, LONG y, DWORD steps, mouse::MoveType type, DWORD milliseconds) {
    POINT tp = translateLocation(x, y);
    return mouse::RightDrag(tp.x, tp.y, steps, type, milliseconds);
}

UINT Robot::rightDrag(POINT p, DWORD steps, mouse::MoveType type, DWORD milliseconds) {
    return rightDrag(p.x, p.y, steps, type, milliseconds);
}
