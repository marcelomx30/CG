#include "../include/Lights.h"
#include <cmath>

Color SpotLight::getIntensityAt(const Vector3& point) const {
    Vector3 lightDir = (position - point).normalized();
    double cosAngle = lightDir.dot(-direction);
    double cutoffCos = std::cos(cutoffAngle);
    
    if (cosAngle < cutoffCos) {
        return Color(0, 0, 0);
    }
    
    double factor = std::pow(cosAngle, falloff);
    return intensity * factor;
}
