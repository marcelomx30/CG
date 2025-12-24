#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"
#include "Vector3.h"

// Tipo de ponteiro para função de textura
typedef Color (*TextureFunctionPtr)(const Vector3&);

class Material {
public:
    Color ka;  // Coeficiente ambiente
    Color kd;  // Coeficiente difuso
    Color ks;  // Coeficiente especular
    double shininess;  // Expoente especular
    TextureFunctionPtr textureFunc;  // Ponteiro para função de textura

    Material()
        : ka(0.1, 0.1, 0.1), kd(0.7, 0.7, 0.7),
          ks(0.5, 0.5, 0.5), shininess(10.0), textureFunc(nullptr) {}

    Material(const Color& ka, const Color& kd, const Color& ks, double shininess)
        : ka(ka), kd(kd), ks(ks), shininess(shininess), textureFunc(nullptr) {}
    
    Material(const Color& ka, const Color& kd, const Color& ks, double shininess, TextureFunctionPtr texFunc)
        : ka(ka), kd(kd), ks(ks), shininess(shininess), textureFunc(texFunc) {}
    
    // Retorna cor difusa (textura ou cor sólida)
    Color getDiffuseColor(const Vector3& point) const {
        if (textureFunc) {
            return textureFunc(point);
        }
        return kd;
    }
};

#endif // MATERIAL_H
