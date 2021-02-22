#include <iostream>
#include "Color.hpp"

using std::cout, std::endl;

int main() {
    cout << "Black-Gray Diff: " << color::diff(color::colors::BLACK, color::colors::GRAY) << endl;
    cout << "Black-White Diff: " << color::diff(color::colors::BLACK, color::colors::WHITE) << endl;
    cout << "Gray-White Diff: " << color::diff(color::colors::GRAY, color::colors::WHITE) << endl;
    cout << "Black-DarkOrange Diff: " << color::diff(color::colors::BLACK, color::colors::DARK_ORANGE) << endl;
    cout << "Red-White Diff: " << color::diff(color::colors::RED, color::colors::WHITE) << endl;
    cout << "Red-SkyBlue Diff: " << color::diff(color::colors::RED, color::colors::SKY_BLUE) << endl;
    cout << "White-SkyBlue Diff: " << color::diff(color::colors::WHITE, color::colors::SKY_BLUE) << endl;
}