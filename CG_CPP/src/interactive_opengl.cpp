#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
#include <thread>
#include <atomic>
#include <limits>
#include <chrono>
#include <string>

#include "../include/Vector3.h"
#include "../include/Color.h"
#include "../include/Ray.h"
#include "../include/Texture.h"
#include "../include/Matrix4x4.h"

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

// ============================================================================
// ⚙️ CONFIGURAÇÕES PARA DEMONSTRAÇÃO AO PROFESSOR
// ============================================================================
// ALTERE ESTES VALORES PARA DEMONSTRAR AS FUNCIONALIDADES!
// Após alterar, recompile com: make clean && make && ./interactive_opengl
// ============================================================================

// ──────────────────────────────────────────────────────────────────────────
// 1️⃣ CÂMERA (Position, LookAt, Up)
// ──────────────────────────────────────────────────────────────────────────
// ⚠️ ALTERE AQUI PARA DEMONSTRAR CÂMERA AO PROFESSOR ⚠️

// Posição da câmera (onde está) - formato: Vector3(X, Y, Z)
// Exemplo de valores para testar:
//   const Vector3 CAMERA_POSITION(10, 3, 5);   // Mais longe e mais alto
//   const Vector3 CAMERA_POSITION(6, 1.8, -5); // Vista de trás
//   const Vector3 CAMERA_POSITION(0, 2, 10);   // Canto esquerdo
const Vector3 CAMERA_POSITION(6, 1.8, 2);        // ← ALTERE AQUI

// Para onde a câmera olha - formato: Vector3(X, Y, Z)
// Exemplo de valores para testar:
//   const Vector3 CAMERA_LOOKAT(6, 1.5, 15);   // Olhar mais para o fundo
//   const Vector3 CAMERA_LOOKAT(10, 1, 10);    // Olhar para a direita
const Vector3 CAMERA_LOOKAT(6, 1.5, 10);         // ← ALTERE AQUI

// Vetor "up" da câmera (orientação) - normalmente (0, 1, 0)
const Vector3 CAMERA_UP(0, 1, 0);                // ← ALTERE AQUI (raramente necessário)

// Campo de visão (FOV) em graus
// Exemplo de valores para testar:
//   const float CAMERA_FOV = 45.0f;   // Visão mais fechada (zoom in)
//   const float CAMERA_FOV = 90.0f;   // Visão mais ampla (wide angle)
const float CAMERA_FOV = 60.0f;                  // ← ALTERE AQUI

// ──────────────────────────────────────────────────────────────────────────
// 2️⃣ TRANSFORMAÇÕES DE OBJETOS (Translação + Rotação)
// ──────────────────────────────────────────────────────────────────────────
// ⚠️ ALTERE AQUI PARA DEMONSTRAR TRANSFORMAÇÕES AO PROFESSOR ⚠️

// Translação do altar (X, Y, Z)
// Exemplo de valores para testar:
//   Vector3 altarTranslation(2, 0, 0);    // Move 2 unidades para DIREITA
//   Vector3 altarTranslation(-2, 0, 0);   // Move 2 unidades para ESQUERDA
//   Vector3 altarTranslation(0, 1, 0);    // Move 1 unidade para CIMA
//   Vector3 altarTranslation(0, -0.5, 0); // Move 0.5 unidades para BAIXO
//   Vector3 altarTranslation(0, 0, 3);    // Move 3 unidades para FRENTE
//   Vector3 altarTranslation(0, 0, -2);   // Move 2 unidades para TRÁS
Vector3 altarTranslation(0, 0, 0);        // ← ALTERE AQUI

// Rotação do altar em torno do eixo Y (em radianos)
// Conversão: graus = radianos * 180 / π
// Exemplo de valores para testar:
//   float altarRotationY = 0.52f;   // ~30 graus
//   float altarRotationY = 0.79f;   // ~45 graus
//   float altarRotationY = 1.57f;   // ~90 graus
//   float altarRotationY = 3.14f;   // ~180 graus
//   float altarRotationY = -1.57f;  // ~-90 graus (sentido oposto)
float altarRotationY = 0.0f;              // ← ALTERE AQUI

// ──────────────────────────────────────────────────────────────────────────
// 3️⃣ ILUMINAÇÃO (Posição e Intensidade das Luzes)
// ──────────────────────────────────────────────────────────────────────────
// ⚠️ ALTERE AQUI PARA DEMONSTRAR ILUMINAÇÃO AO PROFESSOR ⚠️

// Luz 1: Hóstia (luz divina/sagrada)
// Exemplo de valores para testar:
//   const Vector3 LIGHT_HOSTIA_POS(6, 5, 15);     // Luz mais alta e para frente
//   const Color LIGHT_HOSTIA_COLOR(1.0f, 1.0f, 1.0f);  // Branco puro
//   const Color LIGHT_HOSTIA_COLOR(1.0f, 0.5f, 0.5f);  // Luz rosada
const Vector3 LIGHT_HOSTIA_POS(6, 1.4, 18);           // ← ALTERE AQUI
const Color LIGHT_HOSTIA_COLOR(0.7f, 0.7f, 0.8f);     // ← ALTERE AQUI (RGB)

// Luz 2: Vela (luz quente quando acesa)
// Exemplo de valores para testar:
//   const Color LIGHT_CANDLE_COLOR(1.0f, 0.3f, 0.1f);  // Luz mais forte
const Vector3 LIGHT_CANDLE_POS(8, 1.1f, 17.5f);       // ← ALTERE AQUI
const Color LIGHT_CANDLE_COLOR(0.5f, 0.15f, 0.075f);  // ← ALTERE AQUI (RGB)

// Luz ambiente (iluminação geral da cena)
// Exemplo de valores para testar:
//   const Color AMBIENT_LIGHT(0.3f, 0.3f, 0.3f);  // Mais claro
//   const Color AMBIENT_LIGHT(0.05f, 0.05f, 0.08f);  // Mais escuro
const Color AMBIENT_LIGHT(0.15f, 0.15f, 0.18f);       // ← ALTERE AQUI (RGB)

// ──────────────────────────────────────────────────────────────────────────
// 4️⃣ OBJETOS EMISSIVOS (Brilho próprio)
// ──────────────────────────────────────────────────────────────────────────
// ⚠️ ALTERE AQUI PARA DEMONSTRAR EMISSIVIDADE AO PROFESSOR ⚠️
// Valores maiores = mais brilho, valores menores = menos brilho

// Exemplo de valores para testar:
//   const float EMISSIVE_HOSTIA = 3.0f;   // Hóstia muito brilhante
//   const float EMISSIVE_VITRAL = 0.5f;   // Vitral mais escuro
//   const float EMISSIVE_WALLS = 0.9f;    // Paredes muito brilhantes
const float EMISSIVE_HOSTIA = 2.0f;       // ← ALTERE AQUI (Hóstia 200%)
const float EMISSIVE_VITRAL = 0.9f;       // ← ALTERE AQUI (Vitral 90%)
const float EMISSIVE_CANDLE = 1.3f;       // ← ALTERE AQUI (Chama vela 130%)
const float EMISSIVE_WALLS = 0.36f;       // ← ALTERE AQUI (Paredes 36%)
const float EMISSIVE_CEILING = 0.36f;     // ← ALTERE AQUI (Teto 36%)
const float EMISSIVE_FLOOR = 0.08f;       // ← ALTERE AQUI (Chão 8%)

// ──────────────────────────────────────────────────────────────────────────
// 5️⃣ DIMENSÕES DA CAPELA (Sistema de Coordenadas)
// ──────────────────────────────────────────────────────────────────────────
// Origem: (0, 0, 0) no canto frontal esquerdo do chão
const float CHAPEL_WIDTH = 12.0f;   // Largura (eixo X)
const float CHAPEL_HEIGHT = 8.0f;   // Altura (eixo Y)
const float CHAPEL_DEPTH = 20.0f;   // Profundidade (eixo Z)

// ──────────────────────────────────────────────────────────────────────────
// 6️⃣ SOMBRAS (Shadow Rays)
// ──────────────────────────────────────────────────────────────────────────
// ⚠️ ALTERE AQUI PARA DEMONSTRAR SOMBRAS AO PROFESSOR ⚠️

// Ativar/desativar sombras
// Exemplo de valores para testar:
//   const bool ENABLE_SHADOWS = false;  // Sem sombras
const bool ENABLE_SHADOWS = true;         // ← ALTERE AQUI

// Intensidade da sombra (quanto de luz chega nas áreas sombreadas)
// 0.0 = completamente escuro (sombra 100%)
// 0.5 = sombra média (50% da luz chega)
// 1.0 = sem sombra (100% da luz chega)
// Exemplo de valores para testar:
//   const float SHADOW_INTENSITY = 0.1f;   // Sombras muito escuras
//   const float SHADOW_INTENSITY = 0.6f;   // Sombras suaves
const float SHADOW_INTENSITY = 0.3f;      // ← ALTERE AQUI

// Pequeno offset para evitar "shadow acne" (raramente precisa alterar)
const float SHADOW_BIAS = 0.001f;

// ──────────────────────────────────────────────────────────────────────────
// 7️⃣ VELA (Estado inicial)
// ──────────────────────────────────────────────────────────────────────────
bool candleLit = true;  // true = acesa, false = apagada

// ============================================================================
// FIM DAS CONFIGURAÇÕES
// ============================================================================

// Texturas globais
Texture woodTexture;
Texture wallTexture;
Texture stainedGlassTexture;
Texture ceilingTexture;

// Estrutura de câmera simples
struct Camera {
    Vector3 position;
    Vector3 lookAt;
    Vector3 up;
    float fov;

    Camera() : position(CAMERA_POSITION), lookAt(CAMERA_LOOKAT), up(CAMERA_UP), fov(CAMERA_FOV) {}

    Ray generateRay(float px, float py, float aspectRatio) const {
        // px, py em [-1, 1]
        Vector3 forward = (lookAt - position).normalized();
        Vector3 right = forward.cross(up).normalized();
        Vector3 newUp = right.cross(forward);

        float tanFov = tan(fov * 0.5f * M_PI / 180.0f);
        Vector3 rayDir = forward + right * (px * tanFov * aspectRatio) + newUp * (py * tanFov);

        return Ray(position, rayDir.normalized());
    }

    void moveForward(float speed) {
        Vector3 dir = (lookAt - position).normalized();
        position = position + dir * speed;
        lookAt = lookAt + dir * speed;
    }

    void moveRight(float speed) {
        Vector3 forward = (lookAt - position).normalized();
        Vector3 right = forward.cross(up).normalized();
        position = position + right * speed;
        lookAt = lookAt + right * speed;
    }

    void moveUp(float speed) {
        position.y += speed;
        lookAt.y += speed;
    }

    void rotate(float yaw, float pitch) {
        Vector3 dir = lookAt - position;
        float dist = dir.length();

        // Rotação yaw (horizontal)
        float currentYaw = atan2(dir.x, dir.z);
        float currentPitch = asin(dir.y / dist);

        currentYaw += yaw;
        currentPitch += pitch;
        currentPitch = max(-1.4f, min(1.4f, currentPitch));

        dir.x = sin(currentYaw) * cos(currentPitch);
        dir.y = sin(currentPitch);
        dir.z = cos(currentYaw) * cos(currentPitch);

        lookAt = position + dir * dist;
    }
};

// Estrutura de luz
struct Light {
    Vector3 position;
    Color intensity;
    bool enabled;

    Light(const Vector3& pos, const Color& col, bool on = true)
        : position(pos), intensity(col), enabled(on) {}
};

// Hit record para interseções
struct HitRecord {
    bool hit;
    float t;
    Vector3 point;
    Vector3 normal;
    Color color;
    float shininess;
    bool useTexture;
    double u, v;
    const Texture* texture;
    string objectName;  // Nome do objeto para picking

    HitRecord() : hit(false), t(numeric_limits<float>::max()),
                  useTexture(false), u(0), v(0), texture(nullptr), objectName("") {}
};

// Função de interseção com esfera
bool intersectSphere(const Ray& ray, const Vector3& center, float radius, HitRecord& rec) {
    Vector3 oc = ray.origin - center;
    float a = ray.direction.dot(ray.direction);
    float b = 2.0f * oc.dot(ray.direction);
    float c = oc.dot(oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) return false;

    float t = (-b - sqrt(discriminant)) / (2.0f * a);
    if (t < 0.001f) {
        t = (-b + sqrt(discriminant)) / (2.0f * a);
        if (t < 0.001f) return false;
    }

    if (t < rec.t) {
        rec.hit = true;
        rec.t = t;
        rec.point = ray.origin + ray.direction * t;
        rec.normal = (rec.point - center).normalized();
        return true;
    }
    return false;
}

// Função de interseção com cilindro (eixo Y)
bool intersectCylinder(const Ray& ray, const Vector3& base, float radius, float height, HitRecord& rec) {
    Vector3 d = ray.direction;
    Vector3 o = ray.origin - base;

    float a = d.x * d.x + d.z * d.z;
    float b = 2.0f * (o.x * d.x + o.z * d.z);
    float c = o.x * o.x + o.z * o.z - radius * radius;

    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) return false;

    float t = (-b - sqrt(discriminant)) / (2.0f * a);
    if (t < 0.001f) t = (-b + sqrt(discriminant)) / (2.0f * a);
    if (t < 0.001f) return false;

    Vector3 point = ray.origin + ray.direction * t;
    float y = point.y - base.y;

    if (y >= 0 && y <= height && t < rec.t) {
        rec.hit = true;
        rec.t = t;
        rec.point = point;
        Vector3 center(base.x, point.y, base.z);
        rec.normal = (point - center).normalized();
        return true;
    }
    return false;
}

// Função de interseção com cone (eixo Y)
bool intersectCone(const Ray& ray, const Vector3& apex, float baseRadius, float height, HitRecord& rec) {
    Vector3 d = ray.direction;
    Vector3 o = ray.origin - apex;

    float k = (baseRadius / height) * (baseRadius / height);

    float a = d.x * d.x + d.z * d.z - k * d.y * d.y;
    float b = 2.0f * (o.x * d.x + o.z * d.z - k * o.y * d.y);
    float c = o.x * o.x + o.z * o.z - k * o.y * o.y;

    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) return false;

    float t = (-b - sqrt(discriminant)) / (2.0f * a);
    if (t < 0.001f) t = (-b + sqrt(discriminant)) / (2.0f * a);
    if (t < 0.001f) return false;

    Vector3 point = ray.origin + ray.direction * t;
    float y = point.y - apex.y;

    if (y <= 0 && y >= -height && t < rec.t) {
        rec.hit = true;
        rec.t = t;
        rec.point = point;

        float r = sqrt(point.x * point.x + point.z * point.z);
        rec.normal = Vector3(point.x, r * (baseRadius / height), point.z).normalized();
        return true;
    }
    return false;
}

// Função de interseção com plano (com UV)
bool intersectPlane(const Ray& ray, const Vector3& point, const Vector3& normal, HitRecord& rec, float uvScale = 1.0f) {
    float denom = normal.dot(ray.direction);
    if (fabs(denom) < 0.0001f) return false;

    float t = (point - ray.origin).dot(normal) / denom;
    if (t < 0.001f || t >= rec.t) return false;

    rec.hit = true;
    rec.t = t;
    rec.point = ray.origin + ray.direction * t;
    rec.normal = normal;

    // Calcula coordenadas UV baseado na orientação do plano
    if (fabs(normal.y) > 0.9f) {
        // Plano horizontal (chão/teto)
        rec.u = fmod(rec.point.x * uvScale, 1.0);
        rec.v = fmod(rec.point.z * uvScale, 1.0);
    } else if (fabs(normal.x) > 0.9f) {
        // Plano vertical (parede perpendicular a X)
        rec.u = fmod(rec.point.z * uvScale, 1.0);
        rec.v = fmod(rec.point.y * uvScale, 1.0);
    } else {
        // Plano vertical (parede perpendicular a Z)
        rec.u = fmod(rec.point.x * uvScale, 1.0);
        rec.v = fmod(rec.point.y * uvScale, 1.0);
    }

    // Garante [0, 1]
    if (rec.u < 0) rec.u += 1.0;
    if (rec.v < 0) rec.v += 1.0;

    return true;
}

// Função de interseção com caixa (AABB simplificado)
bool intersectBox(const Ray& ray, const Vector3& min, const Vector3& max, HitRecord& rec) {
    float tmin = (min.x - ray.origin.x) / ray.direction.x;
    float tmax = (max.x - ray.origin.x) / ray.direction.x;
    if (tmin > tmax) swap(tmin, tmax);

    float tymin = (min.y - ray.origin.y) / ray.direction.y;
    float tymax = (max.y - ray.origin.y) / ray.direction.y;
    if (tymin > tymax) swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax)) return false;
    if (tymin > tmin) tmin = tymin;
    if (tymax < tmax) tmax = tymax;

    float tzmin = (min.z - ray.origin.z) / ray.direction.z;
    float tzmax = (max.z - ray.origin.z) / ray.direction.z;
    if (tzmin > tzmax) swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax)) return false;
    if (tzmin > tmin) tmin = tzmin;
    if (tzmax < tmax) tmax = tzmax;

    if (tmin < 0.001f || tmin >= rec.t) return false;

    rec.hit = true;
    rec.t = tmin;
    rec.point = ray.origin + ray.direction * tmin;

    // Calcula normal da face atingida
    Vector3 c = (min + max) * 0.5f;
    Vector3 p = rec.point - c;
    Vector3 d = (max - min) * 0.5f;
    float bias = 1.0001f;

    rec.normal = Vector3(
        int(p.x / fabs(d.x) * bias),
        int(p.y / fabs(d.y) * bias),
        int(p.z / fabs(d.z) * bias)
    ).normalized();

    // Calcula coordenadas UV baseado na face atingida
    Vector3 size = max - min;
    if (fabs(rec.normal.y) > 0.9f) {
        // Face horizontal (top/bottom)
        rec.u = (rec.point.x - min.x) / size.x;
        rec.v = (rec.point.z - min.z) / size.z;
    } else if (fabs(rec.normal.x) > 0.9f) {
        // Face lateral (left/right)
        rec.u = (rec.point.z - min.z) / size.z;
        rec.v = (rec.point.y - min.y) / size.y;
    } else {
        // Face frontal/traseira
        rec.u = (rec.point.x - min.x) / size.x;
        rec.v = (rec.point.y - min.y) / size.y;
    }

    return true;
}

// Verifica se um ponto está na sombra em relação a uma luz
bool isInShadow(const Vector3& point, const Vector3& lightPos, const Vector3& normal) {
    if (!ENABLE_SHADOWS) return false;

    Vector3 toLight = lightPos - point;
    float distanceToLight = toLight.length();
    Vector3 lightDir = toLight.normalized();

    // Cria raio de sombra com pequeno offset para evitar "shadow acne"
    Ray shadowRay(point + normal * SHADOW_BIAS, lightDir);

    // Testa interseção com objetos principais (altar, bancos, ostensório, vela)
    HitRecord shadowHit;

    // Altar
    Vector3 baseMin(4.5, 0, 17.5);
    Vector3 baseMax(7.5, 0.8, 18.5);
    Vector3 altarCenter((baseMin.x + baseMax.x) * 0.5f,
                       (baseMin.y + baseMax.y) * 0.5f,
                       (baseMin.z + baseMax.z) * 0.5f);
    Matrix4x4 transform = Matrix4x4::translation(altarTranslation) *
                         Matrix4x4::translation(altarCenter) *
                         Matrix4x4::rotationY(altarRotationY) *
                         Matrix4x4::translation(altarCenter * -1.0f);
    Vector3 altarMin = transform.transformPoint(baseMin);
    Vector3 altarMax = transform.transformPoint(baseMax);
    Vector3 realMin(min(altarMin.x, altarMax.x), min(altarMin.y, altarMax.y), min(altarMin.z, altarMax.z));
    Vector3 realMax(max(altarMin.x, altarMax.x), max(altarMin.y, altarMax.y), max(altarMin.z, altarMax.z));

    if (intersectBox(shadowRay, realMin, realMax, shadowHit)) {
        if (shadowHit.t > 0.0f && shadowHit.t < distanceToLight) {
            return true;
        }
    }

    // Bancos
    for (int i = 0; i < 4; i++) {
        float z = 5 + i * 3.0f;
        // Banco esquerdo
        if (intersectBox(shadowRay, Vector3(1.3, 0, z - 0.25), Vector3(3.7, 0.45, z + 0.25), shadowHit)) {
            if (shadowHit.t > 0.0f && shadowHit.t < distanceToLight) {
                return true;
            }
        }
        // Banco direito
        if (intersectBox(shadowRay, Vector3(8.3, 0, z - 0.25), Vector3(10.7, 0.45, z + 0.25), shadowHit)) {
            if (shadowHit.t > 0.0f && shadowHit.t < distanceToLight) {
                return true;
            }
        }
    }

    // Ostensório base
    if (intersectCylinder(shadowRay, Vector3(6, 0.8, 18), 0.15f, 0.3f, shadowHit)) {
        if (shadowHit.t > 0.0f && shadowHit.t < distanceToLight) {
            return true;
        }
    }

    // Ostensório hóstia
    if (intersectSphere(shadowRay, Vector3(6, 1.4, 18), 0.14f, shadowHit)) {
        if (shadowHit.t > 0.0f && shadowHit.t < distanceToLight) {
            return true;
        }
    }

    // Vela
    if (intersectCylinder(shadowRay, Vector3(8, 0, 17.5), 0.12f, 1.0f, shadowHit)) {
        if (shadowHit.t > 0.0f && shadowHit.t < distanceToLight) {
            return true;
        }
    }

    return false;
}

// Modelo de iluminação Phong (com suporte a texturas e sombras)
Color phongShading(
    const Vector3& point,
    const Vector3& normal,
    const Vector3& viewDir,
    const Color& albedo,
    float shininess,
    const vector<Light>& lights,
    const Color& ambient,
    bool useTexture = false,
    double u = 0,
    double v = 0,
    const Texture* texture = nullptr
) {
    // Cor base (textura ou cor sólida)
    Color baseColor = albedo;
    if (useTexture && texture && texture->isLoaded()) {
        baseColor = texture->sample(u, v);
    }

    Color result = baseColor * ambient * 0.3f;

    for (const auto& light : lights) {
        if (!light.enabled) continue;

        Vector3 lightDir = (light.position - point).normalized();

        // Verifica se o ponto está na sombra em relação a esta luz
        bool inShadow = isInShadow(point, light.position, normal);
        float shadowFactor = inShadow ? SHADOW_INTENSITY : 1.0f;

        // Componente difusa
        float diff = fmax(0.0f, (float)normal.dot(lightDir));
        Color diffuse = baseColor * light.intensity * diff * shadowFactor;

        // Componente especular
        Vector3 reflectDir = normal * (2.0f * normal.dot(lightDir)) - lightDir;
        float spec = pow(fmax(0.0f, (float)viewDir.dot(reflectDir)), shininess);
        Color specular = light.intensity * spec * 0.5f * shadowFactor;

        result = result + diffuse + specular;
    }

    return result;
}

// Função de picking - retorna o objeto mais próximo atingido por um raio
HitRecord performPicking(const Ray& ray) {
    HitRecord rec;

    // Chão (finito)
    HitRecord floorRec;
    if (intersectPlane(ray, Vector3(0, 0, 0), Vector3(0, 1, 0), floorRec, 0.5f)) {
        Vector3 p = floorRec.point;
        if (p.x >= 0.0f && p.x <= CHAPEL_WIDTH && p.z >= 0.0f && p.z <= CHAPEL_DEPTH) {
            rec = floorRec;
            rec.color = Color(0.6f, 0.5f, 0.4f);
            rec.shininess = 5.0f;
            rec.objectName = "Chao";
        }
    }

    // Paredes (finitas)
    HitRecord wallRec;
    // Parede do fundo
    if (intersectPlane(ray, Vector3(0, 0, 20), Vector3(0, 0, 1), wallRec, 0.25f)) {
        Vector3 p = wallRec.point;
        if (p.x >= 0.0f && p.x <= CHAPEL_WIDTH && p.y >= 0.0f && p.y <= CHAPEL_HEIGHT) {
            if (wallRec.t < rec.t) {
                rec = wallRec;
                rec.objectName = "Parede do Fundo";
            }
        }
    }
    // Parede esquerda
    if (intersectPlane(ray, Vector3(0, 0, 0), Vector3(1, 0, 0), wallRec, 0.25f)) {
        Vector3 p = wallRec.point;
        if (p.z >= 0.0f && p.z <= CHAPEL_DEPTH && p.y >= 0.0f && p.y <= CHAPEL_HEIGHT) {
            if (wallRec.t < rec.t) {
                rec = wallRec;
                rec.objectName = "Parede Esquerda";
            }
        }
    }
    // Parede direita
    if (intersectPlane(ray, Vector3(12, 0, 0), Vector3(1, 0, 0), wallRec, 0.25f)) {
        Vector3 p = wallRec.point;
        if (p.z >= 0.0f && p.z <= CHAPEL_DEPTH && p.y >= 0.0f && p.y <= CHAPEL_HEIGHT) {
            if (wallRec.t < rec.t) {
                rec = wallRec;
                rec.objectName = "Parede Direita";
            }
        }
    }
    // Parede frontal (com porta)
    if (intersectPlane(ray, Vector3(0, 0, 0), Vector3(0, 0, 1), wallRec, 0.25f)) {
        Vector3 p = wallRec.point;
        bool isWall = (p.x >= 0.0f && p.x <= 12.0f && p.y >= 0.0f && p.y <= 8.0f);
        bool isDoor = (p.x >= 4.0f && p.x <= 8.0f && p.y >= 0.0f && p.y <= 3.0f);
        if (isWall && !isDoor) {
            if (wallRec.t < rec.t) {
                rec = wallRec;
                rec.objectName = "Parede da Frente (Entrada)";
            }
        }
    }

    // Janela de vitral
    HitRecord glassRec;
    if (intersectPlane(ray, Vector3(0, 0, 19.9f), Vector3(0, 0, 1), glassRec, 0.5f)) {
        Vector3 p = glassRec.point;
        if (p.x >= 4.5f && p.x <= 7.5f && p.y >= 2.0f && p.y <= 5.0f) {
            if (glassRec.t < rec.t) {
                rec = glassRec;
                rec.objectName = "Janela de Vitral";
            }
        }
    }

    // Teto (finito)
    if (intersectPlane(ray, Vector3(0, 8, 0), Vector3(0, 1, 0), wallRec, 0.5f)) {
        Vector3 p = wallRec.point;
        if (p.x >= 0.0f && p.x <= CHAPEL_WIDTH && p.z >= 0.0f && p.z <= CHAPEL_DEPTH) {
            if (wallRec.t < rec.t) {
                rec = wallRec;
                rec.objectName = "Teto";
            }
        }
    }

    // Porta de entrada
    HitRecord boxRec;
    if (intersectBox(ray, Vector3(4.0, 0, 0.05), Vector3(8.0, 3.0, 0.15), boxRec)) {
        if (boxRec.t < rec.t) {
            rec = boxRec;
            rec.objectName = "Porta de Entrada";
        }
    }

    // Altar
    if (intersectBox(ray, Vector3(4.5, 0, 17.5), Vector3(7.5, 0.8, 18.5), boxRec)) {
        if (boxRec.t < rec.t) {
            rec = boxRec;
            rec.objectName = "Altar";
        }
    }

    // Bancos
    for (int i = 0; i < 4; i++) {
        float z = 5 + i * 3.0f;
        if (intersectBox(ray, Vector3(1.3, 0, z - 0.25), Vector3(3.7, 0.45, z + 0.25), boxRec)) {
            if (boxRec.t < rec.t) {
                rec = boxRec;
                rec.objectName = "Banco Esquerdo " + to_string(i + 1);
            }
        }
        if (intersectBox(ray, Vector3(8.3, 0, z - 0.25), Vector3(10.7, 0.45, z + 0.25), boxRec)) {
            if (boxRec.t < rec.t) {
                rec = boxRec;
                rec.objectName = "Banco Direito " + to_string(i + 1);
            }
        }
    }

    // Ostensório
    HitRecord cylRec;
    if (intersectCylinder(ray, Vector3(6, 0.8, 18), 0.15f, 0.3f, cylRec)) {
        if (cylRec.t < rec.t) {
            rec = cylRec;
            rec.objectName = "Ostensorio - Base";
        }
    }

    HitRecord sphereRec;
    if (intersectSphere(ray, Vector3(6, 1.4, 18), 0.14f, sphereRec)) {
        if (sphereRec.t < rec.t) {
            rec = sphereRec;
            rec.objectName = "Ostensorio - Hostia";
        }
    }

    // Raios do ostensório
    for (int i = 0; i < 8; i++) {
        float angle = i * 2 * M_PI / 8;
        float offsetX = 0.25f * cos(angle);
        float offsetY = 0.25f * sin(angle);

        // Esfera na ponta
        if (intersectSphere(ray, Vector3(6 + offsetX, 1.4 + offsetY, 18), 0.025f, sphereRec)) {
            if (sphereRec.t < rec.t) {
                rec = sphereRec;
                rec.objectName = "Ostensorio - Raio";
            }
        }

        // Conector (linha dourada)
        float startDist = 0.16f;
        float endDist = 0.225f;

        Vector3 rayStart = Vector3(6 + startDist * cos(angle), 1.4 + startDist * sin(angle), 18);
        Vector3 rayEnd = Vector3(6 + endDist * cos(angle), 1.4 + endDist * sin(angle), 18);
        Vector3 rayMid = Vector3(6 + (startDist + endDist) * 0.5f * cos(angle),
                                1.4 + (startDist + endDist) * 0.5f * sin(angle), 18);

        Vector3 boxMin(rayMid.x - 0.008f, rayMid.y - 0.008f, 17.98f);
        Vector3 boxMax(rayMid.x + 0.008f, rayMid.y + 0.008f, 18.02f);

        if (fabs(cos(angle)) > fabs(sin(angle))) {
            boxMin.x = rayStart.x;
            boxMax.x = rayEnd.x;
        } else {
            boxMin.y = rayStart.y;
            boxMax.y = rayEnd.y;
        }

        if (intersectBox(ray, boxMin, boxMax, boxRec)) {
            if (boxRec.t < rec.t) {
                rec = boxRec;
                rec.objectName = "Ostensorio - Raio Conector";
            }
        }
    }

    // Vela
    if (intersectCylinder(ray, Vector3(8, 0, 17.5), 0.12f, 1.0f, cylRec)) {
        if (cylRec.t < rec.t) {
            rec = cylRec;
            rec.objectName = candleLit ? "Vela (Acesa)" : "Vela (Apagada)";
        }
    }

    // Chama da vela
    if (candleLit) {
        HitRecord coneRec;
        if (intersectCone(ray, Vector3(8, 1.3, 17.5), 0.08f, 0.3f, coneRec)) {
            if (coneRec.t < rec.t) {
                rec = coneRec;
                rec.objectName = "Chama da Vela";
            }
        }
    }

    return rec;
}

// Renderiza a cena para um tile
void renderTile(
    int startY, int endY,
    int width, int height,
    vector<Color>& framebuffer,
    const Camera& camera,
    const vector<Light>& lights,
    const Color& ambient
) {
    float aspectRatio = (float)width / (float)height;

    for (int y = startY; y < endY; y++) {
        for (int x = 0; x < width; x++) {
            float px = (2.0f * x / width - 1.0f);
            float py = (1.0f - 2.0f * y / height);

            Ray ray = camera.generateRay(px, py, aspectRatio);
            HitRecord rec;
            Color pixelColor = Color(0.3f, 0.35f, 0.4f); // Background

            // Chão (finito - dentro da capela)
            HitRecord floorRec;
            if (intersectPlane(ray, Vector3(0, 0, 0), Vector3(0, 1, 0), floorRec, 0.5f)) {
                Vector3 p = floorRec.point;
                // Limita o chão às dimensões da capela
                if (p.x >= 0.0f && p.x <= CHAPEL_WIDTH && p.z >= 0.0f && p.z <= CHAPEL_DEPTH) {
                    rec = floorRec;
                    rec.color = Color(0.6f, 0.5f, 0.4f);
                    rec.shininess = 5.0f;
                    rec.objectName = "Chao";
                }
            }

            // Parede do fundo (com textura) - finita
            HitRecord wallRec;
            if (intersectPlane(ray, Vector3(0, 0, 20), Vector3(0, 0, 1), wallRec, 0.25f)) {
                Vector3 p = wallRec.point;
                // Limita a parede: X=[0,12], Y=[0,8]
                if (p.x >= 0.0f && p.x <= CHAPEL_WIDTH && p.y >= 0.0f && p.y <= CHAPEL_HEIGHT) {
                    if (wallRec.t < rec.t) {
                        rec = wallRec;
                        rec.color = Color(0.7f, 0.68f, 0.65f);
                        rec.shininess = 5.0f;
                        rec.useTexture = true;
                        rec.texture = &wallTexture;
                        rec.objectName = "Parede do Fundo";
                    }
                }
            }

            // Parede esquerda (com textura) - finita
            if (intersectPlane(ray, Vector3(0, 0, 0), Vector3(1, 0, 0), wallRec, 0.25f)) {
                Vector3 p = wallRec.point;
                // Limita a parede: Z=[0,20], Y=[0,8]
                if (p.z >= 0.0f && p.z <= CHAPEL_DEPTH && p.y >= 0.0f && p.y <= CHAPEL_HEIGHT) {
                    if (wallRec.t < rec.t) {
                        rec = wallRec;
                        rec.color = Color(0.7f, 0.68f, 0.65f);
                        rec.shininess = 5.0f;
                        rec.useTexture = true;
                        rec.texture = &wallTexture;
                        rec.objectName = "Parede Esquerda";
                    }
                }
            }

            // Parede direita (com textura) - finita
            if (intersectPlane(ray, Vector3(12, 0, 0), Vector3(1, 0, 0), wallRec, 0.25f)) {
                Vector3 p = wallRec.point;
                // Limita a parede: Z=[0,20], Y=[0,8]
                if (p.z >= 0.0f && p.z <= CHAPEL_DEPTH && p.y >= 0.0f && p.y <= CHAPEL_HEIGHT) {
                    if (wallRec.t < rec.t) {
                        rec = wallRec;
                        rec.color = Color(0.7f, 0.68f, 0.65f);
                        rec.shininess = 5.0f;
                        rec.useTexture = true;
                        rec.texture = &wallTexture;
                        rec.objectName = "Parede Direita";
                    }
                }
            }

            // Parede frontal (com porta) - com textura
            if (intersectPlane(ray, Vector3(0, 0, 0), Vector3(0, 0, 1), wallRec, 0.25f)) {
                Vector3 p = wallRec.point;
                // Parede frontal: X=[0,12], Y=[0,8]
                // Porta: X=[4,8], Y=[0,3] (entrada central)
                bool isWall = (p.x >= 0.0f && p.x <= CHAPEL_WIDTH && p.y >= 0.0f && p.y <= CHAPEL_HEIGHT);
                bool isDoor = (p.x >= 4.0f && p.x <= 8.0f && p.y >= 0.0f && p.y <= 3.0f);

                if (isWall && !isDoor) {
                    if (wallRec.t < rec.t) {
                        rec = wallRec;
                        rec.color = Color(0.7f, 0.68f, 0.65f);
                        rec.shininess = 5.0f;
                        rec.useTexture = true;
                        rec.texture = &wallTexture;
                        rec.objectName = "Parede da Frente (Entrada)";
                    }
                }
            }

            // Janela de vitral atrás do ostensório (emissiva/brilhante)
            HitRecord glassRec;
            if (intersectPlane(ray, Vector3(0, 0, 19.9f), Vector3(0, 0, 1), glassRec, 0.5f)) {
                Vector3 p = glassRec.point;
                // Limitar a janela a uma área específica atrás do ostensório
                if (p.x >= 4.5f && p.x <= 7.5f && p.y >= 2.0f && p.y <= 5.0f) {
                    if (glassRec.t < rec.t) {
                        rec = glassRec;
                        rec.color = Color(1.2f, 1.2f, 1.5f); // Cor base mais brilhante
                        rec.shininess = 100.0f;
                        rec.useTexture = true;
                        rec.texture = &stainedGlassTexture;
                        rec.objectName = "Janela de Vitral";
                        // Ajusta UV para a janela
                        rec.u = (p.x - 4.5f) / 3.0f;
                        rec.v = (p.y - 2.0f) / 3.0f;
                    }
                }
            }

            // Teto (finito com textura - uma única imagem para todo o teto)
            if (intersectPlane(ray, Vector3(0, 8, 0), Vector3(0, 1, 0), wallRec, 1.0f)) {
                Vector3 p = wallRec.point;
                // Limita o teto às dimensões da capela
                if (p.x >= 0.0f && p.x <= CHAPEL_WIDTH && p.z >= 0.0f && p.z <= CHAPEL_DEPTH) {
                    if (wallRec.t < rec.t) {
                        rec = wallRec;
                        rec.color = Color(0.65f, 0.63f, 0.60f);
                        rec.shininess = 5.0f;
                        rec.useTexture = true;
                        rec.texture = &ceilingTexture;
                        rec.objectName = "Teto";
                        // Mapeia UMA ÚNICA imagem para todo o teto (0-1 em ambos os eixos)
                        rec.u = p.x / CHAPEL_WIDTH;   // 0 a 1 ao longo da largura
                        rec.v = p.z / CHAPEL_DEPTH;   // 0 a 1 ao longo do comprimento
                    }
                }
            }

            // Porta de entrada (caixa com textura de madeira)
            HitRecord boxRec;
            if (intersectBox(ray, Vector3(4.0, 0, 0.05), Vector3(8.0, 3.0, 0.15), boxRec)) {
                if (boxRec.t < rec.t) {
                    rec = boxRec;
                    rec.color = Color(0.5f, 0.35f, 0.2f); // Madeira escura
                    rec.shininess = 15.0f;
                    rec.useTexture = true;
                    rec.texture = &woodTexture;
                    rec.objectName = "Porta de Entrada";
                }
            }

            // Altar (caixa com textura de madeira) - COM TRANSFORMAÇÕES
            {
                // Posição original do altar
                Vector3 baseMin(4.5, 0, 17.5);
                Vector3 baseMax(7.5, 0.8, 18.5);
                Vector3 altarCenter((baseMin.x + baseMax.x) * 0.5f,
                                   (baseMin.y + baseMax.y) * 0.5f,
                                   (baseMin.z + baseMax.z) * 0.5f);

                // Aplica transformações: translação + rotação em torno do centro
                Matrix4x4 transform = Matrix4x4::translation(altarTranslation) *
                                     Matrix4x4::translation(altarCenter) *
                                     Matrix4x4::rotationY(altarRotationY) *
                                     Matrix4x4::translation(altarCenter * -1.0f);

                // Transforma os vértices do altar
                Vector3 altarMin = transform.transformPoint(baseMin);
                Vector3 altarMax = transform.transformPoint(baseMax);

                // Corrige ordem min/max após rotação
                Vector3 realMin(min(altarMin.x, altarMax.x), min(altarMin.y, altarMax.y), min(altarMin.z, altarMax.z));
                Vector3 realMax(max(altarMin.x, altarMax.x), max(altarMin.y, altarMax.y), max(altarMin.z, altarMax.z));

                if (intersectBox(ray, realMin, realMax, boxRec)) {
                    if (boxRec.t < rec.t) {
                        rec = boxRec;
                        rec.color = Color(0.6f, 0.4f, 0.2f);
                        rec.shininess = 10.0f;
                        rec.useTexture = true;
                        rec.texture = &woodTexture;
                        rec.objectName = "Altar";
                    }
                }
            }

            // Bancos (com textura de madeira)
            for (int i = 0; i < 4; i++) {
                float z = 5 + i * 3.0f;
                // Banco esquerdo
                if (intersectBox(ray, Vector3(1.3, 0, z - 0.25), Vector3(3.7, 0.45, z + 0.25), boxRec)) {
                    if (boxRec.t < rec.t) {
                        rec = boxRec;
                        rec.color = Color(0.6f, 0.4f, 0.2f);
                        rec.shininess = 10.0f;
                        rec.useTexture = true;
                        rec.texture = &woodTexture;
                        rec.objectName = "Banco Esquerdo " + to_string(i + 1);
                    }
                }
                // Banco direito
                if (intersectBox(ray, Vector3(8.3, 0, z - 0.25), Vector3(10.7, 0.45, z + 0.25), boxRec)) {
                    if (boxRec.t < rec.t) {
                        rec = boxRec;
                        rec.color = Color(0.6f, 0.4f, 0.2f);
                        rec.shininess = 10.0f;
                        rec.useTexture = true;
                        rec.texture = &woodTexture;
                        rec.objectName = "Banco Direito " + to_string(i + 1);
                    }
                }
            }

            // Ostensório base (cilindro)
            HitRecord cylRec;
            if (intersectCylinder(ray, Vector3(6, 0.8, 18), 0.15f, 0.3f, cylRec)) {
                if (cylRec.t < rec.t) {
                    rec = cylRec;
                    rec.color = Color(0.9f, 0.75f, 0.3f); // Dourado
                    rec.shininess = 50.0f;
                    rec.objectName = "Ostensorio - Base";
                }
            }

            // Ostensório hóstia (esfera) - emissiva/brilhante
            HitRecord sphereRec;
            if (intersectSphere(ray, Vector3(6, 1.4, 18), 0.14f, sphereRec)) {
                if (sphereRec.t < rec.t) {
                    rec = sphereRec;
                    rec.color = Color(1.0f, 1.0f, 0.95f); // Branco brilhante
                    rec.shininess = 100.0f;
                    rec.objectName = "Ostensorio - Hostia";
                }
            }

            // Raios do ostensório (esferas nas pontas)
            for (int i = 0; i < 8; i++) {
                float angle = i * 2 * M_PI / 8;
                float offsetX = 0.25f * cos(angle);
                float offsetY = 0.25f * sin(angle);

                // Esfera na ponta do raio
                if (intersectSphere(ray, Vector3(6 + offsetX, 1.4 + offsetY, 18), 0.025f, sphereRec)) {
                    if (sphereRec.t < rec.t) {
                        rec = sphereRec;
                        rec.color = Color(0.9f, 0.75f, 0.3f);
                        rec.shininess = 50.0f;
                        rec.objectName = "Ostensorio - Raio";
                    }
                }

                // Linha/cilindro conectando a hóstia à esfera (não toca a hóstia)
                // Começa a 0.16 da hóstia (raio da hóstia = 0.14 + pequeno gap = 0.16)
                // Termina em 0.225 (perto da esfera que está a 0.25)
                float startDist = 0.16f; // Começa logo após a hóstia
                float endDist = 0.225f;  // Termina logo antes da esfera

                Vector3 rayStart = Vector3(6 + startDist * cos(angle), 1.4 + startDist * sin(angle), 18);
                Vector3 rayEnd = Vector3(6 + endDist * cos(angle), 1.4 + endDist * sin(angle), 18);

                // Cria um cilindro fino conectando os pontos
                // Vamos simular com uma caixa fina (box) orientada
                Vector3 rayMid = Vector3(6 + (startDist + endDist) * 0.5f * cos(angle),
                                        1.4 + (startDist + endDist) * 0.5f * sin(angle), 18);

                // Caixa fina ao longo do raio
                Vector3 boxMin(rayMid.x - 0.008f, rayMid.y - 0.008f, 17.98f);
                Vector3 boxMax(rayMid.x + 0.008f, rayMid.y + 0.008f, 18.02f);

                // Ajusta dimensões baseado no ângulo
                if (fabs(cos(angle)) > fabs(sin(angle))) {
                    boxMin.x = rayStart.x;
                    boxMax.x = rayEnd.x;
                } else {
                    boxMin.y = rayStart.y;
                    boxMax.y = rayEnd.y;
                }

                if (intersectBox(ray, boxMin, boxMax, boxRec)) {
                    if (boxRec.t < rec.t) {
                        rec = boxRec;
                        rec.color = Color(0.95f, 0.85f, 0.4f); // Dourado brilhante
                        rec.shininess = 60.0f;
                        rec.objectName = "Ostensorio - Raio Conector";
                    }
                }
            }

            // Vela (cilindro)
            if (intersectCylinder(ray, Vector3(8, 0, 17.5), 0.12f, 1.0f, cylRec)) {
                if (cylRec.t < rec.t) {
                    rec = cylRec;
                    if (candleLit) {
                        rec.color = Color(0.8f, 0.2f, 0.15f); // Vermelha
                    } else {
                        rec.color = Color(0.3f, 0.3f, 0.3f); // Cinza (apagada)
                    }
                    rec.shininess = 10.0f;
                    rec.objectName = candleLit ? "Vela (Acesa)" : "Vela (Apagada)";
                }
            }

            // Chama da vela (cone) - só se acesa
            if (candleLit) {
                HitRecord coneRec;
                if (intersectCone(ray, Vector3(8, 1.3, 17.5), 0.08f, 0.3f, coneRec)) {
                    if (coneRec.t < rec.t) {
                        rec = coneRec;
                        rec.color = Color(1.0f, 0.8f, 0.0f); // Amarela
                        rec.shininess = 5.0f;
                        rec.objectName = "Chama da Vela";
                    }
                }
            }

            // Se acertou algo, calcula iluminação
            if (rec.hit) {
                // Objetos emissivos (brilham por conta própria)
                if (rec.objectName == "Janela de Vitral") {
                    // Vitral é emissivo com textura
                    if (rec.useTexture && rec.texture && rec.texture->isLoaded()) {
                        Color texColor = rec.texture->sample(rec.u, rec.v);
                        pixelColor = texColor * EMISSIVE_VITRAL;
                    } else {
                        pixelColor = rec.color * EMISSIVE_VITRAL;
                    }
                } else if (rec.objectName == "Ostensorio - Hostia") {
                    // Hóstia brilha intensamente (fonte de luz divina)
                    pixelColor = rec.color * EMISSIVE_HOSTIA;
                } else if (rec.objectName == "Chama da Vela") {
                    // Chama da vela brilha
                    pixelColor = rec.color * EMISSIVE_CANDLE;
                } else if (rec.objectName == "Parede do Fundo" ||
                           rec.objectName == "Parede Esquerda" ||
                           rec.objectName == "Parede Direita" ||
                           rec.objectName == "Parede da Frente (Entrada)") {
                    // Paredes com emissão configurável
                    Vector3 viewDir = (ray.origin - rec.point).normalized();
                    Color litColor = phongShading(rec.point, rec.normal, viewDir,
                                                 rec.color, rec.shininess, lights, ambient,
                                                 rec.useTexture, rec.u, rec.v, rec.texture);

                    if (rec.useTexture && rec.texture && rec.texture->isLoaded()) {
                        Color texColor = rec.texture->sample(rec.u, rec.v);
                        pixelColor = litColor + texColor * EMISSIVE_WALLS;
                    } else {
                        pixelColor = litColor + rec.color * EMISSIVE_WALLS;
                    }
                } else if (rec.objectName == "Teto") {
                    // Teto com emissão configurável
                    Vector3 viewDir = (ray.origin - rec.point).normalized();
                    Color litColor = phongShading(rec.point, rec.normal, viewDir,
                                                 rec.color, rec.shininess, lights, ambient,
                                                 rec.useTexture, rec.u, rec.v, rec.texture);

                    if (rec.useTexture && rec.texture && rec.texture->isLoaded()) {
                        Color texColor = rec.texture->sample(rec.u, rec.v);
                        pixelColor = litColor + texColor * EMISSIVE_CEILING;
                    } else {
                        pixelColor = litColor + rec.color * EMISSIVE_CEILING;
                    }
                } else if (rec.objectName == "Chao") {
                    // Chão com emissão configurável
                    Vector3 viewDir = (ray.origin - rec.point).normalized();
                    Color litColor = phongShading(rec.point, rec.normal, viewDir,
                                                 rec.color, rec.shininess, lights, ambient,
                                                 rec.useTexture, rec.u, rec.v, rec.texture);

                    if (rec.useTexture && rec.texture && rec.texture->isLoaded()) {
                        Color texColor = rec.texture->sample(rec.u, rec.v);
                        pixelColor = litColor + texColor * EMISSIVE_FLOOR;
                    } else {
                        pixelColor = litColor + rec.color * EMISSIVE_FLOOR;
                    }
                } else {
                    // Objetos normais - usa iluminação Phong
                    Vector3 viewDir = (ray.origin - rec.point).normalized();
                    pixelColor = phongShading(rec.point, rec.normal, viewDir,
                                             rec.color, rec.shininess, lights, ambient,
                                             rec.useTexture, rec.u, rec.v, rec.texture);
                }
            }

            framebuffer[y * width + x] = pixelColor;
        }
    }
}

int main() {
    cout << "CAPELA RAY TRACING - CPU RENDERING\n" << endl;
    cout << "Controles:" << endl;
    cout << "  W/A/S/D - Mover camera" << endl;
    cout << "  Q/E - Subir/Descer" << endl;
    cout << "  Setas - Rotacionar camera" << endl;
    cout << "  Mouse - Picking (clique na vela para ligar/desligar)" << endl;
    cout << "  ESC - Sair" << endl;
    cout << "\nPara alterar transformacoes, iluminacao, camera, etc.:" << endl;
    cout << "  Edite: src/interactive_opengl.cpp (linhas 21-106)" << endl;
    cout << "  Recompile: make clean && make\n" << endl;

    // Carregar texturas
    cout << "Carregando texturas..." << endl;
    if (!woodTexture.load("textures/wood.jpg")) {
        cout << "  Aviso: Nao foi possivel carregar textura de madeira" << endl;
    } else {
        cout << "  ✓ Textura de madeira carregada" << endl;
    }

    if (!wallTexture.load("textures/wall.jpg")) {
        cout << "  Aviso: Nao foi possivel carregar textura de parede" << endl;
    } else {
        cout << "  ✓ Textura de parede carregada" << endl;
    }

    if (!stainedGlassTexture.load("textures/stained_glass.jpg")) {
        cout << "  Aviso: Nao foi possivel carregar textura de vitral" << endl;
    } else {
        cout << "  ✓ Textura de vitral carregada" << endl;
    }

    if (!ceilingTexture.load("textures/ceiling.jpg")) {
        cout << "  Aviso: Nao foi possivel carregar textura do teto (ceiling.jpg)" << endl;
    } else {
        cout << "  ✓ Textura do teto carregada" << endl;
    }

    cout << "\nRenderizando na CPU (sem aceleração GPU)...\n" << endl;

    // Inicializar SDL
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Capela Ray Tracing - CPU Rendering (Sem GPU)",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    SDL_GLContext context = SDL_GL_CreateContext(window);

    // Framebuffer na CPU
    vector<Color> framebuffer(WIDTH * HEIGHT);
    vector<unsigned char> pixelBuffer(WIDTH * HEIGHT * 3);

    // Criar textura OpenGL para display
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    // Setup OpenGL para display 2D
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);

    Camera camera;

    // Luzes (intensidades reduzidas)
    vector<Light> lights;
    // Luz da hóstia no ostensório (luz divina/sagrada)
    lights.push_back(Light(LIGHT_HOSTIA_POS, LIGHT_HOSTIA_COLOR));
    // Luz da vela (quente, quando acesa)
    lights.push_back(Light(LIGHT_CANDLE_POS, LIGHT_CANDLE_COLOR, candleLit));
    Color ambient = AMBIENT_LIGHT;

    bool running = true;
    bool needsRender = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                // Sistema de picking completo
                int mx = event.button.x;
                int my = event.button.y;

                float px = (2.0f * mx / WIDTH - 1.0f);
                float py = (1.0f - 2.0f * my / HEIGHT);

                Ray pickRay = camera.generateRay(px, py, (float)WIDTH / HEIGHT);
                HitRecord pickRec = performPicking(pickRay);

                if (pickRec.hit) {
                    // Calcula distância da câmera até o objeto
                    float distance = pickRec.t;

                    cout << "\n========== PICKING ==========" << endl;
                    cout << "Objeto: " << pickRec.objectName << endl;
                    cout << "Distancia da camera: " << fixed << setprecision(2) << distance << " unidades" << endl;
                    cout << "Posicao: (" << fixed << setprecision(2)
                         << pickRec.point.x << ", "
                         << pickRec.point.y << ", "
                         << pickRec.point.z << ")" << endl;
                    cout << "============================\n" << endl;

                    // Interatividade especial com a vela
                    if (pickRec.objectName == "Vela (Acesa)" || pickRec.objectName == "Vela (Apagada)") {
                        candleLit = !candleLit;
                        lights[1].enabled = candleLit;
                        needsRender = true;

                        if (candleLit) {
                            cout << "🕯️  Vela foi ACESA!" << endl;
                        } else {
                            cout << "💨 Vela foi APAGADA!" << endl;
                        }
                    }
                } else {
                    cout << "\n[Picking] Nenhum objeto foi clicado (ceu/background)\n" << endl;
                }
            }
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: running = false; break;

                    // Movimento da câmera
                    case SDLK_w: camera.moveForward(0.2f); needsRender = true; break;
                    case SDLK_s: camera.moveForward(-0.2f); needsRender = true; break;
                    case SDLK_a: camera.moveRight(-0.2f); needsRender = true; break;
                    case SDLK_d: camera.moveRight(0.2f); needsRender = true; break;
                    case SDLK_e: camera.moveUp(0.2f); needsRender = true; break;
                    case SDLK_q: camera.moveUp(-0.2f); needsRender = true; break;

                    // Rotação da câmera
                    case SDLK_LEFT: camera.rotate(-0.05f, 0); needsRender = true; break;
                    case SDLK_RIGHT: camera.rotate(0.05f, 0); needsRender = true; break;
                    case SDLK_UP: camera.rotate(0, 0.05f); needsRender = true; break;
                    case SDLK_DOWN: camera.rotate(0, -0.05f); needsRender = true; break;
                }
            }
        }

        // Renderiza apenas se necessário
        if (needsRender) {
            needsRender = false;

            cout << "Renderizando frame (CPU)..." << flush;
            auto start = chrono::high_resolution_clock::now();

            // Renderização multi-thread
            int numThreads = max(1, (int)thread::hardware_concurrency());
            int linesPerThread = HEIGHT / numThreads;
            vector<thread> threads;

            for (int i = 0; i < numThreads; i++) {
                int startY = i * linesPerThread;
                int endY = (i == numThreads - 1) ? HEIGHT : (i + 1) * linesPerThread;

                threads.emplace_back(renderTile, startY, endY, WIDTH, HEIGHT,
                                   ref(framebuffer), ref(camera), ref(lights), ref(ambient));
            }

            for (auto& t : threads) t.join();

            // Converte framebuffer para textura OpenGL
            for (int i = 0; i < WIDTH * HEIGHT; i++) {
                pixelBuffer[i * 3 + 0] = (unsigned char)(fmin(1.0, framebuffer[i].r) * 255);
                pixelBuffer[i * 3 + 1] = (unsigned char)(fmin(1.0, framebuffer[i].g) * 255);
                pixelBuffer[i * 3 + 2] = (unsigned char)(fmin(1.0, framebuffer[i].b) * 255);
            }

            glBindTexture(GL_TEXTURE_2D, texture);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixelBuffer.data());

            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
            cout << " OK (" << duration.count() << "ms)" << endl;
        }

        // Display usando OpenGL (GPU apenas mostra textura)
        glClear(GL_COLOR_BUFFER_BIT);
        glBindTexture(GL_TEXTURE_2D, texture);

        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(0, 0);
        glTexCoord2f(1, 0); glVertex2f(WIDTH, 0);
        glTexCoord2f(1, 1); glVertex2f(WIDTH, HEIGHT);
        glTexCoord2f(0, 1); glVertex2f(0, HEIGHT);
        glEnd();

        SDL_GL_SwapWindow(window);
        SDL_Delay(16); // ~60 FPS para display
    }

    glDeleteTextures(1, &texture);
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    cout << "\n✓ Programa encerrado." << endl;
    return 0;
}
