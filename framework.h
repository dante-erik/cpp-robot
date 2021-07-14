#pragma once

//#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <Windows.h>
#include <functional>

typedef struct tagPOINTD
{
    DOUBLE  x;
    DOUBLE  y;

    explicit operator POINT() {
        POINT p;
        p.x = static_cast<LONG>(x);
        p.y = static_cast<LONG>(y);
        return p;
    }
} POINTD, * PPOINTD, NEAR* NPPOINTD, FAR* LPPOINTD;

template <typename T, class Compare = std::less<T>>
inline T clamp(T const& obj, T const& min, T const& max, Compare comp = Compare{}) {
    if (comp(obj, min)) return min;
    else if (comp(max, obj)) return max;
    return obj;
}
