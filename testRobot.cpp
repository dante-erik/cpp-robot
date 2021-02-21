#include <iostream>
#include <vector>
#include "Robot.hpp"

using std::cout, std::endl;
using std::vector;

// From Spy++
// "Window Description" WINDOW_CLASS
// == Login Client ==
// "Riot Client" RCLIENT
// == Buggy Client to start games ==
// "League of Legends" RCLIENT
// == Game itself ==
// League of Legends (TM) Client" RiotWindowClass


int main() {
    cout << "Open MS Paint" << endl;
    cout << "Paint Drawing...";
    Robot paint("MSPaintApp", "Untitled - Paint");
    if(!paint.getWindow()) {
        cout << "error: Window failed to open" << endl;
        return 1;
    }
    constexpr unsigned int NUM_POINTS = 5;
    constexpr unsigned int x_border = 50;
    constexpr unsigned int y_top = 200;
    constexpr unsigned int y_bottom = 1000;
    constexpr unsigned int sleep = 100;
    POINT origin;
    origin.x = x_border;
    origin.y = y_top;
    vector<POINT> points;
    for(unsigned int i = 0; i < NUM_POINTS; ++i) {
        POINT p;
        p.x = x_border + LONG((paint.getWidth() - 2 * x_border) * ((DOUBLE) i) / NUM_POINTS);
        p.y = y_bottom;
        points.push_back(p);
    }
    for(unsigned int i = 0; i < NUM_POINTS; ++i) {
        paint.setCursorPos(origin);
        Sleep(sleep);
        paint.leftDrag(points[i], 1 << 18, mouse::MoveType::LINEAR);
    }
    cout << "done" << endl;
}