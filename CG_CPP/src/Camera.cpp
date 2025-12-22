#include "../include/Camera.h"
#include <cmath>

Camera::Camera()
    : eye(0, 0, 0), at(0, 0, -1), up(0, 1, 0),
      d(1.0), viewWidth(2.0), viewHeight(2.0),
      imageWidth(500), imageHeight(500) {
    computeCameraFrame();
}

Camera::Camera(const Vector3& eye, const Vector3& at, const Vector3& up,
               double d, double viewWidth, double viewHeight,
               int imageWidth, int imageHeight)
    : eye(eye), at(at), up(up), d(d),
      viewWidth(viewWidth), viewHeight(viewHeight),
      imageWidth(imageWidth), imageHeight(imageHeight) {
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
    
    // Ponto na janela de visualização
    Vector3 pointOnPlane = eye - w * d + u * x + v * y;
    
    // Direção do raio
    Vector3 direction = (pointOnPlane - eye).normalized();
    
    return Ray(eye, direction);
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
