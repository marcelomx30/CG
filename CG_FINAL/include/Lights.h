#ifndef LIGHTS_H
#define LIGHTS_H

#include "Vector3.h"
#include "Color.h"

class Light {
public:
    Color intensity;
    
    Light() : intensity(1, 1, 1) {}
    Light(const Color& intensity) : intensity(intensity) {}
    virtual ~Light() {}
};

class AmbientLight : public Light {
public:
    AmbientLight() {}
    AmbientLight(const Color& intensity) : Light(intensity) {}
};

class PointLight : public Light {
public:
    Vector3 position;
    
    PointLight() : position(0, 0, 0) {}
    PointLight(const Vector3& pos, const Color& intensity)
        : Light(intensity), position(pos) {}
};

class DirectionalLight : public Light {
public:
    Vector3 direction;
    
    DirectionalLight() : direction(0, -1, 0) {}
    DirectionalLight(const Vector3& dir, const Color& intensity)
        : Light(intensity), direction(dir.normalized()) {}
};

class SpotLight : public Light {
public:
    Vector3 position;
    Vector3 direction;
    double cutoffAngle;  // em radianos
    double falloff;
    
    SpotLight() : position(0, 0, 0), direction(0, -1, 0), cutoffAngle(0.5), falloff(1.0) {}
    SpotLight(const Vector3& pos, const Vector3& dir, const Color& intensity,
              double cutoffDegrees, double falloff = 1.0)
        : Light(intensity), position(pos), direction(dir.normalized()),
          cutoffAngle(cutoffDegrees * M_PI / 180.0), falloff(falloff) {}
    
    Color getIntensityAt(const Vector3& point) const;
};

#endif // LIGHTS_H
