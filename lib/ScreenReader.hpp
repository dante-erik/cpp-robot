// Only include this file 1 time (extra includes are ignored)
#pragma once

// Includes
#include <codecvt>
#include <locale>
#include <string>
#include <Windows.h>
#include "Color.hpp"

class ScreenReader
{
protected:
    std::string windowClass, windowDesc;
    HWND window = NULL;
    HDC windowDC = NULL;
    HDC captureDC = NULL;
    HBITMAP captureBitmap = NULL;
    BITMAPINFO bmi;
    RECT rect;
    RGBQUAD *pixels = NULL;

    LONG coordToIndex(LONG x, LONG y) const;

    void setup();
    void destroy();

public:
    ScreenReader();                                                // Entire Screen
    ScreenReader(std::string const& windowClass, std::string const& windowDesc); // Specific Window
    ~ScreenReader();
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
    [[nodiscard]] std::string const &getWindowClass() const;
    [[nodiscard]] std::string const &getWindowDesc() const;
    [[nodiscard]] HWND const &getWindow() const;
    [[nodiscard]] HDC const &getWindowDC() const;
    [[nodiscard]] HDC const &getCaptureDC() const;
    [[nodiscard]] HBITMAP const &getCaptureBitmap() const;
    [[nodiscard]] BITMAPINFO const &getBitmapInfo() const;
    [[nodiscard]] RECT const &getRect() const;
    [[nodiscard]] RGBQUAD *const &getPixels() const;

    [[nodiscard]] virtual DOUBLE getPixelDiff(LONG x, LONG y, RGBQUAD color) const;
    [[nodiscard]] virtual BOOL getPixelDiff(LONG x, LONG y, RGBQUAD color, DOUBLE tolerance) const;
    [[nodiscard]] virtual UINT getPixelsDiff(LONG x, LONG y, LONG width, LONG height, RGBQUAD color, DOUBLE tolerance) const;
    [[nodiscard]] virtual DOUBLE getPixelsDiffPercent(LONG x, LONG y, LONG width, LONG height, RGBQUAD color, DOUBLE tolerance) const;
};

inline LONG ScreenReader::coordToIndex(LONG x, LONG y) const
{
    if (x < 0)
    {
        x = 0;
    }
    else if (x >= getWidth())
    {
        x = getWidth() - 1;
    }
    if (y < 0)
    {
        y = 0;
    }
    else if (y >= getHeight())
    {
        y = getHeight() - 1;
    }
    return (getHeight() - y - 1) * getWidth() + x;
}

inline void ScreenReader::setup()
{
    GetWindowRect(window, &rect);
    LONG width = getWidth(), height = getHeight();
    windowDC = GetDC(window);
    captureDC = CreateCompatibleDC(windowDC);
    captureBitmap = CreateCompatibleBitmap(windowDC, width, height);
    SelectObject(captureDC, captureBitmap);

    BitBlt(captureDC, 0, 0, width, height, windowDC, 0, 0, SRCCOPY | CAPTUREBLT);

    bmi = {0};
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    pixels = new RGBQUAD[getNumPixels()];
}

inline void ScreenReader::destroy()
{
    delete[] pixels;
    if (window)
    {
        ReleaseDC(window, windowDC);
        DeleteDC(captureDC);
        DeleteObject(captureBitmap);
    }
}

inline ScreenReader::ScreenReader() : windowClass(""), windowDesc(""), bmi(), rect()
{
    window = GetDesktopWindow();
    if (window)
    {
        setup();
        updatePixels();
    }
}

inline std::wstring safeWstringConvert(std::string const& string) {
    std::wstring converted;
    int convertResult = MultiByteToWideChar(CP_UTF8, 0, string.c_str(), static_cast<int>(string.size()), NULL, 0);
    if (convertResult <= 0)
    {
        converted = L"Failure to convert its message text using MultiByteToWideChar: convertResult=";
        converted += std::to_wstring(convertResult);
    }
    else
    {
        converted.resize(static_cast<size_t>(convertResult) + 10);
        convertResult = MultiByteToWideChar(CP_UTF8, 0, string.c_str(), static_cast<int>(string.size()), &converted[0], static_cast<int>(converted.size()));
        if (convertResult <= 0)
        {
            converted = L"Failure to convert its message text using MultiByteToWideChar: convertResult=";
            converted += std::to_wstring(convertResult);
        }
    }
    return converted;
}

inline ScreenReader::ScreenReader(std::string const& windowClass, std::string const& windowDesc) : windowClass(windowClass), windowDesc(windowDesc), bmi(), rect()
{
    window = FindWindowW(static_cast<LPCWSTR>(safeWstringConvert(windowClass).c_str()), static_cast<LPCWSTR>(safeWstringConvert(windowDesc).c_str()));
    if (window)
    {
        setup();
        updatePixels();
    }
}

inline ScreenReader::~ScreenReader() { destroy(); }

inline int ScreenReader::updatePixels()
{
    return GetDIBits(
        captureDC,
        captureBitmap,
        0,
        getHeight(),
        pixels,
        &bmi,
        DIB_RGB_COLORS);
}

inline RGBQUAD ScreenReader::getPixel(LONG x, LONG y) const
{
    return pixels[coordToIndex(x, y)];
}

inline BYTE ScreenReader::getRed(LONG x, LONG y) const
{
    return getPixel(x, y).rgbRed;
}

inline BYTE ScreenReader::getGreen(LONG x, LONG y) const
{
    return getPixel(x, y).rgbGreen;
}

inline BYTE ScreenReader::getBlue(LONG x, LONG y) const
{
    return getPixel(x, y).rgbBlue;
}

inline LONG ScreenReader::getNumPixels() const
{
    return getWidth() * getHeight();
}

inline LONG ScreenReader::getWidth() const
{
    return rect.right - rect.left;
}

inline LONG ScreenReader::getHeight() const
{
    return rect.bottom - rect.top;
}

inline std::string const &ScreenReader::getWindowClass() const
{
    return windowClass;
}

inline std::string const &ScreenReader::getWindowDesc() const
{
    return windowDesc;
}

inline HWND const &ScreenReader::getWindow() const
{
    return window;
}

inline HDC const &ScreenReader::getWindowDC() const
{
    return windowDC;
}

inline HDC const &ScreenReader::getCaptureDC() const
{
    return captureDC;
}

inline HBITMAP const &ScreenReader::getCaptureBitmap() const
{
    return captureBitmap;
}

inline BITMAPINFO const &ScreenReader::getBitmapInfo() const
{
    return bmi;
}

inline RECT const &ScreenReader::getRect() const
{
    return rect;
}

inline RGBQUAD *const &ScreenReader::getPixels() const
{
    return pixels;
}

inline DOUBLE ScreenReader::getPixelDiff(LONG x, LONG y, RGBQUAD color) const {
    return color::diff(getPixel(x, y), color);
}

inline BOOL ScreenReader::getPixelDiff(LONG x, LONG y, RGBQUAD color, DOUBLE tolerance) const {
    return color::diffLE(getPixel(x, y), color, tolerance);
}

inline UINT ScreenReader::getPixelsDiff(LONG x, LONG y, LONG width, LONG height, RGBQUAD color, DOUBLE tolerance) const {
    const LONG w = getWidth(), h = getHeight();
    UINT count = 0;
    for(LONG i = (x < 0 ? 0 : x); i < x + width && i < w; ++i) {
        for(LONG j = (y < 0 ? 0 : y); j < y + height && j < h; ++j) {
            count += getPixelDiff(i, j, color, tolerance);
        }
    }
    return count;
}

inline DOUBLE ScreenReader::getPixelsDiffPercent(LONG x, LONG y, LONG width, LONG height, RGBQUAD color, DOUBLE tolerance) const {
    const LONG w = getWidth(), h = getHeight();
    LONG trueX = 0 < x ? x : 0;
    LONG trueY = 0 < y ? x : 0;
    LONG trueW = trueX + width <= w ? width : w - trueX;
    LONG trueH = trueY + height <= h ? height : h - trueY;
    DOUBLE area = static_cast<DOUBLE>(static_cast<LONG64>(trueW) * static_cast<LONG64>(trueH));
    return getPixelsDiff(x, y, width, height, color, tolerance) / area;
}
