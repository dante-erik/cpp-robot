#include <fstream>
#include <iostream>
#include "../lib/ScreenReader.hpp"

#define forever for(;;)
#define and &&
#define or ||

using std::cout, std::endl, std::flush;
using std::ofstream;

BOOL colorEquality(RGBQUAD a, RGBQUAD b) {
    return a.rgbRed == b.rgbRed and a.rgbGreen == b.rgbGreen and a.rgbBlue == b.rgbBlue;
}

int main() {
    POINT cursor_pos;
    RGBQUAD color, prev_color;
    ScreenReader paint("MSPaintApp", "Untitled - Paint");
    cout << "Paint Screenshot...";
    if(!paint.getWindow()) {
        cout << "error: Window failed to open" << endl;
        return 1;
    }
    ofstream file("paint.ppm");
    file << "P3\n" << paint.getWidth() << " " << paint.getHeight() << "\n255\n";
    for(LONG y = 0; y < paint.getHeight(); ++y) {
        for(LONG x = 0; x < paint.getWidth(); ++x) {
            color = paint.getPixel(x, y);
            file << (INT)color.rgbRed << " " << (INT)color.rgbGreen << " " << (INT)color.rgbBlue << "\n";
        }
    }
    file << flush;
    cout << "done";
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