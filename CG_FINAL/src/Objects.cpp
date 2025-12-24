#include "../include/Objects.h"
#include <cmath>

const double EPSILON = 1e-6;

// SPHERE INTERSECTION
bool Sphere::intersect(const Ray& ray, HitRecord& rec) const {
    Vector3 oc = ray.origin - center;
    
    double a = ray.direction.dot(ray.direction);
    double b = 2.0 * oc.dot(ray.direction);
    double c = oc.dot(oc) - radius * radius;
    
    double discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0) {
        return false;
    }
    
    double sqrtDisc = std::sqrt(discriminant);
    double t1 = (-b - sqrtDisc) / (2 * a);
    double t2 = (-b + sqrtDisc) / (2 * a);
    
    double t = -1;
    if (t1 > EPSILON) {
        t = t1;
    } else if (t2 > EPSILON) {
        t = t2;
    } else {
        return false;
    }
    
    rec.t = t;
    rec.point = ray.at(t);
    rec.normal = (rec.point - center).normalized();
    rec.material = material;
    
    return true;
}

// PLANE INTERSECTION
bool Plane::intersect(const Ray& ray, HitRecord& rec) const {
    double denom = normal.dot(ray.direction);
    
    if (std::abs(denom) < EPSILON) {
        return false;
    }
    
    double t = (point - ray.origin).dot(normal) / denom;
    
    if (t < EPSILON) {
        return false;
    }
    
    rec.t = t;
    rec.point = ray.at(t);
    rec.normal = normal;
    rec.material = material;
    
    return true;
}

// CYLINDER INTERSECTION
bool Cylinder::intersect(const Ray& ray, HitRecord& rec) const {
    Vector3 oc = ray.origin - baseCenter;
    
    // Componentes perpendiculares ao eixo
    Vector3 dPerp = ray.direction - axis * ray.direction.dot(axis);
    Vector3 ocPerp = oc - axis * oc.dot(axis);
    
    double a = dPerp.dot(dPerp);
    double b = 2.0 * ocPerp.dot(dPerp);
    double c = ocPerp.dot(ocPerp) - radius * radius;
    
    double discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0) {
        return false;
    }
    
    double sqrtDisc = std::sqrt(discriminant);
    double t1 = (-b - sqrtDisc) / (2 * a);
    double t2 = (-b + sqrtDisc) / (2 * a);
    
    // Verifica ambas as soluções
    for (double t : {t1, t2}) {
        if (t < EPSILON) continue;
        
        Vector3 point = ray.at(t);
        double projOnAxis = (point - baseCenter).dot(axis);
        
        if (projOnAxis >= 0 && projOnAxis <= height) {
            rec.t = t;
            rec.point = point;
            Vector3 pointOnAxis = baseCenter + axis * projOnAxis;
            rec.normal = (point - pointOnAxis).normalized();
            rec.material = material;
            return true;
        }
    }
    
    return false;
}

// CONE INTERSECTION
bool Cone::intersect(const Ray& ray, HitRecord& rec) const {
    double cosAlphaSq = (height * height) / (height * height + radius * radius);
    
    Vector3 oc = ray.origin - baseCenter;
    
    double dDotV = ray.direction.dot(axis);
    double ocDotV = oc.dot(axis);
    
    double a = dDotV * dDotV - cosAlphaSq;
    double b = 2 * (dDotV * ocDotV - ray.direction.dot(oc) * cosAlphaSq);
    double c = ocDotV * ocDotV - oc.dot(oc) * cosAlphaSq;
    
    double discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0) {
        return false;
    }
    
    double sqrtDisc = std::sqrt(discriminant);
    double t1 = (-b - sqrtDisc) / (2 * a);
    double t2 = (-b + sqrtDisc) / (2 * a);
    
    for (double t : {t1, t2}) {
        if (t < EPSILON) continue;
        
        Vector3 point = ray.at(t);
        double projOnAxis = (point - baseCenter).dot(axis);
        
        if (projOnAxis >= 0 && projOnAxis <= height) {
            rec.t = t;
            rec.point = point;
            
            Vector3 pointOnAxis = baseCenter + axis * projOnAxis;
            Vector3 radial = (point - pointOnAxis).normalized();
            Vector3 tangent = axis;
            rec.normal = (radial - tangent * (radius / height)).normalized();
            rec.material = material;
            return true;
        }
    }
    
    return false;
}

// TRIANGLE INTERSECTION (Möller-Trumbore algorithm)
bool Triangle::intersect(const Ray& ray, HitRecord& rec) const {
    Vector3 edge1 = v1 - v0;
    Vector3 edge2 = v2 - v0;
    Vector3 h = ray.direction.cross(edge2);
    double a = edge1.dot(h);
    
    if (std::abs(a) < EPSILON) {
        return false;
    }
    
    double f = 1.0 / a;
    Vector3 s = ray.origin - v0;
    double u = f * s.dot(h);
    
    if (u < 0.0 || u > 1.0) {
        return false;
    }
    
    Vector3 q = s.cross(edge1);
    double v = f * ray.direction.dot(q);
    
    if (v < 0.0 || u + v > 1.0) {
        return false;
    }
    
    double t = f * edge2.dot(q);
    
    if (t < EPSILON) {
        return false;
    }
    
    rec.t = t;
    rec.point = ray.at(t);
    rec.normal = normal;
    rec.material = material;
    
    return true;
}

// MESH INTERSECTION
bool Mesh::intersect(const Ray& ray, HitRecord& rec) const {
    bool hitAnything = false;
    double closest = std::numeric_limits<double>::max();
    HitRecord tempRec;
    
    for (const auto& triangle : triangles) {
        if (triangle.intersect(ray, tempRec) && tempRec.t < closest) {
            closest = tempRec.t;
            rec = tempRec;
            hitAnything = true;
        }
    }
    
    return hitAnything;
}
