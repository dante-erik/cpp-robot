#pragma once

#include <cmath>
#include <Windows.h>

namespace color {
    DOUBLE diffSq(RGBQUAD color1, RGBQUAD color2) {
        BYTE redDiff = color1.rgbRed - color2.rgbRed;
        BYTE greenDiff = color1.rgbGreen - color2.rgbGreen;
        BYTE blueDiff = color1.rgbBlue - color2.rgbBlue;
        return redDiff*redDiff + greenDiff*greenDiff + blueDiff*blueDiff;
    }

    DOUBLE diff(RGBQUAD color1, RGBQUAD color2) {
        return std::sqrt(diffSq(color1, color2));
    }

    BOOL diffLT(RGBQUAD color1, RGBQUAD color2, DOUBLE threshold) {
        return diffSq(color1, color2) < threshold*threshold;
    }

    BOOL diffLE(RGBQUAD color1, RGBQUAD color2, DOUBLE threshold) {
        return diffSq(color1, color2) <= threshold*threshold;
    }

    BOOL diffGT(RGBQUAD color1, RGBQUAD color2, DOUBLE threshold) {
        return diffSq(color1, color2) > threshold*threshold;
    }

    BOOL diffGE(RGBQUAD color1, RGBQUAD color2, DOUBLE threshold) {
        return diffSq(color1, color2) >= threshold*threshold;
    }

    BOOL equal(RGBQUAD color1, RGBQUAD color2) {
        return !diffSq(color1, color2);
    }
}