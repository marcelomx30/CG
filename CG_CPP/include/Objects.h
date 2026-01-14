#ifndef OBJECTS_H
#define OBJECTS_H

#include "Vector3.h"
#include "Ray.h"
#include "Material.h"
#include <vector>
#include <memory>
#include <limits>
#include <string>

// Forward declaration
class Object;

struct HitRecord {
    double t;
    Vector3 point;
    Vector3 normal;
    Material material;
    const Object* object;  // Ponteiro para objeto atingido (para picking)

    HitRecord() : t(std::numeric_limits<double>::max()), object(nullptr) {}
};

class Object {
public:
    Material material;
    std::string name;  // Nome/ID do objeto para picking

    Object() : name("unnamed") {}
    Object(const Material& mat) : material(mat), name("unnamed") {}
    Object(const Material& mat, const std::string& objName) : material(mat), name(objName) {}
    virtual ~Object() {}

    virtual bool intersect(const Ray& ray, HitRecord& rec) const = 0;
    virtual std::string getType() const = 0;  // Retorna tipo do objeto
};

// ESFERA
class Sphere : public Object {
public:
    Vector3 center;
    double radius;
    
    Sphere() : center(0, 0, 0), radius(1.0) {}
    Sphere(const Vector3& center, double radius, const Material& mat)
        : Object(mat), center(center), radius(radius) {}
    Sphere(const Vector3& center, double radius, const Material& mat, const std::string& name)
        : Object(mat, name), center(center), radius(radius) {}

    bool intersect(const Ray& ray, HitRecord& rec) const override;
    std::string getType() const override { return "Sphere"; }
};

// PLANO
class Plane : public Object {
public:
    Vector3 point;
    Vector3 normal;
    
    Plane() : point(0, 0, 0), normal(0, 1, 0) {}
    Plane(const Vector3& point, const Vector3& normal, const Material& mat)
        : Object(mat), point(point), normal(normal.normalized()) {}
    Plane(const Vector3& point, const Vector3& normal, const Material& mat, const std::string& name)
        : Object(mat, name), point(point), normal(normal.normalized()) {}

    bool intersect(const Ray& ray, HitRecord& rec) const override;
    std::string getType() const override { return "Plane"; }
};

// CILINDRO
class Cylinder : public Object {
public:
    Vector3 baseCenter;
    double radius;
    double height;
    Vector3 axis;
    
    Cylinder() : baseCenter(0, 0, 0), radius(1.0), height(2.0), axis(0, 1, 0) {}
    Cylinder(const Vector3& base, double r, double h, const Vector3& axis, const Material& mat)
        : Object(mat), baseCenter(base), radius(r), height(h), axis(axis.normalized()) {}
    Cylinder(const Vector3& base, double r, double h, const Vector3& axis, const Material& mat, const std::string& name)
        : Object(mat, name), baseCenter(base), radius(r), height(h), axis(axis.normalized()) {}

    bool intersect(const Ray& ray, HitRecord& rec) const override;
    std::string getType() const override { return "Cylinder"; }
};

// CONE
class Cone : public Object {
public:
    Vector3 baseCenter;
    double radius;
    double height;
    Vector3 axis;
    
    Cone() : baseCenter(0, 0, 0), radius(1.0), height(2.0), axis(0, 1, 0) {}
    Cone(const Vector3& base, double r, double h, const Vector3& axis, const Material& mat)
        : Object(mat), baseCenter(base), radius(r), height(h), axis(axis.normalized()) {}
    Cone(const Vector3& base, double r, double h, const Vector3& axis, const Material& mat, const std::string& name)
        : Object(mat, name), baseCenter(base), radius(r), height(h), axis(axis.normalized()) {}

    bool intersect(const Ray& ray, HitRecord& rec) const override;
    std::string getType() const override { return "Cone"; }
};

// TRIÂNGULO
class Triangle : public Object {
public:
    Vector3 v0, v1, v2;
    Vector3 normal;
    
    Triangle() : v0(0,0,0), v1(1,0,0), v2(0,1,0) {
        Vector3 edge1 = v1 - v0;
        Vector3 edge2 = v2 - v0;
        normal = edge1.cross(edge2).normalized();
    }
    
    Triangle(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Material& mat)
        : Object(mat), v0(v0), v1(v1), v2(v2) {
        Vector3 edge1 = v1 - v0;
        Vector3 edge2 = v2 - v0;
        normal = edge1.cross(edge2).normalized();
    }

    bool intersect(const Ray& ray, HitRecord& rec) const override;
    std::string getType() const override { return "Triangle"; }
};

// MALHA
class Mesh : public Object {
public:
    std::vector<Triangle> triangles;
    
    Mesh() {}
    Mesh(const Material& mat) : Object(mat) {}
    Mesh(const Material& mat, const std::string& name) : Object(mat, name) {}

    void addTriangle(const Triangle& tri) {
        triangles.push_back(tri);
    }

    bool intersect(const Ray& ray, HitRecord& rec) const override;
    std::string getType() const override { return "Mesh"; }
};

#endif // OBJECTS_H
