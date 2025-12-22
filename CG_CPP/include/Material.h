#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"

class Material {
public:
    Color ka;  // Coeficiente ambiente
    Color kd;  // Coeficiente difuso
    Color ks;  // Coeficiente especular
    double shininess;  // Expoente especular

    Material()
        : ka(0.1, 0.1, 0.1), kd(0.7, 0.7, 0.7),
          ks(0.5, 0.5, 0.5), shininess(10.0) {}

    Material(const Color& ka, const Color& kd, const Color& ks, double shininess)
        : ka(ka), kd(kd), ks(ks), shininess(shininess) {}
};

#endif // MATERIAL_H
