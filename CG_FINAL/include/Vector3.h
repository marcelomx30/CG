#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <iostream>

class Vector3 {
public:
    double x, y, z;

    // Construtores
    Vector3() : x(0), y(0), z(0) {}
    Vector3(double x, double y, double z) : x(x), y(y), z(z) {}

    // Operadores
    Vector3 operator+(const Vector3& v) const {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }

    Vector3 operator-(const Vector3& v) const {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    Vector3 operator*(double t) const {
        return Vector3(x * t, y * t, z * t);
    }

    Vector3 operator/(double t) const {
        return Vector3(x / t, y / t, z / t);
    }

    Vector3 operator-() const {
        return Vector3(-x, -y, -z);
    }

    // Produto escalar
    double dot(const Vector3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    // Produto vetorial
    Vector3 cross(const Vector3& v) const {
        return Vector3(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }

    // Comprimento
    double length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    double lengthSquared() const {
        return x * x + y * y + z * z;
    }

    // Normalização
    Vector3 normalized() const {
        double len = length();
        if (len > 0) {
            return *this / len;
        }
        return Vector3(0, 0, 0);
    }

    void normalize() {
        double len = length();
        if (len > 0) {
            x /= len;
            y /= len;
            z /= len;
        }
    }

    // Reflexão
    Vector3 reflect(const Vector3& normal) const {
        return *this - normal * 2 * this->dot(normal);
    }

    // Acesso por índice
    double operator[](int i) const {
        if (i == 0) return x;
        if (i == 1) return y;
        return z;
    }

    double& operator[](int i) {
        if (i == 0) return x;
        if (i == 1) return y;
        return z;
    }
};

// Operador de multiplicação escalar à esquerda
inline Vector3 operator*(double t, const Vector3& v) {
    return v * t;
}

// Operador de saída
inline std::ostream& operator<<(std::ostream& out, const Vector3& v) {
    return out << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ")";
}

#endif // VECTOR3_H
