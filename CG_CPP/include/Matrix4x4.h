#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include "Vector3.h"
#include <cmath>
#include <array>

class Matrix4x4 {
public:
    std::array<std::array<double, 4>, 4> m;

    // Construtor padrão: matriz identidade
    Matrix4x4() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m[i][j] = (i == j) ? 1.0 : 0.0;
            }
        }
    }

    // Construtor com valores explícitos (por linha)
    Matrix4x4(const std::array<std::array<double, 4>, 4>& values) : m(values) {}

    // ============ OPERAÇÕES DE MATRIZ ============

    // Multiplicação de matrizes
    Matrix4x4 operator*(const Matrix4x4& other) const {
        Matrix4x4 result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.m[i][j] = 0.0;
                for (int k = 0; k < 4; k++) {
                    result.m[i][j] += m[i][k] * other.m[k][j];
                }
            }
        }
        return result;
    }

    // Transformação de ponto (coordenadas homogêneas)
    Vector3 transformPoint(const Vector3& v) const {
        double x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3];
        double y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3];
        double z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3];
        double w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3];

        // Normaliza por w se necessário
        if (w != 0.0 && w != 1.0) {
            return Vector3(x / w, y / w, z / w);
        }
        return Vector3(x, y, z);
    }

    // Transformação de vetor/direção (ignora translação)
    Vector3 transformDirection(const Vector3& v) const {
        double x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z;
        double y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z;
        double z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z;
        return Vector3(x, y, z);
    }

    // ============ TRANSFORMAÇÕES BÁSICAS ============

    // Matriz identidade
    static Matrix4x4 identity() {
        return Matrix4x4();
    }

    // Translação
    static Matrix4x4 translation(double tx, double ty, double tz) {
        Matrix4x4 result;
        result.m[0][3] = tx;
        result.m[1][3] = ty;
        result.m[2][3] = tz;
        return result;
    }

    static Matrix4x4 translation(const Vector3& t) {
        return translation(t.x, t.y, t.z);
    }

    // Escala
    static Matrix4x4 scale(double sx, double sy, double sz) {
        Matrix4x4 result;
        result.m[0][0] = sx;
        result.m[1][1] = sy;
        result.m[2][2] = sz;
        return result;
    }

    static Matrix4x4 scale(double s) {
        return scale(s, s, s);
    }

    // ============ ROTAÇÕES ============

    // Rotação em torno do eixo X (ângulo em radianos)
    static Matrix4x4 rotationX(double angle) {
        Matrix4x4 result;
        double c = cos(angle);
        double s = sin(angle);
        result.m[1][1] = c;
        result.m[1][2] = -s;
        result.m[2][1] = s;
        result.m[2][2] = c;
        return result;
    }

    // Rotação em torno do eixo Y (ângulo em radianos)
    static Matrix4x4 rotationY(double angle) {
        Matrix4x4 result;
        double c = cos(angle);
        double s = sin(angle);
        result.m[0][0] = c;
        result.m[0][2] = s;
        result.m[2][0] = -s;
        result.m[2][2] = c;
        return result;
    }

    // Rotação em torno do eixo Z (ângulo em radianos)
    static Matrix4x4 rotationZ(double angle) {
        Matrix4x4 result;
        double c = cos(angle);
        double s = sin(angle);
        result.m[0][0] = c;
        result.m[0][1] = -s;
        result.m[1][0] = s;
        result.m[1][1] = c;
        return result;
    }

    // Rotação arbitrária em torno de um eixo (Rodrigues' rotation formula)
    // angle: ângulo em radianos
    // axis: vetor de direção do eixo (será normalizado)
    static Matrix4x4 rotation(double angle, const Vector3& axis) {
        Vector3 a = axis.normalized();
        double c = cos(angle);
        double s = sin(angle);
        double t = 1.0 - c;

        Matrix4x4 result;
        result.m[0][0] = t * a.x * a.x + c;
        result.m[0][1] = t * a.x * a.y - s * a.z;
        result.m[0][2] = t * a.x * a.z + s * a.y;
        result.m[0][3] = 0.0;

        result.m[1][0] = t * a.x * a.y + s * a.z;
        result.m[1][1] = t * a.y * a.y + c;
        result.m[1][2] = t * a.y * a.z - s * a.x;
        result.m[1][3] = 0.0;

        result.m[2][0] = t * a.x * a.z - s * a.y;
        result.m[2][1] = t * a.y * a.z + s * a.x;
        result.m[2][2] = t * a.z * a.z + c;
        result.m[2][3] = 0.0;

        result.m[3][0] = 0.0;
        result.m[3][1] = 0.0;
        result.m[3][2] = 0.0;
        result.m[3][3] = 1.0;

        return result;
    }

    // ============ CISALHAMENTO (SHEARING) ============

    // Cisalhamento genérico
    // Cada parâmetro define quanto uma coordenada afeta outra
    // Ex: shxy = quanto x afeta y
    static Matrix4x4 shearing(double shxy, double shxz,  // X afeta Y e Z
                              double shyx, double shyz,  // Y afeta X e Z
                              double shzx, double shzy)  // Z afeta X e Y
    {
        Matrix4x4 result;
        result.m[0][1] = shxy;
        result.m[0][2] = shxz;
        result.m[1][0] = shyx;
        result.m[1][2] = shyz;
        result.m[2][0] = shzx;
        result.m[2][1] = shzy;
        return result;
    }

    // Cisalhamento no plano XY (Z constante)
    static Matrix4x4 shearingXY(double shx, double shy) {
        return shearing(shx, 0.0, shy, 0.0, 0.0, 0.0);
    }

    // ============ REFLEXÃO/ESPELHO ============

    // Reflexão em relação a um plano definido por sua normal
    // O plano passa pela origem
    static Matrix4x4 reflection(const Vector3& normal) {
        Vector3 n = normal.normalized();

        Matrix4x4 result;
        result.m[0][0] = 1.0 - 2.0 * n.x * n.x;
        result.m[0][1] = -2.0 * n.x * n.y;
        result.m[0][2] = -2.0 * n.x * n.z;

        result.m[1][0] = -2.0 * n.y * n.x;
        result.m[1][1] = 1.0 - 2.0 * n.y * n.y;
        result.m[1][2] = -2.0 * n.y * n.z;

        result.m[2][0] = -2.0 * n.z * n.x;
        result.m[2][1] = -2.0 * n.z * n.y;
        result.m[2][2] = 1.0 - 2.0 * n.z * n.z;

        return result;
    }

    // Reflexão em plano com offset (plano não passa pela origem)
    // planePoint: um ponto no plano
    // normal: vetor normal ao plano
    static Matrix4x4 reflectionPlane(const Vector3& planePoint, const Vector3& normal) {
        // Translada para origem, reflete, translada de volta
        Matrix4x4 t1 = translation(-planePoint.x, -planePoint.y, -planePoint.z);
        Matrix4x4 ref = reflection(normal);
        Matrix4x4 t2 = translation(planePoint.x, planePoint.y, planePoint.z);
        return t2 * ref * t1;
    }

    // Espelhos especiais nos planos principais
    static Matrix4x4 reflectionXY() {
        return reflection(Vector3(0, 0, 1));  // Espelho no plano XY
    }

    static Matrix4x4 reflectionXZ() {
        return reflection(Vector3(0, 1, 0));  // Espelho no plano XZ
    }

    static Matrix4x4 reflectionYZ() {
        return reflection(Vector3(1, 0, 0));  // Espelho no plano YZ
    }
};

#endif // MATRIX4X4_H
