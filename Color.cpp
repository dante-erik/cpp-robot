#include "pch.h"
#include "Color.hpp"

namespace Color {
    LONG diffSq(RGBQUAD color1, RGBQUAD color2)
    {
        SHORT redDiff = color1.rgbRed - color2.rgbRed;
        SHORT greenDiff = color1.rgbGreen - color2.rgbGreen;
        SHORT blueDiff = color1.rgbBlue - color2.rgbBlue;
        return redDiff * redDiff + greenDiff * greenDiff + blueDiff * blueDiff;
    }

    DOUBLE diff(RGBQUAD color1, RGBQUAD color2)
    {
        return std::sqrt(diffSq(color1, color2));
    }

    BOOL diffLT(RGBQUAD color1, RGBQUAD color2, DOUBLE threshold)
    {
        return diffSq(color1, color2) < threshold * threshold;
    }

    BOOL diffLE(RGBQUAD color1, RGBQUAD color2, DOUBLE threshold)
    {
        return diffSq(color1, color2) <= threshold * threshold;
    }

    BOOL diffGT(RGBQUAD color1, RGBQUAD color2, DOUBLE threshold)
    {
        return diffSq(color1, color2) > threshold * threshold;
    }

    BOOL diffGE(RGBQUAD color1, RGBQUAD color2, DOUBLE threshold)
    {
        return diffSq(color1, color2) >= threshold * threshold;
    }

    BOOL equal(RGBQUAD color1, RGBQUAD color2)
    {
        return !diffSq(color1, color2);
    }
}