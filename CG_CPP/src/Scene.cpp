#include "../include/Scene.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>

Scene::Scene() : backgroundColor(0.1, 0.1, 0.15) {}

void Scene::addObject(std::shared_ptr<Object> obj) {
    objects.push_back(obj);
}

void Scene::addLight(std::shared_ptr<Light> light) {
    if (auto pointLight = std::dynamic_pointer_cast<PointLight>(light)) {
        pointLights.push_back(pointLight);
    } else if (auto dirLight = std::dynamic_pointer_cast<DirectionalLight>(light)) {
        directionalLights.push_back(dirLight);
    } else if (auto spotLight = std::dynamic_pointer_cast<SpotLight>(light)) {
        spotLights.push_back(spotLight);
    } else if (auto ambient = std::dynamic_pointer_cast<AmbientLight>(light)) {
        ambientLight = ambient;
    }
}

void Scene::setAmbientLight(std::shared_ptr<AmbientLight> light) {
    ambientLight = light;
}

bool Scene::intersect(const Ray& ray, HitRecord& rec) const {
    bool hitAnything = false;
    double closest = std::numeric_limits<double>::max();
    HitRecord tempRec;
    
    for (const auto& obj : objects) {
        if (obj->intersect(ray, tempRec) && tempRec.t < closest) {
            closest = tempRec.t;
            rec = tempRec;
            hitAnything = true;
        }
    }
    
    return hitAnything;
}

bool Scene::isInShadow(const Vector3& point, const Vector3& lightPos) const {
    Vector3 toLight = lightPos - point;
    double distanceToLight = toLight.length();
    Vector3 directionToLight = toLight.normalized();
    
    Ray shadowRay(point + directionToLight * 1e-4, directionToLight);
    
    HitRecord tempRec;
    for (const auto& obj : objects) {
        if (obj->intersect(shadowRay, tempRec) && tempRec.t < distanceToLight) {
            return true;
        }
    }
    
    return false;
}

Color Scene::computeLighting(const HitRecord& hit, const Ray& ray) const {
    const Material& mat = hit.material;
    Vector3 point = hit.point;
    Vector3 normal = hit.normal;
    Vector3 viewDir = -ray.direction;
    
    Color materialColor = mat.getDiffuseColor(point);
    
    Color ambient(0, 0, 0);
    if (ambientLight) {
        ambient = materialColor * ambientLight->intensity;  // USA COR DA TEXTURA!
    }
    
    Color diffuse(0, 0, 0);
    Color specular(0, 0, 0);
    
    for (const auto& light : pointLights) {
        Vector3 lightDir = (light->position - point).normalized();
        
        if (isInShadow(point, light->position)) {
            continue;
        }
        
        double nDotL = std::max(0.0, normal.dot(lightDir));
        if (nDotL > 0) {
            diffuse = diffuse + materialColor * light->intensity * nDotL;
            
            Vector3 reflectDir = lightDir.reflect(normal);
            double vDotR = std::max(0.0, viewDir.dot(reflectDir));
            if (vDotR > 0) {
                double specularFactor = std::pow(vDotR, mat.shininess);
                specular = specular + mat.ks * light->intensity * specularFactor;
            }
        }
    }
    
    for (const auto& light : directionalLights) {
        Vector3 lightDir = -light->direction;
        
        double nDotL = std::max(0.0, normal.dot(lightDir));
        if (nDotL > 0) {
            diffuse = diffuse + materialColor * light->intensity * nDotL;
            
            Vector3 reflectDir = lightDir.reflect(normal);
            double vDotR = std::max(0.0, viewDir.dot(reflectDir));
            if (vDotR > 0) {
                double specularFactor = std::pow(vDotR, mat.shininess);
                specular = specular + mat.ks * light->intensity * specularFactor;
            }
        }
    }
    
    for (const auto& light : spotLights) {
        Vector3 lightDir = (light->position - point).normalized();
        
        if (isInShadow(point, light->position)) {
            continue;
        }
        
        Color lightIntensity = light->getIntensityAt(point);
        
        double nDotL = std::max(0.0, normal.dot(lightDir));
        if (nDotL > 0) {
            diffuse = diffuse + materialColor * lightIntensity * nDotL;
            
            Vector3 reflectDir = lightDir.reflect(normal);
            double vDotR = std::max(0.0, viewDir.dot(reflectDir));
            if (vDotR > 0) {
                double specularFactor = std::pow(vDotR, mat.shininess);
                specular = specular + mat.ks * lightIntensity * specularFactor;
            }
        }
    }
    
    Color finalColor = ambient + diffuse + specular;
    finalColor.clamp(0, 1);
    return finalColor;
}

Color Scene::traceRay(const Ray& ray) const {
    HitRecord rec;
    
    if (intersect(ray, rec)) {
        return computeLighting(rec, ray);
    }
    
    return backgroundColor;
}

Renderer::Renderer(Scene& scene, Camera& camera)
    : scene(scene), camera(camera) {}

void Renderer::render(const std::string& filename) {
    int width = camera.imageWidth;
    int height = camera.imageHeight;
    
    std::vector<std::vector<Color>> image(height, std::vector<Color>(width));
    
    std::cout << "Renderizando cena " << width << "x" << height << "..." << std::endl;
    
    for (int j = 0; j < height; j++) {
        if (j % 50 == 0) {
            std::cout << "Linha " << j << "/" << height << std::endl;
        }
        
        for (int i = 0; i < width; i++) {
            Ray ray = camera.getRay(i, j);
            Color pixelColor = scene.traceRay(ray);
            image[j][i] = pixelColor;
        }
    }
    
    std::cout << "Salvando imagem..." << std::endl;
    savePPM(filename, image);
}

void Renderer::savePPM(const std::string& filename, const std::vector<std::vector<Color>>& image) {
    std::ofstream file(filename, std::ios::binary);
    
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir arquivo: " << filename << std::endl;
        return;
    }
    
    int height = image.size();
    int width = image[0].size();
    
    file << "P3\n" << width << " " << height << "\n255\n";
    
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            const Color& color = image[j][i];
            int r = static_cast<int>(255.99 * color.r);
            int g = static_cast<int>(255.99 * color.g);
            int b = static_cast<int>(255.99 * color.b);
            
            file << r << " " << g << " " << b << "\n";
        }
    }
    
    file.close();
    std::cout << "Imagem salva: " << filename << std::endl;
}
