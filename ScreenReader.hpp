// Only include this file 1 time (extra includes are ignored)
#pragma once

// Includes
#include <Windows.h>

class ScreenReader
{
protected:
    const char *windowClass, *windowDesc;
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
    ScreenReader(const char *windowClass, const char *windowDesc); // Specific Window
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
    [[nodiscard]] const char *const &getWindowClass() const;
    [[nodiscard]] const char *const &getWindowDesc() const;
    [[nodiscard]] HWND const &getWindow() const;
    [[nodiscard]] HDC const &getWindowDC() const;
    [[nodiscard]] HDC const &getCaptureDC() const;
    [[nodiscard]] HBITMAP const &getCaptureBitmap() const;
    [[nodiscard]] BITMAPINFO const &getBitmapInfo() const;
    [[nodiscard]] RECT const &getRect() const;
    [[nodiscard]] RGBQUAD *const &getPixels() const;
};

LONG ScreenReader::coordToIndex(LONG x, LONG y) const {
    return (getHeight()-y-1)*getWidth()+x;
}

void ScreenReader::setup() {
    GetWindowRect(window, &rect);
    LONG width = getWidth(), height = getHeight();
    windowDC = GetDC(window);
    captureDC = CreateCompatibleDC(windowDC);
    captureBitmap = CreateCompatibleBitmap(windowDC, width, height);
    SelectObject(captureDC, captureBitmap);

    BitBlt(captureDC, 0, 0, width, height, windowDC, 0,0, SRCCOPY|CAPTUREBLT);

    bmi = {0}; 
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader); 
    bmi.bmiHeader.biWidth = width; 
    bmi.bmiHeader.biHeight = height; 
    bmi.bmiHeader.biPlanes = 1; 
    bmi.bmiHeader.biBitCount = 32; 
    bmi.bmiHeader.biCompression = BI_RGB;

    pixels = new RGBQUAD[getNumPixels()];
}

void ScreenReader::destroy() {
    delete [] pixels; 
    if(window) {
        ReleaseDC(window, windowDC);
        DeleteDC(captureDC);
        DeleteObject(captureBitmap);
    }
}

ScreenReader::ScreenReader() : windowClass(nullptr), windowDesc(nullptr) {
    window = GetDesktopWindow();
    if(window) {
        setup();
        updatePixels();
    }
}

ScreenReader::ScreenReader(const char* windowClass, const char* windowDesc) : windowClass(windowClass), windowDesc(windowDesc) {
    window = FindWindow(windowClass, windowDesc);
    if(window) {
        setup();
        updatePixels();
    }
}

ScreenReader::~ScreenReader() { destroy(); }

int ScreenReader::updatePixels() {
    return GetDIBits(
        captureDC,
        captureBitmap,
        0,
        getHeight(),
        pixels,
        &bmi,
        DIB_RGB_COLORS
    );
}

RGBQUAD ScreenReader::getPixel(LONG x, LONG y) const {
    return pixels[coordToIndex(x, y)];
}

BYTE ScreenReader::getRed(LONG x, LONG y) const {
    return getPixel(x, y).rgbRed;
}

BYTE ScreenReader::getGreen(LONG x, LONG y) const {
    return getPixel(x, y).rgbGreen;
}

BYTE ScreenReader::getBlue(LONG x, LONG y) const {
    return getPixel(x, y).rgbBlue;
}

LONG ScreenReader::getNumPixels() const {
    return getWidth() * getHeight();
}

LONG ScreenReader::getWidth() const {
    return rect.right - rect.left;
}

LONG ScreenReader::getHeight() const {
    return rect.bottom - rect.top;
}

const char* const& ScreenReader::getWindowClass() const {
    return windowClass;
}

const char* const& ScreenReader::getWindowDesc() const {
    return windowDesc;
}

HWND const& ScreenReader::getWindow() const {
    return window;
}

HDC const& ScreenReader::getWindowDC() const {
    return windowDC;
}

HDC const& ScreenReader::getCaptureDC() const {
    return captureDC;
}

HBITMAP const& ScreenReader::getCaptureBitmap() const {
    return captureBitmap;
}

BITMAPINFO const& ScreenReader::getBitmapInfo() const {
    return bmi;
}

RECT const& ScreenReader::getRect() const {
    return rect;
}

RGBQUAD* const& ScreenReader::getPixels() const {
    return pixels;
}
