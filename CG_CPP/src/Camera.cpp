#include "../include/Camera.h"
#include <cmath>

Camera::Camera()
    : eye(0, 0, 0), at(0, 0, -1), up(0, 1, 0),
      d(1.0), viewWidth(2.0), viewHeight(2.0),
      imageWidth(500), imageHeight(500),
      projectionType(ProjectionType::PERSPECTIVE),
      obliqueAngle(45.0), obliqueFactor(1.0) {
    computeCameraFrame();
}

Camera::Camera(const Vector3& eye, const Vector3& at, const Vector3& up,
               double d, double viewWidth, double viewHeight,
               int imageWidth, int imageHeight)
    : eye(eye), at(at), up(up), d(d),
      viewWidth(viewWidth), viewHeight(viewHeight),
      imageWidth(imageWidth), imageHeight(imageHeight),
      projectionType(ProjectionType::PERSPECTIVE),
      obliqueAngle(45.0), obliqueFactor(1.0) {
    computeCameraFrame();
}

void Camera::computeCameraFrame() {
    // w aponta para trás (de at para eye)
    w = (eye - at).normalized();
    
    // u aponta para a direita
    u = up.cross(w).normalized();
    
    // v aponta para cima
    v = w.cross(u).normalized();
}

Ray Camera::getRay(int i, int j) const {
    // Normaliza coordenadas do pixel para [0, 1]
    double uCoord = (i + 0.5) / imageWidth;
    double vCoord = (j + 0.5) / imageHeight;

    // Mapeia para coordenadas da janela
    double x = (uCoord - 0.5) * viewWidth;
    double y = (0.5 - vCoord) * viewHeight;  // Inverte Y

    switch (projectionType) {
        case ProjectionType::PERSPECTIVE: {
            // Projeção perspectiva (padrão)
            Vector3 pointOnPlane = eye - w * d + u * x + v * y;
            Vector3 direction = (pointOnPlane - eye).normalized();
            return Ray(eye, direction);
        }

        case ProjectionType::ORTHOGRAPHIC: {
            // Projeção ortográfica: raios paralelos
            // Origem do raio varia, mas direção é sempre -w
            Vector3 origin = eye + u * x + v * y;
            Vector3 direction = -w;  // Todos os raios apontam na mesma direção
            return Ray(origin, direction);
        }

        case ProjectionType::OBLIQUE: {
            // Projeção oblíqua (cavalier/cabinet)
            // Raios paralelos mas em ângulo
            double angleRad = obliqueAngle * M_PI / 180.0;

            // Componente oblíqua ao longo de u (direita) e -w (profundidade)
            Vector3 obliqueDir = (-w + u * obliqueFactor * std::cos(angleRad)
                                      + v * obliqueFactor * std::sin(angleRad)).normalized();

            Vector3 origin = eye + u * x + v * y;
            return Ray(origin, obliqueDir);
        }

        default:
            // Fallback para perspectiva
            Vector3 pointOnPlane = eye - w * d + u * x + v * y;
            Vector3 direction = (pointOnPlane - eye).normalized();
            return Ray(eye, direction);
    }
}

void Camera::zoom(double factor) {
    viewWidth *= factor;
    viewHeight *= factor;
}

void Camera::setFOV(double fovDegrees) {
    double aspect = static_cast<double>(imageWidth) / imageHeight;
    double fovRad = fovDegrees * M_PI / 180.0;

    viewHeight = 2 * d * std::tan(fovRad / 2);
    viewWidth = viewHeight * aspect;
}

// ============ CONFIGURAÇÃO DE PROJEÇÕES ============

void Camera::setPerspective() {
    projectionType = ProjectionType::PERSPECTIVE;
}

void Camera::setOrthographic() {
    projectionType = ProjectionType::ORTHOGRAPHIC;
}

void Camera::setOblique(double angleDegrees, double factor) {
    projectionType = ProjectionType::OBLIQUE;
    obliqueAngle = angleDegrees;
    obliqueFactor = factor;
}

void Camera::setObliqueCabinet() {
    // Projeção cabinet: ângulo 63.4°, fator 0.5
    setOblique(63.4, 0.5);
}
