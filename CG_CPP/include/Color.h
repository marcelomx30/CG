#ifndef COLOR_H
#define COLOR_H

#include <algorithm>
#include <iostream>

class Color {
public:
    double r, g, b;

    Color() : r(0), g(0), b(0) {}
    Color(double r, double g, double b) : r(r), g(g), b(b) {}

    Color operator+(const Color& c) const {
        return Color(r + c.r, g + c.g, b + c.b);
    }

    Color operator*(const Color& c) const {
        return Color(r * c.r, g * c.g, b * c.b);
    }

    Color operator*(double t) const {
        return Color(r * t, g * t, b * t);
    }

    Color operator/(double t) const {
        return Color(r / t, g / t, b / t);
    }

    void clamp(double minVal = 0.0, double maxVal = 1.0) {
        r = std::max(minVal, std::min(maxVal, r));
        g = std::max(minVal, std::min(maxVal, g));
        b = std::max(minVal, std::min(maxVal, b));
    }

    // Converte para RGB 0-255
    void toRGB(int& ir, int& ig, int& ib) const {
        ir = static_cast<int>(std::max(0.0, std::min(255.0, r * 255.0)));
        ig = static_cast<int>(std::max(0.0, std::min(255.0, g * 255.0)));
        ib = static_cast<int>(std::max(0.0, std::min(255.0, b * 255.0)));
    }
};

inline Color operator*(double t, const Color& c) {
    return c * t;
}

// Cores pré-definidas
namespace Colors {
    const Color BLACK(0, 0, 0);
    const Color WHITE(1, 1, 1);
    const Color RED(1, 0, 0);
    const Color GREEN(0, 1, 0);
    const Color BLUE(0, 0, 1);
    const Color YELLOW(1, 1, 0);
    const Color CYAN(0, 1, 1);
    const Color MAGENTA(1, 0, 1);
}

#endif // COLOR_H
