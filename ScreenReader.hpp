#pragma once

#include <Windows.h>
#include <string>


class ScreenReader
{
protected:
    std::string m_WindowClass, m_WindowDescription;
    HWND m_WindowHandle = NULL;
    HDC m_WindowDC = NULL;
    HDC m_CaptureDC = NULL;
    HBITMAP m_CaptureBitmap = NULL;
    BITMAPINFO m_BitmapInfo;
    RECT m_Rectangle;
    RGBQUAD* m_Pixels = NULL;

    LONG coordToIndex(LONG x, LONG y) const;

    void setup();
    void destroy();

public:
    ScreenReader();                                                // Entire Screen
    ScreenReader(std::string const& windowClass, std::string const& windowDesc); // Specific Window
    virtual ~ScreenReader();
    int updatePixels();

    // Useful Getters
    [[nodiscard]] virtual RGBQUAD getPixel(LONG x, LONG y) const;
    [[nodiscard]] virtual BYTE getRed(LONG x, LONG y) const;
    [[nodiscard]] virtual BYTE getGreen(LONG x, LONG y) const;
    [[nodiscard]] virtual BYTE getBlue(LONG x, LONG y) const;
    [[nodiscard]] LONG getNumPixels() const;
    [[nodiscard]] LONG getWidth() const;
    [[nodiscard]] LONG getHeight() const;

    // Useless Getters
    [[nodiscard]] std::string const& getWindowClass() const;
    [[nodiscard]] std::string const& getWindowDesc() const;
    [[nodiscard]] HWND const& getWindow() const;
    [[nodiscard]] HDC const& getWindowDC() const;
    [[nodiscard]] HDC const& getCaptureDC() const;
    [[nodiscard]] HBITMAP const& getCaptureBitmap() const;
    [[nodiscard]] BITMAPINFO const& getBitmapInfo() const;
    [[nodiscard]] RECT const& getRect() const;
    [[nodiscard]] RGBQUAD* const& getPixels() const;

    [[nodiscard]] virtual DOUBLE getPixelDiff(LONG x, LONG y, RGBQUAD color) const;
    [[nodiscard]] virtual BOOL getPixelDiff(LONG x, LONG y, RGBQUAD color, DOUBLE tolerance) const;
    [[nodiscard]] virtual UINT getPixelsDiff(LONG x, LONG y, LONG width, LONG height, RGBQUAD color, DOUBLE tolerance) const;
    [[nodiscard]] virtual DOUBLE getPixelsDiffPercent(LONG x, LONG y, LONG width, LONG height, RGBQUAD color, DOUBLE tolerance) const;
};

