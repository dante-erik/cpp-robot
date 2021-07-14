#pragma once

#include "EventWriter.hpp"
#include "ScreenReader.hpp"
#include "framework.h"

class Robot : public ScreenReader
{
public:
    enum PositionMode {
        ABSOLUTE_POSITION,
        RELATIVE_POSITION
    };

private:
    PositionMode m_PositionMode;

    POINTD translateLocation(DOUBLE x, DOUBLE y) const;
    POINT translateLocation(LONG x, LONG y) const;
    POINT translateLocation(POINT p) const;

public:
    Robot(PositionMode positionMode = RELATIVE_POSITION);
    Robot(std::string const& windowClass, std::string const& windowDesc, PositionMode positionMode = RELATIVE_POSITION);
    virtual ~Robot();

    void focusApplication();
    PositionMode positionMode() const;
    void positionMode(PositionMode positionMode) const;

    // Writer
    BOOL moveCursor(DOUBLE x, DOUBLE y, DWORD steps, EventWriter::Mouse::MoveType type, const EventWriter::Mouse::MoveParams* params = NULL, DWORD milliseconds = 0);
    BOOL moveCursor(POINT p, DWORD steps, EventWriter::Mouse::MoveType type, const EventWriter::Mouse::MoveParams* params = NULL, DWORD milliseconds = 0);
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
    UINT leftDrag(DOUBLE x, DOUBLE y, DWORD steps, EventWriter::Mouse::MoveType type, const EventWriter::Mouse::MoveParams* params = NULL, DWORD milliseconds = 0);
    UINT leftDrag(POINT p, DWORD steps, EventWriter::Mouse::MoveType type, const EventWriter::Mouse::MoveParams* params = NULL, DWORD milliseconds = 0);
    UINT rightDrag(DOUBLE x, DOUBLE y, DWORD steps, EventWriter::Mouse::MoveType type, const EventWriter::Mouse::MoveParams* params = NULL, DWORD milliseconds = 0);
    UINT rightDrag(POINT p, DWORD steps, EventWriter::Mouse::MoveType type, const EventWriter::Mouse::MoveParams* params = NULL, DWORD milliseconds = 0);

    // Reader
    [[nodiscard]] RGBQUAD getPixel(LONG x, LONG y) const;
    [[nodiscard]] BYTE getRed(LONG x, LONG y) const;
    [[nodiscard]] BYTE getGreen(LONG x, LONG y) const;
    [[nodiscard]] BYTE getBlue(LONG x, LONG y) const;
    [[nodiscard]] DOUBLE getPixelDiff(LONG x, LONG y, RGBQUAD color) const;
    [[nodiscard]] BOOL getPixelDiff(LONG x, LONG y, RGBQUAD color, DOUBLE tolerance) const;
    [[nodiscard]] UINT getPixelsDiff(LONG x, LONG y, LONG width, LONG height, RGBQUAD color, DOUBLE tolerance) const;
    [[nodiscard]] DOUBLE getPixelsDiffPercent(LONG x, LONG y, LONG width, LONG height, RGBQUAD color, DOUBLE tolerance) const;
};
