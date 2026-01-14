#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#include "../include/Texture.h"
#include <iostream>
#include <cmath>

using namespace std;

// ============ CLASSE TEXTURE ============

Texture::Texture() : data(nullptr), width(0), height(0), channels(0), loaded(false) {}

Texture::Texture(const std::string& filename) : data(nullptr), width(0), height(0), channels(0), loaded(false) {
    load(filename);
}

Texture::~Texture() {
    if (data) {
        stbi_image_free(data);
        data = nullptr;
    }
}

bool Texture::load(const std::string& filename) {
    std::cout << "Carregando textura: " << filename << std::endl;

    // Libera textura anterior se existir
    if (data) {
        stbi_image_free(data);
        data = nullptr;
    }

    // Força carregar 3 canais (RGB)
    data = stbi_load(filename.c_str(), &width, &height, &channels, 3);

    if (!data) {
        std::cerr << "  ✗ ERRO ao carregar: " << stbi_failure_reason() << std::endl;
        loaded = false;
        return false;
    }

    channels = 3;  // Forçamos RGB
    loaded = true;
    std::cout << "  ✓ Carregada: " << width << "x" << height << " (" << channels << " canais)" << std::endl;
    return true;
}

Color Texture::sample(double u, double v) const {
    if (!loaded || !data) {
        return Color(1.0, 0.0, 1.0);  // Magenta = textura faltando
    }

    // Garante UV em [0, 1] com wrapping
    u = u - floor(u);
    v = v - floor(v);

    // Converte para coordenadas de pixel
    int x = static_cast<int>(u * (width - 1));
    int y = static_cast<int>((1.0 - v) * (height - 1));  // Inverte V

    // Garante dentro dos limites
    x = std::max(0, std::min(x, width - 1));
    y = std::max(0, std::min(y, height - 1));

    // Acessa pixel (RGB)
    int index = (y * width + x) * 3;
    unsigned char r = data[index + 0];
    unsigned char g = data[index + 1];
    unsigned char b = data[index + 2];

    // Converte para [0, 1]
    return Color(r / 255.0, g / 255.0, b / 255.0);
}

// ============ TEXTURE MANAGER ============

std::shared_ptr<Texture> TextureManager::woodTexture = nullptr;
std::shared_ptr<Texture> TextureManager::stainedGlassTexture = nullptr;

void TextureManager::loadTextures() {
    std::cout << "\n========================================" << endl;
    std::cout << "CARREGANDO TEXTURAS" << endl;
    std::cout << "========================================" << endl;

    woodTexture = std::make_shared<Texture>("textures/wood.jpg");
    stainedGlassTexture = std::make_shared<Texture>("textures/stained_glass.jpg");

    std::cout << "========================================\n" << endl;
}

std::shared_ptr<Texture> TextureManager::getWoodTexture() {
    if (!woodTexture) {
        loadTextures();
    }
    return woodTexture;
}

std::shared_ptr<Texture> TextureManager::getStainedGlassTexture() {
    if (!stainedGlassTexture) {
        loadTextures();
    }
    return stainedGlassTexture;
}
