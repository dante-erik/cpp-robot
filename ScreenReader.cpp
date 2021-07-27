#include "pch.h"
#include "ScreenReader.hpp"
#include "framework.h"

LONG ScreenReader::coordToIndex(LONG x, LONG y) const
{
    return (getHeight() - clamp<LONG>(y, 0, getHeight()) - 1)
        * getWidth() + clamp<LONG>(x, 0, getWidth() - 1);
}

void ScreenReader::setup()
{
    GetWindowRect(m_WindowHandle, &m_Rectangle);
    LONG width = getWidth(), height = getHeight();
    m_WindowDC = GetDC(m_WindowHandle);
    m_CaptureDC = CreateCompatibleDC(m_WindowDC);
    m_CaptureBitmap = CreateCompatibleBitmap(m_WindowDC, width, height);
    SelectObject(m_CaptureDC, m_CaptureBitmap);

    BitBlt(m_CaptureDC, 0, 0, width, height, m_WindowDC, 0, 0, SRCCOPY | CAPTUREBLT);

    m_BitmapInfo = { 0 };
    m_BitmapInfo.bmiHeader.biSize = sizeof(m_BitmapInfo.bmiHeader);
    m_BitmapInfo.bmiHeader.biWidth = width;
    m_BitmapInfo.bmiHeader.biHeight = height;
    m_BitmapInfo.bmiHeader.biPlanes = 1;
    m_BitmapInfo.bmiHeader.biBitCount = 32;
    m_BitmapInfo.bmiHeader.biCompression = BI_RGB;

    m_Pixels = new RGBQUAD[getNumPixels()];
}

void ScreenReader::destroy()
{
    delete[] m_Pixels;
    if (m_WindowHandle)
    {
        ReleaseDC(m_WindowHandle, m_WindowDC);
        DeleteDC(m_CaptureDC);
        DeleteObject(m_CaptureBitmap);
    }
}

ScreenReader::ScreenReader() : m_WindowClass(""), m_WindowDescription(""), m_BitmapInfo(), m_Rectangle()
{
    m_WindowHandle = GetDesktopWindow();
    if (m_WindowHandle)
    {
        setup();
        updatePixels();
    }
}

std::wstring safeWstringConvert(std::string const& string) {
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

ScreenReader::ScreenReader(std::string const& windowClass, std::string const& windowDesc) : m_WindowClass(windowClass), m_WindowDescription(windowDesc), m_BitmapInfo(), m_Rectangle()
{
    m_WindowHandle = FindWindowW(static_cast<LPCWSTR>(safeWstringConvert(windowClass).c_str()), static_cast<LPCWSTR>(safeWstringConvert(windowDesc).c_str()));
    if (m_WindowHandle)
    {
        setup();
        updatePixels();
    }
}

ScreenReader::~ScreenReader() { destroy(); }

int ScreenReader::updatePixels()
{
    BitBlt(m_CaptureDC, 0, 0, getWidth(), getHeight(), m_WindowDC, 0, 0, SRCCOPY | CAPTUREBLT);

    return GetDIBits(
        m_CaptureDC,
        m_CaptureBitmap,
        0,
        getHeight(),
        m_Pixels,
        &m_BitmapInfo,
        DIB_RGB_COLORS);
}

RGBQUAD ScreenReader::getPixel(LONG x, LONG y) const
{
    LONG index = coordToIndex(x, y);
    return m_Pixels[clamp<LONG>(index, 0, getWidth() * getHeight() - 1)];
}

BYTE ScreenReader::getRed(LONG x, LONG y) const
{
    return getPixel(x, y).rgbRed;
}

BYTE ScreenReader::getGreen(LONG x, LONG y) const
{
    return getPixel(x, y).rgbGreen;
}

BYTE ScreenReader::getBlue(LONG x, LONG y) const
{
    return getPixel(x, y).rgbBlue;
}

LONG ScreenReader::getNumPixels() const
{
    return getWidth() * getHeight();
}

LONG ScreenReader::getWidth() const
{
    return m_Rectangle.right - m_Rectangle.left;
}

LONG ScreenReader::getHeight() const
{
    return m_Rectangle.bottom - m_Rectangle.top;
}

std::string const& ScreenReader::getWindowClass() const
{
    return m_WindowClass;
}

std::string const& ScreenReader::getWindowDesc() const
{
    return m_WindowDescription;
}

HWND const& ScreenReader::getWindow() const
{
    return m_WindowHandle;
}

HDC const& ScreenReader::getWindowDC() const
{
    return m_WindowDC;
}

HDC const& ScreenReader::getCaptureDC() const
{
    return m_CaptureDC;
}

HBITMAP const& ScreenReader::getCaptureBitmap() const
{
    return m_CaptureBitmap;
}

BITMAPINFO const& ScreenReader::getBitmapInfo() const
{
    return m_BitmapInfo;
}

RECT const& ScreenReader::getRect() const
{
    return m_Rectangle;
}

RGBQUAD* const& ScreenReader::getPixels() const
{
    return m_Pixels;
}

DOUBLE ScreenReader::getPixelDiff(LONG x, LONG y, RGBQUAD color) const {
    return Color::diff(getPixel(x, y), color);
}

BOOL ScreenReader::getPixelDiff(LONG x, LONG y, RGBQUAD color, DOUBLE tolerance) const {
    return Color::diffLE(getPixel(x, y), color, tolerance);
}

UINT ScreenReader::getPixelsDiff(LONG x, LONG y, LONG width, LONG height, RGBQUAD color, DOUBLE tolerance) const {
    const LONG w = getWidth(), h = getHeight();
    UINT count = 0;
    for (LONG i = (x < 0 ? 0 : x); i < x + width && i < w; ++i) {
        for (LONG j = (y < 0 ? 0 : y); j < y + height && j < h; ++j) {
            count += getPixelDiff(i, j, color, tolerance);
        }
    }
    return count;
}

DOUBLE ScreenReader::getPixelsDiffPercent(LONG x, LONG y, LONG width, LONG height, RGBQUAD color, DOUBLE tolerance) const {
    const LONG w = getWidth(), h = getHeight();
    LONG trueX = 0 < x ? x : 0;
    LONG trueY = 0 < y ? x : 0;
    LONG trueW = trueX + width <= w ? width : w - trueX;
    LONG trueH = trueY + height <= h ? height : h - trueY;
    DOUBLE area = static_cast<DOUBLE>(static_cast<LONG64>(trueW) * static_cast<LONG64>(trueH));
    return getPixelsDiff(x, y, width, height, color, tolerance) / area;
}