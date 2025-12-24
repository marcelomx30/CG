#ifndef SCENE_H
#define SCENE_H

#include "Objects.h"
#include "Lights.h"
#include "Camera.h"
#include "Color.h"
#include <vector>
#include <memory>

class Scene {
public:
    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<PointLight>> pointLights;
    std::vector<std::shared_ptr<DirectionalLight>> directionalLights;
    std::vector<std::shared_ptr<SpotLight>> spotLights;
    std::shared_ptr<AmbientLight> ambientLight;
    Color backgroundColor;
    
    Scene();
    
    void addObject(std::shared_ptr<Object> obj);
    void addLight(std::shared_ptr<Light> light);
    void setAmbientLight(std::shared_ptr<AmbientLight> light);
    
    bool intersect(const Ray& ray, HitRecord& rec) const;
    bool isInShadow(const Vector3& point, const Vector3& lightPos) const;
    Color computeLighting(const HitRecord& hit, const Ray& ray) const;
    Color traceRay(const Ray& ray) const;
};

class Renderer {
public:
    Scene& scene;
    Camera& camera;
    
    Renderer(Scene& scene, Camera& camera);
    
    void render(const std::string& filename);
    void savePPM(const std::string& filename, const std::vector<std::vector<Color>>& image);
};

#endif // SCENE_H
