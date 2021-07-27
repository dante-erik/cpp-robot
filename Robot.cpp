#include "pch.h"
#include "Robot.hpp"

#include <stdexcept>

template <typename P, typename NUMBER>
void relativeRelocate(P& pos, NUMBER x, NUMBER y, RECT const& rect) {
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
}

POINTD Robot::translateLocation(DOUBLE x, DOUBLE y) const
{
    POINTD pos;
    switch (m_PositionMode) {
    case ABSOLUTE_POSITION:
        pos.x = x;
        pos.y = y;
        break;
    case RELATIVE_POSITION:
        relativeRelocate(pos, x, y, m_Rectangle);
        break;
    default:
        throw std::invalid_argument("PositionMode not supported in Translate Location.");
    }

    return pos;
}

POINT Robot::translateLocation(LONG x, LONG y) const
{
    POINT pos;
    switch (m_PositionMode) {
    case PositionMode::ABSOLUTE_POSITION:
        pos.x = x;
        pos.y = y;
        break;
    case PositionMode::RELATIVE_POSITION:
        relativeRelocate(pos, x, y, m_Rectangle);
        break;
    default:
        throw std::invalid_argument("PositionMode not supported in Translate Location.");
    }

    return pos;
}

POINT Robot::translateLocation(POINT p) const
{
    return translateLocation(p.x, p.y);
}

Robot::Robot(PositionMode positionMode)
    : ScreenReader(), m_PositionMode(positionMode)
{
    if (getWindow())
    {
        focusApplication();
    }
}

Robot::Robot(std::string const& windowClass, std::string const& windowDesc, PositionMode positionMode)
    : ScreenReader(windowClass, windowDesc), m_PositionMode(positionMode)
{
    if (getWindow())
    {
        focusApplication();
    }
}

Robot::~Robot() = default;

void Robot::focusApplication()
{
    SetForegroundWindow(m_WindowHandle);
    SetActiveWindow(m_WindowHandle);
    SetFocus(m_WindowHandle);
}

BOOL Robot::moveCursor(DOUBLE x, DOUBLE y, DWORD steps, EventWriter::Mouse::MoveType type, const EventWriter::Mouse::MoveParams * params, DWORD milliseconds)
{
    POINTD tp = translateLocation(x, y);
    return EventWriter::Mouse::MoveCursor(tp.x, tp.y, steps, type, params, milliseconds);
}

BOOL Robot::moveCursor(POINT p, DWORD steps, EventWriter::Mouse::MoveType type, const EventWriter::Mouse::MoveParams * params, DWORD milliseconds)
{
    return moveCursor(p.x, p.y, steps, type, params, milliseconds);
}

BOOL Robot::setCursorPos(LONG x, LONG y)
{
    POINT tp = translateLocation(x, y);
    return EventWriter::Mouse::MoveCursor(tp.x, tp.y, 0);
}

BOOL Robot::setCursorPos(POINT p)
{
    return setCursorPos(p.x, p.y);
}

UINT Robot::leftDown(LONG x, LONG y)
{
    setCursorPos(x, y);
    return leftDown();
}

UINT Robot::leftDown(POINT p)
{
    setCursorPos(p);
    return leftDown();
}

UINT Robot::leftDown()
{
    return EventWriter::Mouse::LeftDown();
}

UINT Robot::leftUp(LONG x, LONG y)
{
    setCursorPos(x, y);
    return leftUp();
}

UINT Robot::leftUp(POINT p)
{
    setCursorPos(p);
    return leftUp();
}

UINT Robot::leftUp()
{
    return EventWriter::Mouse::LeftUp();
}

UINT Robot::rightDown(LONG x, LONG y)
{
    setCursorPos(x, y);
    return rightDown();
}

UINT Robot::rightDown(POINT p)
{
    setCursorPos(p);
    return rightDown();
}

UINT Robot::rightDown()
{
    return EventWriter::Mouse::RightDown();
}

UINT Robot::rightUp(LONG x, LONG y)
{
    setCursorPos(x, y);
    return rightUp();
}

UINT Robot::rightUp(POINT p)
{
    setCursorPos(p);
    return rightUp();
}

UINT Robot::rightUp()
{
    return EventWriter::Mouse::RightUp();
}

UINT Robot::leftClick(LONG x, LONG y, DWORD milliseconds)
{
    setCursorPos(x, y);
    return leftClick(milliseconds);
}

UINT Robot::leftClick(POINT p, DWORD milliseconds)
{
    setCursorPos(p);
    return leftClick(milliseconds);
}

UINT Robot::leftClick(DWORD milliseconds)
{
    return EventWriter::Mouse::leftClick(milliseconds);
}

UINT Robot::rightClick(LONG x, LONG y, DWORD milliseconds)
{
    setCursorPos(x, y);
    return rightClick(milliseconds);
}

UINT Robot::rightClick(POINT p, DWORD milliseconds)
{
    setCursorPos(p);
    return rightClick(milliseconds);
}

UINT Robot::rightClick(DWORD milliseconds)
{
    return EventWriter::Mouse::RightClick(milliseconds);
}

UINT Robot::leftDrag(DOUBLE x, DOUBLE y, DWORD steps, EventWriter::Mouse::MoveType type, const EventWriter::Mouse::MoveParams * params, DWORD milliseconds)
{
    POINTD tp = translateLocation(x, y);
    return EventWriter::Mouse::LeftDrag(tp.x, tp.y, steps, type, params, milliseconds);
}

UINT Robot::leftDrag(POINT p, DWORD steps, EventWriter::Mouse::MoveType type, const EventWriter::Mouse::MoveParams * params, DWORD milliseconds)
{
    return leftDrag(p.x, p.y, steps, type, params, milliseconds);
}

UINT Robot::rightDrag(DOUBLE x, DOUBLE y, DWORD steps, EventWriter::Mouse::MoveType type, const EventWriter::Mouse::MoveParams * params, DWORD milliseconds)
{
    POINTD tp = translateLocation(x, y);
    return EventWriter::Mouse::RightDrag(tp.x, tp.y, steps, type, params, milliseconds);
}

UINT Robot::rightDrag(POINT p, DWORD steps, EventWriter::Mouse::MoveType type, const EventWriter::Mouse::MoveParams * params, DWORD milliseconds)
{
    return rightDrag(p.x, p.y, steps, type, params, milliseconds);
}

RGBQUAD Robot::getPixel(LONG x, LONG y) const {
    POINT tp = translateLocation(x, y);
    return ScreenReader::getPixel(tp.x, tp.y);
}

BYTE Robot::getRed(LONG x, LONG y) const {
    POINT tp = translateLocation(x, y);
    return ScreenReader::getRed(tp.x, tp.y);
}

BYTE Robot::getGreen(LONG x, LONG y) const {
    POINT tp = translateLocation(x, y);
    return ScreenReader::getGreen(tp.x, tp.y);
}

BYTE Robot::getBlue(LONG x, LONG y) const {
    POINT tp = translateLocation(x, y);
    return ScreenReader::getBlue(tp.x, tp.y);
}

DOUBLE Robot::getPixelDiff(LONG x, LONG y, RGBQUAD color) const {
    POINT tp = translateLocation(x, y);
    return ScreenReader::getPixelDiff(tp.x, tp.y, color);
}

BOOL Robot::getPixelDiff(LONG x, LONG y, RGBQUAD color, DOUBLE tolerance) const {
    POINT tp = translateLocation(x, y);
    return ScreenReader::getPixelDiff(tp.x, tp.y, color, tolerance);
}

UINT Robot::getPixelsDiff(LONG x, LONG y, LONG width, LONG height, RGBQUAD color, DOUBLE tolerance) const {
    POINT tp = translateLocation(x, y);
    return ScreenReader::getPixelsDiff(tp.x, tp.y, width, height, color, tolerance);
}

DOUBLE Robot::getPixelsDiffPercent(LONG x, LONG y, LONG width, LONG height, RGBQUAD color, DOUBLE tolerance) const {
    POINT tp = translateLocation(x, y);
    return ScreenReader::getPixelsDiffPercent(tp.x, tp.y, width, height, color, tolerance);
}