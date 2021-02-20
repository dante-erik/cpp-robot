#include <iostream>
#include "Robot.hpp"

using std::cout, std::endl;

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
    paint.moveCursor(100, 200, 1 << 20, mouse::MoveType::LINEAR);
    paint.leftDrag(1000, 700, 1 << 20, mouse::MoveType::LINEAR);
    paint.moveCursor(100, 200, 1 << 20, mouse::MoveType::LINEAR);
    paint.leftDrag(500, 1000, 1 << 20, mouse::MoveType::LINEAR);
    paint.moveCursor(100, 200, 1 << 20, mouse::MoveType::LINEAR);
    paint.leftDrag(700, 1000, 1 << 20, mouse::MoveType::LINEAR);
    paint.leftDrag(1000, 700, 1 << 20, mouse::MoveType::LINEAR);
    cout << "done" << endl;
}