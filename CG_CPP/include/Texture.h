#ifndef TEXTURE_H
#define TEXTURE_H

#include "Color.h"
#include "Vector3.h"
#include <string>
#include <memory>

class Texture {
private:
    unsigned char* data;
    int width;
    int height;
    int channels;
    bool loaded;

public:
    Texture();
    Texture(const std::string& filename);
    ~Texture();

    bool load(const std::string& filename);
    Color sample(double u, double v) const;  // UV em [0, 1]
    bool isLoaded() const { return loaded; }

    // Evita cópia acidental (textura pode ser grande)
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
};

// Classe gerenciadora de texturas (singleton pattern)
class TextureManager {
private:
    static std::shared_ptr<Texture> woodTexture;
    static std::shared_ptr<Texture> stainedGlassTexture;

public:
    static void loadTextures();
    static std::shared_ptr<Texture> getWoodTexture();
    static std::shared_ptr<Texture> getStainedGlassTexture();
};

// ============ FUNÇÕES DE MAPEAMENTO UV ============

// Mapeamento UV esférico (para esferas)
inline void sphericalUV(const Vector3& point, const Vector3& center, double radius, double& u, double& v) {
    Vector3 p = (point - center) / radius;  // Normaliza para esfera unitária

    // Coordenadas esféricas
    double theta = atan2(p.z, p.x);  // Ângulo horizontal [-π, π]
    double phi = asin(p.y);          // Ângulo vertical [-π/2, π/2]

    // Mapeia para [0, 1]
    u = (theta + M_PI) / (2 * M_PI);
    v = (phi + M_PI / 2) / M_PI;
}

// Mapeamento UV planar (para planos)
inline void planarUV(const Vector3& point, double& u, double& v, double scale = 1.0) {
    u = fmod(point.x * scale, 1.0);
    v = fmod(point.z * scale, 1.0);

    // Garante [0, 1]
    if (u < 0) u += 1.0;
    if (v < 0) v += 1.0;
}

#endif // TEXTURE_H
