#pragma once

#include <Windows.h>

#include <string>

#include "Pixel.hpp"

class Robot
{
private:
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
    Robot();
    Robot(std::string const& windowClass, std::string const& windowDesc);
    ~Robot();

    // Mouse
    /**
     * @brief Set the Cursor to a Position
     * 
     * @param p position of the cursor after set
     * @return BOOL success or failure
     */
    BOOL setCursorPos(const POINT& p);
    
    /**
     * @brief Moves and Presses the Left Mouse Button
     * 
     * @param p position of the cursor for the press
     * @return UINT error code
     */
    UINT leftDown(const POINT& p);

    /**
     * @brief Presses the Left Mouse Button
     * 
     * @return UINT error code
     */
    UINT leftDown();

    /**
     * @brief Moves and Releases the Left Mouse Button
     * 
     * @param p position of the cursor for the release
     * @return UINT error code
     */
    UINT leftUp(const POINT& p);

    /**
     * @brief Releases the Left Mouse Button
     * 
     * @return UINT error code
     */
    UINT leftUp();

    /**
     * @brief Moves and Presses the Right Mouse Button
     * 
     * @param p position of the cursor for the press
     * @return UINT error code
     */
    UINT rightDown(const POINT& p);

    /**
     * @brief Presses the Right Mouse Button
     * 
     * @return UINT error code
     */
    UINT rightDown();

    /**
     * @brief Moves and Releases the Right Mouse Button
     * 
     * @param p position of the cursor for the release
     * @return UINT error code
     */
    UINT rightUp(const POINT& p);

    /**
     * @brief Releases the Right Mouse Button
     * 
     * @return UINT error code
     */
    UINT rightUp();

    /**
     * @brief Moves and Clicks the Left Mouse Button
     * 
     * @param p position of the cursor for the click
     * @param clickDuration milliseconds
     * @return UINT error code
     */
    UINT leftClick(const POINT& p, DWORD clickDuration = 0);

    /**
     * @brief Clicks the Left Mouse Button
     * 
     * @param clickDuration milliseconds
     * @return UINT error code
     */
    UINT leftClick(DWORD clickDuration = 0);

    /**
     * @brief Moves and Clicks the Right Mouse Button
     * 
     * @param p position of the cursor for the click
     * @param clickDuration milliseconds
     * @return UINT error code
     */
    UINT rightClick(const POINT& p, DWORD clickDuration = 0);

    /**
     * @brief Clicks the Left Mouse Button
     * 
     * @param clickDuration milliseconds
     * @return UINT error code
     */
    UINT rightClick(DWORD clickDuration = 0);

    // Keyboard
    /**
     * @brief Presses the provided key
     * 
     * @param keyStroke character representing the key to press
     */
    void keyDown(char keyStroke);

    /**
     * @brief Presses the provided keys with the duration between each keystroke
     * 
     * @param keyStrokes characters representing the keys to press
     * @param durationBetweenKeyStrokes milliseconds between each keystroke
     */
    void keyDown(const char keyStrokes[], DWORD durationBetweenKeyStrokes = 0);

    /**
     * @brief Releases the provided key
     * 
     * @param keyStroke character representing the key to release
     */
    void keyUp(char keyStroke);
    
    /**
     * @brief Releases the provided keys with the duration between each keystroke
     * 
     * @param keyStrokes characters representing the keys to release
     * @param durationBetweenKeyStrokes milliseconds between each keystroke
     */
    void keyUp(const char keyStrokes[], DWORD durationBetweenKeyStrokes = 0);

    /**
     * @brief Clicks (types) the provided key with the duration between each press and release
     * 
     * @param keyStroke character representing the key to type
     * @param clickDuration milliseconds between each action
     */
    void keyClick(char keyStroke, DWORD clickDuration = 0);
    
    /**
     * @brief Clicks (types) the provided keys with the duration between each press and release (no additional duration between subsequent characters)
     * 
     * @param keyStrokes characters representing the keys to type
     * @param durationBetweenKeyStrokes milliseconds between each action
     */
    void keyClick(const char keyStrokes[], DWORD clickDurationForEachKey = 0);

    /**
     * @brief Presses Left Control, then the provided keyStroke, waits clickDuration milliseconds, then releases the provided keyStroke, and finally releases Left Control
     * 
     * @param keyStroke character representing the key to type
     * @param clickDuration milliseconds between each action
     */
    void ctrlPlusKeyClick(char keyStroke, DWORD clickDuration = 0);

    /**
     * @brief Presses Left Control, performs keyClick(keystrokes, clickDurationForEachKey), and finally releases Left Control
     * 
     * @param keyStrokes character representing the key to type
     * @param clickDurationForEachKey milliseconds between each action
     */
    void ctrlPlusKeyClick(const char keyStrokes[], DWORD clickDurationForEachKey = 0);

    /**
     * @brief Clicks the Enter Key
     * 
     * @param clickDuration milliseconds
     */
    void enterKeyClick(DWORD clickDuration = 0);
    
    /**
     * @brief Clicks the Escape Key
     * 
     * @param clickDuration milliseconds
     */
    void escapeKeyClick(DWORD clickDuration = 0);


    // Reader
    /**
     * @brief Updates the Screen Buffer
     * 
     */
    void updateScreenBuffer();

    /**
     * @brief Get the Red value for the POINT
     * 
     * @param p Point in the screen
     * @return BYTE red component of the point
     */
    [[nodiscard]] BYTE getRed(const POINT& p) const;

    /**
     * @brief Get the Green value for the POINT
     * 
     * @param p Point in the screen
     * @return BYTE green component of the point
     */
    [[nodiscard]] BYTE getGreen(const POINT& p) const;

    /**
     * @brief Get the Blue value for the POINT
     * 
     * @param p Point in the screen
     * @return BYTE blue component of the point
     */
    [[nodiscard]] BYTE getBlue(const POINT& p) const;

    /**
     * @brief Compares the Euclidean Color Distance between the provided Pixel and the Screen Buffer
     * 
     * @param pix Pixel to compare to the screen buffer
     * @param tolerance Value at which (or below) the difference is negligible
     * @return BOOL true - close enough; false - different
     */
    [[nodiscard]] BOOL isPixelSimilar(const Pixel& pix, unsigned short tolerance = 0.1) const;

    /**
     * @brief Determines if the provided Pixel matches the Screen Buffer
     * 
     * @param pix Pixel to compare to the screen buffer
     * @return BOOL true - equivalent; false - not equivalent
     */
    [[nodiscard]] BOOL getPixelEquiv(const Pixel& pix) const;
};
