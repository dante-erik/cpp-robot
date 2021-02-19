#include <cmath>
#include <iostream>
#include "EventWriter.hpp"

const double pi = std::acos(-1);

using std::cout, std::endl, std::flush;

int main() {
    /*
    steps - Refined way to control speed
    milliseconds - Heavy-handed way to control speed
    */
   constexpr bool logCursorPos = false;
   LONG width = 2560, height = 1440;
   cout << "Random..." << flush;
    for(int i = 0; i < 10; ++i) {
        LONG x = rand() % (2 * width), y = rand() % height;
        DWORD steps = 1<<(17 + rand() % 3);
        mouse::MoveCursor(x, y, steps, mouse::MoveType::LINEAR);
        if(logCursorPos) cout << "x: " << x << "\ty: " << y << "\tsteps: " << steps << endl;
    }
    cout << "done" << endl;
    cout << "Circle (radius=";
    LONG radius = 512;
    INT revolutions = 1 + rand() % 3;
    cout << radius << ", revolutions=" << revolutions << ")..." << flush;
    for(DOUBLE i = 0; i < 2 * revolutions * pi; i += 0.01) {
        LONG x = roundl(width / 2 + radius * std::cos(i)), y = roundl(height / 2 + radius * std::sin(i));
        mouse::MoveCursor(x, y, 1<<8, mouse::MoveType::LINEAR);
        if(logCursorPos) cout << "x: " << x << "\ty: " << y << "\ti: " << i << endl;
    }
    cout << "done";
}