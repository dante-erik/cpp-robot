// Only include this file 1 time (extra includes are ignored)
#pragma once

// Includes
#include <Windows.h>

class ScreenReader {
    const char* windowClass, *windowDesc;
    HWND window;
    HDC windowDC;
    HDC captureDC;
    HBITMAP captureBitmap;
    BITMAPINFO bmi;
    RECT rect;
    RGBQUAD* pixels;

    LONG coordToIndex(LONG x, LONG y) const;

    void setup();
    void destroy();

    public:
    ScreenReader(); // Entire Screen
    ScreenReader(const char* windowClass, const char* windowDesc); // Specific Window
    ~ScreenReader();
    int updatePixels();
    // Useful Getters
    [[nodiscard]] RGBQUAD getPixel(LONG x, LONG y) const;
    [[nodiscard]] BYTE getRed(LONG x, LONG y) const;
    [[nodiscard]] BYTE getGreen(LONG x, LONG y) const;
    [[nodiscard]] BYTE getBlue(LONG x, LONG y) const;
    [[nodiscard]] LONG getNumPixels() const;
    [[nodiscard]] LONG getWidth() const;
    [[nodiscard]] LONG getHeight() const;

    // Useless Getters
    [[nodiscard]] const char* const& getWindowClass() const;
    [[nodiscard]] const char* const& getWindowDesc() const;
    [[nodiscard]] HWND const& getWindow() const;
    [[nodiscard]] HDC const& getWindowDC() const;
    [[nodiscard]] HDC const& getCaptureDC() const;
    [[nodiscard]] HBITMAP const& getCaptureBitmap() const;
    [[nodiscard]] BITMAPINFO const& getBitmapInfo() const;
    [[nodiscard]] RECT const& getRect() const;
    [[nodiscard]] RGBQUAD* const& getPixels() const;
};
