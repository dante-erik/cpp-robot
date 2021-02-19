#include <iostream>
#include "ScreenReader.hpp"

#define forever for(;;)
#define and &&
#define or ||

using std::cout, std::endl, std::flush;

BOOL colorEquality(RGBQUAD a, RGBQUAD b) {
    return a.rgbRed == b.rgbRed and a.rgbGreen == b.rgbGreen and a.rgbBlue == b.rgbBlue;
}

int main() {
    POINT cursor_pos;
    RGBQUAD color, prev_color;
    bool first = true;
    ScreenReader sr;
    cout << "Color Under Cursor:" << endl;
    forever {
        GetCursorPos(&cursor_pos);
        prev_color = color;
        color = sr.getPixel(cursor_pos.x - 2, cursor_pos.y - 2);
        sr.updatePixels();
        if(!colorEquality(color, prev_color) || first) {
            cout << "x: " << cursor_pos.x - 2 << "\ty: " << cursor_pos.y - 2 << "\t(r,g,b): (" << (INT)color.rgbRed << ',' << (INT)color.rgbGreen << ',' << (INT)color.rgbBlue << ')' << endl;
            first = false;
        }
    }
}