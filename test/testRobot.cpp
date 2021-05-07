#include <cmath>
#include <iostream>
#include <vector>
#include "../lib/Robot.hpp"

using std::cout, std::endl;
using std::vector;
using std::sin;

// From Spy++
// "Window Description" WINDOW_CLASS
// == Login Client ==
// "Riot Client" RCLIENT
// == Buggy Client to start games ==
// "League of Legends" RCLIENT
// == Game itself ==
// League of Legends (TM) Client" RiotWindowClass

const DOUBLE PI = std::acos(-1);
const DOUBLE TWO_PI = 2*PI;
const DOUBLE HALF_PI = PI/2;

int main() {
    cout << "Open MS Paint" << endl;
    cout << "Paint Drawing...";
    Robot paint("MSPaintApp", "Untitled - Paint");
    if(!paint.getWindow()) {
        cout << "error: Window failed to open" << endl;
        return 1;
    }
    constexpr unsigned int NUM_POINTS = 5;
    constexpr unsigned int sleep = 1000;
    const unsigned int x_border = paint.getWidth() / 100;
    const unsigned int y_border = paint.getHeight() / 100;
    const unsigned int y_top = 200;
    const unsigned int y_bottom = paint.getHeight() - y_border;
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
    cout << "Paint Circle...";
    mouse::PolarParams pp;
    constexpr int radius = 250;
    RECT paintRect = paint.getRect();
    pp.origin.x = paintRect.left + paint.getWidth() / 2;
    pp.origin.y = paintRect.top + paint.getHeight() / 2;
    paint.moveCursor(radius, 0, 1 << 18, mouse::MoveType::POLAR, &pp, 0, true);
    Sleep(sleep);
    paint.leftDrag(radius, TWO_PI, 1 << 18, mouse::MoveType::POLAR, &pp, 0, true);
    cout << "done" << endl;
    cout << "Random Moves...";
    for(int i = 0; i < 10; ++i) {
        paint.leftDrag(x_border + rand() % (paint.getWidth() - 2*(x_border + y_top)), y_top + rand() % (y_bottom-y_top), 1 << 19, mouse::MoveType::LINEAR);
    }
    cout << "done" << endl;
    cout << "Random Polar Moves...";
    for(int i = 0; i < 10; ++i) {
        paint.leftDrag(rand() % (paint.getHeight() / 4), (rand() % 628) / 100., 1 << 19, mouse::MoveType::POLAR, &pp, 0, true);
    }
    cout << "done" << endl;
}