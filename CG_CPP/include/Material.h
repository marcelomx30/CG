#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"
#include "Vector3.h"
#include <functional>

// Tipo de função para textura procedural
using TextureFunction = std::function<Color(const Vector3&)>;

class Material {
public:
    Color ka;  // Coeficiente ambiente
    Color kd;  // Coeficiente difuso
    Color ks;  // Coeficiente especular
    double shininess;  // Expoente especular
    TextureFunction texture;  // Textura procedural (opcional)

    Material()
        : ka(0.1, 0.1, 0.1), kd(0.7, 0.7, 0.7),
          ks(0.5, 0.5, 0.5), shininess(10.0), texture(nullptr) {}

    Material(const Color& ka, const Color& kd, const Color& ks, double shininess)
        : ka(ka), kd(kd), ks(ks), shininess(shininess), texture(nullptr) {}
    
    Material(const Color& ka, const Color& kd, const Color& ks, double shininess, TextureFunction tex)
        : ka(ka), kd(kd), ks(ks), shininess(shininess), texture(tex) {}
    
    // Retorna cor difusa (textura ou cor sólida)
    Color getDiffuseColor(const Vector3& point) const {
        if (texture) {
            return texture(point);
        }
        return kd;
    }
};

#endif // MATERIAL_H
